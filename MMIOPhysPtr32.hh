#include "AbstractPhysPtr32.hh"


template<class T>
class MMIOPhysPtr32 : public AbstractPhysPtr32<MMIOConfig, T> {

public:
	using AbstractPhysPtr32<MMIOConfig, T>::AbstractPhysPtr32;
};
