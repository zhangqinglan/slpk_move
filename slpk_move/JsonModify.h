#pragma once
#include "ZipHelper.h"
#include "json.h"
#include <io.h>
#include <glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class JsonModify
{
public:
	double m_dx, m_dy, m_dz;//Æ½ÒÆ
	float m_px, m_py, m_pz, angleZ;//ÈÆµãÐý×ª
	glm::vec3 roatePoint;
	JsonModify(double dx, double dy, double dz);
	JsonModify(float px, float py, float pz, float angle);
	vector<string> visitFiles(string path);
	void modify3dScene();
	void modifycenter();
	void spinmodify3dScene();
	void spinmodifycenter();
	~JsonModify();
};

