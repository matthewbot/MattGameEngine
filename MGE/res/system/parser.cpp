#include "parser.h"
#include "ResourceNode.h"
#include <MGE/util/Tokenizer.h>

using namespace mge;
using namespace std;

static pair<string, ResourceNode> parseKeyValue(StreamTokenizer &tok);

static ResourceNode::ListType parseKeyValueMap(StreamTokenizer &tok) {
	ResourceNode::ListType vals;

	while (true) {
		StreamTokenizer::Token t = tok.nextToken();

		if (t == StreamTokenizer::CLOSE)
			break;
		else if (t == StreamTokenizer::NEWLINE)
			continue;
		else if (t == StreamTokenizer::HASH)
			while (tok.nextToken() != StreamTokenizer::NEWLINE) { }
		else {
			tok.backToken(t);
			vals.push_back(parseKeyValue(tok));
		}
	}

	return vals;
}

static pair<string, ResourceNode> parseKeyValue(StreamTokenizer &tok) {
	StreamTokenizer::Token t = tok.nextToken();
	if (t != StreamTokenizer::WORD)
		throw Exception("Expected word for resource node key");
	string key = tok.strValue();

	t = tok.nextToken();
	if (t == StreamTokenizer::EQUALS)
		t = tok.nextToken();
		
	StreamTokenizer::Token nextt = tok.nextToken();

	if (nextt == StreamTokenizer::HASH)
		while (tok.nextToken() != StreamTokenizer::NEWLINE) { }
	else if (nextt != StreamTokenizer::NEWLINE)
		throw Exception("Expected newline after key value");

	switch (t) {
		case StreamTokenizer::WORD:
		case StreamTokenizer::STRING:
			return make_pair(key, tok.strValue());
			
		case StreamTokenizer::INTNUM:
			return make_pair(key, tok.intValue());

		case StreamTokenizer::FLOATNUM:
			return make_pair(key, tok.floatValue());

		case StreamTokenizer::OPEN:
			return make_pair(key, parseKeyValueMap(tok));

		default:
			throw Exception(string("Unexpected token after key ") + key);
	}
}

pair<ResourceNode, vector<string> > mge::parseResourceFile(istream &stream) {
	StreamTokenizer tok(stream);
	ResourceNode::ListType vals;
	vector<string> files;

	while (true) {
		StreamTokenizer::Token t = tok.nextToken();
		if (t == StreamTokenizer::END)
			break;
		else if (t == StreamTokenizer::NEWLINE)
			continue;
		else if (t == StreamTokenizer::HASH)
			while (tok.nextToken() != StreamTokenizer::NEWLINE) { }
		else if (t == StreamTokenizer::COLON) {
			if (tok.nextToken() != StreamTokenizer::WORD || tok.strValue() != "import")
				throw Exception("Expected import after :");

			if (tok.nextToken() != StreamTokenizer::STRING)
				throw Exception("Expected file name as string after :import");

			files.push_back(tok.strValue());
		} else {
			tok.backToken(t);

			vals.push_back(parseKeyValue(tok));
		}
	}

	return make_pair(vals, files);
}
