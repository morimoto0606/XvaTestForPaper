#include <boost/random.hpp>
#include "PVfunction.h"
#include "StochasticMesh.h"
#include "Normal.h"
#include "LogNormal.h"
#include "CVA_LogNormal.h"
#include "LogNormalPaths.h"
#include "NormalPaths.h"
#include "Paths.h"
#include "PayoffFunction.h"
#include <fstream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "MaxPayoff.h"
#include <boost/array.hpp>
#include "QuadraticPayoff.h"
#include "EuropeanMax2FOption.h"

double calcEuropeanMax2F(double iniVal1, double iniVal2, double strike,
		double maturity, const std::size_t timePartition, double sigma, std::size_t monteNum)
{
	EuropeanMaxOption2F opt(iniVal1, iniVal2, strike, maturity, timePartition, sigma, monteNum);
	return opt.calculate();
}

double calcCVA(const double iniVal, const double strike,
	const double maturity, const double subMaturity,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum, 
	boost::shared_ptr<Paths<double>> calibPathPtr,
	boost::shared_ptr<Paths<double>> montePathPtr,
	boost::shared_ptr<TransKernel> trans, long type, long seed_calib, long seed_monte)
{
	typedef std::vector<double> Path;
	typedef std::vector<Path> Paths;

	double dt = maturity / timePartition;

	//Path 生成
	calibPathPtr->build(calibNum, seed_calib);
	montePathPtr->build(monteNum, seed_monte);

	const boost::shared_ptr<Paths> calibPaths = calibPathPtr->paths();
	const boost::shared_ptr<Paths> montePaths = montePathPtr->paths();

	//StochasticMeshOperatorを作る
	//boost::shared_ptr<TransKernel> trans
	//	= boost::shared_ptr<TransKernel>(new LogNormal());
	typedef boost::shared_ptr<StochasticMesh> StochasticMeshPtr;
	std::vector<StochasticMeshPtr> smVector;

	typedef boost::shared_ptr<Payoff<double>> PayoffPtr;
	
	std::vector<double> statesEnd;
	Paths::const_iterator itCalib = calibPaths->begin();
	for (; itCalib!= calibPaths->end(); ++itCalib) {
		statesEnd.push_back(*(itCalib->end()-1));
	}
	//states < end
	boost::function<double (double)> f =
		boost::bind(maxPayoff, _1, strike);
	PayoffPtr payoffPtr = 
		PayoffPtr(new Payoff<double>(f));
	for (std::size_t i = 0; (i + 1) * dt <= subMaturity; ++ i) {
		std::vector<double> states;
		itCalib = calibPaths->begin();
		for (; itCalib!= calibPaths->end(); ++itCalib) {
			states.push_back((*itCalib)[i]);
		}
		StochasticMeshPtr smPtr
			= StochasticMeshPtr(new StochasticMesh(trans,
			payoffPtr,
			i * dt, maturity, states, statesEnd));
		smVector.push_back(StochasticMeshPtr(smPtr));
	}
	
	//Montepathを走らせる
	double cva = 0.0;
	Paths::const_iterator itMonte = montePaths->begin();

	for (; itMonte != montePaths->end(); ++itMonte) {
		double payoff =  payoffPtr->evaluate(*(itMonte->end()-1));
		for (std::size_t i = 0; (i + 1) * dt <= maturity; ++ i) {
			double x = (*itMonte)[i];
			double iVal = f(x);
			if ((i+1) * dt <= subMaturity) {
				iVal = smVector[i]->contVal(x);
			}

			if (type == 0) {
				cva += iVal > 0.0 ? payoff * dt  : 0.0;
			}
			else if (type == 1){
				cva += iVal > 0.0 ? iVal * dt : 0.0;
			}
			else if (type == 2) {
				cva += x > 0.0 ? x * dt : 0.0;
			}
		}
	}
	return cva / montePaths->size();
}

