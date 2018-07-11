#pragma once

#include <cassert>

template<class CFG, typename T>
class AbstractOffsetPtr32 {

public:

	typedef T valuetype;

	AbstractOffsetPtr32() : offs(0) {}

	//explicit AbstractOffsetPtr32(uint32_t offs) : offs(offs) {}

	explicit AbstractOffsetPtr32(uintptr_t offs) : offs(uint32_t(offs)) {}	

	static bool isValidPhysAddress(uintptr_t ptr) {
		return (ptr >= CFG::physBase()) && (ptr < CFG::physBase() + CFG::size());
	}
	
	// oder hier KERN_END  symbol nehmen?
	static bool isValidVirtAddress(uintptr_t ptr) {
		return (ptr > CFG::virtBase()) && (ptr < CFG::virtBase() + CFG::size());
	}	

	static AbstractOffsetPtr32 fromPhys(T* vp) {
		return AbstractOffsetPtr32(reinterpret_cast<uintptr_t>(vp) - CFG::physBase());
	}
	
	static AbstractOffsetPtr32 fromVirt(T* vp) {
		return AbstractOffsetPtr32(reinterpret_cast<uintptr_t>(vp) - CFG::virtBase());
	}

	static AbstractOffsetPtr32 fromPhys(uintptr_t ptr) {
		return AbstractOffsetPtr32(ptr - CFG::physBase());
	}
	
	explicit operator bool() const { return offs != 0; }
    bool operator==(AbstractOffsetPtr32 rhs) const { return offs == rhs.offs; }
    bool operator!=(AbstractOffsetPtr32 rhs) const { return offs != rhs.offs; }
    bool operator<(AbstractOffsetPtr32 rhs) const { return offs < rhs.offs; }
    bool operator<=(AbstractOffsetPtr32 rhs) const { return offs <= rhs.offs; }
    bool operator>=(AbstractOffsetPtr32 rhs) const { return offs >= rhs.offs; }
    bool operator>(AbstractOffsetPtr32 rhs) const { return offs > rhs.offs; }

    AbstractOffsetPtr32& operator+=(size_t inc) { offs += sizeof(T)*inc; return *this; }
    AbstractOffsetPtr32 operator+(size_t inc) const { return AbstractOffsetPtr32(offs+sizeof(T)*inc); }
    AbstractOffsetPtr32& incbytes(size_t inc) { offs += inc; return *this; }
    AbstractOffsetPtr32 plusbytes(size_t inc) const { return AbstractOffsetPtr32(offs+inc); }

    AbstractOffsetPtr32& operator-=(size_t inc) { offs -= sizeof(T)*inc; return *this; }
    AbstractOffsetPtr32 operator-(size_t inc) const { return AbstractOffsetPtr32(offs-sizeof(T)*inc); }
    size_t operator-(AbstractOffsetPtr32 rhs) const { return (offs-rhs)/sizeof(T); }

	AbstractOffsetPtr32& operator=(AbstractOffsetPtr32 rhs) { offs = rhs.offs; return *this; }

	uintptr_t phys() const { return  CFG::physBase() + offs; }
	
	uintptr_t offset() const { return offs; }
	
	uintptr_t logint() const {
		assert(mem());
		return phys();
	}
	
	bool mem() const { return offs < CFG::size(); }
	
	bool canonical() const
  	{
      	static constexpr uintptr_t CANONICAL_MASK = ((1ull << (64 - 48))-1) << 48;
      	return (offs & CANONICAL_MASK) == 0 || (offs & CANONICAL_MASK) == CANONICAL_MASK;
   	}

	T* log() const { return reinterpret_cast<T*>(logint()); }

	T* operator->() const { return log(); }

protected:
	uint32_t offs;
};













