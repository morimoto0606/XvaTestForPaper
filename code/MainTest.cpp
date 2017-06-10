
#include <iostream>
#include <boost/timer.hpp>
#include <boost/random.hpp>
#include "StochasticMesh.h"
#include "PVfunction.h"
#include "CVA_LogNormal.h"
#include "CVA_Normal.h"
#include "CVA_LogNormal_Analytic.h"
#include "LogNormalPaths.h"
#include "NormalPaths.h"
#include <boost/random.hpp>
#include "PayoffFunction.h"
#include <fstream>
#include <boost/math/constants/constants.hpp>

int main()
{
	//double result =  calcEuropeanMax2F(100, 100, 120,
	//	1.0, 100, 0.3, 10000);

	//std::cout << result << std::endl;
	boost::timer t; // タイマーの開始
//	std::cout << t.elapsed() << " sec" << std::endl;
//	const double ansNormal = 0.26596152;
//	const double ansNormalOneTime = 0.39894228040143;
//	const double ansLogNormal0
//		= CVA_LogNormal_Analytic(1.0, 1.0, 1000000, 0.0);
//	
//	double ansLogNormal[5];
//	for (std::size_t i = 0; i <= 1; ++i) {
//		ansLogNormal[i] = CVA_LogNormal_Analytic(1.0, 1.0 - 0.1 * i, 1000000, 1.0);
//		std::cout << "ans =" << ansLogNormal[i] << std::endl;
//	}
//	t.restart();
//
//	//for (std::size_t i = 0; i <= 3; ++i) {
//	//	t.restart();
//	//	double c1 = calcCVALogNormal(1.0, 1.0, 1.0, 1.0 - 0.1 * i, 100, 1000, 10000);
//	//	std::cout << " calib=" << 1-0.1*i << ',' <<	c1 - ansLogNormal[i] << ',' << t.elapsed() << "sec" << ',';
//	//	t.restart();
//	//	double c2 =  calcCVALogNormal(1.0, 1.0, 1.0, 1.0-0.1*i, 100, 1000, 10000, true);
//	//	std::cout << c2- ansLogNormal[i] << ',' << t.elapsed() <<  "sec" << std::endl;
//	//}
//
//	
//	//for (std::size_t i = 1; i <= 9; ++i) {
//	//	t.restart();
//	//	double c1 = calcCVALogNormal(1.0, 1.0, 1.0, 1.0, 100, 100*i, 10000);
//	//	std::cout << " calib=" << i << ',' <<	c1 - ansLogNormal[0] << ',' << t.elapsed() << "sec" << ',';
//	//	t.restart();
//	//	double c2 =  calcCVALogNormal(1.0, 1.0, 1.0, 1.0, 100, 100*i, 10000, true);
//	//	std::cout << c2- ansLogNormal[0] << ',' << t.elapsed() <<  "sec" << std::endl;
//	//}
//
//	for (int j = 1;j<10;++j) {
//		for (std::size_t i = 0; i <= 6; ++i) {
//			t.restart();
//			double c1 = calcCVALogNormal(1.0, 1.0, 1.0, 1.0 - 0.1 * i, 10 *j, 10, 10);
//			std::cout << " calib=" << 1-0.1*i << ',' <<	c1 - ansLogNormal[i] << ',' << t.elapsed() << "sec" << ',';
//			t.restart();
//			double c2 =  calcCVALogNormal(1.0, 1.0, 1.0, 1.0-0.1*i, 10 *j, 1000, 10000, true);
//			std::cout << c2- ansLogNormal[i] << ',' << t.elapsed() <<  "sec" << std::endl;
//		}
//	}
//
////	0 sec
////ans =0.767647
////ans =0.679948
////ans =0.594348
////ans =0.510966
////ans =0.429931
////ans =0.351389
////ans =0.275497
//// calib=1,-0.321377,9.407sec,-0.0668445,13.366sec
//// calib=0.9,-0.27928,0.001sec,-0.0656705,12.123sec
//// calib=0.8,-0.239281,0.002sec,-0.0586168,10.927sec
//// calib=0.7,-0.2015,0.001sec,-0.051413,9.549sec
//// calib=0.6,-0.172831,0.001sec,-0.0443665,8.299sec
//// calib=0.5,-0.136576,0.001sec,-0.0371278,6.965sec
//// calib=0.4,-0.104561,0.001sec,-0.0287419,6.082sec
//// calib=1,0.236986,0.004sec,-0.0239041,26.717sec
//// calib=0.9,0.202723,0.002sec,-0.0208458,24.324sec
//// calib=0.8,0.166361,0.003sec,
	std::ofstream ofs("C:\\Users\\MORIMOTO\\Documents\\研究\\検証Excel\\result.csv");
	ofs.precision(10);
	//for (size_t i = 1; i <=10; ++i) {
	//	for (std::size_t j = 1; j < 10; ++j) {
	//		double c3 = calcCVANormal(0.0, 0.0, 1.0, 1.0, 10 *i, 1, 10000*j, 2, 42, 42, 1);
	//		std::cout << i  << ',' << j << ',' << c3 << std::endl;
	//	}
	//}
	//double pi = boost::math::constants::pi<double>();
	//for (size_t k = 1; k <=10000; ++k) {	
	//	double dt = 1.0 / static_cast<double>(k);
	//	double sum = 0.0;
	//	double sum2 = 0.0;
	//	for (size_t i = 0; (i+1)* dt <=1.0; ++i) {
	//		sum += sqrt(i * dt / (2.0 * pi)) * dt;
	//	}
	//	ofs  << k << ',' << sum << std::endl;
	//	std::cout << sum << std::endl;
	//}
	for (std::size_t j = 0; j < 100; ++j) {
		size_t pathNum = 100;
		//double c3 = calcCVANormal(0.0, 0.0, 1.0, 1.0, 100, 1, 1000000, 2, 40, 40, 1);
		for (std::size_t i =0; i < 7; ++i) {
				//double c1 = calcCVANormal(0.0, 0.0, 1.0, 1.0, 100, pathNum, 100000, 0, 42+j, 42, 1);	
				double c2 = calcCVANormal(0.0, 0.0, 1.0, 1.0, 100, pathNum, 10000, 1,42+j, 42, 1);
				//double c3 = calcCVANormal(0.0, 0.0, 1.0, 1.0, 100, 0, 10000*i, 2,42+j, 42+j, 1);

				//double c2 = calcCVANormal1time(0.0, 0.0, 2.0, 1, 2, 100*i, 10000, false, 100000+j);
				//double c3 = calcCVANormal1time(0.0, 0.0, 2.0, 1, 2, 100*i, 100*i, true, 100000+ j);
				//double c4 = calcCVANormal1time(0.0, 0.0, 2.0, 1, 2, 100*i, 100*i, false, 100000+ j);
				////double c3 = calcCVANormal2F1time(0.0, 1.0, 2.0, 190, 200, 1000, 1, false, 100000+j);
				////double c4 = calcCVANormal2F1time(0.0, 1.0, 2.0, 100+i, 200, 1000, 10000, true, 100000+ j);
				//std::cout  << j << ',' << pathNum << ',' << c1<< ',' << c2  <<  ',' << c3 << std::endl;
				ofs  << i << ',' << j << ',' << pathNum <<  ','  << c2  <<  std::endl;
				std::cout << i << ',' << j << ',' << pathNum << ',' <<  c2  << std::endl;
				pathNum *= 2;
		}
	}
	
	//for (std::size_t j = 0; j < 100; ++j) {
	//	size_t pathNum = 100;
	//	double c3 = calcCVANormal(0.0, 0.0, 1.0, 1.0, 100, 1, 10000, 2, 40, 40, 1);
	//	for (std::size_t i =0; i < 6; ++i) {
	//			//double c1 = calcCVANormal1time(0.0, 0.0, 2.0, 1, 2, 100*i, 10000, true, 100000, 100000);
	//			//double c2 = calcCVANormal1time(0.0, 0.0, 2.0, 1, 2, 100*i, 10000, false, 100000, 100000);
	//			//double c1 = calcCVANormal(0.0, 0.0, 1.0, 1.0, 3, pathNum, pathNum, true, 100000+j, 100000+j);
	//			double c1 = calcCVANormal(0.0, 0.0, 1.0, 1.0, 100, pathNum, 10000, 0, 42+j, 40, 1);	
	//			double c2 = calcCVANormal(0.0, 0.0, 1.0, 1.0, 100, pathNum, pathNum, 1, 42+j, 42+j, 1);

	//			//double c2 = calcCVANormal1time(0.0, 0.0, 2.0, 1, 2, 100*i, 10000, false, 100000+j);
	//			//double c3 = calcCVANormal1time(0.0, 0.0, 2.0, 1, 2, 100*i, 100*i, true, 100000+ j);
	//			//double c4 = calcCVANormal1time(0.0, 0.0, 2.0, 1, 2, 100*i, 100*i, false, 100000+ j);
	//			////double c3 = calcCVANormal2F1time(0.0, 1.0, 2.0, 190, 200, 1000, 1, false, 100000+j);
	//			////double c4 = calcCVANormal2F1time(0.0, 1.0, 2.0, 100+i, 200, 1000, 10000, true, 100000+ j);
	//			std::cout  << j << ',' << pathNum << ',' << c1<< ',' << c2  <<  ',' << c3 << std::endl;
	//			ofs  << j << ',' << pathNum <<  ','  << c1 << ',' << c2  <<  ',' << c3 << std::endl;
	//			pathNum *= 2;
	//	}
	//}
	std::cout << "Enter the Number to finish the program";
	int num;
	std::cin >> num;
	return 0;
}