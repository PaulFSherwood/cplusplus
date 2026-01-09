/*
   Linux/X11 + GLX version of classic NeHe OpenGL framework
   Converted from Win32/WGL

   g++ 01_main.cpp -o program -lX11 -lGL -lGLU

*/

#include <X11/Xlib.h>        		// X11 core
#include <X11/keysym.h>     		// Key symbols
#include <GL/gl.h>          		// OpenGL
#include <GL/glu.h>         		// GLU
#include <GL/glx.h>         		// GLX (OpenGL for X11)
#include <cstring>
#include <cstdio>
#include <cstdlib>

// ---------------------------
// Global Variables (Linux)
// ---------------------------

Display*    gDisplay = nullptr;     // X Server connection
Window      gWindow  = 0;           // X Window handle
GLXContext  gContext = nullptr;     // OpenGL rendering context
Atom        gWmDelete;              // Window close event

bool keys[256];                     // Keyboard state array
bool active     = true;             // Window active flag
bool fullscreen = false;            // Fullscreen flag

int gWidth  = 640;
int gHeight = 480;

// ---------------------------
// Resize OpenGL Scene
// ---------------------------
void ReSizeGLScene(GLsizei width, GLsizei height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height); // Reset viewport

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Perspective projection
    gluPerspective(45.0f,
                   (GLfloat)width / (GLfloat)height,
                   0.1f,
                   100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// ---------------------------
// Initialize OpenGL
// ---------------------------
bool InitGL()
{
    glShadeModel(GL_SMOOTH);         // Smooth shading
    glClearColor(0, 0, 0, 0);        // Black background
    glClearDepth(1.0f);              // Depth buffer setup
    glEnable(GL_DEPTH_TEST);         // Enable depth testing
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,
           GL_NICEST);

    return true;
}

// ---------------------------
// Render Scene
// ---------------------------
// bool DrawGLScene()
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glLoadIdentity();
// 
//     // (Draw your scene here)
// 
//     return true;
// }

bool DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Move camera back so we can see something
    glTranslatef(0.0f, 0.0f, -5.0f);

    // ==========================================
    // Draw a simple colored triangle
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex3f( 0.0f,  1.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f); // Green
        glVertex3f(-1.0f, -1.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f); // Blue
        glVertex3f( 1.0f, -1.0f, 0.0f);
    glEnd();
    // ==========================================

    return true;
}

// ---------------------------
// Destroy Window / GL Context
// ---------------------------
void KillGLWindow()
{
    if (gContext)
    {
        glXMakeCurrent(gDisplay, None, nullptr);
        glXDestroyContext(gDisplay, gContext);
        gContext = nullptr;
    }

    if (gWindow)
    {
        XDestroyWindow(gDisplay, gWindow);
        gWindow = 0;
    }

    if (gDisplay)
    {
        XCloseDisplay(gDisplay);
        gDisplay = nullptr;
    }
}

// ---------------------------
// Create OpenGL Window
// ---------------------------
bool CreateGLWindow(const char* title,
                    int width,
                    int height,
                    bool fullscreenFlag)
{
    gWidth  = width;
    gHeight = height;
    fullscreen = fullscreenFlag;

    gDisplay = XOpenDisplay(nullptr);
    if (!gDisplay)
    {
        fprintf(stderr, "Cannot connect to X server\n");
        return false;
    }

    int screen = DefaultScreen(gDisplay);

    static int visualAttribs[] =
    {
        GLX_RGBA,
        GLX_DOUBLEBUFFER,
        GLX_DEPTH_SIZE, 16,
        None
    };

    XVisualInfo* vi = glXChooseVisual(gDisplay, screen, visualAttribs);
    if (!vi)
    {
        fprintf(stderr, "No suitable GLX visual\n");
        return false;
    }

    Colormap cmap = XCreateColormap(
        gDisplay,
        RootWindow(gDisplay, vi->screen),
        vi->visual,
        AllocNone
    );

    XSetWindowAttributes swa{};
    swa.colormap = cmap;
    swa.event_mask =
        ExposureMask |
        KeyPressMask |
        KeyReleaseMask |
        StructureNotifyMask |
        FocusChangeMask;

    gWindow = XCreateWindow(
        gDisplay,
        RootWindow(gDisplay, vi->screen),
        0, 0,
        width, height,
        0,
        vi->depth,
        InputOutput,
        vi->visual,
        CWColormap | CWEventMask,
        &swa
    );

    XStoreName(gDisplay, gWindow, title);

    // Enable window close button handling
    gWmDelete = XInternAtom(gDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(gDisplay, gWindow, &gWmDelete, 1);

    XMapWindow(gDisplay, gWindow);

    gContext = glXCreateContext(gDisplay, vi, nullptr, GL_TRUE);
    glXMakeCurrent(gDisplay, gWindow, gContext);

    ReSizeGLScene(width, height);

    if (!InitGL())
        return false;

    return true;
}

// ---------------------------
// Main Entry Point (Linux)
// ---------------------------
int main()
{
    memset(keys, 0, sizeof(keys));

    if (!CreateGLWindow("NeHe's OpenGL Framework (Linux)",
                        640, 480, false))
        return 1;

    bool done = false;

    while (!done)
    {
        while (XPending(gDisplay))
        {
            XEvent event;
            XNextEvent(gDisplay, &event);

            switch (event.type)
            {
                case ClientMessage:
                    if ((Atom)event.xclient.data.l[0] == gWmDelete)
                        done = true;
                    break;
            case KeyPress:
            {
                // Keycode is guaranteed 0–255
                unsigned int kc = event.xkey.keycode;
                if (kc < 256)
                    keys[kc] = true;
                break;
            }
            case KeyRelease:
            {
                unsigned int kc = event.xkey.keycode;
                if (kc < 256)
                    keys[kc] = false;
                break;
            }
            case ConfigureNotify:
				ReSizeGLScene(event.xconfigure.width,
                              event.xconfigure.height);
                break;
            }
        }

        // ESC to quit
        if (keys[XKeysymToKeycode(gDisplay, XK_Escape)])
            done = true;

        DrawGLScene();
        glXSwapBuffers(gDisplay, gWindow);
    }

    KillGLWindow();
    return 0;
}

