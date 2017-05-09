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
#ifndef _SETTINGSSCREEN_H_
#define _SETTINGSSCREEN_H_

#include "Screen.h"
#include "WindowInfo.h"
#include <string>
#include <vector>

// Forward declarations
class UIManager;
class ThreadService;
class ResourceTable;
class RadioButton;
class TextField;

/**
 * SettingsScreen
 * Manipulates the settings for the API server, username, and password.
 * TODO: Thread flags as well
 */
class SettingsScreen : public Screen
{
public:
	SettingsScreen(UIManager * m, ThreadService * service, ResourceTable * res, WindowInfo info);
	~SettingsScreen();
	
	// Overriding virtual functions
	virtual void Initialize();
	virtual void DisplayKeys();
	virtual void HandleDialogReturn(int ch);
	virtual void HandleInput(int ch);
	virtual void Refresh();
	
private:
	// Helper function for printing the list of items to change
	void PrintSettings();
	
	// Handles selecting a radio button
	// TODO: This is actually a radio group in function form, so less versatile
	void HandleRadioSelection();
	
	// Changes what is in focus and what isn't
	void ChangeCurrentFocus(bool focus);
	
	// Helper for saving the changes to the XML file
	void SaveChanges();
	
	// Service that will generate and store the authorization
	ThreadService * threadService;
	
	// Resource class with information about servers and authentication
	ResourceTable * resource;
	
	// List of radio buttons to display
	std::vector<RadioButton *> radioButtons;
	
	// List of text fields to display
	std::vector<TextField *> textFields;
	
	// Specific text fields for extracting the values from
	// TODO: Not a good way of doing this
	TextField * customServerText;
	TextField * userText;
	TextField * passwordText;
	
	// The current field the person is on
	unsigned int currentField;
	
	// Index of the radio button selected
	unsigned int selectedServer;
	
	// Values for the custom server, username, and password
	std::string customServer;
	std::string username;
	std::string password;
};

#endif
