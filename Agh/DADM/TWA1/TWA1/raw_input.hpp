#ifndef _modules_raw_input_hpp_
#define _modules_raw_input_hpp_

#include "abstract_output.hpp"
#include <vector>

namespace Modules {

class RawInput : public AbstractOutput {
public:
	RawInput(vector<double> _data) : data(_data) {};
	std::vector<double> data;
};

}

#endif
