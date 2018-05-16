/*#include "boot/memory-layout.h"
#include "util/compiler.hh"
#include "util/assert.hh"*/
#include <cstddef> // for SIZE_t
#include <cstdint>

//template<typename SmartPtr>

class SmartPtr 
{

  public:

	SmartPtr() : ptr(0) {}
	
	explicit SmartPtr(uint64_t ptr) : ptr(ptr) {}

	explicit SmartPtr(uint32_t ptr) : ptr(ptr) {}

	//explicit operator bool() const { return ptr != 0; }
    bool operator==(SmartPtr rhs) const { return ptr == rhs.ptr; }
    bool operator!=(SmartPtr rhs) const { return ptr != rhs.ptr; }
    bool operator<(SmartPtr rhs) const { return ptr < rhs.ptr; }
    bool operator<=(SmartPtr rhs) const { return ptr <= rhs.ptr; }
    bool operator>=(SmartPtr rhs) const { return ptr >= rhs.ptr; }
    bool operator>(SmartPtr rhs) const { return ptr > rhs.ptr; }

	
    SmartPtr& operator+=(size_t inc) { ptr += sizeof(SmartPtr)*inc; return *this; }
    SmartPtr operator+(size_t inc) const { return SmartPtr(ptr+sizeof(SmartPtr)*inc); }
    SmartPtr& incbytes(size_t inc) { ptr += inc; return *this; }
    SmartPtr plusbytes(size_t inc) const { return SmartPtr(ptr+inc); }

    SmartPtr& operator-=(size_t inc) { ptr -= sizeof(SmartPtr)*inc; return *this; }
    SmartPtr operator-(size_t inc) const { return SmartPtr(ptr-sizeof(SmartPtr)*inc); }
    size_t operator-(SmartPtr rhs) const { return (ptr-rhs)/sizeof(SmartPtr); }

    SmartPtr& operator=(SmartPtr rhs) { ptr = rhs.ptr; return *this; }
  protected:
	//uint32_t ptr;
	uint64_t ptr;
};
