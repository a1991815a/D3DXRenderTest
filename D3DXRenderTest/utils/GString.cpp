#include "GString.h"
#include <stdarg.h>
#include <stdio.h>
#include <windows.h>
#pragma warning(disable: 4996)

static const size_t max_length = 1024;
static char s_buf[max_length + 1] = { 0 };

//÷ÿ‘ÿ…¢¡–∫Ø ˝


GString GString::FormatString(const char* str, ...)
{
	GString return_str = "";
	va_list ap;
	va_start(ap, str);
	int buf_size = _vsnprintf(nullptr, 0, str, ap);
	if (buf_size <= max_length) {
		va_end(ap);
		va_start(ap, str);
		vsprintf_s(s_buf, max_length + 1, str, ap);
		return_str += s_buf;
		memset(s_buf, 0, max_length + 1);
		va_end(ap);
	}
	else
	{
		char* tmp_buf = new char[buf_size + 1];
		memset(tmp_buf, 0, buf_size + 1);
		va_end(ap);
		va_start(ap, str);
		vsprintf_s(tmp_buf, buf_size + 1, str, ap);
		return_str += tmp_buf;
		delete[] tmp_buf;
		va_end(ap);
	}

	return return_str;
}

GString::GString()
	:m_str("")
{

}

GString::GString(const GString& str)
	:m_str(str.m_str)
{

}

GString::GString(GString&& str)
{
	m_str = std::forward<std::string>(str.m_str);
}

GString::GString(const std::string& str)
	:m_str(str)
{

}

GString::GString(std::string&& str)
	:m_str(str)
{
}

GString::GString(const char* str)
{
	if (str == nullptr)
		m_str = "";
	else
		m_str = str;
}

GString::GString(int num)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%d", num);
	m_str = tmp_str;
}

GString::GString(double num)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%f", num);
	m_str = tmp_str;
	while(m_str.size() > 0 && m_str.back() == '0')
		m_str.pop_back();
	m_str = tmp_str;
}

GString::GString(char c)
	:m_str("")
{
	m_str += c;
}

GString::GString( const wchar_t* wstr )
{
	char* str = nullptr;
	int len= WideCharToMultiByte(CP_ACP,0,wstr,wcslen(wstr),NULL,0,NULL,NULL); 
	str=new char[len+1]; 
	WideCharToMultiByte(CP_ACP,0,wstr,wcslen(wstr),str,len,NULL,NULL); 
	str[len]='\0'; 
	m_str += str;
	delete[] str;
}

bool GString::operator>(const GString& compare_obj) const
{
	return m_str > compare_obj.m_str;
}

bool GString::operator>(const std::string& compare_obj) const
{
	return m_str > compare_obj;
}

bool GString::operator<(const GString& compare_obj) const
{
	return m_str < compare_obj.m_str;
}

bool GString::operator<=(const GString& compare_obj) const
{
	return m_str <= compare_obj.m_str;
}

bool GString::operator<(const std::string& compare_obj) const
{
	return m_str < compare_obj;
}

bool GString::operator<=(const std::string& compare_obj) const
{
	return m_str <= compare_obj;
}

GString GString::operator+(const GString& compare_obj) const
{
	GString gstr = *this;
	gstr.m_str += compare_obj.m_str;
	return gstr;
}

GString GString::operator+(const std::string& compare_obj) const
{
	GString gstr = *this;
	gstr.m_str += compare_obj;
	return gstr;
}

GString GString::operator+(const char* compare_obj) const
{
	GString gstr = *this;
	gstr.m_str += compare_obj;
	return gstr;
}

GString GString::operator+(const char& c) const
{
	GString gstr = *this;
	gstr.m_str += c;
	return gstr;
}

GString GString::operator+(const int& num) const
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%d", num);
	GString gstr = *this;
	gstr.m_str += tmp_str;
	return gstr;
}

