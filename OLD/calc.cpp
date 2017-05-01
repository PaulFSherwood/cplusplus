#include<iostream>
using namespace std;

int main(void)
{
    
    system("TITLE Calculator");
    system("COLOR 2");
    char eChar;
    double dfirstnumber;
    double dsecondnumber;
    char cDoagain;
    
    do
    {
         system("CLS");
         cout << "please enter the first number that you would like to use"
              << endl;
         cin >> dfirstnumber;
         cout << "please enter the second number you would like to use"
              << endl;         
         cout << "please enter the operation that you would like to complete"
              << " (+,-,*,/)" << endl;
         cin >> eChar;         
         
         switch (eChar)
         {
         case '+':
                cout << "The answer is: " << dfirstnumber << " + " <<
                dsecondnumber << " = " << (dfirstnumber + dsecondnumber)
                << endl;
                break;
         case '-':
                cout << "The answer is: " << dfirstnumber << " - " <<
                dsecondnumber << " = " << (dfirstnumber - dsecondnumber)
                << endl;
                break;
         case '*':
                cout << "The answer is: " << dfirstnumber << " * " <<
                dsecondnumber << " = " << (dfirstnumber * dsecondnumber)
                << endl;
                break;
         case 'x':
                cout << "The answer is: " << dfirstnumber << " x " <<
                dsecondnumber << " = " << (dfirstnumber * dsecondnumber)
                << endl;
                break;
         case 'X':
                cout << "The answer is: " << dfirstnumber << " X " <<
                dsecondnumber << " = " << (dfirstnumber * dsecondnumber)
                << endl;
                break;
         case '/':
              if(dsecondnumber == 0) {
              cout << "That is an invalid operation" << endl;
              }else{
                cout << "The answer is: " << dfirstnumber << " / " <<
                dsecondnumber << " = " << (dfirstnumber / dsecondnumber)
                << endl;
                }
                break;
                default:
                cout << "That is an invalid operation" << endl;
                break;
                }
                cout << "Would you like to start again? (y or n)" << endl;
                cin >> cDoagain;
                }while (cDoagain == 'Y' || cDoagain == 'y');
                system("PAUSE");
                return 0;
                }
