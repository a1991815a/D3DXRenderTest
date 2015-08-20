#ifndef __MAP__
#define __MAP__
#include <unordered_map>

template<typename _kTy, typename _vTy>
class Map{
public:
	typedef typename std::unordered_map<_kTy, _vTy> _myContainer;
	typedef typename std::unordered_map<_kTy, _vTy>::key_type key_type;
	typedef typename std::unordered_map<_kTy, _vTy>::value_type value_type;
	typedef typename std::unordered_map<_kTy, _vTy>::mapped_type mapped_type;
	typedef typename std::unordered_map<_kTy, _vTy>::iterator iterator;
	typedef typename std::unordered_map<_kTy, _vTy>::const_iterator const_iterator;
	typedef typename std::unordered_map<_kTy, _vTy>::reference reference;
	typedef typename std::unordered_map<_kTy, _vTy>::const_reference const_reference;
	typedef typename std::unordered_map<_kTy, _vTy>::pointer pointer;
	typedef typename std::unordered_map<_kTy, _vTy>::const_pointer const_pointer;

private:
	std::unordered_map<_kTy, _vTy> m_refMap;

public:
	Map();
	Map(const Map& copy_obj);
	Map(Map&& copy_obj);
	~Map();

	_vTy& at(const _kTy& key);
	const _vTy& at(const _kTy& key) const;
	void insert(const _kTy& key, _vTy& value);
	void erase(const _kTy& key);
	void erase(typename Map<_kTy, _vTy>::const_iterator key);
	void clear();
	void swap(Map& map);
	size_t size() const;
	typename Map<_kTy, _vTy>::iterator begin();
	typename Map<_kTy, _vTy>::const_iterator begin() const;
	typename Map<_kTy, _vTy>::iterator end();
	typename Map<_kTy, _vTy>::const_iterator end() const;
	typename Map<_kTy, _vTy>::iterator find(const _kTy& key);
	typename Map<_kTy, _vTy>::const_iterator find(const _kTy& key) const;

	const Map<_kTy, _vTy>& operator=(const Map<_kTy, _vTy>& copy_obj);
};

template<typename _kTy, typename _vTy>
const Map<_kTy, _vTy>& Map<_kTy, _vTy>::operator=( const Map<_kTy, _vTy>& copy_obj )
{
	clear();
	m_refMap = copy_obj.m_refMap;
	auto itor = m_refMap.begin();
	for (; itor != m_refMap.end(); ++itor)
		itor->second->retain();
}

template<typename _kTy, typename _vTy>
typename Map<_kTy, _vTy>::const_iterator 
Map<_kTy, _vTy>::find( const _kTy& key ) const
{
	return m_refMap.find(key);
}

template<typename _kTy, typename _vTy>
typename Map<_kTy, _vTy>::iterator 
Map<_kTy, _vTy>::find( const _kTy& key )
{
	return m_refMap.find(key);
}

template<typename _kTy, typename _vTy>
typename Map<_kTy, _vTy>::const_iterator 
Map<_kTy, _vTy>::end() const
{
	return m_refMap.end();
}

template<typename _kTy, typename _vTy>
typename Map<_kTy, _vTy>::iterator
Map<_kTy, _vTy>::end()
{
	return m_refMap.end();
}

template<typename _kTy, typename _vTy>
typename Map<_kTy, _vTy>::const_iterator
Map<_kTy, _vTy>::begin() const
{
	return m_refMap.begin();
}

template<typename _kTy, typename _vTy>
typename Map<_kTy, _vTy>::iterator
Map<_kTy, _vTy>::begin()
{
	return m_refMap.begin();
}

template<typename _kTy, typename _vTy>
size_t 
Map<_kTy, _vTy>::size() const
{
	return m_refMap.size();
}

template<typename _kTy, typename _vTy>
void 
Map<_kTy, _vTy>::swap( Map& map )
{
	m_refMap.swap(map.m_refMap);
}

template<typename _kTy, typename _vTy>
void Map<_kTy, _vTy>::clear()
{
	auto itor = m_refMap.begin();
	for (; itor != m_refMap.end(); ++itor)
		itor->second->release();
	m_refMap.clear();
}

template<typename _kTy, typename _vTy>
void 
Map<_kTy, _vTy>::erase( typename Map<_kTy, _vTy>::const_iterator key )
{
	auto itor = m_refMap.find(key->first);
	itor->second->release();
	m_refMap.erase(itor);
}

template<typename _kTy, typename _vTy>
void Map<_kTy, _vTy>::erase( const _kTy& key )
{
	auto itor = m_refMap.find(key);
	itor->second->release();
	m_refMap.erase(itor);
}

template<typename _kTy, typename _vTy>
void 
Map<_kTy, _vTy>::insert( const _kTy& key, _vTy& value )
{
	m_refMap[key] = value;
	value->retain();
}

template<typename _kTy, typename _vTy>
const _vTy& Map<_kTy, _vTy>::at( const _kTy& key ) const
{
	return m_refMap.at(key);
}

template<typename _kTy, typename _vTy>
_vTy& 
Map<_kTy, _vTy>::at( const _kTy& key )
{
	return m_refMap.at(key);
}

template<typename _kTy, typename _vTy>
Map<_kTy, _vTy>::~Map()
{
	clear();
}

template<typename _kTy, typename _vTy>
Map<_kTy, _vTy>::Map( Map&& copy_obj )
{
	m_refMap = std::move(copy_obj.m_refMap);
}

template<typename _kTy, typename _vTy>
Map<_kTy, _vTy>::Map( const Map& copy_obj )
{
	m_refMap = copy_obj.m_refMap;
	auto itor = m_refMap.begin();
	for (; itor != m_refMap.end(); ++itor)
		itor->second->retain();
}

template<typename _kTy, typename _vTy>
Map<_kTy, _vTy>::Map()
{

}

#endif