double calcCVA1time(const double iniVal, const double strike,
	const double maturity, const std::size_t observationNum,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum, 
	boost::shared_ptr<Paths<double>> calibPathPtr,
	boost::shared_ptr<Paths<double>> montePathPtr,
	boost::shared_ptr<TransKernel> trans, bool isOld, long seed_calib, long seed_monte)
{
	typedef std::vector<double> Path;
	typedef std::vector<Path> Paths;

	double dt = maturity / timePartition;

	//Path 生成
	calibPathPtr->build(calibNum, seed_calib);
	montePathPtr->build(monteNum, seed_monte);

	const boost::shared_ptr<Paths> calibPaths = calibPathPtr->paths();
	const boost::shared_ptr<Paths> montePaths = montePathPtr->paths();

	//StochasticMeshOperatorを作る
	//boost::shared_ptr<TransKernel> trans
	//	= boost::shared_ptr<TransKernel>(new LogNormal());
	typedef boost::shared_ptr<StochasticMesh> StochasticMeshPtr;
	std::vector<StochasticMeshPtr> smVector;

	typedef boost::shared_ptr<Payoff<double>> PayoffPtr;
	
	std::vector<double> statesEnd;
	Paths::const_iterator itCalib = calibPaths->begin();
	for (; itCalib!= calibPaths->end(); ++itCalib) {
		statesEnd.push_back(*(itCalib->end()-1));
	}
	//states < end
	boost::function<double (double)> f =
		boost::bind(maxPayoff, _1, strike);
	PayoffPtr payoffPtr = 
		PayoffPtr(new Payoff<double>(f));

		std::vector<double> states;
		itCalib = calibPaths->begin();
		for (; itCalib!= calibPaths->end(); ++itCalib) {
			states.push_back((*itCalib)[observationNum]);
		}
		StochasticMeshPtr smPtr
			= StochasticMeshPtr(new StochasticMesh(trans,
			payoffPtr,
			observationNum * dt, maturity, states, statesEnd));
		smVector.push_back(StochasticMeshPtr(smPtr));

		//double iVal =0.0;
		//for (int i = -50; i <= 50; ++i) {
		//	double d = (double) i / 10.0;
		//	 iVal = smVector[0]->contVal(d);
		//	std::cout << observationNum << ',' << d << ',' << iVal << std::endl;
		//}
		//return 0;
	//Montepathを走らせる
	double cva = 0.0;
	Paths::const_iterator itMonte = montePaths->begin();

	for (; itMonte != montePaths->end(); ++itMonte) {
		double payoff =  payoffPtr->evaluate(*(itMonte->end()-1));
		double iVal = smVector[0]->contVal((*itMonte)[observationNum]);
		if (!isOld) {
			cva += iVal > 0.0 ? payoff  : 0.0;
		}
		else {
			cva += iVal > 0.0 ? iVal  : 0.0;
		}
	}
	return cva / montePaths->size();
}

double calcCVA2F(const double iniVal, const double strike,
	const double maturity, const double subMaturity,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum, 
	boost::shared_ptr<Paths<double>> calibPathPtr1,
	boost::shared_ptr<Paths<double>> montePathPtr1,
	boost::shared_ptr<Paths<double>> calibPathPtr2,
	boost::shared_ptr<Paths<double>> montePathPtr2,
	boost::shared_ptr<TransKernel> trans, bool isOld, long seed_calib, long seed_monte)
{
	typedef std::vector<double> Path;
	typedef std::vector<Path> Paths;

	double dt = maturity / timePartition;

	//Path 生成
	calibPathPtr1->build(calibNum, seed_calib);
	montePathPtr1->build(monteNum, seed_monte);
	calibPathPtr2->build(calibNum, seed_calib+1);
	montePathPtr2->build(monteNum, seed_monte+1);

	const boost::shared_ptr<Paths> calibPaths1 = calibPathPtr1->paths();
	const boost::shared_ptr<Paths> montePaths1 = montePathPtr1->paths();
	const boost::shared_ptr<Paths> calibPaths2 = calibPathPtr2->paths();
	const boost::shared_ptr<Paths> montePaths2 = montePathPtr2->paths();

	//StochasticMeshOperatorを作る
	//boost::shared_ptr<TransKernel> trans
	//	= boost::shared_ptr<TransKernel>(new LogNormal());
	typedef boost::shared_ptr<StochasticMesh2F> StochasticMeshPtr;
	std::vector<StochasticMeshPtr> smVector;

	typedef boost::shared_ptr<Payoff<double>> PayoffPtr;
	std::vector< boost::array<double,2> > statesEnd;
	Paths::const_iterator itCalib1 = calibPaths1->begin();
	Paths::const_iterator itCalib2 = calibPaths2->begin();
	for (; itCalib1!= calibPaths1->end(); ++itCalib1, ++itCalib2) {
		boost::array<double,2> state = {*(itCalib1->end()-1),*(itCalib2->end()-1)};
		statesEnd.push_back(state);
	}
	//states < end
	boost::function<double (double)> f =
		boost::bind(maxPayoff, _1, strike);
	PayoffPtr payoffPtr = 
		PayoffPtr(new Payoff<double>(f));
	for (std::size_t i = 0; i * dt < subMaturity; ++ i) {
		std::vector< boost::array<double,2>> states;
		itCalib1 = calibPaths1->begin();
		itCalib2 = calibPaths2->begin();
		for (; itCalib1!= calibPaths1->end(); ++itCalib1, ++itCalib2) {
			boost::array<double,2> state = {(*itCalib1)[i],(*itCalib2)[i]};
			states.push_back(state);
		}
		StochasticMeshPtr smPtr
			= StochasticMeshPtr(new StochasticMesh2F(trans,
			payoffPtr, i * dt, maturity, states, statesEnd));
		smVector.push_back(StochasticMeshPtr(smPtr));
	}
	
	//Montepathを走らせる
	double cva = 0.0;
	Paths::const_iterator itMonte1 = montePaths1->begin();
	Paths::const_iterator itMonte2 = montePaths2->begin();
	
	for (; itMonte1 != montePaths1->end(); ++itMonte1, ++itMonte2) {
		double payoff =  payoffPtr->evaluate(*(itMonte1->end()-1));
		//for (std::size_t i = 0; i * dt < subMaturity; ++ i) {
		//	boost::array<double, 2> state = {(*itMonte1)[i],(*itMonte2)[i]};
		//	double iVal = smVector[i]->contVal(state);

		//	if (!isOld) {
		//		cva += iVal > 0.0 ? payoff * dt : 0.0;
		//	}
		//	else {
		//		cva += iVal > 0.0 ? iVal * dt : 0.0;
		//	}
		//}
		boost::array<double, 2> state = {(*itMonte1)[1],(*itMonte2)[1]};
		double iVal = smVector[1]->contVal(state);
		if (!isOld) {
			cva += iVal > 0.0 ? payoff  : 0.0;
		}
		else {
			cva += iVal > 0.0 ? iVal  : 0.0;
		}
	}
	return cva / montePaths1->size();
}

