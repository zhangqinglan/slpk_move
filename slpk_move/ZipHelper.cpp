#include "ZipHelper.h"
#include<io.h>
#pragma warning(disable : 4996)

#define MAX_LEN 1024*100//本例只适用于小于100KB的文件


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
	//修改
	//char* zipout = zipout;
	//zipOpen64()
	zf = zipOpen64(zipout.c_str(), 0);

	zip_fileinfo FileInfo;
	ZeroMemory(&FileInfo, sizeof(FileInfo));
	zipOpenNewFileInZip(zf, inpath.c_str(), &FileInfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, 9);//修改
	ifstream infile(inpath.c_str(), ios::binary);//修改
	infile.read(buf, MAX_LEN);
	uLong readlen = infile.gcount();
	ret = zipWriteInFileInZip(zf, buf, readlen);
	zipCloseFileInZip(zf);
	delete[] buf;
	zipClose(zf, 0);
	return 0;
}
//获取当前路径
string GetCurrentPath2()
{
	char apppath[MAX_PATH] = { 0 };
	string tmppath = "";
	GetModuleFileNameA(NULL, apppath, MAX_PATH);
	tmppath = (string)apppath;
	tmppath = tmppath.replace(tmppath.find("slpk_move.exe"), 13, "");
	return tmppath;
}


//利用7z.exe进行文件压缩
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

void ZipHelper::exeCompressMore(string inpath, string zipout)//利用exe压缩目录下的多文件
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
	intptr_t hFile = 0; //注意这里，文件句柄
	_finddata_t fileinfo;
	string p;
	vector<string> FileName;

	if ((hFile = _findfirst(p.assign(Directory).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录则递归
			//如果不是则加入vector 
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
		FileName.push_back(Directory); //是文件直接加入
	return FileName;
}

//压缩多种类型文件
//将文件添加到zip文件中，注意如果源文件srcFile为空则添加空目录    
//fileNameInZip: 在zip文件中的文件名，包含相对路径    
void AddFileToZip(zipFile zf, string fileNameInZip, string srcFile)
{
	FILE* srcfp = NULL;

	//初始化写入zip的文件信息
	//zip_fileinfo zi;
	zip_fileinfo   zi = { 0 };

	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
		zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
	zi.dosDate = 0;
	zi.internal_fa = 0;
	zi.external_fa = 0;

	//如果srcFile为空，加入空目录    
	string new_file_name = "";
	//if (fileNameInZip == "json")
	//	fileNameInZip = "";
	new_file_name += fileNameInZip;
	if (srcFile == "")
	{
		new_file_name += "/";
	}

	//在zip文件中创建新文件    
	//zipOpenNewFileInZip(zf, new_file_name.c_str(), &zi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);
	zipOpenNewFileInZip(zf, new_file_name.c_str(), &zi, NULL, 0, NULL, 0, NULL, 0, Z_DEFAULT_COMPRESSION);//注意这里，0，默认压缩算法为Store.

	if (srcFile != "")
	{
		//打开源文件    
		fopen_s(&srcfp, srcFile.c_str(), "rb");
		if (srcfp == NULL)
		{
			printf("无法添加文件: %s !\n", srcFile);
			zipCloseFileInZip(zf); //关闭zip文件  
			return;
		}

		//读入源文件并写入zip文件    
		char buf[100 * 1024]; //buffer    
		int numBytes = 0;
		while (!feof(srcfp))
		{
			numBytes = fread(buf, 1, sizeof(buf), srcfp);
			zipWriteInFileInZip(zf, buf, numBytes);
			if (ferror(srcfp))
				break;
		}

		//关闭源文件    
		fclose(srcfp);
	}

	//关闭zip文件    
	zipCloseFileInZip(zf);
}


//递归添加子目录到zip文件    
void CollectFilesInDirToZip(zipFile zf, string strPath, string parentDir)
{
	string allfilestr = "";

	allfilestr += strPath;
	allfilestr += "//*.*";//find all files

	intptr_t Handle;
	struct _finddata_t FileInfo;

	if ((Handle = _findfirst(allfilestr.c_str(), &FileInfo)) == -1L)//目录不存在
		return;

	string currentPath;
	string fullPath;

	do
	{
		if (strlen(FileInfo.name) == 1 && FileInfo.name[0] == '.'
			|| strlen(FileInfo.name) == 2 && FileInfo.name[0] == '.'&&FileInfo.name[1] == '.')
			continue;//当前文件夹 上一层目录

		if (parentDir.length() != 0)
		{
			//if (parentDir == "json")
			//	parentDir = "";
			fullPath = parentDir;
			fullPath += "/";
			fullPath += FileInfo.name;//生成在zip文件中的相对路径
		}
		else
			fullPath += FileInfo.name;

		currentPath = strPath;
		currentPath += "//";
		currentPath += FileInfo.name;

		if (FileInfo.attrib & _A_SUBDIR)// is a directory
		{
			AddFileToZip(zf, fullPath, ""); //在zip文件中生成目录结构
			CollectFilesInDirToZip(zf, currentPath, fullPath);//递归收集子目录文件    
			continue;
		}
		AddFileToZip(zf, fullPath, currentPath); //将文件添加到zip文件中
	} while (_findnext(Handle, &FileInfo) == 0);//find next file
	_findclose(Handle);//修改：（2021.01.12）
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
			//FileName.swap(vector<string>()); //清空vector的内存//修改
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
				//FileName.swap(vector<string>());//修改
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
					//FileName.swap(vector<string>());//修改
					return 1;
				}
				Sleep(80); //使cpu的使用率降低
			} while (!infile.eof());
			zipCloseFileInZip(zf);
		}
		delete[] buf;
		zipClose(zf, NULL);
		vector<string>().swap(FileName);
		//FileName.swap(vector<string>());//修改
	}
	catch (...)
	{
		vector<string>().swap(FileName);
		//FileName.swap(vector<string>());//修改
		return 1;
	}
	return 0;

}



