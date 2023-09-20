//
// Created by Samer Ali on 9/13/23.
//
#if 0
Copyright (c) 2023 Samer Ali and Rahul Singh

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#endif

#pragma once


#include <utility>
#include "glad/glad.h"
#include "CYNTHIA/Core/Utility.h"
#include "../EigenUtils/EigenAliases.h"
#include "load.h"
//#include <pybind11/pybind11.h>

namespace Cynthia
{
	enum class Channel : int
	{
		RGB ,
		RGBA ,
		HSV ,
		YUV ,
		CMYK ,
		LAB ,
		HSL ,
		GRAYSCALE
	};
	struct ImageData
	{
		GLenum texture_internal_fmt;
		GLenum original_pixel_fmt;
		GLenum texture_data_t;
		GLenum original_data_t;
		GLuint texture;
		uint8_t* pixels { NULL };

		int texture_loaded { };
		int length = width * height * num_color_ch;
		int width { };
		int height { };
		int num_color_ch { };
		int num_mipmap_lvls { };

		bool flip_vertically;
		int  error_code { };
		const char* error_msg;

		void reset();
	};

	template < typename T = unsigned char >
	class Image
	{
	public:
		explicit Image ( const char* filepath , Channel flag = Channel::RGB );
		Image ( );
		explicit Image ( const char* filepath , int color_channel = 3 /* RGB */);
		~Image ( );
		static Image< T > LoadImg ( std::string filename , Channel color_channel = Channel::RGB );

		Vector< T > operator[] ( int i );
		bool operator== ( const Image img );
		bool operator!= ( const Image img );
		void operator++ ( int );
		void operator-- ( int );


		T* dump ( );

	private:
		void loadData();
		void free();
		void reset();
	public:
		ImageData* m_data;
	private:
		ImageMat< T >        m_image;
		std::unique_ptr< T > m_pixels;

		int m_texture_loaded;
		int m_width;
		int m_height;
		int m_color_channel;

	};

}