#ifndef MGE_GFX_SHADERMANAGER_H
#define MGE_GFX_SHADERMANAGER_H

#include "ShaderName.h"
#include "ShaderProgram.h"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <map>
#include <string>

namespace mge {
	class Logger;
	class FileStreamProducer;

	class ShaderManager : boost::noncopyable {
		friend class GraphicsSystem;
		friend class ShaderDeleter;
	
		public:
			boost::shared_ptr<ShaderProgram> getProgram(const ShaderName &name);
			
		private:
			ShaderManager(Logger &logger, FileStreamProducer &fsp, Renderer &renderer);
			
			typedef std::map<ShaderName, boost::weak_ptr<ShaderProgram> > ShaderCache;
			ShaderCache shadercache;
			Logger &logger;
			FileStreamProducer &fsp;
			Renderer &renderer;
			
			bool compileShader(int id, const std::string &name);
			
	};
}

#endif
