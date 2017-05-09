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
#ifndef _THREADSCREEN_H_
#define _THREADSCREEN_H_

#include "Screen.h"

// Forward declaration
class ScrollableList;
class UIManager;
class ThreadService;

/**
 * ThreadScreen
 *
 * Renders a list of posts onto the screen
 */
class ThreadScreen : public Screen
{
public:
	ThreadScreen(UIManager * m, ThreadService * service, WindowInfo info);
	~ThreadScreen();
	
	// DEBUGGING: Parse a sample XML to display
	void DebugParseXML(const char * filename);
	
	// Sets page numbers
	void SetPage(const unsigned int page);
	
	// Overriding base functions
	virtual void Initialize();
	virtual void DisplayKeys();
	virtual void HandleInput(int ch);
	virtual void Refresh();

private:
	// Helper function to load the thread and parse the results into the display
	bool RefreshThread();
	void ParseThread();
	
	// Service that will parse XML tags for this screen
	ThreadService * threadService;
	
	// Scrolling list view to display the threads
	ScrollableList * threadView;
	
	// Determines if there's data loaded or not
	bool initialized;
	
	// Store the current page that is being viewed in this story
	unsigned int currentPage;
	
	// Stores the last page of this story for bound checking the current page
	unsigned int lastPage;
	
	// Keeps track of the top most index to make the scrolling correct
	unsigned int topIndex;
	
	// Index of the currently highlighted thread
	unsigned int selectedThread;
};

#endif
