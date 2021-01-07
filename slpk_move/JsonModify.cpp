#pragma warning(disable:4996)
#include "JsonModify.h"
JsonModify::JsonModify(double dx, double dy, double dz)
{
	this->m_dx = dx;
	this->m_dy = dy;
	this->m_dz = dz;

}

//获取文件夹中全部文件
vector<string> JsonModify::visitFiles(string path)
{
	vector<string> files;
	struct _finddata_t   filefind;
	string  curr = path + "/*.*";
	int   done = 0;
	intptr_t handle;
	//int filenum = 0;
	if ((handle = _findfirst(curr.c_str(), &filefind)) == -1)return files;
	while (!(done = _findnext(handle, &filefind)))
	{
		//printf("%s\n", filefind.name);
		if (!strcmp(filefind.name, "..")) {
			continue;
		}
		//for (i = 0; i < layer; i++)cout << "     ";
		if ((_A_SUBDIR == filefind.attrib)) //是目录
		{
			//printf("----------%s\n", filefind.name);
			//cout << filefind.name << "(dir)" << endl;
			/*curr = path + "\\" + filefind.name;
			dirs.push_back(curr);*/
			//filenum += 1;
		}
		else//不是目录，是文件     
		{
			//cout << path + "\\" + filefind.name << endl;
			curr = path + "/" + filefind.name;
			files.push_back(curr);
		}
	}
	_findclose(handle);
	return files;
}

//修改slpk中的3dScenelayer.json文件中的extent
void JsonModify::modify3dScene()
{
	
	ZipHelper uncompessjson;
	uncompessjson.exeUnCompress("process", "process/3dSceneLayer.json.gz");
	Json::Reader reader;
	Json::Value root;
	Json::Value delete1;
	ifstream f;
	f.open("process/3dSceneLayer.json", ios::binary);
	if (f.is_open())
	{
		bool parse_ok = reader.parse(f, root);
		f.close();
		remove("process/3dSceneLayer.json");
		if (parse_ok)
		{
			//if (root["geometryDefinitions"][0]["geometryBuffers"].size() != 1)
			//{
			//	//root.removeIndex(1, &root["geometryDefinitions"][0]["geometryBuffers"]);
			//	root["geometryDefinitions"][0]["geometryBuffers"].removeIndex(1, &delete1);
			//}
			root["store"]["extent"][0] = root["store"]["extent"][0].asDouble() + m_dx;
			root["store"]["extent"][1] = root["store"]["extent"][1].asDouble() + m_dy;
			root["store"]["extent"][2] = root["store"]["extent"][2].asDouble() + m_dx;
			root["store"]["extent"][3] = root["store"]["extent"][3].asDouble() + m_dy;

			Json::StyledWriter sw;
			//输出到文件  
			ofstream os;
			os.open("process/3dSceneLayer.json", std::ios::trunc);
			os << sw.write(root);
			os.close();


		}
	}
	remove("process/3dSceneLayer.json.gz");
	//压缩3dSceneLayer.json
	uncompessjson.exeCompress("process/3dSceneLayer.json", "process/3dSceneLayer.json.gz");
	//删除3dSceneLayer.json
	remove("process/3dSceneLayer.json");

}

//修改nodespages文件夹的json文件中的center
void JsonModify::modifycenter()
{
	//已经将slpk模型文件解压到了process文件夹中，这里需根据路径获取节点页索引文件，并解压
	//遍历获取nodepages文件夹下面所有的压缩包，并解压
	vector<string> nodepages = visitFiles("process/nodepages");
	for (int i = 0; i < nodepages.size(); i++)
	{
		string pagename = nodepages[i].substr(nodepages[i].find_last_of('/') + 1, nodepages[i].find_last_of('.') - 6 - nodepages[i].find_last_of('/'));
		string uncompesspath = "process/nodepages/";
		string uncompesspath1 = "process/nodepages/" + pagename + ".json";
		ZipHelper uncompesspage;
		uncompesspage.exeUnCompress(uncompesspath, nodepages[i]);
		Json::Reader reader;
		Json::Value root;
		ifstream f;
		f.open(uncompesspath1, ios::binary);
		if (f.is_open())
		{
			bool parse_ok = reader.parse(f, root);
			f.close();
			remove(uncompesspath1.c_str());
			if (parse_ok)
			{

				int nodescount = root["nodes"].size();//节点页索引中节点总数
				for (int j=0; j < nodescount; j++)
				{
					root["nodes"][j]["obb"]["center"][0] = root["nodes"][j]["obb"]["center"][0].asDouble() + m_dx;
					root["nodes"][j]["obb"]["center"][1] = root["nodes"][j]["obb"]["center"][1].asDouble() + m_dy;
					root["nodes"][j]["obb"]["center"][2] = root["nodes"][j]["obb"]["center"][2].asDouble() + m_dz;
				}
				Json::StyledWriter sw;
				//输出到文件  
				ofstream os;
				os.open(uncompesspath1.c_str(), std::ios::trunc);
				os << sw.write(root);
				os.close();

			}
		}
		remove(nodepages[i].c_str());
		//压缩json
		uncompesspage.exeCompress(uncompesspath1, nodepages[i].c_str());
		//删除json
		remove(uncompesspath1.c_str());

	}
}

JsonModify::~JsonModify()
{

}