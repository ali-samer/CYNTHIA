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
#include <type_traits>


#ifndef GLAD_CONFIG_H_INCLUDED
#define GLAD_CONFIG_H_INCLUDED


#include "glad_config.h"


#endif


#include "CYNTHIA/Core/Utility.h"
#include "../EigenUtils/EigenAliases.h"
#include "load.h"
//#include <pybind11/pybind11.h>

namespace Cynthia
{
	enum class Channel : int
	{
		RGB       = 3 ,
		RGBA      = 4 ,
		HSV       = 3 ,
		YUV       = 3 ,
		CMYK      = 4 ,
		LAB       = 3 ,
		HSL       = 3 ,
		GRAYSCALE = 1 ,
		NULL_CH   = 0
	};

	template < typename T >
	using IsMatrixFloat = std::enable_if_t< std::is_same_v< T , Matrix< float>> , bool >;

	template < typename T >
	using IsMatrixInt = std::enable_if_t< std::is_same_v< T , Matrix< int>> , bool >;

	template < typename T >
	using IsMatrixUChar = std::enable_if_t< std::is_same_v< T , Matrix< unsigned char>> , bool >;

	template < typename T >
	using IsIntegral = std::enable_if_t< std::is_same_v< T , int > , bool >;

	template < typename T >
	using IsFloat = std::enable_if_t< std::is_same_v< T , float > , bool >;

	template < typename T >
	using IsDouble = std::enable_if_t< std::is_same_v< T , double > , bool >;

	template < typename T >
	using IsUChar = std::enable_if_t< std::is_same_v< T , unsigned char > , bool >;

	template < typename T >
	using IsChar = std::enable_if_t< std::is_same_v< T , char > , bool >;


	template < typename T = unsigned char >
	class Image
	{
	public:

		Image ( ) : m_width( 0 ) ,
		            m_height( 0 ) ,
		            m_colorChannel( Channel::NULL_CH ) ,
		            m_pixels( nullptr ) ,
		            m_textureLoaded( false ) ,
		            m_textureId( 0 ) ,
		            m_isReset( false )
		{
//			m_image = NULL;
		}

		Image(int width, int height, Channel colorChannel, std::unique_ptr<T> pixels, bool textureLoaded, GLuint textureId, bool isReset)
			: m_width(width),
			  m_height(height),
			  m_colorChannel(colorChannel),
			  m_pixels(std::move(pixels)),
			  m_textureLoaded(textureLoaded),
			  m_textureId(textureId),
			  m_isReset(isReset)
		{
		}

		Image (int width, int height, int channel = 3) : m_width(width),
														 m_height(height),
														 m_colorChannel((Channel)channel) ,
														 m_pixels( nullptr),
														 m_textureId(NULL),
														 m_isReset(false),
														 m_textureLoaded(false)
		{
			m_image.resize(width, height);
		}

		Image ( ImageMat< T > image , int width , int height , Channel ch , T* pixels ,
		        bool texture_loaded , GLuint texture_id , bool is_reset )

			:                       m_image( image ) ,
			                        m_width( width ) ,
			                        m_height( height ) ,
			                        m_colorChannel( ch ) ,
			                        m_pixels( pixels ) ,
			                        m_textureLoaded( texture_loaded ) ,
			                        m_textureId( texture_id ) ,
			                        m_isReset( is_reset )
		{
		}

		explicit Image ( const std::string & filepath , const Channel & color_channel = Channel::RGB )
		{
			*this = loadFromFile( filepath , color_channel );
		}

		Image ( const Image & image )
		{
			return new Image( image.m_image , image.m_width , image.m_height ,
			                  image.m_colorChannel , image.m_pixels ,
			                  image.m_textureLoaded , image.m_textureId , image.m_isReset );
		}

		Image ( const Image && image ) : Image(image)
		{

		}

		~Image ( )
		{
			this->free( );
			this->reset( );
		}

		/**
		 * Overloaded [] operator to access image rows
		 *
		 * @param i Row index
		 * @return Vector of Vectors containing pixel values for row i
		*/
		Vector< T > operator[] ( int i )
		{
			return m_image[ i ];
		}

		/**
		 * Equality operator overload
		 *
		 * @param img Image to compare
		 * @return True if images are equal, false otherwise
		*/
		bool operator== ( const Image & img )
		{
			if ( img.m_height != this->m_height )
				return false;
			if ( img.m_width != this->m_width )
				return false;
			if ( img.m_color_channel != this->m_colorChannel )
				return false;
			for ( int i = 0 ; i < this->m_height ; i++ )
			{
				for ( int j = 0 ; j < this->m_width ; j++ )
				{
					if ( m_image[ i ][ j ] != img[ i ][ j ] )
						return false;
				}
			}
			return true;
		}

