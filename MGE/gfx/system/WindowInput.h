#ifndef MGE_GFX_WINDOWINPUT_H
#define MGE_GFX_WINDOWINPUT_H

#include <MGE/util/input/InputDispatcher.h>
#include <map>

namespace mge {
	class WindowInput {
		public:
			WindowInput(int width, int height);
		
			inline void addInputListener(InputListener &listener) { dispatch.add(listener); }
			inline void removeInputListener(InputListener &listener) { dispatch.remove(listener); }
		
			void update(); 
			
		private:			
			int width, height;
			InputDispatcher dispatch;

			class KeyCodeConvertor {
				public:
					KeyCodeConvertor();

					KeyCode operator()(int SDLKey) const;
				private:
					typedef std::map<int, KeyCode> LookupMap;
					LookupMap lookup;
			};

			static const KeyCodeConvertor convertKey;
	};
}

#endif
