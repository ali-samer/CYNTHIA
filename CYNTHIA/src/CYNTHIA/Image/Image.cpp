#include "CYNTHIA/Image/Image.h"
#include "CYNTHIA/Core/Assert.h"


#if 1

namespace Cynthia
{
	template < typename T , typename DS >
	Image< T , DS >::Image ( ) : m_width( 0 ) ,
	                             m_height( 0 ) ,
	                             m_colorChannel( Channel::NULL_CH ) ,
	                             m_pixels( nullptr ) ,
	                             m_textureLoaded( false ) ,
	                             m_textureId( NULL ) ,
	                             m_isReset( false )
	{
		m_image = NULL;
	}

	template < typename T , typename DS >
	Image< T , DS >::Image ( ImageMat< T > image , int width , int height , Channel ch , T* pixels ,
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

	template < typename T , typename DS >
	Image< T , DS >::Image ( const std::string & filepath , const Channel & color_chanel )
	{
		*this = loadFromFile( filepath , color_chanel );
	}

	template < typename T , typename DS >
	Image< T , DS >::~Image ( )
	{
		this->free( );
		this->reset( );
	}

	template < typename T , typename DS >
	Vector< T > Image< T , DS >::operator[] ( int i )
	{
		return m_image[ i ];
	}

	template < typename T , typename DS >
	Image< T , DS >::Image ( const Image & image )
	{
		return new Image( image.m_image , image.m_width , image.m_height ,
		                  image.m_colorChannel , image.m_pixels ,
		                  image.m_textureLoaded , image.m_textureId , image.m_isReset );
	}
	template < typename T , typename DS >
	Image< T , DS >::Image ( const Image && image )
	{

	}

	template < typename T , typename DS >
	bool Image< T , DS >::operator== ( const Image & img )
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

	template < typename T , typename DS >
	bool Image< T , DS >::operator!= ( const Image & img )
	{
		return !operator==( img );
	}

	template < typename T , typename DS >
	void Image< T , DS >::operator++ ( int )
	{
		Vector< T > inc( 1 );
		inc.resize( ( int ) m_colorChannel - 1 );
		for ( int i = 0 ; i < m_height ; i++ )
		{
			for ( int j = 0 ; j < m_width ; j++ )
			{
				m_image[ i ][ j ] += inc;
			}
		}
	}

	template < typename T , typename DS >
	void Image< T , DS >::operator-- ( int )
	{
		Vector< T > inc( -1 );
		inc.resize( ( int ) m_colorChannel - 1 );
		for ( int i = 0 ; i < m_height ; i++ )
		{
			for ( int j = 0 ; j < m_width ; j++ )
			{
				m_image[ i ][ j ] += inc;
			}
		}
	}

	template < typename T , typename DS >
	T* Image< T , DS >::getPixels ( ) { return m_pixels; }

	template < typename T , typename DS >
	Image< T > Image< T , DS >::loadFromFile ( const std::string & filepath , Channel _ch )
	{
		if ( !cute::is_file( filepath.c_str( ) ) )
		{
			assert( false && "filepath not recognized" );
		}

		int   ch = static_cast<int>(_ch);
		Image temp;
		temp.m_colorChannel = _ch;
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
		return temp;
	}

	template < typename T , typename DS >
	void Image< T , DS >::freeData ( )
	{
		stbi_image_free( m_pixels );
		resetData( );
	}

	template < typename T , typename DS >
	void Image< T , DS >::resetData ( )
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

	template < typename T , typename DS >
	void Image< T , DS >::loadTexture ( )
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

	template < typename T , typename DS >
	Image< T , DS > & Image< T , DS >::blur ( double sigma )
	{
		return *this;
	}

	template < typename T , typename DS >
	auto Image< T , DS >::getNorm ( ) -> IsMatrixFloat< DS > // ensuring data structure (DS) is float instead of container
	{
		Image< float , Matrix< float > > gradientNorm;
		gradientNorm.m_image
		            .resize( this->m_width , this->m_height );
		for ( int i = 0 ; i < this->m_height ; i++ )
		{
			for ( int j = 0 ; j < this->m_width ; j++ )
			{
				this->m_image( i , j )
				    .norm( );
			}
		}
		return gradientNorm;
	}
}
#endif