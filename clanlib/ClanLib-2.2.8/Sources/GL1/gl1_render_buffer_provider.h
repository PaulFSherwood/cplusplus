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
**    Harry Storbacka
*/

#pragma once


#include "gl1_graphic_context_provider.h"
#include "API/Display/TargetProviders/render_buffer_provider.h"

class CL_GL1RenderBufferProvider : public CL_RenderBufferProvider
{
/// \name Construction
/// \{

public:
	CL_GL1RenderBufferProvider(CL_GL1GraphicContextProvider *gc_provider);

	~CL_GL1RenderBufferProvider();


/// \}
/// \name Attributes
/// \{

public:
	CLuint get_handle();


/// \}
/// \name Operations
/// \{

public:
	/// \brief Creates a render buffer image of the specified dimensions.
	virtual void create(int width, int height, CL_TextureFormat internal_format, int multisample_samples);

	/// \brief Destroys the provider.
	virtual void destroy();


/// \}
/// \name Implementation
/// \{

private:
	CL_GL1GraphicContextProvider *gc_provider;

/// \}
};


