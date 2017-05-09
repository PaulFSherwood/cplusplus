/****************************************************************************
 *
 *  LinuxChatty
 *  Copyright (C) 2010, David Hsu.
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 ***************************************************************************/
#ifndef _NCURSEWINDOW_H_
#define _NCURSEWINDOW_H_

#include "WindowInfo.h"
#include <ncurses.h>

/**
 * Window
 * Base class for any class that needs to draw on the screen with ncurses. This handles creating the
 * window and cleaning up after the class is destroyed
 */
class Window
{
public:
	Window(WindowInfo& info);
	virtual ~Window();
	
	// Returns the size and position information for the window
	WindowInfo GetWindowInfo() const;
	
	// Changes the position of the window
	void SetPosition(unsigned int top, unsigned int left);
	
	// Changes the window based on the WindowInfo
	void SetWindow(WindowInfo newInfo);
	
	// Virtual function for updating the view
	// Any inheriting class needs to implement this as each window draws differently
	virtual void Refresh() = 0;
	
protected:
	// ncurses window for displaying on the screen
	WINDOW * window;
	
	// Keeps track of the window size and position in the screen
	WindowInfo windowInfo;
};

#endif
