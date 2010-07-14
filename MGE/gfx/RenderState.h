#ifndef MGE_GFX_RENDERSTATE_H
#define MGE_GFX_RENDERSTATE_H

#include "util.h"
#include <MGE/gfx/shader/ShaderVariableValue.h>
#include <boost/shared_ptr.hpp>
#include <map>

namespace mge {
	class ShaderProgram;
	class ShaderVariable;
	class Texture;

	class RenderState {
		typedef std::map<const ShaderVariable *, ShaderVariableValue> ProgramVariableMap;
	
		public:
			RenderState();

			RenderState &program(const boost::shared_ptr<ShaderProgram> &program);
			RenderState &programVar(const std::string &varname, const ShaderVariableValue &val);
			RenderState &texture(const boost::shared_ptr<Texture> &tex, int id=0);
			RenderState &clearTexture(int id=0);
			RenderState &pointSize(float pointsize);

			bool operator==(const RenderState &state) const;
			inline bool operator!=(const RenderState &state) const { return !(*this == state); }

			inline const boost::shared_ptr<ShaderProgram> &getProgram() const { return prgm; }				
			inline const boost::shared_ptr<Texture> &getTexture(int id=0) const { return texes[id]; }			
			inline float getPointSize() const { return pointsize; }
			
			typedef ProgramVariableMap::const_iterator ProgramVariableIterator;
			
			inline ProgramVariableIterator beginPVars() const { return prgmvars.begin(); }
			inline ProgramVariableIterator endPVars() const { return prgmvars.end(); }

		private:
			boost::shared_ptr<Texture> texes[MAX_TEXES]; // textures
			boost::shared_ptr<ShaderProgram> prgm; // program
			ProgramVariableMap prgmvars; // program variables
			float pointsize;
	};
}

#endif
