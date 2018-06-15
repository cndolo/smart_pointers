#include <iostream>
template <class T>
class KernelOffsetPtr : public AbstractOffsetPtr<KernelConfig, T> {

public:

		KernelOffsetPtr() {
		std::cout<<"hello from KernelOffsetPtr"<<std::endl;		
	}

};

