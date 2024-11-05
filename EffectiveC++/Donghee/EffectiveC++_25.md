# 챕터4: 설계 및 선언

## 항목 25: 예외를 던지지 않는 swap에 대한 지원도 생각해 보자

두 객체의 값을 맞바꾸기(swap)한다는 것은 각자의 값을 상대방에게 주는 동작이다. 표준 라이브러리에서 제공하는 swap 알고리즘을 쓰는 경우가 많은데, 이것은 우리가 알고 있는 ‘swap’ 동작과 다른 바가 없다.

```cpp
namespace std{
	template<typename T>
	void swap(T& a, T& b)
	{
		T temp(a);
		a = b;
		b = temp;
	}
}
```

복사 생성자와 복사 대입 연산자를 통해 복사만 제대로 지원하는 타입이기만 하면 어떤 타입의 객체이든 맞바꾸기 동작을 수행한다. 하지만 여기서는 복사가 세 번이나 일어난다. a에서 temp로, b에서 a로, temp에서 b로.

복사를 하면 손해를 보는 타입들 중 최고는 포인터가 주성분인 타입일 것이다. 많이들 쓰는 pimpl(pointer to implementation) 관용구이다. 이를 이용한 Widget 클래스 예제를 먼저 보자.

```cpp
class WidgetImpl{
public:
	...
private:
	int a, b, c;
	std::vector<double> v;
	... // 기타 복사 비용이 높음
};
class Widget{
public:
	Widget(const Widget& rhs);
	Widget& operator=(const Widget& rhs) // WidgetImpl 객체만 복사하는 것이 복사 과정
	{
		...
		*pImpl = *(rhs.pImpl);
		...
	}
	...
private:
	WidgetImpl *pImpl; // 실제 데이터를 가진 객체에 대한 포인터
};
```

지금 Widget 객체를 우리가 바꾼다면, pImpl 포인터만 살짝 바꾸는 것 말고는 할 일이 없다. 하지만 이런 점을 표준 swap 알고리즘이 알 리가 없다. Widget 객체를 세 개 복사하고, WidgetImpl 객체 세 개도 복사할 것이다.

그래서 우리는 std::swap에 Widget 객체를 맞바꿀 때는 pImpl 포인터만 맞바꾸라고 알려준다. std::swap을 Widget에 대해 특수화하는 것이다.

```cpp
namespace std{
	template<>
	void swap<Widget>(Widget& a, Widget& b)
	{
		swap(a.pImpl, b.pImpl);
	}
}
```

`template<>` 부분이 이 함수가 std::swap의 **완전 템플릿 특수화** 함수라는 것을 알려주는 부분이다. 함수 뒤의 `<Widget>` 부분은 T가 Widget일 경우의 특수화라는 것을 알려주는 부분이다.

하지만 이 함수는 컴파일되지 않는다. pImpl 포인터는 private 멤버기 때문이다. 그래서 Widget 안에 swap이라는 public 멤버 함수를 선언하고, 그것을 std::swap의 특수화함수에게 다시 호출하도록 한다.

```cpp
class Widget{
public:
	void swap(Widget& other)
	{
		using std::swap;
		swap(pImpl, other.pImpl);
	}
};
namespace std{
	template<>
	void swap<Widget>(Widget& a, Widget& b)
	{
		a.swap(b);
	}
}
```

이제 컴파일이 정상적으로 된다.

여기서 한발 더 나아가서, Widget과 WidgetImpl이 클래스 템플릿이라면 어떻게 될까? std::swap을 다음과 같이 변경해보자.

```cpp
namespace std{
	template<typename T>
	void swap<Widget<T>>(Widget<T>& a, Widget<T>& b)
	{
		a.swap(b);
	}
}
```

하지만 C++는 클래스 템플릿에 대해서는 부분 특수화를 허용하지만, 함수 템플릿에 대해서는 허용하지 않는다. 함수 템플릿을 부분적으로 특수화하고 싶다면, 그냥 오버로드 버전을 하나 추가하는 것이 편하다.

```cpp
namespace std{
	template<typename T>
	void swap(Widget<T>& a, Widget<T>& b)
	{
		a.swap(b);
	}
}
```

