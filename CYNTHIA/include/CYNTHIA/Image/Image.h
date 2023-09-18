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

namespace Color
{

	enum Channel : int
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
}


#include <utility>
#include "CYNTHIA/Core/Utility.h"
#include "../EigenUtils/EigenAliases.h"
#include "load.h"
//#include <pybind11/pybind11.h>

namespace Cynthia
{
	template < typename T = unsigned char >
	class Image
	{
	public:
		Image ( );
		explicit Image ( const char* filepath , int color_channel = 3 /* RGB */);
		~Image ( );
		ImageMat< T > loadImg ( std::string filename , int color_channel = 3 );

		Vector< T > operator[] ( int i );
		bool operator== ( const Image img );
		bool operator!= ( const Image img );
		void operator++ ( int );
		void operator-- ( int );


		T* dump ( );
	private:
		ImageMat< T >        m_image;
		std::unique_ptr< T > m_pixels;

		int m_texture_loaded;
		int m_width;
		int m_height;
		int m_color_channel;

	};

}