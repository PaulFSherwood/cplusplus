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
#include "ScrollableInput.h"
#include "services/StringUtil.h"
#include <string>
#include <ctype.h>

using namespace std;

/**
 * Constructor
 * @param info Window size information
 */
ScrollableInput::ScrollableInput(WindowInfo info):
	Window(info), cursorIndex(0), textPos(0), text(""), lastCh(0)
{	
	// Initialize the pad that will display the text
	// The pad will have a max width that's the same as the screen size
	// TODO: Make the height variable
	textPad = newpad(info.height * 5, info.width);
	
	Clear();
}

/**
 * Destructor. Makes sure the text pad is cleaned up.
 */
ScrollableInput::~ScrollableInput()
{
	if (textPad)
	{
		delwin(textPad);
		textPad = NULL;
	}
}

/**
 * Clears the text and display screen and resets all cursors and index.
 */
void ScrollableInput::Clear()
{
	// Clear the text pad before clearing out the display and text
	string padding(windowInfo.width - 2, ' ');
	for (unsigned int i = 0; i < displayText.size(); i++)
	{
		mvwprintw(textPad, i, 0, "%s", padding.c_str());
	}
	
	text.clear();
	displayText.clear();
	textPos = 0;
	cursorIndex = 0;
	cursorPos.row = 0;
	cursorPos.col = 0;
	textPadPos.row = 0;
	textPadPos.col = 0;
	
	DrawCursor();
}

/**
 * Set the text in the text view. Erases everything before setting the text and reformating.
 */
void ScrollableInput::SetText(std::string text)
{
	Clear();
	this->text = text;
	RefreshText();
}

/**
 * Returns the raw text in the input.
 */
std::string ScrollableInput::GetText() const
{
	return text;
}

/**
 * Initializes the screen.
 */
void ScrollableInput::Initialize()
{
	DrawCursor();
}

/**
 * Handles key presses and determines what to do with them.
 */
void ScrollableInput::HandleInput(int ch)
{
	lastCh = ch;
	switch(ch)
	{
		case KEY_UP:
			// Move the cursor up if possible
			// move(row, col)
			if (cursorPos.row > 0)
				cursorPos.row--;
			
			CheckCursorBounds();
			break;
		case KEY_DOWN:
			// Move the cursor down if possible
			if (cursorPos.row < displayText.size() - 1)
				cursorPos.row++;
			
			CheckCursorBounds();
			break;
		case KEY_RIGHT:
			// Move the cursor to the right and wrap to the next line if it reaches the end
			if (displayText.size() > 0)
			{
				if (cursorPos.col + 1 > displayText[cursorPos.row].length())
				{
					if (cursorPos.row < displayText.size() - 1)
					{
						cursorPos.row++;
						cursorPos.col = 0;
					}
				}
				else
				{
					cursorPos.col++;
				}
				CheckCursorBounds();
			}
			break;
		case KEY_LEFT:
			// Move the cursor to the left and wrap to the previous line if it reaches the beginning
			if (displayText.size() > 0)
			{
				if (cursorPos.col == 0)
				{
					if (cursorPos.row > 0)
					{
						cursorPos.row--;
						cursorPos.col = displayText[cursorPos.row].length();
					}
				}
				else
				{
					cursorPos.col--;
				}
				CheckCursorBounds();
			}
			break;
		default:
			// For all regular key presses, add it to the text if it is a valid character to add
			UpdateText(ch);
			break;
	};
}

/**
 * Refreshes the screen and updates the view.
 */
void ScrollableInput::Refresh()
{
	DrawBorder();
	DebugPrint();
	wnoutrefresh(window);
	
	// Refresh the pad display
	pnoutrefresh(textPad,
			textPadPos.row, textPadPos.col,
			windowInfo.topRow + 1, windowInfo.leftCol + 1,
			windowInfo.topRow + windowInfo.height - 2,
			windowInfo.leftCol + windowInfo.width - (displayText.size() > windowInfo.height) - 2);

	doupdate();
}

/**
 * Adds or removes a character from the text depending on the key press.
 */
