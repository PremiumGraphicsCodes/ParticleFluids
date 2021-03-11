// CrystalNumerics.cpp : スタティック ライブラリ用の関数を定義します。
//

#include "pch.h"
#include "framework.h"
#include <iostream>
#include <Eigen/Dense>
using Eigen::MatrixXd;

// TODO: これは、ライブラリ関数の例です
void fnCrystalNumerics()
{


	{
		MatrixXd m(2, 2);
		m(0, 0) = 3;
		m(1, 0) = 2.5;
		m(0, 1) = -1;
		m(1, 1) = m(1, 0) + m(0, 1);
		std::cout << m << std::endl;
	}
}
