// Main.cpp
// #include <vld.h>
#include "BleachUtils/Memory/EastlNew.h"
#include "BleachUtils/Debug/Debbuger.h"
#include "Application.h"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

void RunUpdate(Application& app)
{
  _LOG("ObjectSystem", "Tick");
  app.Update(33.3f);
  std::this_thread::sleep_for(500ms);
}

int main()
{
  Logger::Init();
  Logger::SetDisplayFlags("ObjectSystem", LOGFLAG_WRITE_TO_CONSOLE | LOGFLAG_WRITE_TO_DEBUGGER);

  Application app;
  app.Init();

  RunUpdate(app);
  RunUpdate(app);
  RunUpdate(app);

  system("pause");
  Logger::Destroy();

  return 0;
}
