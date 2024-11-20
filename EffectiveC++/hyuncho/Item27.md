# Item27. 캐스팅은 절약, 또 절약! 잊지 말자
"어떤 일이 있어도 타입 에러가 생기지 않도록 보장한다."

C++의 동작 규칙은 바로 이 철학을 바탕으로 설계되어 있다.

이 말은 C++프로그램은 일단 컴파일만 깔끔하게 끝나면 그 이후엔 어떤 객체에 대해서도 불안전한 연산이나 말도 안 되는 연산을 수행하려 들지 않는다는 것이다.

C++에서 캐스팅은 정말 조심해서 써야 하는 기능이다. 
```cpp
//표현식 부분을 T 타입으로 캐스팅.(구형 스타일의 캐스트)
(T) 표현식
T(표현식)

//C++스타일 캐스트
const_cast<T>(표현식)   //객체의 상수성을 없애는 용도
dynamic_cast<T>(표현식)  //안전한 다운캐스팅을 할 때 사용. 즉, 주어진 객체가 어떤 클래스 상속 계통에 속한 특정 타입인지 아닌지를 결정하는 작업에 사용
reinterpret_cast<T>(표현식)  //포인터를 int로 바꾸는 등의 하부 수준 캐스팅을 위해 만들어진 연산자로, 이것의 적용 결과는 구현환경에 의존적임
static_cast<T>(표현식)  //암시적 변환을 강제로 진행할 때 사용한다. 흔히들 이루어지는 타입 변환을 거꾸로 수행하는 용도로도 쓰인다.
```
구형 스타일의 캐스트보다 C++ 스타일 캐스트를 쓰는 것이 바람직한 이유는 코드를 읽을 때 알아보기 쉽기 때문이고 캐스트를 사용한 목적을 좁혀서 지정하기 때문에 컴파일러 쪽에서 사용 에러를 진단할 수 있다.

구형 스타일의 캐스트를 쓰는 경우가 한 가지 있다. 객체를 인자로 받는 함수에 객체를 넘기기 위해 명시호출 생성자를 호출하고 싶을 경우이다.
```cpp
class Widget {
public:
	explicit Widget(int size);
	...
};

void doSomeWork(const Widget& w);

doSomeWork(Widget(15));   //함수 방식 캐스트 문법

doSomeWork(static_cast<Widget>(15));   //C++방식 캐스트
```
캐스팅이 그냥 어떤 타입을 다른 타입으로 처리하라고 컴파일러에게 알려 주는 용도 말고 더 있느냐라고 생각하는 프로그래머가 많다. 하지만 타입변환이 있으면 런타임에 실행되는 코드가 만들어지는 경우가 적지 않다.
```cpp
int x, y;
...
double d = static_cast<double>(x) / y;
```
위의 경우는 int 타입의 x를 double 타입으로 캐스팅한 부분에서 코드가 만들어진다.
```cpp
class Base {...};

class Derived: public Base {...};

Derived d;

Base *pb = &d;   //Derived* => Base*의 암시적 변환이 이루어진다.
```
위의 경우 파생클래스 객체에 대한 기본 클래스 포인터를 만드는 코드이다. 그런데 두 포인터 값이 같지 않은 경우도 있다. 이런 경우가 되면, 포인터의 변위를 Derived* 포인터에 적용하여 실제 Base* 포인터 값을 구하는 동작이 바로 런타임에 이루어진다.

이는 객체 하나가 가질 수 있는 주소가 오직 한 개가 아니라 그 이상이 될 수 있음을 보여준다.

포인터 변위를 써야하는 때는 가끔이어야 한다. 이유는 객체의 메모리 배치구조를 결정하는 방법과 객체의 주소를 계산하는 방법은 컴파일러마다 천차만별이다. 어떤 플랫폼에서는 캐스팅했을 때 문제가 없을지 몰라도 다른 플랫폼에서는 문제가 발생할 수 있다는 말이다.

