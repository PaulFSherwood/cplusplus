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
#include "ScrollableView.h"
#include "services/StringUtil.h"
#include <string>
#include <ncurses.h>

using namespace std;

/**
 * Constructor
 * @param info Window information with width, height, top, and left
 */
ScrollableView::ScrollableView(WindowInfo info):
	Window(info), topRow(0)
{
	// Nothing else
}

/**
 * Set the text to display in the scrollable view. Note that this also does word wrapping.
 * @param text String to display in the view
 */
void ScrollableView::SetText(const std::string& text)
{	
	ClearText();
	StringUtil::WordWrapText(text, textArray, windowInfo.width);
}

/**
 * Removes all text from the view.
 */
void ScrollableView::ClearText()
{
	textArray.clear();
	topRow = 0;
}

/**
 * Scrolls the view.
 * @param distance An integer distance to scroll, can be negative
 */
void ScrollableView::Scroll(const int distance)
{
	// If the text array isn't even fill the screen, then there's no scrolling
	if (textArray.size() < windowInfo.height)
		return;
	
	if ((int)topRow + distance  < 0)
		topRow = 0;
	else
		topRow += distance;
	
	// Bound checking
	if (topRow > textArray.size() - windowInfo.height)
		topRow = textArray.size() - windowInfo.height;
}

/**
 * Refreshes the display and redraws the text on the screen.
 */
void ScrollableView::Refresh()
{
	// Draws the text on the screen
	string padding(windowInfo.width, ' ');
	for (unsigned int i = 0; i < windowInfo.height; i++)
	{
		// Clears the line in this section
		mvwprintw(window, i, 0, "%s", padding.c_str());
		
		if (i + topRow < textArray.size())
		{	
			// Prints the text line on the screen
			mvwprintw(window, i, 0, "%s", textArray[i+topRow].c_str());
		}
	}
	// mvwprintw(window, 5, 0, "%d", textArray.size());
	// mvwprintw(window, 6, 0, "%d", windowInfo.height);
	// mvwprintw(window, 7, 0, "%d", topRow);
	wrefresh(window);
}
