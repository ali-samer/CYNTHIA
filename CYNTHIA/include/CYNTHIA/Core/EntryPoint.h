//
// Created by Samer Ali on 8/14/23.
//

#ifndef CYNTHIA_CORE_ENTRYPOINT_H
#define CYNTHIA_CORE_ENTRYPOINT_H

#include "CYNTHIA/Cynthia.h"

int main(int argc, char** argv)
{
	Eigen::MatrixXd matrix1(2, 2);
	matrix1 << 1, 2,
		3, 4;

	Eigen::MatrixXd matrix2(2, 2);
	matrix2 << 5, 6,
		7, 8;

	// Element-wise addition
	Eigen::MatrixXd result1 = matrix1 + matrix2;

	std::cout << "Element-wise addition:" << std::endl << result1 << std::endl;

	std::cout << "Size of Matrix1 is: " << matrix1.cols() << std::endl;

	Eigen::VectorXd vector1(3);
	vector1 << 1, 2, 3;

	Eigen::VectorXd vector2(3);
	vector2 << 4, 5, 6;

	// Element-wise addition for vectors
	Eigen::VectorXd result2 = vector1 + vector2;

	std::cout << "Element-wise addition for vectors:" << std::endl << result2 << std::endl;
	Cynthia::Vector<float> vec3(3);
	vec3 << 1,2,3;

	Cynthia::Vector<float> vec4(3);
	vec4 << 1,
	2,
	3;

	Cynthia::Vector<float> result3 = vec3 + vec4;

	std::cout << "Element-wise addition for cynthia vectors:" << std::endl << result3 << std::endl;
	std::cout << "Element on index one:  " << vec4[3] << std::endl;

	Cynthia::Log::Init();
	auto app = Cynthia::CreateApplication();
	app->Run();
	delete app;
}


#endif //CYNTHIA_CORE_ENTRYPOINT_H
