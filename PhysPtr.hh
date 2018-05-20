#include <cstddef>
#include <cstdint>

#include "KernelPtr.hh"

template<uint64_t PHYS, size_t SIZE, uint64_t VIRT>

class PhysPtr : public KernelPtr<PhysPtr<PHYS, SIZE, VIRT>>
{
	public:
	
		using KernelPtr<MemoryPtr<PHYS, SIZE, VIRT>>::KernelPtr;		

		bool isValidTypeAddress(const void* ptr)
		{
			auto p = reinterpret_cast<uintptr_t>(ptr);
			return (p >= PHYS) && (p < PHYS + 
		}

		static PhysPtr phys2kernel(uintptr_t phys)
		{
			return PhysPtr(phys + PHYS);
		}

		static uint64_t phys() { return PHYS; }

		static size_t size() { return SIZE; }

		static uint64_t virt() { return VIRT; }
};
