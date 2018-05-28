#include "Config.hh"

//template <typename T>

class AbstractOffsetPtr : public config {

public: 

	bool isValidTypeAddress(const void* ptr) 
	{
		auto p = reinterpret_cast<uintptr_t>(ptr);
		return (p >= config::getPhys()) && (p < config::getPhys() + config::getSize()); 
	}

};

