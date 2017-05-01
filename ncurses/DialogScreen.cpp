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
#include "DialogScreen.h"
#include "WindowInfo.h"
#include "UIManager.h"
#include <string>
#include <vector>
#include <ctype.h>

using namespace std;

DialogScreen::DialogScreen(UIManager * m, WindowInfo info):
	Screen(m, info)
{

}
	
void DialogScreen::SetText(const std::string& text)
{
	dialogText = text;
	Refresh();
}
	
void DialogScreen::AddChoice(const std::string& text, int ch, bool defaultCh)
{
	choices.push_back( DialogChoice(text, ch) );
	if (defaultCh)
		enterCh = ch;
}

void DialogScreen::Initialize()
{
	enterCh = 0;
	choices.clear();
}

void DialogScreen::HandleInput(int ch)
{
	ch = tolower(ch);
	if (ch == 10) // ENTER
	{
		// Send the default character
		manager->PopDialog(enterCh);
	}
	
	// Loop through the choices and see if a key press matches one of the choices
	for (unsigned int i = 0; i < choices.size(); i++)
	{
		if (ch == choices[i].ch)
		{
			manager->PopDialog(ch);
		}
	}
}

void DialogScreen::Refresh()
{
	// Clear this screen
	wclear(window);
	
	// Draw the dialog text inverted
	wattron(window, A_REVERSE);
	
	int spacesNeeded = windowInfo.width - dialogText.length();
	
	if (spacesNeeded < 0)
		spacesNeeded = 0;
	
	// Pad with spaces
	string padding(spacesNeeded, ' ');
	string msg = dialogText + padding;
	mvwprintw(window, 0, 0, "%s", msg.c_str());
	
	wattroff(window, A_REVERSE);
	
	// Draw the choices
	// TODO: Currently splitting the screen into 4 areas for a maximum of 4 choices.  Require more?
	for (unsigned int i = 0; i < choices.size(); i++)
	{
		mvwprintw(window, 1 + (i % 2), 0 + (int(i / 2) * (windowInfo.width / 2)), "[%c] %s", choices[i].ch, choices[i].text.c_str());
	}
	
	wrefresh(window);
}
