//
// Created by Samer Ali on 9/13/23.
//
#pragma once

#include "../EigenUtils/EigenAliases.h"
#include <pybind11/pybind11.h>

namespace Cynthia
{
	class Image : public Eigen::Matrix<unsigned char, -1, -1>
	{
	public:
		Image();
		~Image();

	};
	class Image read_image(std::string filename);
}
