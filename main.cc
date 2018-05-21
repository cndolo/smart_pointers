#include <iostream>
#include <cstddef>
#include <cstdint>
#include <stdint.h>
#include "MemoryPtr.hh"

int main(int argv, char* argc[]) {

	const uintptr_t phys = 0x50000; 
	const uintptr_t log = 0x40000;
	const size_t size = 20 * sizeof(int);
	
	const void* ptr = reinterpret_cast<const void*>(phys);
	const void* ptr2 = reinterpret_cast<const void*>(phys+size+1);
	const void* ptr3 = reinterpret_cast<const void*>(log + size);

	
	MemoryPtr<phys, size, log> * mp;
	KernelPtr<MemoryPtr<phys, size, log>> *kp;

	std::cout<<"phys: "<<kp->PHYS()<<std::endl;
	std::cout<<"size: "<<kp->SIZE()<<std::endl;
	std::cout<<"virt: "<<kp->VIRT()<<std::endl;

	bool valid = kp->isValidAddress(ptr);
	bool valid2 = kp->isValidAddress((char*)ptr3 + 1);
	
	std::cout<<"Ptr1 valid: "<<valid<<std::endl;
	std::cout<<"Ptr2 valid: "<<valid2<<std::endl;

	bool valid3 =mp->isValidTypeAddress(ptr);
	std::cout<<"Ptr2 valid: "<<valid3<<std::endl;
	
	MemoryPtr<phys, size, log>* mp2;
	*mp2 = MemoryPtr<phys,size,log>::toImageFromMemory(mp);
}
