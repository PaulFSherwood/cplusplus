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
#include "CommentsScreen.h"
#include "UIManager.h"
#include "ScrollableList.h"
#include "ScrollableView.h"
#include "services/ThreadService.h"
#include <string>
#include <vector>

using namespace std;

/**
 * Constructor
 * @param m UIManager that the screen will have a referenced to
 * @param service ThreadService class with access to the shack API
 * @param info Window information with width, height, top, and left
 */
CommentsScreen::CommentsScreen(UIManager * m, ThreadService * service, WindowInfo info):
	Screen(m, info), initialized(false), threadService(service), currentDisplay(SplitScreen)
{
	// By default, the screen is in split view, so create the thread and comment view
	// with those dimensions.
	commentView = new ScrollableView( WindowInfo(info.width, info.height / 2 - 1, info.topRow + 1, 0) );
	threadView = new ScrollableList( WindowInfo(info.width, info.height / 2, 
		(windowInfo.height / 2 + info.topRow + 1), 0) );
}

// DEBUGGING: Parse a sample XML to display
void CommentsScreen::DebugParseXML(const char * filename)
{
	threadService->DebugParseXML(filename, false);
}

/**
 * Initializes any states in the screen
 */
void CommentsScreen::Initialize()
{
	initialized = false;
	
	// Set the status for now to show that it is loading
	manager->SetStatus("[Loading...]");
	manager->Refresh();
	
	// If the thread retrieval failed, then this screen isn't initialized
	if (RefreshComments())
	{
		initialized = true;
		manager->SetStatus("");
		DisplayKeys();
	}
	else
	{
		manager->SetStatus("[Error in loading the comment thread!]");
		manager->PopUI();
	}
	manager->Refresh();
}

/**
 * Displays the hot keys at the bottom.
 */
void CommentsScreen::DisplayKeys()
{
	manager->SetKeyString( "[A/Z] Scroll Comment  [<-] Back  [->] View  [F5] Refresh [M] Modes" );
}

/**
 * Determines what to do with the passed in input key
 * @param ch Input character that was pressed
 */
void CommentsScreen::HandleInput(int ch)
{
	// TODO: Handle arrow keys for naviating
	// TODO: Handle keypress for switching comment display mode
	vector<CommentData *> comments = threadService->GetCurrentComments();
	// Handle arrow keys for navigating
	switch(ch)
	{
		case KEY_UP:
			// Scrool up on the thread
			threadView->ScrollSelected(-1);
			commentView->SetText( comments[threadView->GetSelectedIndex()]->body );
			break;
		case KEY_DOWN:
			// Scroll down on the thread
			threadView->ScrollSelected(1);
			commentView->SetText( comments[threadView->GetSelectedIndex()]->body );
			break;
		case 'A': case 'a':
			// Scroll up the comment
			commentView->Scroll(-1);
			break;
		case 'Z': case 'z':
			// Scroll down the comment
			commentView->Scroll(1);
			break;
		case KEY_LEFT:
			// Back button, returns to the previous screen
			if (currentDisplay == ThreadView || currentDisplay == SplitScreen)
			{
				manager->PopUI();
				manager->SetStatus("");
			}
			else if (currentDisplay == CommentView)
			{
				currentDisplay = ThreadView;
				manager->SetStatus("[Thread View]");
			}
			break;
		case KEY_RIGHT:
			// Depending on the comment display mode, show the body of the comment
			// or it does nothing
			if (currentDisplay == ThreadView)
			{
				currentDisplay = CommentView;
				manager->SetStatus("[Comment View]");
			}
			break;
		case 'M': case 'm':
			// Switch display modes for the comment screen:
			// Split screen mode and threaded/comment mode
			if (currentDisplay == ThreadView || currentDisplay == CommentView)
			{
				currentDisplay = SplitScreen;
				manager->SetStatus("[Split View]");
				
				// Change the size and positions of the views
				commentView->SetWindow( WindowInfo(windowInfo.width, windowInfo.height / 2 - 1, windowInfo.topRow + 1, 0) );
				threadView->SetWindow( WindowInfo(windowInfo.width, windowInfo.height / 2, 
					(windowInfo.height / 2 + windowInfo.topRow + 1), 0) );
				threadView->ScrollSelected(0);
			}
			else
			{
				currentDisplay = ThreadView;
				manager->SetStatus("[Thread View]");
				
				// Change the size and positions of the views
				commentView->SetWindow( WindowInfo(windowInfo.width, windowInfo.height, windowInfo.topRow + 1, 0) );
				threadView->SetWindow( WindowInfo(windowInfo.width, windowInfo.height, windowInfo.topRow, 0) );
				threadView->ScrollSelected(0);
			}
			Refresh();
			break;
		case 'R': case 'r':
			if (currentDisplay == CommentView || currentDisplay == SplitScreen)
			{
				// Reply to the current post
				manager->PushUI( "post" );
				manager->SetThreadId( "post", comments[threadView->GetSelectedIndex()]->id );
				manager->SetReplyComment( comments[threadView->GetSelectedIndex()]->body,
					comments[threadView->GetSelectedIndex()]->author,
					comments[threadView->GetSelectedIndex()]->date );
			}
			break;
		case KEY_F(5):
			// Refreshes the current comment thread
			RefreshComments();
			break;
	}
}

