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
**    (if your name is missing here, please add it)
*/

#include "Display/precomp.h"
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#endif
#include "jpeg_provider_impl.h"
#include <jerror.h>
#include "API/Core/System/exception.h"
#include "API/Core/Text/string_format.h"

#define INPUT_BUF_SIZE  4096

/////////////////////////////////////////////////////////////////////////////
// CL_JPEGProvider_Impl construction:

CL_JPEGProvider_Impl::CL_JPEGProvider_Impl(
	const CL_String &name,
	const CL_VirtualDirectory &directory)
: directory(directory)
{
	filename = name;
	image = NULL;

	init();
}

CL_JPEGProvider_Impl::CL_JPEGProvider_Impl(
	CL_IODevice &iodev)
{
	input_source = iodev;
	image = NULL;

	init();
}

CL_JPEGProvider_Impl::~CL_JPEGProvider_Impl()
{
	deinit();
}

/////////////////////////////////////////////////////////////////////////////
// CL_JPEGProvider_Impl operations:
  
void *CL_JPEGProvider_Impl::get_data()
{
	return image;
}

void CL_JPEGProvider_Impl::init()
{
	struct jpeg_error_mgr jerr;	
	struct jpeg_decompress_struct cinfo;
	//	FILE * infile;		
	JSAMPARRAY buffer;	
	int row_stride;		
	
	memset (&cinfo,0,sizeof(cinfo));

	if (input_source.is_null())
	{
		input_source = directory.open_file(
			filename,
			CL_File::open_existing,
			CL_File::access_read | CL_File::access_write,
			CL_File::share_all);
	}

	cinfo.err = jpeg_std_error(&jerr);
	jerr.error_exit = jpeg_local_error_exit;

	jpeg_create_decompress(&cinfo);
	jpeg_InputSource_src(&cinfo, this);
	jpeg_read_header(&cinfo, TRUE);
	// cinfo.dct_method = JDCT_FLOAT; // Float is only faster with my SSE patch for libjpeg -- mbn 13. Sept 2009
	jpeg_start_decompress(&cinfo);

	row_stride = cinfo.output_width * cinfo.output_components;

	width = cinfo.output_width;
	height = cinfo.output_height;
	pitch = width * 3;

	// FIXME: Where is the allocated memory freed?
	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 32);

	image = new unsigned char[get_pitch() * cinfo.output_height];

	// RGB Image
	if (cinfo.output_components == 3)
	{
		while (cinfo.output_scanline < cinfo.output_height) 
		{
			jpeg_read_scanlines(&cinfo, buffer, 1);
		
			unsigned char *outptr = image + pitch * (cinfo.output_scanline-1);
			for(unsigned int i=0; i < pitch; i += 3)
			{
				outptr[i + 0] = buffer[0][i + 2];
				outptr[i + 1] = buffer[0][i + 1];
				outptr[i + 2] = buffer[0][i + 0];
			}
		}
	}
	// Greyscale Image
	else if (cinfo.output_components == 1)
	{
		while (cinfo.output_scanline < cinfo.output_height) 
		{
			jpeg_read_scanlines(&cinfo, buffer, 1);
			
			unsigned char *outptr = image + pitch * (cinfo.output_scanline-1);
			for(int i=0; i < width; i += 1)
			{
				outptr[3*i + 0] = buffer[0][i];
				outptr[3*i + 1] = buffer[0][i];
				outptr[3*i + 2] = buffer[0][i];
			}
		}
	}
	else
	{
		throw CL_Exception(cl_format("CL_JPEGProvider: Unsupported color completion: %1",  cinfo.output_components));
	}
	
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	input_source = CL_IODevice();

	// this could be integrated better, but I'm too tired, so I just hack CL_JPEGProvider
	// support into it. -- mbn 21. feb 2002

	CL_JPEGProvider_Impl::sized_format = cl_rgb8;
	CL_JPEGProvider_Impl::pitch = get_pitch();
	CL_JPEGProvider_Impl::width = get_width();
	CL_JPEGProvider_Impl::height = get_height();
}