//将某个目录或者文件(dirName)压缩为zipFileName(.zip)文件
void ZipHelper::CreateZipFromDir(string dirName, string zipFileName)
{
	long Handle;
	struct _finddata_t FileInfo;

	if ((Handle = _findfirst(dirName.c_str(), &FileInfo)) == -1L)//目录不存在
		return;

	zipFile newZipFile = zipOpen(zipFileName.c_str(), APPEND_STATUS_CREATE); //创建zip文件    
	if (newZipFile == NULL)
	{
		printf("\n无法创建zip文件!");
		return;
	}
	if (FileInfo.attrib & _A_SUBDIR)// is a directory
	{
		string dirallfilestr = "";

		dirallfilestr += dirName;
		dirallfilestr += "//*.*";//find all files

		intptr_t Handle;
		struct _finddata_t dirFileInfo;

		if ((Handle = _findfirst(dirallfilestr.c_str(), &dirFileInfo)) == -1L)//目录不存在
			return;
		string dircurrentPath;
		string dirfullPath;
		do
		{
			if (strlen(dirFileInfo.name) == 1 && dirFileInfo.name[0] == '.'
				|| strlen(dirFileInfo.name) == 2 && dirFileInfo.name[0] == '.'&&dirFileInfo.name[1] == '.')
				continue;//当前文件夹 上一层目录
			dirfullPath = dirFileInfo.name;

			dircurrentPath = dirName;
			dircurrentPath += "//";
			dircurrentPath += dirFileInfo.name;

			if (dirFileInfo.attrib & _A_SUBDIR)
			{
				//AddFileToZip(newZipFile, fullPath, ""); //在zip文件中生成目录结构
				CollectFilesInDirToZip(newZipFile, dircurrentPath, dirfullPath);//递归收集子目录文件    
				continue;

			}
			else
				AddFileToZip(newZipFile, dirFileInfo.name, dircurrentPath);
		} while (_findnext(Handle, &dirFileInfo) == 0);//find next file



			//dirfullPath = dirName;
			//dirfullPath += "//";
			//dirfullPath += dirFileInfo.name;



		_findclose(Handle);//修改：（2021.01.12）
	}
	else// is a file
		AddFileToZip(newZipFile, FileInfo.name, dirName);

	zipClose(newZipFile, NULL); //关闭zip文件    
}

//利用7z.exe解压文件
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