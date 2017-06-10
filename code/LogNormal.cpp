#include <boost/math/distributions.hpp>
#include <fstream>
#include "LogNormal.h"

double LogNormal::calculate(double t_1, double t_2,
		double x, double y) 
{
	//boost::math::lognormal_distribution<double> 
	//	n(std::log(x), std::sqrt(t_2-t_1));
	//return boost::math::pdf(n, y);
	boost::math::normal_distribution<double> n(0.0, 1.0);	
	return boost::math::pdf(n, std::log(y / x) / std::sqrt(t_2 - t_1)) 
		/std::sqrt(t_2 - t_1);
}

double LogNormal::calculate(double t_1, double t_2,
		State x, State y)
{
		boost::math::normal_distribution<double> n(0.0, 1.0);	
		std::size_t size = x.size();
		double p = 1.0;
		for (std::size_t i = 0; i < size; ++i) {
			p *= boost::math::pdf(n, std::log(y[i] / x[i]) / std::sqrt(t_2 - t_1)) 
			/std::sqrt(t_2 - t_1);
		}
	return p;
}