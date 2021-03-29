#include "pch.h"

#include "SVD.h"

#include "Converter.h"

using namespace Crystal::Numerics;

#include <iostream>
#include <Eigen/Dense>
//#include <Eigen/SVD>

//using namespace Crystal::Numerics;

using namespace std;
using namespace Eigen;
using namespace Crystal::Math;

SVD::SVD2dResult SVD::calculate(const Matrix2dd& lhs)
{
	SVD2dResult result;
	Matrix2d A = Impl::Converter::toEigen(lhs);
	SelfAdjointEigenSolver<Matrix2d> eigensolver(A);
	if (eigensolver.info() != Success) {
		result.isOk = false;
	}
	result.isOk = true;
	result.eigenValues = Impl::Converter::fromEigen(eigensolver.eigenvalues());
	result.eigenVectors = Impl::Converter::fromEigen(eigensolver.eigenvectors());
	return result;
}

SVD::SVD3dResult SVD::calculate(const Matrix3dd& lhs)
{
	SVD3dResult result;
	Matrix3d A = Impl::Converter::toEigen(lhs);
	SelfAdjointEigenSolver<Matrix3d> eigensolver(A);
	if (eigensolver.info() != Success) {
		result.isOk = false;
	}
	result.isOk = true;
	result.eigenValues = Impl::Converter::fromEigen(eigensolver.eigenvalues());
	result.eigenVectors = Impl::Converter::fromEigen(eigensolver.eigenvectors());
	return result;
}
