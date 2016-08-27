
// 0141122299_zhangpengDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <string>
using namespace std;
// CMy0141122299_zhangpengDlg �Ի���
class CMy0141122299_zhangpengDlg : public CDialogEx
{
// ����
public:
	CMy0141122299_zhangpengDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY0141122299_ZHANGPENG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��

	//��ʼ������
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//��ʼ���԰�ť
	CButton button_begin_exam;
	//��ʼ������Ϣ
	afx_msg void OnBnClickedBeginExam();
	//��ʱ��
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//����ʱ/��
	int total_time;
	//��������ʱ��
	CString getCountDownTime(int time_remaining);
	//ʣ��ʱ��
	CString tv_time_remaining;
	//׼��֤��
	CString exam_number;
	//���֤��
	CString id_number;
	//�ж�׼��֤��
	int judge_exam_number(CString examNumber);
	//�ж����֤��
	int judge_id_number(CString idNumber);
	//д��pdf�ļ�
	int write_pdf(CString zkz, CString sfz, double zhun_que_lv, double da_zi_su_du, double cheng_ji, CString nei_rong);
	//��������༭��
	CString input_text;
	//�ύ����
	afx_msg void OnBnClickedOk();
	//���ֲ���
	void OnPlay(int music_select);
	//������ɫ
	DWORD getinfo(UINT wDeviceID,DWORD item);
	//���ֲ���ֹͣ
	void OnStop();
	//��������༭��control���ͱ���
	CEdit in_text;
	//��ȡ�����ļ�
	void readConfigureFile(void);
	//��������ʱ
	int total_minutes;
	//����������
	int total_questions;
	//������������
	CString audio_format;
	//��������ٶ�
	int max_speed;
	//����׼ȷ��Ȩ��
	double percentage_accuracy;
	//�����ٶ�Ȩ��
	double percentage_speed;
	//�����
	CString answer;
	//���������˵�����
	CComboBox btn_test_select;
	//����������͵�׼��֤��
	CEdit Exam_number;
	//����������͵����֤��
	CEdit Id_number;
	//�����ӡ׼��֤
	CButton Print_report;
	//���������˵�
	CString Btn_select_number;
	//��ӡ�ɼ���
	afx_msg void OnBnClickedPrint();
	//���������ı������ƶ�
	int cmax(int a, int b);
	int cmin(int a, int b);
	int cmin(int a, int b, int c);
	float similarity(string str1, string str2);
	//�ı�������ɫ�ĺ���
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//�����������
	CFont m_editFont;
	CStatic m_static;
private:
	//�����������
	CFont m_Font;

public:
	//���ܺ���
	CString encode(CString cs);
	//���ܺ���
	CString decode(CString cs);
	//У�����֤��Ϣ
	char getValidateCode(string id17);
	//�Զ��������ļ�
	afx_msg void OnBnClickedConfig();
	//��ȡtxt�ļ�����
	CString read_file(int answer_id);
};

