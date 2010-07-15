#ifndef MGE_RES_RESOURCENODE_H
#define MGE_RES_RESOURCENODE_H

#include <list>
#include <string>
#include <map>
#include <ostream>

namespace mge {
	class ResourceNode {
		public:
			typedef std::list<std::pair<std::string, ResourceNode> > ListType;
			typedef ListType::const_iterator const_iterator;
		
			ResourceNode();
			ResourceNode(const ResourceNode &node);
			ResourceNode(const ListType &type);
			ResourceNode(int i);
			ResourceNode(float f);
			ResourceNode(const std::string &str);
			~ResourceNode();
			
			ResourceNode &operator=(const ResourceNode &node);
			
			int toInt() const;
			float toFloat() const;
			const std::string &toString() const;
			
			enum ValType { INT, FLOAT, STRING, LIST };
			inline ValType getType() const { return valtype; }
			
			// TODO
			/*void setInt(int i);
			void setFloat(float f);
			void setString(const std::string &str);*/
			
			bool has(const std::string &key) const;
			const ResourceNode &get(const std::string &key) const;
			int getInt(const std::string &key) const;
			int getInt(const std::string &key, int def) const;
			float getFloat(const std::string &key) const;
			float getFloat(const std::string &key, float def) const;
			const std::string &getString(const std::string &key) const;
			const std::string getString(const std::string &key, const std::string &def) const;
			
			void set(const std::string &key, const ResourceNode &val);
			
			void mergeWith(const ResourceNode &node);
			
			const_iterator begin() const;
			const_iterator end() const;
			
			void output(std::ostream &ostream, int indent) const;
			
		private:
			typedef std::map<std::string, ListType::iterator> CacheMap;
			
			CacheMap::iterator lookup(const std::string &key) const;
			
			ValType valtype;
			union {
				int i;
				float f;
				std::string *s;
				ListType *l;
			} val;
			
			mutable CacheMap *listcache;
	};
	
	std::ostream &operator<<(std::ostream &ostream, const ResourceNode &node);
	
}

#endif
