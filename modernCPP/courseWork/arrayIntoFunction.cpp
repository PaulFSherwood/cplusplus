#include <iostream>
#include <vector>
#include <array>

void PrintArray(int arr[], size_t size) {
   std::cout << "sizeof(arr) " << sizeof(&arr) << std::endl;
      
   for (int i = 0; i < size; i++) {
      std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
   }
}
void PrintVector(const std::vector<int>& vec) {
   // for (int i = 0; i < vec.size(); i++){
   //    std::cout << vec[i] << std::endl;
   // }
   for (int i = 0; i < vec.size(); i++) {
      std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
   }
}

int main() {

   int array[] = {1,3,5,7};
   std::vector<int> newVector = {7,5,3,1,9};
   PrintArray(array, 4);
   PrintVector(newVector);

   return 0;
}
