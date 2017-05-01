#include "stdafx.h"
#include <iostream>
using namespace std;
#include "string"
#include <windows.h>


/*
                      windows.h
- I needed the COORD class which is found in this header

- I needed the Sleep(int); function which is defined in this header
  lol dont forget that capital S on Sleep, sheesh
  the int is a number of milliseconds; so Sleep(1000); pauses the console for 1 second

- I needed the function:
  SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coord );
  which is defined in this header
*/



void gotoxy ( short x, short y )
{
  COORD coord = {x, y};
  SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coord );
}

void Music (string WhatMusic);
void Scene (string WhatScene);
void Play (string PlayWhat, int Ax, int Ay , string ExtraCommnd);  //animations
void Delete(string DeleteWhat, int Ax, int Ay);
void Text(string WhatText, int Ax, int Ay, bool TypewriterEffect, int Speed);
void Object(string WhatObject, int Ax, int Ay, bool DeleteAfterDisplay, int Exposure);

void Refresh();
void Input();


//==Initialize Pixels=======

//=Dots=========
char d[256];
char Spike = 127;
char LGray = 176;
char MGray = 177;
char DGray = 178;

/*
//=UI=========
//lines
char  V=186 , v =179; //Capital means double lines (Horizontal Vertical)
char  H=205 , h =196; //Common  means single lines

//corners
char TL=201 , tl=218, Tl=213, tL=214; //(TopLeft, BottomRight ...)
char BL=200 , bl=192, bL=211, Bl=212; // Eg: tL= top left corner and the left 'side' is a double line
char BR=188 , br=217, Br=190, bR=189;
char TR=187 , tr=191, Tr=184, tR=183;

//T intersections
char vl=180, vL=181, Vl=182, VL=185; //The first letter means the orientation of a line
char vr=195, vR=198, Vr=199, VR=204; //The second letter is the 'direction towards which' another line shoots off...
char ht=193, hT=208, Ht=207, HT=202; //...from the first's midpoint at 90 degrees
char hb=194, hB=210, Hb=209, HB=203;

//Cross Intersections (eg: +)
char vh=197, vH=216, Vh=215, VH=206;



//=TEXTURE====

//stripes
char HStripesB = 220;
char HStripesT = 223;
char VStripesL = 221;
char VStripesR = 222;
char hbars = 196,HBars = 205;
char vbars = 179,VBars = 186; //(186 = curtains with open or close transition)


char ChainMail = 127;
char BeeHive = 240;
char BlackTablet = 254;
char Metal = 44;
char VBrick = 215;
char Grid = 197;

char Cells = 206;
char VCell = 185;
char VBamboo1 = 182;
char VBamboo2 = 199;
char City = 216;
char ScalesR = 242;
char ScalesL = 243;
char FineScalesR = 174;
char FineScalesL = 175;
char Grass = 251;
char Rough1 = 171;
char Rough2 = 172;
char Cheese = 228;  // well there you go.. this word is said in a cpp source




//============
char Spike = 127;
char LGray = 176;
char MGray = 177;
char DGray = 178;

*/

int Score=0,Lives=4,Hull=10,Shields=100;


string Weapon = "Basic"; //Automatic (sparse) , Seeker (nearest foe)
string Item = "None"; // Bomb
// other objects: powerups <P> (fills hull 'then' sheilds)

int GameState= 0;
int GameOver = 0;
int Position = 0;
int Selection[10]={0};
int RunOnce[5]={0,0,0,0,0};

//-----
int UI_Update=1;
int ScreenUpdate=1;
int GlobalCounter[3]={0,0,0};
//-----


//----
float PlayerX=23,PlayerY=5;
int SpriteX[5]={70,0,0,0,0};
int SpriteY[5]={0,0,0,0,0};// xy locations for upto 5 simultaneous sprites
int NumberOfObjects=0; // max 5 onscreen else will fade too much

int SFX_Busy=0; //if a sound is playing

string CurrentScene = "WhatScene";
string CurrentItem = "Default";

string Option_Speed = "MED";int Speed = 2;
string Option_Sound = "ON"; int Sound = 1; //1 or 0
















//===============================================================
//===============================================================
//===============================================================
//===============================================================




