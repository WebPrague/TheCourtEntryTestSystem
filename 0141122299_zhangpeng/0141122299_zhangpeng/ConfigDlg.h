#pragma once
#include "afxwin.h"


// ConfigDlg 对话框

class ConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfigDlg)

public:
	ConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ConfigDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	//定义总用时
	int bj_total_minutes;
	//定义总题数
	int bj_total_questions;
	//定义音乐文件格式
	CString bj_audio_format;
	//定义最大速度
	int bj_max_speed;
	//定义准确率权重
	double bj_percentage_accuracy;
	//定义速度权重
	double bj_percentage_speed;
	//定义下拉菜单--选择题数
	CString xz_select_answer;
	//定义答案下拉选项
	CString bj_answer;
	//初始化文件
	virtual BOOL OnInitDialog();
	//配置文件函数
	void configuration(void);
	//提交选项
	afx_msg void OnBnClickedOk();
	//下拉选择题目选项
	CComboBox XZ_select_questions;
	afx_msg void OnChangeTotalQuestions();
	CEdit BJ_answer;
	afx_msg void OnCbnSelchangeSelectTopic();
	//定义答案数组
	CString answer[100];
	//定义答案文件存储路径
	CString file_paths[100];
	//定义选项
	int selected;
	afx_msg void OnEnChangeMfceditbrowse();
	//定义写文件变量
	CString eb_file;

	void add_file(int answer_id, CString answer);
};
