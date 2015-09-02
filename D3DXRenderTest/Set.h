#ifndef __SET__
#define __SET__
#include <unordered_set>

template<typename _vTy>
class Set{
//类型定义
public:
	typedef typename std::unordered_set<_vTy>::key_type key_type;
	typedef typename std::unordered_set<_vTy>::value_type value_type;
	typedef typename std::unordered_set<_vTy>::iterator iterator;
	typedef typename std::unordered_set<_vTy>::const_iterator const_iterator;
	typedef typename std::unordered_set<_vTy>::reference reference;
	typedef typename std::unordered_set<_vTy>::const_reference const_reference;
	typedef typename std::unordered_set<_vTy>::pointer pointer;
	typedef typename std::unordered_set<_vTy>::const_pointer const_pointer;
	typedef typename std::unordered_set<_vTy>::size_type size_type;
public:
	Set();
	Set(const Set& copy_obj);
	Set(Set&& move_obj);
	~Set();
	
	void clear();
	size_t size() const;
	void insert(_vTy& _val);
	void erase(_vTy& _val);
	typename Set<_vTy>::iterator 
	erase(typename Set<_vTy>::iterator _iterator);
	void swap(_vTy& swap_obj);
	bool empty() const;

	typename Set<_vTy>::iterator begin();
	typename Set<_vTy>::const_iterator begin() const;
	typename Set<_vTy>::iterator end();
	typename Set<_vTy>::const_iterator end() const;


private:
	std::unordered_set<_vTy> m_set;
};

template<typename _vTy>
typename Set<_vTy>::iterator
Set<_vTy>::erase(typename Set<_vTy>::iterator _iterator)
{
	(*_iterator)->release();
	return m_set.erase(_iterator);
}

template<typename _vTy>
bool Set<_vTy>::empty() const
{
	return m_set.empty();
}

template<typename _vTy>
typename Set<_vTy>::const_iterator
Set<_vTy>::end() const
{
	return m_set.end();
}

template<typename _vTy>
typename Set<_vTy>::iterator 
Set<_vTy>::end()
{
	return m_set.end();
}

template<typename _vTy>
typename Set<_vTy>::const_iterator
Set<_vTy>::begin() const
{
	return m_set.begin();
}

template<typename _vTy>
typename Set<_vTy>::iterator 
Set<_vTy>::begin()
{
	return m_set.begin();
}

template<typename _vTy>
void Set<_vTy>::swap( _vTy& swap_obj )
{
	m_set = std::move(swap_obj.m_set);
}

template<typename _vTy>
void Set<_vTy>::erase(_vTy& _val )
{
	m_set.erase(_val);
	_val->release();
}

template<typename _vTy>
void Set<_vTy>::insert(_vTy& _val )
{
	m_set.insert(value_type(_val));
	_val->retain();
}

template<typename _vTy>
size_t Set<_vTy>::size() const
{
	return m_set.size();
}

template<typename _vTy>
void Set<_vTy>::clear()
{
	for(auto itor = m_set.begin(); itor != m_set.end(); ++itor)
		(*itor)->release();
	m_set.clear();
}

template<typename _vTy>
Set<_vTy>::~Set()
{
	clear();
}

template<typename _vTy>
Set<_vTy>::Set( Set&& move_obj )
{
	m_set = std::move(move_obj);
}

template<typename _vTy>
Set<_vTy>::Set( const Set& copy_obj )
{
	m_set = copy_obj.m_set;
	for(auto itor = m_set.begin(); itor != m_set.end(); ++itor)
		(*itor)->retain();
}

template<typename _vTy>
Set<_vTy>::Set()
{

}


#endif