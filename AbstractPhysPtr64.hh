#pragma once

#include <cassert>

template<typename CFG, typename T>
class AbstractPhysPtr64 {

public:

	typedef T valuetype;

	AbstractPhysPtr64() : ptr(0) {}

	explicit AbstractPhysPtr64(uint64_t ptr) : ptr(ptr) {} 

	explicit AbstractPhysPtr64(uintptr_t ptr) : ptr(ptr) {}

	static bool isValidPhysAddress(uintptr_t ptr) 
	{
		return (ptr >= CFG::physBase()) && (ptr < CFG::physBase() + CFG::size()); 
	}
	
	static bool isValidVirtAddress(uintptr_t ptr)
  	{
    	return (ptr >= CFG::virtBase()) && (ptr < CFG::virtBase() + CFG::size());
  	}

	static AbstractPhysPtr64 fromPhys(T* ptr) 
	{
		return AbstractPhysPtr64(reinterpret_cast<uintptr_t>(ptr));
	}
    
	// Image -> phys 
	static AbstractPhysPtr64 fromVirt(T* vp) {
      //ASSERT(isImageAddress(vp));
      return AbstractPhysPtr64(reinterpret_cast<uintptr_t>(vp) - CFG::virtBase());
    }
   
	// Kernel -> phys 
	static AbstractPhysPtr64 fromPhys(uintptr_t ptr) {
      //ASSERT(isKernelAddress(vp));
      return AbstractPhysPtr64(ptr);
    }
/*	
	//phys -> image
	static AbstractPhysPtr64 toImage(AbstractPhysPtr64* ptr) {
		return reinterpret_cast<AbstractPhysPtr64*>(reinterpret_cast<uintptr_t>(ptr) + T::getVirt());
	}

	AbstractPhysPtr64* phys2kernel (AbstractPhysPtr64* phys) {
		//ASSERT(isValidAddress(reinterpret_cast<const void*>(phys)));
		return reinterpret_cast<AbstractPhysPtr64*>(reinterpret_cast<uintptr_t>(phys) + T::getPhys());
	}	
	
	uint64_t kernel2phys(AbstractPhysPtr64* vp) {
    	//ASSERT(isKernelAddress(vp));
    	return uint64_t(reinterpret_cast<uintptr_t>(vp) - T::getPhys());
  	}

	AbstractPhysPtr64* image2kernel(AbstractPhysPtr64* vp) {
    	//ASSERT(isImageAddress(vp));
    	return reinterpret_cast<AbstractPhysPtr64**>(reinterpret_cast<uintptr_t>(vp) - T::getVirt() + T::getPhys());
  	}	
  	
	AbstractPhysPtr64* kernel2image(AbstractPhysPtr64* kp) {
		//ASSERT(isKernelAddress(kp));
		return reinterpret_cast<AbstractPhysPtr64*>(reinterpret_cast<uintptr_t>(kp) + T::getVirt - T::getPhys());
	}
*/	
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

	uintptr_t phys() const { return ptr + CFG::virtBase() - CFG::physBase(); }
	
	uintptr_t physint() const { return ptr; }
	
	uintptr_t logint() const {
		assert(mem());
		return phys();
	}

	uintptr_t getPtr() const {
		return ptr;
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
	uint64_t ptr;
	//g++
	//const char KERN_END = ("KERN_END");
	//clang++
	const char* KERN_END = "KERN_END";
};
