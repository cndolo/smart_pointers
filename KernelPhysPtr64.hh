#include "AbstractPhysPtr64.hh"

template<class T>
class KernelPhysPtr64 : public AbstractPhysPtr64<KernelConfig, T> {

public:
	using AbstractPhysPtr64<KernelConfig, T>::AbstractPhysPtr64;
};
