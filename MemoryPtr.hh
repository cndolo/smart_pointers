#include <cstddef>
#include <cstdint>

#include "KernelPtr.hh"

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
			ASSERT(isValidAddress(mp));
			return MemoryPtr(reinterpret_cast<uintptr_t>(mp)-PHYS);
		}

		uintptr_t physint() const { return ptr;}

		bool logint() const {
			ASSERT(kernelmem());
			return ptr + PHYS;
		}

		bool kernelmem() const { return ptr < SIZE; }

				
    	bool canonical() const
    	{
      		static constexpr uintptr_t CANONICAL_MASK = ((1ull << (64 - 48))-1) << 48;
      		return (ptr & CANONICAL_MASK) == 0 || (ptr & CANONICAL_MASK) == CANONICAL_MASK;
    	}

		MemoryPtr* log() const { return reinterpret_cast<MemoryPtr*>(logint()); }

		MemoryPtr* operator->() const { return log(); }

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
