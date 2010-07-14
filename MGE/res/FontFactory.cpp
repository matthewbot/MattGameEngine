#include "FontFactory.h"
#include "FontDef.h"
#include "Font.h"
#include <MGE/res/system/ResourceNode.h>
#include <MGE/gfx/texture/TextureManager.h>
#include <MGE/util/Tokenizer.h>
#include <MGE/util/FileStreamProducer.h>
#include <memory>

using namespace std;
using namespace mge;
using namespace boost;

FontFactory::FontFactory(TextureManager &texman, FileStreamProducer &fsp) : texman(texman), fsp(fsp) { }

Resource *FontFactory::makeResource(const std::string &name, const ResourceNode &props) {
	if (props.getString("type") != "font")
		return NULL;

	string fntname = props.getString("fntname");
	string texname = props.getString("texname");

	std::auto_ptr<FontDef> def(parseFnt(fntname));
	shared_ptr<Texture> tex = texman.loadTexture(texname);

	return new Font(def, tex, name);
}

static int parseKeyInt(StreamTokenizer *tokenizer, const char *key) {
	if (tokenizer->nextToken() != StreamTokenizer::WORD || tokenizer->strValue() != key)
		throw Exception(string("Error parsing fnt: expected ") + key);
	if (tokenizer->nextToken() != StreamTokenizer::EQUALS)
		throw Exception(string("Error parsing fnt: expected equals after ") + key);
	if (tokenizer->nextToken() != StreamTokenizer::INTNUM)
		throw Exception(string("Error parsing fnt: expected number after ") + key + string("="));

	return tokenizer->intValue();
}

static inline float parseKeyFloat(StreamTokenizer *tokenizer, const char *key) {
	return (float)parseKeyInt(tokenizer, key);
}

auto_ptr<FontDef> FontFactory::parseFnt(const string &fname) {
	auto_ptr<istream> stream(fsp.readFile(fname));
	StreamTokenizer tokenizer(*stream);
	auto_ptr<FontDef> def(new FontDef());

	while (true) {
		int tok = tokenizer.nextToken();

		if (tok == StreamTokenizer::WORD) {
			if (tokenizer.strValue() == "common") {
				def->lineheight = parseKeyInt(&tokenizer, "lineHeight");
			} else if (tokenizer.strValue() == "char") {
				FontChar schar;

				schar.id = parseKeyInt(&tokenizer, "id");
				schar.x = parseKeyFloat(&tokenizer, "x");
				schar.y = parseKeyFloat(&tokenizer, "y");
				schar.width = parseKeyFloat(&tokenizer, "width");
				schar.height = parseKeyFloat(&tokenizer, "height");
				schar.xoffset = parseKeyFloat(&tokenizer, "xoffset");
				schar.yoffset = parseKeyFloat(&tokenizer, "yoffset");
				schar.xadvance = parseKeyFloat(&tokenizer, "xadvance");

				def->chars[schar.id] = schar;
			} else if (tokenizer.strValue() == "kerning") {
				FontKerning skern;

				skern.first = parseKeyInt(&tokenizer, "first");
				skern.second = parseKeyInt(&tokenizer, "second");
				skern.amount = parseKeyFloat(&tokenizer, "amount");

				def->kernings[make_pair(skern.first, skern.second)] = skern;
			}

			do {
				tok = tokenizer.nextToken();
			} while (tok != StreamTokenizer::NEWLINE && tok != StreamTokenizer::END);
		} else if (tok == StreamTokenizer::END) {
			break;
		} else {
			throw Exception("Unexpected token at beginning of line");
		}
	}

	return def;
}
