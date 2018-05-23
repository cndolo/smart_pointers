#include <cstddef>
#include <cstdint>

#include "KernelPtr.hh"

//extern char KERN_END SYMBOL("KERN END");

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
			ASSERT(isValidTypeAddress(ip));
			return ImagePtr(reinterpret_cast<uintptr_t>(ip)-VIRT + PHYS);
			//return KernelPtr<ImagePtr>(reinterpret_cast<uintptr_t>(ip)-VIRT);		
		}

		uintptr_t physint() const { return ptr; }

		uintptr_t logint() const {
			ASSERT(imagemem());
			return ptr + PHYS;
		}

		bool imagemem() const { return ptr < SIZE; }

		bool canonical() const
  		{
      			static constexpr uintptr_t CANONICAL_MASK = ((1ull << (64 - 48))-1) << 48;
      			return (ptr & CANONICAL_MASK) == 0 || (ptr & CANONICAL_MASK) == CANONICAL_MASK;
    		}

		static uint64_t phys() { return PHYS; }		

		static size_t size() { return SIZE; }

		static uint64_t virt() { return VIRT; }

		ImagePtr* logical() const { return reinterpret_cast<ImagePtr*>(logint()); }

		ImagePtr* operator->() const { return logical(); }
		ImagePtr& operator=(ImagePtr rhs) { ptr = rhs.ptr; return *this; }	
	protected:
		uint64_t ptr;
};

template <uint32_t PHYS, size_t SIZE, uint32_t VIRT>
class ImagePtr32 : public KernelPtr<ImagePtr32<PHYS, SIZE, VIRT>>
{
	public:
	
		ImagePtr32() : ptr(0) {}
		
		explicit ImagePtr32(uint32_t ptr) : ptr(ptr) {}
		explicit ImagePtr32(uint64_t ptr) : ptr(uint32_t(ptr)) {
			ASSERT(ptr <= 0xFFFFFFFF);
		}
	 	
		inline bool isValidTypeAddress(const void* ptr)
		{
			auto p = reinterpret_cast<uintptr_t>(ptr);
			return p = (p >= VIRT) && (p < VIRT + SIZE);
			//return p = ( >= VIRT) && (p < VIRT + uintptr_t(&KERN_END));
		}
	
		static ImagePtr32 image2kernel(ImagePtr32* ip) {
			ASSERT(isValidTypeAddress(ip));
			return ImagePtr32(reinterpret_cast<uintptr_t>(ip)-VIRT + PHYS);
			//return KernelPtr<ImagePtr>(reinterpret_cast<uintptr_t>(ip)-VIRT);		
		}	
		bool imagemem() const { return ptr < SIZE; }

		bool canonical() const
  		{
      			static constexpr uintptr_t CANONICAL_MASK = ((1ull << (64 - 48))-1) << 48;
      			return (ptr & CANONICAL_MASK) == 0 || (ptr & CANONICAL_MASK) == CANONICAL_MASK;
    		}
		
		static uint64_t phys() { return PHYS; }		

		static size_t size() { return SIZE; }

		static uint64_t virt() { return VIRT; }

		uintptr_t physint() const { return ptr; }
	
		uintptr_t logint() const { return uintptr_t(ptr) + PHYS; }

		ImagePtr32* logical() const { return reinterpret_cast<ImagePtr32*>(logint()); }

		ImagePtr32* operator->() const { return logical(); }
protected:
 uint32_t ptr;
};
