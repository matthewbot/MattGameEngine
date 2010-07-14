#ifndef MGE_FS_IMPL_H
#define MGE_FS_IMPL_H

#include <physfs.h>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

namespace mge {
	class PhysFSStreamBufBase : public std::streambuf {
		public:
			PhysFSStreamBufBase(PHYSFS_File *file, size_t bufsize);
			virtual ~PhysFSStreamBufBase();

		protected:
			virtual std::streampos seekoff(std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which = std::ios_base::in|std::ios_base::out);
			virtual std::streampos seekpos(std::streampos sp, std::ios_base::openmode which = std::ios_base::in|std::ios_base::out);

			virtual void clearBuf() = 0;

			PHYSFS_File *file;
			std::vector<char> bufdata;
	};

	class PhysFSIStreamBuf : public PhysFSStreamBufBase {
		public:
			PhysFSIStreamBuf(PHYSFS_File *file, size_t bufsize, size_t putsize);

		protected:
			virtual int underflow();

			virtual void clearBuf();

		private:
			size_t putsize; // putback size
	};

	class PhysFSIStream : public std::istream {
		public:
			PhysFSIStream(PHYSFS_File *file, size_t bufsize);
			virtual ~PhysFSIStream();

		private:
			PhysFSIStreamBuf buf;
	};

	class PhysFSOStreamBuf : public PhysFSStreamBufBase {
		public:
			PhysFSOStreamBuf(PHYSFS_File *file, size_t bufsize);

		protected:
			virtual int sync();
			virtual int overflow(int c);
			
			virtual void clearBuf();
	};

	class PhysFSOStream : public std::ostream {
		public:
			PhysFSOStream(PHYSFS_File *file, size_t bufsize);
			virtual ~PhysFSOStream();

		private:
			PhysFSOStreamBuf buf;
	};
}

#endif
