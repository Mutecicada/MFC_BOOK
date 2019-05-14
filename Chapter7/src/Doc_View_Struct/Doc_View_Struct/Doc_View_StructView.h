
// Doc_View_StructView.h: CDocViewStructView 클래스의 인터페이스
//

#pragma once


class CDocViewStructView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDocViewStructView() noexcept;
	DECLARE_DYNCREATE(CDocViewStructView)

// 특성입니다.
public:
	CDocViewStructDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CDocViewStructView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Doc_View_StructView.cpp의 디버그 버전
inline CDocViewStructDoc* CDocViewStructView::GetDocument() const
   { return reinterpret_cast<CDocViewStructDoc*>(m_pDocument); }
#endif

