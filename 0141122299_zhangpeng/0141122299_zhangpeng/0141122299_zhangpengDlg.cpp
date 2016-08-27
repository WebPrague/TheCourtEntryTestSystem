
// 0141122299_zhangpengDlg.cpp : 实现文件
//

#include<stdio.h>
#include "stdafx.h"
#include "0141122299_zhangpeng.h"
#include "0141122299_zhangpengDlg.h"
#include "afxdialogex.h"
#include "mmsystem.h"
#include "pdflib.h"
#include<string>
#include<sstream>
#include<Windows.h>

#include "ConfigDlg.h"

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma   comment(lib, "winmm.lib")
#pragma comment(lib, "PDFLib.lib")
// CMy0141122299_zhangpengDlg 对话框


MCI_OPEN_PARMS op;


CMy0141122299_zhangpengDlg::CMy0141122299_zhangpengDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy0141122299_zhangpengDlg::IDD, pParent)
	, total_time(0)
	, tv_time_remaining(_T(""))
	, exam_number(_T(""))
	, id_number(_T(""))
	, input_text(_T(""))
	, total_minutes(0)
	, Btn_select_number(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy0141122299_zhangpengDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Begin_Exam, button_begin_exam);
	DDX_Text(pDX, IDC_Time_Remaining, tv_time_remaining);
	DDX_Text(pDX, IDC_EDIT1, exam_number);
	DDV_MaxChars(pDX, exam_number, 11);
	DDX_Text(pDX, IDC_EDIT2, id_number);
	DDV_MaxChars(pDX, id_number, 18);
	DDX_Text(pDX, IDC_Text, input_text);
	DDX_Control(pDX, IDC_Text, in_text);
	DDX_Control(pDX, IDC_COMBO1, btn_test_select);
	DDX_Control(pDX, IDC_EDIT1, Exam_number);
	DDX_Control(pDX, IDC_EDIT2, Id_number);
	DDX_Control(pDX, IDC_Print, Print_report);
	DDX_CBString(pDX, IDC_COMBO1, Btn_select_number);
	DDX_Control(pDX, IDC_Time_Remaining, m_static);
}

BEGIN_MESSAGE_MAP(CMy0141122299_zhangpengDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Begin_Exam, &CMy0141122299_zhangpengDlg::OnBnClickedBeginExam)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CMy0141122299_zhangpengDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_Print, &CMy0141122299_zhangpengDlg::OnBnClickedPrint)
	ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_Config, &CMy0141122299_zhangpengDlg::OnBnClickedConfig)
END_MESSAGE_MAP()
// CMy0141122299_zhangpengDlg 消息处理程序

BOOL CMy0141122299_zhangpengDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	

	m_Font.CreatePointFont(100,_T("华文楷体"),NULL);
	m_static.SetFont(&m_editFont,true);
	readConfigureFile();
	CWnd *pWnd = GetDlgItem(IDC_Print);
	pWnd->EnableWindow(FALSE);
	pWnd = GetDlgItem(IDOK);
	pWnd->EnableWindow(FALSE);
	CEdit * pEdit = (CEdit*)GetDlgItem(IDC_Text);
	pEdit->SetSel(-1);
	pEdit->SetFocus();   
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy0141122299_zhangpengDlg::OnPaint()
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
HCURSOR CMy0141122299_zhangpengDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//开始考试
void CMy0141122299_zhangpengDlg::OnBnClickedBeginExam()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int input_examNumber=judge_exam_number(exam_number);
	if(input_examNumber==1)
	{
		MessageBox(_T("准考证为11位数字"));
	    return;
	}

	int input_idNumber=judge_id_number(id_number);
	if(input_idNumber==1)
	{
		 MessageBox(_T("身份证号为18位数字（最后一位可以是x，支持大小写）"));
         return;
	}
	  if ( input_idNumber== 2)
    {
        MessageBox(_T("对不起，您的年龄不在合法的职工年龄范围"));
        return;
    }
    if (input_idNumber == 3)
    {
        MessageBox(_T("身份证号码错误"));
        return;
    }
	button_begin_exam.EnableWindow(FALSE);
	SetTimer(1,1000,NULL);

	OnPlay(	btn_test_select.GetCurSel()+1);
	Invalidate();
	Exam_number.EnableWindow(FALSE);
	Id_number.EnableWindow(FALSE);
	btn_test_select.EnableWindow(FALSE);
	CWnd *pWnd = GetDlgItem(IDOK);
	pWnd->EnableWindow(TRUE);
	readConfigureFile();
}


