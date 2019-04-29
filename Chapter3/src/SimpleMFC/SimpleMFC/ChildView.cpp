
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "SimpleMFC.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// 베이스 클래스가 제공하는 가상 함수를 먼저 호출한다.
	// CREATESTRUCT 구조체의 일부 멤버를 초기화한다.
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;


	// |= 연산자로 새로운 스타일을 추가, &= 연산자로 특정 스타일을 제거할 수 있다.
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	//	윈도우 클래스 이름을 나타낸다.
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

//	::BeginPaint()와 EndPaint() 함수를 내부적으로 호출한다.
void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}

