#include <iostream>
template<class T>
class MMIOPhysPtr32 : public AbstractPhysPtr32<MMIOConfig, T> {

public:

	MMIOPhysPtr32() {
		std::cout<<"hello from MMIOPhysPtr32"<<std::endl;		
	}

};
