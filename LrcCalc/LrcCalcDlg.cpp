// LrcCalcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LrcCalc.h"
#include "LrcCalcDlg.h"
#include ".\lrccalcdlg.h"

#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CLrcCalcDlg 对话框



CLrcCalcDlg::CLrcCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLrcCalcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLrcCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CWNUMEDIT_SLAVE_NUM, m_nSlaveNum);
	DDX_Control(pDX, IDC_CWNUMEDIT_FUNCODE, m_nFunCode);
	DDX_Control(pDX, IDC_CWNUMEDIT_START_ADDR, m_nStartAddr);
	DDX_Control(pDX, IDC_CWNUMEDIT_DATASIZE, m_nDataSize);

}

BEGIN_MESSAGE_MAP(CLrcCalcDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, OnExit)
	ON_BN_CLICKED(IDC_BUTTON1, CreateMessage)
	ON_BN_CLICKED(1009, CreateMessage)
END_MESSAGE_MAP()


// CLrcCalcDlg 消息处理程序

BOOL CLrcCalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CLrcCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLrcCalcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CLrcCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//************************************
// Method	 : LRC
// Returns	 	 : unsigned char
// Parameter : unsigned char * auchMsg	要进行LRC校验的消息
// Parameter : unsigned short usDataLen  消息中字节数
// 功能说明	 :  返回LRC校验值
//************************************
unsigned char LRC(unsigned char *auchMsg, int usDataLen)
{
	unsigned char uchLRC = 0 ;							/* LRC char initialized */
	while (usDataLen--)										/* pass through message buffer */
	{
		uchLRC += *auchMsg++ ;						/* add buffer byte without carry */
	}
	return ((unsigned char)(-((char)uchLRC))) ;		/* return twos complement */
}


void CLrcCalcDlg::OnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CLrcCalcDlg::CreateMessage()
{
	int nSlaveNum = int(m_nSlaveNum.GetValue());
	int nFunCode = int(m_nFunCode.GetValue());
	int nStartAddr = int(m_nStartAddr.GetValue());
	int nDataSize = int(m_nDataSize.GetValue());


	BYTE buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	buffer[0] = BYTE(nSlaveNum);			// 从设备地址
	buffer[1] = BYTE(nFunCode);				// 功能码
	buffer[2] = HIBYTE(WORD(nStartAddr));	// 起始地址高位
	buffer[3] = LOBYTE(WORD(nStartAddr));	// 起始地址低位
	buffer[4] = HIBYTE(WORD(nDataSize));					// 寄存器数量高位
	buffer[5] = LOBYTE(WORD(nDataSize));					// 寄存器数量低位

	int nResult = LRC( buffer, 6 );

	char tmpSlaveNum[255];
	itoa(buffer[0], tmpSlaveNum, 16);
	CString strSlaveNum;
	strSlaveNum.Format("%02s", tmpSlaveNum);

	char tmpFunCode[255];
	itoa(buffer[1], tmpFunCode, 16);
	CString strFunCode;
	strFunCode.Format("%02s", tmpFunCode);

	char tmpHiStartAddr[255];
	itoa(buffer[2], tmpHiStartAddr, 16);
	CString strHiStartAddr;
	strHiStartAddr.Format("%02s", tmpHiStartAddr);

	char tmpLoStartAddr[255];
	itoa(buffer[3], tmpLoStartAddr, 16);
	CString strLoStartAddr;
	strLoStartAddr.Format("%02s", tmpLoStartAddr);

	char tmpHiDataSize[255];
	itoa(buffer[4], tmpHiDataSize, 16);
	CString strHiDataSize;
	strHiDataSize.Format("%02s", tmpHiDataSize);

	char tmpLoDataSize[255];
	itoa(buffer[5], tmpLoDataSize, 16);
	CString strLoDataSize;
	strLoDataSize.Format("%02s", tmpLoDataSize);

	char tmpCheck[255];
	itoa(nResult, tmpCheck, 16);
	CString strCheck;
	strCheck.Format("%02s", tmpCheck);
	GetDlgItem(IDC_LRC_RESULT)->SetWindowText(strCheck);	

	CString strResult;
	strResult = strSlaveNum + strFunCode + strHiStartAddr + strLoStartAddr + strHiDataSize + strLoDataSize +  strCheck;
	GetDlgItem(IDC_RESULT)->SetWindowText(strResult);	
}
