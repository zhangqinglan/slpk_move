#include "ZipHelper.h"
#include<io.h>
#pragma warning(disable : 4996)

#define MAX_LEN 1024*100//����ֻ������С��100KB���ļ�


ZipHelper::ZipHelper()
{
}
//vector<string> GetAllFiles(const char * Directory, int type);

int ZipHelper::Compress(string inpath, string zipout)
{
	//zipFile zf = NULL;
	//zf = zipOpen64("1.zip", 0);
	//zip_fileinfo FileInfo;
	//ZeroMemory(&FileInfo, sizeof(FileInfo));
	//zipOpenNewFileInZip4(zf, "3dSceneLayer.json", &FileInfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, 5, 0, -MAX_WBITS, DEF_MEM_LEVEL,
	//	Z_DEFAULT_STRATEGY, NULL, 0, 0, ZIP_GPBF_LANGUAGE_ENCODING_FLAG);
	//zipWriteInFileInZip(zf, data, size);
	//zipCloseFileInZip(zf);
	//zipClose(zf, 0);
	int ret;
	char * buf = new(nothrow) char[MAX_LEN];
	zipFile zf = NULL;
	//zf = zipOpen64("3dSceneLayer.json.gz", 0);
	//�޸�
	//char* zipout = zipout;
	//zipOpen64()
	zf = zipOpen64(zipout.c_str(), 0);

	zip_fileinfo FileInfo;
	ZeroMemory(&FileInfo, sizeof(FileInfo));
	zipOpenNewFileInZip(zf, inpath.c_str(), &FileInfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, 9);//�޸�
	ifstream infile(inpath.c_str(), ios::binary);//�޸�
	infile.read(buf, MAX_LEN);
	uLong readlen = infile.gcount();
	ret = zipWriteInFileInZip(zf, buf, readlen);
	zipCloseFileInZip(zf);
	delete[] buf;
	zipClose(zf, 0);
	return 0;
}
//��ȡ��ǰ·��
string GetCurrentPath2()
{
	char apppath[MAX_PATH] = { 0 };
	string tmppath = "";
	GetModuleFileNameA(NULL, apppath, MAX_PATH);
	tmppath = (string)apppath;
	tmppath = tmppath.replace(tmppath.find("slpk_move.exe"), 13, "");
	return tmppath;
}


//����7z.exe�����ļ�ѹ��
void ZipHelper::exeCompress(string inpath, string zipout)
{
	//TCHAR str1[MAX_PATH] = { 0 };
	//CString strCurPath;
	//GetModuleFileName(NULL, str1, MAX_PATH);
	//strCurPath.Format(_T("%sfile.txt"), strCurPath);
	string out = GetCurrentPath2();
	//string zipexe = out + "7z.exe a -tZip \"";
	string zipexe = out + "7z.exe a \"";
	zipexe = zipexe.append(zipout);
	zipexe = zipexe.append("\" ");
	zipexe = zipexe.append(" \"");
	zipexe = zipexe.append(inpath);
	const char* c_s = zipexe.c_str();
	system(c_s);
	//system("pause");
}

void ZipHelper::exeCompressMore(string inpath, string zipout)//����exeѹ��Ŀ¼�µĶ��ļ�
{
	//TCHAR str1[MAX_PATH] = { 0 };
	//CString strCurPath;
	//GetModuleFileName(NULL, str1, MAX_PATH);
	//strCurPath.Format(_T("%sfile.txt"), strCurPath);
	string out = GetCurrentPath2();
	//string zipexe = out + "7z.exe a -tZip \"";
	string zipexe = out + "7z.exe a ";
	zipexe = zipexe.append(zipout);
	zipexe = zipexe.append(" \"");
	zipexe = zipexe.append(inpath);
	zipexe = zipexe.append("\"");

	//zipexe = zipexe.append(" -r -mx=9 -m2=BZip2 -ms=10m -mf=on -mhc=on -mmt=on");
	//zipexe = zipexe.append(" -m3=BZip2");
	const char* c_s = zipexe.c_str();
	system(c_s);
	//system("pause");
}

