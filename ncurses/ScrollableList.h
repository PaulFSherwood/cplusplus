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
#ifndef _SCROLLABLELIST_H_
#define _SCROLLABLELIST_H_

#include "Window.h"
#include "WindowInfo.h"
#include <string>
#include <vector>
#include <ncurses.h>

/**
 * ScrollableList
 *
 * Stores a list of string items to display and keeps track of the selected item in the list.
 * Currently, this view can only scroll vertically, no horizontal support yet.
 */
class ScrollableList : public Window
{
public:
	ScrollableList(WindowInfo info);
	
	// Adds items to the list to display
	void AddItem(const std::string& text);
	void ClearItems();
	
	// Returns the currently selected item
	unsigned int GetSelectedIndex();
	
	// Returns true if there's currently no items in this list
	bool IsEmpty();
	
	// Changes the selected item in the list
	void ScrollSelected(const int distance);
	
	// Base function for updating the screen
	virtual void Refresh();

private:
	// The currently selected item from the list
	unsigned int selectedItem;
	
	// Array for each item to list
	std::vector<std::string> listItems;
	
	// Keeps track of the top most index to make the scrolling correct
	unsigned int topRow;
};

#endif
