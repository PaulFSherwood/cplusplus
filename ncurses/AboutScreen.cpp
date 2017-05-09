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
#include "AboutScreen.h"
#include "UIManager.h"
#include "WindowInfo.h"

/**
 * Constructor
 * @param m UIManager that the screen will have a referenced to
 * @param info Window information with width, height, top, and left
 */
AboutScreen::AboutScreen(UIManager * m, WindowInfo info):
	Screen(m, info)
{
	// Nothing else
}

/**
 * Set up the title and status display
 */
void AboutScreen::Initialize()
{
	// TODO: Put these in a string file
	manager->SetTitle( "About" );
	manager->SetStatus( "[Press ENTER to continue...]" );
	manager->SetKeyString( "[ENTER] Exit from screen" );
	
	Refresh();
}

/**
 * Handles key presses. For the now, only cares about ENTER, which will pop the UI off and
 * load the latest chatty.
 * @param ch Key press
 */
void AboutScreen::HandleInput(int ch)
{
	switch(ch)
	{
		case 10: // ENTER key
			manager->PopUI();
			break;
	};
}

/**
 * Writes the about information on the screen
 */
void AboutScreen::Refresh()
{
	// TODO: Put these in a string file
	mvwprintw(window, 1, 5, "Linux Chatty: The Linux terminal client using ncurses");
	mvwprintw(window, 3, 5, "Under development");
	mvwprintw(window, 5, 5, "David Hsu");
	wrefresh(window);
}
