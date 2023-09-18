//
// Created by Samer Ali on 9/13/23.
//
#pragma once


#include "eigen/Eigen/Eigen"


namespace Cynthia
{
	template < typename T >
	using Matrix = Eigen::Matrix< T , Eigen::Dynamic , Eigen::Dynamic >;

	template < typename T >
	using Vector = Eigen::Matrix< T , Eigen::Dynamic , 1 >;

	template < typename T >
	using RowVector = Eigen::Matrix< T , 1 , Eigen::Dynamic >;

	template < typename T >
	using ImageMat = Matrix< Vector< Vector< T > > >;
	// Unsigned char matrices
	using MatrixXuc = Eigen::Matrix< unsigned char , Eigen::Dynamic , Eigen::Dynamic >;

	// Float matrices
	using MatrixXf = Eigen::MatrixXf;

	// Double matrices
	using MatrixXd = Eigen::MatrixXd;

	// Complex float matrices
	using MatrixXcf = Eigen::MatrixXcf;

	// Complex double matrices
	using MatrixXcd = Eigen::MatrixXcd;

	// Unsigned char vectors
	using VectorXuc = Eigen::Matrix< unsigned char , Eigen::Dynamic , 1 >;

	// Float vectors
	using VectorXf = Eigen::VectorXf;
	using RowVectorXf = Eigen::RowVectorXf;

	// Double vectors
	using VectorXd = Eigen::VectorXd;
	using RowVectorXd = Eigen::RowVectorXd;

	// Complex float vectors
	using VectorXcf = Eigen::VectorXcf;
	using RowVectorXcf = Eigen::RowVectorXcf;

	// Complex double vectors
	using VectorXcd = Eigen::VectorXcd;
	using RowVectorXcd = Eigen::RowVectorXcd;

	// Integer matrices
	using MatrixXi = Eigen::MatrixXi;

	// Integer vectors
	using VectorXi = Eigen::VectorXi;
	using RowVectorXi = Eigen::RowVectorXi;

	// 3D float affine transform
	using Affine3f = Eigen::Affine3f;

	// 3D double affine transform
	using Affine3d = Eigen::Affine3d;

	// Float quaternion
	using Quaternionf = Eigen::Quaternionf;

	// Double quaternion
	using Quaterniond = Eigen::Quaterniond;

}