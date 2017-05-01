/*
**  ClanLib SDK
**  Copyright (c) 1997-2011 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
**    (if your name is missing here, please add it)
*/

/// \addtogroup clanMikMod_System clanMikMod System
/// \{

#pragma once

/// \brief ClanMikMod initialization.
///
/// \xmlonly !group=MikMod/System! !header=mikmod.h! \endxmlonly
class CL_SetupMikMod
{
/// \name Construction
/// \{

public:
	/// \brief Initializes clanMikMod.
	/** <p>Constructing a CL_SetupMikMod object is equalent to calling CL_SetupMikMod::init().</p>
	    <p>When the CL_SetupMikMod instance is destroyed, CL_SetupMikMod::deinit() is called.</p>*/
	CL_SetupMikMod(bool register_resources_only = false);

	~CL_SetupMikMod();

/// \}
/// \name Operations
/// \{

public:
	/// \brief Call this function in init_modules() to use clanMikMod.
	static void init(bool register_resources_only = false);

	/// \brief Call this function in deinit_modules().
	static void deinit();
/// \}
};

/// \}