void main()
{
   Scene("Intro");

   gotoxy(0,0);
   system("color F0");
   for(int x=0;x<255;x++)d[x]=x; // Loads the Ascii Chart
   for(int x=0;x<2000;x++){cout<<d[219];}gotoxy(0,0); //Start with Black Screen

    Music("Power");

   Scene("Open");
   Scene("Title");
   Music("Intro");





   GameState=1;



   //-Game--------------------

   while(GameOver==0) //The Game Loop
   {
      if(GameState==1)
      {
         Scene("MAIN");
      }

      if(GameState==2)
      {
         Scene("MAIN_Option");
      }

      //if(GameState==3){Scene("MAIN");}Esc options menu

      if(GameState==4) //Level Setup
      {

         Input(); //listens for input

         Object("Player",PlayerX,PlayerY,1,100);

         gotoxy(SpriteX[0]+7,20);cout<<" ";
         gotoxy(SpriteX[0],20);cout<<d[237]; SpriteX[0]-=7;
         if(SpriteX[0]<7){gotoxy(7,20);cout<<" ";SpriteX[0]=70;}

         if(SpriteX[0]==PlayerX){Shields-=14;UI_Update=1;}

         //gotoxy(65,23);cout<<"a"<<GlobalCounter[2]<<" b"<<GlobalCounter[1]<<" c"<<GlobalCounter[0];

         Scene("Display_Panel");
         Refresh();
      }

   }




   Scene("Clear_Screen"); cout<< "END"; Sleep(50000);

}//VOID MAIN();



//===============================================================
//===============================================================
//===============================================================
//===============================================================

