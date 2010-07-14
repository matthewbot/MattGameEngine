#include "ShaderVariableValue.h"
#include <cstring>

using namespace mge;

ShaderVariableValue::ShaderVariableValue(float val) : datacount(1) { data[0] = val; }
ShaderVariableValue::ShaderVariableValue(float val, float val2) : datacount(2) { 
	data[0] = val; data[1] = val2;
}
ShaderVariableValue::ShaderVariableValue(float val, float val2, float val3) : datacount(3) { 
	data[0] = val; data[1] = val2; data[2] = val3;
}
ShaderVariableValue::ShaderVariableValue(float val, float val2, float val3, float val4) : datacount(4) {
	data[0] = val; data[1] = val2; data[2] = val3; data[3] = val4;
}
ShaderVariableValue::ShaderVariableValue(const float vals[], int count) : datacount(count) {
	memcpy(data, vals, datacount*sizeof(float));
}
ShaderVariableValue::ShaderVariableValue(const ShaderVariableValue &val) {
	*this = val;
}

const ShaderVariableValue &ShaderVariableValue::operator=(const ShaderVariableValue &val) {
	datacount = val.datacount;
	memcpy(data, val.data, datacount*sizeof(float));
	
	return *this;
}

bool ShaderVariableValue::operator==(const ShaderVariableValue &val) const {
	if (datacount != val.datacount)
		return false;
		
	if (memcmp(data, val.data, datacount*sizeof(float)) != 0)
		return false;
		
	return true;
}

