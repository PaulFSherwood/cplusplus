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
#include "MainMenuScreen.h"
#include "WindowInfo.h"
#include "UIManager.h"
#include "services/ResourceTable.h"
#include <vector>

using namespace std;

/**
 * Constructor that takes a UIManager for reference
 * @param m Keeps track of the UIManager to add or end UIs
 * @param res ResourceTable for menu items
 * @param info Screen information with width, height, top, and left
 */
MainMenuScreen::MainMenuScreen(UIManager * m, ResourceTable * res, WindowInfo info):
	Screen(m, info), resource(res)
{
	highlight = 0;
}

/**
 * Handles what to do when the screen gains focus again.
 */
void MainMenuScreen::HandleFocus()
{
	// Resets the keys to show nothing
	DisplayKeys();
}

/**
 * Handle key presses from the user
 * @param ch User key press
 */
void MainMenuScreen::HandleInput(int ch)
{
	switch(ch)
	{	
		case KEY_UP:
			if(highlight == 0)
				highlight = resource->NumMenuItems() - 1;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if(highlight == resource->NumMenuItems() - 1)
				highlight = 0;
			else 
				++highlight;
			break;
		case 10:
			// Depending on the highlight choice, add the correct UI to the screen
			ParseChoice();
			break;
		default:
			mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", ch, ch);
			refresh();
			break;
	}
}

/**
 * Refreshes the screen
 */
void MainMenuScreen::Refresh()
{
	wclear(window);
	
	// mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	// refresh();
	PrintMenu();
}

/**
 * Private helper function for drawing the menu
 */
void MainMenuScreen::PrintMenu()
{
	int x, y;
	unsigned int i;
	
	x = 2;
	y = 2;
	vector<MenuItem> choices = resource->GetMenuList();
	
	for(i = 0; i < choices.size(); i++, y += 2)
	{	
		// Format the choices into a readable string
		// TODO: Make everything aligned
		string msg = choices[i].keyText + " " + choices[i].title + " - " + choices[i].desc;
		
		if(highlight == i) /* High light the present choice */
			wattron(window, A_REVERSE);
		
		mvwprintw(window, y, x, "%s", msg.c_str());
		
		if(highlight == i)
			wattroff(window, A_REVERSE);
	}
	wrefresh(window);
}

/**
 * Private helper for determining what to do with the current highlight
 */
void MainMenuScreen::ParseChoice()
{
	// Get the phrase associated with the highlight index
	MenuItem item = resource->GetMenuListItem(highlight);
	
	// If the menu selected was quit, then we show a prompt at the bottom asking if
	// we really want to quit
	// TODO!
	if (item.data == "quit")
	{
		manager->PopUI();
	}
	else
	{
		// Otherwise, load the UI with the item data
		wclear(window);
		wrefresh(window);
		manager->PushUI( item.data );
	}
}
