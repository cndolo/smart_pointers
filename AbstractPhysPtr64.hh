#include "Config.hh"

template<typename T>

class AbstractPhysPtr64 : public T {

public:

	//TODO: Add constructor

	bool isValidAddress(const void* ptr) 
	{
		auto p = reinterpret_cast<uintptr_t>(ptr);
				return (p >= T::getPhys()) && (p < T::getPhys() + T::getSize()); 
	}
	
	static AbstractPhysPtr64 phys2kernel (AbstractPhysPtr64* phys) {
		//ASSERT(isValidAddress(reinterpret_cast<const void*>(phys)));
		return AbstractPhysPtr64(reinterpret_cast<uintptr_t>(phys) + T::getPhys());
	}	
	
	/*static uintptr_t phys2kernel (AbstractPtr64* phys) {
		//ASSERT(isValidAddress(reinterpret_cast<const void*>(phys)));
		return (reinterpret_cast<uintptr_t>(phys) + T::getPhys());
	}*/	

	static AbstractPhysPtr64 fromPhys(AbstractPhysPtr64* ptr) {
		return AbstractPhysPtr64(reinterpret_cast<uintptr_t>(ptr));
	}
	
	explicit operator bool() const { return ptr != 0; }
    bool operator==(AbstractPhysPtr64 rhs) const { return ptr == rhs.ptr; }
    bool operator!=(AbstractPhysPtr64 rhs) const { return ptr != rhs.ptr; }
    bool operator<(AbstractPhysPtr64 rhs) const { return ptr < rhs.ptr; }
    bool operator<=(AbstractPhysPtr64 rhs) const { return ptr <= rhs.ptr; }
    bool operator>=(AbstractPhysPtr64 rhs) const { return ptr >= rhs.ptr; }
    bool operator>(AbstractPhysPtr64 rhs) const { return ptr > rhs.ptr; }

    AbstractPhysPtr64& operator+=(size_t inc) { ptr += sizeof(T)*inc; return *this; }
    AbstractPhysPtr64 operator+(size_t inc) const { return AbstractPhysPtr64(ptr+sizeof(T)*inc); }
    AbstractPhysPtr64& incbytes(size_t inc) { ptr += inc; return *this; }
    AbstractPhysPtr64 plusbytes(size_t inc) const { return AbstractPhysPtr64(ptr+inc); }

    AbstractPhysPtr64& operator-=(size_t inc) { ptr -= sizeof(T)*inc; return *this; }
    AbstractPhysPtr64 operator-(size_t inc) const { return AbstractPhysPtr64(ptr-sizeof(T)*inc); }
    size_t operator-(AbstractPhysPtr64 rhs) const { return (ptr-rhs)/sizeof(T); }

    AbstractPhysPtr64& operator=(AbstractPhysPtr64 rhs) { ptr = rhs.ptr; return *this; }

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

	AbstractPhysPtr64* logical() const { return reinterpret_cast<AbstractPhysPtr64*>(logint()); }

	AbstractPhysPtr64* operator->() const { return logical(); }

protected:
	uint64_t ptr;
};
