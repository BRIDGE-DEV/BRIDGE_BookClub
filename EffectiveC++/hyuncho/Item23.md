# Item23. 멤버 함수보다는 비멤버 비프렌드 함수와 더 가까워지자
```cpp
class WebBrowser {
public:
	...
	void clearCache();
	void clearHistory();
	void removeCookies();
	...
};
```
사용자 중에는 이 세동작을 한 번에 하고 싶은 분들이 있어 세 함수를 모아서 불러주는 함수도 준비할 수 있을 것이다.
```cpp
class WebBrowser {
public:
	...
	void clearEverything();
}
```
물론 이 기능은 비멤버 함수로 제공해도 된다. 웹브라우저 객체의 멤버 함수를 순서대로 불러주기만 하면 된다.
```cpp
void clearBrowser(WebBrowser& wb)
{
	wb.clearCache();
	wb.clearHistory();
	wb.removeCookies();
}
```
어느 쪽이 더 괜찮을까? 멤버 버전인 clearEverything 일까 아니면 비멤버 버전인 clearBrowser 일까?
멤버 버전인 clearEverything이 비멤버 버전인 clearBrowser보다 캡슐화가 형편없다. 

결국 비멤버 버전 함수를 사용하면 패키징 유연성이 높아지고 컴파일 의존도도 낮추고 WebBrowser의 확장성도 높일 수 있다.

캡슐화에 대해서 이야기를 해보면 캡슐화를 하는 것이 늘어나면 그만큼 밖에서 볼 수 있는 것들이 줄어든다. 밖에서 볼 수 있는 것들이 줄어들면, 그것들을 바꿀 때 필요한 유연성이 커진다. 

결국 캡슐화되는 것이 많아지면 그것들을 변경할 수 있는 여유도 많아진다. 위에서 보았듯이 똑같은 기능을 제공하는데 멤버 함수를 쓸 것이냐, 아니면 비멤버 비프렌드 함수를 쓸 것이냐를 이제 다시 생각해보면 캡슐화가 더 높은 쪽을 고른다면 당연히 후자가 된다. 왜냐하면 비멤버 비프렌드 함수는 어떤 클래스의 private 멤버 부분을 접근할 수 있는 함수의 개수를 늘리지 않기 때문이다.

주의해야 할 두 가지
1. 이 이야기는 비멤버 비프렌드 함수에만 적용된다는 것.(프렌드 함수는 private에 대한 접근 권한이 해당 클래스의 멤버 함수가 가진 접근권한과 똑같이 때문에, 캡슐화에 대한 영향 역시 같다.)
2. 캡슐화에 대한 이런저런 이야기 때문에 "함수는 어떤 클래스의 비멤버가 되어야 한다."라는 주장이 "그 함수는 다른 클래스의 멤버가 될 수 없다." 라는 의미는 아니다.

네임스페이스를 사용하면 좀 더 자연스럽게 사용이 가능하다.
```cpp
namespace WebBrowserStuff {
	class WebBrowser { ... };
	void clearBrowser(WebBrowser& wb);
	...
}
```
C++ 라이브러리를 보면 std 네임스페이스에 속한 모든 것들이 <C++StandardLibrary> 헤더 같은 것에 모조리 들어가 한 통으로 섞여 있지 않고, 몇 개의 기능과 관련된 함수들이 수십 개의 헤더(\<vector>, \<algorithm>, \<meomory> 등)에 흩어져 있다. 이렇게 하면 vector 기능만 사용하길 원한다면 \<algorithm>을 \#include하지 않아도 괜찮다. 이렇게 하면 사용자가 실제로 사용하는 구성요소에 대해서 컴파일 의존성을 고려할 수 있게 된다.(컴파일 의존성을 줄이게 됨.)

편의 함수 전체를 여러 개의 헤더 파일에 나누어 놓으면 편의 함수 집합의 확장도 손쉬워진다.


+ 멤버 함수보다는 비멤버 비프렌드 함수를 자주 쓰도록 하자. 캡슐화 정도가 높아지고, 패키징 유연성도 커지며, 기능적인 확장성도 늘어난다.