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

Crystal::Math::Vector2dd SVD::calculate(const Crystal::Math::Matrix2dd& lhs)
{
	Matrix2f A = Impl::Converter::toEigen(lhs);
	cout << "Here is the matrix A:\n" << A << endl;
	SelfAdjointEigenSolver<Matrix2f> eigensolver(A);
	if (eigensolver.info() != Success) abort();
	const auto values = eigensolver.eigenvalues();
	cout << "The eigenvalues of A are:\n" << eigensolver.eigenvalues() << endl;
	cout << "Here's a matrix whose columns are eigenvectors of A \n"
		<< "corresponding to these eigenvalues:\n"
		<< eigensolver.eigenvectors() << endl;
	return Crystal::Math::Vector2dd(values[0], values[1]);
}

void SVD::calculate(const Crystal::Math::Matrix3dd& lhs)
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
