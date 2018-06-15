#include <iostream>
template<class T>
class KernelPhysPtr32 : public AbstractPhysPtr32<KernelConfig, T> {

public:

	KernelPhysPtr32() {
		std::cout<<"hello from KernelPhysPtr32"<<std::endl;		
	}

};

