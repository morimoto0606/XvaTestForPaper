#ifndef Payoff_h
#define Payoff_h

#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>

template <typename T>
class Payoff {
public:
	Payoff(boost::function<double (T)> f) 
		: f_(f) {}
	virtual ~Payoff() {}

	double evaluate(const T& x) {
		return f_(x);
	}
private:
	boost::function<double (T)> f_;
};


#endif