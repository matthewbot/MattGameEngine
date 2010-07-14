#ifndef MGE_GFX_SHADERNAME_H
#define MGE_GFX_SHADERNAME_H

#include <string>
#include <ostream>

namespace mge {
	class ShaderName {
		public:
			ShaderName(const std::string &pixshader, const std::string &vertshader);
		
			inline const std::string &getPixelShader() const { return pixshader; }
			inline const std::string &getVertexShader() const { return vertshader; }
			
			bool operator==(const ShaderName &name) const;
			bool operator<(const ShaderName &name) const;
		
		private:
			std::string pixshader, vertshader;
	};
	
	std::ostream &operator<<(std::ostream &stream, const ShaderName &name);
}

#endif
