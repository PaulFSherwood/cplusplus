#include <iostream>
#include "Hannah.h"
using namespace std;

Hannah::Hannah()
{
}

Hannah::Hannah(int a){
	num = a;
}

Hannah Hannah::operator+(Hannah aso){
	Hannah brandnew;
	brandnew.num = num + aso.num;
	return(brandnew);
}
