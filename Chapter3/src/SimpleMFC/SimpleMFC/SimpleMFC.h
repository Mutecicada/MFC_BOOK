
// SimpleMFC.h: SimpleMFC 응용 프로그램의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.
// 리소스 ID가 #define으로 정의 되어있다.


// CSimpleMFCApp:
// 이 클래스의 구현에 대해서는 SimpleMFC.cpp을(를) 참조하세요.
//


// CWinApp 클래스를 상속받는다.
class CSimpleMFCApp : public CWinApp
{
public:
	CSimpleMFCApp() noexcept;


// 재정의입니다.
public:
	// CWinApp에서 상속받은 가상함수를 재정의한다.
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.

public:
	afx_msg void OnAppAbout();		// 도움말 - SimpleMFC 정보 메뉴를 선택할시 자동으로 호췰되는 메시지 핸들러이다.
	DECLARE_MESSAGE_MAP()			// 어떤 클래스에 메시지 핸들러가 한 개 이상 존재한다면 DECLARE_MESSAGE_MAP() 매크로가 클래스 선언부에 있어야한다.
	// 관례상 클래스 선언부의 가장 아래에 위치한다.
};

extern CSimpleMFCApp theApp;
