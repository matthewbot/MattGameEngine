#include "Texture.h"
#include <string>
#include <GL/glew.h>

using namespace std;
using namespace mge;

Texture::Texture(int width, int height, int twidth, int theight, const std::string &name, TexFlags flags) 
: width(width), height(height), twidth(twidth), theight(theight), name(name), flags(flags)
{ 
	GLuint glid;
	glGenTextures(1, &glid);
  id = glid;
}

Texture::~Texture() {
	GLuint glid = id;
	glDeleteTextures(1, &glid);
}
