#include <iostream>
template<class T>
class ImagePhysPtr32 : public AbstractPhysPtr32<ImageConfig, T> {

public:

	ImagePhysPtr32() {
		std::cout<<"hello from ImagePhysPtr32"<<std::endl;		
	}

};
