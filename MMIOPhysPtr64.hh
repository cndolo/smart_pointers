#include "AbstractPhysPtr64.hh"


template<class T>
class MMIOPhysPtr64 : public AbstractPhysPtr64<MMIOConfig, T> {

public:

	using AbstractPhysPtr64<MMIOConfig, T>::AbstractPhysPtr64;

};
