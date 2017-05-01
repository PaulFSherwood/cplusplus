#include <iostream>
#include<windows.h>
using namespace std;

void AltEnter();
void pointerfunc(int* pitimes1, int* pitimes2, int* piPointer1);

int main()
{
    int iPointer = 0;
    int iTimes1;
    int iTimes2;
    
    AltEnter();
    pointerfunc(&iTimes1, &iTimes2, &iPointer);
    
    cout << iTimes1 << "*" << iTimes2 << "=" << iPointer << endl;
    system("pause");
    return 0;
}

void AltEnter()
{
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
    return;
}
void pointerfunc(int* pitimes1, int* pitimes2, int* piPointer1)
{
    
    cout << endl << "Input i1 and i2: ";
    cin >> *pitimes1 >> *pitimes2;
    *piPointer1 = (*pitimes1 * *pitimes2);
}
