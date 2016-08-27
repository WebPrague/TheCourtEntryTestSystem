#pragma once
#include "afxwin.h"


// ConfigDlg �Ի���

class ConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfigDlg)

public:
	ConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ConfigDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	//��������ʱ
	int bj_total_minutes;
	//����������
	int bj_total_questions;
	//���������ļ���ʽ
	CString bj_audio_format;
	//��������ٶ�
	int bj_max_speed;
	//����׼ȷ��Ȩ��
	double bj_percentage_accuracy;
	//�����ٶ�Ȩ��
	double bj_percentage_speed;
	//���������˵�--ѡ������
	CString xz_select_answer;
	//���������ѡ��
	CString bj_answer;
	//��ʼ���ļ�
	virtual BOOL OnInitDialog();
	//�����ļ�����
	void configuration(void);
	//�ύѡ��
	afx_msg void OnBnClickedOk();
	//����ѡ����Ŀѡ��
	CComboBox XZ_select_questions;
	afx_msg void OnChangeTotalQuestions();
	CEdit BJ_answer;
	afx_msg void OnCbnSelchangeSelectTopic();
	//���������
	CString answer[100];
	//������ļ��洢·��
	CString file_paths[100];
	//����ѡ��
	int selected;
	afx_msg void OnEnChangeMfceditbrowse();
	//����д�ļ�����
	CString eb_file;

	void add_file(int answer_id, CString answer);
};