GString GString::operator+(const float& num) const
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%f", num);
	GString gstr = *this;
	gstr.m_str += tmp_str;
	return gstr;
}

const GString& GString::operator+=(const GString& compare_obj)
{
	m_str += compare_obj.m_str;
	return *this;
}

const GString& GString::operator+=(const std::string& compare_obj)
{
	m_str += compare_obj;
	return *this;
}

const GString& GString::operator+=(const char* compare_obj)
{
	m_str += compare_obj;
	return *this;
}

const GString& GString::operator+=(const char& c)
{
	m_str += c;
	return *this;
}

const GString& GString::operator+=(const int& num)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%d", num);
	m_str += tmp_str;
	return *this;
}

const GString& GString::operator+=(const double& num)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%f", num);
	m_str += tmp_str;
	while(m_str.size() > 0 && m_str.back() == '0')
		m_str.pop_back();
	return *this;
}

const GString& GString::operator<<(const GString& obj)
{
	m_str += obj.m_str;
	return *this;
	return obj;
}

const GString& GString::operator<<(const int& obj)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%d", obj);
	m_str += tmp_str;
	return *this;
}

const GString& GString::operator<<(const double& obj)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%f", obj);
	m_str += tmp_str;
	while(m_str.size() > 0 && m_str.back() == '0')
		m_str.pop_back();
	return *this;
}

const GString& GString::operator<<(const char& obj)
{
	m_str += obj;
	return *this;
}

const GString& GString::operator<<(const std::string& obj)
{
	m_str += obj;
	return *this;
}

const GString& GString::operator<<(const char* obj)
{
	m_str += obj;
	return *this;
}

const GString& GString::operator>>(GString& obj) const
{
	obj.m_str += this->m_str;
	return obj;
}

const int& GString::operator>>(int& obj) const
{
	obj = atoi(this->m_str.c_str());
	return obj;
}

const double& GString::operator>>(double& obj) const
{
	obj = atof(this->m_str.c_str());
	return obj;
}

const char& GString::operator>>(char& obj) const
{
	if (this->size() == 0)
	{
		obj = 0;
		return obj;
	}
	obj = this->m_str.front();
	return obj;
}

const std::string& GString::operator>>(std::string& obj) const
{
	obj += this->m_str;
	return obj;
}

GString::size_type GString::size() const
{
	return m_str.size();
}

bool GString::empty() const
{
	if (size() == 0)
		return true;
	return false;
}

GString::iterator GString::begin()
{
	return m_str.begin();
}

GString::const_iterator GString::begin() const
{
	return m_str.begin();
}

GString::iterator GString::end()
{
	return m_str.end();
}

GString::const_iterator GString::end() const
{
	return m_str.end();
}

void GString::clear()
{
	m_str.clear();
}

int GString::find(char ch, size_type offset /*=0 */) const
{
	return m_str.find(ch, offset);
}

int GString::find(const GString& find_str, size_type offset /*=0 */) const
{
	if (find_str.size() == 1)
		return this->m_str.find(find_str.c_str());

	while ((offset = m_str.find(find_str.m_str.front(), offset)) != -1)
	{
		for(size_t i = 1; i < find_str.size(); i++){
			if (find_str.at(i) != this->at(offset + i))
				break;
			else if (i == find_str.size() - 1)
				return offset;
		}
		offset += find_str.size();
		break;
	}
	return -1;
}

int GString::findFinal( char ch, size_type offset /*= 0*/ ) const
{
	int index = -1;
	for (size_t i = offset; i < size(); ++i)
		if(m_str.at(i) == ch)
			index = i;
	return index;
}

GString GString::substr(size_type offset, size_type count /*= 1*/) const
{
	return m_str.substr(offset, count);
}

