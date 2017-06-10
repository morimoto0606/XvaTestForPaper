#ifndef Path_h
#define Path_h

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/random.hpp>

template <typename T>
class Paths
{
	typedef std::vector<T> PATH;
	typedef std::vector<PATH> PATHS;

public: 
	Paths(const T& iniVal, std::size_t timePartition, double maturity) 
		: _iniVal(iniVal), _timePartition(timePartition), _maturity(maturity) {
			_paths = boost::shared_ptr<PATHS>(new PATHS);
	}
	Paths(const Paths&  paths) {
		_paths = boost::shared_ptr<PATHS>(new PATHS);
		*_paths = *(paths._paths);
	}
	virtual ~Paths() {};

	virtual void build(std::size_t pathNum, long seed) = 0;

	T val(int i, double t) const;
	PATH path(int i) const {
		retrun (*_paths)[i];
	}
	boost::shared_ptr<PATHS> paths() {
		return _paths;
	}

protected:
	T _iniVal;
	std::size_t _timePartition;
	double _maturity;
	boost::shared_ptr<PATHS> _paths;	
};

template <typename T>
T Paths<T>::val(int i, double t) const 
{
	if (t >= _maturity) {
		return *(((*_paths)[i]).end() - 1);
	}
	else {
		double dt = _maturity / _timePartition;
		int pre = static_cast<int>(std::floor(t / dt));
		int fw = static_cast<int>(std::ceil(t / dt));
		double t_pre = pre * dt;
		double t_fw = fw * dt;

		double val = (t_pre == t_fw) ?  ((*_paths)[i])[pre]
			:((t - t_pre) * ((*_paths)[i])[fw]
			+ (t_fw - t) * ((*_paths)[i])[pre]) / dt;
		return val;
	}
}

#endif