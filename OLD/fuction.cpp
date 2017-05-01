#include <iostream>
void f();

main(void){
     f();
     std::cout << "we have returned" << std::endl;
     }
     
     void f() {
          std::cout << "line to show" << std::endl;
          return;
          std::cout << "dont show" << std::endl;
          
          }
