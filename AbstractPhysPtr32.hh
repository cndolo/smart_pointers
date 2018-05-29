#include "Config.hh"

template <typename T>

class AbstractPhysPtr32 : public T {

public:

	AbstractPhysPtr32() : ptr(ptr) {}

	explicit AbstractPhysPtr32(uint32_t ptr) : ptr(ptr) {}

	explicit AbstractPhysPtr32(uint64_t ptr) : ptr(uint32_t(ptr)) {}
	
	bool isValidAddress(const void* ptr) 
	{
		auto p = reinterpret_cast<uintptr_t>(ptr);
				return (p >= T::getPhys()) && (p < T::getPhys() + T::getSize()); 
	}
    explicit operator bool() const { return ptr != 0; }
    bool operator==(AbstractPhysPtr32 rhs) const { return ptr == rhs.ptr; }
    bool operator!=(AbstractPhysPtr32 rhs) const { return ptr != rhs.ptr; }
    bool operator<(AbstractPhysPtr32 rhs) const { return ptr < rhs.ptr; }
    bool operator<=(AbstractPhysPtr32 rhs) const { return ptr <= rhs.ptr; }
    bool operator>=(AbstractPhysPtr32 rhs) const { return ptr >= rhs.ptr; }
    bool operator>(AbstractPhysPtr32 rhs) const { return ptr > rhs.ptr; }

    AbstractPhysPtr32& operator+=(size_t inc) { ptr += sizeof(T)*inc; return *this; }
    AbstractPhysPtr32 operator+(size_t inc) const { return AbstractPhysPtr32(ptr+sizeof(T)*inc); }
    AbstractPhysPtr32& incbytes(size_t inc) { ptr += inc; return *this; }
    AbstractPhysPtr32 plusbytes(size_t inc) const { return AbstractPhysPtr32(ptr+inc); }

    AbstractPhysPtr32& operator-=(size_t inc) { ptr -= sizeof(T)*inc; return *this; }
    AbstractPhysPtr32 operator-(size_t inc) const { return AbstractPhysPtr32(ptr-sizeof(T)*inc); }
    size_t operator-(AbstractPhysPtr32 rhs) const { return (ptr-rhs)/sizeof(T); }

    AbstractPhysPtr32& operator=(AbstractPhysPtr32 rhs) { ptr = rhs.ptr; return *this; }
	
protected:
	uint32_t ptr;

};
