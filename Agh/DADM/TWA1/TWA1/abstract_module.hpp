#ifndef _modules_abstract_module_hpp_
#define _modules_abstract_module_hpp_

#include "module.hpp"
#include "abstract_output.hpp"

#include <map>
#include <stdexcept>

using namespace std;

namespace Modules {

class IAbstractModule {

public:
	virtual const AbstractOutput* run(const map<Module, const AbstractOutput*>& inputs) const = 0;
	virtual ~IAbstractModule() {}
};

template<class ParametersClass, class OutputClass>
class AbstractModule : public IAbstractModule {

public:
	class InvalidOutputs : public runtime_error {
	public:
		explicit InvalidOutputs(const string& what_arg) : runtime_error(what_arg) {}
	};

	AbstractModule(const ParametersClass& parameters) : params(parameters) {}

	const ParametersClass& getParameters() {
		return params;
	}

//	virtual OutputClass* run(map<Module, AbstractOutput const*> inputs) const = 0;
	virtual ~AbstractModule() {}

protected:
	template <class InputClass>
	const InputClass* getOutput(Module module, const map<Module, const AbstractOutput*>& inputs) const throw(InvalidOutputs) {
		std::map<Module, const AbstractOutput*>::const_iterator it = inputs.find(RAW_INPUT);
		if (it == inputs.end())
			throw InvalidOutputs("Invalid outputs passed");
		return dynamic_cast<const InputClass*>(it->second);
	}

private:
	const ParametersClass& params;

};

}

#endif
