#include "AbstractOffsetPtr32.hh"

template <class T>
class KernelOffsetPtr32 : public AbstractOffsetPtr32<KernelConfig, T> {

public:

	using AbstractOffsetPtr32<KernelConfig,T>::AbstractOffsetPtr32;
};

