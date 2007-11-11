// loveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "love.h"
#include "loveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CloveDlg dialog




CloveDlg::CloveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CloveDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CloveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CloveDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CloveDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CloveDlg message handlers

BOOL CloveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// so ugly... 
	CEdit *Display;

	Display = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT1));
	Display->SetWindowText(_T("roses are #ff0000\r\nviolets are #0000ff\r\nall my base\r\nare belong to you"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CloveDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CloveDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CloveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CloveDlg::OnBnClickedOk()
{
	
	// this is where everything goes down
	if (MessageBox(_T("Are you sure you want to do this? This may kill this machine!!!"),_T("Are you SURE?!"),MB_YESNO) == IDYES && 
		MessageBox(_T("Really? Are you really really sure? This is dangerous!"),_T("Are you crazy?!"),MB_YESNO) == IDYES){
		
		CEdit* editCtrl = (CEdit*)GetDlgItem(IDC_EDIT1);
		// Extract value as text
		CString text;
		editCtrl->GetWindowText(text);

		// hehe. 
		text.Append(_T("\r\n\r\nMissing operating system"));

		// convert the string to ANSI (http://www.codeguru.com/forum/showthread.php?t=231165)

		TCHAR * unicodestr = text.GetBuffer();
		char *ansistr;
		int lenW = (int)_tcslen(unicodestr);
		int lenA = ::WideCharToMultiByte(CP_ACP, 0, unicodestr, lenW, 0, 0, NULL, NULL);
		if (lenA > 0){
			  ansistr = new char[((lenA+1) / 512)*512 + 512]; // round to multiple of 512
			  ZeroMemory(ansistr,((lenA+1) / 512)*512 + 512);
			::WideCharToMultiByte(CP_ACP, 0, unicodestr, lenW, ansistr, lenA, NULL, NULL);
			  
		}else{
			// handle the error
			MessageBox(_T("Error converting string!"),_T("Error"),MB_OK);
			return;
		}


		write_message(ansistr, (int)strlen(ansistr));

		delete[] ansistr;
		text.ReleaseBuffer();
	}

}
