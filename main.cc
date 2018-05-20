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

	/*	KernelImPtr<phys, size, log> *kip;
	
	bool val = kip->isKernelImAddress(ptr);
	bool val2 = kip->isKernelImAddress(ptr2);
	bool val3 = kip->isKernelImAddress(ptr);
	std::cout<<"Ptr1 valid: "<<val<<std::endl;
	std::cout<<"Ptr2 valid: "<<val2<<std::endl;
	std::cout<<"Ptr3 valid: "<<val3<<std::endl;

	uintptr_t physint = kip->physint();
    std::cout<<"Ptr: "<<physint<<std::endl;

	bool kimage = kip->kernelImage();
	std::cout<<"kernelImage(): "<<kimage<<std::endl;*/
}
