#include "pch.h"

#include "SVD.h"

#include "Converter.h"

using namespace Crystal::Numerics;


//#include "framework.h"

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
	const auto values = eigensolver.eigenvalues();
	result.eigenValues = Crystal::Math::Vector2dd(values[0], values[1]);
	result.eigenVectors = Impl::Converter::fromEigen(eigensolver.eigenvectors());
	return result;
}

SVD::SVD3dResult SVD::calculate(const Matrix3dd& lhs)
{
	Matrix3d A = Impl::Converter::toEigen(lhs);
	SelfAdjointEigenSolver<Matrix3d> eigensolver(A);
	SVD3dResult result;
	if (eigensolver.info() != Success) {
		result.isOk = false;
	}
	result.isOk = true;
	const auto values = eigensolver.eigenvalues();
	result.eigenValues = Crystal::Math::Vector3dd(values[0], values[1], values[2]);
	result.eigenVectors = Impl::Converter::fromEigen(eigensolver.eigenvectors());
	return result;
}
