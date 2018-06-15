#include <iostream>
template <class T>
class MMIOOffsetPtr : public AbstractOffsetPtr<MMIOConfig, T> {

public:

		MMIOOffsetPtr() {
		std::cout<<"hello from MMIOOffsetPtr"<<std::endl;		
	}

};
