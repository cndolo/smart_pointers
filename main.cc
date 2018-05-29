#include <iostream>
#include <cstddef>
#include <cstdint>
#include <stdint.h>
#include "Config.hh"
#include "AbstractOffsetPtr.hh"
#include "AbstractPhysPtr64.hh"
#include "AbstractPhysPtr32.hh"

int main(int argv, char* argc[]) {

	const uintptr_t phys = 0x5000; 
	const uintptr_t log = 0x5200;
	const size_t size = 20 * sizeof(int);
	
	const void* ptr = reinterpret_cast<const void*>(phys);
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
	
	bool val1 = ap1->isValidTypeAddress(ptr);
	bool val2 = ap1->isValidTypeAddress(ptr2);
	bool val3 = ap1->isValidTypeAddress(ptr3);
	
	std::cout<<ptr<<" valid: "<<val1<<std::endl;
	std::cout<<ptr2<<" valid: "<<val2<<std::endl;
	std::cout<<ptr3<<" valid: "<<val3<<std::endl;

	AbstractPhysPtr64<config64Phys>* apPhys;

	std::cout<<"size of config64phys: "<<sizeof(config64Phys)<<std::endl;
	std::cout<<"size of AbstractPhysPtr64: "<<sizeof(apPhys)<<std::endl;
		
	bool val4 = apPhys->isValidAddress(ptr);
	bool val5 = apPhys->isValidAddress(ptr2);
	bool val6 = apPhys->isValidAddress(ptr3);

	std::cout<<ptr<<" valid: "<<val4<<std::endl;
	std::cout<<ptr2<<" valid: "<<val5<<std::endl;
	std::cout<<ptr3<<" valid: "<<val6<<std::endl;

}
