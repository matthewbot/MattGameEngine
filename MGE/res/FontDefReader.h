#ifndef MGE_RES_FONTDEFREADER_H
#define MGE_RES_FONTDEFREADER_H

#include <cassert>
#include <string>
#include "FontDef.h"

namespace mge {
	class FontData {
		friend class FontDefReader;
	
		public:
			inline const FontChar &getChar() const { assert(fc); return *fc; }
			inline bool hasKerning() const { return (fk != 0); }
			inline float getKerning() const { assert(fk); return fk->amount; }
			inline int getCharValue() const { return charval; }
			
		private:
			const FontChar *fc; // rendering information for the character
			const FontKerning *fk; // kerning information for the character
			int charval; // the value of the character
	};

	// this is an iterator of sorts that generates FontData given a FontDef and a string
	// you create this with its constructor, no .begin() method.
	// you also must use its bool conversion operator to test for the end of the string

	class FontDefReader {
		public:
			FontDefReader(const FontDef &def, const std::string &str);

			FontDefReader& operator++();
			FontDefReader operator++(int i);

			inline const FontData& operator*() const { return data; }
			inline const FontData* operator->() const { return &data; }
			operator bool() const;

		private:
			void updateData();

			const FontDef &def;
			const std::string &str;
			std::string::const_iterator iter;
			int prevc;
			FontData data;
	};
}

#endif
