#ifndef MGE_UTIL_SFSP_H
#define MGE_UTIL_SFSP_H

#include <MGE/util/FileStreamProducer.h>

namespace mge {
  class StandardFileStreamProducer : public FileStreamProducer {
    public:
      StandardFileStreamProducer();
	virtual ~StandardFileStreamProducer();
	  
	  virtual std::istream *readFile(const std::string &str);
	    virtual std::ostream *writeFile(const std::string &str);
	      virtual std::time_t getModTime(const std::string &str);
		
		static StandardFileStreamProducer inst;
		  };
}

#endif
