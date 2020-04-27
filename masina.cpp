#include "masina.h"

bool cmpType(const Car& c1, const Car&c2) {
	return c1.getType() < c2.getType();
}

bool cmpnrInm(const Car& c1, const Car&c2)noexcept{
	return c1.getnrInm() < c2.getnrInm();
}

bool cmpProAndMod(const Car& c1, const Car& c2) {
	return c1.getProd() < c2.getProd() || (c1.getProd() == c2.getProd() && c1.getMod() < c2.getMod());
}