		friend std::ostream& operator<<(std::ostream& os, const Image& img) {
			os << "MyClass data: " << img.m_image;
			return os;
		}

		/**
		 * Inequality operator overload
		 *
		 * @param img Image to compare
		 * @return True if images are not equal, false otherwise
		*/
		bool operator!= ( const Image & img )
		{
			return !operator==( img );
		}

		/**
		 * Pre-increment operator overload
		 *
		 * Increments all pixel values by 1
		*/
		Image< T > & operator++ ( int )
		{
			Vector< T > inc( 1 );
			inc.resize( ( int ) m_colorChannel - 1 );
			for ( int i = 0 ; i < this->m_height ; i++ )
			{
				for ( int j = 0 ; j < this->m_width ; j++ )
				{
					m_image[ i ][ j ] += inc;
				}
			}
			return *this;
		}

		/**
		 * Pre-decrement operator overload
		 *
		 * Decrements all pixel values by 1
		*/
		Image< T > & operator-- ( int ) // TODO: fix any possible mistakes
		{
			{
				Vector< T > inc( -1 );
				inc.resize( ( int ) m_colorChannel - 1 );
				for ( int i = 0 ; i < this->m_height ; i++ )
				{
					for ( int j = 0 ; j < this->m_width ; j++ )
					{
						m_image[ i ][ j ] += inc;
					}
				}
				return *this;
			}
		}

		/**
		 * Adds the pixel values of two images.
		 * This operator combines two images by element-wise addition,
		 * resulting in a new image with the sum of corresponding pixel values.
		 *
		 * @return A new image where pixel values are the sum of the input images' pixels.
		 */
		Image< T > & operator+ (const Image img) // TODO: fix any possible mistakes
		{
			int newWidth = m_width + img.m_width;
			int newHeight = m_height + img.m_height;
			Channel newColorChannel = m_colorChannel;
			bool newTextureLoaded = m_textureLoaded || img.m_textureLoaded;
			bool newIsReset = m_isReset || img.m_isReset;

			std::unique_ptr<T> newPixels = nullptr;
			if (newWidth > 0 && newHeight > 0)
			{
				newPixels = std::make_unique<T>(newWidth * newHeight);
			}

			auto *result = new Image<T>(newWidth, newHeight, newColorChannel, std::move(newPixels), newTextureLoaded, 0, newIsReset);

			return *result;
		}

		/**
		 * Subtracts the pixel values of two images.
		 * This operator combines two images by element-wise subtraction,
		 * resulting in a new image with the difference of corresponding pixel values.
		 *
		 * @return A new image where pixel values are the difference of the input images' pixels.
		 */
		Image<T> &operator-(const Image img)
		{
			int newWidth = m_width - img.m_width;
			int newHeight = m_height - img.m_height;
			Channel newColorChannel = m_colorChannel;
			bool newTextureLoaded = m_textureLoaded && !img.m_textureLoaded;
			bool newIsReset = m_isReset || img.m_isReset;

			std::unique_ptr<T> newPixels = nullptr;
			if (newWidth > 0 && newHeight > 0)
			{
				newPixels = std::make_unique<T[]>(newWidth * newHeight);
			}

			auto *result = new Image<T>(newWidth, newHeight, newColorChannel, std::move(newPixels), newTextureLoaded, 0, newIsReset);

			return *result;
		}

		/**
		 * Spatially smooths the pixels.
		 * Uses a recursive filter for this operation.
		 *
		 * @param sigma is the standard deviation
		 * used to make the subsequent calculations of statistical variations
		 * promotes accuracy
		 */
		Image & blur ( double sigma ) // TODO
		{
			return *this;
		}

		/**
		 * computes image whose pixels are L**2 norms of the colors of the
		 * instance image
		 *
		 * @return as new Image of type float
		 */
		Image< T > getNorm ( ) // TODO: check if works
		{
			Image< float > gradientNorm;
			gradientNorm.m_image
			            .resize( this->m_width , this->m_height );

			for ( int i = 0 ; i < this->m_height ; i++ )
			{
				for ( int j = 0 ; j < this->m_width ; j++ )
				{
					Vector<T> temp = gradientNorm.m_image[ i ][ j ];
					temp = temp.template cast<float>();
					auto norm = temp.norm();
					temp.resize(1);
					temp[0] = norm;
					gradientNorm[i][j] = temp;
				}
			}
			return gradientNorm;
		}

