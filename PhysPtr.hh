#include <cstddef>
#include <cstdint>

#include "KernelPtr.hh"

template<uint64_t PHYS, size_t SIZE, uint64_t VIRT>

class PhysPtr : public KernelPtr<PhysPtr<PHYS, SIZE, VIRT>>
{
	public:
	
		using KernelPtr<PhysPtr<PHYS, SIZE, VIRT>>::KernelPtr;		

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


template <uint32_t PHYS, size_t SIZE, uint32_t VIRT>
class PhysPtr32 : public KernelPtr<PhysPtr32<PHYS, SIZE, VIRT>>
{
	PhysPtr32() : ptr(0) {}
	
	explicit PhysPtr32(uint32_t ptr) : ptr(ptr) {}
	explicit PhysPtr32(uint64_t ptr) : ptr(uint32_t(ptr)) {
		ASSERT(ptr <= 0xFFFFFFFF);
	}

	uintptr_t physint() const { return ptr; }
	
	uintptr_t logint() const { return uintptr_t(ptr) + PHYS; }

	PhysPtr32* log() const { return reinterpret_cast<PhysPtr32*>(logint()); }

	PhysPtr32* operator->() const { return log(); }
protected:
 uint32_t ptr;
};
