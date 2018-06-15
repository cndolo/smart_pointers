#include <iostream>
template<class T>
class ImagePhysPtr64 : public AbstractPhysPtr64<ImageConfig, T> {

public:

	ImagePhysPtr64() {
		std::cout<<"hello from ImagePhysPtr64"<<std::endl;		
	}

};
