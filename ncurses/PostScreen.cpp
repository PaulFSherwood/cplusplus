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
#include "PostScreen.h"
#include "UIManager.h"
#include "WindowInfo.h"
#include "services/ThreadService.h"
#include "ScrollableView.h"
#include "ScrollableInput.h"
#include <string>
#include <stdlib.h>
#include <ncurses.h>

using namespace std;

/**
 * Constructor
 * @param m UIManager that the screen will have a referenced to
 * @param service ThreadService class with access to the shack API
 * @param info Window information with width, height, top, and left
 */
PostScreen::PostScreen(UIManager * m, ThreadService * service, WindowInfo info):
	Screen(m, info), threadService(service), isReply(false)
{
	// Initialize the input box and comment view
	commentView = new ScrollableView( WindowInfo(info.width, info.height / 2 - 1, info.topRow + 1, 0) );
	inputBox = new ScrollableInput( WindowInfo(info.width, info.height / 2, 
		(windowInfo.height / 2 + info.topRow + 1), 0) );
}

/**
 * Destructor for safely removing the comment view and input box.
 */
PostScreen::~PostScreen()
{
	if (commentView != NULL)
		delete commentView;
	
	if (inputBox != NULL)
		delete inputBox;
}

/**
 * Overrides the default thread id function in order to check if creating a new thread or not.
 */
void PostScreen::SetThreadId(const unsigned int threadId)
{
	this->threadId = threadId;
	
	isReply = (this->threadId != 0);
}

/**
 * Set the comment preview at the top with the author and date so we know what thread we're
 * responding to.
 * @param preview String comment text that we're replying to
 * @param author Author that wrote the post
 * @param date Time the post was created
 */
void PostScreen::SetPreview(const string& preview, const string& author, const string& date)
{
	this->author = author;
	this->date = date;
	commentView->SetText( preview );
	Refresh();
}

/**
 * Clears all text and data.
 */
void PostScreen::Initialize()
{
	commentView->ClearText();
	inputBox->Clear();
	author.clear();
	date.clear();
	
	// DEBUGGING POSTING
	//threadService.CheckAuthorization("dhavatar", "blah");
}

/**
 * Determines what to do with the passed in input key
 * @param ch Input character that was pressed
 */
void PostScreen::HandleInput(int ch)
{
	switch(ch)
	{
		case 5: // CTRL + E
			// Exits from the post screen
			// TODO: Confirmation?
			manager->PopUI();
			break;
		case 16: // CTRL + P
			// Sends the text from the input box to the thread
			// TODO: Get authorization from a file/data structure
			// TODO: Confirmation dialog
			// TODO: Determine if the post went through or not
			threadService->PostData(storyId, threadId, inputBox->GetText());
			manager->PopUI();
			break;
		default:
			// Send inputs to the panel
			inputBox->HandleInput(ch);
			break;
	}
}

/**
 * Refreshes the screen and redraws the comment information
 */
void PostScreen::Refresh()
{
	// Display the comment text in the upper half if replying to a comment
	if (isReply)
	{
		DisplayCommentInfo();
		commentView->Refresh();
	}
	
	// Draw a line divider between the body text and the threads
	mvwhline(window, (windowInfo.height / 2), 0, ACS_HLINE, windowInfo.width);
	
	// If this is a new post, then we overwrite part of the dividing line
	// saying that we're creating a new post
	if (!isReply)
	{
		DisplayCreateInfo();
	}
	
	wrefresh(window);
	
	// Display the reply box in the bottom half
	inputBox->Refresh();
}

/**
 * Displays the comment preview at the top half of the screen.
 */
void PostScreen::DisplayCommentInfo()
{	
	unsigned int datePos = 0;
	if (windowInfo.width - date.length() > 0)
		datePos = windowInfo.width - date.length();
	
	// Clears the author/date line, then displays it
	string padding(windowInfo.width, ' ');
	mvwprintw(window, 0, 0, "%s", padding.c_str());
	mvwprintw(window, 0, 0, "By: %s", author.c_str());
	mvwprintw(window, 0, datePos, "%s", date.c_str());
}

/**
 * Displays a message in the middle line that we're creating a new post.
 */
void PostScreen::DisplayCreateInfo()
{
	string text = "[CREATE POST]";
	unsigned int createPos = (windowInfo.width - text.length()) / 2;
	
	mvwprintw(window, (windowInfo.height / 2), createPos, "%s", text.c_str());
}
