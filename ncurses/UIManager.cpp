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
#include "UIManager.h"
#include "Screen.h"
#include "ThreadScreen.h"
#include "CommentsScreen.h"
#include "PostScreen.h"
#include "DialogScreen.h"
#include "WindowInfo.h"
#include <ncurses.h>

using namespace std;

/**
 * Constructor that initializes the overlay and also stores the current terminal resolution
 */
UIManager::UIManager():
	dialogShowing(false)
{
	// The position in WindowInfo isn't used since the terminal is always at (0,0)
	terminalSize.topRow = 0;
	terminalSize.leftCol = 0;
	
	// Get the initial terminal size and store it
	RefreshTerminalSize();
	
	// Create the dialog screen
	dialogScreen = new DialogScreen(this, WindowInfo(terminalSize.width, 3, terminalSize.height - 3, 0) );
}

/**
 * Destructor
 *
 * Clears the stack and cleans up the memory
 */
UIManager::~UIManager()
{
	// Clean up the UI cache
	map<string, Screen *>::iterator it;
	for (it = uiCache.begin() ; it != uiCache.end(); it++ )
	{
		delete it->second;
		it->second = NULL;
	}
	
	// Clean up the dialog
	if (dialogScreen != NULL)
	{
		delete dialogScreen;
		dialogScreen = NULL;
	}
}

/**
 * Returns the terminal size for rendering
 */
WindowInfo UIManager::GetTerminalSize() const
{
	return terminalSize;
}

/**
 * Get the current terminal size and stores it
 */
void UIManager::RefreshTerminalSize()
{
	getmaxyx(stdscr, terminalSize.height, terminalSize.width);
}

void UIManager::SetStoryId(const string& name, unsigned int id)
{
	map<string, Screen *>::iterator it;
	it = uiCache.find(name);
	if (it != uiCache.end())
	{
		it->second->SetStoryId(id);
	}
}

void UIManager::SetThreadId(const string& name, unsigned int id)
{
	map<string, Screen *>::iterator it;
	it = uiCache.find(name);
	if (it != uiCache.end())
	{
		it->second->SetThreadId(id);
	}
}

// TODO: These functions are really specific and should be done better.
// For now, it works. :(
void UIManager::SetStoryInfo(int id, int page)
{
	ThreadScreen * screen = (ThreadScreen *)uiCache["thread"];
	screen->SetStoryId(id);
	screen->SetPage(page);
}

void UIManager::SetReplyComment(const std::string& preview, const std::string& author, const std::string& date)
{
	PostScreen * screen = (PostScreen *)uiCache["post"];
	screen->SetPreview(preview, author, date);
}

/**
 * Set the title that will display in the upper right corner
 */
void UIManager::SetTitle(const string& title)
{
	this->title = title;
}

/**
 * Set the status to display near the bottom
 */
void UIManager::SetStatus(const string& status)
{
	this->status = status;
}

/**
 * Set the keys that will display at the bottom
 */
void UIManager::SetKeyString(const string& keys)
{
	this->keys = keys;
}

/**
 * Adds a screen to the UI cache
 */
void UIManager::AddUI(const string& name, Screen * sc)
{
	uiCache[name] = sc;
}

/**
 * Add a UI to the top of the stack
 * @param name Name of the screen to show
 */
void UIManager::PushUI(const string& name)
{
	map<string, Screen *>::iterator it;
	it = uiCache.find(name);
	if (it != uiCache.end())
	{
		uiStack.push(it->second);
		it->second->Initialize();
	}
}

/**
 * Set the text that will be displayed in the dialog screen.
 * @param text Text to show in the dialog
 */
void UIManager::SetDialogText(const string& text)
{
	if (dialogScreen != NULL)
	{
		dialogScreen->SetText(text);
	}
}

/**
 * Add a choice to the dialog screen.
 * @param text Text that will show up as the choice
 * @param ch Keypress that the choice corresponds to
 * @param defaultCh Bool determining if the person just presses enter, it will return this character.
 *	defaultCh is false unless otherwise.
 */
void UIManager::AddDialogChoice(const string& text, int ch, bool defaultCh)
{
	if (dialogScreen != NULL)
	{
		dialogScreen->AddChoice(text, ch, defaultCh);
	}
}

/**
 * Adds a dialog UI to show on the screen.  This will override the key inputs for
 * an UI.
 */
void UIManager::PushDialog()
{
	if (dialogScreen != NULL)
	{
		dialogScreen->Initialize();
		dialogShowing = true;
	}
}

/**
 * Removes the dialog screen and send the value of the key press to the screen that called it.
 * @param ch Character the dialog screen will return
 */
