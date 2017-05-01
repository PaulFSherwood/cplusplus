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
#include "ScrollableList.h"
#include <string>
#include <ncurses.h>

using namespace std;

/**
 * Constructor
 * @param info Window information with width, height, top, and left
 */
ScrollableList::ScrollableList(WindowInfo info):
	Window(info), selectedItem(0), topRow(0)
{
	// Nothing for now
}

/**
 * Adds a string to the list.
 * @param text String to add to the list
 */
void ScrollableList::AddItem(const std::string& text)
{
	listItems.push_back(text);
}

/**
 * Removes all text from the list.
 */
void ScrollableList::ClearItems()
{
	listItems.clear();
	topRow = 0;
	selectedItem = 0;
}

/**
 * Get the currently highlighted list item index.
 * @return uint index of the currently selected item in the list
 */
unsigned int ScrollableList::GetSelectedIndex()
{
	return selectedItem;
}

/**
 * Checks if the list has anything.
 * @return True if the list is empty. False otherwise.
 */
bool ScrollableList::IsEmpty()
{
	return listItems.empty();
}

/**
 * Move the selection an arbitrary amount.
 * @param distance How far to move the selection index
 */
void ScrollableList::ScrollSelected(const int distance)
{
	// Make sure distance isn't so large negative that it causes selectedItem to go past 0
	if (((int)selectedItem + distance) < 0)
		selectedItem = 0;
	else
		selectedItem += distance;
	
	// Bound checking
	if (selectedItem > listItems.size() - 1)
		selectedItem = listItems.size() - 1;
	
	// The top index keeps track of the topmost item in the view
	if (selectedItem < topRow)
		topRow = selectedItem;
	if (selectedItem > windowInfo.height - 1 && 
		topRow < selectedItem - (windowInfo.height - 1))
		topRow = selectedItem - (windowInfo.height - 1);
}

/**
 * Updates the view and redraws the list items.
 */
void ScrollableList::Refresh()
{
	// Draws the text on the screen
	string padding(windowInfo.width, ' ');
	for (unsigned int i = 0; i < windowInfo.height; i++)
	{
		// Clears the line in this section
		mvwprintw(window, i, 0, "%s", padding.c_str());
		
		if (i + topRow < listItems.size())
		{	
			if (selectedItem == i + topRow) /* Highlight the present choice */
				wattron(window, A_REVERSE);
				
			// Prints the text line on the screen
			mvwprintw(window, i, 0, "%s", listItems[i+topRow].c_str());
			
			if (selectedItem == i + topRow)
				wattroff(window, A_REVERSE);
		}
	}
	wrefresh(window);
}
