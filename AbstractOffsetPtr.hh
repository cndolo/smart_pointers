template<class CFG, typename T>
class AbstractOffsetPtr {

public:
	typedef T valuetype;

	bool isValidPhysAddress(const void* ptr) {
		auto p = reinterpret_cast<uintptr_t>(ptr);
		return (p >= CFG::physBase()) && (p < CFG::physBase() + CFG::size());
	}
	
	// oder hier KERN_END  symbol nehmen?
	bool isValidVirtAddress(const void* ptr) {
		auto p = reinterpret_cast<uintptr_t>(ptr);
		return (p > CFG::virtBase()) && (p < CFG::virtBase() + CFG::size());
	}	

	static AbstractOffsetPtr fromKernel(T* vp) {
		return AbstractOffsetPtr(reinterpret_cast<uintptr_t>(vp) - CFG::physBase());
	}
	
	static AbstractOffsetPtr fromImage(T* vp) {
		return AbstractOffsetPtr(reinterpret_cast<uintptr_t>(vp) - CFG::virtBase());
	}

	static AbstractOffsetPtr fromPhys(T* ptr) {
		return AbstractOffsetPtr(reinterpret_cast<uintptr_t>(ptr));
	}
	
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

	uint32_t phys() { return  CFG::physBase() + offs; }
	
	uintptr_t physint() const { return offs; }
	
	uintptr_t logint() const {
		//ASSERT(mem());
		return phys();
	}
	
	bool mem() const { return offs < CFG::getSize(); }
	
	bool canonical() const
  	{
      	static constexpr uintptr_t CANONICAL_MASK = ((1ull << (64 - 48))-1) << 48;
      	return (offs & CANONICAL_MASK) == 0 || (offs & CANONICAL_MASK) == CANONICAL_MASK;
   	}

	AbstractOffsetPtr* log() const { return reinterpret_cast<AbstractOffsetPtr*>(logint()); }

	AbstractOffsetPtr* operator->() const { return log(); }

private:
	uint32_t ptr;
	uint32_t offs;
};