일반적인 경우라면 되었겠지만, std는 특별한 네임스페이스이기 때문에 문제가 생긴다. std 내의 템플릿에 대한 완전 특수화는 괜찮지만, std에 새로운 템플릿을 추가하는 것은 괜찮지 못하다. std에 들어가는 구성요소는 C++ 표준화 위원회가 담당하기 때문에, 영역을 건드릴 수 없기 때문이다.

우선 std의 영역을 침범해도 컴파일은 거의 되고 실행도 된다. 하지만 결과가 미정의 사항이 나오게 된다. 따라서 std에는 아무것도 추가하지 말자.

그렇다면 그냥 멤버 swap을 호출하는 비멤버 swap만 선언하고, 이를 std::swap의 오버로딩이나 특수화 버전으로 선언하지 말자.

```cpp
namespace WidgetStuff{
	...
	template<typename T>
	class Widget{...};
	...
	template<typename T> // 이 swap은 std 네임스페이스의 일부가 아니다.
	void swap(Widget<T>& a, Widget<T>& b)
	{
		a.swap(b);
	}
}
```

이제 컴파일러는 C++의 이름 탐색 규칙에 의해 WidgetStuff 네임스페이스 안에서 Widget 특수화 버전을 찾아낸다. 이름 탐색 규칙은 ADL (Argument-Dependent Lookup)라고도 한다.

https://en.cppreference.com/w/cpp/language/adl

만약 우리가 타입 T 전용 버전이 있다면 그것을 호출하고, 아니면 std의 일반형 버전이 호출되게 하고 싶다면 어떻게 할까?

```cpp
template<typename T>
void doSomething(T& obj1, T& obj2)
{
	using std::swap;
	...
	swap(obj1, obj2);
	...
}
```

컴파일러가 위의 swap을 만난다면 현재의 상황에 딱 맞는 swap을 찾게 된다. 먼저 전역 유효범위 혹은 타입 T와 동일한 네임스페이스 안에 T 전용의 swap이 있는지 찾는다. T 전용 swap이 없다면, 컴파일러는 std::swap을 볼 수 있게 해주는 using 선언 덕분에 std::swap을 쓰도록 결정한다. 이 상황에서도 std::swap의 T 전용 버전을 일반형 템플릿보다 더 우선해서 선택한다.

결국 우리가 호출문에 한정자를 먼저 붙이거나 하지 않는 이상(std::swap), 컴파일러는 구속받지 않고 알맞은 swap을 찾게 된다. 이제 정리해보자.

첫째, 표준에서 제공하는 swap이 납득할만한 효율을 보이면 그냥 쓰자.

둘째, swap의 효율이 기대한 만큼 충분하지 않다면, 다음과 같이 하자.

1. 두 객체의 값을 빠르게 바꾸는 함수를 swap으로 만들고, public 멤버 함수로 둔다.
2. 클래스 혹은 템플릿과 같은 네임스페이스에 비멤버 함수 swap을 만들어 넣어 1번에서 만든 멤버 함수를 호출하게 한다.
3. 새로운 클래스를 만들고 있다면, 그 클래스에 대한 std::swap의 특수화 버전을 만들자. 그리고 이 특수화 버전에서도 swap 멤버 함수를 호출하자.
4. 사용자 입장에서 swap을 호출할 때, swap을 호출하는 함수가 std::swap을 볼 수 있도록 using 선언을 반드시 포함시키자. 네임스페이스 한정자는 붙이지 말자.

여기서 멤버 함수 버전의 swap은 절대로 예외를 던져선 안된다. swap을 통해 강력한 예외 안전성 보장을 제공하도록 도움을 주는 기법이 있기 때문이다.

> std::swap이 느리게 동작할 여지가 있다면 swap 멤버 함수를 제공하자. 이 swap은 예외를 던지지 않도록 하자.
멤버 swap을 제공했으면, 이 멤버를 호출하는 비멤버 swap도 제공하자. 클래스에 대해서는 std::swap도 특수화하자.
사용자 입장에서 swap을 호출할 때는, std::swap에 대한 using 선언을 넣어 준 후 네임스페이스 한정 없이 swap을 호출하자.
std 템플릿을 완전 특수화하는 것은 가능하다. 그러나 std에 어떤 것이라도 추가하려고 들지는 말자.