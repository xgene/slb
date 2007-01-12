#ifndef __SLB_MANAGER__
#define __SLB_MANAGER__

#include "Object.hpp"
#include "ref_ptr.hpp"
#include "Export.hpp"
#include <typeinfo>
#include <map>

namespace SLB {

	class ClassInfo;
	class Namespace;

	class SLB_EXPORT Manager : public virtual Object
	{
	public:
		typedef std::map< const std::type_info*, ref_ptr<ClassInfo> > ClassMap;
		typedef std::map< const std::string, const std::type_info *> NameMap;

		static Manager &getInstance();
		static Manager *getInstancePtr();

		const ClassInfo *getClass(const std::type_info&) const;
		const ClassInfo *getClass(const std::string&) const;
		ClassInfo *getClass(const std::type_info&);
		ClassInfo *getClass(const std::string&);
		ClassInfo *getOrCreateClass(const std::type_info &);

		// set a global value ( will be registered authomatically on every lua_State )
		void set(const std::string &, Object *obj);

		void registerSLB(lua_State *L);

	protected:

		Manager();
		virtual ~Manager();

		void pushImplementation(lua_State *L);
		void setName( const std::string &old, const std::string &new_name, const std::type_info*);
		void addClass( ClassInfo *c );

	private:
		Manager(const Manager&);
		Manager& operator=(const Manager&);

		static ref_ptr<Manager> _instance;
		ClassMap _classes;
		NameMap  _names;
		ref_ptr<Namespace> _global;

		friend class ClassInfo;
	};
	
	//--------------------------------------------------------------------
	// Inline implementations:
	//--------------------------------------------------------------------
	
	inline Manager &Manager::getInstance()
	{
		return *getInstancePtr();
	}
}

#endif
