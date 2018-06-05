#include <iostream>

class ImagePhysPtr32 : public AbstractPhysPtr32<config32phys> {

public:

	ImagePhysPtr32() {
		std::cout<<"hello from ImagePhysPtr32"<<std::endl;		
	}

};
