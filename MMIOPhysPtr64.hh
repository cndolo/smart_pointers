#include <iostream>
template<class T>
class MMIOPhysPtr64 : public AbstractPhysPtr64<MMIOConfig, T> {

public:

	MMIOPhysPtr64() {
		std::cout<<"hello from MMIOPhysPtr64"<<std::endl;		
	}

};
