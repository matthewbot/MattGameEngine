#include "ResourceSystem.h"
#include "parser.h"
#include <MGE/util/Exception.h>
#include <MGE/util/algorithm.h>
#include <MGE/util/FileStreamProducer.h>
#include <MGE/util/Logger.h>
#include <boost/scoped_ptr.hpp>

using namespace mge;
using namespace std;
using namespace boost;

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

ResourceSystem::ResourceSystem(FileStreamProducer &fsp, Logger &log) 
: fsp(fsp), log(log), props(ResourceNode::ListType()) { }

ResourceSystem::~ResourceSystem() { }

void ResourceSystem::registerResourceFactory(ResourceFactory *fact) {
	factories.push_back(fact);
}

void ResourceSystem::mergeProperties(const ResourceNode &val) {
	props.mergeWith(val);
}

void ResourceSystem::loadFile(const string &name) {
	string basedir = name.substr(0, name.rfind('/')+1);

	pair<ResourceNode, vector<string> > result;
	try {
		scoped_ptr<istream> file(fsp.readFile(name));
		result = parseResourceFile(*file);
	} catch (Exception &ex) {
		throw Exception(string("Got exception while parsing resource file ") + name + string(": ") + string(ex.what()));
	}

	mergeProperties(result.first);

	log.log("res", DEBUG) << "Loaded resource file " << name << endl;

	typedef vector<string> FileList;
	FileList &files = result.second;
	for (FileList::iterator i = files.begin(); i != files.end(); ++i) {
		loadFile(basedir + *i);
	}
}

shared_ptr<Resource> ResourceSystem::getResource(const string &name) const {
	ResourceCacheMap::iterator cacheptr = cache.find(name); // do a cache lookup
	if (cacheptr != cache.end()) { // if we got it
		shared_ptr<Resource> res(cacheptr->second.lock()); // try to lock the weak ptr
		
		if (res) // got that too?
			return res; // return it
	}
	
	const ResourceNode &propval = props.get(name);
	
	Resource *res=NULL;
	for (ResourceFactoryList::const_iterator i = factories.begin(); i != factories.end(); i++) {
		res = (*i)->makeResource(name, propval);
		if (res != NULL)
			break;
	}

	if (res == NULL)
		throw Exception(string("No ResourceFactory could create resource ") + name);

	shared_ptr<Resource> resptr(res);
	cache[name] = resptr;

	return resptr;
	
}

const char *ResourceSystem::getName() const { return "ResourceSystem"; }
	