double calcCVA2F1Time(const double iniVal, const double strike,
	const double maturity, const std::size_t observationNum,
	const std::size_t timePartition, 
	const std::size_t calibNum, const std::size_t monteNum, 
	boost::shared_ptr<Paths<double>> calibPathPtr1,
	boost::shared_ptr<Paths<double>> montePathPtr1,
	boost::shared_ptr<Paths<double>> calibPathPtr2,
	boost::shared_ptr<Paths<double>> montePathPtr2,
	boost::shared_ptr<TransKernel> trans, bool isOld, long seed_calib, long seed_monte)
{
	typedef std::vector<double> Path;
	typedef std::vector<Path> Paths;

	double dt = maturity / timePartition;

	//Path 生成
	calibPathPtr1->build(calibNum, seed_calib);
	montePathPtr1->build(monteNum, seed_monte);
	calibPathPtr2->build(calibNum, seed_calib+1);
	montePathPtr2->build(monteNum, seed_monte+1);

	const boost::shared_ptr<Paths> calibPaths1 = calibPathPtr1->paths();
	const boost::shared_ptr<Paths> montePaths1 = montePathPtr1->paths();
	const boost::shared_ptr<Paths> calibPaths2 = calibPathPtr2->paths();
	const boost::shared_ptr<Paths> montePaths2 = montePathPtr2->paths();

	//StochasticMeshOperatorを作る
	//boost::shared_ptr<TransKernel> trans
	//	= boost::shared_ptr<TransKernel>(new LogNormal());
	typedef boost::shared_ptr<StochasticMesh2F> StochasticMeshPtr;
	std::vector<StochasticMeshPtr> smVector;

	typedef boost::shared_ptr<Payoff<double>> PayoffPtr;
	std::vector< boost::array<double,2> > statesEnd;
	Paths::const_iterator itCalib1 = calibPaths1->begin();
	Paths::const_iterator itCalib2 = calibPaths2->begin();
	for (; itCalib1!= calibPaths1->end(); ++itCalib1, ++itCalib2) {
		boost::array<double,2> state = {*(itCalib1->end()-1),*(itCalib2->end()-1)};
		statesEnd.push_back(state);
	}
	//states < end
	boost::function<double (double)> f =
		boost::bind(quadraticPayoff, _1, strike, 2.0);
	PayoffPtr payoffPtr = 
		PayoffPtr(new Payoff<double>(f));

	std::vector< boost::array<double,2>> states;
	itCalib1 = calibPaths1->begin();
	itCalib2 = calibPaths2->begin();
	for (; itCalib1!= calibPaths1->end(); ++itCalib1, ++itCalib2) {
		boost::array<double,2> state
			= {(*itCalib1)[observationNum],(*itCalib2)[observationNum]};
		states.push_back(state);
	}
	StochasticMeshPtr smPtr
		= StochasticMeshPtr(new StochasticMesh2F(trans,
		payoffPtr, observationNum * dt, maturity, states, statesEnd));
	smVector.push_back(StochasticMeshPtr(smPtr));
	
	double iVal =0.0;
	for (int i = -50; i <= 50; ++i) {
		double d = (double) i / 10.0;
		boost::array<double, 2> state
			= {d,0.0};
			iVal = smVector[0]->contVal(state);
		std::cout << observationNum << ',' << d << ',' << iVal << std::endl;
	}
	return 0;
	//Montepathを走らせる
	double cva = 0.0;
	Paths::const_iterator itMonte1 = montePaths1->begin();
	Paths::const_iterator itMonte2 = montePaths2->begin();
	
	for (; itMonte1 != montePaths1->end(); ++itMonte1, ++itMonte2) {
		double payoff =  payoffPtr->evaluate(*(itMonte1->end()-1));
		boost::array<double, 2> state
			= {(*itMonte1)[observationNum],(*itMonte2)[observationNum]};
		double iVal = smVector[0]->contVal(state);
		if (!isOld) {
			cva += iVal > 0.0 ? payoff  : 0.0;
		}
		else {
			cva += iVal > 0.0 ? iVal  : 0.0;
		}
	}
	return cva / montePaths1->size();
}