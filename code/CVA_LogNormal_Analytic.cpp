#include <boost/math/distributions.hpp>
#include <fstream>
#include "CVA_LogNormal_Analytic.h"

using namespace boost;
using namespace std;

double CVA_LogNormal_Analytic(
	const double term, const double integralTerm,
	const std::size_t devideNum, const double strike)
{
	boost::math::normal_distribution<double> n(0.0, 1.0);	
	double dt = term / devideNum;
	double integral = 0.0;
	double pre = 0.0;
	double fw = 0.0;
	for (std::size_t i = 0; i * dt < integralTerm; ++i) {
		double t = (i+1) * dt;
		double e  = std::exp(term / 2.0);
		double x1 = ((term + t) / 2.0 - std::log(strike)) /std::sqrt(t);
		double x2 = ((term - t) / 2.0 - std::log(strike)) / std::sqrt(t);
		double phi1 = boost::math::cdf(n, x1);
		double phi2 = boost::math::cdf(n, x2);

		fw = e * phi1 - strike * phi2;
		integral += dt * (fw + pre) / 2.0;
		pre = fw;
	}
	return integral;
}
