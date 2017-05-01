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
#include "TextField.h"
#include <string>

using namespace std;

/**
 * Constructor
 * @param info Window size information
 */
TextField::TextField(WindowInfo info):
	Window(info), isPassword(false), passwordCh('*'), inFocus(false), cursorIndex(0)
{

}

TextField::~TextField()
{
	// Nothing for now
}

void TextField::SetText(const string& text)
{
	this->text = text;
	Refresh();
}

const string& TextField::GetText() const
{
	return text;
}

void TextField::SetPasswordField(bool password, char ch)
{
	isPassword = password;
	passwordCh = ch;
}

void TextField::SetFocus(bool focus)
{
	inFocus = focus;
	
	// If gaining focus, set the cursor index to the beginning
	if (focus)
		cursorIndex = 0;
	
	Refresh();
}

void TextField::HandleInput(int ch)
{
	switch(ch)
	{
		case KEY_RIGHT:
			// Move the cursor to the right
			if (cursorIndex < text.length())
			{
				cursorIndex++;
				Refresh();
			}
			break;
		case KEY_LEFT:
			// Move the cursor to the left
			if (cursorIndex > 0)
			{
				cursorIndex--;
				Refresh();
			}
			break;
		default:
			// For all regular key presses, add it to the text if it is a valid character to add
			UpdateText(ch);
			break;
	};
}

void TextField::Refresh()
{
	// Invert the field if not selected
	if (!inFocus)
		wattron(window, A_REVERSE);
	
	// Clear the text field
	string padding(windowInfo.width, ' ');
	mvwprintw(window, 0, 0, "%s", padding.c_str());
	
	// Display the text
	if (isPassword)
	{
		string passwordText(text.length(), passwordCh);
		mvwprintw(window, 0, 0, "%s", passwordText.c_str());
	}
	else
	{
		mvwprintw(window, 0, 0, "%s", text.c_str());
	}
	
	if (!inFocus)
		wattroff(window, A_REVERSE);
	
	// Draw the cursor if this text field is in focus
	if (inFocus)
	{
		wattron(window, A_REVERSE);
		if (cursorIndex < text.length())
			if (isPassword)
				mvwprintw(window, 0, cursorIndex, "%c", passwordCh);
			else
				mvwprintw(window, 0, cursorIndex, "%c", text[cursorIndex]);
		else
			mvwprintw(window, 0, cursorIndex, "%c", ' ');
		wattroff(window, A_REVERSE);
	}
	wrefresh(window);
}

void TextField::UpdateText(int ch)
{
	// NOTE:  Cygwin marks delete and backspace differently for some reason, registers as a printable character
	// when it shouldn't.  Seems to work fine in Linux though.  Instead of checking to see if it's a control character
	// as Cygwin fails this, we'll check the keys directly before attempting to check if it's printable.
	
	// These keys are unaffected by whether or not the cursor is at the end
	if (ch == KEY_BACKSPACE)
	{
		// Erase the character before this cursor point
		if (cursorIndex > 0)
		{
			text.erase(cursorIndex - 1, 1);
			cursorIndex--;
		}
	}	
	else if (ch == KEY_HOME)
	{
		cursorIndex = 0;
	}
	else if (ch == KEY_END)
	{
		cursorIndex = text.length();
	}
	else if (ch == KEY_DC) // DELETE CHARACTER
	{
		if (cursorIndex < text.length())
		{
			text.erase(cursorIndex, 1);
		}
	}
	
	// If the cursor is at the end, then we can't add any more characters
	if (cursorIndex < windowInfo.width - 1)
	{
		if (isprint(ch)) // Check if the character is a valid character to print
		{
			// Check to make sure we're not exceeding the maximum width of the text field
			if (text.length() < windowInfo.width)
			{
				// Add the character to the string based on text position
				text.insert(cursorIndex, 1, ch);
				cursorIndex++;
			}
		}
	}
	Refresh();
}
