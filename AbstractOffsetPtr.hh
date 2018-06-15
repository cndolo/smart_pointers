template<class CFG, typename T>
class AbstractOffsetPtr {

public:
	
	typedef T valuetype;
	
	uint64_t phys() { return  CFG::physBase + offs; }

	
	explicit operator bool() const { return ptr != 0; }
    bool operator==(AbstractOffsetPtr rhs) const { return ptr == rhs.ptr; }
    bool operator!=(AbstractOffsetPtr rhs) const { return ptr != rhs.ptr; }
    bool operator<(AbstractOffsetPtr rhs) const { return ptr < rhs.ptr; }
    bool operator<=(AbstractOffsetPtr rhs) const { return ptr <= rhs.ptr; }
    bool operator>=(AbstractOffsetPtr rhs) const { return ptr >= rhs.ptr; }
    bool operator>(AbstractOffsetPtr rhs) const { return ptr > rhs.ptr; }

    AbstractOffsetPtr& operator+=(size_t inc) { ptr += sizeof(T)*inc; return *this; }
    AbstractOffsetPtr operator+(size_t inc) const { return AbstractOffsetPtr(ptr+sizeof(T)*inc); }
    AbstractOffsetPtr& incbytes(size_t inc) { ptr += inc; return *this; }
    AbstractOffsetPtr plusbytes(size_t inc) const { return AbstractOffsetPtr(ptr+inc); }

    AbstractOffsetPtr& operator-=(size_t inc) { ptr -= sizeof(T)*inc; return *this; }
    AbstractOffsetPtr operator-(size_t inc) const { return AbstractOffsetPtr(ptr-sizeof(T)*inc); }
    size_t operator-(AbstractOffsetPtr rhs) const { return (ptr-rhs)/sizeof(T); }

	AbstractOffsetPtr& operator=(AbstractOffsetPtr rhs) { ptr = rhs.ptr; return *this; }
	
	bool mem() const { return offs < T::physBase(); }
		
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
	
	uintptr_t logint() const {
		//ASSERT(kernelmem());
		return phys();
	}

	AbstractOffsetPtr* logical() const { return reinterpret_cast<AbstractOffsetPtr*>(logint()); }

	AbstractOffsetPtr* operator->() const { return logical(); }

private:
	uint32_t ptr;
	uint32_t offs;
};













