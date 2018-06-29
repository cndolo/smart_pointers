#include "AbstractPhysPtr64.hh"

template<class T>
class ImagePhysPtr64 : public AbstractPhysPtr64<ImageConfig, T> {

public:
	
	using AbstractPhysPtr64<ImageConfig,T>::AbstractPhysPtr64;
};
