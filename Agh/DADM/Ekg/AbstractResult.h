#ifndef ABSTRACTRESULT_H
#define ABSTRACTRESULT_H


class AbstractResult
{
    public:
		virtual AbstractResult* getResult(){return new AbstractResult();};
        AbstractResult();
        virtual ~AbstractResult();
		int paramType;    
protected:

private:
		
};

#endif // ABSTRACTRESULT_H
