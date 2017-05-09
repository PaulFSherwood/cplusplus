
/********************
*                   *
*   NeHeGL Header   *
*    SDL Version    *
*                   *
**********************************************************************************
*                                                                                *
*	You Need To Provide The Following Functions:                                 *
*                                                                                *
*	bool Initialize (void);                                                      *
*		Performs All Your Initialization                                         *
*		Returns TRUE If Initialization Was Successful, FALSE If Not              *
*                                                                                *
*	void Deinitialize (void);                                                    *
*		Performs All Your DeInitialization                                       *
*                                                                                *
*	void Update (Uint32 Milliseconds, Uint8 * Keys);                             *
*		Perform Motion Updates                                                   *
*		'Milliseconds' Is The Number Of Milliseconds Passed Since The Last Call  *
*		With Whatever Accuracy SDL_GetTicks() Provides                           *
*       'Keys' Is A Pointer To An Array Where The Snapshot Of The Keyboard       *
*       State Is Stored. The Snapshot Is Updated Every Time A Key Is Pressed     *
*                                                                                *
*	void Draw (void);                                                            *
*		Perform All Your Scene Drawing                                           *
*                                                                                *
*********************************************************************************/


#ifndef _MAIN_H_
#define _MAIN_H_


// Includes
#ifdef WIN32												// If We're Under MSVC
#include <windows.h>										// We Need The Windows Header
#else														// Otherwhise
#include <stdio.h>											// We Only Need The Standard IO Header
#endif														// And...
#include <SDL.h>											// The SDL Header Of Course :)


//Defines
#define APP_NAME	"NeHe OpenGL Basecode - SDL port by SnowDruid" // The App Name And Caption
#define APP_VERSION	"0.2"

#define SCREEN_W	640										// Screen Width Of Our App Is 640 Points
#define SCREEN_H	480										// SCreen Height Of Our App Is 480 Points
#define SCREEN_BPP	16										// Screen Depth Of Our App Is 16 bit (65536 Colors)

#define LOG_FILE	"log.txt"								// The Name Of The Log File


// Data Types
typedef struct												// We Use A Struct To Hold Application Runtime Data
{
	bool Visible;											// Is The Application Visible? Or Iconified?
	bool MouseFocus;										// Is The Mouse Cursor In The Application Field?
	bool KeyboardFocus;										// Is The Input Focus On Our Application?
}
	S_AppStatus;											// We Call It S_AppStatus


// Prototypes
int main(int, char **);										// The main() Function, Every Program Must Have One!		

bool InitErrorLog(void);									// Initializes The Error Log
void CloseErrorLog(void);									// Closes The Error Log
int  Log(char *, ...);										// Uses The Error Log :)

bool InitTimers(Uint32 *);									// Initializes The Timers
bool InitGL(SDL_Surface *);									// Performs OpenGL Scene Initialization
bool CreateWindowGL(SDL_Surface *, int, int, int, Uint32);	// Create The OpenGL Window
SDL_Surface *SetUpIcon(char *);								// Load  A Bitmap And Set It As The Window Icon

void ReshapeGL(int, int);									// Resize The OpenGL Scene
void ToggleFullscreen(void);								// Toggles Between Fullscreen/Windowed Modes (Linux/BeOS Only)
void TerminateApplication(void);							// Send A SDL_QUIT Event To The Queue

bool Initialize(void);										// Performs User Initializations
void Deinitialize(void);									// Performs User De-Initializations
void Update(Uint32, Uint8 *);								// Update Data
void Draw(SDL_Surface *);									// Do The Drawings
void Draw2D(SDL_Surface *);									// SDL Drawing routine
void Draw3D(SDL_Surface *);									// OpenGL Drawing routine

#endif
