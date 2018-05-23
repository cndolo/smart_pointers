#include <cstddef>
#include <cstdint>

#include "KernelPtr.hh"

template <uint64_t IM_PHYS, size_t IM_SIZE, uint64_t IM_VIRT> class ImagePtr;

template<uint64_t PHYS, size_t SIZE, uint64_t VIRT>

class MemoryPtr : public KernelPtr<MemoryPtr<PHYS, SIZE, VIRT>>
{

	public:
	
		using KernelPtr<MemoryPtr<PHYS, SIZE, VIRT>>::KernelPtr;

		inline bool isValidTypeAddress(const void* ptr) 
		{
			auto p = reinterpret_cast<uintptr_t>(ptr);
			return (p >= PHYS) && (p < PHYS + SIZE); 
		}

		static MemoryPtr toImageFromMemory(MemoryPtr* mp) {
			//ASSERT(isValidTypeAddress(reinterpret_cast<const void*>(mp)));
			return MemoryPtr(reinterpret_cast<uintptr_t>(mp)-PHYS);
		}

		uintptr_t physint() const { return ptr;}

		uintptr_t logint() const {
			ASSERT(kernelmem());
			return ptr + PHYS;
		}

		bool kernelmem() const { return ptr < SIZE; }

		bool canonical() const
  		{
      			static constexpr uintptr_t CANONICAL_MASK = ((1ull << (64 - 48))-1) << 48;
      			return (ptr & CANONICAL_MASK) == 0 || (ptr & CANONICAL_MASK) == CANONICAL_MASK;
    		}

		static uint64_t phys() { return PHYS; }

		static size_t size() { return SIZE; }

		static uint64_t virt() { return VIRT; }
    	
		MemoryPtr* logical() const { return reinterpret_cast<MemoryPtr*>(logint()); }

		MemoryPtr* operator->() const { return logical(); }
		MemoryPtr& operator=(MemoryPtr rhs) { ptr = rhs.ptr; return *this; }	
	protected:
		uintptr_t ptr;
		
};
/*template<uint32_t OFFSET, size_t SIZE>
class MemoryPtr32 : public KernelPtr<MemoryPtr32<>>
{
		static MemoryPtr32 kernel2phys(MemoryPtr32* mp) 
		{
			return MemoryPtr32(reinterpret_cast<uint64_t>(mp)-PHYS);
		}

};*/

template <uint32_t PHYS, size_t SIZE, uint32_t VIRT>
class MemoryPtr32 : public KernelPtr<MemoryPtr32<PHYS, SIZE, VIRT>>
{
	public: 
		
		MemoryPtr32() : ptr(0) {}
	
		explicit MemoryPtr32(uint32_t ptr) : ptr(ptr) {}
		explicit MemoryPtr32(uint64_t ptr) : ptr(uint32_t(ptr)) {
			ASSERT(ptr <= 0xFFFFFFFF);
		}

		inline bool isValidTypeAddress(const void* ptr) 
		{
			auto p = reinterpret_cast<uintptr_t>(ptr);
			return (p >= PHYS) && (p < PHYS + SIZE); 
		}

		static MemoryPtr32 toImageFromMemory(MemoryPtr32* mp) {
			ASSERT(isValidTypeAddress(reinterpret_cast<const void*>(mp)));
			return MemoryPtr32(reinterpret_cast<uintptr_t>(mp)-PHYS);
		}

		bool kernelmem() const { return ptr < SIZE; }

		bool canonical() const
  		{
      			static constexpr uintptr_t CANONICAL_MASK = ((1ull << (64 - 48))-1) << 48;
      			return (ptr & CANONICAL_MASK) == 0 || (ptr & CANONICAL_MASK) == CANONICAL_MASK;
    		}

		uintptr_t physint() const { return ptr; }
	
		uintptr_t logint() const { return uintptr_t(ptr) + PHYS; }

		static uint64_t phys() { return PHYS; }

		static size_t size() { return SIZE; }

		static uint64_t virt() { return VIRT; }

		MemoryPtr32* logical() const { return reinterpret_cast<MemoryPtr32*>(logint()); }

		MemoryPtr32* operator->() const { return logical(); }
	protected:
 uint32_t ptr;
};
