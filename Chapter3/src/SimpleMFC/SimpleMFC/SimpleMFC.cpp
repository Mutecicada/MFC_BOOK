#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "SimpleMFC.h"
#include "MainFrm.h"
/*
*	필요한 헤더 파일들을 포함한다.
*	미리 컴파일된 헤더 파일을 지원하기 위해 stdafx.h를 첫 줄에 포함한다.(순서를 바꾸면 컴파일 실패)
*	CMainFrame 클래스를 사용하므로 MainFrm.h를 포함한다.
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimpleMFCApp

BEGIN_MESSAGE_MAP(CSimpleMFCApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CSimpleMFCApp::OnAppAbout)
END_MESSAGE_MAP()
// 윈도우 메시지와 메시지 핸들러를 연결한다.

// CSimpleMFCApp 생성

CSimpleMFCApp::CSimpleMFCApp() noexcept
{
	SetAppID(_T("SimpleMFC.AppID.NoVersion"));
	// 윈7 작업 표시줄과 관련된 기능이다.

}

// 유일한 CSimpleMFCApp 개체입니다.

CSimpleMFCApp theApp;
/*
*	전역 응용 프로그램 객체를 선언한다.
*	유일한 전역 객체이다.
*/

// CSimpleMFCApp 초기화


// 각종 초기화 코드를 넣는다.
BOOL CSimpleMFCApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);			// 윈7 작업표시줄과 관련된 기능

	// RichEdit 컨트롤을 사용하려면 AfxInitRichEdit2()가 있어야 합니다.
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));


	// 주 창을 만들기 위해 이 코드에서는 새 프레임 창 개체를
	// 만든 다음 이를 응용 프로그램의 주 창 개체로 설정합니다.
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 프레임을 만들어 리소스와 함께 로드합니다.
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
		nullptr);

	/*
	*	프레임 윈도우 객체를 동적으로 생성한 후 객체의 주소값을 CWinThread::m_pMainWnd 멤버 변수에 저장한다.
	*	CWinThread는 CWinApp의 베이스 클래스므로 CWinThread의 멤버 변수에 접근할 수 있다.
	*	프레임 윈도우 객체는 만들어졌지만 운영체제 수준의 실제 프레임 윈도우는 아니다.
	*	순수한 C++의 객체
	*	CFrame::LoadFrame() 실제 프레임 윈도우를 생성, 앞의 객체와 연결한다.
	*	
	*/



	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	pFrame->ShowWindow(SW_SHOW);		// 생성된 프레임윈도우를 화면에 표시
	pFrame->UpdateWindow();				// 프레임 윈도우가 WM_PAINT 메시지를 지금 즉시 처리하게 한다.
	return TRUE;						// False 리턴시 프로그램이 시작되자마자 종료
}

//	각종 청소 코드 작성
int CSimpleMFCApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	return CWinApp::ExitInstance();
}

// CSimpleMFCApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CSimpleMFCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSimpleMFCApp 메시지 처리기



