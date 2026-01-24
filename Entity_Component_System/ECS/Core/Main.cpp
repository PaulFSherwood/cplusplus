#include "Application.h"

int main()
{
    Application app;    // Creates the App with private variables and functions
    app.Init();         // Starts the Init function : Sets up the video screen, starts adding the player with entities. Sets the player to initial location 
    app.Run();          // Starts the Run function : Adds in the input, movement, render and collision systems : then updates each.
    app.Shutdown();     // Cleanly kills Renderer, Window, and Quits SDL.
    return 0;
}