GString GString::substr(
	const GString& left,
	const GString& right,
	size_type offset /*= 0*/,
	size_type* out_index /*= nullptr*/) const
{
	if (out_index != nullptr)
		*out_index = -1;
	int left_index = -1;
	int right_index = -1;
	left_index = find(left, offset);
	if (left_index == -1)
		return "";
	left_index += left.size();
	right_index = find(right, left_index);
	if (right_index == -1)
		return "";
	if (out_index != nullptr)
		*out_index = right_index + right.size();
	return m_str.substr(left_index, right_index - left_index);
}

void GString::erase(size_type offset, size_type count /*= 1*/)
{
	m_str.erase(offset, count);
}

void GString::emplace(const GString& str, const GString& emplace_str, size_type offset /*= 0*/)
{
	int index = -1;
	while ((index = find(str, offset)) != -1)
	{
		m_str.erase(index, str.size());
		m_str.insert(index, emplace_str.m_str);
	}
}

char GString::at(int index) const
{
	return m_str.at(index);
}

const char* GString::c_str() const
{
	return m_str.c_str();
}

GString::const_reference GString::front() const
{
	return m_str.front();
}

GString::const_reference GString::back() const
{
	return m_str.back();
}

void GString::push_back(char ch)
{
	m_str.push_back(ch);
}

void GString::pop_back()
{
	m_str.pop_back();
}

void GString::push_front(char ch)
{
	m_str.insert(m_str.begin(), ch);
}

void GString::pop_front()
{
	m_str.erase(m_str.begin());
}

int GString::toInt() const
{
	return atoi(m_str.c_str());
}

double GString::toDouble() const
{
	return atof(m_str.c_str());
}

long GString::toInt_hex() const
{
	long val = 0;
	int index = m_str.size() - 1;
	int hex = 1;

	for (size_t i = 0; i < 8; ++i, --index, hex *= 16)
	{
		if (index < 0)
			break;
		char num[3] = { 0 };
		num[0] = m_str.at(index);
		switch (num[0])
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			break;
		case 'A':
		case 'a':
			num[0] = '1';
			num[1] = '0';
			break;
		case 'B':
		case 'b':
			num[0] = '1';
			num[1] = '1';
			break;
		case 'C':
		case 'c':
			num[0] = '1';
			num[1] = '2';
			break;
		case 'D':
		case 'd':
			num[0] = '1';
			num[1] = '3';
			break;
		case 'E':
		case 'e':
			num[0] = '1';
			num[1] = '4';
			break;
		case 'F':
		case 'f':
			num[0] = '1';
			num[1] = '5';
			break;
		case 'x':
		case 'X':
			return val;
		default:
			break;
		}
		val += (atoi(num) * hex);
	}

	return val;
}

const GString& GString::operator=(const GString& copy_obj)
{
	m_str = copy_obj.m_str;
	return *this;
}

bool GString::operator>=(const std::string& compare_obj) const
{
	return m_str >= compare_obj;
}

bool GString::operator>=(const GString& compare_obj) const
{
	return m_str >= compare_obj.m_str;
}

bool GString::operator==(const char* compare_obj) const
{
	return m_str == compare_obj;
}

bool GString::operator==(const std::string& compare_obj) const
{
	return m_str == compare_obj;
}

bool GString::operator==(const GString& compare_obj) const
{
	return m_str == compare_obj.m_str;
}

std::basic_string<wchar_t> GString::toWString() const
{
	
	wchar_t* wstr = nullptr;
	int len = MultiByteToWideChar(CP_ACP,0,m_str.c_str(), m_str.size(),NULL,0); 
	wstr=new wchar_t[len+1]; 
	MultiByteToWideChar(CP_ACP,0,m_str.c_str(), m_str.size(), wstr,len); 
	wstr[len]='\0'; 

	std::basic_string<wchar_t> wString = wstr;
	delete[] wstr;

	return wString; 
}

std::ostream& operator<<(std::ostream& os, const GString& str) {
	os << str.c_str();
	return os;
};

#pragma warning(default: 4996)