/**
 * Refreshes the screen and redraws the comment information
 */
void CommentsScreen::Refresh()
{
	// If the data isn't loaded yet, don't refresh
	if (!initialized)
		return;
	
	// Depending on the mode of the screen, the display will be different
	// If in split screen mode, then display both the body of the comments and the threaded
	// view on the two halves of the screen.  In threaded mode, only display the comment thread.
	// In comment view, only display the author and body of the text.
	// TODO: This should actually be split into 3 different classes, not merged into one like this
	if (currentDisplay == SplitScreen)
	{
		// Display the comments in the upper half
		DisplayCommentInfo();
		commentView->Refresh();
		
		// Draw a line divider between the body text and the threads
		mvwhline(window, (windowInfo.height / 2), 0, ACS_HLINE, windowInfo.width);
		
		// Display the thread view in the lower half
		threadView->Refresh();
	}
	else if (currentDisplay == ThreadView)
	{
		threadView->Refresh();
	}
	else if (currentDisplay == CommentView)
	{
		DisplayCommentInfo();
		commentView->Refresh();
	}
	// mvwprintw(window, 0, 0, "%d", topIndex);
	// mvwprintw(window, 1, 0, "%d", threadView->GetSelectedIndex());
	// mvwprintw(window, 2, 0, "%d", maxRows);
	wrefresh(window);
}

/**
 * Displays the author and date at the top of the comment
 */
void CommentsScreen::DisplayCommentInfo()
{
	vector<CommentData *> comments = threadService->GetCurrentComments();
	
	string date = comments[threadView->GetSelectedIndex()]->date;
	unsigned int datePos = 0;
	if (windowInfo.width - date.length() > 0)
		datePos = windowInfo.width - date.length();
	
	// Clears the author/date line, then displays it
	string padding(windowInfo.width, ' ');
	mvwprintw(window, 0, 0, "%s", padding.c_str());
	mvwprintw(window, 0, 0, "By: %s", comments[threadView->GetSelectedIndex()]->author.c_str());
	mvwprintw(window, 0, datePos, "%s", date.c_str());
}

/**
 * Updates the thread information and updates the views
 * @return True if the thread was successfully updated. False otherwise.
 */
bool CommentsScreen::RefreshComments()
{
	if( threadService->GetThread(threadId) )
	{
		// Updates the thread view with the new threads
		threadView->ClearItems();
		
		// Loop through the root comments and display them on the screen
		// The format will be display as much as the preview text as possible
		// The ending part will contain the author
		// Author name will also be truncated if it's longer than 10 characters
		// Preview post(columns - 11ch - depth * 2), Author(10 ch max)
		string indent;
		string threadItem;
		vector<CommentData *> comments = threadService->GetCurrentComments();
		for (unsigned int i = 0; i < comments.size(); i++)
		{
			indent.clear();
			threadItem.clear();
			if (comments[i]->depth > 0)
			{
				indent.resize(comments[i]->depth * 2, ' ');
			}
			string text = indent + comments[i]->preview.substr(0, windowInfo.width - 11 - (comments[i]->depth * 2));
			string author = comments[i]->author.substr(0,10);
			
			// Determine the amount of string padding needed to line the authors up
			string textPadding((windowInfo.width - 10) - text.size(), ' ');
			
			threadItem = text + textPadding + author;
			
			// Add the string to the list for display
			threadView->AddItem(threadItem);
		}
		
		// Also loads the currently selected thread into the comment view to display
		commentView->SetText( comments[threadView->GetSelectedIndex()]->body );
		
		return true;
	}
	return false;
}
