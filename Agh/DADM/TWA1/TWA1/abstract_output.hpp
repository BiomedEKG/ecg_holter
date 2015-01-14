#ifndef _modules_abstract_output_hpp_
#define _modules_abstract_output_hpp_

#include <ctime>

namespace Modules {

class AbstractOutput {
public:
	AbstractOutput(const std::clock_t timeElapsed = 0)
		: TimeElapsed(timeElapsed) {}

	virtual ~AbstractOutput() {}
	const std::clock_t TimeElapsed;
};

}

#endif
