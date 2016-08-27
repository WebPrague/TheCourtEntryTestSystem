// ConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0141122299_zhangpeng.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"
#include "0141122299_zhangpengDlg.h"
#include<string>
using namespace std;

#include <Windows.h>


// ConfigDlg �Ի���

IMPLEMENT_DYNAMIC(ConfigDlg, CDialogEx)

ConfigDlg::ConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ConfigDlg::IDD, pParent)
	, bj_total_minutes(0)
	, bj_total_questions(0)
	, bj_audio_format(_T(""))
	, bj_max_speed(0)
	, bj_percentage_accuracy(0)
	, bj_percentage_speed(0)
	, xz_select_answer(_T(""))
	, bj_answer(_T(""))
	,selected(-1)
	, eb_file(_T(""))
{
	for (int i = 0 ; i < 100 ; i ++)
	{
		answer[i] = L"";
	}
}

ConfigDlg::~ConfigDlg()
{
}

void ConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Total_Minutes, bj_total_minutes);
	DDX_Text(pDX, IDC_Total_Questions, bj_total_questions);
	DDX_Text(pDX, IDC_Audio_Format, bj_audio_format);
	DDX_Text(pDX, IDC_Max_Speed, bj_max_speed);
	DDX_Text(pDX, IDC_Percentage_Accuracy, bj_percentage_accuracy);
	DDX_Text(pDX, IDC_Percentage_Speed, bj_percentage_speed);
	DDX_CBString(pDX, IDC_Select_Topic, xz_select_answer);
	DDX_Text(pDX, IDC_Answer, bj_answer);
	DDX_Control(pDX, IDC_Select_Topic, XZ_select_questions);
	DDX_Control(pDX, IDC_Answer, BJ_answer);
	DDX_Text(pDX, IDC_MFCEDITBROWSE, eb_file);
}


BEGIN_MESSAGE_MAP(ConfigDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ConfigDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_Total_Questions, &ConfigDlg::OnChangeTotalQuestions)
	ON_CBN_SELCHANGE(IDC_Select_Topic, &ConfigDlg::OnCbnSelchangeSelectTopic)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE, &ConfigDlg::OnEnChangeMfceditbrowse)
	//ON_EN_CHANGE(IDC_Answer, &ConfigDlg::OnEnChangeAnswer)
END_MESSAGE_MAP()


// ConfigDlg ��Ϣ�������


BOOL ConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��



	CEdit*  pEdit=(CEdit*)GetDlgItem(IDC_Audio_Format);//��ȡ��Ӧ�ı༭��ID
	pEdit->SetWindowText(_T("mp3")); //����Ĭ����ʾ������
	bj_max_speed = 100;
	bj_percentage_accuracy = 0.7;
	bj_percentage_speed = 0.3;
	bj_total_minutes = 15;
	bj_audio_format = L"mp3";
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//д�����ļ�
void ConfigDlg::configuration(void)
{
	UpdateData(TRUE);
	CString strtemp_total_minutes;
	strtemp_total_minutes.Format(L"%d",bj_total_minutes);
	CString strtemp_total_questions;
	strtemp_total_questions.Format(L"%d",bj_total_questions);
	CString strtemp_max_speed;
	strtemp_max_speed.Format(L"%d",bj_max_speed);
	CString strtemp_percentage_accuracy;
	strtemp_percentage_accuracy.Format(_T("%f"),bj_percentage_accuracy);
	CString strtemp_percentage_speed;
	strtemp_percentage_speed.Format(_T("%f"),bj_percentage_speed);
	WritePrivateProfileStringW(_T("ExamInfo"),_T("total_minutes"),strtemp_total_minutes,_T("ini/work.ini")); 	
	WritePrivateProfileStringW(_T("ExamInfo"),_T("total_questions"),strtemp_total_questions,_T("ini/work.ini"));  
	WritePrivateProfileStringW(_T("ExamInfo"),_T("audio_format"),bj_audio_format,_T("ini/work.ini"));  
	WritePrivateProfileStringW(_T("ExamInfo"),_T("max_speed"),strtemp_max_speed,_T("ini/work.ini")); 
	WritePrivateProfileStringW(_T("ExamInfo"),_T("percentage_accuracy"),strtemp_percentage_accuracy,_T("ini/work.ini")); 
	WritePrivateProfileStringW(_T("ExamInfo"),_T("percentage_speed"),strtemp_percentage_speed,_T("ini/work.ini")); 
	CString strtemp;
	for (int i=1;i<=bj_total_questions;i++)
	{
		//strtemp.Format(L"answer%d",i);
		CMy0141122299_zhangpengDlg dlg;
		//WritePrivateProfileStringW(_T("ExamInfo"),strtemp,dlg.encode(answer[i-1]),_T("ini/answer.ini"));
		CString cc = dlg.encode(answer[i-1]);
		add_file(i,cc);
	}
}

//�ύ�����ļ�
void ConfigDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
   //////////////////////////////////////////////////////////////////////////////////////////////////
	UpdateData(TRUE);
	if (selected != -1)
	{
		answer[selected] = bj_answer;
	}
	 configuration();
	CDialogEx::OnOK();
}

//ͬ���𰸱༭��������˵�ѡ��
void ConfigDlg::OnChangeTotalQuestions()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	XZ_select_questions.ResetContent();
	for (int i = 1;i<=bj_total_questions; i ++)
	{
		CString tmp;
		tmp.Format(L"%d",i);
		XZ_select_questions.AddString(tmp);
	}
}

//����Ԥ�ȴ����ڴ���
void ConfigDlg::OnCbnSelchangeSelectTopic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (selected != -1)
	{
		answer[selected] = bj_answer;
		file_paths[selected]=eb_file;
	}
	selected = XZ_select_questions.GetCurSel();
	bj_answer = answer[selected];
	eb_file=file_paths[selected];
	eb_file = "";
	UpdateData(FALSE);
}

//�õ������ļ�·��
void ConfigDlg::OnEnChangeMfceditbrowse()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������'
	UpdateData(TRUE);
	//�ļ����Ʋ���
	CString source = eb_file;
	source = L"\"" + source + L"\"";
	CString target;
	USES_CONVERSION;

	target.Format(L"\".\\mp3\\Music%d.",selected+1);
	target = target + bj_audio_format ;
	target = target + L"\"";

	CString comm = L"copy /y " + source + L" " + target;
	
	string str_comm = T2A(comm.GetBuffer());
	comm.ReleaseBuffer();
	system(str_comm.c_str());
}

//����д��txt�ļ�
void ConfigDlg::add_file(int answer_id, CString answer)
{
	//bj_answer.ReleaseBuffer();
	CFile Sfile;
	CString file_name;
	file_name.Format(L"./result/%d.txt",answer_id);
	Sfile.Open(file_name,CFile::modeCreate|CFile::modeWrite);
	USES_CONVERSION;
	char * ss = T2A(answer); 
	Sfile.Write(ss,strlen(ss));
	Sfile.Close();
}





