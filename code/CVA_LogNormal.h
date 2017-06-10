#ifndef CVA_LogNormal_h
#define CVA_LogNormal_h

#include <boost/shared_ptr.hpp>
#include "Paths.h"

double calcCVALogNormal(const double iniVal, const double strike,
	const double maturity, const double subMaturity,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum,
	bool isOld = false);

void testSMOpt(const double iniVal, const double strike,
	const double maturity, const std::size_t calibNum);


#endif