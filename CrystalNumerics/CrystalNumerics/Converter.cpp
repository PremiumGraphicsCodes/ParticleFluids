#include "pch.h"

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::Numerics::Impl;

Eigen::Matrix2f Converter::toEigen(const Matrix2dd& src)
{
	Eigen::Matrix2f dest;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			dest(i,j) = src[i][j];
		}
	}
	return dest;
}

Eigen::Matrix3f Converter::toEigen(const Matrix3dd& src)
{
	Eigen::Matrix3f dest;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			dest(i, j) = src[i][j];
		}
	}
	return dest;
}

Eigen::Matrix4f Converter::toEigen(const Matrix4dd& src)
{
	Eigen::Matrix4f dest;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			dest(i, j) = src[i][j];
		}
	}
	return dest;
}


Matrix2df Converter::fromEigen(const Eigen::Matrix2f& src)
{
	Matrix2df dest;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			dest[i][j] = src(i, j);
		}
	}
	return dest;
}

Matrix3df Converter::fromEigen(const Eigen::Matrix3f& src)
{
	Matrix3df dest;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			dest[i][j] = src(i, j);
		}
	}
	return dest;
}

Matrix4dd Converter::fromEigen(const Eigen::Matrix4d& src)
{
	Matrix4dd dest;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			dest[i][j] = src(i, j);
		}
	}
	return dest;
}
