#include <iostream>

class ImagePhysPtr64 : public AbstractPhysPtr64<config64phys> {

public:

	ImagePhysPtr64() {
		std::cout<<"hello from ImagePhysPtr64"<<std::endl;		
	}

};
