
// PInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PInfo.h"
#include "PInfoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPInfoDlg 对话框



CPInfoDlg::CPInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PINFO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPInfoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GAME, &CPInfoDlg::OnBnClickedGame)
	ON_BN_CLICKED(IDC_BUTTON2, &CPInfoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_PLAY_IT, &CPInfoDlg::OnBnClickedPlayIt)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPInfoDlg 消息处理程序

BOOL CPInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	SetDlgItemText(IDC_NAME, L"张三");
	CheckRadioButton(IDC_MALE, IDC_FEMALE, IDC_MALE);
	SetDlgItemInt(IDC_AGE, 22);

	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_AGE);
	pSpin->SetRange(0, 150);

	CListBox* pLB = (CListBox*)GetDlgItem(IDC_EDU);
	pLB->AddString(L"大专");
	pLB->AddString(L"本科");
	pLB->AddString(L"硕士");
	pLB->AddString(L"博士");
	pLB->SetCurSel(1);

	CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_MAJOR);
	pCB->AddString(L"国际经济与贸易");
	pCB->AddString(L"法学");
	pCB->AddString(L"计算机科学与技术");
	pCB->AddString(L"网络工程");
	pCB->AddString(L"信息安全");
	pCB->SetCurSel(2);	//设置默认初始选中的项
	CheckDlgButton(IDC_ART, 1);
	CheckDlgButton(IDC_SPORT, 1);


	//设置进度条
	pch = (CProgressCtrl *)GetDlgItem(IDC_PCH);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPInfoDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPInfoDlg::OnBnClickedGame()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_GAME))
		MessageBox(L"少玩游戏！");
}


void CPInfoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sName, sAge, sEdu;
	wchar_t buf[20];
	GetDlgItemText(IDC_NAME, sName);
	GetDlgItemText(IDC_AGE, sAge); // 可以用下面的两个语句代替
								   /*int iAge = GetDlgItemInt(IDC_AGE);
								   _itow_s(iAge, sAge.GetBuffer(4), 4, 10);*/
	CListBox* pLB = (CListBox*)GetDlgItem(IDC_EDU);
	pLB->GetText(pLB->GetCurSel(), sEdu);
	/*CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_MAJOR);
	pCB->GetLBText(pCB->GetCurSel(), buf);*/
	GetDlgItemText(IDC_MAJOR, buf, 20);
	CString str = sName + (IsDlgButtonChecked(IDC_MALE) ? L" 男 " : L" 女 ")
		+ sAge + L"岁\n" + buf + L"专业 " + sEdu + L"毕业"
		+ L"\n爱好：" + (IsDlgButtonChecked(IDC_GAME) ? L" 网游" : L"")
		+ (IsDlgButtonChecked(IDC_ART) ? L" 艺术" : L"")
		+ (IsDlgButtonChecked(IDC_SPORT) ? L" 运动" : L"");
	MessageBox(str, L"结果");
}


void CPInfoDlg::OnBnClickedPlayIt()
{
	// TODO: 在此添加控件通知处理程序代码
	pch->SetPos(50);
	SetTimer(1, 500, NULL);
}


void CPInfoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pch->StepIt();
	if (pch->GetPos() >= 100)
		KillTimer(1);
	CDialog::OnTimer(nIDEvent);
}
