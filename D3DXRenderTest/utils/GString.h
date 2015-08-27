#ifndef __GSTRING__
#define __GSTRING__
#include <string>
#include <iosfwd>
#include <unordered_map>
#include <xstddef>


class GString{
//静态函数工具
public:
	static GString FormatString(const char* str, ...);

public:
	typedef std::string::value_type value_type;
	typedef std::string::reference reference;
	typedef std::string::const_reference const_reference;
	typedef std::string::pointer pointer;
	typedef std::string::const_pointer const_pointer;
	typedef std::string::iterator iterator;
	typedef std::string::const_iterator const_iterator;
	typedef std::string::size_type size_type;
public:
	GString();
	GString(const GString& str);
	GString(GString&& str);
	GString(const std::string& str);
	GString(std::string&& str);
	GString(const char* str);
	GString(int num);
	GString(double num);
	GString(char c);
	GString(const wchar_t* wstr);

public:
//关系运算符
	bool operator==(const GString& compare_obj) const;
	bool operator==(const std::string& compare_obj) const;
	bool operator==(const char* compare_obj) const;
	bool operator>(const GString& compare_obj) const;
	bool operator<(const GString& compare_obj) const;
	bool operator>=(const GString& compare_obj) const;
	bool operator<=(const GString& compare_obj) const;
	bool operator>(const std::string& compare_obj) const;
	bool operator<(const std::string& compare_obj) const;
	bool operator>=(const std::string& compare_obj) const;
	bool operator<=(const std::string& compare_obj) const;
//连接
	GString operator+(const GString& compare_obj) const;
	GString operator+(const std::string& compare_obj) const;
	GString operator+(const char* compare_obj) const;
	GString operator+(const char& c) const;
	GString operator+(const int& num) const;
	GString operator+(const float& num) const;

//赋值运算符
	const GString& operator=(const GString& copy_obj);
	const GString& operator+=(const GString& compare_obj);
	const GString& operator+=(const std::string& compare_obj);
	const GString& operator+=(const char* compare_obj);
	const GString& operator+=(const char& c);
	const GString& operator+=(const int& num);
	const GString& operator+=(const double& num);

//流操作运算符
	const GString& operator<<(const GString& obj);
	const GString& operator<<(const int& obj);
	const GString& operator<<(const double& obj);
	const GString& operator<<(const char& obj);
	const GString& operator<<(const std::string& obj);
	const GString& operator<<(const char* obj);

	const GString& operator>>(GString& obj) const;
	const int& operator>>(int& obj) const;
	const double& operator>>(double& obj) const;
	const char& operator>>(char& obj) const;
	const std::string& operator>>(std::string& obj) const;

//输入输出运算符
	friend std::ostream& operator<<(std::ostream& os, const GString& str);
//API
public:
	size_type size() const;
	bool empty() const;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	void clear();
	//查找
	int find(char ch, size_type offset = 0) const;
	int find(const GString& find_str, size_type offset = 0) const;
	int findFinal(char ch, size_type offset = 0) const;
	//取自字符串
	GString substr(size_type offset, size_type count = 1) const;
	GString substr(
		const GString& left, 
		const GString& right, 
		size_type offset = 0, 
		size_type* out_index = nullptr) const;
	//删除字符串
	void erase(size_type offset, size_type count = 1);
	//将所有str替换为emplace_str
	void emplace(const GString& str, const GString& emplace_str, size_type offset = 0);

	//返回index位置上的字符
	char at(int index) const;
	//返回C类型字符串
	const char* c_str() const;
	std::basic_string<wchar_t> toWString() const;

	//返回头尾字符,和头尾插入删除操作
	const_reference front() const;
	const_reference back() const;
	void push_back(char ch);
	void pop_back();
	void push_front(char ch);
	void pop_front();

	//各类转换
	int toInt() const;
	double toDouble() const;
	long toInt_hex() const;

	friend struct GString_hash;
private:
	std::string m_str;
};

//自定义散列仿函数
struct GString_hash
{
	typedef GString::value_type value_type;
	std::tr1::hash<std::string> hasher;
	size_t operator()(const GString& _Keyval) const
	{
		return hasher(_Keyval.m_str);
// 		return (std::_Hash_seq((const unsigned char *)_Keyval.m_str.c_str(),
// 			_Keyval.m_str.size() * sizeof(value_type)));
	}
};


//公共散列函数
template<>
class std::tr1::hash<GString>
	: public std::unary_function<GString, size_t>
{	// hash functor
public:
	typedef GString _Kty;

	size_t operator()(const _Kty& _Keyval) const
	{	// hash _Keyval to size_t value by pseudorandomizing transform
		size_t _Val = 2166136261U;
		size_t _First = 0;
		size_t _Last = _Keyval.size();
		size_t _Stride = 1 + _Last / 10;

		for(; _First < _Last; _First += _Stride)
			_Val = 16777619U * _Val ^ (size_t)_Keyval.at(_First);
		return (_Val);
	}
};

#endif