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
#include "css_parser_background_repeat.h"
#include "../css_box_properties.h"

std::vector<CL_String> CL_CSSParserBackgroundRepeat::get_names()
{
	std::vector<CL_String> names;
	names.push_back("background-repeat");
	return names;
}

void CL_CSSParserBackgroundRepeat::parse(CL_CSSBoxProperties &properties, const CL_String &name, const std::vector<CL_CSSToken> &tokens)
{
	size_t pos = 0;
	CL_CSSToken token = next_token(pos, tokens);
	if (token.type == CL_CSSToken::type_ident && pos == tokens.size())
	{
		if (token.value == "repeat")
			properties.background_repeat.type = CL_CSSBoxBackgroundRepeat::type_repeat;
		else if (token.value == "repeat-x")
			properties.background_repeat.type = CL_CSSBoxBackgroundRepeat::type_repeat_x;
		else if (token.value == "repeat-y")
			properties.background_repeat.type = CL_CSSBoxBackgroundRepeat::type_repeat_y;
		else if (token.value == "no-repeat")
			properties.background_repeat.type = CL_CSSBoxBackgroundRepeat::type_no_repeat;
		else if (token.value == "-clan-stretch")
			properties.background_repeat.type = CL_CSSBoxBackgroundRepeat::type_clan_stretch;
		else if (token.value == "inherit")
			properties.background_repeat.type = CL_CSSBoxBackgroundRepeat::type_inherit;
	}
}
