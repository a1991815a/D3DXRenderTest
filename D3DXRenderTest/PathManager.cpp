#include "PathManager.h"

PathManager::~PathManager()
{

}

PathManager::PathManager()
{

}

void PathManager::init()
{
	addPath("../assets/");
	addPath("../../assets/");
}

void PathManager::addPath(const std::string& path)
{
	if(path.back() != '\\' && path.back() != '/')
		m_pathList.push_back(path + '/');
	else
		m_pathList.push_back(path);
}

std::string PathManager::getPath( const std::string& in_path, size_t index ) const
{
	return m_pathList.at(index) + in_path;
}

size_t PathManager::size() const
{
	return m_pathList.size();
}
