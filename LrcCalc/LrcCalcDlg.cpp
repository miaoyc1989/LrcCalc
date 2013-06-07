// LrcCalcDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLrcCalcDlg �Ի���



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


// CLrcCalcDlg ��Ϣ�������

BOOL CLrcCalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLrcCalcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CLrcCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//************************************
// Method	 : LRC
// Returns	 	 : unsigned char
// Parameter : unsigned char * auchMsg	Ҫ����LRCУ�����Ϣ
// Parameter : unsigned short usDataLen  ��Ϣ���ֽ���
// ����˵��	 :  ����LRCУ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CLrcCalcDlg::CreateMessage()
{
	int nSlaveNum = int(m_nSlaveNum.GetValue());
	int nFunCode = int(m_nFunCode.GetValue());
	int nStartAddr = int(m_nStartAddr.GetValue());
	int nDataSize = int(m_nDataSize.GetValue());


	BYTE buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	buffer[0] = BYTE(nSlaveNum);			// ���豸��ַ
	buffer[1] = BYTE(nFunCode);				// ������
	buffer[2] = HIBYTE(WORD(nStartAddr));	// ��ʼ��ַ��λ
	buffer[3] = LOBYTE(WORD(nStartAddr));	// ��ʼ��ַ��λ
	buffer[4] = HIBYTE(WORD(nDataSize));					// �Ĵ���������λ
	buffer[5] = LOBYTE(WORD(nDataSize));					// �Ĵ���������λ

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
