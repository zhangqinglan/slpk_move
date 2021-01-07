#pragma once
#include <string>
#include <vector>
#include <io.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <direct.h>
using namespace std;
class DeleteProcess
{
public:
	DeleteProcess();
	vector<string> deletefile(string dir);
	void deletedir(vector<string> dirname);
	void removeDir(string dirPath);
	~DeleteProcess();
};

