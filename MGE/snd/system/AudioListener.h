#ifndef MGE_SND_AUDIOLISTENER_H
#define MGE_SND_AUDIOLISTENER_H

namespace mge {
	class AudioListener {
		friend class AudioSystem;
		public:
			inline float getX() const { return xpos; }
			inline float getY() const { return ypos; }
			inline float getRotation() const { return rot; }
			inline float getGain() const { return gain; }

			void setPos(float x, float y);
			void setRotation(float rot);
			void setGain(float gain);

		private:
			float xpos, ypos;
			float rot;
			float gain;

			AudioListener();
	};
}

#endif
