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
*/

#include "CSSLayout/precomp.h"
#include "css_box_height.h"
#include "../../css_resource_cache.h"

CL_CSSBoxHeight::CL_CSSBoxHeight()
: type(type_auto)
{
}

void CL_CSSBoxHeight::compute(const CL_CSSBoxHeight *parent, CL_CSSResourceCache *layout, float em_size, float ex_size, bool is_containing_block_height_auto)
{
	if (type == type_inherit)
	{
		if (parent)
		{
			type = parent->type;
			length = parent->length;
			percentage = parent->percentage;
		}
		else
		{
			type = type_auto;
		}
	}

	// To do: This property does not apply to non-replaced inline-level elements. Set it to type_auto in this case.

	if (type == type_percentage && is_containing_block_height_auto)
		type = type_auto;

	if (type == type_length)
		length = layout->compute_length(length, em_size, ex_size);
}
