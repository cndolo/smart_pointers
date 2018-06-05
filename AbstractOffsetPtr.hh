template <typename T>

class AbstractOffsetPtr : public T {

public: 

	AbstractOffsetPtr() : ptr(0) {}

	explicit AbstractOffsetPtr(uint32_t ptr) : ptr(ptr) {}
	
	explicit AbstractOffsetPtr(uint64_t ptr) : ptr(uint32_t(ptr)) {}

	// first expression always evaluates to true so can be removed
	bool isKernelAddress(const void* ptr) 
	{
		auto p = reinterpret_cast<uintptr_t>(ptr);
		return (p + T::getPhys() >= T::getPhys()) && (p + T::getPhys() < T::getPhys() + T::getSize()); 
	}

	// first expression always evaluates to true so can be removed
	bool isImageAddress(const void* ptr) {
		auto p = reinterpret_cast<uintptr_t>(ptr);
		return (p + T::getPhys() >= T::getPhys()) && (p + T::getPhys() < T::getVirt() + T::getSize() + uintptr_t(&KERN_END));
		//return (p + T::getPhys() >= T::getPhys()) && (p + T::getPhys() < T::getVirt() + uintptr_t(&KERN_END));
	}

	static AbstractOffsetPtr fromPhys(AbstractOffsetPtr* ptr) {
		return AbstractOffsetPtr(reinterpret_cast<uintptr_t>(ptr));
	}
	
	// Image -> phys 
	static AbstractOffsetPtr fromImage(AbstractOffsetPtr* vp) {
      //ASSERT(isImageAddress(vp));
      return AbstractOffsetPtr(reinterpret_cast<uintptr_t>(vp) - T::getPhys() -  T::getVirt());
    }
   
	// Kernel -> phys 
	static AbstractOffsetPtr fromKernel(AbstractOffsetPtr* vp) {
      //ASSERT(isKernelAddress(vp));
      return reinterpret_cast<AbstractOffsetPtr*>(reinterpret_cast<uintptr_t>(vp) - T::getPhys());
    }
	
	//phys -> image
	static AbstractOffsetPtr toImage(AbstractOffsetPtr* ptr) {
		return reinterpret_cast<AbstractOffsetPtr*>(reinterpret_cast<uintptr_t>(ptr) + T::getPhys() +T::getVirt());
	}

	static AbstractOffsetPtr phys2kernel (AbstractOffsetPtr* phys) {
		//ASSERT(isValidAddress(reinterpret_cast<const void*>(phys)));
		return AbstractOffsetPtr(reinterpret_cast<uintptr_t>(phys) + T::getPhys());
	}	

	uint32_t kernel2phys(AbstractOffsetPtr* vp) {
    	//ASSERT(isKernelAddress(vp));
    	return uint32_t(reinterpret_cast<uintptr_t>(vp) - T::getPhys());
  	}

	AbstractOffsetPtr* image2kernel(AbstractOffsetPtr* vp) {
    	//ASSERT(isImageAddress(vp));
    	return reinterpret_cast<AbstractOffsetPtr**>(reinterpret_cast<uintptr_t>(vp) - T::getVirt() + T::getPhys());
  	}	
  	
	AbstractOffsetPtr* kernel2image(AbstractOffsetPtr* kp) {
		//ASSERT(isKernelAddress(kp));
		return reinterpret_cast<AbstractOffsetPtr*>(reinterpret_cast<uintptr_t>(kp) + T::getVirt - T::getPhys());
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


protected:

	uint32_t ptr;
	//g++
	// const char KERN_END = ("KERN_END");
	//clang++
	const char* KERN_END = "KERN_END";
};

