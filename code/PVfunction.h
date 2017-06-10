#ifndef CVA_h
#define CVA_h

#include <boost/shared_ptr.hpp>
#include "Paths.h"
#include "Transkernel.h"

double calcEuropeanMax2F(double iniVal1, double iniVal2, double strike,
		double maturity, const std::size_t timePartition, double sigma, 
		std::size_t monteNum);

double calcCVA(const double iniVal, const double strike,
	const double maturity, const double subMaturity,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum, 
	boost::shared_ptr<Paths<double>> calibPathPtr,
	boost::shared_ptr<Paths<double>> montePathPtr,
	boost::shared_ptr<TransKernel> trans, long type, long seed_calib, long seed_monte);

double calcCVA1time(const double iniVal, const double strike,
	const double maturity, const std::size_t observationNum,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum, 
	boost::shared_ptr<Paths<double>> calibPathPtr,
	boost::shared_ptr<Paths<double>> montePathPtr,
	boost::shared_ptr<TransKernel> trans, bool isOld, long seed_calib, long seed_monte);

double calcCVA2F(const double iniVal, const double strike,
	const double maturity, const double subMaturity,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum, 
	boost::shared_ptr<Paths<double>> calibPathPtr1,
	boost::shared_ptr<Paths<double>> montePathPtr1,
	boost::shared_ptr<Paths<double>> calibPathPtr2,
	boost::shared_ptr<Paths<double>> montePathPtr2,
	boost::shared_ptr<TransKernel> trans, bool isOld, long seed_calib, long seed_monte);

double calcCVA2F1Time(const double iniVal, const double strike,
	const double maturity, const std::size_t observationNm,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum, 
	boost::shared_ptr<Paths<double>> calibPathPtr1,
	boost::shared_ptr<Paths<double>> montePathPtr1,
	boost::shared_ptr<Paths<double>> calibPathPtr2,
	boost::shared_ptr<Paths<double>> montePathPtr2,
	boost::shared_ptr<TransKernel> trans, bool isOld, long seed_calib, long seed_monte);

double calcContVale2F(const double x, const double iniVal, const double strike,
	const double maturity, const std::size_t observationNum,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum, 
	boost::shared_ptr<Paths<double>> calibPathPtr1,
	boost::shared_ptr<Paths<double>> calibPathPtr2,
	boost::shared_ptr<TransKernel> trans, bool isOld, long seed_calib, long seed_monte);

#endif