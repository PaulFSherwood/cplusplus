//============================================================================
// Name        : switch.cpp
// Author      :
// Version     :
// http://www.youtube.com/watch?v=Zs-kdWI8C0Q&feature=autoplay&list=ULE4kkhjHGi4s&index=2&playnext=8
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
using namespace std;

int adding(int a,int b)
{
    int answer=0;
    answer = a+b;
    return answer;
}

int main()
{
	int userinput1;
	int userinput2;
	int answer1;
	char operator1;


	cout << "enter your first number" << endl;
		cin >> userinput1;
	cout << "enter your second number" << endl;
		cin >> userinput2;
	cout << "enter your operator like +, -, *, or /" << endl;
		cin >> operator1;

	switch(operator1){
	case '+':
		//answer1 = userinput1 + userinput2;
	//	printf("your answer is %d", answer1);
		adding(userinput1,userinput2);
		break;
	case '-':
		answer1 = userinput1 + userinput2;
		printf("your answer is %d", answer1);
		break;
	case '*':
		answer1 = userinput1 + userinput2;
		printf("your answer is %d", answer1);
		break;
	case '/':
		answer1 = userinput1 + userinput2;
		printf("your answer is %d", answer1);
		break;
	default:
		printf("i have detected an error and its you\n");
		printf("your numbers where %d and %d but %c didnt make any sense", userinput1, userinput2, operator1);
		break;
	}
	return 0;
}

