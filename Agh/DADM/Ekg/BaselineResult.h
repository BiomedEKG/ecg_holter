#include <AbstractResult.h>
#include <vector>


class BaselineResult : public AbstractResult
{
 public:
	 BaselineResult();
     ~BaselineResult();
	 std::vector <double> filteredSignal;
 protected:
 private:
};
