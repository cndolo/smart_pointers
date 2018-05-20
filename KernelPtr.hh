#pragma once

#include <cstddef> // for SIZE_t
#include <cstdint>

template<typename T>
class KernelPtr 
{

  public:

	KernelPtr() : ptr(0) {}

	explicit KernelPtr(uint64_t ptr) : ptr(ptr) {}
	
	explicit KernelPtr(uint32_t ptr) : ptr(ptr) {}

	//explicit operator bool() const { return ptr != 0; }
    bool operator==(KernelPtr rhs) const { return ptr == rhs.ptr; }
    bool operator!=(KernelPtr rhs) const { return ptr != rhs.ptr; }
    bool operator<(KernelPtr rhs) const { return ptr < rhs.ptr; }
    bool operator<=(KernelPtr rhs) const { return ptr <= rhs.ptr; }
    bool operator>=(KernelPtr rhs) const { return ptr >= rhs.ptr; }
    bool operator>(KernelPtr rhs) const { return ptr > rhs.ptr; }

	
    T& operator+=(size_t inc) { ptr += sizeof(T)*inc; return *this; }
    T operator+(size_t inc) const { return T(ptr+sizeof(T)*inc); }
    T& incbytes(size_t inc) { ptr += inc; return *this; }
    T plusbytes(size_t inc) const { return T(ptr+inc); }

    T& operator-=(size_t inc) { ptr -= sizeof(T)*inc; return *this; }
    T operator-(size_t inc) const { return T(ptr-sizeof(T)*inc); }
    size_t operator-(T rhs) const { return (ptr-rhs)/sizeof(T); }

    T& operator=(T rhs) { ptr = rhs.ptr; return *this; }

    bool isValidAddress(const void* ptr) 
	{
		auto p = T::isValidTypeAdress(ptr);
		return p;
	}

	uintptr_t physInt() const
	{
		return T::physint();
	}

	const uint64_t PHYS() {
		return T::phys();
	}

	const uint64_t SIZE() {
		return T::size();
	}

	const uint64_t VIRT() {
		return T::virt();
	}  
protected:
	//uint32_t ptr;
	uint64_t ptr;
};
