#include "Config.hh"

template<typename t>

class AbstractPhysPtr64 : public T {

public:

	bool isValidAddress(const void* ptr) 
	{
		auto p = reinterpret_cast<uintptr_t>(ptr);
		return (p >= T::getPhys()) && (p < T::getPhys() + T::getSize()); 
	}
};
