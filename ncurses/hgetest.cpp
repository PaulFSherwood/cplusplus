/* First, we include hge.h header and declare a variable to store the HGE interface pointer to: */

#include <hge.h>
HGE *hge = 0;

/* Then we create our frame function.  The frame function is a user-defined funtion that will be called
 * by HGE once-per frame: put your game loop code here.  When the frame function returns true.  the
 * HGE stops execution of game loop.
 *
 * In this example we just check whether ESC key has been pressed:
 */
 
 bool FrameFunc()
 {
 	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
 	return false;
 }
 
/* The WinMain function is a standard windows application entry point. Here we'll obtain a pointer to 
 * HGE interface to access HGE functions. In this example we use global pointer to HGE interface.  
 * Instead you may use hgeCreate function every time you need access to HGE. Just be sure to have  
 * a corresponding Release call for each call to hgeCreate.
 */

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  hge = hgeCreate(HGE_VERSION);

/* Then we set some internal HGE system states to configure the environment. Although most of the  
 * system states have appropriate defaults, at least HGE_FRAMEFUNC must be set before calling  
 * System_Start.
 */

  hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
  hge->System_SetState(HGE_WINDOWED, true);
  hge->System_SetState(HGE_USESOUND, false);
  hge->System_SetState(HGE_TITLE,
                 "HGE Tutorial 01 - Minimal HGE application");
                 
/* Now we initiate HGE with the states set. If something goes wrong, the System_Initiate function  
 * returns false and more specific description of what have happened can be read with  
 * System_GetErrorMessage. 
 *
 * Having HGE initiated we start the game loop with call to the System_Start function. The execution  
 * "stops" here until true is returned from the frame function.
 */

  if(hge->System_Initiate())
  {
    hge->System_Start();
  }
  else
  {	
    MessageBox(NULL, hge->System_GetErrorMessage(), "Error",
               MB_OK | MB_ICONERROR | MB_APPLMODAL);
  }
  
/* Now ESC has been pressed or the user has closed the window by other means. We should restore  
 * video mode and free all allocated resources. Also we should release the HGE interface:
 */

  hge->System_Shutdown();
  hge->Release();

  return 0;
}

/* Voila! Just about 20 lines of code and we have fully functional and running environment for a game! 

 * The complete source code with detailed comments for this tutorial you may find in the folder  
 * tutorials\tutorial01.
 */
