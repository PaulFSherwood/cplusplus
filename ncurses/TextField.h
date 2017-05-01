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
#ifndef _TEXTFIELD_H_
#define _TEXTFIELD_H_

#include "Window.h"
#include "WindowInfo.h"
#include <string>

/**
 * Simple text field where a person can enter text.  Has the option to be "password" so any letter that shows up will be
 * the specified custom character.
 */
class TextField : public Window
{
public:
	TextField(WindowInfo info);
	virtual ~TextField();
	
	// Set the text to display in the field
	void SetText(const std::string& text);
	const std::string& GetText() const;
	
	// Set this text field to be a password type with the specified character
	void SetPasswordField(bool password, char ch='*');
	
	// Determines if this field has focus or not
	void SetFocus(bool focus);
	
	// Overriding virtual functions
	void HandleInput(int ch);
	void Refresh();
	
private:
	// Helper function for changing the text string
	void UpdateText(int ch);
	
	// Text that this text field holds
	std::string text;
	
	// Determines if this text field will be replaced with password characters
	bool isPassword;
	char passwordCh;
	
	// True if the text field is currently selected and editing
	bool inFocus;
	
	// Cursor index in the text where a letter will be inserted or deleted
	unsigned int cursorIndex;
};

#endif
