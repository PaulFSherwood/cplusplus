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
 #include "Screen.h"
 #include "UIManager.h"
 #include "WindowInfo.h"
 
/**
 * Screen constructor
 * @param m Keeps track of the UIManager to add or end UIs
 * @param info Screen information with width, height, top, and left
 */
Screen::Screen(UIManager * m, WindowInfo& info):
	Window(info), manager(m), storyId(0), threadId(0)
{
	// Nothing else for now
}

/**
 * Destructor to clean up the memory allocated
 */
Screen::~Screen()
{
	// Nothing for now
}

/**
 * Resets the state of the screen to the defaults whenever the screen is added to the UI.
 * Should be over-writen by any classes that needs something done.
 */
void Screen::Initialize()
{
	// Nothing here
}

/**
 * This will be called whenever a dialog screen closes and the screen that called it will get
 * the character press from the dialog to determine what to do.
 */
void Screen::HandleDialogReturn(int ch)
{
	// Nothing here
}

/**
 * Default behavior for handling key presses.  Should be over-written by
 * classes that inherit this class.
 * @param ch User keypress value
 */
void Screen::HandleInput(int ch)
{
	// Nothing here
}

/**
 * Handles what to do when the screen gains focus again.
 */
void Screen::HandleFocus()
{
	// Nothing for now
}

/**
 * Displays the text at the bottom of the screen of available key presses.
 * Individual classes will handle what to display.
 */
void Screen::DisplayKeys()
{
	// By default display keys sets the string as nothing
	manager->SetKeyString("");
}

void Screen::SetStoryId(const unsigned int storyId)
{
	this->storyId = storyId;
}

void Screen::SetThreadId(const unsigned int threadId)
{
	this->threadId = threadId;
}

/**
 * Redraws the UI on the terminal
 */
void Screen::Refresh()
{
	if (window == NULL)
		return;
	
	wrefresh(window);
}
