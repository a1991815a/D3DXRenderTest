#ifndef __XMLPARSE__
#define __XMLPARSE__
#include "tiny/tinyxml.h"
#include "../utils/Value.h"

#define _xmlParse		XmlParse::getInstance()

class XmlParse{
public:
	static XmlParse* getInstance();
	static void destroyInstance();
private:
	static XmlParse* m_instance;

public:
	GString loadFromFile(const char* in_file) const;
	Value parseFromFile(const char* in_file) const;

private:
	void parseNode(const TiXmlElement* ele, Value* parent_val) const;

	void parseNodeDic(const TiXmlElement* ele, Value* parent_val) const;
	void parseNodeArray(const TiXmlElement* ele, Value* parent_val) const;
	void parseNodeString(const TiXmlElement* ele, Value* parent_val) const;

};

#endif