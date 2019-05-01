# WM_COMMAND 메시지와 사용자 메시지
- 윈도우에서는 상황에 따라 사용하는 메시지 형태가 다르다.

- 메시지를 `직접 생성하여` 보낼 때는 `SendMessage()`나 `PostMessage()`함수를 사용한다.

- SendMessage() 함수는 메시지를 `바로 처리`하는 반면, PostMessage() 함수는 메시지를 `메시지 큐에 넣기`만 한다.
```C++
SendMessage(WM_COMMAND, MAKEWPARAM(ID_FILE_OPEN, 0), NULL);
// ID_FILE_OPEN 메뉴의 명령을 메시지로 생성
```

- SendMessage(), PostMessage() 함수를 사용하여 사용자가 메시지를 직접 정의할 수도 있다.
```C++
#define WM_TRAY_NOTIFICATION WM_APP+1
SendMessage(WM_TRAY_NOTIFICATION, wParam, lParam);
```

- 정의하는 메시지는 WM_APP부터 시작하여 내부에서 `유일한 메시지 값`이어야 한다.

- wParam, lParam은 자신이 필요한 대로 전송할 수 있지만 크기가 클 경우 포인터로 전송한다.

- 메시지 맵에서 WM_COMMAND는 ON_COMMAND() 매크로를 사용하고, 사용자 메시지는 `ON_MESSAGE()` 매크로를 사용하며, 다음과 같은 형태이여야 한다.

```C++
afx_msg LRESULT OnTrayNotification(WPARAM, LPARAM);
ON_MESSAGE(WM_TRAY_NOTIFICATION, OnTrayNotification)
```

- 맵 방식은 `타입`검사를 하지 않기에 함수가 잘못된 형태로 입력되도 알지 못하고 같은 방식으로 접근하려 한다.

- 내부에서 사용하는 메시지가 아니고 윈도우 전체에서 사용할 메시지는 `::RegisterWindowMessage()`함수와 `ON_REGISTERED_MESSAGE()` 매크로를 사용한다.

