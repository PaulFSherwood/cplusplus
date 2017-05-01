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
#ifndef _ABOUTSCREEN_H_
#define _ABOUTSCREEN_H_

#include "Screen.h"

// Forward declaration
class UIManager;
 
/**
 * AboutScreen
 * 
 * Displays information about the program
 */
class AboutScreen : public Screen
{
public:
	// Constructor that stores a pointer to the UIManager for use and determines the size of the screen
	// to draw
	AboutScreen(UIManager * m, WindowInfo info);
	
	// Initializes the screen
	virtual void Initialize();
	
	// Handles a passed in key press
	virtual void HandleInput(int ch);

	// Redraws the UI on the terminal
	virtual void Refresh();
};
 
#endif
