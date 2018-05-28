#include "Config.hh"

template <typename T>

class AbstractOffsetPtr : public T {

public: 

	bool isValidTypeAddress(const void* ptr) 
	{
		auto p = reinterpret_cast<uintptr_t>(ptr);
		return (p >= T::getPhys()) && (p < T::getPhys() + T::getSize()); 
	}

	
};