void CL_JPEGProvider_Impl::deinit()
{
	delete[] image;
	image = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CL_JPEGProvider_Impl implementation:

void CL_JPEGProvider_Impl::jpeg_local_error_exit (jpeg_common_struct* cinfo)
{
	/* Always display the message */
	(*cinfo->err->output_message) (cinfo);

	/* Let the memory manager delete any temp files before we die */
	jpeg_destroy(cinfo);

	throw CL_Exception(cl_format("CL_JPEGProvider: Error: %1",  cinfo->err->msg_code));
}

void CL_JPEGProvider_Impl::jpeg_InputSource_src (j_decompress_ptr cinfo, CL_JPEGProvider_Impl* provider)
{
	InputSource_src_ptr src;
	
	if (cinfo->src == NULL) /* first time for this JPEG object? */
	{
		cinfo->src = (struct jpeg_source_mgr*)
			(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
						    sizeof(InputSource_source_mgr));
		src = (InputSource_src_ptr) cinfo->src;
		src->buffer = (JOCTET *)
			(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
						    INPUT_BUF_SIZE * sizeof(JOCTET));
	}

	src = (InputSource_src_ptr) cinfo->src;
	src->pub.init_source = CL_JPEGProvider_Impl::init_source;
	src->pub.fill_input_buffer = CL_JPEGProvider_Impl::fill_input_buffer;
	src->pub.skip_input_data = CL_JPEGProvider_Impl::skip_input_data;
	src->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
	src->pub.term_source = CL_JPEGProvider_Impl::term_source;
	src->jpeg_provider = provider;
	src->pub.bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
	src->pub.next_input_byte = NULL; /* until buffer loaded */
}

void CL_JPEGProvider_Impl::init_source (j_decompress_ptr cinfo)
{
	InputSource_src_ptr src = (InputSource_src_ptr) cinfo->src;
	src->start_of_file = TRUE;	
}

boolean CL_JPEGProvider_Impl::fill_input_buffer (j_decompress_ptr cinfo)
{
	InputSource_src_ptr src = (InputSource_src_ptr) cinfo->src;
	size_t nbytes;

	nbytes = src->jpeg_provider->input_source.read(src->buffer, INPUT_BUF_SIZE);
	
	if (nbytes <= 0) 
	{
		if (src->start_of_file)	/* Treat empty input file as fatal error */
			ERREXIT(cinfo, JERR_INPUT_EMPTY);
		WARNMS(cinfo, JWRN_JPEG_EOF);
		/* Insert a fake EOI marker */
		src->buffer[0] = (JOCTET) 0xFF;
		src->buffer[1] = (JOCTET) JPEG_EOI;
		nbytes = 2;
	}
	src->pub.next_input_byte = src->buffer;
	src->pub.bytes_in_buffer = nbytes;
	src->start_of_file = FALSE;
	
	return TRUE;
}

void CL_JPEGProvider_Impl::skip_input_data (j_decompress_ptr cinfo, long num_bytes)
{
	InputSource_src_ptr src = (InputSource_src_ptr) cinfo->src;
	
	/* Just a dumb implementation for now.  Could use fseek() except
	 * it doesn't work on pipes.  Not clear that being smart is worth
	 * any trouble anyway --- large skips are infrequent.
	 */
	if (num_bytes > 0)
	{
		while (num_bytes > (long) src->pub.bytes_in_buffer)
		{
			num_bytes -= (long) src->pub.bytes_in_buffer;
			(void) fill_input_buffer(cinfo);
			/* note we assume that fill_input_buffer will never return FALSE,
			 * so suspension need not be handled.
			 */
		}
		src->pub.next_input_byte += (size_t) num_bytes;
		src->pub.bytes_in_buffer -= (size_t) num_bytes;
	}
}

void CL_JPEGProvider_Impl::term_source (j_decompress_ptr cinfo)
{
	// do nothing
}
