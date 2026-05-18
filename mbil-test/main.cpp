#include <iostream>
#include <string>
#include <vector>

enum class MessageType
{
  SensorReading,
  DisplayUpdate
};

struct Message 
{
  int tick{};
  std::string source;
  std::string destination;
  MessageType type{};
  double value{};
  std::string text;
};

class MessageBus
{
  public:
    void publish(const Message& message)
    {
      messages.push_back(message);
    }
    std::vector<Message> drain()
    {
      auto outgoing = messages;
      messages.clear();
      return outgoing;
    }
  private:
    std::vector<Message> messages;
};

class TemperatureSensor
{
  public:
    void update(int tick, MessageBus& bus)
    {
      double temperature = 72.0 + tick;

      bus.publish(Message{
          tick,
          "TEMP_SENSOR",
          "MC1",
          MessageType::SensorReading,
          temperature,
          ""
      });
    }
};

class MissionComputer
{
  public:
    void receive(const Message& message)
    {
      if (message.type == MessageType::SensorReading)
      {
        lastTemperature = message.value;
        hasTemperature = true;

        std::cout << "[MC1] received temperature: "
                  << lastTemperature << "\n";
      }
    }
    void update(int tick, MessageBus& bus)
    {
      if (!hasTemperature)
      {
        return;
      }
      bus.publish(Message{
          tick,
          "MC1",
          "DISPLAY",
          MessageType::DisplayUpdate,
          lastTemperature,
          "Temperature is " + std::to_string(lastTemperature)
          });
      std::cout << "[MC1] sent display update\n";
    }
  private:
    bool hasTemperature{false};
    double lastTemperature{};
};

class Display 
{
  public:
    void receive(const Message& message)
    {
      if (message.type == MessageType::DisplayUpdate)
      {
        std:: cout << "[DISPLAY] " << message.text << "\n";
      }
    }
};

int main()
{
  MessageBus bus;
  TemperatureSensor sensor;
  MissionComputer missionComputer;
  Display display;

  for (int tick = 1; tick <= 5; ++tick)
  {
    std::cout << "\n--- TICK " << tick << " ---\n";
    sensor.update(tick, bus);
    auto sensorMessages = bus.drain();
    for (const auto& message : sensorMessages)
    {
      if (message.destination == "MC1")
      {
        missionComputer.receive(message);
      }
    }
    missionComputer.update(tick, bus);
    auto computerMessages = bus.drain();
    for (const auto& message : computerMessages)
    {
      if (message.destination == "DISPLAY")
      {
        display.receive(message);
      }
    }
  }
  return 0;
}
