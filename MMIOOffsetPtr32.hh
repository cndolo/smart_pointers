#include "AbstractOffsetPtr32.hh"


template <class T>
class MMIOOffsetPtr32 : public AbstractOffsetPtr32<MMIOConfig, T> {

public:

	using AbstractOffsetPtr32<MMIOConfig, T>::AbstractOffsetPtr32;

};
