
// 0141122299_zhangpeng.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy0141122299_zhangpengApp:
// �йش����ʵ�֣������ 0141122299_zhangpeng.cpp
//

class CMy0141122299_zhangpengApp : public CWinApp
{
public:
	CMy0141122299_zhangpengApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy0141122299_zhangpengApp theApp;