#include <iostream>

template<typename T=int, int Size=10>
class Container {
   public:
      Container() {
         m_data = new T[Size];
         std::cout << Size << std::endl;
      }
      ~Container() {
         delete[] m_data;
      }

   private:
      T* m_data;
};

int main() {

   Container<int, 5> c1;
   Container<int, 7> c2;
   Container c3;

}
