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

	int Compress(string inpath, string zipout);//���ļ�ѹ��
	void exeCompress(string inpath, string zipout);//����exeѹ�����ļ�
	void exeCompressMore(string inpath, string zipout);//����exeѹ��Ŀ¼�µĶ��ļ�

	///int Compress(char * DestName, const char *SrcName);
	int CompressMore(const char * Directory, const char * DestPath, int type, int mode);//�ļ���ѹ��
	//��ĳ��Ŀ¼�����ļ�(dirName)ѹ��ΪzipFileName(.zip)�ļ�
	//void CreateZipFromDir(const char* dirName, const char* zipFileName);
	void CreateZipFromDir(string dirName, string zipFileName);
	void exeUnCompress(string inpath, string zipout);//����exe��ѹĿ¼
	~ZipHelper();
};

