
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창
// 베이스 클래스인 CWnd는 일반적인 윈도우의 기능을 정의하는 클래스다.
// 도큐먼트/뷰 구조를 선택하지 않아서 선택하면 CView나 CView의 파생클래스가 베이스 클래스가된다.
class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

