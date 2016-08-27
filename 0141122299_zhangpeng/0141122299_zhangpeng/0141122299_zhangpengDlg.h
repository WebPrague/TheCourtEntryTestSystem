
// 0141122299_zhangpengDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <string>
using namespace std;
// CMy0141122299_zhangpengDlg 对话框
class CMy0141122299_zhangpengDlg : public CDialogEx
{
// 构造
public:
	CMy0141122299_zhangpengDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY0141122299_ZHANGPENG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数

	//初始化函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//开始考试按钮
	CButton button_begin_exam;
	//开始考试消息
	afx_msg void OnBnClickedBeginExam();
	//定时器
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//总用时/秒
	int total_time;
	//计算生于时间
	CString getCountDownTime(int time_remaining);
	//剩余时间
	CString tv_time_remaining;
	//准考证号
	CString exam_number;
	//身份证号
	CString id_number;
	//判断准考证号
	int judge_exam_number(CString examNumber);
	//判断身份证号
	int judge_id_number(CString idNumber);
	//写入pdf文件
	int write_pdf(CString zkz, CString sfz, double zhun_que_lv, double da_zi_su_du, double cheng_ji, CString nei_rong);
	//定义输入编辑框
	CString input_text;
	//提交考试
	afx_msg void OnBnClickedOk();
	//音乐播放
	void OnPlay(int music_select);
	//字体颜色
	DWORD getinfo(UINT wDeviceID,DWORD item);
	//音乐播放停止
	void OnStop();
	//定义输入编辑框control类型变量
	CEdit in_text;
	//读取配置文件
	void readConfigureFile(void);
	//定义总用时
	int total_minutes;
	//定义总题数
	int total_questions;
	//定义音乐类型
	CString audio_format;
	//定义最大速度
	int max_speed;
	//定义准确率权重
	double percentage_accuracy;
	//定义速度权重
	double percentage_speed;
	//定义答案
	CString answer;
	//定义下拉菜单变量
	CComboBox btn_test_select;
	//定义控制类型的准考证号
	CEdit Exam_number;
	//定义控制类型的身份证号
	CEdit Id_number;
	//定义打印准考证
	CButton Print_report;
	//定义下拉菜单
	CString Btn_select_number;
	//打印成绩单
	afx_msg void OnBnClickedPrint();
	//计算两个文本的相似度
	int cmax(int a, int b);
	int cmin(int a, int b);
	int cmin(int a, int b, int c);
	float similarity(string str1, string str2);
	//改变字体颜色的函数
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//定义字体变量
	CFont m_editFont;
	CStatic m_static;
private:
	//定义字体变量
	CFont m_Font;

public:
	//加密函数
	CString encode(CString cs);
	//解密函数
	CString decode(CString cs);
	//校验身份证信息
	char getValidateCode(string id17);
	//自定义配置文件
	afx_msg void OnBnClickedConfig();
	//读取txt文件内容
	CString read_file(int answer_id);
};

