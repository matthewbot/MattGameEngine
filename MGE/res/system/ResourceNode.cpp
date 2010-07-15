#include "ResourceNode.h"
#include <MGE/util/Exception.h>

using namespace mge;
using namespace std;

ResourceNode::ResourceNode() {
	valtype = INT;
	val.i = 0;
}
ResourceNode::ResourceNode(const ResourceNode &val) {
	valtype = INT;
	*this = val;
}
ResourceNode::ResourceNode(const ListType &map) {
	valtype = LIST;
	val.l = new ListType(map);
	listcache = 0;
}
ResourceNode::ResourceNode(int i) {
	valtype = INT;
	val.i = i;
}
ResourceNode::ResourceNode(float f) {
	valtype = FLOAT;
	val.f = f;
}
ResourceNode::ResourceNode(const string &str) {
	valtype = STRING;
	val.s = new string(str);
}

ResourceNode::~ResourceNode() {
	if (valtype == STRING)
		delete val.s;
	else if (valtype == LIST) {
		delete listcache;
		delete val.l;
	}
}

ResourceNode& ResourceNode::operator=(const ResourceNode &n) {
	if ((valtype == INT || valtype == FLOAT) && (n.valtype == INT) || (n.valtype == FLOAT)) { // if we're both a primitive
		val = n.val; // copy the bits
	} else if (valtype == STRING && n.valtype == STRING) { // if we're both strings
		*val.s = *n.val.s; // copy the strings
	} else if (valtype == LIST && n.valtype == LIST) { // if we're both lists
		*val.l = *n.val.l; // copy the list
		if (listcache) {
			delete listcache; // invalidate our cache
			listcache = NULL; 
		}
	} else if (valtype == INT || valtype == FLOAT) { // if we're a primitive
		if (n.valtype == STRING) { // and they're a string
			val.s = new string(*n.val.s); // allocate a copy
		} else if (n.valtype == LIST) { // if they're a map
			val.l = new ListType(*n.val.l); // allocate a copy
			listcache = NULL;
		} else
			throw Exception("Bad valtype?");
	} else { // else, they're a primitive
		if (valtype == STRING) // if we're a string
			delete val.s;
		else if (valtype == LIST) {
			delete val.l;
			delete listcache;
		} else
			throw Exception("Bad valtype?");

		val = n.val;
	}

	valtype = n.valtype;
	return *this;
}	

int ResourceNode::toInt() const {
	switch (valtype) {
		case STRING:
			throw Exception(string("Can't convert string resource node to int"));

		case INT:
			return val.i;

		case FLOAT:
			throw Exception(string("Can't convert float resource node to int"));

		case LIST:
			throw Exception(string("Can't convert list resource node to int"));

		default:
			throw Exception("Bad valtype?");
	}
}

float ResourceNode::toFloat() const {
	switch (valtype) {
		case STRING:
			throw Exception(string("Can't convert string resource node to float"));

		case INT:
			return (float)val.i;

		case FLOAT:
			return val.f;

		case LIST:
			throw Exception(string("Can't convert list resource node to float"));

		default:
			throw Exception("Bad valtype?");
	}
}

const string &ResourceNode::toString() const {
	switch (valtype) {
		case STRING:
			return *val.s;

		case INT:
			throw Exception("Can't convert int resource node to string");

		case FLOAT:
			throw Exception("Can't convert float resource node to string");

		case LIST:
			throw Exception("Can't convert list resource node to string");

		default:
			throw Exception("Bad valtype?");
	}
}

ResourceNode::CacheMap::iterator ResourceNode::lookup(const std::string &key) const {
	if (!listcache) {
		listcache = new CacheMap();
		for (ListType::iterator i = val.l->begin(); i != val.l->end(); ++i) {
			listcache->insert(make_pair(i->first, i));
		}
	}

	return listcache->find(key);
}

bool ResourceNode::has(const std::string &key) const {
	CacheMap::iterator i = lookup(key);
	return i != listcache->end();
}

int ResourceNode::getInt(const std::string &key) const {
	return get(key).toInt();
}

int ResourceNode::getInt(const std::string &key, int def) const {
	if (valtype != LIST)
		throw Exception("Can't retrieve value from non-list resource node");

	CacheMap::iterator i = lookup(key);
	if (i != listcache->end())
		return i->second->second.toInt();
	else
		return def;
}

float ResourceNode::getFloat(const std::string &key) const {
	return get(key).toFloat();
}

float ResourceNode::getFloat(const std::string &key, float def) const {
	if (valtype != LIST)
		throw Exception("Can't retrieve value from non-list resource node");

	CacheMap::iterator i = lookup(key);
	if (i != listcache->end())
		return i->second->second.toFloat();
	else
		return def;
}

const std::string &ResourceNode::getString(const std::string &key) const {
	return get(key).toString();
}

const std::string ResourceNode::getString(const std::string &key, const std::string &def) const {
	if (valtype != LIST)
		throw Exception("Can't retrieve value from non-list resource node");

	CacheMap::iterator i = lookup(key);
	if (i != listcache->end())
		return i->second->second.toString();
	else
		return def;
}

const ResourceNode &ResourceNode::get(const std::string &key) const {
	if (valtype != LIST)
		throw Exception("Can't retrieve value from non-list resource node");

	CacheMap::iterator i = lookup(key);
	if (i != listcache->end())
		return i->second->second;
	else
		throw Exception(string("ResourceNode contains no child named ") + key);
}

void ResourceNode::set(const std::string &key, const ResourceNode &node) {
	if (valtype != LIST)
		throw Exception("Can't set field on list resource");
		
	CacheMap::iterator i = lookup(key);
	if (i != listcache->end())
		i->second->second = node;
	else {
		ListType::iterator i = val.l->insert(val.l->end(), make_pair(key, node));
		listcache->insert(make_pair(key,i));
	}
}

void ResourceNode::mergeWith(const ResourceNode &other) {
	if (valtype != LIST || other.valtype != LIST)
		throw Exception("Can only merge two list resource nodes");

	val.l->insert(val.l->end(), other.val.l->begin(), other.val.l->end());
}

ResourceNode::const_iterator ResourceNode::begin() const {
	if (valtype != LIST)
		throw Exception("Can't retrieve iterator for non-list resource node");

	return val.l->begin();
}

ResourceNode::const_iterator ResourceNode::end() const {
	return val.l->end();
}

ostream &mge::operator<<(ostream &stream, const ResourceNode &node) {
	node.output(stream, 0);
	return stream;
}

void ResourceNode::output(ostream &stream, int indent) const {
	switch (valtype) {
		case INT:
			stream << val.i;
			break;
			
		case FLOAT:
			stream << val.f;
			break;
			
		case STRING:
			if (val.s->find(' ') != string::npos)
				stream << '"' << *val.s << '"';
			else
				stream << *val.s;
			break;
			
		case LIST: 
			{
				string indstr(indent+2, ' ');
			
				stream << "{" << endl;
				for (ListType::const_iterator i = val.l->begin(); i != val.l->end(); ++i) {
					stream << indstr << i->first << " ";
					i->second.output(stream, indent+2);
					stream << endl;
				};
				stream << string(indent, ' ') << "}";
			
				break;
			}
	}
}
		
