//
// Created by Samer Ali on 9/18/23.
//

/**
 * @author: Samer Ali
 * @desc: utility toolkit extension library for C++ std utility lib
 */
#ifndef CUTE_CORE_HPP
#define CUTE_CORE_HPP


#include <cstdint>
#include <utility>
#include <type_traits>
#include <algorithm>
#include <sys/stat.h>
#include <dirent.h>
#include <vector>
#include <string>


#define ERROR_EXIT( str ) do {fprintf(stderr, str); exit(1);}while(0)
//#define JPEG 0xFFD8
//#define GIF 0x47494638
//#define PNG 0x89504E47
//#define PDF 0x25504446
//#define MP3 0x494433 // ID3 tag
//#define FLAC 0x664C6143
//#define WAV 0x52494646 // RIFF header
//#define AVI 0x41564920
//#define ZIP 0x504B0304 // Local file header signature
//#define RAR 0x52617221
//#define __7Z 0x377ABCAF271C
//#define EXE 0x4D5A // PE signature
//#define ELF 0x7F454C46
//#define XML 0x3C3F786D6C // <?xml
//#define JSON 0x7B // {
//#define YAML 0x2D2D2D // ---
//#define MPEG 0x000001BA // Pack header
//#define WEBM 0x1A45DFA3
//#define RGBA 4
//#define RGB 3


namespace cute
{
	static void error_callback ( int error ,
	                             const char* description )
	{
		fprintf( stderr , "GLFW Error %d: %s\n" , error , description );
	}


	// APIS to handle stat and file args
	enum
	{
		FILES , DIRECTORIES , FILES_AND_DIRECTORIES , MAX_PATH = 256
	};


	// validates if path exists in system
	static bool is_path ( const char* path )
	{
		FILE* file = fopen( path , "r" );
		return file != nullptr && !fclose( file );
	}


	// validates if provided path leads to a file
	static bool is_file ( const char* path )
	{
		struct stat my_stat { };
		stat( path , &my_stat );
		return S_ISREG( my_stat.st_mode );
	}


	// validates if provided path leads to a directory
	static bool is_directory ( const char* path )
	{
		struct stat my_stat { };
		stat( path , &my_stat ); //
		return S_ISDIR( my_stat.st_mode );
	}


	enum class Option : int
	{
		CUTE_KEY_ESCAPE = 256
	};
	enum class State : int
	{
		CUTE_CONFIG_KEY_INPUT = 0
	};
	//empty struct. used for template types that are not necessary
	struct empty
	{
	};

	namespace details
	{
		template < typename T > using has_assign_op = decltype( std::declval< T& >() = std::declval< T const& >() );
	}

	template < typename T >
	struct has_assign_operator : std::integral_constant< bool , !std::is_void< details::has_assign_op< T>>::value >
	{
	};

	//    int64_t ceil(long long n)
	//    {
	//        uint8_t sign {n > 0};
	//        int64_t whole_n {n};
	//        return sign ?
	//               (n > whole_n ? whole_n + 1 : whole_n) :
	//               (n < whole_n ? whole_n - 1 : whole_n);
	//    }

	inline int64_t floor ( long long n )
	{ return static_cast<int64_t>(n); }


	template < typename T >
	inline std::enable_if_t< !has_assign_operator< T >::value , T& > genericAssign ( T& to ,
	                                                                                 T&& rhs )
	{ return to = std::move( rhs ); }

	//    template<typename T>
	//    auto genericAssign(T& to, T&& rhs) -> std::enable_if_t<!has_assign_operator<T>::value, T&>
	//    {
	//        auto old = std::exchange(to, std::forward<T>(rhs));
	//        if(&old != &rhs)
	//            std::exchange(to, old);
	//        return to;
	//    }
}
#endif // CUTE_CORE_HPP