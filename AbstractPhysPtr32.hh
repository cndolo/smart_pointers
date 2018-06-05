template <typename T>

class AbstractPhysPtr32 : public T {

public:

	AbstractPhysPtr32() : ptr(0) {}

	explicit AbstractPhysPtr32(uint32_t ptr) : ptr(ptr) {}

	explicit AbstractPhysPtr32(uint64_t ptr) : ptr(uint32_t(ptr)) {}
	
	bool isKernelAddress(const void* ptr) 
	{
		auto p = reinterpret_cast<uintptr_t>(ptr);
		return (p >= T::getPhys()) && (p < T::getPhys() + T::getSize()); 
	}
	
	bool isImageAddress(const void* ptr)
  	{
    	auto p = reinterpret_cast<uintptr_t>(ptr);
    	return (p >= T::getVirt()) && (p < T::getVirt() + uintptr_t(&KERN_END));
  	}
    
	static AbstractPhysPtr32 fromPhys(AbstractPhysPtr32* ptr) {
		return AbstractPhysPtr32(reinterpret_cast<uintptr_t>(ptr));
	}
	
	// Image -> phys 
	static AbstractPhysPtr32 fromImage(AbstractPhysPtr32* vp) {
      //ASSERT(isImageAddress(vp));
      return AbstractPhysPtr32(reinterpret_cast<uintptr_t>(vp) - T::getVirt());
    }
   
	// Kernel -> phys 
	static AbstractPhysPtr32 fromKernel(AbstractPhysPtr32* vp) {
      //ASSERT(isKernelAddress(vp));
      return reinterpret_cast<AbstractPhysPtr32*>(reinterpret_cast<uintptr_t>(vp) - T::getPhys());
    }
	
	//phys -> image
	static AbstractPhysPtr32 toImage(AbstractPhysPtr32* ptr) {
		return reinterpret_cast<AbstractPhysPtr32*>(reinterpret_cast<uintptr_t>(ptr) + T::getVirt());
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

	AbstractPhysPtr32* logical() const { return reinterpret_cast<AbstractPhysPtr32*>(logint()); }

	AbstractPhysPtr32* operator->() const { return logical(); }

	
protected:
	uint32_t ptr;
	//g++
	// const char KERN_END = ("KERN_END");
	//clang++
	const char* KERN_END = "KERN_END";
};
