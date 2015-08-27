#ifndef __PATHMANAGER__
#define __PATHMANAGER__
#include "SingleInstance.h"
#include <vector>
#include "UtilsHeader.h"

#define _pathManager PathManager::getInstance()

class PathManager: public SingleInstance<PathManager>{
	DEFINE_PRIVATE_INSTANCE(PathManager);
private:
	std::vector<GString> m_pathList;
	
public:
	void init();
	void addPath(const GString& path);
	GString getPath(const GString& in_path, size_t index) const;
	size_t size() const;
};
#endif