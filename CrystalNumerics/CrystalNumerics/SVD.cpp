#include "pch.h"

#include "SVD.h"

using namespace Crystal::Numerics;


//#include "framework.h"

#include <iostream>
#include <Eigen/Dense>

//using namespace Crystal::Numerics;

using namespace std;
using namespace Eigen;

void SVD::calculate(const Crystal::Math::Matrix3dd& lhs, const Crystal::Math::Matrix3dd& rhs)
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
