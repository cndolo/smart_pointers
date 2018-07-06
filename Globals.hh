//#include "util/error-trace.hh"

template <class TO, class FROM>
inline TO convert(FROM from) {
//	static_assert(isEqual<TO:: >);
	if(TO::isValidPhysAddress(from.phys())) {
		return TO::fromPhys(from.phys());
	} else {
		//print error message using optional
	}
};
/* 
 *	MYTHOS CODE WITH OPTIONAL
inline optional <TO> convert(FROMfrom) {
	auto o = TO::isValidPhysAddress(from.phys());
	if (o) return TO::fromPhys(from.phys());
	else RETHROW(o);
};*/		

template <class T1, class T2>
struct isEqual {
	enum equal { val = 0 };
};

template <class T>
struct isEqual<T,T> {
	enum equal { val = 1 };
};

