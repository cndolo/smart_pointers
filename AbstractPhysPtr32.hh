#pragma once

#include <cassert>

template<class CFG, typename T>
class AbstractPhysPtr32 {

public:
	
	typedef T valuetype;

	AbstractPhysPtr32() : ptr(0) {}

	//explicit AbstractPhysPtr32(uint32_t ptr) : ptr(ptr) {}

	explicit AbstractPhysPtr32(uint64_t ptr) : ptr(uint32_t(ptr)) {}
	
	static bool isValidPhysAddress(uintptr_t ptr) 
	{
		return (ptr >= CFG::physBase()) && (ptr < CFG::physBase() + CFG::size()); 
	}
	
	static bool isValidVirtAddress(uintptr_t ptr)
  	{
    	return (ptr >= CFG::virtBase()) && (ptr < CFG::virtBase() + CFG::size());
  	}
	
	// Kernel -> phys 
	static AbstractPhysPtr32 fromPhys(T* vp) {
      asser(isValidPhysAddress(vp));
      return AbstractPhysPtr32(reinterpret_cast<uintptr_t>(vp) - CFG::physBase());
    }
 	// Image -> phys 
	static AbstractPhysPtr32 fromVirt(T* vp) {
      assert(isValidVirtAddress(vp));
      return AbstractPhysPtr32(reinterpret_cast<uintptr_t>(vp) - CFG::virtBase());
    }   

	static AbstractPhysPtr32 fromPhys(uintptr_t ptr) {
		return AbstractPhysPtr32(ptr - CFG::physBase());
	}
		   
	//phys -> image
/*	static AbstractPhysPtr32 toImage(AbstractPhysPtr32* ptr) {
		return reinterpret_cast<AbstractPhysPtr32*>(reinterpret_cast<uintptr_t>(ptr) + CFG::virtBase());
	}

	static AbstractPhysPtr32 phys2kernel (AbstractPhysPtr32* phys) {
		//ASSERT(isValidAddress(reinterpret_cast<const void*>(phys)));
		return AbstractPhysPtr32(reinterpret_cast<uintptr_t>(phys) + T::getPhys());
	}	

	uint32_t kernel2phys(AbstractPhysPtr32* vp) {
    	//ASSERT(isKernelAddress(vp));
    	return uint32_t(reinterpret_cast<uintptr_t>(vp) - T::getPhys());
  	}

	AbstractPhysPtr32* image2kernel(AbstractPhysPtr32* vp) {
    	//ASSERT(isImageAddress(vp));
    	return reinterpret_cast<AbstractPhysPtr32**>(reinterpret_cast<uintptr_t>(vp) - T::getVirt() + T::getPhys());
  	}	
  	
	AbstractPhysPtr32* kernel2image(AbstractPhysPtr32* kp) {
		//ASSERT(isKernelAddress(kp));
		return reinterpret_cast<AbstractPhysPtr32*>(reinterpret_cast<uintptr_t>(kp) + T::getVirt - T::getPhys());
	}*/

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

	uintptr_t phys() const { return ptr + CFG::virtBase() - CFG::physBase(); }
		
	uintptr_t physint() const { return ptr; }
	
	uintptr_t logint() const {
		assert(mem());
		return phys();
	}

	bool mem() const { return ptr < CFG::size(); }
	
	bool canonical() const
  	{
      	static constexpr uintptr_t CANONICAL_MASK = ((1ull << (64 - 48))-1) << 48;
      	return (ptr & CANONICAL_MASK) == 0 || (ptr & CANONICAL_MASK) == CANONICAL_MASK;
   	}

	T* log() const { return reinterpret_cast<T*>(logint()); }

	T* operator->() const { return log(); }

	
protected:
	uint32_t ptr;
	//g++
	// const char KERN_END = ("KERN_END");
	//clang++
	const char* KERN_END = "KERN_END";
};