//倒计时
void CMy0141122299_zhangpengDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(TRUE);
    tv_time_remaining=getCountDownTime(++total_time);
	if(total_time==total_minutes*60)
	{
		in_text.EnableWindow(FALSE);
	     KillTimer(1);
	}
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}
CString CMy0141122299_zhangpengDlg::getCountDownTime(int time_remaining)
{
	int total=total_minutes*60 - time_remaining;
	int sec=total%60;
	int min=total/60;
	CString time ;
	time.Format(L"剩余考试时间：     %d分%d秒",min,sec);
	return time;
}

//检查身份
int CMy0141122299_zhangpengDlg::judge_exam_number(CString examNumber)
{
	int size=examNumber.GetLength();
	if(size==11)
		return 0;
	return 1;
}
int CMy0141122299_zhangpengDlg::judge_id_number(CString idNumber)
{
	int size=idNumber.GetLength();
	if(size!=18)
	{
		return 1;
	}
	
	USES_CONVERSION;
	string str_id_number = T2A(idNumber);
	string str_id_17 = str_id_number.substr(0,17);
	char c_id_18 = str_id_number[17];
	if (getValidateCode(str_id_17) != c_id_18)
	{
		return 3;
	}
	return 0;
}

//提交考试
void CMy0141122299_zhangpengDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
    int nRes = MessageBox(L"提交之后您的本次考试将结束，\n您确定要提交吗？",L"提示",MB_ICONASTERISK|MB_OKCANCEL);
	if (IDOK == nRes)
	{
	
		KillTimer(1);
		tv_time_remaining.Format(L"考试总用时：\n%d分%d秒",total_time/60,total_time%60);
		UpdateData(FALSE);
		CWnd *pWnd = GetDlgItem(IDC_Print);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDOK);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_Text);
		pWnd->EnableWindow(FALSE);
		OnStop();
	}
}


//读音乐文件
void CMy0141122299_zhangpengDlg::OnPlay(int music_select)
{
 // TODO: Add your control notification handler code here
 DWORD cdlen;//音频文件长度

 op.dwCallback=NULL;
 op.lpstrAlias=NULL;
 op.lpstrDeviceType=_T("MPEGAudio");  //设备类型，大多数文件可以这样设置
 CString filename;
 filename.Format(L"mp3/Music%d.",music_select);
 
 audio_format.ReleaseBuffer();

 filename = filename + audio_format;

 op.lpstrElementName= filename; //文件路径
 op.wDeviceID=NULL;      //打开设备成功以后保存这个设备号备用
 UINT rs;        //接受函数返回结果
 //发送命令打开设备，成功返回0，否则返回错误号，第三个参数这里必须MCI_OPEN_ELEMENT  
 rs=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)&op);

 mciSendCommand(NULL,MCI_SET,MCI_SET_DOOR_OPEN,NULL);

 cdlen=getinfo(op.wDeviceID,MCI_STATUS_LENGTH);//获取音频文件长度

 if(rs==0)        //设备打开成功就播放文件
 {
  MCI_PLAY_PARMS pp;
  pp.dwCallback=NULL;
  pp.dwFrom=0;      //开始播放的位置
  mciSendCommand(op.wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)&pp);
  //播放文件，如果第三个参数设为MCI_WAIT则程序窗口会被阻塞，为了避免这种情况可以设为MCI_NOTIFY
 }

 //Sleep(cdlen);//根据文件长度等待，与MCI_WAIT效果一样，cdlen参数可以控制播放时间
 //OnStop();        //关闭音频文件 
}
DWORD CMy0141122299_zhangpengDlg::getinfo(UINT wDeviceID,DWORD item)
{
 MCI_STATUS_PARMS mcistatusparms;
 mcistatusparms.dwCallback=(DWORD)GetSafeHwnd();
 mcistatusparms.dwItem=item;
 mcistatusparms.dwReturn=0;
 mciSendCommand(wDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)&mcistatusparms);
 return mcistatusparms.dwReturn;
}
void CMy0141122299_zhangpengDlg::OnStop()
{
 // TODO: Add your control notification handler code here
 //在WM_CLOSE消息处理过程中发送MCI_CLOSE命令关闭设备
 MCI_GENERIC_PARMS gp;
 gp.dwCallback=NULL;
 mciSendCommand(op.wDeviceID,MCI_CLOSE,MCI_WAIT,(DWORD)&gp);  
}


