
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "InputCharacter.h"
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
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
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

	CFont font;
	font.CreatePointFont(150, _T("궁서"));
	dc.SelectObject(&font);

	CRect rect;
	GetClientRect(&rect);
	dc.DrawText(m_str.GetData(), m_str.GetSize(), &rect, DT_LEFT);
}



void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CPoint coord = GetCaretPos();


	if (nChar == _T('\b'))
	{
		if (m_str.GetSize() > 0)
			m_str.RemoveAt(m_str.GetSize() - 1);
		CPoint temp{ coord.x - 14, coord.y };
		SetCaretPos(temp);
	}
	else
	{
		m_str.Add(nChar);
		if (nChar == 13)
		{
			CPoint temp{ 0, coord.y + 25 };
			SetCaretPos(temp);
		}
		else
		{
			CPoint temp(coord.x + 14, coord.y);
			SetCaretPos(temp);
		}
	}


	Invalidate();
}


void CChildView::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	CreateSolidCaret(1, 25);
	ShowCaret();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
