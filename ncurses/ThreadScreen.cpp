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
#include "ThreadScreen.h"
#include "UIManager.h"
#include "ScrollableList.h"
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
ThreadScreen::ThreadScreen(UIManager * m, ThreadService * service, WindowInfo info):
	Screen(m, info), threadService(service), initialized(false), currentPage(0), lastPage(0), topIndex(0), selectedThread(0)
{
	// Create the view for this screen just below the title
	threadView = new ScrollableList( WindowInfo(info.width, info.height, 1, 0) );
}

/**
 * Destructor.  Mainly for cleaning up the thread view.
 */
ThreadScreen::~ThreadScreen()
{
	if (threadView)
	{
		delete threadView;
		threadView = NULL;
	}
}

/**
 * Sets the current page of the story to load.
 * @param page Current page to load from the story
 */
void ThreadScreen::SetPage(const unsigned int page)
{
	currentPage = page;
}

/**
 * Initializes the thread information and sets the proper title based on the story
 */
void ThreadScreen::Initialize()
{
	initialized = false;
	
	DisplayKeys();
	
	// Set the status for now to show that it is loading
	manager->Clear();
	manager->Refresh();
	
	currentPage = 1;
	
	// Grab the latest story threads from the site
	// If the retrieval fails, then we don't initialize
	if (RefreshThread())
	{
		initialized = true;
	}
	
	manager->Refresh();
}

// DEBUGGING: Parse a sample XML to display
void ThreadScreen::DebugParseXML(const char * filename)
{
	threadService->DebugParseXML(filename, true);
}

/**
 * Displays the hot keys at the bottom.
 */
void ThreadScreen::DisplayKeys()
{
	manager->SetKeyString( "[UP/DOWN] Navigate  [->] View  [F5] Refresh  [<] Prev Page  [>] Next Page" );
}

/**
 * Determines what to do with the passed in input key
 * @param ch Input character that was pressed
 */
void ThreadScreen::HandleInput(int ch)
{
	WindowInfo res = GetWindowInfo();
	vector<CommentData *> comments = threadService->GetRootComments();
	// Handle arrow keys for navigating
	switch(ch)
	{
		case KEY_DOWN:
			threadView->ScrollSelected(1);
			break;
		case KEY_UP:
			threadView->ScrollSelected(-1);
			break;
		case KEY_RIGHT:
			// If the thread isn't initialized, then this won't work as there won't be
			// a thread to go to.
			if (initialized)
			{
				manager->SetThreadId( "comments", comments[threadView->GetSelectedIndex()]->id );
				manager->PushUI( "comments" );
			}
			break;
		case KEY_F(5):
			// Refresh the current story page
			RefreshThread();
			break;
		case 'n': case 'N':
			// New Comment
			manager->SetThreadId( "post", 0 );
			manager->PushUI( "post" );
			break;
		case '.': case '>':
			// Goes to the next page if available
			if (currentPage < lastPage)
			{
				currentPage++;
				RefreshThread();
			}
			break;
		case ',': case '<':
			// Goes to the previous page if not on the first already
			if (currentPage > 1)
			{
				currentPage--;
				RefreshThread();
			}
			break;
	}
}

/**
 * Refreshes the screen and redraws the thread information
 */
void ThreadScreen::Refresh()
{
	if (!initialized)
		return;
	
	// Only need to update the list view
	threadView->Refresh();
}

/**
 * Loads the thread
 */
bool ThreadScreen::RefreshThread()
{
	manager->SetStatus("[Loading...]");
	manager->Refresh();
	
	if (threadService->GetStory(storyId, currentPage))
	{
		StoryPost sp = threadService->GetStoryPost();
		manager->SetTitle(sp.storyName);
		
		// TODO: Ahhhhh, conversion mess here. Need a cleaner method
		// Display the current page and the total pages
		char chCurrentPage[16], chMaxPage[16];
		sprintf(chCurrentPage, "%d", currentPage);
		sprintf(chMaxPage, "%d", sp.lastPage);
		string strCurrentPage(chCurrentPage);
		string strMaxPage(chMaxPage);
		string status("[Page " + strCurrentPage + " of " + strMaxPage + "]");
		manager->SetStatus(status);
		
		// Store the ID and last page
		storyId = sp.storyId;
		lastPage = sp.lastPage;
		
		// Send the story id to the post screen
		manager->SetStoryId( "post", storyId );
		
		// Reset the currently selected thread and top index
		selectedThread = 0;
		topIndex = 0;
		
		// Parse the thread and update the list view
		ParseThread();
		
		return true;
	}
	
	manager->SetStatus("[Error retrieving story threads!]");
	manager->Refresh();
	
	return false;
}

/**
 * Parses the thread received from the thread service and places each thread into the list view
 */
void ThreadScreen::ParseThread()
{
	threadView->ClearItems();
	
	// Loop through the root comments and convert it to a single string
	// The format will display as much as the preview text as possible
	// The ending part will contain the author, reply count, and any additional replies
	// Author name will also be truncated if it's longer than 10 characters
	// Preview post(columns - 16ch), Author(10 ch max), Replies(4 ch max)
	vector<CommentData *> comments = threadService->GetRootComments();
	for (unsigned int i = 0; i < comments.size(); i++)
	{
		string threadItem;
		string text = comments[i]->preview.substr(0, windowInfo.width - 16);
		string author = comments[i]->author.substr(0,10);
		
		// Determine the amount of string padding needed to line the authors up
		string textPadding((windowInfo.width - 15) - text.size(), ' ');
		
		// TODO: Conversion mess from number to string
		char chReplies[16];
		sprintf(chReplies, "%d", comments[i]->replyCount);
		string replies(chReplies);
		
		// Padding for the author
		string authorPadding(11 - author.size(), ' ');
		
		threadItem = text + textPadding + author + authorPadding + replies;
		
		// Add the string to the list for display
		threadView->AddItem(threadItem);
	}
}
