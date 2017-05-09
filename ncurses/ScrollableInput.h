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
#ifndef _SCROLLABLELINPUT_H_
#define _SCROLLABLELINPUT_H_

#include "Window.h"
#include "WindowInfo.h"
#include <string>
#include <vector>
#include <ncurses.h>

/**
 * ScrollableInput
 *
 * Supports the user entering text into the box and being able to add more than the
 * current view, allowing them to scroll.
 */
class ScrollableInput : public Window
{
public:
	ScrollableInput(WindowInfo info);
	virtual ~ScrollableInput();
	
	// Clears the input text
	void Clear();
	
	// Set the text directly
	void SetText(std::string text);
	
	// Get the text entered in the input field
	std::string GetText() const;
	
	// Overriding virtual functions
	void Initialize();
	void HandleInput(int ch);
	void Refresh();
	
private:
	// Helper function to set the display text whenever a character is added to the actual text and
	// update the positions of the cursor
	void UpdateText(int ch);
	
	// Checks the cursor bounds and updates the scroll area and index
	void CheckCursorBounds();
	
	// Updates what area of the text pad to display on the screen
	void UpdateScrollArea();
	
	// Updates the cursor index or cursor positing based on the other
	void UpdateCursorIndex();
	void UpdateCursorPosition();
	
	// Does word wrapping and formats the display text
	void RefreshText();
	
	// Draws the box around the reply box and include scroll bars if needed
	void DrawBorder();
	
	// Draws an inverse block that will represent the cursor
	void DrawCursor();
	
	// DEBUGGING function for displaying position and character information
	void DebugPrint();
	
	struct ScreenPos
	{
		ScreenPos(): row(0), col(0)
		{}
		
		unsigned int row;
		unsigned int col;
	};
	
	// Pad that will contain a scrollable area and the text to show
	WINDOW * textPad;
	
	// Tracks the cursor position of the text box so we can determine how to erase
	// text and add text correctly.
	ScreenPos cursorPos;
	
	// Tracks the index of the actual text that the cursor is on
	unsigned int cursorIndex;
	
	// Keep track of the top left corner of the text pad so we know how much to render on the screen
	ScreenPos textPadPos;
	
	// Keeps track of the position in the actual string, which we can use to convert to the actual
	// screen coordinates
	unsigned int textPos;
	
	// The current string input without the screen formatting
	std::string text;
	
	// The display text that will be what appears on the screen
	std::vector<std::string> displayText;
	
	// DEBUG: Stores the last entered character
	unsigned int lastCh;
};

#endif
