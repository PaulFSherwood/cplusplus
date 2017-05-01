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
#ifndef _COMMENTSSCREEN_H_
#define _COMMENTSSCREEN_H_

#include "Screen.h"
#include "WindowInfo.h"

// Forward declaration
class ScrollableList;
class ScrollableView;
class UIManager;
class ThreadService;

/**
 * CommentsScreen
 *
 * Renders a list of comments onto the screen along with the full post on the top half.
 */
class CommentsScreen : public Screen
{
public:
	CommentsScreen(UIManager * m, ThreadService * service, WindowInfo info);
	
	// DEBUGGING: Parse a sample XML to display
	void DebugParseXML(const char * filename);
	
	// Overriding base functions
	virtual void Initialize();
	virtual void DisplayKeys();
	virtual void HandleInput(int ch);
	virtual void Refresh();

private:
	// Private enum for determining the display mode of the comments
	enum DisplayType { SplitScreen, ThreadView, CommentView };
	
	// Helper function for refreshing the information on the screen
	void DisplayCommentInfo();
	bool RefreshComments();
	
	// Determines whether or not the data is loaded yet so we can refresh the screen
	bool initialized;
	
	// Service that will parse XML tags for this screen
	ThreadService * threadService;
	
	// List view and the scrollable view for displaying the comments and thread
	ScrollableView * commentView;
	ScrollableList * threadView;
	
	// The current mode of display for the comments
	// Can be either split screen, threaded mode, or comment display
	DisplayType currentDisplay;
};

#endif
