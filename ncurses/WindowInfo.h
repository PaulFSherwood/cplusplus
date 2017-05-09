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

 #ifndef _WINDOWINFO_H_
 #define _WINDOWINFO_H_
 
typedef unsigned int uint;

/**
 * WindowInfo structure
 * Gives screens information about the size of the screen and where it will be
 * positioned in the terminal
 */
struct WindowInfo
{
	WindowInfo(uint w, uint h, uint top, uint left):
		width(w), height(h), topRow(top), leftCol(left)
	{}
	
	WindowInfo(uint w, uint h):
		width(w), height(h), topRow(0), leftCol(0)
	{}
	
	WindowInfo():
		width(0), height(0), topRow(0), leftCol(0)
	{}
	
	uint width;
	uint height;
	uint topRow;
	uint leftCol;
};

#endif
