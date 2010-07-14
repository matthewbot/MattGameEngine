#ifndef MGE_GFX_SHADERVARIABLE_H
#define MGE_GFX_SHADERVARIABLE_H

#include <boost/noncopyable.hpp>
#include <string>

namespace mge {
	class ShaderVariable : boost::noncopyable {
		friend class ShaderProgram;
	
		public:
			inline const std::string &getName() const { return name; }
			inline int getUniformID() const { return unifid; }
			inline int getProgramID() const { return prgmid; }
			
			inline bool operator<(const ShaderVariable &var) const { return unifid < var.unifid; }
			inline bool operator==(const ShaderVariable &var) const { return unifid == var.unifid; }
		
		private:
			inline ShaderVariable(int prgmid, int unifid, const std::string &name) : prgmid(prgmid), unifid(unifid), name(name) { }
			
			int prgmid;
			int unifid;
			std::string name;
	};
}

#endif
