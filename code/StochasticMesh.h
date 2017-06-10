#ifndef StochasticMeshTest_h
#define StochasticMeshTest_h

#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "Transkernel.h"
#include "PayoffFunction.h"
#include <boost/array.hpp>


class StochasticMesh {
public:
	StochasticMesh(boost::shared_ptr<TransKernel> kernel, 
		boost::shared_ptr<Payoff<double>> payoff,
		double t_1, double t_2, 
		std::vector<double>& tmpPath, std::vector<double>& futPath)
		: _kernel(kernel), _payoff(payoff), _t1(t_1), _t2(t_2),
		_tmpPath(tmpPath), _futPath(futPath) {
			this->buildQ();
	}
	void buildQ();
	double contVal(double state);

private:
	StochasticMesh(const StochasticMesh&);
	boost::shared_ptr<TransKernel> _kernel;
	boost::shared_ptr<Payoff<double>> _payoff;
	double _t1;
	double _t2;
	std::vector<double> _tmpPath;
	std::vector<double> _futPath;
	std::vector<double> _q;
};

class StochasticMesh2F {
public:
	StochasticMesh2F(boost::shared_ptr<TransKernel> kernel, 
		boost::shared_ptr<Payoff<double>> payoff,
		double t_1, double t_2, 
		std::vector< boost::array<double,2> >& tmpPath, 
		std::vector< boost::array<double,2> >& futPath)
		: _kernel(kernel), _payoff(payoff), _t1(t_1), _t2(t_2),
		_tmpPath(tmpPath), _futPath(futPath) {
			this->buildQ();
	}
	void buildQ();
	double StochasticMesh2F::contVal(boost::array<double,2> state);

private:
	StochasticMesh2F(const StochasticMesh2F&);
	boost::shared_ptr<TransKernel> _kernel;
	boost::shared_ptr<Payoff<double>> _payoff;
	double _t1;
	double _t2;
	std::vector< boost::array<double,2> > _tmpPath;
	std::vector< boost::array<double,2> > _futPath;
	std::vector<double> _q;
};
#endif