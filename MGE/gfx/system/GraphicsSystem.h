#ifndef MGE_GFX_GRAPHICSSYSTEM_H
#define MGE_GFX_GRAPHICSSYSTEM_H

#include <MGE/kernel/KernelSystem.h>
#include "Display.h"
#include "WindowInput.h"
#include "Timer.h"
#include <MGE/gfx/renderer/RenderManager.h>
#include <MGE/gfx/texture/TextureManager.h>
#include <MGE/gfx/shader/ShaderManager.h>
#include <MGE/gfx/renderer/Renderer.h>
#include <string>

namespace mge {
	class Logger;
	class FileStreamProducer;

	class GraphicsSystem : public KernelSystem {
	public:
		GraphicsSystem(Logger &logger, FileStreamProducer &fsp, int w, int h, bool vsync, const std::string &title);

		inline Timer &getTimer() { return timer; }
		inline Display &getDisplay() { return display; }
		inline TextureManager &getTextureManager() { return texman; }
		inline RenderManager &getRenderManager() { return rendman; }
		inline WindowInput &getWindowInput() { return input; }
		inline ShaderManager &getShaderManager() { return shade; }
		
		inline const Timer &getTimer() const { return timer; }
		inline const Display &getDisplay() const { return display; }
		inline const TextureManager &getTextureManager() const { return texman; }
		inline const RenderManager &getRenderManager() const { return rendman; }
		inline const WindowInput &getWindowInput() const { return input; }
		inline const ShaderManager &getShaderManager() const { return shade; }
		inline const RenderStats &getStats() { return renderer.getStats(); }
		
		// KernelSystem

		virtual const char *getName() const;
		virtual SystemUpdateValue update();

	private:
		struct SubSystemHandler {
			SubSystemHandler(Logger &logger, int w, int h, bool vsync, const std::string &title);
			~SubSystemHandler();
		} subsystem;
		
		Timer timer;
		WindowInput input;
		Renderer renderer;
		RenderManager rendman;
		TextureManager texman;
		ShaderManager shade;
		Display display;
	};

}

#endif
