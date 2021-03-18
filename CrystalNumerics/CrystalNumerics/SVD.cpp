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
	Matrix2f A = Impl::Converter::toEigen(lhs);
	SelfAdjointEigenSolver<Matrix2f> eigensolver(A);
	if (eigensolver.info() != Success) {
		result.isOk = false;
	}
	result.isOk = true;
	const auto values = eigensolver.eigenvalues();
	const auto vectors = eigensolver.eigenvectors();
	result.eigenValues = Crystal::Math::Vector2dd(values[0], values[1]);
	return result;
}

Vector3dd SVD::calculate(const Matrix3dd& lhs)
{
	Matrix3f A = Impl::Converter::toEigen(lhs);
	SelfAdjointEigenSolver<Matrix3f> eigensolver(A);
	if (eigensolver.info() != Success) abort();
	const auto values = eigensolver.eigenvalues();
	const auto vectors = eigensolver.eigenvectors();
	return Crystal::Math::Vector3dd(values[0], values[1], values[2]);
}

void SVD::calculate(const Crystal::Math::Matrix4dd& lhs)
{
	Matrix2f A;
	A << 1, 2, 2, 3;
	cout << "Here is the matrix A:\n" << A << endl;
	SelfAdjointEigenSolver<Matrix2f> eigensolver(A);
	if (eigensolver.info() != Success) abort();
	cout << "The eigenvalues of A are:\n" << eigensolver.eigenvalues() << endl;
	cout << "Here's a matrix whose columns are eigenvectors of A \n"
		<< "corresponding to these eigenvalues:\n"
		<< eigensolver.eigenvectors() << endl;
}
