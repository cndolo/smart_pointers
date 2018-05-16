#include <cstddef>
#include <cstdint>

#include "KernelPtr.hh"

extern char KERN_END SYMBOL("KERN END");

template<uint64_t PHYS, size_t SIZE, uint64_t VIRT>

class ImagePtr : public KernelPtr<ImagePtr<PHYS, SIZE, VIRT>>
{

	public:

		using KernelPtr<MemoryPtr<PHYS, SIZE, VIRT>>::KernelPtr;
			
		bool isValidTypeAddress(const void* ptr)
		{
			auto p = reinterpret_cast<uintptr_t>(ptr);
			return p = (p >= VIRT) && (p < VIRT + SIZE);
			//return p = ( >= VIRT) && (p < VIRT + uintptr_t(&KERN_END));
		}

		static ImagePtr image2kernel(ImagePtr* ip) {
			ASSERT(isValidAddress(ip));
			return ImagePtr(reinterpret_cast<uintptr_t>(ip)-VIRT + PHYS);
			//return KernelPtr<MemoryPtr>(reinterpret_cast<uintptr_t>(ip)-VIRT);		
		}

};
