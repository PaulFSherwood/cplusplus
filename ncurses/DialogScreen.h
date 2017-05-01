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
#ifndef _DIALOGSCREEN_H_
#define _DIALOGSCREEN_H_

#include "Screen.h"
#include "WindowInfo.h"
#include <string>
#include <vector>

// Forward declaration
class UIManager;

/**
 * Structure for holding the choices that can be made in the dialog screen.
 */
struct DialogChoice
{
	DialogChoice():
		text(""), ch(0) {}
	
	DialogChoice(const std::string& t, int c):
		text(t), ch(c) {}
	
	std::string text;
	int ch;
};

/**
 * Dialog screen that will be displayed in the bottom 3 rows for making choices.
 */
class DialogScreen : public Screen
{
public:
	DialogScreen(UIManager * m, WindowInfo info);
	
	// Set what the dialog screen will say
	void SetText(const std::string& text);
	
	// Adds a choice to the dialog screen that it will respond to
	void AddChoice(const std::string& text, int ch, bool defaultCh=false);
	
	// Overriding virtual functions
	void Initialize();
	void HandleInput(int ch);
	void Refresh();

private:
	// Text to display for the question
	std::string dialogText;
	
	// The choices and the corresponding key press it registers
	std::vector<DialogChoice> choices;
	
	// Default character that will send if the person just presses enter
	int enterCh;
};

#endif
