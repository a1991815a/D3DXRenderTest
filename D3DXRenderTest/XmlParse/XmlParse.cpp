#include "XmlParse.h"

#include <iostream>
#include <assert.h>
using namespace std;

XmlParse* XmlParse::m_instance = nullptr;

XmlParse* XmlParse::getInstance()
{
	if(m_instance == nullptr)
		m_instance = new XmlParse();
	return m_instance;
}

void XmlParse::destroyInstance()
{
	if(m_instance){
		delete m_instance;
		m_instance = nullptr;
	}
}



GString XmlParse::loadFromFile(const char* in_file) const
{
	FILE* f = nullptr;
	errno_t err = 0;
	err = fopen_s(&f, in_file, "rb+");
	assert(err == 0);

	char buf[1025];
	memset(buf, 0, 1025);
	fseek(f, 0, SEEK_END);
	long len = ftell(f);
	rewind(f);

	GString file_data;

	for (long read_len = len; read_len >0; )
	{
		if((read_len -= 1024) >= 0)
		{
			fread_s(buf, 1025, 1, 1024, f);
			file_data += buf;
			memset(buf, 0, 1025);
		}else{
			fread_s(buf, 1025, 1, 1024 + read_len, f);
			file_data += buf;
			memset(buf, 0, 1025);
		}
	}
	fclose(f);

	cout << file_data << endl;

	return file_data;
}

Value XmlParse::parseFromFile(const char* in_file) const
{
	GString tmp_text;
	Value root_val = ValueMap();
	TiXmlDocument* doc = new TiXmlDocument();
	doc->LoadFile(in_file);
	TiXmlElement* root = doc->FirstChildElement();
	assert(root != nullptr);
	tmp_text = root->Attribute("key");
	root_val.asVMap()[tmp_text] = ValueMap();
	Value& parse_val = root_val.asVMap().at(tmp_text);

	const TiXmlElement* child_node = root->FirstChildElement();
	for (; child_node != nullptr; child_node = child_node->NextSiblingElement())
		parseNode(child_node, &parse_val);

	return root_val;
}

void XmlParse::parseNode(const TiXmlElement* ele, Value* parent_val) const
{
	GString signal_text = ele->Value();
	if(signal_text == "dic"){
		parseNodeDic(ele, parent_val);
	}else if(signal_text == "array"){
		parseNodeArray(ele, parent_val);
	}else if(signal_text == "string"){
		parseNodeString(ele, parent_val);
	}else{
		assert(false);
	}
}

void XmlParse::parseNodeDic(const TiXmlElement* ele, Value* parent_val) const
{
	if(parent_val->getType() == Value::VMAP)
	{
		GString key = ele->Attribute("key");
		parent_val->asVMap()[key] = ValueMap();
		Value& val = parent_val->asVMap().at(key);
		const TiXmlElement* child_ele = ele->FirstChildElement();
		for (; child_ele != nullptr; child_ele = child_ele->NextSiblingElement())
			parseNode(child_ele, &val);
	}

	else if(parent_val->getType() == Value::VVECTOR){
		parent_val->asVVector().push_back(ValueMap());
		Value& val = parent_val->asVVector().back();
		const TiXmlElement* child_ele = ele->FirstChildElement();
		for (;child_ele != nullptr; child_ele = child_ele->NextSiblingElement())
			parseNode(child_ele, &val);
	}
	
	else{
		assert(false);
	}
}

void XmlParse::parseNodeArray(const TiXmlElement* ele, Value* parent_val) const
{
	if(parent_val->getType() == Value::VMAP)
	{
		GString key = ele->Attribute("key");
		parent_val->asVMap()[key] = ValueVector();
		Value& val = parent_val->asVMap().at(key);
		const TiXmlElement* child_ele = ele->FirstChildElement();
		for (;child_ele != nullptr; child_ele = child_ele->NextSiblingElement())
			parseNode(child_ele, &val);
	}
	
	else if(parent_val->getType() == Value::VVECTOR){
		parent_val->asVVector().push_back(ValueVector());
		Value& val = parent_val->asVVector().back();
		const TiXmlElement* child_ele = ele->FirstChildElement();
		for (;child_ele != nullptr; child_ele = child_ele->NextSiblingElement())
			parseNode(child_ele, &val);
	}
	
	else{
		assert(false);
	}
	
}

void XmlParse::parseNodeString(const TiXmlElement* ele, Value* parent_val) const
{
	if(parent_val->getType() == Value::VMAP)
	{
		GString key = ele->Attribute("key");
		parent_val->asVMap()[key] = ele->GetText();
	}else if(parent_val->getType() == Value::VVECTOR){
		parent_val->asVVector().push_back(Value(ele->GetText()));
	}else{
		assert(false);
	}
}
