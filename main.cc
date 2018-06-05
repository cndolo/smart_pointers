#include <iostream>
#include <cstddef>
#include <cstdint>
#include <stdint.h>
#include "Config.hh"
#include "AbstractOffsetPtr.hh"
#include "AbstractPhysPtr64.hh"
#include "AbstractPhysPtr32.hh"
#include "ImagePhysPtr32.hh"
#include "KernelPhysPtr32.hh"

int main(int argv, char* argc[]) {

	const uintptr_t phys = 0x5000; 
	const uintptr_t log = 0x5200;
	const size_t size = 20 * sizeof(int);
	
	const void* ptr = reinterpret_cast<const void*>(phys + (size-1));
	const void* ptr2 = reinterpret_cast<const void*>(phys+size+1);
	const void* ptr3 = reinterpret_cast<const void*>(log + size);
		
	std::cout<<"phys: "<<ptr<<std::endl;
	std::cout<<"size: "<<size<<std::endl;
	std::cout<<"log: "<<log<<std::endl;
	
	configOffset::setPhys(phys);
	configOffset::setVirt(log);
	configOffset::setSize(size);	
	
	std::cout<<"phys: "<<configOffset::getPhys()<<std::endl;
	std::cout<<"size: "<<configOffset::getSize()<<std::endl;
	std::cout<<"virt: "<<configOffset::getVirt()<<std::endl;
		
	AbstractOffsetPtr<configOffset>* ap1;
	
	bool val1 = ap1->isKernelAddress(ptr);
	bool val2 = ap1->isKernelAddress(ptr2);
	bool val3 = ap1->isImageAddress(ptr3);
	
	std::cout<<ptr<<" valid: "<<val1<<std::endl;
	std::cout<<ptr2<<" valid: "<<val2<<std::endl;
	std::cout<<ptr3<<" valid: "<<val3<<std::endl;

	AbstractPhysPtr64<config64phys>* apPhys;

	std::cout<<"size of config64phys: "<<sizeof(config64phys)<<std::endl;
	std::cout<<"size of AbstractPhysPtr64: "<<sizeof(apPhys)<<std::endl;
		
	bool val4 = apPhys->isKernelAddress(ptr);
	bool val5 = apPhys->isKernelAddress(ptr2);
	bool val6 = apPhys->isKernelAddress(ptr3);

	std::cout<<ptr<<" valid: "<<val4<<std::endl;
	std::cout<<ptr2<<" valid: "<<val5<<std::endl;
	std::cout<<ptr3<<" valid: "<<val6<<std::endl;

	AbstractPhysPtr32<config32phys>* apPhys32;

	std::cout<<"size of AbstractPhysPtr32: "<<sizeof(apPhys32)<<std::endl;
	std::cout<<"phys: "<<config32phys::getPhys()<<std::endl;
	std::cout<<"size: "<<config32phys::getSize()<<std::endl;
	std::cout<<"virt: "<<config32phys::getVirt()<<std::endl;

	bool val7 = apPhys32->isKernelAddress(ptr);
	bool val8 = apPhys32->isImageAddress(ptr2);
	bool val9 = apPhys32->isKernelAddress(ptr3);

	std::cout<<ptr<<" valid: "<<val7<<std::endl;
	std::cout<<ptr2<<" valid: "<<val8<<std::endl;
	std::cout<<ptr3<<" valid: "<<val9<<std::endl;

	ImagePhysPtr32* ip = new ImagePhysPtr32();
	KernelPhysPtr32* kp = new KernelPhysPtr32();

}
