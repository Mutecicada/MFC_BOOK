
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "ChangeCursor.h"
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
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (!click)
	{
		dc.SelectStockObject(LTGRAY_BRUSH);
		dc.Ellipse(coord.x - 20, coord.y - 20, coord.x + 20, coord.y + 20);
	}

	//dc.SelectStockObject(LTGRAY_BRUSH);
	//dc.Ellipse(10, 10, 600, 200);
}



BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (nHitTest == HTCLIENT)
	{
		CPoint point;
		::GetCursorPos(&point); //커서 위치(스크린 좌표)를 얻는다
		ScreenToClient(&point); //스크린 좌표를 클라이언트 좌표로 변환
		CRgn rgn;
		rgn.CreateEllipticRgn(coord.x - 20, coord.y - 20, coord.x + 20, coord.y + 20); //타원형 리전 생성
		if (rgn.PtInRegion(point)) //커서가 리전 안쪽에 있는지 확인
			::SetCursor(AfxGetApp()->LoadCursorW(IDC_ARROW));
		else
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		return TRUE;
	}


	
	if (nHitTest == HTCLIENT)
	{
		CPoint point;
		::GetCursorPos(&point);
		ScreenToClient(&point);
		CRect rect;
		GetClientRect(&rect);

		CRgn rgn;
		rgn.CreateRectRgn(0, 0, rect.Width(), rect.Height());

		if (rgn.PtInRegion(point)) //커서가 리전 안쪽에 있는지 확인
		{
			onClient = TRUE;
			coord.x = point.x;
			coord.y = point.y;
		}
		else
			onClient = FALSE;
		/*
		rgn.CreateEllipticRgn(10, 10, 600, 200);

		if (rgn.PtInRegion(point))
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		else
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		*/
		return TRUE;
	}
	
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (click)
	{
		CClientDC dc(this);
		dc.SetROP2(R2_NOT);
		dc.Ellipse(point.x - 20, point.y - 20, point.x + 20, point.y + 20);
		Sleep(50);
		dc.SetROP2(R2_NOT);
		dc.Ellipse(point.x - 20, point.y - 20, point.x + 20, point.y + 20);

	}
	
	/*		연습문제 5 - 5		
	if (onClient == TRUE)
	{
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOT);
		dc.Ellipse(coord.x - 50, coord.y - 20, coord.x + 50, coord.y + 20);
		Sleep(50); 
		dc.SetROP2(R2_NOT);
		dc.Ellipse(coord.x - 50, coord.y - 20, coord.x + 50, coord.y + 20);
	}
	*/
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	click = TRUE;
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	coord.x = point.x;
	coord.y = point.y;
	click = FALSE;
	Invalidate();

	CWnd::OnLButtonUp(nFlags, point);
}