void Scene (string WhatScene)
{
   if(WhatScene=="Intro")
   {
      gotoxy(25,10);cout<< "Unvieling the Noob Interface Console";Sleep(3000);
      gotoxy(25,10);cout<< "                                    ";Sleep(700);

      gotoxy(35,9);cout<< "The ASCIJIN";Sleep(2000);

      gotoxy(33,11);cout<< "Noob Game Engine";Sleep(2000);

      Scene("Clear_Screen"); Sleep(1000);


   }//Scene("Intro");

   if(WhatScene=="Close")
   {
      for(int x=0;x<40;x++)
      {
         for(int y=0;y<25;y++){gotoxy(x,y);cout<<d[219];}
         for(int y=0;y<25;y++){gotoxy(79-x,y);cout<<d[219];}
         Sleep(50);
      }
   }

   if(WhatScene=="Open")
   {
      for(int x=40;x>=0;x--)
      {
         for(int y=0;y<25;y++){gotoxy(x,y);cout<<" ";}
         for(int y=0;y<25;y++){gotoxy(80-x,y);cout<<" ";}
         Sleep(50);
      }

   }//Scene("Open");



   if(WhatScene=="Title")
   {
      for(int x1=40, y1=12, x2=0, y2=3 , z=0;z==0;) //"Title" transition in
      {
         while(x2<32)
         {
            Object("Title1",x1,y1,1,15); //end 10,3
            Object("Title2",x2,y2,1,15); //end 33,12
             x2++;x1--;
         }
         x2=33;
         x1=10;

         while(y2<12)
         {
            Object("Title1",x1,y1,1,15); //end 10,3
            Object("Title2",x2,y2,1,15); //end 33,12
             y2++;y1--;
         }
         y1=3;
         y2=12;
         z=1;
      }

      Object("Title1",10,3,0,15);
      Object("Title2",33,12,0,15);

      for (int x=0,start=0;;x++) //Press Start
      {
         if(x%2==0)
         {
            gotoxy(34,21);cout<<"Press Start";
            for(int e=0;e<400;e++)
            {
               if(GetKeyState(0x20)<-100||GetKeyState(0x01)<-100){start = 1;}
               Sleep(1);
            }
         }

         if(x%2!=0)
         {
            gotoxy(34,21);cout<<"           ";
             for(int e=0;e<400;e++)
            {
               if(GetKeyState(0x20)<-100||GetKeyState(0x01)<-100){start = 1;}
               Sleep(1);
            }
         }

         if(start==1)
         {Scene("Clear_Screen");gotoxy(35,10); GameState=1;break;}

      }//Press Start

   }//Scene("Title");

   if(WhatScene=="MAIN")
   {
      Object("Title1",10,3,0,15);
      Object("Title2",33,12,0,15);
      gotoxy(33,21);cout<<"New Game";
      gotoxy(33,22);cout<<"Options";
      gotoxy(33,23);cout<<"Info";

      gotoxy(30,21);cout<<d[45]<<d[62];gotoxy(33,21);

      for(int highlight=1, selection=0, z=0; selection == 0;)
      {
         Sleep(10);

         if((GetKeyState(0x28)<-100)&&highlight==1)
         {gotoxy(30,21);cout<<"  ";highlight = 2;gotoxy(30,22);cout<<d[45]<<d[62]<<" ";while((GetKeyState(0x28)<-100))Sleep(10);}

         if((GetKeyState(0x28)<-100)&&highlight==2)
         {gotoxy(30,22);cout<<"  ";highlight = 3;gotoxy(30,23);cout<<d[45]<<d[62]<<" ";while((GetKeyState(0x28)<-100))Sleep(10);}

         if((GetKeyState(0x28)<-100)&&highlight==3)
         {gotoxy(30,23);cout<<"  ";highlight = 1;gotoxy(30,21);cout<<d[45]<<d[62]<<" ";while((GetKeyState(0x28)<-100))Sleep(10);}

         if((GetKeyState(0x26)<-100)&&highlight==1)
         {gotoxy(30,21);cout<<"  ";highlight = 3;gotoxy(30,23);cout<<d[45]<<d[62]<<" ";while((GetKeyState(0x26)<-100))Sleep(10);}

         if((GetKeyState(0x26)<-100)&&highlight==2)
         {gotoxy(30,22);cout<<"  ";highlight = 1;gotoxy(30,21);cout<<d[45]<<d[62]<<" ";while((GetKeyState(0x26)<-100))Sleep(10);}

         if((GetKeyState(0x26)<-100)&&highlight==3)
         {gotoxy(30,23);cout<<"  ";highlight = 2;gotoxy(30,22);cout<<d[45]<<d[62]<<" ";while((GetKeyState(0x26)<-100))Sleep(10);}

         if((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100)&&highlight==1) // Game Start
         {
            while((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100))Sleep(10);
            Scene("Clear_Screen");GameState=4;selection=1;
         }

         if((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100)&&highlight==2) // Option Menu
         {
            while((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100))Sleep(10);
            Scene("Clear_Screen");GameState=2;selection=1;
         }

      }



   }//Scene("MAIN");

   if(WhatScene=="MAIN_Option")
   {
      if(RunOnce[1]==0)
      {
         RunOnce[1]=1;

         Object("Option",30,1,0,0);

         gotoxy(3,10);cout<<"Speed";
         gotoxy(3,13);cout<<"Sound";
         gotoxy(3,16);cout<<"Exit";

         gotoxy(17,10);cout<< Option_Speed;
         gotoxy(17,13);cout<< Option_Sound ;
      }
      RunOnce[1]=0;


      for(int highlight=1, selection=0; selection<4;)
      {
         if(highlight==1)
         {
            Object("BUTTON1",1,9,0,0);Object("button1",1,12,0,0);Object("button1",1,15,0,0);
            Text("Option_Speed_Info",2 ,20,0,0);
         }

         if(highlight==2)
         {
            Object("button1",1,9,0,0);Object("BUTTON1",1,12,0,0);Object("button1",1,15,0,0);
            Text("Option_Sound_Info",2 ,20,0,0);
         }

         if(highlight==3)
         {
            Object("button1",1,9,0,0);Object("button1",1,12,0,0);Object("BUTTON1",1,15,0,0);
            Text("Option_Exit_Info",2 ,20,0,0);
         }


         while(!(GetKeyState(0x26)<-100) && !(GetKeyState(0x28)<-100) && !(GetKeyState(0x20)<-100) && !(GetKeyState(0x0D)<-100))
         {Sleep(10);}//Idle State

         if((GetKeyState(0x28)<-100)&&highlight==1)
         {highlight = 2;Delete("OptionInfo",2,20);while((GetKeyState(0x28)<-100))Sleep(10);}

         if((GetKeyState(0x28)<-100)&&highlight==2)
         {highlight = 3;Delete("OptionInfo",2,20);while((GetKeyState(0x28)<-100))Sleep(10);}

         if((GetKeyState(0x28)<-100)&&highlight==3)
         {highlight = 1;Delete("OptionInfo",2,20);while((GetKeyState(0x28)<-100))Sleep(10);}

         if((GetKeyState(0x26)<-100)&&highlight==1)
         {highlight = 3;Delete("OptionInfo",2,20);while((GetKeyState(0x26)<-100))Sleep(10);}

         if((GetKeyState(0x26)<-100)&&highlight==2)
         {highlight = 1;Delete("OptionInfo",2,20);while((GetKeyState(0x26)<-100))Sleep(10);}

         if((GetKeyState(0x26)<-100)&&highlight==3)
         {highlight = 2;Delete("OptionInfo",2,20);while((GetKeyState(0x26)<-100))Sleep(10);}


         if((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100) && highlight==1 && Option_Speed == "MED")
         {
            Option_Speed = "HI";Speed = 3;
            gotoxy(17,10);cout<<"   ";
            gotoxy(17,10);cout<< Option_Speed;
            while((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100))Sleep(10);
         }

         if((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100) && highlight==1 && Option_Speed == "HI")
         {
            Option_Speed = "LOW";Speed = 1;
            gotoxy(17,10);cout<<"   ";
            gotoxy(17,10);cout<< Option_Speed;
            while((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100))Sleep(10);
         }

         if((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100) && highlight==1 && Option_Speed == "LOW")
         {
            Option_Speed = "MED";Speed = 3;
            gotoxy(17,10);cout<<"   ";
            gotoxy(17,10);cout<< Option_Speed;
            while((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100))Sleep(10);
         }
         //-----
         if((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100) && highlight==2 && Option_Sound == "ON")
         {
            Option_Sound = "OFF";Sound = 0;
            gotoxy(17,13);cout<<"   ";
            gotoxy(17,13);cout<< Option_Sound;
            while((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100))Sleep(10);
         }

         if((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100) && highlight==2 && Option_Sound == "OFF")
         {
            Option_Sound = "ON";Sound = 1;
            gotoxy(17,13);cout<<"   ";
            gotoxy(17,13);cout<< Option_Sound;
            while((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100))Sleep(10);
         }
         //-----
         if((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100) && highlight==3)
         {
            while((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100))Sleep(10);
            Scene("Clear_Screen");GameState=1;selection=5;
         }



      //   if((GetKeyState(0x20)<-100)||(GetKeyState(0x0D)<-100)&&highlight==2) // Option Menu
      //   {Scene("Clear_Screen");GameState=2;selection=1;}

      }

   }//Scene("MAIN_Option");



   if(WhatScene=="Clear_Screen")
   {
      gotoxy(0,0);
      for(int x=0;x<2000;x++){cout<<" ";}
      gotoxy(0,0);
   }//Scene("Clear_Screen");



   if(WhatScene=="Display_Panel")
   {
      if(RunOnce[1]==0)
      {
         Object("Display_Panel",1,1,0,0);
         RunOnce[1]=1;
      }

      if(UI_Update==1)
      {

      //-Score-Display-------------------
         if(Score>=0 && Score<10){gotoxy(7,2); cout << "Score = ";gotoxy(15,2); cout << Score;}
         if(Score>=10 && Score<100){gotoxy(6,2); cout << "Score = ";gotoxy(14,2); cout << Score;}
         if(Score>=100 && Score<1000){gotoxy(5,2); cout << "Score = ";gotoxy(13,2); cout << Score;}
         if(Score>=1000 && Score<10000){gotoxy(4,2); cout << "Score = ";gotoxy(12,2); cout << Score;}
         if(Score>=10000 && Score<99999){gotoxy(3,2); cout << "Score = ";gotoxy(11,2); cout << Score;}
         if(Score>=99999){gotoxy(3,2); cout << "Score = ";Score=99999;gotoxy(11,2); cout << Score;}


      //-Lives-Display--------------------
         gotoxy(23,2); cout << "Ships = " << Lives;


      //-Item-Display--------------------
         Object(CurrentItem,39,1,0,0);


      //-Hull-Display--------------------
         gotoxy(46,2);
         cout<<"Hull ";

         if(Shields<=0 || Shields==100 )
         {
            for(int H=1;H<=10;H++)
            {
               if(H==Hull)
               {
                  for(int x=0;x<Hull;x++){cout<<d[178];}
                  for(int x=0;x<10-Hull;x++){cout<<" ";}
               }
            }
         }
         if(Shields<=0)Hull--;


      //-Shields-Display-----------------
         gotoxy(63,2);
         if(Shields<=0)Shields=0;
         if(Shields>99){cout<<" Shields= " << Shields << "%";}
         if(Shields<100){cout<<" Shields= " << Shields << "% ";}


         UI_Update=0;
      }


   }//Scene("Display_Panel");



}//void Scene();

