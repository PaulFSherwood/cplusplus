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
#include "RadioButton.h"
#include <string>

using namespace std;

RadioButton::RadioButton(WindowInfo info, const string& label):
	Window(info), text(label), inFocus(false), isSelected(false)
{

}

RadioButton::~RadioButton()
{
	// Nothing for now
}

void RadioButton::SetLabel(const string& text)
{
	this->text = text;
	Refresh();
}

const std::string& RadioButton::GetLabel() const
{
	return text;
}

void RadioButton::SetSelection(bool select)
{
	isSelected = select;
	Refresh();
}

bool RadioButton::IsSelected() const
{
	return isSelected;
}

void RadioButton::SetFocus(bool focus)
{
	inFocus = focus;
	Refresh();
}

void RadioButton::HandleInput(int ch)
{
	// All we care about here is if we're selecting the radio button
	// so whether or not someone pressed ENTER or x
	if (ch == 10 || ch == 'x' || ch == 'X')
	{
		isSelected = !isSelected;
		Refresh();
	}
}

void RadioButton::Refresh()
{
	// Invert the first part if the radio button is selected
	if (inFocus)
		wattron(window, A_REVERSE);
	
	mvwprintw(window, 0, 0, "[ ]");
	if (isSelected)
		mvwprintw(window, 0, 1, "%c", 'X');
	
	if (inFocus)
		wattroff(window, A_REVERSE);
	
	// Print the radio button label
	mvwprintw(window, 0, 4, "%s", text.c_str());
	
	wrefresh(window);
}
