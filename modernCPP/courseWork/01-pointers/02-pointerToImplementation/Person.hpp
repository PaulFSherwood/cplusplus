#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <memory>

class Person {
   public:
      Person(std::string s);
      ~Person();
      std::string GetAttributes();

   private:
      struct pImplPerson;
      // pImplPerson* m_impl;
      std::unique_ptr<pImplPerson> m_impl;

};

#endif
