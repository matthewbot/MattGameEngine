#ifndef MGE_UTIL_BLOB_H
#define MGE_UTIL_BLOB_H

#include <string>
#include <ostream>

namespace mge {
	class Blob {
		public:
			Blob();
			Blob(const Blob &b);
			Blob(int size);
			Blob(const char *data, int size);
			~Blob();

			Blob &operator=(const Blob &b);
			inline Blob clone() const { return Blob(*this); }
			
			inline int getRemaining() const { return limit-pos; }
			inline char *get() { return data+pos; }
			inline char &operator[](int pos) { return data[pos]; }
			inline const char *get() const { return data+pos; }
			inline char operator[](int pos) const { return data[pos]; }

			inline int getPos() const { return pos; }
			inline void setPos(int newpos) { pos = newpos; }
			inline int getLimit() const { return limit; }
			inline void setLimit(int newlimit) { limit = newlimit; }
			inline int getLength() const { return length; }

			void flip();
			void clear();
			void resize(int length, bool preserve=true);

			template <typename ValType> ValType get() {
				ValType val = *reinterpret_cast<ValType *>(data + pos); // yeah, we don't use network byte order. To spite me, one day this will have to run on some big-endian server.
				pos += sizeof(ValType);
				return val;
			}

			template <typename ValType> void put(ValType val) {
				*reinterpret_cast<ValType *>(data + pos) = val;
				pos += sizeof(ValType);
			}

			void put(const char *data, int length);
			void get(char *data, int length);
			
			void getFrom(mge::Blob &blob, int amt=0);
			inline void putTo(mge::Blob &blob, int amt=0) { blob.getFrom(*this, amt); }
			
			void copyFrom(const mge::Blob &blob, int amt=0);
			inline void copyTo(mge::Blob &blob, int amt=0) const { blob.copyFrom(*this, amt); }

			float getShortFloat(int dec);
			void putShortFloat(int dec, float val);

			std::string getString();
			void putString(const std::string &str);
			
		private:
			char *data; int length;

			int pos, limit;
	};	
	
	std::ostream &operator<<(std::ostream &os, const Blob &blob);
}			

#endif
