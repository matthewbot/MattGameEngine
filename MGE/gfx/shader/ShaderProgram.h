#ifndef MGE_GFX_SHADERPROGRAM_H
#define MGE_GFX_SHADERPROGRAM_H

#include "ShaderName.h"
#include <boost/noncopyable.hpp>
#include <string>
#include <map>

namespace mge {
	class Renderer;
	class ShaderVariable;

	class ShaderProgram : public boost::noncopyable {
		friend class ShaderManager;
		
		public:		
			~ShaderProgram();
		
			std::string getPixelShaderLog() const;
			std::string getVertexShaderLog() const;
			std::string getProgramLog() const;
			std::string getLog() const;
			
			inline const ShaderName &getName() const { return name; }
			inline int getID() const { return programid; }
			const ShaderVariable &getVariable(const std::string &name) const;
			
		private:
			ShaderProgram(const ShaderName &name);
			
			void generateTexUniforms(Renderer &renderer);
			
			int programid;
			int pshaderid;
			int vshaderid;
			ShaderName name;
			
			typedef std::map<std::string, ShaderVariable *> ShaderVariableMap;
			mutable ShaderVariableMap varcache;
	};
}

#endif
