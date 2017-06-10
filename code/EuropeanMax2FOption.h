#ifndef EuropeanMax2FOption_h
#define EuropeanMax2FOption_h

#include <boost/shared_ptr.hpp>
#include "Paths.h"
#include "LogNormalPaths.h"
#include <functional>
#include <vector>

class Max2Ffunction : public std::unary_function<std::vector<double>, double>
{
public:
	Max2Ffunction(double strike) : 
	  _strike(strike) {}
private:
	double _strike;
public:
	double operator()(const std::vector<double>& und)
	{
		return std::max(
			std::max(und[0], und[1]) - _strike, 0.0);
	}
};

class EuropeanMaxOption2F
{
public :
	EuropeanMaxOption2F(double iniVal1, double iniVal2, double strike,
		double maturity, const std::size_t timePartition, double sigma,
		const std::size_t monteNum) : _strike(strike), _monteNum(monteNum) 
		{
		_pathptr1 = boost::shared_ptr<Paths<double>>
			(new LogNormalPaths<double>(iniVal1, timePartition, maturity, sigma, 0.0)); 
		_pathptr2 = boost::shared_ptr<Paths<double>>
			(new LogNormalPaths<double>(iniVal2, timePartition, maturity, sigma, 0.0)); 
	}
	double	calculate();

private : 
	double _strike;
	std::size_t _monteNum;
	boost::shared_ptr<Paths<double>> _pathptr1;
	boost::shared_ptr<Paths<double>> _pathptr2;
};

#endif