vector<string> GetAllFiles(const char * Directory, int type)
{
	intptr_t hFile = 0; //ע������ļ����
	_finddata_t fileinfo;
	string p;
	vector<string> FileName;

	if ((hFile = _findfirst(p.assign(Directory).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼��ݹ�
			//������������vector 
			if (fileinfo.attrib & _A_SUBDIR)
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					GetAllFiles(p.assign(Directory).append("\\").append(fileinfo.name).c_str(), type);
			}
			else
			{

				FileName.push_back(p.assign(Directory).append("\\").append(fileinfo.name));
			}

		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	else
		FileName.push_back(Directory); //���ļ�ֱ�Ӽ���
	return FileName;
}

//ѹ�����������ļ�
//���ļ���ӵ�zip�ļ��У�ע�����Դ�ļ�srcFileΪ������ӿ�Ŀ¼    
//fileNameInZip: ��zip�ļ��е��ļ������������·��    
void AddFileToZip(zipFile zf, string fileNameInZip, string srcFile)
{
	FILE* srcfp = NULL;

	//��ʼ��д��zip���ļ���Ϣ
	//zip_fileinfo zi;
	zip_fileinfo   zi = { 0 };

	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
		zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
	zi.dosDate = 0;
	zi.internal_fa = 0;
	zi.external_fa = 0;

	//���srcFileΪ�գ������Ŀ¼    
	string new_file_name = "";
	//if (fileNameInZip == "json")
	//	fileNameInZip = "";
	new_file_name += fileNameInZip;
	if (srcFile == "")
	{
		new_file_name += "/";
	}

	//��zip�ļ��д������ļ�    
	//zipOpenNewFileInZip(zf, new_file_name.c_str(), &zi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);
	zipOpenNewFileInZip(zf, new_file_name.c_str(), &zi, NULL, 0, NULL, 0, NULL, 0, Z_DEFAULT_COMPRESSION);//ע�����0��Ĭ��ѹ���㷨ΪStore.

	if (srcFile != "")
	{
		//��Դ�ļ�    
		fopen_s(&srcfp, srcFile.c_str(), "rb");
		if (srcfp == NULL)
		{
			printf("�޷�����ļ�: %s !\n", srcFile);
			zipCloseFileInZip(zf); //�ر�zip�ļ�  
			return;
		}

		//����Դ�ļ���д��zip�ļ�    
		char buf[100 * 1024]; //buffer    
		int numBytes = 0;
		while (!feof(srcfp))
		{
			numBytes = fread(buf, 1, sizeof(buf), srcfp);
			zipWriteInFileInZip(zf, buf, numBytes);
			if (ferror(srcfp))
				break;
		}

		//�ر�Դ�ļ�    
		fclose(srcfp);
	}

	//�ر�zip�ļ�    
	zipCloseFileInZip(zf);
}


//�ݹ������Ŀ¼��zip�ļ�    
void CollectFilesInDirToZip(zipFile zf, string strPath, string parentDir)
{
	string allfilestr = "";

	allfilestr += strPath;
	allfilestr += "//*.*";//find all files

	intptr_t Handle;
	struct _finddata_t FileInfo;

	if ((Handle = _findfirst(allfilestr.c_str(), &FileInfo)) == -1L)//Ŀ¼������
		return;

	string currentPath;
	string fullPath;

	do
	{
		if (strlen(FileInfo.name) == 1 && FileInfo.name[0] == '.'
			|| strlen(FileInfo.name) == 2 && FileInfo.name[0] == '.'&&FileInfo.name[1] == '.')
			continue;//��ǰ�ļ��� ��һ��Ŀ¼

		if (parentDir.length() != 0)
		{
			//if (parentDir == "json")
			//	parentDir = "";
			fullPath = parentDir;
			fullPath += "/";
			fullPath += FileInfo.name;//������zip�ļ��е����·��
		}
		else
			fullPath += FileInfo.name;

		currentPath = strPath;
		currentPath += "//";
		currentPath += FileInfo.name;

		if (FileInfo.attrib & _A_SUBDIR)// is a directory
		{
			AddFileToZip(zf, fullPath, ""); //��zip�ļ�������Ŀ¼�ṹ
			CollectFilesInDirToZip(zf, currentPath, fullPath);//�ݹ��ռ���Ŀ¼�ļ�    
			continue;
		}
		AddFileToZip(zf, fullPath, currentPath); //���ļ���ӵ�zip�ļ���
	} while (_findnext(Handle, &FileInfo) == 0);//find next file
	_findclose(Handle);//�޸ģ���2021.01.12��
	zipCloseFileInZip(zf);
}

int ZipHelper::CompressMore(const char * Directory, const char * DestPath, int type, int mode)
{
	vector<string> FileName = GetAllFiles(Directory, type);
	try
	{
		//GetAllFiles(Directory, type);
		if (FileName.size() == 0)
		{

			return 1;
		}
		char * buf = new(nothrow) char[MAX_LEN];
		if (buf == NULL)
		{
			abort();
			vector<string>().swap(FileName);
			//FileName.swap(vector<string>()); //���vector���ڴ�//�޸�
			return 1;
		}
		zipFile zf = NULL;
		zf = zipOpen64(DestPath, mode);
		zip_fileinfo FileInfo;
		ZeroMemory(&FileInfo, sizeof(FileInfo));
		int ret;
		for (vector<string>::size_type i = 0; i < FileName.size(); i++)
		{

			zipOpenNewFileInZip(zf, FileName.at(i).c_str(), &FileInfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, 9);
			ifstream infile(FileName.at(i), ios::binary);
			if (!infile.good())
			{


				zipCloseFileInZip(zf);
				zipClose(zf, NULL);
				remove(DestPath);
				vector<string>().swap(FileName);
				//FileName.swap(vector<string>());//�޸�
				return 1;
			}
			do
			{
				infile.read(buf, MAX_LEN);
				uLong readlen = infile.gcount();
				ret = zipWriteInFileInZip(zf, buf, readlen);
				if (ret != ZIP_OK)
				{

					zipCloseFileInZip(zf);
					zipClose(zf, NULL);
					remove(DestPath);
					vector<string>().swap(FileName);
					//FileName.swap(vector<string>());//�޸�
					return 1;
				}
				Sleep(80); //ʹcpu��ʹ���ʽ���
			} while (!infile.eof());
			zipCloseFileInZip(zf);
		}
		delete[] buf;
		zipClose(zf, NULL);
		vector<string>().swap(FileName);
		//FileName.swap(vector<string>());//�޸�
	}
	catch (...)
	{
		vector<string>().swap(FileName);
		//FileName.swap(vector<string>());//�޸�
		return 1;
	}
	return 0;

}



//��ĳ��Ŀ¼�����ļ�(dirName)ѹ��ΪzipFileName(.zip)�ļ�
void ZipHelper::CreateZipFromDir(string dirName, string zipFileName)
{
	long Handle;
	struct _finddata_t FileInfo;

	if ((Handle = _findfirst(dirName.c_str(), &FileInfo)) == -1L)//Ŀ¼������
		return;

	zipFile newZipFile = zipOpen(zipFileName.c_str(), APPEND_STATUS_CREATE); //����zip�ļ�    
	if (newZipFile == NULL)
	{
		printf("\n�޷�����zip�ļ�!");
		return;
	}
	if (FileInfo.attrib & _A_SUBDIR)// is a directory
	{
		string dirallfilestr = "";

		dirallfilestr += dirName;
		dirallfilestr += "//*.*";//find all files

		intptr_t Handle;
		struct _finddata_t dirFileInfo;

		if ((Handle = _findfirst(dirallfilestr.c_str(), &dirFileInfo)) == -1L)//Ŀ¼������
			return;
		string dircurrentPath;
		string dirfullPath;
		do
		{
			if (strlen(dirFileInfo.name) == 1 && dirFileInfo.name[0] == '.'
				|| strlen(dirFileInfo.name) == 2 && dirFileInfo.name[0] == '.'&&dirFileInfo.name[1] == '.')
				continue;//��ǰ�ļ��� ��һ��Ŀ¼
			dirfullPath = dirFileInfo.name;

			dircurrentPath = dirName;
			dircurrentPath += "//";
			dircurrentPath += dirFileInfo.name;

			if (dirFileInfo.attrib & _A_SUBDIR)
			{
				//AddFileToZip(newZipFile, fullPath, ""); //��zip�ļ�������Ŀ¼�ṹ
				CollectFilesInDirToZip(newZipFile, dircurrentPath, dirfullPath);//�ݹ��ռ���Ŀ¼�ļ�    
				continue;

			}
			else
				AddFileToZip(newZipFile, dirFileInfo.name, dircurrentPath);
		} while (_findnext(Handle, &dirFileInfo) == 0);//find next file



			//dirfullPath = dirName;
			//dirfullPath += "//";
			//dirfullPath += dirFileInfo.name;



		_findclose(Handle);//�޸ģ���2021.01.12��
	}
	else// is a file
		AddFileToZip(newZipFile, FileInfo.name, dirName);

	zipClose(newZipFile, NULL); //�ر�zip�ļ�    
}

//����7z.exe��ѹ�ļ�
void ZipHelper::exeUnCompress(string inpath, string zipout)
{
	string out = GetCurrentPath2();
	//7z.exe x test.zip -oD:\test -aoa
	string zipexe = out + "7z.exe x ";
	zipexe = zipexe.append(zipout);
	zipexe = zipexe.append(" -o");
	zipexe = zipexe.append(inpath);
	zipexe = zipexe.append(" -aoa");
	const char* c_s = zipexe.c_str();
	system(c_s);
}
ZipHelper::~ZipHelper()
{

}