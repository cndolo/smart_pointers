#include <cstddef>
#include <cstdint>

#include "KernelPtr.hh"

template<uint64_t PHYS, size_t SIZE, uint64_t VIRT>

class PhysPtr : public KernelPtr<PhysPtr<PHYS, SIZE, VIRT>>
{
	
	public:
	
		using KernelPtr<PhysPtr<PHYS, SIZE, VIRT>>::KernelPtr;		

		inline bool isValidTypeAddress(const void* ptr)
		{
			auto p = reinterpret_cast<uintptr_t>(ptr);
			return (p >= PHYS) && (p < PHYS + SIZE);
		}

		static PhysPtr phys2kernel(PhysPtr* phys)
		{
			ASSERT(isValidTypeAddress(reinterpret_cast<const void*>(phys)));
			return PhysPtr(reinterpret_cast<uintptr_t>(phys) + PHYS);
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

		PhysPtr* logical() const { return reinterpret_cast<PhysPtr*>(logint()); }

		PhysPtr* operator->() const { return logical(); }
		PhysPtr& operator=(PhysPtr rhs) { ptr = rhs.ptr; return *this; }

	protected:
		uintptr_t ptr;	
};


template <uint32_t PHYS, size_t SIZE, uint32_t VIRT>
class PhysPtr32 : public KernelPtr<PhysPtr32<PHYS, SIZE, VIRT>>
{
	public:

		PhysPtr32() : ptr(0) {}
	
		explicit PhysPtr32(uint32_t ptr) : ptr(ptr) {}
		explicit PhysPtr32(uint64_t ptr) : ptr(uint32_t(ptr)) {
			ASSERT(ptr <= 0xFFFFFFFF);
		}
		
		inline bool isValidTypeAddress(const void* ptr) 
		{
			auto p = reinterpret_cast<uintptr_t>(ptr);
			return (p >= PHYS) && (p < PHYS + SIZE); 
		}
		
		static PhysPtr32 phys2kernel(PhysPtr32* phys)
		{
			ASSERT(isValidTypeAddress(reinterpret_cast<const void*>(phys)));
			return PhysPtr32(reinterpret_cast<uintptr_t>(phys) + PHYS);
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

		PhysPtr32* logical() const { return reinterpret_cast<PhysPtr32*>(logint()); }

		PhysPtr32* operator->() const { return logical(); }
	protected:
 		uint32_t ptr;
};
