#include "CYNTHIA/Image/Image.h"
#include "CYNTHIA/Core/Assert.h"


#if 1

namespace Cynthia
{
	template < typename T >
	Image< T >::Image ( ) : m_textureLoaded( false ) ,
	                        m_width( 0 ) ,
	                        m_height( 0 ) ,
	                        m_colorChannel( Channel::NULL_CH ) ,
	                        m_pixels( nullptr )
	{
		m_image = NULL;
	}

	template < typename T >
	Image< T >::Image ( const std::string& filepath , const Channel& color_chanel )
	{
		*this = loadFromFile( filepath , color_chanel );
	}

	template < typename T >
	Image< T >::~Image ( )
	{
		this->free( );
		this->reset( );
	}

	template < typename T >
	Vector< T > Image< T >::operator[] ( int i )
	{
		return m_image[ i ];
	}

	template < typename T >
	bool Image< T >::operator== ( const Image& img )
	{
		if ( img.m_height != m_height || m_height == 0 )
			return false;
		if ( img.m_width != m_width || m_width == 0 )
			return false;
		if ( img.m_color_channel != m_colorChannel || m_colorChannel == Channel::NULL_CH )
			return false;
		for ( int i = 0 ; i < m_height ; i++ )
		{
			for ( int j = 0 ; j < m_width ; j++ )
			{
				if ( m_image[ i ][ j ] != img[ i ][ j ] )
					return false;
			}
		}
		return true;
	}

	template < typename T >
	bool Image< T >::operator!= ( const Image& img )
	{
		return !operator==( img );
	}

	template < typename T >
	[[noreturn]] void Image< T >::operator++ ( int )
	{
		Vector< T > inc( 1 );
		inc.resize( (int)m_colorChannel - 1 );
		for ( int i = 0 ; i < m_height ; i++ )
		{
			for ( int j = 0 ; j < m_width ; j++ )
			{
				m_image[ i ][ j ] += inc;
			}
		}
	}

	template < typename T >
	[[noreturn]] void Image< T >::operator-- ( int )
	{
		Vector< T > inc( -1 );
		inc.resize( (int)m_colorChannel - 1 );
		for ( int i = 0 ; i < m_height ; i++ )
		{
			for ( int j = 0 ; j < m_width ; j++ )
			{
				m_image[ i ][ j ] += inc;
			}
		}
	}

	template < typename T >
	std::shared_ptr< T > Image< T >::getPixels ( ) const
	{
		return m_pixels;
	}

	template < typename T >
	Image< T > Image< T >::loadFromFile ( const std::string& filepath , Channel _ch )
	{
		int   ch = static_cast<int>(_ch);
		Image temp;
		if ( !cute::is_file( filepath.c_str( ) ) )
		{
			assert( "filepath not recognized" );
		}
		ImageMat< T > image_mat;
		#if 1 // TODO: used to comment out code. remove when no longer in need
		temp.m_pixels = ( std::unique_ptr< T > ) stbi_load( filepath.c_str( ) , &temp.m_width , &temp.m_height ,
		                                                    &temp.m_color_channel , ch );
		for ( int i = 0 ; i < temp.m_height ; i++ )
		{
			for ( int j = 0 ; j < temp.m_width ; j++ )
			{
				Vector< T > pixel_values;
				pixel_values.resize( ch );
				for ( int k            = 0 ; k < ch ; k++ )
				{
					pixel_values[ k ] = temp.m_pixels[ i + j ];
				}
				temp.m_image[ i ][ j ] = pixel_values;
			}
		}
		#endif
		return temp;
	}

	template < typename T >
	void Image< T >::freeData ( )
	{
		stbi_image_free( m_pixels );
	}

	template < typename T >
	void Image< T >::resetData ( )
	{
		m_width         = 0;
		m_height        = 0;
		m_textureLoaded = false;
		m_textureId     = NULL;
	}

	template < typename T >
	void Image< T >::loadTexture ( )
	{
		if ( !m_pixels )
			assert( false && "Image data is NULL" );
		glGenTextures( 1 , &m_textureId );
		glBindTexture( GL_TEXTURE_2D , m_textureId );
		glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGBA , m_width , m_height , 0 , GL_RGBA , GL_UNSIGNED_BYTE ,
		              m_pixels );

		glGenerateMipmap( GL_TEXTURE_2D );
		m_textureLoaded = true;
	}
	#if 0

	void texture_image ( std::shared_ptr< Image > img )
	{
		if ( img->pixels == NULL )
			assert( false && "Image data is NULL" );
		glGenTextures( 1 , &img->texture );
		glBindTexture( GL_TEXTURE_2D , img->texture );
		glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGBA , img->width , img->height , 0 , GL_RGBA , GL_UNSIGNED_BYTE ,
					  img->pixels );

		glGenerateMipmap( GL_TEXTURE_2D );
		img->texture_loaded = true;
	}

	#endif
}
#endif