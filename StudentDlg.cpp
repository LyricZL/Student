
// StudentDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Student.h"
#include "StudentDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>
#include<list>
#include <iostream>
#include  "process.h"
#pragma warning( disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include "afxdialogex.h"
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct ThreadData     //添加的对话框数据结构
{
	CStudentDlg* pDlg;
	int nIndex;
}THREADDATA;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStudentDlg 对话框



CStudentDlg::CStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Student_DIALOG, pParent)
	, m_studentid(NULL)
	, m_studentname(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_studentid);
	DDX_Text(pDX, IDC_EDIT2, m_studentname);
	DDX_Control(pDX, IDC_PROGRESS1, m_process1);
}

BEGIN_MESSAGE_MAP(CStudentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CStudentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStudentDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CStudentDlg 消息处理程序

BOOL CStudentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStudentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStudentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CStudentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int m_studentid;
CString m_studentname;
CProgressCtrl m_process1;
CMutex mutexT;
CInfoFile::CInfoFile()
{
}

CInfoFile::~CInfoFile()
{
}
///读取文件数据到链表
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_login); //输入方式打开文件

	char buf[1024] = { 0 };
	//num = 0;	//初始化商品数目为0
	ls.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		Stu tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行

		char *sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.num = atoi(sst); //n
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.schoolid = atoi(sst);	//学号

		sst = strtok(NULL, "|");
		tmp.name = sst;	//姓名
		//if (tmp.xuehao == m_studentid)
		//{
		//	ifs.close();
		//	return -1;
		//	break;
		//}

		ls.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//写入链表数据到文件
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_login);//输出方式打开文件

	if (ls.size() > 0)	//链表有内容才执行
	{
		ofs << "ID|学号|姓名" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<Stu>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->num << "|";
			ofs << it->schoolid << "|";
			ofs << it->name << endl;
		}
	}

	ofs.close();//关闭文件
}

//添加数据到链表
void CInfoFile::Addline(int xuehao,CString name)
{
	Stu tmp;

	if (ls.size() > 0)
	{
		//商品名称，库存，价格有效
		if (!name.IsEmpty() )
		{
			tmp.num = ls.size() + 1;	//id自动加1
			CStringA str;
			str = name;	//CString转CStirngA
			tmp.schoolid = xuehao;
			tmp.name = str.GetBuffer(); //CStirngA转char *，姓名

			ls.push_back(tmp);	//放在链表的后面
		}
	}
}
//验证是否重复注册
int CInfoFile::CheckDocline(int m_studentid)
{
	ifstream ifs(_F_login); //输入方式打开文件

	char buf[1024] = { 0 };
	ls.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		Stu tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行

		char *sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.num = atoi(sst); //n
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.schoolid = atoi(sst);	//学号
		if (tmp.schoolid == m_studentid)
		{
			return 20;
			break;
		}
		sst = strtok(NULL, "|");
		tmp.name = sst;	//姓名
		ls.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//线程1
UINT ThreadFunc1(LPVOID param)
{
	THREADDATA* pData = (THREADDATA*)param;
	mutexT.Lock();
	CInfoFile file;
	if (file.CheckDocline(pData->pDlg->m_studentid) == 20)
	{
		pData->pDlg->MessageBox(TEXT("这个学号已经注册过了！"));
		Sleep(2000);
		TerminateThread(ThreadFunc1, 0);
	}
	else
	{
		file.ReadDocline();
		file.Addline(pData->pDlg->m_studentid, pData->pDlg->m_studentname);
		file.WirteDocline();
		pData->pDlg->MessageBox(TEXT("注册成功"));
	}
	
	mutexT.Unlock();
	return 0;
}

//线程2
UINT ThreadFunc2(LPVOID lParam)
{
	THREADDATA* pData = (THREADDATA*)lParam;
	mutexT.Lock();
	CInfoFile file1;
	if (pData->pDlg->m_studentid <= 0 || pData->pDlg->m_studentname.IsEmpty())
	{
		pData->pDlg->MessageBox(TEXT("输入内容不能为空"));
	}
	else
	{

		for (int i = 0; i <= 100; i++)
		{
			//更新对应进度条。
			Sleep(200);	//延缓时间
			pData->pDlg->m_process1.SetPos(i);
		}
	}
	mutexT.Unlock();
	return 0;
}

void CStudentDlg::OnBnClickedOk()
{
//更新数据并且初次判断
	UpdateData(TRUE);
	THREADDATA* pData = new THREADDATA;
	pData->nIndex = 1;
	pData->pDlg = this;
	AfxBeginThread(ThreadFunc2, pData);
	AfxBeginThread(ThreadFunc1, pData);

}

void CStudentDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
