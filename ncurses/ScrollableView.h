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
#ifndef _SCROLLABLEVIEW_H_
#define _SCROLLABLEVIEW_H_

#include "Window.h"
#include "WindowInfo.h"
#include <string>
#include <vector>
#include <ncurses.h>

/**
 * ScrollableView
 *
 * Base class that supports the ability to display text on the screen in a scrollable window.
 * Currently, this view can only scroll vertically, no horizontal support yet.
 */
class ScrollableView : public Window
{
public:
	ScrollableView(WindowInfo info);
	
	// Set the text to display
	void SetText(const std::string& text);
	void ClearText();
	
	// Scrolls the text on the display
	void Scroll(const int distance);
	
	// Base functions for updating the screen
	void Refresh();

protected:
	// Text array for word wrapped text
	std::vector<std::string> textArray;
	
	// Keeps track of the top most index to make the scrolling correct
	unsigned int topRow;
};

#endif
