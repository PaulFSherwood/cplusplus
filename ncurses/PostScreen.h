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
#ifndef _POSTSCREEN_H_
#define _POSTSCREEN_H_

#include "Screen.h"
#include <string>
#include <ncurses.h>

// Forward declarations
class ScrollableInput;
class ScrollableView;
class UIManager;
class ThreadService;

/**
 * Handles getting input from the keyboard and posting the new reply/topic to the thread.
 */
class PostScreen : public Screen
{
public:
	PostScreen(UIManager * m, ThreadService * service, WindowInfo info);
	~PostScreen();

	// Overriding virutal function
	void SetThreadId(const unsigned int threadId);
	
	// Set the comment message to remind us what we're replying to
	void SetPreview(const std::string& preview, const std::string& author, const std::string& date);

	// Overriding base functions
	void Initialize();
	void HandleInput(int ch);
	void Refresh();

private:
	// Helper function for displaying the comment box
	void DisplayCommentInfo();
	void DisplayCreateInfo();
	
	// Text pad for enter information
	ScrollableInput * inputBox;
	
	// Comment that we're responding to at the top
	ScrollableView * commentView;
	
	// Service that will send the data to the chatty
	ThreadService * threadService;
	
	// Post information at the top (author and date)
	std::string author;
	std::string date;
	
	// True if currently replying to a comment.  If not, then the top half is ignored
	bool isReply;
};

#endif
