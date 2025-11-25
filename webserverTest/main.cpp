#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mqtt/async_client.h>

#include "external/crow.h"

// -----------------------------
// MQTT Configuration
// -----------------------------
constexpr char MQTT_BROKER[]    = "tcp://test.mosquitto.org:1883";
constexpr char MQTT_TOPIC_PUB[] = "demo/heater/setpoint_cpp";
constexpr char MQTT_TOPIC_SUB[] = "demo/heater/status_cpp";

class Callback : public virtual mqtt::callback {
   public:
      void message_arrived(mqtt::const_message_ptr msg) override {
         std::cout << "[MQTT] " << msg->get_topic()
                   << ": " << msg->to_string() << std::endl;
      }
};

// -----------------------------
// MQTT Thread Function 
// -----------------------------
void mqtt_thread() {
   mqtt::async_client client(MQTT_BROKER, "cpp_client_ed");
   Callback db;
   client.set_callback(db);

   mqtt::connect_options connOpts;
   connOpts.set_clean_session(true);

   try {
      std::cout << "[MQTT] Connecting..." << std::endl;
      client.connect(connOpts)->wait();
      client.subscribe(MQTT_TOPIC_SUB, 1)->wait();
      std::cout << "[MQTT] Subscribed to " << MQTT_TOPIC_SUB << std::endl;

      while(true) {
         std::this_thread::sleep_for(std::chrono::seconds(1));
      }
   }
   catch (const mqtt::exception& e) {
      std::cerr << "MQTT Error: " << e.what() << std::endl;
   }
}
// -----------------------------
// Main Web Server (Crow) 
// -----------------------------
int main() {
   // Launch MQTT in its own thread
   std::thread(mqtt_thread).detach();

   crow::SimpleApp app;

   // -----------------------------
   // Web UI 
   // -----------------------------
   CROW_ROUTE(app, "/")
      ([](){ 
         return R"(
         <!DOCTYPE html>
         <html>
         <body style="font-family:sans-serif;">
            <h2>C++ MQTT Heater Control Test</h2>
            <form action="/set" method="POST">
               Setpoint: <input name"value" type="number" step="0.1">
               <input type="submit" value="Send MQTT">
            </form>
         </body>
         </html>
         )";
       });

   // -----------------------------
   // HTTP -> MQTT 
   // -----------------------------
   CROW_ROUTE(app, "/set").methods("POST"_method)
      ([](const crow::request& req){
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
       catch(...) {
         return crow::response(500, "MQTT publish failed");
       }
      });


   // -----------------------------
   // API TEST 
   // -----------------------------
   CROW_ROUTE(app, "/api/status")
      ([](){ 
       crow::json::wvalue j;
       j["message"] = "Server OK";
       j["broker"] = MQTT_BROKER;
       return j;
       });

   // Start Server
   std::cout << "Web running at: http://localhost:8080\n";
   app.port(8080).multithreaded().run();
}
