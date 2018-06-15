#include <iostream>
template <class T>
class ImageOffsetPtr : public AbstractOffsetPtr<ImageConfig, T> {

public:

		ImageOffsetPtr() {
		std::cout<<"hello from ImageOffsetPtr"<<std::endl;		
	}

};

