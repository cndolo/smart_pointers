#include <iostream>
#include <cstddef>
#include <cstdint>
#include <stdint.h>
#include "Config.hh"
#include "AbstractOffsetPtr.hh"

int main(int argv, char* argc[]) {

	const uintptr_t phys = 0x5000; 
	const uintptr_t log = 0x5200;
	const size_t size = 20 * sizeof(int);
	
	const void* ptr = reinterpret_cast<const void*>(phys);
	const void* ptr2 = reinterpret_cast<const void*>(phys+size+1);
	const void* ptr3 = reinterpret_cast<const void*>(log + size);
	
	std::cout<<"phys: "<<config::getPhys()<<std::endl;
	std::cout<<"size: "<<config::getSize()<<std::endl;
	std::cout<<"virt: "<<config::getVirt()<<std::endl;
	
	std::cout<<"phys: "<<ptr<<std::endl;
	std::cout<<"size: "<<size<<std::endl;
	std::cout<<"log: "<<log<<std::endl;
	
	config::setPhys(phys);
	config::setVirt(log);
	config::setSize(size);	
	
	std::cout<<"phys: "<<config::getPhys()<<std::endl;
	std::cout<<"size: "<<config::getSize()<<std::endl;
	std::cout<<"virt: "<<config::getVirt()<<std::endl;
	
	AbstractOffsetPtr* ap1;
	
	bool val1 = ap1->isValidTypeAddress(ptr);
	bool val2 = ap1->isValidTypeAddress(ptr2);

	std::cout<<ptr<<" valid: "<<val1<<std::endl;
	std::cout<<ptr2<<" valid: "<<val2<<std::endl;
}
