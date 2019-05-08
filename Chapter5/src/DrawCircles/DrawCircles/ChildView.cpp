
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "DrawCircles.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_bDrawMode = FALSE;
	m_bRDrawMode = FALSE;
	color = RGB(0, 0, 0);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
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
	CPaintDC dc(this);

	POSITION pos = list.GetHeadPosition();
	while (pos != NULL)
	{
		CRect rect = list.GetNext(pos);
		dc.SelectStockObject(NULL_BRUSH);
		dc.Ellipse(rect);
	}


	POSITION p_pos = p_list.GetHeadPosition();
	
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_bDrawMode = TRUE;
	m_x1 = m_x2 = point.x;
	m_y1 = m_y2 = point.y;
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDrawMode)
	{
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOT);

		if (GetKeyState(VK_SHIFT)) //shift 누른 상태
		{
			dc.SetROP2(R2_NOT);
			dc.Rectangle(m_x1, m_y1, m_x2, m_y2);
			dc.SetROP2(R2_NOT);
			m_x2 = point.x;
			m_y2 = point.y;
			dc.Rectangle(m_x1, m_y1, m_x2, m_y2);
		}

		else //shift 다시 눌러 풀은 상태
		{
			dc.SetROP2(R2_NOT);
			dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
			dc.SetROP2(R2_NOT);
			m_x2 = point.x;
			m_y2 = point.y;
			dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
		}
	}
	else if (m_bRDrawMode)
	{
		CClientDC dc(this);

		p_list.AddTail(point);
		dc.SetPixelV(point, RGB(0, 0, 0));
	}
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	CPen pen(PS_SOLID, 1, color);
	dc.SelectObject(&pen);
	dc.SetROP2(R2_COPYPEN);
	dc.SelectStockObject(NULL_BRUSH);

	m_x2 = point.x;
	m_y2 = point.y;

	if (::GetKeyState(VK_CONTROL))
	{
		CBrush brush(RGB(255, 0, 0));
		dc.SelectObject(&brush);
		
		if (::GetKeyState(VK_SHIFT))
			dc.Rectangle(m_x1, m_y1, m_x2, m_y2);

		else
			dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
	}
	else
	{
		if (::GetKeyState(VK_SHIFT))
			dc.Rectangle(m_x1, m_y1, m_x2, m_y2);

		else
			dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
	}

	m_bDrawMode = FALSE;
	
	CRect rect(m_x1, m_y1, m_x2, m_y2);
	list.AddTail(rect);

	::ReleaseCapture();
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	switch (nChar)
	{
		// R, r
	case 82:
	case 114:
		color = RGB(255, 0, 0);
		break;

		// G, g
	case 71:
	case 103:
		color = RGB(0, 255, 0);
		break;
		
		// B, b
	case 66:
	case 98:
		color = RGB(0, 0, 255);
		break;
	}

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_DELETE)
		list.RemoveTail();
	Invalidate();
	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	Invalidate();

	m_bRDrawMode = TRUE;
	SetCapture();
	p_list.AddTail(point);
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_bRDrawMode = FALSE;
	::ReleaseCapture();
	CWnd::OnRButtonUp(nFlags, point);
}
