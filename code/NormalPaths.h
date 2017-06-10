#ifndef NormalPaths_h
#define NormalPaths_h

#include <vector>
#include <boost/shared_ptr.hpp>
#include "Paths.h"

template <typename T>
class NormalPaths : public Paths<T>
{
	typedef std::vector<T> PATH;
	typedef std::vector<PATH> PATHS;

public: 
	NormalPaths(const T& iniVal, std::size_t timePartition, double maturity,
		double sigma, double mu) 
		: Paths(iniVal, timePartition, maturity), _sigma(sigma), _mu(mu) {};

	virtual ~NormalPaths() {};

	virtual void build(std::size_t pathNum, long seed);
	
private:
	double _sigma;
	double _mu;

};

template <typename T>
void NormalPaths<T>::build(std::size_t pathNum, long seed)
{
	double maturity = Paths<T>::_maturity;
	const double dt = _maturity / _timePartition;
	
	boost::mt19937 gen( static_cast<unsigned long>(seed));
	boost::normal_distribution<> dist(0.0, _sigma);
	//generate path
	for (std::size_t i = 0; i < pathNum; ++i) {
		PATH onePath;
		onePath.push_back(_iniVal);
		//generate path by term1
		for (std::size_t j = 1; j <= _timePartition; ++j) {
			onePath.push_back(*(onePath.end()-1) + _sigma * 
				std::sqrt(dt) * dist(gen));
		}
		_paths->push_back(onePath);
	}
}

#endif