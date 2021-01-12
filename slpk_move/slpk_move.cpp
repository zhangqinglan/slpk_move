// slpk_move.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//slpk模型平移：x,y,z方向上移动，需要修改slpk文件中的3dScenelayer.json中的extent
//修改nodepages中center值

#include <iostream>
#include "ZipHelper.h"
#include "JsonModify.h"
#include "DeleteProcess.h"

int main()
{

	////测试：平移（2021.01.08）
	//string inslpk = "D:/work_data/work_code/I3S工具/test/wout0/w.slpk", outslpk1 = "D:/work_data/work_code/投影改变/slpk包/result";
	//double dx = 100, dy = 100, dz = 100;
	////cout << "输入平移前的slpk文件：\n";
	////cin >> inslpk;
	////cout << "分别输入x,y,z方向上的平移值（单位为米）：\n";
	////cin >> dx;
	////cin >> dy;
	////cin >> dz;
	////解压slpk
	//ZipHelper unslpk;
	//unslpk.exeUnCompress("process", inslpk.c_str());
	////修改相关json文件
	//JsonModify modifyjson(dx,dy,dz);
	//modifyjson.modify3dScene();
	//modifyjson.modifycenter();
	////压缩process文件为slpk
	//string inslpkname = inslpk.substr(0, inslpk.find_last_of('.') );
	//string outslpk = inslpkname + "_move.slpk";
	//
	//unslpk.CreateZipFromDir("process", outslpk);
	//DeleteProcess delprocess;
	//delprocess.removeDir("process");



	//测试：旋转（2021.01.08）
	string inslpk = "D:/work_data/work_code/I3S工具/test/wout0/w.slpk", outslpk1 = "D:/work_data/work_code/投影改变/slpk包/result";
	float dx = 70751.371781888927, dy = 230271.74700546623, dz = 38.332534790039063;
	float angle = 90;
	//cout << "输入平移前的slpk文件：\n";
	//cin >> inslpk;
	//cout << "分别输入x,y,z方向上的平移值（单位为米）：\n";
	//cin >> dx;
	//cin >> dy;
	//cin >> dz;
	//解压slpk
	ZipHelper unslpk;
	unslpk.exeUnCompress("process", inslpk.c_str());
	//修改相关json文件
	JsonModify modifyjson(dx, dy, dz, angle);
	modifyjson.spinmodify3dScene();
	modifyjson.spinmodifycenter();
	//压缩process文件为slpk
	string inslpkname = inslpk.substr(0, inslpk.find_last_of('.'));
	string outslpk = inslpkname + "_spin.slpk";

	unslpk.CreateZipFromDir("process", outslpk);
	//system("pause");
	DeleteProcess delprocess;
	delprocess.removeDir("process");


}

