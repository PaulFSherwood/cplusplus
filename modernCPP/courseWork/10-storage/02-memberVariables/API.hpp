#ifndef API_HPP
#define API_HPP

struct API {
   API();
   ~API();

   // Member variable that belongs to each instance
   // int m_local = 1;
   // Static variables in a class exists outside of the class.
   // The scope is within the class.
   // Declaration
   static int MAJOR;
   static int MINOR;

   static int GetMajorVersion();

};

#endif
