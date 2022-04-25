#include "MovieValidator.h"




void MovieValidator::validate(const Movie& p) {
	std::vector<std::string> msgs;
	if (p.get_year() < 0) msgs.push_back("Negative year");
	if (p.get_genre().size() == 0) msgs.push_back("Genre null");
	if (p.get_title().size() == 0) msgs.push_back("Title null");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

std::ostream& operator<<(std::ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	MovieValidator v;
	Movie p{"",-2,"c",""};
	try {
		v.validate(p);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("Negative") >= 0);
		assert(mesaj.find("null") >= 0);
	}

}