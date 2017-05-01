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
#ifndef _RADIOBUTTON_H_
#define _RADIOBUTTON_H_

#include "Window.h"
#include "WindowInfo.h"
#include <string>

/**
 * Handles radio buttons on the screen.
 */
class RadioButton : public Window
{
public:
	RadioButton(WindowInfo info, const std::string& label);
	virtual ~RadioButton();
	
	// Set the text label to display in the field
	void SetLabel(const std::string& text);
	const std::string& GetLabel() const;
	
	// Sets whether or not the radio button is selected
	void SetSelection(bool select);
	bool IsSelected() const;
	
	// Determines if this field has focus or not
	void SetFocus(bool focus);
	
	// Overriding virtual functions
	void HandleInput(int ch);
	void Refresh();
	
private:
	// Text label of the radio button
	std::string text;
	
	// True if the text field is currently selected and editing
	bool inFocus;
	
	// True if this radio button is selected
	bool isSelected;
};

#endif
