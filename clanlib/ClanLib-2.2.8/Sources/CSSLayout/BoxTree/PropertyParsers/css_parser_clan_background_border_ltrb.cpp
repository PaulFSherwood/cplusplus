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
#include "css_parser_clan_background_border_ltrb.h"
#include "../css_box_properties.h"

std::vector<CL_String> CL_CSSParserClanBackgroundBorderLTRB::get_names()
{
	std::vector<CL_String> names;
	names.push_back("-clan-background-border-left");
	names.push_back("-clan-background-border-top");
	names.push_back("-clan-background-border-right");
	names.push_back("-clan-background-border-bottom");
	return names;
}

void CL_CSSParserClanBackgroundBorderLTRB::parse(CL_CSSBoxProperties &properties, const CL_String &name, const std::vector<CL_CSSToken> &tokens)
{
	CL_CSSBoxClanBackgroundBorder *width = 0;
	if (name == "-clan-background-border-top")
		width = &properties.clan_background_border_top;
	else if (name == "-clan-background-border-right")
		width = &properties.clan_background_border_right;
	else if (name == "-clan-background-border-bottom")
		width = &properties.clan_background_border_bottom;
	else if (name == "-clan-background-border-left")
		width = &properties.clan_background_border_left;

	if (width)
	{
		size_t pos = 0;
		CL_CSSToken token = next_token(pos, tokens);
		if (token.type == CL_CSSToken::type_ident && pos == tokens.size())
		{
			if (token.value == "inherit")
				width->type = CL_CSSBoxClanBackgroundBorder::type_inherit;
		}
		else if (is_length(token) && pos == tokens.size())
		{
			CL_CSSBoxLength length;
			if (parse_length(token, length) && length.type == CL_CSSBoxLength::type_px)
			{
				width->type = CL_CSSBoxClanBackgroundBorder::type_length;
				width->length = length;
			}
		}
	}
}
