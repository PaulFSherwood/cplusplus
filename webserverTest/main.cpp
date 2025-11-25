#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mqtt/async_client.h>

#include "external/crow.h"
#include "external/crow/app.h"

// -----------------------------
// GLOBAL STATE
// -----------------------------
std::atomic<float> g_last_value{0.0f};

// -----------------------------
// MQTT Configuration
// -----------------------------
constexpr char MQTT_BROKER[]    = "tcp://test.mosquitto.org:1883";
constexpr char MQTT_TOPIC_PUB[] = "demo/heater/setpoint_cpp";
constexpr char MQTT_TOPIC_SUB[] = "demo/heater/status_cpp";


// -------------------------------------------------------
// MQTT CALLBACK (fixed braces + always prints)
// -------------------------------------------------------
class Callback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override
    {
        // Print MQTT message
        std::cout << "[MQTT] " << msg->get_topic()
                  << ": " << msg->to_string() << std::endl;

        // Store the value (if numeric)
        try {
            g_last_value = std::stof(msg->to_string());
        } catch (...) {
            // ignore parsing errors
        }
    }
};


// -------------------------------------------------------
// MQTT THREAD
// -------------------------------------------------------
void mqtt_thread()
{
    mqtt::async_client client(MQTT_BROKER, "cpp_client_ed");
    Callback cb;
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    try {
        std::cout << "[MQTT] Connecting..." << std::endl;
        client.connect(connOpts)->wait();

        auto subtok = client.subscribe(MQTT_TOPIC_SUB, 1);
        subtok->wait();   // WAIT FOR SUBACK
        std::cout << "[MQTT] Subscribed to " << MQTT_TOPIC_SUB << std::endl;

        // IMPORTANT: wait a bit to ensure broker handshake finished
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        // -------------------------------------------------------
        // Separate publisher client (AFTER SUBSCRIBE ACK)
        // -------------------------------------------------------
        mqtt::async_client pub(MQTT_BROKER, "cpp_publisher");
        pub.connect()->wait();

        std::thread([&pub]() {
            while (true) {
                float val = (rand() % 1000) / 10.0f;
                pub.publish(MQTT_TOPIC_SUB, std::to_string(val));
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }).detach();

        // keep thread alive
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (const mqtt::exception& e) {
        std::cerr << "MQTT Error: " << e.what() << std::endl;
    }
}

// -------------------------------------------------------
// MAIN + WEB SERVER
// -------------------------------------------------------
int main()
{
    // Launch MQTT listener thread
    std::thread(mqtt_thread).detach();

    crow::SimpleApp app;

    // -----------------------------
    // Web UI
    // -----------------------------
    CROW_ROUTE(app, "/")
    ([]() {
        return R"(
        <!DOCTYPE html>
        <html>
        <body style="font-family:sans-serif;">
        <h2>C++ MQTT Heater Control Test</h2>

        <!-- CURRENT VALUE -->
        <h3>Current Value: <span id="cur">--</span></h3>

        <!-- SEND SETPOINT -->
        <form action="/set" method="POST">
            Setpoint: <input name="value" type="number" step="0.1">
            <input type="submit" value="Send MQTT">
        </form>

        <script>
        // Poll server every second
        setInterval(() => {
            fetch('/api/value')
                .then(r => r.json())
                .then(j => {
                    document.getElementById('cur').innerText = j.value;
                });
        }, 1000);
        </script>

        </body>
        </html>
        )";
    });


    // -----------------------------
    // HTTP → MQTT
    // -----------------------------
    CROW_ROUTE(app, "/set").methods("POST"_method)
    ([](const crow::request& req)
    {
        auto mw = mqtt::async_client(MQTT_BROKER, "cpp_pub_client");
        try {
            mw.connect()->wait();

            auto val = req.url_params.get("value");
            if (!val)
                return crow::response(400, "Missing value");

            mw.publish(MQTT_TOPIC_PUB, val)->wait();
            mw.disconnect()->wait();

            std::string html = "<h3>Published MQTT Setpoint: ";
            html += val;
            html += "</h3><a href='/'>Back</a>";

            return crow::response(html);
        }
        catch (...) {
            return crow::response(500, "MQTT publish failed");
        }
    });


    // -----------------------------
    // API: SERVER STATUS
    // -----------------------------
    CROW_ROUTE(app, "/api/status")
    ([]() {
        crow::json::wvalue j;
        j["message"] = "Server OK";
        j["broker"]  = MQTT_BROKER;
        return j;
    });


    // -----------------------------
    // API: CURRENT VALUE (AJAX)
    // -----------------------------
    CROW_ROUTE(app, "/api/value")
    ([]() {
        crow::json::wvalue j;
        j["value"] = (double)g_last_value.load();
        return j;
    });


    // -----------------------------
    // Start Web Server
    // -----------------------------
    std::cout << "Web running at: http://localhost:8080\n";
    app.port(8080).multithreaded().run();
}
