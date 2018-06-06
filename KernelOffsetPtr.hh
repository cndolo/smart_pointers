#include <iostream>

class KernelOffsetPtr : public AbstractOffsetPtr<configOffset> {

public:

	KernelOffsetPtr() {
		std::cout<<"hello from KernelOffsetPtr"<<std::endl;		
	}

};

