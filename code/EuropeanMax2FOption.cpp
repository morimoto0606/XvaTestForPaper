#include "EuropeanMax2FOption.h"
#include "Paths.h"
#include <algorithm>

typedef std::vector<std::vector<double>> Path;

double EuropeanMaxOption2F::calculate()
{
	_pathptr1->build(_monteNum, 100000);
	_pathptr2->build(_monteNum, 200000);

	const boost::shared_ptr<Path> paths1 = _pathptr1->paths();
	const boost::shared_ptr<Path> paths2 = _pathptr2->paths();

	Path::const_iterator it1 = paths1->begin();
	Path::const_iterator it2 = paths2->begin();

	std::vector<std::vector<double>> statesEnd;
	for (; it1!= paths1->end(); ++it1) {
		std::vector<double> stateVal;
		stateVal.push_back( *(it1->end()-1));
		stateVal.push_back( *(it2->end()-1));
		statesEnd.push_back(stateVal);
	}
	std::vector<double> result(statesEnd.size());
	Max2Ffunction f(_strike);
	std::transform(statesEnd.begin(), statesEnd.end(), result.begin(), f);

	std::vector<double>::const_iterator  it = result.begin();

	double sum = 0.0;
	for (; it != result.end(); ++it) {
		sum += *it;
	}
	return sum / statesEnd.size();
}