//读配置文件
void CMy0141122299_zhangpengDlg::readConfigureFile(void)
{
	total_minutes = GetPrivateProfileInt(L"ExamInfo",L"total_minutes",0,L"ini/work.ini");
	total_questions = GetPrivateProfileInt(L"ExamInfo",L"total_questions",0,L"ini/work.ini");
	GetPrivateProfileString(L"ExamInfo",L"audio_format",L"",audio_format.GetBuffer(MAX_PATH),MAX_PATH,L"ini/work.ini");
	max_speed = GetPrivateProfileInt(L"ExamInfo",L"max_speed",0,L"ini/work.ini");
	CString tmp;
	string str_tmp;
	USES_CONVERSION;
	stringstream oss;
	GetPrivateProfileString(L"ExamInfo",L"percentage_accuracy",L"",tmp.GetBuffer(MAX_PATH),MAX_PATH,L"ini/work.ini");
	str_tmp = T2A(tmp.GetBuffer());
	oss<<str_tmp;
	oss>>percentage_accuracy;
	oss.clear();
	GetPrivateProfileString(L"ExamInfo",L"percentage_speed",L"",tmp.GetBuffer(MAX_PATH),MAX_PATH,L"ini/work.ini");
	str_tmp = T2A(tmp.GetBuffer());
	oss<<str_tmp;
	oss>>percentage_speed;

	/*
	CString c;
	c.Format(L"answer%d",btn_test_select.GetCurSel()+1);
	GetPrivateProfileString(L"ExamInfo",c,L"",answer.GetBuffer(MAX_PATH),MAX_PATH,L"ini/answer.ini");
	answer.ReleaseBuffer();
	answer = decode(answer);
	*/
	if (btn_test_select.GetCurSel() +1 > 0)
	{
		int a = btn_test_select.GetCurSel();
		answer = decode(read_file(btn_test_select.GetCurSel() + 1));
	}


	btn_test_select.ResetContent();
	for (int i = 1;i<=total_questions; i ++)
	{
		CString tmp;
		tmp.Format(L"0%d",i);
		btn_test_select.AddString(tmp);
	}
	btn_test_select.SetCurSel(0);
	return;
}

//写入pdf文件
int CMy0141122299_zhangpengDlg::write_pdf(CString zkz, CString sfz, double zhun_que_lv, double da_zi_su_du, double cheng_ji, CString nei_rong)
{
	remove("成绩单.pdf");

	PDF *p;

	if ((p = PDF_new()) == (PDF *) 0){
		printf("Couldn't create PDFlib object (out of memory)!/n");
		return 1;
	}

	PDF_TRY(p) {
		/* This means we must check return values of load_font() etc. */
		if (PDF_begin_document(p, "./成绩单.pdf", 0, "") == -1) {
			printf("Error: %s/n", PDF_get_errmsg(p));
			return 2;
		}
		/* This line is required to avoid problems on Japanese systems */
		PDF_set_parameter(p, "hypertextencoding", "host");
		PDF_set_info(p, "Creator", "hello.c");
		PDF_set_info(p, "Author", "Thomas Merz");
		PDF_set_info(p, "Title", "Hello, world (C)!");

		PDF_begin_page_ext(p, a4_width, a4_height, "");

		int font_song = PDF_findfont(p,"STSong-Light", "GB-EUC-H", 0);
		PDF_setfont(p,font_song, 12);
		PDF_set_text_pos(p,50, a4_height - 50);
		USES_CONVERSION;
		string s = T2A(( zkz.GetBuffer()));
		s = "准考证号：" + s;
		PDF_show(p,s.c_str());
		PDF_set_text_pos(p,50, a4_height - 65);
		s = T2A(( sfz.GetBuffer()));
		s = "身份证号：" + s;
		PDF_show(p,s.c_str());
		PDF_setfont(p,font_song, 8);
		PDF_set_text_pos(p,50, a4_height - 85);
		CString cs;
		cs.Format(L"您打字的正确率是%f，速度是%f字/分钟，本次考试的成绩是%f分",zhun_que_lv,da_zi_su_du,cheng_ji);
		s = T2A(cs.GetBuffer());
		PDF_show(p,s.c_str());
		PDF_setfont(p,font_song, 8);
		PDF_set_text_pos(p,50, a4_height - 100);
		s="以下是您本次考试录入的内容:";
		PDF_show(p,s.c_str());
		s = T2A(nei_rong.GetBuffer());
		for (int i = 0 ; i <= s.length()/90 ; i++)
		{
			PDF_set_text_pos(p,50, a4_height - 130 - i * 10);

			int begin = 0+90*i;
			int end = 90;
			if (90 + 90 * i >= s.length())
			{
				end = s.length()-begin;
			}else{
				end = 90 ;
			}
			string tmp = s.substr(begin,end);
			PDF_show(p,tmp.c_str());
		}
		PDF_end_page_ext(p, "");
		PDF_end_document(p, "");
	}

	PDF_CATCH(p) {
		printf("PDFlib exception occurred in sample:/n");
		printf("[%d] %s: %s/n",
			PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
		CString cs;
		cs.Format(L"[%d] %s: %s/n",
			PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
		PDF_delete(p);

		return 3;
	}

	PDF_delete(p);
	return 0;
}

//打印成绩单
void CMy0141122299_zhangpengDlg::OnBnClickedPrint()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int speed = input_text.GetLength() / total_time * 60;
	if (speed > max_speed)
	{
		speed = max_speed;
	}
	USES_CONVERSION;
	string str_answer = T2A(answer.GetBuffer());
	string str_input = T2A(input_text.GetBuffer());

	double accuracy = 100 * similarity(str_input,str_answer);
	double score =  percentage_speed * speed + percentage_accuracy * accuracy;

	write_pdf(exam_number,id_number,accuracy,speed,score,input_text);
	system("成绩单.pdf");
}

//计算文本相似度
int CMy0141122299_zhangpengDlg::cmax(int a, int b)
{
	return a>b?a:b;
}
int CMy0141122299_zhangpengDlg::cmin(int a, int b)
{
	return a<b?a:b;
}
int CMy0141122299_zhangpengDlg::cmin(int a, int b, int c)
{
	return cmin(cmin(a,b),c);
}
float CMy0141122299_zhangpengDlg::similarity(string str1, string str2)
{
	//计算两个字符串的长度。
	int len1 = str1.length();
	int len2 = str2.length();
	//建立数组，比字符长度大一个空间
	int **dif;
	dif = new int*[len1+1];
	for (int i = 0 ; i < len1 +1 ; i++)
	{
		dif[i] = new int[len2+1];
	}
	//赋初值，步骤B。
	for (int a = 0; a <= len1; a++) {
		dif[a][0] = a;
	}
	for (int a = 0; a <= len2; a++) {
		dif[0][a] = a;
	}
	//计算两个字符是否一样，计算左上的值
	int temp;
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (str1.at(i - 1) == str2.at(j - 1)) {
				temp = 0;
			} else {
				temp = 1;
			}
			//取三个值中最小的
			dif[i][j] = cmin(dif[i - 1][j - 1] + temp, dif[i][j - 1] + 1,
				dif[i - 1][j] + 1);
		}
	}
	return 1 - (float) dif[len1][len2] / cmax(str1.length(), str2.length());
}

