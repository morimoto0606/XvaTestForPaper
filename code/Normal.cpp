#include <boost/math/distributions.hpp>
#include <fstream>
#include "Normal.h"

double Normal::calculate(double t_1, double t_2,
		double x, double y) 
{	
	boost::math::normal_distribution<double> n(0.0, _sigma * std::sqrt(t_2 - t_1));	
	return boost::math::pdf(n, (y-x)) ;
}

double Normal::calculate(double t_1, double t_2,
		State x, State y)
{
	boost::math::normal_distribution<double> n(0.0, _sigma);	
	std::size_t size = x.size();
	double p = boost::math::pdf(n, (y[0]-x[0])/std::sqrt(t_2 - t_1)) / std::sqrt(t_2 - t_1)
		* boost::math::pdf(n, (y[1]-x[1])/std::sqrt(t_2 - t_1)) / std::sqrt(t_2 - t_1);
	return p;
}