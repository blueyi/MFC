
//
//  Generic Class Factory
//  (C) Robert A. T. Káldy <kaldy@matfyz.cz>
//  last updated on 17.4.2004


#if !defined(FACTORY_H)
#define FACTORY_H

#pragma warning(disable: 4786)

#include <map>
#include <exception>
#include <utility>
#include <typeinfo.h>


#define DECLARE_CLASS_FACTORY(factory)							\
	extern class_factory<void, int, empty_tag> factory;

#define DECLARE_CLASS_FACTORY_EX(Root, Key, Tag, factory)		\
	extern class_factory<Root, Key, Tag> factory;

#define DECLARE_CLASS_FACTORY_EXT(Root, factory)		\
	extern class_factory<Root, int, empty_tag> factory;

#define IMPLEMENT_CLASS_FACTORY(factory)						\
	class_factory<void, int, empty_tag> factory;				\
	int class_factory<void, int, empty_tag>::initial_lock;

#define IMPLEMENT_CLASS_FACTORY_EX(Root, Key, Tag, factory)		\
	class_factory<Root, Key, Tag> factory;						\
	int class_factory<Root, Key, Tag>::initial_lock;

#define IMPLEMENT_CLASS_FACTORY_EXT(Root, factory)		\
	class_factory<Root, int, empty_tag> factory;						\
	int class_factory<Root, int, empty_tag>::initial_lock;

#define REGISTER_CLASS(factory, class_name, key)				\
	class_factory_wrapper _register_class_##class_name((factory.register_class((class_name*)0, key), 0));

#define REGISTER_TAGGED_CLASS(factory, class_name, key, tag)	\
	class_factory_wrapper _register_class_##class_name((factory.register_class((class_name*)0, key, tag), 0));

#define SET_TAG_PROPERTY(factory, class_name, property, value)	\
	class_factory_wrapper _set_tag_property_##class_name##property((factory.tag_ref(typeid(class_name)).property = value, 0));


class not_registered : public std::exception
{
public:
	virtual const char* what() const
	{
		return "Class/key not registered";
	}
};

template<class Root, class T>
class class_creator
{
public:
	static Root* create()
	{
		return new T;
	}
};

template<class Root, class Key, class Tag>
class class_info
{
public:
	Key key;
	Tag tag;
	Root* (*create)();
};

class empty_tag
{};

class class_factory_wrapper
{
public:
	class_factory_wrapper(int)								{}
};


template<class Root, class Key = int, class Tag = empty_tag>
class class_factory
{
	typename typedef class_info<Root, Key, Tag> class_info_type;
	typename typedef std::map<const type_info*, class_info_type>::iterator classes_iterator;
	typename typedef std::map<Key, class_info_type*>::iterator key_map_iterator;

	class_factory(const class_factory<Root, Key, Tag>& rhs)	{}

public:
	class_factory()	
	{
		unlock();
	}
	~class_factory()
	{
		delete classes;
		delete key_map;
	}

	const Key key(const type_info& ti) throw(not_registered)
	{
		unlock();
		classes_iterator i = classes->find(&ti);
		if (i == classes->end())
			throw not_registered();
		return (*i).second.key;
	}
	const Tag& tag(const type_info& ti) throw(not_registered)
	{
		unlock();
		classes_iterator i = classes->find(&ti);
		if (i == classes->end())
			throw not_registered();
		return (*i).second.tag;
	}
	const Tag& tag(const Key key) throw(not_registered)
	{
		unlock();
		key_map_iterator i = key_map->find(key);
		if (i == key_map->end())
			throw not_registered();
		return (*i).second->tag;
	}
	Tag& tag_ref(const type_info& ti)
	{
		unlock();
		return (*classes)[&ti].tag;
	}
	Root* create(const Key key) throw(not_registered)
	{
		unlock();
		key_map_iterator i = key_map->find(key);
		if (i == key_map->end())
			throw not_registered();
		return (*i).second->create();
	}

	template<class T>
	void register_class(const T* t, const Key key)
	{
		unlock();
		class_info_type& info = (*classes)[&typeid(T)];
		info.key = key;
		info.create = class_creator<Root, T>::create;
		key_map->insert(std::make_pair<Key, class_info_type*>(key, &info));
	}
	template<class T>
	void register_class(const T* t, const Key key, const Tag tag)
	{
		unlock();
		class_info_type& info = (*classes)[typeid(T)];
		info.key = key;
		info.tag = tag;
		info.create = class_creator<Root, T>::create;
		key_map->insert(std::make_pair<Key, class_info_type*>(key, &info));
	}

private:
	void unlock()
	{
		if (initial_lock == 0)
		{
			classes = new std::map<const type_info*, class_info_type>;
			key_map = new std::map<Key, class_info_type*>;
			initial_lock = 1;
		}
	}

	static int initial_lock;
	std::map<const type_info*, class_info_type>* classes;
	std::map<Key, class_info_type*>* key_map; 
};


#endif	// FACTORY_H