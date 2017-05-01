#include "/usr/include/X11/Xlib.h"
int main() {
    int delta_x = 500, delta_y = 160;
    Display *display = XOpenDisplay(0);
    Window root = DefaultRootWindow(display);
    XWarpPointer(display, None, root, 0, 0, 0, 0, delta_x, delta_y);
    XCloseDisplay(display);
    return 0;
}
