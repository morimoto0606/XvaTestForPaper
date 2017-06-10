#ifndef Transkernel_h 
#define Transkernel_h 

#include <iostream>
#include <boost/array.hpp>

typedef boost::array<double,2> State;

class TransKernel {
public:
	TransKernel(){}
	virtual ~TransKernel(){}

	virtual double calculate(double t_1, double t_2,
		double x, double y) = 0;
	virtual double calculate(double t_1, double t_2,
		 State x, State y) =0;
private:
};

#endif