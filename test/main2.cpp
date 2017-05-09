#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int answer;     // integer
    int num1;
    int num2;
    double doubletrouble = 5.5;
    int doubletest = 5;
    string cup = "coffee";
    
    cout << doubletrouble << " " 
    << doubletest << " " 
    << cup << endl;
    
    cout << "enter number 1" << endl;
    cin >> num1;
    
    cout << "enter number 2" << endl;
    cin >> num2;
    
    answer = num1 + num2;
    
    cout << "answer is: " << answer << endl;
    
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
