#ifndef __VECTOR__
#define __VECTOR__
#include <vector>

template<typename _vTp>
class Vector{
public:
	typedef typename std::vector<typename _vTp>::iterator iterator;
	typedef typename std::vector<typename _vTp>::const_iterator const_iterator;
private:
	std::vector<_vTp> m_list;
public:
	Vector();
	Vector(const Vector& copy_obj);
	Vector(Vector&& move_obj);
	~Vector();

	inline void reserve(size_t size);
	inline size_t size() const;
	inline const _vTp& at(size_t index) const;
	inline _vTp& at(size_t index);
	inline void push_back(const _vTp& ins_data);
	inline void push_front(const _vTp& ins_data);
	inline void pop_back();
	inline void pop_front();
	inline _vTp& front();
	inline _vTp& back();
	inline const _vTp& front() const;
	inline const _vTp& back() const;
	inline void swap(Vector& swap_obj);
	inline void clear();
	inline void erase(size_t index);
	inline void erase(typename Vector<_vTp>::iterator itor);
	inline void insert(const _vTp& ins_data, typename Vector<typename _vTp>::const_iterator itor);

	inline typename Vector<_vTp>::iterator begin();
	inline typename Vector<_vTp>::const_iterator begin() const;
	inline typename Vector<_vTp>::iterator end();
	inline typename Vector<_vTp>::const_iterator end() const;

	const Vector<_vTp>& operator=(const Vector<_vTp>& copy_obj);
};

template<typename _vTp>
void Vector<_vTp>::reserve( size_t size )
{
	m_list.reserve(size);
}

template<typename _vTp>
const Vector<_vTp>& Vector<_vTp>::operator=( const Vector<_vTp>& copy_obj )
{
	this->clear();
	m_list = copy_obj.m_list;
	auto itor = m_list.begin();
	for (; itor != m_list.end(); ++itor)
		(*itor)->retain();
	return *this;
}

template<typename _vTp>
typename Vector<_vTp>::const_iterator Vector<_vTp>::end() const
{
	return m_list.end();
}

template<typename _vTp>
typename Vector<_vTp>::iterator Vector<_vTp>::end()
{
	return m_list.end();
}

template<typename _vTp>
typename Vector<_vTp>::const_iterator Vector<_vTp>::begin() const
{
	return m_list.begin();
}

template<typename _vTp>
typename Vector<_vTp>::iterator Vector<_vTp>::begin()
{
	return m_list.begin();
}

template<typename _vTp>
void Vector<_vTp>::insert(const _vTp& ins_data, typename Vector<_vTp>::const_iterator itor)
{
	ins_data->retain();
	m_list.insert(itor, ins_data);
}

template<typename _vTp>
void Vector<_vTp>::erase(typename Vector<_vTp>::iterator itor)
{
	(*itor)->release();
	m_list.erase(itor);
}

template<typename _vTp>
void Vector<_vTp>::erase(size_t index)
{
	m_list.at(index)->release();
	m_list.erase(m_list.begin() + index);
}

template<typename _vTp>
void Vector<_vTp>::clear()
{
	auto itor = m_list.begin();
	for (; itor != m_list.end(); ++itor)
		(*itor)->release();
	m_list.clear();
}

template<typename _vTp>
void Vector<_vTp>::swap(Vector& swap_obj)
{
	m_list.swap(swap_obj);
}

template<typename _vTp>
const _vTp& Vector<_vTp>::back() const
{
	return m_list.back();
}

template<typename _vTp>
const _vTp& Vector<_vTp>::front() const
{
	return m_list.front();
}

template<typename _vTp>
_vTp& Vector<_vTp>::back()
{
	return m_list.back();
}

template<typename _vTp>
_vTp& Vector<_vTp>::front()
{
	return m_list.front();
}

template<typename _vTp>
void Vector<_vTp>::pop_front()
{
	m_list.pop_front();
	ins_data->release();
}

template<typename _vTp>
void Vector<_vTp>::pop_back()
{
	m_list.pop_back();
	ins_data->release();
}

template<typename _vTp>
void Vector<_vTp>::push_front(const _vTp& ins_data)
{
	m_list.push_front(ins_data);
	ins_data->retain();
}

template<typename _vTp>
void Vector<_vTp>::push_back(const _vTp& ins_data)
{
	m_list.push_back(ins_data);
	ins_data->retain();
}

template<typename _vTp>
_vTp& Vector<_vTp>::at(size_t index)
{
	return m_list.at(index);
}

template<typename _vTp>
const _vTp& Vector<_vTp>::at(size_t index) const
{
	return m_list.at(index);
}

template<typename _vTp>
size_t Vector<_vTp>::size() const
{
	return m_list.size();
}

template<typename _vTp>
Vector<_vTp>::~Vector()
{
	clear();
}

template<typename _vTp>
Vector<_vTp>::Vector(Vector&& move_obj)
{
	m_list = std::move(move_obj.m_list);
}

template<typename _vTp>
Vector<_vTp>::Vector(const Vector& copy_obj)
{
	m_list = copy_obj.m_list;
	auto itor = m_list.begin();
	for (; itor != m_list.end(); ++itor)
		(*itor)->retain();
}

template<typename _vTp>
Vector<_vTp>::Vector()
{

}

#endif