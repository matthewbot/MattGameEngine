#include "Blob.h"
#include <cmath>
#include <cstring>

using namespace std;
using namespace mge;

Blob::Blob() {
	length = pos = limit = 0;
	data = NULL;
}

Blob::Blob(int s) {
	data = new char [s];
	length = limit = s;
	pos = 0;
}

Blob::Blob(const Blob &b) {
	if (b.length > 0) {
		length = b.length;
		pos = b.pos;
		limit = b.limit;

		data = new char [length];
		memcpy(data, b.data, length);
	} else {
		length = pos = limit = 0;
		data = NULL;
	}
}

Blob::Blob(const char *d, int s) {
	data = new char [s];
	memcpy(data, d, s);

	length = limit = s;
	pos = 0;
}

Blob::~Blob() {
	delete data;
}

Blob &Blob::operator=(const Blob &b) {
	if (length != b.length) {
		delete data;
		data = new char [b.length];
	}

	length = b.length;
	pos = b.pos;
	limit = b.limit;

	memcpy(data, b.data, length);

	return *this;
}

void Blob::clear() {
	pos = 0;
	limit = length;
}

void Blob::flip() {
	limit = pos;
	pos = 0;
}

void Blob::resize(int newlength, bool preserve) {
	if (!data) { // if we currently have no data
		data = new char [newlength]; // allocate
		limit = length = newlength;
		return; // and we're done
	}
	
	if (length == newlength) // if the size doesn't need to change
		return; // nothing to do
	
	if (preserve) { 
		char *datatmp = new char [newlength];
		memcpy(datatmp, data, min(length, newlength));
		delete data;
		data = datatmp;
	} else {
		delete data;
		data = new char [newlength];
	}

	pos = min(pos, newlength); // adjust positions and variables
	limit = min(pos, newlength);
	length = newlength;
}

float Blob::getShortFloat(int dec) {
	short val = get<short>();
	return (float)val * pow((float)10, dec);
}

void Blob::putShortFloat(int dec, float fval) {
	short val = (short)(fval / pow((float)10, dec));
	put<short>(val);
}

void Blob::put(const char *newdata, int newlength) {
	memcpy(data+pos, newdata, newlength);
	pos += newlength;
}

void Blob::get(char *outdata, int outlength) {
	memcpy(outdata, data+pos, outlength);
	pos += outlength;
}

string Blob::getString() {
	int length = get<unsigned char>();
	string ret(data+pos, length);
	pos += length;
	return ret;
}

void Blob::putString(const std::string &str) {
	int length = str.size();
	put((unsigned char)length);
	memcpy(data+pos, str.c_str(), length);
	pos += length;
}

void Blob::copyFrom(const Blob &blob, int amt) {
	memcpy(data+pos, blob.data+blob.pos, amt);
	pos += amt;
}

ostream &mge::operator<<(ostream &out, const Blob &blob) {
    int i;
    for (i=0;i<blob.getLength();i++) {
    	out << (int)blob[i] << " ";
    }
    
    return out;
}

