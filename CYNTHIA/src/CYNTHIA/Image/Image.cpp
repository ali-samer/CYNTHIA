#include "CYNTHIA/Image/Image.h"

namespace Cynthia
{
	template <typename T>
	Image<T>::Image ( )
	{

	}
	template <typename T>
	Image<T>::Image ( const char* filename , int color_chanel )
	{
		pixels = (std::unique_ptr<T>) stbi_load(filename, &width, &height, &color_channels, color_chanel);

	}

	template <typename T>
	Image<T>::~Image( )
	{
	}

	template <typename T>
	Matrix< Vector<T> > Image<T>::loadImg ( std::string filename , int color_channel )
	{

	}

	template <typename T>
	Vector<T> Image<T>::operator[] ( int i )
	{
		return Cynthia::VectorXuc( );
	}
}