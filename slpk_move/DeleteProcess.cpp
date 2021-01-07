#include "DeleteProcess.h"
DeleteProcess::DeleteProcess()
{

}

//ɾ��processĿ¼�µ������ļ�����������Ŀ¼�ŵ�vector��
vector<string> DeleteProcess::deletefile(string Directory)
{
	//����process����ȡ�����ļ��м��ļ���ɾ��
	//string Directory = "process";
	intptr_t hFile = 0; //ע������ļ����
	_finddata_t fileinfo;
	string p;
	vector<string> DirName;

	if ((hFile = _findfirst(p.assign(Directory).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼��ݹ�,�������ŵ�vector��
			//���������ɾ��
			if (fileinfo.attrib & _A_SUBDIR)
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					DirName.push_back(p.assign(Directory).append("\\").append(fileinfo.name));
					deletefile(p.assign(Directory).append("\\").append(fileinfo.name).c_str());
					//_rmdir(p.assign(Directory).append("\\").append(fileinfo.name).c_str());
				}

			}
			else
			{

				remove(p.assign(Directory).append("\\").append(fileinfo.name).c_str());
			}

		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	else
		remove(Directory.c_str());
	return DirName;

}

//ɾ��processĿ¼�µ�����Ŀ¼
void DeleteProcess::deletedir(vector<string> dirname)
{
	for (int i = dirname.size() - 1; i > 0; i--)
	{
		cout << dirname[i] << endl;
		_rmdir(dirname[i].c_str());
	}
}

void DeleteProcess::removeDir(string dirPath)
{
	struct _finddata_t fb;   //find the storage structure of the same properties file.
	string path;
	intptr_t   handle;
	int  resultone;
	int   noFile;            // the tag for the system's hidden files

	noFile = 0;
	handle = 0;

	path = dirPath + "/*";

	handle = _findfirst(path.c_str(), &fb);

	//find the first matching file
	if (handle != -1)
	{
		//find next matching file
		while (0 == _findnext(handle, &fb))
		{
			// "." and ".." are not processed
			noFile = strcmp(fb.name, "..");

			if (0 != noFile)
			{
				path.clear();
				path = dirPath + "/" + fb.name;

				//fb.attrib == 16 means folder
				if (fb.attrib == 16)
				{
					removeDir(path);
					_rmdir(path.c_str());
				}
				else
				{
					//not folder, delete it. if empty folder, using _rmdir istead.
					remove(path.c_str());
					//string path1 = path.substr(0, path.find_last_of('/'));
					//_rmdir(path1.c_str());
				}
			}
		}
		// close the folder and delete it only if it is closed. For standard c, using closedir instead(findclose -> closedir).
		// when Handle is created, it should be closed at last.
		_findclose(handle);
		//return 0;
	}

	_rmdir(dirPath.c_str());
}
DeleteProcess::~DeleteProcess()
{

}