void ScrollableInput::UpdateText(int ch)
{
	// NOTE:  Cygwin marks delete and backspace differently for some reason, registers as a printable character
	// when it shouldn't.  Seems to work fine in Linux though.  Instead of checking to see if it's a control character
	// as Cygwin fails this, we'll check the keys directly before attempting to check if it's printable.
	if (ch == 10) // ENTER KEY
	{
		text.insert(cursorIndex, 1, '\n');
		cursorIndex++;
	}
	else if (ch == KEY_BACKSPACE)
	{
		// Erase the character before this cursor point
		if (cursorIndex > 0)
		{
			text.erase(cursorIndex - 1, 1);
			cursorIndex--;
		}
	}
	else if (ch == KEY_DC) // DELETE CHARACTER
	{
		if (cursorIndex < text.length())
		{
			text.erase(cursorIndex, 1);
		}
	}
	else if (ch == KEY_HOME)
	{
		cursorPos.col = 0;
		UpdateCursorIndex();
	}
	else if (ch == KEY_END)
	{
		cursorPos.col = displayText[cursorPos.row].length();
		UpdateCursorIndex();
	}
	else if (isprint(ch)) // Check if the character is a valid character to print
	{
		// Add the character to the string based on text position
		text.insert(cursorIndex, 1, ch);
		cursorIndex++;
	}
	
	RefreshText();
	UpdateCursorPosition();
}

void ScrollableInput::CheckCursorBounds()
{
	// If the cursor col is past the end of the row text, make it attach to the end
	if (displayText.size() > 0)
		if (displayText[cursorPos.row].empty() || cursorPos.col > displayText[cursorPos.row].length() - 1)
			cursorPos.col = displayText[cursorPos.row].length();
	
	UpdateScrollArea();
	UpdateCursorIndex();
}

/**
 * Updates the display text with the new text in the input.
 */
void ScrollableInput::RefreshText()
{
	// TODO: Do some math to determine if the character can be added to the display text
	// without going past the edge.  Should we just recalculate the whole thing every time on
	// delete?
	// TODO: Make this more efficient to prevent screen flicker
	unsigned int lastDisplaySize = displayText.size();
	displayText.clear();
	StringUtil::WordWrapText(text, displayText, windowInfo.width - 2);
	string padding(windowInfo.width - 2, ' ');
	
	for (unsigned int i = 0; i < displayText.size(); i++)
	{
		// Clear the line before printing the text
		mvwprintw(textPad, i, 0, "%s", padding.c_str());
		mvwprintw(textPad, i, 0, displayText[i].c_str());
	}
	
	// If the new display size is less than the previous, then we also need to clear out the extra
	// line after the last row
	if (lastDisplaySize > displayText.size())
	{
		for (unsigned int i = displayText.size(); i < lastDisplaySize; i++)
			mvwprintw(textPad, i, 0, "%s", padding.c_str());
	}
	
	UpdateScrollArea();
}

/**
 * Updates the top row that is displaying in the scrollable view.
 */
void ScrollableInput::UpdateScrollArea()
{
	// If the cursor is above the current text pad display, also scroll up
	if (cursorPos.row < textPadPos.row)
		textPadPos.row = cursorPos.row;
	
	// If the cursor is below the currently displayed text pad, then scroll down
	// The extra 3 is for the bounding box space and an off-by-1 indexing
	if (cursorPos.row > textPadPos.row + windowInfo.height - 3)
		textPadPos.row = cursorPos.row - windowInfo.height + 3;
}

/**
 * Updates the index in the actual text that the cursor is pointing to on the screen.
 */
void ScrollableInput::UpdateCursorIndex()
{
	// Calculate the string index that the cursor is on from the cursor position
	// If the string is empty, then the index is 0
	cursorIndex = 0;
	if (!text.empty() && !displayText.empty())
	{
		for (unsigned int i = 0; i < cursorPos.row; i++)
		{
			cursorIndex += displayText[i].length();
			if (cursorIndex < text.length() && text[cursorIndex] == '\n')
				cursorIndex++;
		}
		cursorIndex += cursorPos.col;
	}
	
	// TODO: Not refresh the whole text on updating the index in order to remove the cursor
	// at the previous spot
	RefreshText();
	DrawCursor();
}

/**
 * Updates the cursor position on the screen based on the actual index in the text.
 */
void ScrollableInput::UpdateCursorPosition()
{
	cursorPos.row = 0;
	cursorPos.col = 0;
	unsigned int index = cursorIndex;
	unsigned int textIndex = 0;
	if (!text.empty() && !displayText.empty())
	{
		while (cursorPos.row < displayText.size() - 1 && index > displayText[cursorPos.row].length())
		{
			textIndex += displayText[cursorPos.row].length();
			index -= displayText[cursorPos.row].length();
			if (textIndex < text.length() && text[textIndex] == '\n')
			{
				index--;
				textIndex++;
			}
			cursorPos.row++;
		}
		cursorPos.col = index;
	}
	
	// TODO: Not refresh the whole text on updating the index in order to remove the cursor
	// at the previous spot
	RefreshText();
	DrawCursor();
}

