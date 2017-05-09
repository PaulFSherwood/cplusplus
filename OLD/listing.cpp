// Listing 18.1
#include <iostream.h>
class Condition
{
   public:
      Condition() { }
      virtual ~Condition() {}
      virtual void Log() = 0;
};
   class Normal : public Condition
{
   public:
      Normal() { Log(); }
      virtual ~Normal() {}
      virtual void Log() { cout << "Logging normal conditions...\n"; }
};

   class Error : public Condition
{
   public:
      Error() {Log();}
      virtual ~Error() {}
      virtual void Log() { cout << "Logging error!\n"; }
};

   class Alarm : public Condition
{
   public:
      Alarm ();
      virtual   ~Alarm() {}
      virtual void Warn() { cout << "Warning!\n"; }
      virtual void Log() { cout << "General Alarm log\n"; }
      virtual void Call() = 0;

};

   Alarm::Alarm()
{
       Log();
      Warn();
}
   class FireAlarm : public Alarm
{
   public:
      FireAlarm(){Log();};
      virtual ~FireAlarm() {}
      virtual void Call() { cout<< "Calling Fire Dept.!\n"; }
      virtual void Log() { cout << "Logging fire call.\n"; }
};

   int main()
{
   int input;
   int okay = 1;
   Condition * pCondition;
   while (okay)
   {
      cout << "(0)Quit (1)Normal (2)Fire: ";
      cin >> input;
      okay = input;
      switch (input)
      {
         case 0: break;
         case 1:
            pCondition = new Normal;
            delete pCondition;
            break;
         case 2:
            pCondition = new FireAlarm;
            delete pCondition;
            break;
         default:
            pCondition = new Error;
            delete pCondition;
            okay = 0;
            break;
      }
   }
   return 0;
}
