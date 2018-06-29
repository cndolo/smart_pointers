#include "AbstractOffsetPtr32.hh"

template <class T>
class ImageOffsetPtr32 : public AbstractOffsetPtr32<ImageConfig, T> {

public:
	
	using AbstractOffsetPtr32<ImageConfig, T>::AbstractOffsetPtr32;
};

