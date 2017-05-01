//headers
#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"

// Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

// Surfaces
SDL_Surface *wKey = NULL;
SDL_Surface *bKey = NULL;
SDL_Surface *wKey2 = NULL;
SDL_Surface *bKey2 = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

// event structure
SDL_Event event;

// The music that will be played
Mix_Chunk *cChord = NULL;
Mix_Chunk *c_sharpChord = NULL;
Mix_Chunk *dChord = NULL;
Mix_Chunk *e_flatChord = NULL;
Mix_Chunk *eChord = NULL;

SDL_Surface *load_image(std::string filename)
{
	// the imgaes thats loaded
	SDL_Surface *loadedImage = NULL;

	SDL_Surface *optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	// If the image loaded
	if(loadedImage != NULL)
	{
		// create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);

		// free the old surface
		SDL_FreeSurface(loadedImage);

		// if the surface was optimized
		if(optimizedImage != NULL)
		{
			// color key surface
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
		}
	}

	// return the optimized surface
	return optimizedImage;
}

void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL)
{
	// Holds offsets
	SDL_Rect offset;

	// get offsets
	offset.x = x;
	offset.y = y;

	// Blit
	SDL_BlitSurface(source, clip, destination, &offset);
}

bool init()
{
	// initialize all SDL subsystems
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	// Set up the screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	// if there was an error in setting up the screen
	if (screen == NULL)
	{
		return false;
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}

	// set the window caption
	SDL_WM_SetCaption("Piano", NULL);

	// If everything initialized fine
	return true;
}

bool load_files()
{
	// load the white key
	wKey = load_image("wKey.bmp");

	// load the black key
	bKey = load_image("bKey.bmp");

	// load white key 2
	wKey2 = load_image("wKey2.bmp");

	// load black key 2
	bKey2 = load_image("bKey2.bmp");

	// load the background
	background = load_image("bg.png");
	//////////**********//////////
	// If there was a problem in loading white key
	if (wKey == NULL)
	{
		std::cout << "problem loading white key\n";
		return false;
	}
	// If there was a problem in loading black key
	if (bKey == NULL)
	{
		std::cout << "problem loading black key\n";
		return false;
	}
	// If there was a problem in loading white key 2
	if (wKey2 == NULL)
	{
		std::cout << "problem loading white key2\n";
	}
	// If there was a problem loading black key 2
	if (bKey2 == NULL)
	{
		std::cout << "problem loading black key2\n";
	}
	// If there was a problem in loading the background
	if (background == NULL)
	{
		std::cout << "problem loading background\n";
		return false;
	}
	
	// load the sound chords
	cChord = Mix_LoadWAV("c.wav");
	c_sharpChord = Mix_LoadWAV("c_sharp.wav");
	dChord = Mix_LoadWAV("d.wav");
	e_flatChord = Mix_LoadWAV("e_flat.wav");
	eChord = Mix_LoadWAV("e.wav");

	if (cChord == NULL)
	{
		return false;
	}
	if (c_sharpChord == NULL)
	{
		return false;
	}
	if (dChord == NULL)
	{
		return false;
	}
	if (e_flatChord == false)
	{
		return false;
	}
	if (eChord == false)
	{
		return false;
	}
	
	// If everything loaded fine
	return true;
}

//Keys class
class Keys
{
	private:
	
	// Initialize bool values
	bool cState, vState, bState, fState, gState;
	
	// to see if the sound is already playing
	//bool isPlaying;

	public:
	// Initializes the variables
	Keys();

	// takes key presses and adjuest the key state
	void handle_input();

	// Shows the change of the key state graphicly
	void show();

	// Plays the sound based on the key states
	void keySounds();
};

Keys::Keys()
{
	// Initialize bool values
	bool cState=true, vState=true, bState=true, fState=true, gState=true;

	// to see if the sound is already playing
	//bool isPlaying=false;
}

