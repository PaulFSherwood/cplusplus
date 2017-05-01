# include <iostream>
# include <cmath>
# include <iomanip>
# include <cstdlib>
using namespace std;
int main()
{
int die1;
int die2;
int dice;
int bet;
int point;
int money = 100;
char roll;
char betChar;

do
{
cout << "You currently have $" << money << " on hand.";

cout << "\nPlace your bet and roll the dice (minimum $1): ";
cin >> bet;

while (bet < 1 || bet > money)
{
if (bet < 1)
cout << "\nDont be so cheap put some money on the table!";
if (bet > money)
cout << "\nYou don't have that much!";
cout << "\n\nPlace your bet and roll the dice (minimum $1): ";
cin >> bet;
}

cout << "You bet $" << bet << ".";


cin.get(roll);

die1 = rand() % 6 + 1;
die2 = rand() % 6 + 1;
dice = die1 + die2;

cout << "\nYou rolled a " << die1 << " and a " << die2
<< " for a total of " << dice << "."<<endl;

if (dice == 7 )
{
cout << "Youve won";
money += bet;
}


else if (dice == 11)
{
cout << "Youve lost";
money -= bet;
}

else
{
do
{
cout << "You currently have $" << money << " on hand."<<endl; //copied the betting loop you had
cout << "\nPlace your bet and roll the dice (minimum $1 - 'q' to quit): ";
cin >> betChar;
if (betChar == 'q' || betChar == 'Q');
exit(1);
bet = betChar;
while (bet < 1 || bet > money)
{
if (bet < 1)
cout << "\nC'mon, take a chance!";
if (bet > money)
cout << "\nYou don't have that much!";
cout << "\n\nPlace your bet (minimum $1): ";
cin >> bet;
}
cout << "You bet $" << bet << "."; //end betting loop

cin.get(roll);

die1 = rand() % 6 + 1;
die2 = rand() % 6 + 1;
dice = die1 + die2;

cout << "\nYou rolled a " << die1
<< " and a " << die2
<< " for a total of " << dice << ".";

if (dice == 7)
{
cout << "\nYOU WON!!!! lets raise the Stakes"<<endl;
money += bet;
}

if (dice == 11)
{
cout << "\nYOU LOSE its ok you can WIN it back"<<endl;
money -= bet;
}

else
{
cout << "\nCooooommmee on 7. "<<endl;

}

} while (dice != point || dice != 7);
}
} while (money > 0);

cout << "/nLooks like you ran out of money. "
<< "Thanks for playing!" << endl;




system("pause");
}
