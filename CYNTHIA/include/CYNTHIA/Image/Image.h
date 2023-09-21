/**
 * @file Image.h
 * @brief Image class definition
 * @author Samer Ali
 * @date September 2023
*/

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
		RGB       = 3,
		RGBA      = 4,
		HSV       = 3,
		YUV       = 3,
		CMYK      = 4,
		LAB       = 3,
		HSL       = 3,
		GRAYSCALE = 1,
		NULL_CH   = 0
	};

	#if 0 // reference this data structure for image data
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

		void reset ( );
	};
	#endif
	#if 0
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
		void texture();
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
	#endif
	template < typename T = unsigned char>
	class Image
	{
	public:

		Image ( );

		Image (ImageMat<T> image, int width, int height, Channel ch, T* pixels,
		                   bool texture_loaded, GLuint texture_id, bool is_reset);

		Image ( const std::string & filepath , const Channel & colo_channel = Channel::RGB );

		Image(const Image& image);

		Image(const Image&& image);

		~Image ( );

		/**
		 * Overloaded [] operator to access image rows
		 *
		 * @param i Row index
		 * @return Vector of Vectors containing pixel values for row i
		*/
		Vector< T > operator[] ( int i );

		/**
		 * Equality operator overload
		 *
		 * @param img Image to compare
		 * @return True if images are equal, false otherwise
		*/
		bool operator== ( const Image & img );

		/**
		 * Inequality operator overload
		 *
		 * @param img Image to compare
		 * @return True if images are not equal, false otherwise
		*/
		bool operator!= ( const Image & img );

		/**
		 * Pre-increment operator overload
		 *
		 * Increments all pixel values by 1
		*/
		void operator++ ( int );

		/**
		 * Pre-decrement operator overload
		 *
		 * Decrements all pixel values by 1
		*/
		void operator-- ( int );

		/**
		 * computes gradient norm of image relative to color
		 * brightness
		 * */

		/**
		 * Spatially smooths the pixels.
		 * Uses a recursive filter for this operation.
		 *
		 * @param sigma is the standard deviation
		 * used to make the subsequent calculations of statistical variations
		 * promotes accuracy
		 */
		 void blur(double sigma);

		 /**
		  * computes image whose pixels are L**2 norms of the colors of the
		  * instance image
		  *
		  * @return as new Image of type float
		  */
		 Image<float> getNorm();

		/**
		 * Loads image from file
		 * @param filepath Path to image file, channel flag
		 * @return True if loaded successfully, false otherwise
		*/
		static Image< T > loadFromFile ( const std::string & filepath , Channel channel = Channel::RGB );

		/**
		 * Gets const iterator to pixel data
		 * @return Iterator pointer to pixel data
		*/
		T* getPixels();
	private:

		/**
		* Loads image texture
		*/
		void loadTexture ( );

		/**
		* Frees image data
		*/
		void freeData ( );

		/**
		* Resets image data
		* essential after freeing image data
		*/
		void resetData ( );
	private:
		ImageMat< T >        m_image;
		std::unique_ptr< T > m_pixels;
		int                  m_width;
		int                  m_height;
		bool                 m_textureLoaded;
		bool                 m_isReset;
		GLuint               m_textureId;
		Channel              m_colorChannel;
	};

}