#include <iostream>

class KernelPhysPtr32 : public AbstractPhysPtr32<config32phys> {

public:

	KernelPhysPtr32() {
		std::cout <<"hello from KernelPhysPtr32"<<std::endl;
	}

};
