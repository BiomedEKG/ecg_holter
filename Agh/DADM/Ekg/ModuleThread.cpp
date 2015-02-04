//#include "ModuleThread.h"
//#include <iostream>
//ModuleThread::ModuleThread(void)
//{
//	module = NULL;
//	if(threadPool < 0 || threadPool > 3) {
//		threadPool = 0;
//	}else {
//		threadPool++;
//	}
//}
//
//
//void ModuleThread::run(){
//	
//	if(module != NULL) {
//		ResultKeeper* rk = &ResultKeeper::getInstance(); 	
//		//rk->setParam(module->compute(rk));
//
//	} else {
//		std::cout << "ModuleThread Error: Module pointer is NULL" << endl;
//	}
//}
//
//ModuleThread::~ModuleThread(void);
//{
//	threadPool--;
//}
