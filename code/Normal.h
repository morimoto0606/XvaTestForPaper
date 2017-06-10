#ifndef Normal_h 
#define Normal_h

#include "Transkernel.h"

class Normal: public TransKernel
{
public:
	Normal(double sigma) : _sigma(sigma){}
	virtual double calculate(double t_1, double t_2,
		double x, double y);
	virtual double calculate(double t_1, double t_2,
		State x, State y);

private:
	double _sigma;
};

#endif