#ifndef ABSTRACTRESULT_H
#define ABSTRACTRESULT_H
#include <iostream>

class AbstractResult
{
public:
	virtual AbstractResult* getResult()=0; //{std:: cout << "jestem AbstractResult" << std::endl;return new AbstractResult();}
	AbstractResult();
	virtual ~AbstractResult();
	int paramType;    

private:

};

#endif // ABSTRACTRESULT_H
