#include <iostream>
template<class T>
class KernelPhysPtr64 : public AbstractPhysPtr64<KernelConfig, T> {

public:

	KernelPhysPtr64() {
		std::cout<<"hello from KernelPhysPtr64"<<std::endl;		
	}

};
