#ifndef MGE_UTIL_TOKENIZER_H
#define MGE_UTIL_TOKENIZER_H

#include <string>
#include <cctype>
#include <sstream>
#include <cassert>
#include "Exception.h"
#include "IStreamRawIterator.h"
#include <iostream>

namespace mge {
	template <typename InputIterator> class Tokenizer {
		public:
			enum Token {
				INTNUM, FLOATNUM, WORD, STRING, OPEN, CLOSE, NEWLINE, EQUALS, COLON, COMMA, HASH, END
			};			
	
		private:
			InputIterator pos, end;
			
			std::string strvalue;
			int intvalue;
			float floatvalue;
		
			char bufchar;
			bool hasbufchar;
			
			Token buftoken;
			bool hasbuftoken;
			
			char getch() {
				if (hasbufchar) {
					hasbufchar = false;
					return bufchar;
				} else if (pos == end)
					return -1;
				else
					return (char)*pos++;
			}
			
			void ungetch(char val) {
				assert(!hasbufchar);
				bufchar = val;
				hasbufchar = true;
			}
	
			static bool isnumsymbol(char c) {
				return isdigit(c) || c == '.';
			}
			
			static bool iswordsymbol(char c) {
				return isalnum(c) || c == '_' || c == '.' || c == '/';
			}
	
		public:
			Tokenizer(const InputIterator &begin, const InputIterator &end) : pos(begin), end(end), hasbufchar(false), hasbuftoken(false) { }
			Tokenizer(const InputIterator &begin) : pos(begin), end(), hasbufchar(false), hasbuftoken(false) { }
			
			inline const std::string &strValue() const { return strvalue; }
			inline int intValue() const { return intvalue; }
			inline float floatValue() const { return floatvalue; }
			
			Token nextToken() {
				char got;
				
				if (hasbuftoken) {
					hasbuftoken = false;
					return buftoken;
				}
				
				do {
					got = getch();
					if (got == -1)
						return END;
					else if (got == '\n')
						return NEWLINE;
				} while (isspace(got));
				
				switch (got) {
					case '=':
						return EQUALS;
						
					case ':':
						return COLON;
						
					case '{':
						return OPEN;
						
					case '}':
						return CLOSE;
						
					case ',':
						return COMMA;
						
					case '#':
						return HASH;
				}
				
				if (got == '"') {
					std::stringstream buf;
					do {
						got = getch();
						
						if (got == -1)
							throw Exception("Got EOF before end quote");
						if (got == '"')
							break;

						buf << got;
					} while (true);
						
					strvalue = buf.str();
					return STRING;
				} else if (isnumsymbol(got) || got == '-') {
					std::stringstream buf;
					bool isfloat = false;
					
					if (got == '-')
						buf << "-";
					else
						ungetch(got);
		
					do {
						got = getch();
						
						if (!isnumsymbol(got))
							break;
							
						if (got == '.') {
							if (!isfloat)
								isfloat = true;
							else
								throw Exception("Two .s in number");
						}
						
						buf << got;
					} while (true);
					
					ungetch(got);
					
					if (isfloat) {
						buf >> floatvalue;
						return FLOATNUM;
					} else {
						buf >> intvalue;
						return INTNUM;
					}
				} else if (iswordsymbol(got)) {
					std::stringstream buf;
					buf << got;
					
					do {
						got = getch();
						
						if (!iswordsymbol(got))
							break;
							
						buf << got;
					} while (true);
					
					ungetch(got);
					
					strvalue = buf.str();
					return WORD;
				}
				
				std::stringstream buf;
				buf << "Bad token staring with " << got << " (" << (int)got << ")";
				
				throw Exception(buf.str());
			}
						
			void backToken(Token t) {
				assert(!hasbuftoken);
				hasbuftoken = true;
				buftoken = t;
			}
	};
	
	typedef Tokenizer<IStreamRawIterator> StreamTokenizer;
}

#endif
