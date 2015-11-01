
// PInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PInfo.h"
#include "PInfoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CPInfoDlg �Ի���



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


// CPInfoDlg ��Ϣ�������

BOOL CPInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetDlgItemText(IDC_NAME, L"����");
	CheckRadioButton(IDC_MALE, IDC_FEMALE, IDC_MALE);
	SetDlgItemInt(IDC_AGE, 22);

	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_AGE);
	pSpin->SetRange(0, 150);

	CListBox* pLB = (CListBox*)GetDlgItem(IDC_EDU);
	pLB->AddString(L"��ר");
	pLB->AddString(L"����");
	pLB->AddString(L"˶ʿ");
	pLB->AddString(L"��ʿ");
	pLB->SetCurSel(1);

	CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_MAJOR);
	pCB->AddString(L"���ʾ�����ó��");
	pCB->AddString(L"��ѧ");
	pCB->AddString(L"�������ѧ�뼼��");
	pCB->AddString(L"���繤��");
	pCB->AddString(L"��Ϣ��ȫ");
	pCB->SetCurSel(2);	//����Ĭ�ϳ�ʼѡ�е���
	CheckDlgButton(IDC_ART, 1);
	CheckDlgButton(IDC_SPORT, 1);


	//���ý�����
	pch = (CProgressCtrl *)GetDlgItem(IDC_PCH);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPInfoDlg::OnBnClickedGame()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (IsDlgButtonChecked(IDC_GAME))
		MessageBox(L"������Ϸ��");
}


void CPInfoDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sName, sAge, sEdu;
	wchar_t buf[20];
	GetDlgItemText(IDC_NAME, sName);
	GetDlgItemText(IDC_AGE, sAge); // ���������������������
								   /*int iAge = GetDlgItemInt(IDC_AGE);
								   _itow_s(iAge, sAge.GetBuffer(4), 4, 10);*/
	CListBox* pLB = (CListBox*)GetDlgItem(IDC_EDU);
	pLB->GetText(pLB->GetCurSel(), sEdu);
	/*CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_MAJOR);
	pCB->GetLBText(pCB->GetCurSel(), buf);*/
	GetDlgItemText(IDC_MAJOR, buf, 20);
	CString str = sName + (IsDlgButtonChecked(IDC_MALE) ? L" �� " : L" Ů ")
		+ sAge + L"��\n" + buf + L"רҵ " + sEdu + L"��ҵ"
		+ L"\n���ã�" + (IsDlgButtonChecked(IDC_GAME) ? L" ����" : L"")
		+ (IsDlgButtonChecked(IDC_ART) ? L" ����" : L"")
		+ (IsDlgButtonChecked(IDC_SPORT) ? L" �˶�" : L"");
	MessageBox(str, L"���");
}


void CPInfoDlg::OnBnClickedPlayIt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pch->SetPos(50);
	SetTimer(1, 500, NULL);
}


void CPInfoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	pch->StepIt();
	if (pch->GetPos() >= 100)
		KillTimer(1);
	CDialog::OnTimer(nIDEvent);
}
