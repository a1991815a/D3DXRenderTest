#ifndef __PATHMANAGER__
#define __PATHMANAGER__
#include "SingleInstance.h"
#include <vector>
#include <string>

#define _pathManager PathManager::getInstance()

class PathManager: public SingleInstance<PathManager>{
	DEFINE_PRIVATE_INSTANCE(PathManager);
private:
	std::vector<std::string> m_pathList;
	
public:
	void init();
	void addPath(const std::string& path);
	std::string getPath(const std::string& in_path, size_t index) const;
	size_t size() const;
};
#endif