//===============================================================
void Object(string WhatObject, int Ax, int Ay, bool DeleteAfterDisplay, int Exposure)
{

   if(WhatObject=="Title1")
   {
      for(int y=Ay;y<Ay+1;)
      {
         for(int x=Ax;x<Ax+33;x++)
         {
            if(x==Ax+1 || x==Ax+2 || x==Ax+3 || x==Ax+4 || x==Ax+7 || x==Ax+8 || x==Ax+9 || x==Ax+10 || x==Ax+15 || x==Ax+16)
            {gotoxy(x,y);cout<<DGray;}
            if(x==Ax+17 || x==Ax+23 || x==Ax+24 || x==Ax+25 || x==Ax+28 || x==Ax+29 || x==Ax+30 || x==Ax+31 || x==Ax+32)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+33;x++)
         {
            if(x==Ax || x==Ax+7 || x==Ax+11 || x==Ax+14 || x==Ax+18 || x==Ax+22 || x==Ax+28)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+33;x++)
         {
            if(x==Ax || x==Ax+7 || x==Ax+11 || x==Ax+14 || x==Ax+18 || x==Ax+21 || x==Ax+28)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+33;x++)
         {
            if(x==Ax+1 || x==Ax+2 || x==Ax+3 || x==Ax+7 || x==Ax+8 || x==Ax+9 || x==Ax+10 || x==Ax+14 || x==Ax+15 || x==Ax+16)
            {gotoxy(x,y);cout<<DGray;}
            if(x==Ax+17 || x==Ax+18 || x==Ax+21 || x==Ax+28 || x==Ax+29 || x==Ax+30 || x==Ax+31 || x==Ax+32)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+33;x++)
         {
            if(x==Ax+4 || x==Ax+7 || x==Ax+14 || x==Ax+18 || x==Ax+18 || x==Ax+21 || x==Ax+28)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+33;x++)
         {
            if(x==Ax+4 || x==Ax+7 || x==Ax+14 || x==Ax+18 || x==Ax+18 || x==Ax+22 || x==Ax+28)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+33;x++)
         {
            if(x==Ax || x==Ax+1 || x==Ax+2 || x==Ax+3 || x==Ax+7 || x==Ax+14 || x==Ax+18 || x==Ax+23 || x==Ax+24 || x==Ax+25)
            {gotoxy(x,y);cout<<DGray;}
            if(x==Ax+28 || x==Ax+29 || x==Ax+30 || x==Ax+31 || x==Ax+32)
            {gotoxy(x,y);cout<<DGray;}
         }
      }


      if(DeleteAfterDisplay==1)
      {
         Sleep(Exposure);
         for(int y=Ay;y<Ay+7;y++)
         {
            for(int x=Ax;x<Ax+41;x++){gotoxy(x,y);cout<<" ";}
         }
      }

   }//Object("Title1");

   if(WhatObject=="Title2")
   {
      for(int y=Ay;y<Ay+1;)
      {
         for(int x=Ax;x<Ax+40;x++)
         {
            if(x==Ax+2 || x==Ax+3 || x==Ax+4 || x==Ax+8 || x==Ax+9 || x==Ax+10 || x==Ax+14 || x==Ax+15 || x==Ax+17 || x==Ax+18)
            {gotoxy(x,y);cout<<DGray;}
            if(x==Ax+21 || x==Ax+22 || x==Ax+23 || x==Ax+24 || x==Ax+29 || x==Ax+30 || x==Ax+31 || x==Ax+35 || x==Ax+36 || x==Ax+37)
            {gotoxy(x,y);cout<<DGray;}
            if(x==Ax+38 || x==Ax+39)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+40;x++)
         {
            if(x==Ax+1 || x==Ax+7 || x==Ax+11 || x==Ax+14 || x==Ax+16 || x==Ax+18 || x==Ax+21 || x==Ax+25 || x==Ax+28 || x==Ax+32)
            {gotoxy(x,y);cout<<DGray;}
            if(x==Ax+37)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+40;x++)
         {
            if(x==Ax || x==Ax+7 || x==Ax+11 || x==Ax+14 || x==Ax+18 || x==Ax+21 || x==Ax+25 || x==Ax+28 || x==Ax+32 || x==Ax+37)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+40;x++)
         {
            if(x==Ax || x==Ax+7 || x==Ax+11 || x==Ax+14 || x==Ax+18 || x==Ax+21 || x==Ax+22 || x==Ax+23 || x==Ax+24 || x==Ax+28)
            {gotoxy(x,y);cout<<DGray;}
            if(x==Ax+29 || x==Ax+30 || x==Ax+31 || x==Ax+32 || x==Ax+37)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+40;x++)
         {
            if(x==Ax || x==Ax+7 || x==Ax+11 || x==Ax+14 || x==Ax+18 || x==Ax+21 || x==Ax+25 || x==Ax+28 || x==Ax+32 || x==Ax+37)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+40;x++)
         {
            if(x==Ax+1 || x==Ax+7 || x==Ax+11 || x==Ax+14 || x==Ax+18 || x==Ax+21 || x==Ax+25 || x==Ax+28 || x==Ax+32)
            {gotoxy(x,y);cout<<DGray;}
            if(x==Ax+37)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
         for(int x=Ax;x<Ax+40;x++)
         {
            if(x==Ax+2 || x==Ax+3 || x==Ax+4 || x==Ax+8 || x==Ax+9 || x==Ax+10 || x==Ax+14 || x==Ax+18 || x==Ax+21 || x==Ax+22)
            {gotoxy(x,y);cout<<DGray;}
            if(x==Ax+23 || x==Ax+24 || x==Ax+28 || x==Ax+32 || x==Ax+37)
            {gotoxy(x,y);cout<<DGray;}
         }
         y++;
      }


      if(DeleteAfterDisplay==1)
      {
         Sleep(Exposure);
         for(int y=Ay;y<Ay+7;y++)
         {
            for(int x=Ax;x<Ax+41;x++){gotoxy(x,y);cout<<" ";}
         }
      }

   }//Object("Title2");


   if(WhatObject=="Player")
   {
      int y=Ay;

      for(int x=Ax;x<Ax+7;x++)
      {if(x==Ax || x==Ax+1 || x==Ax+2){gotoxy(x,y);cout<<d[219];}}y++;

      for(int x=Ax;x<Ax+7;x++)
      {if(x==Ax+1 || x==Ax+2 || x==Ax+3 || x==Ax+4 || x==Ax+5 || x==Ax+6){gotoxy(x,y);cout<<d[219];}}y++;

      for(int x=Ax;x<Ax+7;x++){if(x==Ax+2 || x==Ax+7)
      {gotoxy(x,y);cout<<d[219];}}y++;

      for(int x=Ax;x<Ax+7;x++)
      {if(x==Ax+1 || x==Ax+2 || x==Ax+3 || x==Ax+4 || x==Ax+5 || x==Ax+6){gotoxy(x,y);cout<<d[219];}}y++;

      for(int x=Ax;x<Ax+7;x++)
      {if(x==Ax || x==Ax+1 || x==Ax+2){gotoxy(x,y);cout<<d[219];}}y++;

      gotoxy(Ax+7,Ay+1);cout<<d[92];
      gotoxy(Ax+7,Ay+3);cout<<d[47];
      gotoxy(Ax+7,Ay+2);cout<<d[222];

      gotoxy(Ax+3,Ay+2);cout<<d[205];
      gotoxy(Ax+4,Ay+2);cout<<d[205];
      gotoxy(Ax+5,Ay+2);cout<<d[205];
      gotoxy(Ax+6,Ay+2);cout<<d[181];




      if(DeleteAfterDisplay==1)
      {
         Sleep(Exposure);
         for(int y=Ay;y<Ay+7;y++)
         {
            for(int x=Ax;x<Ax+8;x++){gotoxy(x,y);cout<<" ";}
         }
      }

   }//Object("Player");


   if(WhatObject=="Option")
   {
      int y=Ay;

      for(int x=Ax;x<Ax+21;x++)
      {
         if(x==Ax || x==Ax+1 || x==Ax+2 || x==Ax+4 || x==Ax+5 || x==Ax+6 || x==Ax+8 || x==Ax+9 || x==Ax+10 || x==Ax+12)
         {gotoxy(x,y);cout<<d[219];}

         if(x==Ax+14 || x==Ax+15 || x==Ax+16 || x==Ax+18 || x==Ax+19 || x==Ax+20)
         {gotoxy(x,y);cout<<d[219];}
      }

      y++;
      for(int x=Ax;x<Ax+21;x++)
      {
         if(x==Ax || x==Ax+2 || x==Ax+4 || x==Ax+5 || x==Ax+6 || x==Ax+9 || x==Ax+12 || x==Ax+14 || x==Ax+16 || x==Ax+18)
         {gotoxy(x,y);cout<<d[219];}

         if(x==Ax+20)
         {gotoxy(x,y);cout<<d[219];}
      }

      y++;
      for(int x=Ax;x<Ax+21;x++)
      {
         if(x==Ax || x==Ax+1 || x==Ax+2 || x==Ax+4 || x==Ax+9 || x==Ax+12 || x==Ax+14 || x==Ax+15 || x==Ax+16 || x==Ax+18)
         {gotoxy(x,y);cout<<d[219];}

         if(x==Ax+20)
         {gotoxy(x,y);cout<<d[219];}
      }

      gotoxy(Ax-1,Ay+3);
      for(int x=0;x<23;x++){cout << d[205];}


      if(DeleteAfterDisplay==1)
      {
         Sleep(Exposure);
         for(int y=Ay;y<Ay+3;y++)
         {
            for(int x=Ax;x<Ax+22;x++){gotoxy(x,y);cout<<" ";}
         }
      }

   }//Object("Option");

   if(WhatObject=="button1")
   {
      int y=Ay;

      gotoxy(Ax,Ay);cout<<d[218];
      gotoxy(Ax+20,Ay);cout<<d[191];
      gotoxy(Ax,Ay+2);cout<<d[192];
      gotoxy(Ax+20,Ay+2);cout<<d[217];

      gotoxy(Ax,Ay+1);cout<<d[179];
      gotoxy(Ax+20,Ay+1);cout<<d[179];

      gotoxy(Ax+1,Ay);
      for(int x=0;x<19;x++){cout<<d[196];}

      gotoxy(Ax+1,Ay+2);
      for(int x=0;x<19;x++){cout<<d[196];}

      gotoxy(Ax+14,Ay);cout<<d[194];
      gotoxy(Ax+14,Ay+1);cout<<d[179];
      gotoxy(Ax+14,Ay+2);cout<<d[193];

   }//Object("button1");

   if(WhatObject=="BUTTON1")
   {
      int y=Ay;

      gotoxy(Ax,Ay);cout<<d[201];
      gotoxy(Ax+20,Ay);cout<<d[187];
      gotoxy(Ax,Ay+2);cout<<d[200];
      gotoxy(Ax+20,Ay+2);cout<<d[188];

      gotoxy(Ax,Ay+1);cout<<d[186];
      gotoxy(Ax+20,Ay+1);cout<<d[186];

      gotoxy(Ax+1,Ay);
      for(int x=0;x<19;x++){cout<<d[205];}

      gotoxy(Ax+1,Ay+2);
      for(int x=0;x<19;x++){cout<<d[205];}


      gotoxy(Ax+14,Ay);cout<<d[203];
      gotoxy(Ax+14,Ay+1);cout<<d[186];
      gotoxy(Ax+14,Ay+2);cout<<d[202];

   }//Object("BUTTON1");


   if(WhatObject=="Display_Panel")
   {

      int y=Ay;

      gotoxy(Ax,Ay);cout<<d[201];//tl
      gotoxy(Ax+77,Ay);cout<<d[187];//tr
      gotoxy(Ax,Ay+2);cout<<d[200];//bl
      gotoxy(Ax+77,Ay+2);cout<<d[188];//br

      gotoxy(Ax,Ay+1);cout<<d[186];
      gotoxy(Ax+77,Ay+1);cout<<d[186];

      gotoxy(Ax+1,Ay);for(int x=0;x<76;x++){cout<<d[205];}

      gotoxy(Ax+1,Ay+2);for(int x=0;x<76;x++){cout<<d[205];}


      gotoxy(Ax+17,Ay);cout<<d[203]; // V Line 1
      gotoxy(Ax+17,Ay+1);cout<<d[186];
      gotoxy(Ax+17,Ay+2);cout<<d[202];


      gotoxy(Ax+61,Ay);cout<<d[203]; // V Line 3
      gotoxy(Ax+61,Ay+1);cout<<d[186];
      gotoxy(Ax+61,Ay+2);cout<<d[202];


      //Current Item Box-------------------------------
      gotoxy(Ax+35,Ay-1);cout<<d[201];//tl
      gotoxy(Ax+43,Ay-1);cout<<d[187];//tr
      gotoxy(Ax+35,Ay+2);cout<<d[202];//bl
      gotoxy(Ax+43,Ay+2);cout<<d[202];//br

      gotoxy(Ax+36,Ay-1);for(int x=0;x<7;x++){cout<<d[205];}//ht

      for(int y=Ax;y<3;y++){gotoxy(Ax+35,y);cout<<d[186];}
      for(int y=Ax;y<3;y++){gotoxy(Ax+43,y);cout<<d[186];}

      gotoxy(Ax+36,Ay);for(int x=0;x<7;x++){cout<<" ";}

      gotoxy(Ax+35,Ay);cout<<d[185];
      gotoxy(Ax+43,Ay);cout<<d[204];


   }//Object("Display_Panel");

   if(WhatObject=="Item_M")
   {
      gotoxy(Ax,Ay);cout<<d[218];;
      gotoxy(Ax+2,Ay);cout<<d[191];
      gotoxy(Ax,Ay+1);cout<<d[212];
      gotoxy(Ax+2,Ay+1);cout<<d[190];;

      gotoxy(Ax+1,Ay);cout<<"M";

      gotoxy(Ax+1,Ay+1);cout<<d[205];

   }//Object("Item_M");


   if(WhatObject=="DefaultItem")
   {
      gotoxy(Ax,Ay);cout<<" ";
      gotoxy(Ax+2,Ay);cout<<" ";
      gotoxy(Ax,Ay+1);cout<<" ";
      gotoxy(Ax+2,Ay+1);cout<<" ";

      gotoxy(Ax+1,Ay);cout<<" ";

      gotoxy(Ax+1,Ay+1);cout<<" ";


   }//Object("Default");


}//void Object();

//===============================================================
void Delete(string DeleteWhat, int Ax, int Ay)
{
   if(DeleteWhat=="OptionInfo")
   {
      gotoxy(Ax,Ay);
      for(int y=Ay;y<Ay+3;y++)
      {for(int x=Ax;x<Ax+34;x++){gotoxy(x,y);cout<<" ";}}
   }

}//void Delete();

//===============================================================
void Text(string WhatText, int Ax, int Ay, bool TypewriterEffect, int Speed)
{
   if(WhatText=="Option_Speed_Info")
   {
      gotoxy(Ax,Ay);  cout<<"Sets The Animation FrameRate";
      gotoxy(Ax,Ay+1);cout<<"for All Motion. Higher Speeds";
      gotoxy(Ax,Ay+2);cout<<"will result in Fadier Picture";
   }//Text("");

   if(WhatText=="Option_Sound_Info")
   {
      gotoxy(Ax,Ay);  cout<<"Turn Console Sound Effects ON/OFF";
      gotoxy(Ax,Ay+1);  cout<<"('OFF' For Better Video Quality";
   }//Text("");

   if(WhatText=="Option_Exit_Info")
   {
      gotoxy(Ax,Ay);  cout<<"Save and Exit to Main Menu";
   }//Text("");



} //void Text();


//===============================================================
void Play (string PlayWhat, int Ax, int Ay , string ExtraCommnd)
{
   if(PlayWhat=="PlayWhat")
   {
   }

}//void Play();
//===============================================================

//===============================================================

//===============================================================

//===============================================================
void Music(string WhatMusic)
{
   if(Sound == 1)
   {
      if(WhatMusic=="Intro")
      {
         for(int x=0;x<2;x++)
         {
            Beep(150,220);
            Beep(150,220);
            Beep(150,220);
            Sleep(500);

            Beep(150,220);
            Beep(150,220);
            Beep(150,220);

            Sleep(150);

            Beep(140,220);
            Sleep(150);
            if(x<1){Beep(150,220);Sleep(500);}

            if(x>=1)
            {
               Beep(3000,200);
               Beep(1600,200);
               Beep(2600,200);
               Beep(1600,200);
            }

         }

      }

      if(WhatMusic=="Power")
      {
         for(int b=0;b<200;b++)if(b%3==0)Beep(10*b,10);
      }


      if(WhatMusic=="Boss")
      {
         for(int h=0;h<13;h++)Beep(10*h,500);
         for (int x=699, d=0;x<1000;x=x+40)
         {
            Beep(x+400,40);
            if(x>=700){x=600;d++;}
            if(d>=12)x=1020;

          }

         Sleep(1000);

      }


      if(WhatMusic=="MainSong"&&SFX_Busy==0)
      {
         if(GlobalCounter[0]%3==0)Beep(150,25);
         if(GlobalCounter[0]%4==0)Beep(1150,10);
         if(GlobalCounter[0]%1==0)Beep(150,20);
         if(GlobalCounter[0]%7==0)Beep(1000,10);
         if(GlobalCounter[0]%14==0)Beep(250,25);
      }

      if(WhatMusic=="SFX_Fire")
      {
         for(int b=0;b<200;b++)if(b%3==0)Beep(10*b,10);
      }



   }

}//void Music();

//===============================================================
void Refresh()
{
   UI_Update=0;
   ScreenUpdate=0;


      GlobalCounter[0]++;
      if(GlobalCounter[0]>=1000){GlobalCounter[1]++;GlobalCounter[0]=0;}
      if(GlobalCounter[1]>=1000){GlobalCounter[2]++;GlobalCounter[0]=0;}
      //divided the counter into 3 vars because i think int can only hold up to about 32000...
      //this way it can hold 1000*1000 = 1millon game cycles. = 27 hours of continuous play which is unlikely



   Music("MainSong");

   Speed=2;


   //Sleep((4-Speed)*1); //RefreshRate

}//void Refresh();

//===============================================================
void Input()
{
   if(GetKeyState(0x25)<-100)PlayerX--;
   if(GetKeyState(0x26)<-100)PlayerY--;
   if(GetKeyState(0x27)<-100)PlayerX++;
   if(GetKeyState(0x28)<-100)PlayerY++;

   if(GetKeyState(0x1B)<-100)GameState=1;
   if(GetKeyState(0x53)<-100)Sound=1;
}

//===============================================================

//===============================================================

//===============================================================

//===============================================================

//===============================================================

//===============================================================

//===============================================================