//修改考试信息的文字颜色
HBRUSH CMy0141122299_zhangpengDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if(IDC_Time_Remaining==pWnd->GetDlgCtrlID())
	{
	   pDC->SetTextColor(RGB(255,0,0));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//加密函数
CString CMy0141122299_zhangpengDlg::encode(CString cstr)
{
	CString tmp = L"";
	int str_len = cstr.GetLength();
	int setpLength = 1;
	for(int i = 0 ; i < str_len ; i ++ )
	{

		wchar_t wc = cstr.GetAt(i);
		wc = wc + setpLength;
		tmp = tmp + wc;
	}
	return tmp;

}

//解密函数
CString CMy0141122299_zhangpengDlg::decode(CString cstr)
{
	CString tmp = L"";
	int str_len = cstr.GetLength();
	int setpLength = 1;
	for(int i = 0 ; i < str_len ; i ++ )
	{

		wchar_t wc = cstr.GetAt(i);
		wc = wc - setpLength;
		tmp = tmp + wc;
	}
	return tmp;

}

//校验身份信息
char CMy0141122299_zhangpengDlg::getValidateCode(string id17)
{
	int weight[]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};    //十七位数字本体码权重
	char validate[]={ '1','0','X','9','8','7','6','5','4','3','2'};    //mod11,对应校验码字符值    

	int sum=0;
	int mode=0;
	for(int i=0;i<id17.length();i++){
		sum=sum+(id17[i]-'0')*weight[i];
	}
	mode=sum%11;
	return validate[mode];
}

//自定义配置文件
void CMy0141122299_zhangpengDlg::OnBnClickedConfig()
{
	// TODO: 在此添加控件通知处理程序代码

      ConfigDlg Dlg2;
	  Dlg2.DoModal();

	  readConfigureFile();
}






//读取txt文件
CString CMy0141122299_zhangpengDlg::read_file(int answer_id)
{
	CString file_name;
	file_name.Format(L"./result/%d.txt",answer_id);
	CFile pfile(file_name,CFile::modeRead);
	char* pBuf;
	DWORD dwFileLen;
	dwFileLen = pfile.GetLength();
	pBuf=new char[dwFileLen+1];
	pBuf[dwFileLen]=0;
	pfile.Read(pBuf,dwFileLen);
	CString cstr(pBuf);
	//MessageBox(cstr);
	pfile.Close();
	return cstr;
}
