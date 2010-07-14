#ifndef MGE_RES_SHADER_H
#define MGE_RES_SHADER_H

#include "Resource.h"
#include <boost/shared_ptr.hpp>

namespace mge {
	class ShaderProgram;

	class Shader : public Resource {
		public:
			Shader(const std::string &name, const boost::shared_ptr<ShaderProgram> &prgm);
		
			inline const boost::shared_ptr<ShaderProgram> &getProgram() { return prgm; }
		
		private:
			boost::shared_ptr<ShaderProgram> prgm;
	};
}


#endif
