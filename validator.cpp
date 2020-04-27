#include "validator.h"

void CarValidator::validate(const Car& c) {
	vector<string> mesaje;
	if (c.getType().size() == 0) mesaje.push_back("Tip Vid!!!\n");
	if (c.getMod().size() == 0) mesaje.push_back("Model Vid!!!\n");
	if (c.getProd().size() == 0) mesaje.push_back("Producator Vid!!!\n");
	if (c.getnrInm().size()==0) mesaje.push_back("Numar de inmatriculare negativ!!!\n");
	if (mesaje.size() > 0) { throw ValidateException(mesaje); }
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto msg : ex.mesaje) {
		out << msg;
	}
	return out;
}
