
<!-- saved from url=(0076)http://linux-chatty.googlecode.com/svn-history/r42/trunk/ui/MainMenuScreen.h -->
<html><head><meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1"></head><body><pre style="word-wrap: break-word; white-space: pre-wrap;">/****************************************************************************
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
#ifndef _MAINMENUSCREEN_H_
#define _MAINMENUSCREEN_H_

#include "Screen.h"
#include "WindowInfo.h"
#include &lt;vector&gt;
 
// Forward declaration
class UIManager;
class ResourceTable;

/**
 * MainScreen
 *
 * Holds the main menu for the program.
 */
class MainMenuScreen : public Screen
{
public:
	MainMenuScreen(UIManager * m, ResourceTable * res, WindowInfo info);
	
	// Overriding base functions
	virtual void HandleFocus();
	virtual void HandleInput(int ch);
	virtual void Refresh();

private:
	// Private function for drawing the menu on the screen
	void PrintMenu();
	// Once a choice is selected, determine what to do with the choice
	void ParseChoice();
	
	// Resource for menu items
	ResourceTable * resource;
	
	// Stores which choice is highlighted
	unsigned int highlight;
};

#endif
</pre></body></html>