/**
 * Draws the scrollable view border and scroll bar.
 */
void ScrollableInput::DrawBorder()
{
	// Draw the lines at the top and left side along with the upper left corner
	mvwaddch(window, 0, 0, ACS_ULCORNER);
	mvwhline(window, 0, 1, ACS_HLINE, windowInfo.width);
	mvwvline(window, 1, 0, ACS_VLINE, windowInfo.height);
	
	// Determine if we need to draw any scroll bars
	// NOTE: For now, only worrying about the verical scroll
	if (displayText.size() > windowInfo.height - 2)
	{
		// Get the ratio by dividing the height of the box with the maximum lines of the text
		// The height has -2 because the border also takes up space on the screen
		float ratio = ((float) windowInfo.height - 2) / ((float) displayText.size());
		
		// Determine how long to draw the scroll bar and where to draw it
		unsigned int lowend = (int) (1 + ((float) textPadPos.row * ratio));
		unsigned int highend = (int) (1 + ((float) (textPadPos.row + windowInfo.height - 2) * ratio));
		
		// Draw the actual scroll bar.  The bar will be an inverted space on the screen
		mvwvline(window, 1, windowInfo.width - 1, ACS_VLINE, lowend);
		//if (highend < windowInfo.height - 2) {
		if (ratio < 1)
		{
			wattron(window, A_REVERSE);
			mvwvline(window, lowend, windowInfo.width - 1, ' ', highend + 1);
			wattroff(window, A_REVERSE);
			mvwvline(window, highend + 1, windowInfo.width - 1, ACS_VLINE, windowInfo.height);
		}
	}
	else
	{
		// If there's nothing to scroll, just draw the line
		mvwvline(window, 1, windowInfo.width - 1, ACS_VLINE, windowInfo.height);
	}
	
	// Horizontal line at the bottom
	mvwhline(window, windowInfo.height - 1, 1, ACS_HLINE, windowInfo.width);
	
	// Draw the corners at the end
	mvwaddch(window, 0, windowInfo.width - 1, ACS_URCORNER);
	mvwaddch(window, windowInfo.height - 1, 0, ACS_LLCORNER);
	mvwaddch(window, windowInfo.height - 1, windowInfo.width - 1, ACS_LRCORNER);
}

/**
 * Draws the block cursor on the screen where the current text index is on the string.
 */
void ScrollableInput::DrawCursor()
{
	// Draw the cursor
	// TODO: Revert the previous place so it shows the non-inverted letter
	wattron(textPad, A_REVERSE);
	if (cursorPos.row < displayText.size() || cursorPos.row == 0)
	{
		if (!text.empty() && cursorPos.col < displayText[cursorPos.row].length())
			mvwprintw(textPad, cursorPos.row, cursorPos.col, "%c", displayText[cursorPos.row][cursorPos.col]);
		else
			mvwprintw(textPad, cursorPos.row, cursorPos.col, "%c", ' ');
	}
	wattroff(textPad, A_REVERSE);
}

/**
 * Debugging purposes for checking positions and key presses
 */
void ScrollableInput::DebugPrint()
{
	string padding(windowInfo.width, ' ');
	for (unsigned int i = 2; i < 9; i++)
		mvwprintw(stdscr, i, 0, "%s", padding.c_str());
	
	mvwprintw(stdscr, 2, 0, "TextPad row: %d", textPadPos.row);
	mvwprintw(stdscr, 3, 0, "Cursor Row: %d", cursorPos.row);
	mvwprintw(stdscr, 4, 0, "Cursor Col: %d", cursorPos.col);
	mvwprintw(stdscr, 5, 0, "Cursor Index: %d", cursorIndex);
	mvwprintw(stdscr, 6, 0, "Window Height: %d", windowInfo.height);
	mvwprintw(stdscr, 7, 0, "Display Text rows: %d", displayText.size());
	mvwprintw(stdscr, 8, 0, "Last character: %d", lastCh);
	//if (!displayText.empty())
	//	mvwprintw(stdscr, 7, 0, "Display Text current cols: %d", displayText[cursorPos.row].length());
}

