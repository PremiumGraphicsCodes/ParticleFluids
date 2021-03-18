#include "pch.h"

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::Numerics::Impl;

Eigen::Matrix2d Converter::toEigen(const Matrix2dd& src)
{
	Eigen::Matrix2d dest;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			dest(i,j) = src[i][j];
		}
	}
	return dest;
}

Eigen::Matrix3d Converter::toEigen(const Matrix3dd& src)
{
	Eigen::Matrix3d dest;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			dest(i, j) = src[i][j];
		}
	}
	return dest;
}

Eigen::Matrix4d Converter::toEigen(const Matrix4dd& src)
{
	Eigen::Matrix4d dest;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			dest(i, j) = src[i][j];
		}
	}
	return dest;
}


Matrix2dd Converter::fromEigen(const Eigen::Matrix2d& src)
{
	Matrix2dd dest;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			dest[i][j] = src(i, j);
		}
	}
	return dest;
}

Matrix3dd Converter::fromEigen(const Eigen::Matrix3d& src)
{
	Matrix3dd dest;
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
