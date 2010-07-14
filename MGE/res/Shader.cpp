#include "Shader.h"
#include <MGE/gfx/shader/ShaderProgram.h>

using namespace mge;
using namespace std;
using namespace boost;

Shader::Shader(const string &name, const shared_ptr<ShaderProgram> &prgm) : Resource(name), prgm(prgm) { }
