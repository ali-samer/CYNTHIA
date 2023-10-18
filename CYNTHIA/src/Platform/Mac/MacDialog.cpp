#include "CYNTHIA/Utils/FileDialog.h"

#ifdef CY_PLATFORM_DARWIN
namespace Cynthia
{
	std::string OpenFileDialog(const char* filter)
	{
		return "";
	}

	std::string SaveFileDialog(const char* filter)
	{
		return "";
	}
}
#endif