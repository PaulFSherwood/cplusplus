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
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "WindowInfo.h"
#include "Window.h"
#include <ncurses.h>

// Forward declaration
class UIManager;
 
/**
 * Screen
 * 
 * Base class that contains generic functions and variables for all terminal
 * screens.
 */
class Screen : public Window
{
public:
	// Constructor that stores a pointer to the UIManager for use and determines the size of the screen
	// to draw
	Screen(UIManager * m, WindowInfo& info);
	virtual ~Screen();

	// Resets the state of the screen to the defaults
	virtual void Initialize();
	
	// Handles the value returned by a dialog screen
	virtual void HandleDialogReturn(int ch);
	
	// Handles a passed in key press
	virtual void HandleInput(int ch);
	
	// Handles what to do when the screen is in focus (the top of the UI stack)
	virtual void HandleFocus();
	
	// All screens have the ability to show the valid hot keys at the bottom
	virtual void DisplayKeys();
	
	// Stores information about the current story and thread ids
	virtual void SetStoryId(const unsigned int storyId);
	virtual void SetThreadId(const unsigned int threadId);
	
	// Redraws the UI on the terminal
	virtual void Refresh();
	
protected:
	// All screens will have a reference to the UIManager in order to add new screens
	// or remove itself
	UIManager * manager;
	
	// Many of the screens require knowing the current story and thread that the chatty is on, whether to display
	// comments or to reply to them
	unsigned int storyId;
	unsigned int threadId;
};
 
#endif
