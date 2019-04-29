
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "SimpleMFC.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()				// OnCreate() 함수와 WM_CREATE 메시지 연결
	ON_WM_SETFOCUS()
	/*
	*	WM_SETFOCUS 메시지와 OnSetFocus() 함수를 연결해 준다.
	*	WM_SETFOCUS 메시지는 윈도우가 키보드 포커스를 가질 때 발생한다.
	*	키보드는 시스템에 한 개만 존재하는 자원이므로 반드시 한 개의 윈도우만 입력 받을 수 있다.
	*	이 사실을 알려주는 메시지가 WM_SETFOCUS이다.
	*/
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}
// LoadFrame() 함수로 프레임 윈도우가 생성되고 WM_CREATE 메시지가 발생하면서 자동으로 호출된다.
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
	if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("뷰 창을 만들지 못했습니다.\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

/*
*	MFC는 윈도우를 생성하기 전에 가상함수인 PreCreateWindow()를 호출한다.
*	순서를 따지면 OnCreate()보다 PreCreateWindow()가 먼저이다.
*	생성할 윈도우의 특성을 바꾸고 싶다면 CREATESTRUCT 구조체를 조작하면 된다.
*/
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 진단

// 타당성 점검 기능과 디버깅을 위한 객체 상태 출력기능 제공
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	// 베이스 클래스인 CFrameWnd가 제공하는 함수 그대로 호출
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기
/*
*	프레임 윈도우가 키보드 포커스를 갖게 되면 WM_SETFOCUS 메시지가 발생하고, 메시지 맵 매크로를 통해 OnSetFocus() 호출
*	여기서는 view 객체의 SetFocus()가 호출되서 포커스를 갖는다.
*	사용자가 키보드 입력하는 코드를 입력하려면 뷰 클래스에 추가한다.
*/
void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.
	m_wndView.SetFocus();
}
/*
*	MFC가 지원하는 독특한 개념의 명령 라우터
*/
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

