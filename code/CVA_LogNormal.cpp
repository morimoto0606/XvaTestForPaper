#include <boost/random.hpp>
#include "PVfunction.h"
#include "StochasticMesh.h"
#include "Normal.h"
#include "LogNormal.h"
#include "CVA_LogNormal.h"
#include "LogNormalPaths.h"
#include "NormalPaths.h"
#include "Paths.h"
#include <fstream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "MaxPayoff.h"

using namespace boost;
using namespace std;


double calcCVALogNormal(const double iniVal, const double strike,
	const double maturity, const double subMaturity,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum,
	bool isOld)
{

	boost::shared_ptr<Paths<double>> calibPathPtr
		= boost::shared_ptr<Paths<double>>
		(new LogNormalPaths<double>(iniVal, timePartition, maturity, 1, 0.0)); 
	boost::shared_ptr<Paths<double>> montePathPtr
		= boost::shared_ptr<Paths<double>>
		(new LogNormalPaths<double>(iniVal, timePartition, maturity, 1, 0.0)); 

	boost::shared_ptr<TransKernel> trans
		= boost::shared_ptr<TransKernel>(new LogNormal());

	double cva = calcCVA(iniVal, strike, maturity, subMaturity,
	timePartition, calibNum,monteNum, calibPathPtr,
	montePathPtr, trans, isOld, 42, 42);

	return cva;
}

void testSMOpt(const double iniVal, const double strike,
	const double maturity, const std::size_t calibNum)
{
	typedef std::vector<double> PATH;
	typedef std::vector<PATH> PATHS;

	double dt = 0.01;
	boost::shared_ptr<Paths<double>> calibPathPtr
		= boost::shared_ptr<Paths<double>>
		(new LogNormalPaths<double>(iniVal, 10000, maturity, 1, 0.0)); 
	
	//Path 生成
	calibPathPtr->build(calibNum, 44);

	const boost::shared_ptr<PATHS> calibPaths = calibPathPtr->paths();


	//StochasticMeshOperatorを作る
	//boost::shared_ptr<TransKernel> trans
	//	= boost::shared_ptr<TransKernel>(new LogNormal());
	typedef boost::shared_ptr<StochasticMesh> StochasticMeshPtr;
	std::vector<StochasticMeshPtr> smVector;

	typedef boost::shared_ptr<Payoff<double>> PayoffPtr;
	
	std::vector<double> statesEnd;
	PATHS::const_iterator itCalib = calibPaths->begin();
	for (; itCalib!= calibPaths->end(); ++itCalib) {
		statesEnd.push_back(*(itCalib->end()-1));
	}

	//sm opt
	boost::shared_ptr<TransKernel> trans
		= boost::shared_ptr<TransKernel>(new LogNormal());
	boost::function<double (double)> f =
		boost::bind(&maxPayoff, _1, strike);
	PayoffPtr payoffPtr = 
		PayoffPtr(new Payoff<double>(f));
	for (std::size_t i = 0; i * dt < maturity; ++ i) {
		std::vector<double> states;
		itCalib = calibPaths->begin();
		for (; itCalib!= calibPaths->end(); ++itCalib) {
			states.push_back((*itCalib)[i]);
		}
		StochasticMeshPtr smPtr
			= StochasticMeshPtr(new StochasticMesh(trans,
			payoffPtr,
			i * dt, maturity, states, statesEnd));
		smPtr->buildQ();
		smVector.push_back(StochasticMeshPtr(smPtr));
	}
	std::vector<StochasticMeshPtr>::const_reverse_iterator smReviter
		= smVector.rbegin();
	for (int i = 1; i<=30; ++i) {
		for (int j=1; j*0.1 <= 5; ++j) {
			double iVal = smVector[smVector.size()-i]->contVal(j*0.1);
		}
	}
}

