#ifndef ExpNormal_h 
#define ExpNormal_h

#include "Transkernel.h"

class LogNormal: public TransKernel
{
public:
	LogNormal(){}
	~LogNormal(){}
	
	virtual double calculate(double t_1, double t_2,
		double x, double y);
	virtual double calculate(double t_1, double t_2,
		State x, State y);

private:
};

#endif