#include "Config.hh"

template<typename T>

class AbstractPhysPtr64 : public T {

public:

	bool isValidAddress(const void* ptr) 
	{
		auto p = reinterpret_cast<uintptr_t>(ptr);
				return (p >= T::getPhys()) && (p < T::getPhys() + T::getSize()); 
	}
	
	/*static AbstractPhysPtr64 toKernelMemory() {
		return 
	}*/	
	
	bool kernelmem() const { return ptr < T::getSize(); }
		
	bool canonical() const
  	{
      	static constexpr uintptr_t CANONICAL_MASK = ((1ull << (64 - 48))-1) << 48;
      	return (ptr & CANONICAL_MASK) == 0 || (ptr & CANONICAL_MASK) == CANONICAL_MASK;
   	}

	uintptr_t physint() const { return ptr; }

	uintptr_t logint() const {
		ASSERT(kernelmem());
		return ptr + T::getPhys();
	}

	AbstractPhysPtr64* logical() const { return reinterpret_cast<AbstractPtr64*>(logint()); }

	AbstractPhysPtr64* operator->() const { return logical(); }

protected:
	uint64_t ptr;
};
