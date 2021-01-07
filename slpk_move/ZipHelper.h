#pragma once
//#undef UNICODE
//#undef _UNICODE
#include <string>
#include <zlib.h>
#include"zlib/zip.h"
#include"zip.h"
#include<io.h>
#include <iostream>
#include<stdio.h>
#include<fstream>
#include<sstream>
#include<vector>
#include<stdlib.h>
#include <assert.h> 
#include <atlconv.h>
using namespace std;
class ZipHelper
{
public:
	ZipHelper();

	int Compress(string inpath, string zipout);//单文件压缩
	void exeCompress(string inpath, string zipout);//利用exe压缩单文件
	void exeCompressMore(string inpath, string zipout);//利用exe压缩目录下的多文件

	///int Compress(char * DestName, const char *SrcName);
	int CompressMore(const char * Directory, const char * DestPath, int type, int mode);//文件夹压缩
	//将某个目录或者文件(dirName)压缩为zipFileName(.zip)文件
	//void CreateZipFromDir(const char* dirName, const char* zipFileName);
	void CreateZipFromDir(string dirName, string zipFileName);
	void exeUnCompress(string inpath, string zipout);//利用exe解压目录
	~ZipHelper();
};

