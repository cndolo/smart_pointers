#include "AbstractPhysPtr32.hh"

template<class T>

class ImagePhysPtr32 : public AbstractPhysPtr32<ImageConfig, T> {
public:

	using AbstractPhysPtr32<ImageConfig, T>::AbstractPhysPtr32;
};
