#pragma once

#include <string>

namespace Cynthia
{
	class FileDialog
	{
	public:
		static std::string OpenFileDialog(const char* filter);
		static std::string SaveFileDialog(const char* filter);
	};
}