		/**
		 * Loads image from file
		 * @param filepath Path to image file, channel flag
		 * @return True if loaded successfully, false otherwise
		*/
		static Image< T > loadFromFile ( const std::string & filepath , Channel channel = Channel::RGB )
		{
			if ( !cute::is_file( filepath.c_str( ) ) )
			{
				assert( false && "filepath not recognized" );
			}

			int   ch = static_cast<int>(channel);
			Image temp;
			temp.m_colorChannel = channel;
			ImageMat< T > image_mat;

			temp.m_pixels = ( std::unique_ptr< T > ) stbi_load( filepath.c_str( ) , &temp.m_width , &temp.m_height ,
			                                                    &temp.m_color_channel , ch );
			for ( int i = 0 , step = 0 ; i < temp.m_height ; i++ )
			{
				for ( int j = 0 ; j < temp.m_width ; j++ , step += ch )
				{
					Vector< T > pixel_to_fill;
					pixel_to_fill.resize( ch );
					for ( int k            = 0 ; k < ch ; k++ )
					{
						pixel_to_fill[ k ] = temp.m_pixels[ step + k ];
					}
					temp.m_image[ i ][ j ] = pixel_to_fill;
				}
			}
			temp.loadTexture( );
			return temp;
		}

		/**
		 * Gets const iterator to pixel data
		 * @return Iterator pointer to pixel data
		*/
		T* getPixels ( ) { return m_pixels; }

		/**
		 * Normalizes pixel range
		 * @param min and max values inclusive
		 * @return current image instance
		 */
		Image< T > & normalize ( int min , int max )
		{
			for ( int i = 0 ; i < this->m_height ; i++ )
			{
				for ( int j = 0 ; j < this->m_width ; j++ )
				{
					for ( int k = 0 ; k < ( int ) this->m_colorChannel ; k++ )
					{
						if ( m_image[ i ][ j ][ k ] < min )
							m_image[ i ][ j ][ k ] = min;
						else if ( m_image[ i ][ j ][ k ] > max )
							m_image[ i ][ j ][ k ] = max;
					}
				}
			}
			return *this;
		}

		std::vector<Image> getGradient() {

			Image gradX(m_width, m_height, 1);
			Image gradY(m_width, m_height, 1);

			for(int y = 0; y < this->m_height; ++y) {
				for(int x = 0; x < this->m_width; ++x) {

					int x1 = std::max(0, x-1);
					int y1 = std::max(0, y-1);
					int x2 = std::min(x+1, m_width-1);
					int y2 = std::min(y+1, m_height-1);

					auto dx = m_image(y, x2)[0] - m_image(y, x1)[0];
					auto dy = m_image(y2, x)[1] - m_image(y1, x)[1];

					gradX.m_image(y, x)[0] = dx;
					gradY.m_image(y, x)[0] = dy;
				}
			}

			return {gradX, gradY};
		}
	private:

		/**
		 * Updates image texture ID
		 */
		void onUpdate ( ) // TODO
		{
			for(int i = 0, i2 = 0; i < m_height; i++)
			{
				for(int j = 0; j < m_width; j++)
				{
					for(int k = 0; k < (int)m_colorChannel; k++, i2++)
					{
						m_pixels[i2] = m_image[i][j][k];
					}
					i2++;
				}

			}
			this->loadTexture();
		}

		/**
		* Loads image texture
		*/
		void loadTexture ( )
		{
			if ( !m_pixels )
				assert( false && "Image data is NULL" );
			glGenTextures( 1 , &m_textureId );
			glBindTexture( GL_TEXTURE_2D , m_textureId );
			glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );
			glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGBA , &m_width , &m_height , 0 , GL_RGBA , GL_UNSIGNED_BYTE ,
			              m_pixels );

			glGenerateMipmap( GL_TEXTURE_2D );
			m_textureLoaded = true;
		}

		/**
		* Frees image data
		*/
		void freeData ( )
		{
			stbi_image_free( m_pixels );
			resetData( );
		}

		/**
		* Resets image data
		* essential after freeing image data
		*/
		void resetData ( )
		{
			if ( m_isReset )
				return;
			m_width         = 0;
			m_height        = 0;
			m_textureLoaded = false;
			m_textureId     = NULL;
			m_isReset       = true;
			freeData( );
		}
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