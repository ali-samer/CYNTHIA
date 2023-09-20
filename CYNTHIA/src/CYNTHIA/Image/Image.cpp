#include "CYNTHIA/Image/Image.h"
#include "CYNTHIA/Core/Assert.h"

#if 1

namespace Cynthia
{
	template <typename T>
	Image<T>::Image ( ) : m_texture_loaded(0), m_width(0), m_height(0), m_color_channel(0), m_pixels( nullptr )
	{
		m_image = NULL;
		m_data = nullptr;
	}

	template <typename T>
	Image<T>::Image ( const char* filepath , Channel color_chanel )
	{
		*this = LoadImg( filepath, color_chanel);
		this->loadData();
	}

	template <typename T>
	Image<T>::~Image ( )
	{
		this->free();
		this->reset();
	}

	template <typename T>
	Vector<T> Image<T>::operator[] ( int i )
	{
		return m_image[i];
	}

	template < typename T >
	bool Image< T >::operator== ( const Image img )
	{
		if(img.m_height != m_height || m_height == 0)
			return false;
		if(img.m_width != m_width || m_width == 0)
			return false;
		if(img.m_color_channel != m_color_channel || m_color_channel == 0)
			return false;
		for(int i = 0; i < m_height; i++)
		{
			for(int j = 0; j < m_width; j++)
			{
				if(m_image[i][j] != img[i][j])
					return false;
			}
		}
		return true;
	}

	template < typename T >
	bool Image< T >::operator!= ( const Image img )
	{
		return !operator==(img);
	}

	template < typename T >
	void Image< T >::operator++ ( int )
	{
		Vector<T> inc(1);
		inc.resize(m_color_channel - 1);
		for(int i = 0; i < m_height; i++)
		{
			for(int j = 0; j < m_width; j++)
			{
				m_image[i][j] += inc;
			}
		}
	}

	template < typename T >
	void Image< T >::operator-- ( int )
	{
		Vector<T> inc(-1);
		inc.resize(m_color_channel - 1);
		for(int i = 0; i < m_height; i++)
		{
			for(int j = 0; j < m_width; j++)
			{
				m_image[i][j] += inc;
			}
		}
	}

	template < typename T >
	T* Image< T >::dump ( )
	{
		return m_pixels;
	}

	template <typename T>
	Image<T> Image<T>::LoadImg ( std::string filename , Channel _ch )
	{
		int ch = static_cast<int>(_ch);
		Image temp;
		if(!cute::is_file(filename.c_str()))
		{
			assert("filepath not recognized");
		}
		ImageMat<T> image_mat;
		#if 1 // TODO: used to comment out code. remove when no longer in need
		temp.m_pixels = (std::unique_ptr<T>) stbi_load(filename.c_str(), &temp.m_width, &temp.m_height, &temp.m_color_channel, ch);
		for(int i = 0; i < temp.m_height; i++)
		{
			for(int j = 0; j < temp.m_width; j++)
			{
				Vector<T> pixel_values;
				pixel_values.resize(ch);
				for(int k = 0; k < ch; k++)
				{
					pixel_values[k] = temp.m_pixels[i+j];
				}
				temp.m_image[i][j] = pixel_values;
			}
		}
		#endif
		return temp;
	}

	template <typename T>
	void Image<T>::free()
	{
		stbi_image_free(m_pixels);
	}

	template <typename T>
	void Image<T>::reset()
	{
		m_data->reset();
	}
}
#endif