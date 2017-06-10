#include <boost/random.hpp>
#include "PVfunction.h"
#include "StochasticMesh.h"
#include "Normal.h"
#include "LogNormal.h"
#include "CVA_LogNormal.h"
#include "LogNormalPaths.h"
#include "NormalPaths.h"
#include "Paths.h"


using namespace boost;
using namespace std;

double calcCVANormal(const double iniVal, const double strike,
	const double maturity, const double subMaturity,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum,
	long type, long seed_calib, long seed_monte, double sigma)
{

	boost::shared_ptr<Paths<double>> calibPathPtr
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, sigma, 0.0)); 
	boost::shared_ptr<Paths<double>> montePathPtr
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, sigma, 0.0)); 

	boost::shared_ptr<TransKernel> trans
		= boost::shared_ptr<TransKernel>(new Normal(sigma));

	double cva = calcCVA(iniVal, strike, maturity, subMaturity,
	timePartition, calibNum,monteNum, calibPathPtr,
	montePathPtr, trans, type, seed_calib, seed_monte);

	return cva;
}

double calcCVANormal1time(const double iniVal, const double strike,
	const double maturity, const std::size_t observationNum,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum,
	bool isOld, long seed_calib, long seed_monte, double sigma)
{

	boost::shared_ptr<Paths<double>> calibPathPtr
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, 1.0, 0.0)); 
	boost::shared_ptr<Paths<double>> montePathPtr
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, 1.0, 0.0)); 

	boost::shared_ptr<TransKernel> trans
		= boost::shared_ptr<TransKernel>(new Normal(sigma));

	double cva = calcCVA1time(iniVal, strike, maturity, observationNum,
	timePartition, calibNum,monteNum, calibPathPtr,
	montePathPtr, trans, isOld, seed_calib, seed_monte);

	return cva;
}

double calcCVANormal2F(const double iniVal, const double strike,
	const double maturity, const double subMaturity,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum,
	bool isOld, long seed_calib, long seed_monte, double sigma)
{

	boost::shared_ptr<Paths<double>> calibPathPtr1
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, 1.0, 0.0)); 
	boost::shared_ptr<Paths<double>> montePathPtr1
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, 1.0, 0.0)); 
	
	boost::shared_ptr<Paths<double>> calibPathPtr2
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, 1.0, 0.0)); 
	boost::shared_ptr<Paths<double>> montePathPtr2
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, 1.0, 0.0)); 

	boost::shared_ptr<TransKernel> trans
		= boost::shared_ptr<TransKernel>(new Normal(sigma));

	double cva = calcCVA2F(iniVal, strike, maturity, subMaturity,
	timePartition, calibNum,monteNum, calibPathPtr1,
	montePathPtr1, calibPathPtr2, montePathPtr2, trans, isOld, seed_calib, seed_monte);
	
	return cva;
}

double calcCVANormal2F1time(const double iniVal, const double strike,
	const double maturity, const std::size_t observationNum,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum,
	bool isOld, long seed_calib, long seed_monte, double sigma)
{

	boost::shared_ptr<Paths<double>> calibPathPtr1
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, 1.0, 0.0)); 
	boost::shared_ptr<Paths<double>> montePathPtr1
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, 1.0, 0.0)); 
	
	boost::shared_ptr<Paths<double>> calibPathPtr2
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, 1.0, 0.0)); 
	boost::shared_ptr<Paths<double>> montePathPtr2
		= boost::shared_ptr<Paths<double>>
		(new NormalPaths<double>(iniVal, timePartition, maturity, 1.0, 0.0)); 

	boost::shared_ptr<TransKernel> trans
		= boost::shared_ptr<TransKernel>(new Normal(sigma));

	double cva = calcCVA2F1Time(iniVal, strike, maturity, observationNum,
	timePartition, calibNum,monteNum, calibPathPtr1,
	montePathPtr1, calibPathPtr2, montePathPtr2, trans, isOld, seed_calib, seed_monte);
	
	return cva;
}