캐스팅이 들어가면, 보기엔 맞는 것 같지만 실제로는 틀린 코드를 쓰고도 모르는 경우가 많아진다. 
만약 가상클래스를 파생클래스에서 재정의해서 구현할 때 기본 클래스의 버전을 호출하는 문장을 가장 먼저 넣어달라는 요구사항을 보았다고 하자.
```cpp
class Window {
public:
	virtual void onResize() { ... }
	...
};

class SpecialWindow: public Window {
public:
	virtual void onResize() {
		static_cast<Window>(*this).onResize();
	}
};
```
위의 코드는 맞는 것 같지만 틀렸다. 이유는 캐스팅 하는 와중에 \*this를 복사한 임시객체가 생성되고 임시객체의 onResize()가 호출되기 때문에 예상한대로 동작하지 않게 된다.
```cpp
class SpecialWindow: public Window {
public:
	virtual void onResize() {
		Window::onResize();   //*this에서 Window::onResize를 호출한다.
	}
}
```
위와 같은 방법으로 해결이 가능하다. 굳이 캐스팅을 하지 않아도 된다.

dynamic_cast를 쓰는 것은 아주 주의를 요한다. 파생 클래스 객체임이 분명한 녀석이 있어서 이에 대해 파생 클래스의 함수를 호출하고 싶은데, 그 객체를 조작할 수 있는 수단으로 기본 클래스의 포인터밖에 없을 경우는 적지 않게 생긴다. 

이런 문제를 피하기 위한 방법으로 두가지가 있다.

첫번째 방법은 파생 클래스 객체에 대한 포인터를 컨테이너에 담아둠으로써 각 객체를 기본 클래스 인터페이스를 통해 조작할 필요를 아예 없애 버리는 것이다.

아래는 잘못된 방법의 코드
```cpp
class Window { ... };

class SpecialWindow: public Window {
public:
	void blink();
	...
};

typedef std::vector<std::tr1::shared_ptr<Window>> VPW;
VPW winPtrs;
...
for (VPW::iterator iter = winPtrs.begin(); iter != windPtrs.end(); ++iter){
	if (SpecialWindow *psw = dynamic_cast<SpecialWindow*>(iter->get()))
		psw->blink();
}
```

아래는 개선된 방법의 코드(dynamic_cast를 사용하지 않음)
```cpp
typedef std::vector<std::tr1::shared_ptr<SpecialWindow>> VPSW;
VPSW winPtrs;
...
for ( VPSW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter )
	(*iter)->blink();
```
다만, 위 방법으로는 Window에서 파생될 수 있는 모든 녀석들에 대한 포인터를 똑같은 컨테이너에 담을 수 없다. 

아래 코드는 아무것도 안하는 기본 blink를 구현해서 가상함수로 제공해 Window에서 뻗어나온 자손들을 전부 기본 클래스 인터페이스를 통해 조작할 수 있는 방법이다.
```cpp
class Window {
public:
	virtual void blink() {}
	...
};

class SpecialWindow: public Window {
public:
	virtual void blink() { ... }
};

typedef std::vector<std::tr1::shared_ptr<Window>> VPW;
VPW winPtrs;

...

for (VPW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
	(*iter)->blink();
```
결국은 dynamic_cast를 쓰는 방법 대신의 두가지 예제를 배웠다.


+ 다른 방법이 가능하다면 캐스팅은 피하라. 특히 수행 성능에 민감한 코드에서 dynamic_cast는 몇 번이고 다시 생각해라. 설계 중에 캐스팅이 필요해졌다면, 캐스팅을 쓰지 않는 다른 방법을 시도해라.
+ 캐스팅이 어쩔 수 없이 필요하다면, 함수 안에 숨길 수 있도록 해봐라. 이렇게 하면 최소한 사용자는 자신의 코드에 캐스팅을 넣지 않고 이 함수를 호출할 수 있게 된다.
+ 구형 스타일의 캐스트를 쓰려거든 C++ 스타일의 캐스트를 선호하라. 발견하기도 쉽고, 설계자가 어떤 역할을 의도했는지가 더 자세하게 드러난다.