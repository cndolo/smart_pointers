#include <iostream>

class KernelPhysPtr64 : public AbstractPhysPtr64<config64phys> {

public:

	KernelPhysPtr64() {
		std::cout <<"hello from KernelPhysPtr64"<<std::endl;
	}

};
