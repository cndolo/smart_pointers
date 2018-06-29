#include "AbstractPhysPtr32.hh"

template<class T>
class KernelPhysPtr32 : public AbstractPhysPtr32<KernelConfig, T> {
public:

	using AbstractPhysPtr32<KernelConfig,T>::AbstractPhysPtr32;
};

