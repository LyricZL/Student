
// Student.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"// 主符号
#include <iostream>
#include <fstream>
#include <string>
#include <list>

#define _F_login "./login.txt"

using namespace std;

struct Stu
{
	int schoolid;//学号
	int num;//计数n
	string name;//名字
};


// CStudentApp:
// 有关此类的实现，请参阅 Student.cpp
//

class CStudentApp : public CWinApp
{
public:
	CStudentApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CStudentApp theApp;


class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();
	//添加数据
	void Addline(int xuehao, CString name);
	//读取数据
	void ReadDocline();
	//写入数据
	void WirteDocline();
	int CheckDocline(int m_studentid);
	list<Stu> ls;
};