void Keys::handle_input()
{
	// if a key was pressed
	if (event.type == SDL_KEYDOWN)
	{
		// set picture to highlighted
		switch(event.key.keysym.sym)
		{
			case SDLK_c:
				cState = false;		// state is zero false
				//isPlaying = true;	// state is one true
				break;
			case SDLK_v:
				vState = false;
				break;
			case SDLK_b:
				bState = false;				
				break;
			case SDLK_f:
				fState = false;
				break;
			case SDLK_g:
				gState = false;
				break;
		}
	}

	// If a key was released
	else if (event.type == SDL_KEYUP)
	{
		// set picture to normal
		switch(event.key.keysym.sym)
		{
			case SDLK_c:
				cState = true;
				//isPlaying = false;
				break;
			case SDLK_v:
				vState = true;
				break;
			case SDLK_b:
				bState = true;
				break;
			case SDLK_f:
				fState = true;
				break;
			case SDLK_g:
				gState = true;
				break;
		}
	}
}

void Keys::show()
{
	// show the updated keys
	if (cState)
	{
		//std::cout << "trying to apply surface wKey to 10,10\n";
		apply_surface(10, 10, wKey, background);	// Key "C" 
	}else{
		//std::cout << "trying to apply surface wKey2 to 10, 10\n";
		apply_surface(10, 10, wKey2, background);	// Key "C"
	}	
	if (vState)
	{		
		apply_surface(50, 10, wKey, background);	// Key "V"
	}else{
		apply_surface(50, 10, wKey2, background);	// Key "V"
	}
	if (bState)
	{
		apply_surface(90, 10, wKey, background);	// Key "B"
	}else{
		apply_surface(90, 10, wKey2, background);	// Key "B"
	}
	if (fState)
	{
		apply_surface(35, 10, bKey, background);	// Key "F"
	}else{
		apply_surface(35, 10, bKey2, background);	// Key "F"
	}
	if (gState)
		apply_surface(75, 10, bKey, background);	// Key "G"
	else
		apply_surface(75, 10, bKey2, background);	// Key "G"

}

void Keys::keySounds()
{
	// if the key is pressed and the sound is not currently being played.
	if (cState){}else
	{
		Mix_PlayChannel(-1, cChord, 0);
	}
	if (fState){}else
	{
		Mix_PlayChannel(-1, c_sharpChord, 0);
	}
	if (vState){}else
	{
		Mix_PlayChannel(-1, dChord, 0);
	}
	if (gState){}else
	{
		Mix_PlayChannel(-1, e_flatChord, 0);
	}
	if (bState){}else
	{
		Mix_PlayChannel(-1, eChord, 0);
	}	


}

void clean_up()
{
	// free the surfaces
	SDL_FreeSurface(wKey);
	SDL_FreeSurface(bKey);
	SDL_FreeSurface(wKey2);
	SDL_FreeSurface(bKey2);
	SDL_FreeSurface(background);
	Mix_FreeChunk(cChord);
	Mix_FreeChunk(c_sharpChord);
	Mix_FreeChunk(dChord);
	Mix_FreeChunk(e_flatChord);
	Mix_FreeChunk(eChord);
	

	// Quit SDL_mixer
	Mix_CloseAudio();

	// Quit SDL
	SDL_Quit();
}

int main(int argc, char *args[])
{
	std::cout << "main\n";
	// Quit flag
	bool quit = false;
	std::cout << "boot quit set\n";
	// Keys object
	Keys myKeys;

	// init 
	if (init() == false)
	{
		return 1;
	}
	std::cout << "Init good\n";
	
	// load the files
	if (load_files() == false)
	{
		return 1;
	}
	std::cout << "Files loaded\n";
	// while the user hasnt quit
	while (quit == false)
	{
	
		// while there events to handle
		while (SDL_PollEvent(&event))
		{
			// Handle the events for the piano keys
			myKeys.handle_input();
			
			// If the user has Xed out of the window
			if (event.type == SDL_QUIT)
			{
				// quit the program
				quit = true;
			}
			if (event.type == SDLK_ESCAPE)
			{
				// quit the program
				quit = true;
			}
		}

		// show the background
		apply_surface(0, 0, background, screen);
		
		apply_surface(10, 10, wKey, background);	// Key "C" 
		
		apply_surface(50, 10, wKey, background);	// Key "V"
		
		apply_surface(90, 10, wKey, background);	// Key "B"
	
		apply_surface(35, 10, bKey, background);	// Key "F"
		
		apply_surface(75, 10, bKey, background);	// Key "G"
		
		// Show the updated keys
		myKeys.show();

		// Play the sounds
		myKeys.keySounds();
		
		// update the screen
		if(SDL_Flip(screen) == -1)
		{
			return 1;
		}

	}

	// clean up
	clean_up();
	
	return 0;
}
