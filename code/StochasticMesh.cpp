#include "StochasticMesh.h"
#include <boost/math/distributions.hpp>
#include <fstream>

using namespace std;

void StochasticMesh::buildQ()
{
	std::vector<double>::const_iterator itFut
		= _futPath.begin();
	double c = 0.0;
	for (; itFut != _futPath.end(); ++itFut) {
		double q = 0.0;
		std::vector<double>::const_iterator itTmp 
			= _tmpPath.begin();
		for (; itTmp != _tmpPath.end(); ++itTmp) {
			q +=  _kernel->calculate(_t1, _t2, *itTmp, *itFut);
 		}
		_q.push_back(q);
	}
}

void StochasticMesh2F::buildQ()
{
	std::vector< boost::array<double,2> >::const_iterator itFut
		= _futPath.begin();
	double c = 0.0;
	for (; itFut != _futPath.end(); ++itFut) {
		double q = 0.0;
		std::vector< boost::array<double,2> >::const_iterator itTmp 
			= _tmpPath.begin();
		for (; itTmp != _tmpPath.end(); ++itTmp) {
			q +=  _kernel->calculate(_t1, _t2, *itTmp, *itFut);

 		}
		_q.push_back(q);
	}
}
double StochasticMesh::contVal(double state)
{
	std::vector<double>::const_iterator itFut
		= _futPath.begin();
	std::vector<double>::const_iterator itQ
		= _q.begin();
	double c = 0.0;
	for (; itFut != _futPath.end(); ++itFut, ++itQ) {
		std::vector<double>::const_iterator itTmp 
			= _tmpPath.begin();
		c += _payoff->evaluate(*itFut) 
			* _kernel->calculate(_t1, _t2, state, *itFut) / *itQ; 
 	}
	return c;
}

double StochasticMesh2F::contVal(boost::array<double,2> state)
{
	std::vector< boost::array<double,2>>::const_iterator itFut
		= _futPath.begin();
	std::vector<double>::const_iterator itQ
		= _q.begin();
	double c = 0.0;
	for (; itFut != _futPath.end(); ++itFut, ++itQ) {
		std::vector< boost::array<double,2>>::const_iterator itTmp 
			= _tmpPath.begin();
		c += _payoff->evaluate((*itFut)[0]) 
			* _kernel->calculate(_t1, _t2, state, *itFut) / *itQ; 
 	}
	return c;
}