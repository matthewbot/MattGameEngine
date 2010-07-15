#include "FontDefReader.h"
#include "FontDef.h"
#include <MGE/util/Exception.h>

using namespace std;
using namespace mge;

FontDefReader::FontDefReader(const FontDef &def, const std::string &str) 
: def(def), str(str), iter(str.begin()), prevc(-1) {
	++*this;
}

FontDefReader& FontDefReader::operator++() {
	if (iter == str.end()) {
		data.charval = -1;
		return *this;
	}

	int c = *iter++; // step one, read character from string
	data.charval = c; // store it

	const FontDef::CharMap &chars = def.chars;
	FontDef::CharMap::const_iterator chardata = chars.find(c); // step two, look up character data
	
	if (chardata == chars.end()) { // if it doesn't exist
		chardata = chars.find('?'); // grab a ? instead
		if (chardata == chars.end()) // if that doesn't exist
			throw Exception(string("Bad character and can't find ? in font")); // then error out
	}
	data.fc = &chardata->second; // store a pointer

	data.fk = NULL; // clear out previous kerning data
	
	if (prevc != -1) { // step three, kerning data, only if we have a previous char to look from
		const FontDef::KerningMap &kernings = def.kernings;
		FontDef::KerningMap::const_iterator kerningdata = kernings.find(make_pair(prevc, c)); // look it up
		
		if (kerningdata != kernings.end()) // if it exists
			data.fk = &kerningdata->second; // store a pointer
	}

	prevc = c; // remember previous char

	return *this;
}

FontDefReader FontDefReader::operator++(int nothing) {
	FontDefReader tmp(*this);
	++*this;
	return tmp;
}

FontDefReader::operator bool() const {
	return data.charval != -1;
}
