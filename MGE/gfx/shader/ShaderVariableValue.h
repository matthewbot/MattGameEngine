#ifndef MGE_GFX_SHADERVARIABLEVALUE_H
#define MGE_GFX_SHADERVARIABLEVALUE_H

namespace mge {
	class ShaderVariableValue {
		public:
			inline ShaderVariableValue() : datacount(0) { }
			ShaderVariableValue(float val);
			ShaderVariableValue(float val, float val2);
			ShaderVariableValue(float val, float val2, float val3);
			ShaderVariableValue(float val, float val2, float val3, float val4);
			ShaderVariableValue(const float vals[], int count);
			ShaderVariableValue(const ShaderVariableValue &val);
			
			const ShaderVariableValue &operator=(const ShaderVariableValue &val);
			bool operator==(const ShaderVariableValue &val) const;
			
			inline int getCount() const { return datacount; }
			inline float *getData() { return data; }
			inline const float *getData() const { return data; }
			
			inline float &operator[](int pos) { return data[pos]; }
			inline float operator[](int pos) const { return data[pos]; }
	
		private:
			unsigned char datacount;
			float data[4];
	};
}


#endif
