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
#include "SettingsScreen.h"
#include "UIManager.h"
#include "RadioButton.h"
#include "TextField.h"
#include "services/ThreadService.h"
#include "services/ResourceTable.h"
#include <string>

using namespace std;

/**
 * Constructor that takes a UIManager for reference
 * @param m Keeps track of the UIManager to add or end UIs
 * @param service ThreadService class with access to the shack API
 * @param res ResourceTable with information about servers and settings
 * @param info Screen information with width, height, top, and left
 */
SettingsScreen::SettingsScreen(UIManager * m, ThreadService * service, ResourceTable * res, WindowInfo info):
	Screen(m, info), threadService(service), resource(res), currentField(0), selectedServer(0)
{
	
}

/**
 * Destructor for cleaning up the vector of radio buttons and text fields.
 */
SettingsScreen::~SettingsScreen()
{
	for (unsigned int i = 0; i < radioButtons.size(); i++)
		delete radioButtons[i];
	
	// Deleting these fields will also clear the class fields since it's stored in it
	for (unsigned int i = 0; i < textFields.size(); i++)
		delete textFields[i];
}

/**
 * Initializes the screen from an XML settings file.  If not found, use defaults.
 */
void SettingsScreen::Initialize()
{
	unsigned int top = windowInfo.topRow;
	unsigned int left = windowInfo.leftCol;
	
	DisplayKeys();
	
	// Load from the XML resource file
	// TODO: Although this supports multiple servers, the current settings screen is only formatted for a maximum of 2 + a custom
	// Will fix this later.
	vector<RadioItem> serverList = resource->GetServerList();
	for (unsigned int i = 0; i < serverList.size(); i++)
	{
		RadioButton * rb = new RadioButton(WindowInfo(25, 1, top + i + 2, left), serverList[i].name);
		if (serverList[i].selected)
			rb->SetSelection(true);
		radioButtons.push_back( rb );
	}
	
	// Custom server field
	customServerText = new TextField(WindowInfo(30, 1, top + 5, left + 15));
	customServerText->SetText( resource->GetCustomServerURL() );
	textFields.push_back( customServerText );
	
	// Decode the authentication if there is any
	string username, password;
	string auth = resource->GetAuthentication();
	if (!auth.empty())
	{
		threadService->DecodeAuthorization(auth, username, password);
	}
	
	// Username field
	userText = new TextField(WindowInfo(40, 1, top + 10, left + 10));
	userText->SetText( username );
	textFields.push_back( userText );
	
	// Password field
	passwordText = new TextField(WindowInfo(30, 1, top + 11, left + 10));
	passwordText->SetPasswordField(true);
	passwordText->SetText( password );
	textFields.push_back( passwordText );
	
	ChangeCurrentFocus(true);
}

/**
 * Displays the hot keys at the bottom.
 */
void SettingsScreen::DisplayKeys()
{
	// If the selection is over a radio button, show that X will select it
	if (currentField < 2)
	{
		manager->SetKeyString( "[UP/DOWN] Select Field  [X] Change Radio  [F2] Save  [F7] Exit" );
	}
	else
	{
		manager->SetKeyString( "[UP/DOWN] Select Field  [F2] Save  [F7] Exit" );
	}
}

/**
 * Handle the return value from the dialog screen.  This screen will only pop up if trying to quit without saving.
 */
void SettingsScreen::HandleDialogReturn(int ch)
{
	// Handle ch
	if (ch == 'y')
	{
		manager->PopUI();
	}
	else
	{
		DisplayKeys();
	}
}

/**
 * Handle key presses from the user
 * @param ch User key press
 */
void SettingsScreen::HandleInput(int ch)
{
	switch(ch)
	{
		case KEY_UP:
			ChangeCurrentFocus(false);
			// Move to the previous field
			if (currentField > 0)
				currentField--;
			ChangeCurrentFocus(true);
			DisplayKeys();
			break;
		case KEY_DOWN:
			ChangeCurrentFocus(false);
			// Move to the next field
			if (currentField < radioButtons.size() + textFields.size() - 1)
				currentField++;
			ChangeCurrentFocus(true);
			DisplayKeys();
			break;
		case KEY_F(7):
			// Exit without saving
			// Dialog to confirm
			manager->PushDialog();
			manager->SetDialogText("Are you sure you want to quit without saving?");
			manager->AddDialogChoice("Yes", 'y');
			manager->AddDialogChoice("[No]", 'n');
			break;
		case KEY_F(2):
			// Save the settings
			// TODO: Save the settings and display whether the authentication worked
			SaveChanges();
			manager->PopUI();
			break;
		default:
			// Send the input to the currently selected radio/text field
			// TODO: Fix this hard code mess!
			if (currentField < 2)
			{
				radioButtons[currentField]->HandleInput(ch);
			}
			else
			{
				textFields[currentField - 2]->HandleInput(ch);
			}
			break;
	}
	Refresh();
}

/**
 * Refreshes the screen
 */
void SettingsScreen::Refresh()
{
	PrintSettings();
}

/**
 * Prints the table of settings that can be changed
 */
void SettingsScreen::PrintSettings()
{
	// TODO: Make this not hard coded!
	mvwprintw(window, 0, 0, "API Server");
	mvwhline(window, 1, 0, ACS_HLINE, 15);
	mvwprintw(window, 5, 4, "Custom URL:");
	
	mvwprintw(window, 8, 0, "Authentication");
	mvwhline(window, 9, 0, ACS_HLINE, 15);
	mvwprintw(window, 10, 0, "Username:");
	mvwprintw(window, 11, 0, "Password:");
	
	wrefresh(window);
	
	// Draw radio boxes and text fields
	for (unsigned int i = 0; i < radioButtons.size(); i++)
		radioButtons[i]->Refresh();
	for (unsigned int i = 0; i < textFields.size(); i++)
		textFields[i]->Refresh();
}

void SettingsScreen::HandleRadioSelection()
{

}

void SettingsScreen::ChangeCurrentFocus(bool focus)
{
	// Determine the radio button or field that is currently in focus
	// TODO: So much hard coding, bad code!
	if (currentField < 2)
	{
		radioButtons[currentField]->SetFocus(focus);
	}
	else
	{
		textFields[currentField - 2]->SetFocus(focus);
	}
}

void SettingsScreen::SaveChanges()
{
	// Save the selected server
	for (unsigned int i = 0; i < radioButtons.size();  i++)
	{
		if (radioButtons[i]->IsSelected())
		{
			resource->SetSelectedServer( radioButtons[i]->GetLabel() );
			break;
		}
	}
	
	// Save the custom server if any
	resource->SetCustomServerURL( customServerText->GetText() );
	
	// Save the authentication
	string auth = threadService->EncodeAuthorization( userText->GetText(), passwordText->GetText() );
	resource->SetAuthorization( auth );
	
	// Save the file
	resource->SaveFile();
	
	// Set the server information and authentication in the thread service
	
}
