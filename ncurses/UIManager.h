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
#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

#include "WindowInfo.h"
#include <string>
#include <map>
#include <stack>

// Forward declares
class ScreenMessage;
class Screen;
class DialogScreen;

/**
* UIManager
*
* Handles all the windows that will be displayed on the screen and distributes
* the key presses to the respective active UIs
*/
class UIManager
{
public:
	// Basic Constructor/Destructor
	UIManager();
	~UIManager();
	
	// Accessor function
	// Returns the size of the terminal to render
	WindowInfo GetTerminalSize() const;
	
	// Refreshes the terminal size whenever a key is pressed to keep it up to date
	void RefreshTerminalSize();
	
	// Set the title and status to display on the screen
	void SetTitle(const std::string& title);
	void SetStatus(const std::string& status);
	void SetKeyString(const std::string& keys);
	
	// Set the id information for the screen
	void SetStoryId(const std::string& name, unsigned int id);
	void SetThreadId(const std::string& name, unsigned int id);
	
	// Set the information needed about specific screens
	// TODO: Make this more versatile and less coded in such a specific way
	void SetStoryInfo(int id, int page);
	void SetReplyComment(const std::string& preview, const std::string& author, const std::string& date);
	
	// Adds a UI to the manager
	void AddUI(const std::string& name, Screen * sc);
	
	// Pushes a new UI to the screen
	void PushUI(const std::string& name);
	
	// Setting text and adding choices for the dialog screen
	void SetDialogText(const std::string& text);
	void AddDialogChoice(const std::string& text, int ch, bool defaultCh=false);
	
	// Push the dialog screen to the screen
	// This UI will override any key input
	void PushDialog();
	void PopDialog(int ch);
	
	// Removes the UI from the top of the stack
	void PopUI();
	
	// Retrieves the top UI
	Screen * TopUI();
	
	// Returns true if there's no UIs on the stack
	bool IsEmpty() const;

	// Passes the input to the top UI
	void HandleInput(int ch);
	
	// Clears the screen
	void Clear();
	
	// Redraws all the UIs
	void Refresh();
	
private:
	// Helper functions for drawing the title bar, status bar, and key bindings
	void DrawTitle();
	void DrawStatus();
	void DrawKeys();
	
	// Title to display
	std::string title;
	
	// Status at the bottom
	std::string status;
	
	// List of valid keys at the bottom
	std::string keys;
	
	// Map of cached screens for faster loading
	std::map<std::string, Screen *> uiCache;
	
	// Stack that holds all the UIs on it
	std::stack<Screen *> uiStack;

	// Holds the current dialog box that is on the screen
	// Note that only one dialog box can be up at a time
	DialogScreen * dialogScreen;
	bool dialogShowing;
	
	// Keeps track of the terminal resolution
	WindowInfo terminalSize;
};

#endif
