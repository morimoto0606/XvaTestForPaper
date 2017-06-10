#ifndef LogNormalPaths_h
#define LogNormalPaths_h

#include <vector>
#include <boost/shared_ptr.hpp>
#include "Paths.h"
#include "halton.h"

template <typename T>
class LogNormalPaths : public Paths<T>
{
	typedef std::vector<T> PATH;
	typedef std::vector<PATH> PATHS;

public: 
	LogNormalPaths(const T& iniVal, std::size_t timePartition, double maturity,
		double sigma, double mu) 
		: Paths(iniVal, timePartition, maturity), _sigma(sigma), _mu(mu) {};

	virtual ~LogNormalPaths() {};

	virtual void build(std::size_t pathNum, long seed);
	
private:
	double _sigma;
	double _mu;

};

template <typename T>
void LogNormalPaths<T>::build(std::size_t pathNum, long seed)
{
	boost::mt19937 gen( static_cast<unsigned long>(seed));
	boost::normal_distribution<> dist(0.0, 1.0);

	double maturity = Paths<T>::_maturity;
	const double dt = _maturity / _timePartition;
	for (std::size_t i = 0; i < pathNum; ++i) {
		PATH bmPath;
		PATH onePath;
		bmPath.push_back(0.0);
		onePath.push_back(_iniVal);
		for (std::size_t j = 1; j <= _timePartition; ++j) {
			double t = j * dt;
			bmPath.push_back(*(bmPath.end()-1) + std::sqrt(dt) * dist(gen));
			double x = _iniVal * std::exp(_mu * t
				+ _sigma * (*(bmPath.end()-1)));
			onePath.push_back(x);
		}
		_paths->push_back(onePath);
	}
}

#endif