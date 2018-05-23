#include <cstddef>
#include <cstdint>

#include "KernelPtr.hh"

extern char KERN_END SYMBOL("KERN END");

template<uint64_t PHYS, size_t SIZE, uint64_t VIRT>

class ImagePtr : public KernelPtr<ImagePtr<PHYS, SIZE, VIRT>>
{

	public:

		using KernelPtr<ImagePtr<PHYS, SIZE, VIRT>>::KernelPtr;
			
	 	inline bool isValidTypeAddress(const void* ptr)
		{
			auto p = reinterpret_cast<uintptr_t>(ptr);
			return p = (p >= VIRT) && (p < VIRT + SIZE);
			//return p = ( >= VIRT) && (p < VIRT + uintptr_t(&KERN_END));
		}

		static ImagePtr image2kernel(ImagePtr* ip) {
			ASSERT(isValidAddress(ip));
			return ImagePtr(reinterpret_cast<uintptr_t>(ip)-VIRT + PHYS);
			//return KernelPtr<ImagePtr>(reinterpret_cast<uintptr_t>(ip)-VIRT);		
		}

		uintptr_t physint() const { return ptr; }

		static uint64_t phys() { return PHYS; }		

		static size_t size() { return SIZE; }

		static uint64_t virt() { return VIRT; }
	protected:
		uint64_t ptr;
};

template <uint32_t PHYS, size_t SIZE, uint32_t VIRT>
class ImagePtr32 : public KernelPtr<ImagePtr32<PHYS, SIZE, VIRT>>
{
	ImagePtr32() : ptr(0) {}
	
	explicit ImagePtr32(uint32_t ptr) : ptr(ptr) {}
	explicit ImagePtr32(uint64_t ptr) : ptr(uint32_t(ptr)) {
		ASSERT(ptr <= 0xFFFFFFFF);
	}

	uintptr_t physint() const { return ptr; }
	
	uintptr_t logint() const { return uintptr_t(ptr) + PHYS; }

	ImagePtr32* log() const { return reinterpret_cast<ImagePtr32*>(logint()); }

	ImagePtr32* operator->() const { return log(); }
protected:
 uint32_t ptr;
};
