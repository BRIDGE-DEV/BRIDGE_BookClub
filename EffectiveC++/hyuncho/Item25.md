# Item25. 예외를 던지지 않는 swap에 대한 지원도 생각해 보자
```cpp
namespace std {
	template<typename T>
	void swap(T& a, T& b)
	{
		T temp(a);
		a = b;
		b = temp;
	}
}
```
위 코드는 표준에서 기본적으로 제공하는 swap의 구현코드로 복사만 제대로 지원하는 타입이기만 하면 어떤 타입의 객체이든 맞바꾸기 동작을 수행해준다.
한 번 호출에 복사가 세 번 일어난다. 

pimpl 관용구(pointer to implementation)를 사용한 설계
```cpp
class WidgetImpl {
public:
	...

private:
	int a, b, c;
	std::vector<double> v;
};

class Widget {
public:
	Widget(const Widget& rhs);

	Widget& operator=(const Widget& rhs)
	{
		*pImpl = *(rhs.pImpl);
	}
private:
	WidgetImpl *pImpl;   //Widget의 실제 데이터를 가진 객체에 대한 포인터
};
```
이렇게 만들어진 객체를 직접 맞바꾼다면, pImpl 포인터만 살짝 바꾸는 것 말고는 실제로 할 일이 없다. 하지만 이런 사정을 표준 swap 알고리즘이 알고 있을 리가 없다.

그래서 std::swap을 좀 손봐서 일반적인 맞바꿈이 아닌 내부의 pImpl 포인터만 맞바꾸도록 한다.

아래 코드처럼 Widget에 대해 std::swap을 특수화하는 것이다.
```cpp
namespace std {
	template<>
	void swap<Widget>(Widget& a, Widget& b)  //T가 Widget인 경우에 대해 std::swap을 특수화한 것.
	{
		swap(a.pImpl, b.pImpl);   //pImpl만 바꿔준다.
	}
}
```
'template<>' 의 의미는 이 함수가 std::swap의 **완전 템플릿 특수화 함수**라는 것을 컴파일러에게 알려주는 것이다.

그런데 위의 함수는 컴파일 되지 않는다. 이유는 pImpl 가 private 멤버이기 때문이다.

해결방법으로 아래 코드처럼 public swap 멤버 함수를 Widget에 추가하는 방법으로 해결한다.
```cpp
class Widget {
public:
	void swap(Widget& other)
	{
		using std::swap;

		swap(pImpl, other.pImpl);
	}
};

namespace std {
	template<>
	void swap<Widget>(Widget& a, Widget& b)
	{
		a.swap(b);
	}
}

```

아래 코드는 함수 템플릿을 부분적으로 특수화해 달라고 컴파일러에게 요청한 것인데, C++는 클래스 템플릿에 대해서는 부분 특수화를 허용하지만 함수 템플릿에 대해서는 허용하지 않도록 정해져 있다. 그래서 컴파일이 되지 않는다.
```cpp
template<typename T>
class Widget {...};

namespace std {
	template<typename T>
	void swap<Widget<T>> (Widget<T>& a, Widget<T>& b)
	{ 
		a.swap(b);
	}
}
```
그래서 함수 템플릿을 '부분적으로 특수화'하고 싶을 때는 오버로드 버전을 하나 추가하면 된다.
```cpp
namespace std {
	template<typename T>
	void swap(Widget<T>& a, Widget<T>& b)
	{
		a.swap(b);
	}
}
```
std 내의 템플릿에 대한 완전 특수화는 가능하지만, std에 새로운 템플릿을 추가하는 것은 안된다.
std에 절대 아무것도 추가하지 말아라.

위를 해결하기 위한 방법은 멤버 swap을 호출하는 비멤버 swap을 선언해 놓되, 이 비멤버 함수를 std::swap의 특수화 버전이나 오버로딩 버전으로 선언하지만 않으면 된다.
```cpp
namespace WidgetStuff {
	template<typename T>
	class Widget { ... };
	...
	template<typename T>   //비멤버 swap 함수
	void swap(Widget<T>& a, Widget<T>& b)
	{
		a.swap(b);
	}
}
```
위와 같은 코드를 통해 어떤 코드가 두 Widget 객체에 대해 swap을 호출하더라도 컴파일러는 C++의 이름 탐색 규칙(인자 기반 탐색 혹은 쾨니그 탐색)에 의해 WidgetStuff 네임스페이스 안에서 Widget 특수화 버전을 찾아낸다.

사용자 입장에서 swap을 호출할 때, swap을 호출하는 함수가 std::swap을 볼 수 있도록 using 선언을 반드시 포함시킨다. 그 다음에 swap을 호출 하되, 네임스페이스 한정자를 붙이지 않도록 하자.
```cpp
template<typename T>
void doSomething(T& obj1, T& obj2)
{
	using std::swap;   //std::swap을 이 함수 안으로 끌어 올 수 있도록 만든 문장

	swap(obj1, obj2);  // T 타입 전용의 swap을 호출
}
```

멤버 버전의 swap은 절대로 예외를 던지지 않도록 만들어야 한다. 이유는 swap을 진짜 쓸모 있게 응용하는 방법들 중에 클래스가 강력한 예외 안정성 보장을 제공하도록 도움을 주는 방법이 있기 때문이다.


+ std::swap 이 여러분의 타입에 대해 느리게 동작할 여지가 있다면 swap 멤버 함수를 제공하자. 이 멤버 swap은 예외를 던지지 않도록 만들자.
+ 멤버 swap을 제공했으면, 이 멤버를 호출하는 비멤버 swap도 제공한다. 클래스(템플릿이 아닌)에 대해서는 std::swap도 특수화 해두자.
+ 사용자 입장에서 swap을 호출할 때는, std::swap에 대한 using 선언을 넣어 준 후에 네임스페이스 한정 없이 swap을 호출하자.
+ 사용자 정의 타입에 대한 std 템플릿을 완전 특수화하는 것은 가능하다. 그러나 std에 어떤 것이라도 새로 '추가'하려고 들지는 말자.