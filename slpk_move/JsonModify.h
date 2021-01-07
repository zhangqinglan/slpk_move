#pragma once
#include "ZipHelper.h"
#include "json.h"
#include <io.h>
class JsonModify
{
public:
	double m_dx, m_dy, m_dz;
	JsonModify(double dx, double dy, double dz);
	vector<string> visitFiles(string path);
	void modify3dScene();
	void modifycenter();
	~JsonModify();
};

