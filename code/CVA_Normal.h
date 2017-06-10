#ifndef CVA_Normal_h
#define CVA_Normal_h

#include <boost/shared_ptr.hpp>
#include "Paths.h"

double calcCVANormal(const double iniVal, const double strike,
	const double maturity, const double subMaturity,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum,
	long type, long seed_calib, long seed_monte, double sigma);

double calcCVANormal1time(const double iniVal, const double strike,
	const double maturity, const std::size_t observationNum,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum,
	bool isOld, long seed_calib, long seed_monte, double sigma);

double calcCVANormal2F(const double iniVal, const double strike,
	const double maturity, const double subMaturity,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum,
	bool isOld, long seed_calib, long seed_monte, double sigma);

double calcCVANormal2F1time(const double iniVal, const double strike,
	const double maturity, const std::size_t observationNum,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum,
	bool isOld, long seed_calib, long seed_monte, double sigma);
#endif