void UIManager::PopDialog(int ch)
{
	dialogShowing = false;
	Screen * topUI = uiStack.top();
	if (topUI != NULL)
	{
		topUI->HandleDialogReturn(ch);
	}
}

/**
 * Removes the top UI from the stack
 */
void UIManager::PopUI()
{
	uiStack.pop();
	Screen * topUI = uiStack.top();
	if (topUI != NULL)
	{
		topUI->HandleFocus();
	}
}

/**
 * Returns the current active UI, which is the top
 * @return Screen class of the active UI
 */
Screen * UIManager::TopUI()
{
	return uiStack.top();
}

/**
 * Checks to see if the UIManager has any screens on the stack
 * @return True if the UI stack is empty
 */
bool UIManager::IsEmpty() const
{
	return uiStack.empty();
}

/**
 * Handles passed in key presses and passes them to the top UI
 * @param ch Key that the user pressed
 */
void UIManager::HandleInput(int ch)
{
	// Always refreshing the terminal size
	RefreshTerminalSize();
	Screen * topUI = uiStack.top();
	
	// If there is a dialog screen, that will take all the input
	if (dialogShowing && dialogScreen != NULL)
	{
		dialogScreen->HandleInput(ch);
	}
	else if (topUI != NULL)
	{
		topUI->HandleInput(ch);
	}
}

/**
 * Clears the terminal screen
 */
void UIManager::Clear()
{
	clear();
}

/**
 * Refreshes and redraws the overlay and top window.  Note that this doesn't clear the screen
 * and redraw as clearing the screen constantly causes a flicker effect that doesn't look good.
 */
void UIManager::Refresh()
{
	// The title and status will override anything that may be drawn there
	DrawTitle();
	DrawStatus();
	refresh();
	
	// If the dialog is showing, draw that instead of the top UI and keys
	if (dialogShowing && dialogScreen != NULL)
	{
		dialogScreen->Refresh();
	}
	else
	{
		// Get the top UI and refresh it
		Screen * topUI = uiStack.top();
		if (topUI != NULL)
		{
			topUI->Refresh();
		}
		
		DrawKeys();
		refresh();
	}
}

/**
 * Draws the title at the top of the screen.
 */
void UIManager::DrawTitle()
{
	// NOTE: These strings should be located somewhere else for easier editing
	string appTitle = "LinuxChatty";
	string version = "v0.1a";
	
	// Calculate the spaces needed to fill the title bar
	WindowInfo res = GetTerminalSize();
	
	// The title bar will have a space in the beginning, the app title, space, version, spaces until the title at the
	// right hand side, the title, and a space (so 3 manditory spaces)
	unsigned int currentLen = 3 + appTitle.size() + version.size() + title.size();
	int spacesNeeded = res.width - currentLen;
	
	if (spacesNeeded < 0)
		spacesNeeded = 0;
	
	// Pad with spaces
	string padding(spacesNeeded, ' ');
	string msg = " " + appTitle + " " + version + padding + title + " ";
	
	// The title will always be at the top with the program title, version, and current navigation title
	wattron(stdscr, A_REVERSE);
	
	mvwprintw(stdscr, 0, 0, "%s", msg.c_str());
	
	wattroff(stdscr, A_REVERSE);
}

/**
 * Draws the status information at the bottom of the screen above the key inputs.
 */
void UIManager::DrawStatus()
{
	// The status will always be 2 lines above the bottom
	// Note that resolution is 0 based, so subtract an extra 1 to get the correct row
	WindowInfo res = GetTerminalSize();
	int row = res.height - 3;
	
	// Status will also be centered, so calculate the centered position
	int col = int((res.width - status.size()) / float(2));
	
	// Padding for clearing the status bar before rendering the new one
	string padding(res.width, ' ');
	mvwprintw(stdscr, row, 0, "%s", padding.c_str());
	
	// Render the status in reversed colors
	wattron(stdscr, A_REVERSE);
	mvwprintw(stdscr, row, col, "%s", status.c_str());
	wattroff(stdscr, A_REVERSE);
}

/**
 * Draws the string of valid keys centered at the bottom
 */
void UIManager::DrawKeys()
{
	WindowInfo res = GetTerminalSize();
	
	// Keys will also be centered, so calculate the centered position
	int col = int((res.width - keys.size()) / float(2));
	
	// Padding for clearing the key string before rendering the new one
	string padding(res.width, ' ');
	mvwprintw(stdscr, res.height - 2, 0, "%s", padding.c_str());
	mvwprintw(stdscr, res.height - 1, 0, "%s", padding.c_str());
	
	// Render the keys
	mvwprintw(stdscr, res.height - 1, col, "%s", keys.c_str());
}
