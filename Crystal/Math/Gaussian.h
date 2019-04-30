#pragma once

#include <cmath>
#include "Tolerance.h"

namespace Crystal {
	namespace Math {

class Gaussian
{
public:
	Gaussian() :
		mu(0.0),
		tau(1.0)
	{}

	Gaussian(double mu, double tau) :
		mu(mu),
		tau(tau)
	{}

	double getValue(const double x) {
		const auto scale = 1.0 / ( std::sqrt(2.0 * Tolerance<double>::getPI()) * tau );
		const auto power = -(x - mu) * (x - mu) / (2.0 * tau * tau);
		return scale * std::exp(power);
	}

private:
	double mu;
	double tau;
};
	}
}