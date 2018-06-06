#include <iostream>

class ImageOffsetPtr : public AbstractOffsetPtr<configOffset> {

public:

	ImageOffsetPtr() {
		std::cout<<"hello from ImageOffsetPtr"<<std::endl;		
	}

};

