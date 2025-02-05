# 챕터7: 템플릿과 일반화 프로그래밍

## 항목 42: typename의 두 가지 의미를 제대로 파악하자

두 템플릿 선언문에서 `class`와 `typename`의 차이점은 무엇일까?

```cpp
template<class T> class Widget;
template<typename T> class Widget;
```

차이가 없다. 템플릿의 타입 매개변수 선언할 때는 `class`와 `typename`의 뜻이 완전히 똑같다. 물론 `typename`을 쓰지 않으면 안 되는 때가 분명히 존재한다. 우선 템플릿 안에서 참조할 수 있는 이름의 종류가 두 가지라는 사실을 살펴보자.

```cpp
template<typename C>
void print2nd(const C& container)
{
	if(container.size() >= 2) {
		C::const_iterator iter(container.begin());
		
		++iter;
		int value = *iter;
		std::cout << value;
	}
}
```

여기서 `iter`의 타입은 `C::const_iterator`인데, 템플릿 매개변수 `C`에 따라 달라지는 타입이다.  이렇게 종속된 매개변수를 **의존 이름**이라고 한다. 의존 이름이 어떤 클래스 안에 중첩된 경우를, **중첩 의존 이름**이라고 한다. 여기서 `C::const_iterator`는 중첩 의존 이름이다. 또 다른 지역변수인 `value`는 `int` 타입인데, 이는 템플릿 매개변수가 어떻든 상관없는 타입 이름이다. 이러한 이름은 **비의존 이름**이라고 한다.

코드 안에 중첩 의존 이름이 있으면 골치 아픈 일들이 생긴다. 아래 예제를 보자.

```cpp
template<typename C>
void print2nd(const C& container)
{
	C::const_iterator * x;
	...
}
```

`C::const_iterator`에 대한 포인터인 지역변수로서 `x`를 선언하고 있는 것같이 보인다. 하지만 `C::const_iterator`가 타입이 아니라면? 우연히 `const_iterator`라는 이름의 정적 데이터 멤버가 `C`에 들어 있다면? 혹은 `x`가 다른 전역 변수의 이름이라면 곱셈 연산으로 인식할 수도 있다. 이는 얼마든지 다 가능한 일이다.

`C`의 정체가 무엇인지 다른 곳에서 알려 주지 않으면, `C::const_iterator`가 진짜 타입인지 아닌지를 알아낼 방법은 컴파일러로서는 없다. 이때 C++는 모호성을 해결하기 위해 하나의 규칙을 사용한다. 이 규칙에 의하면, 구문 분석기는 템플릿 안에서 중첩 의존 이름을 만나면 프로그래머가 타입이라고 알려 주지 않는 한 그 이름을 타입이 아니라고 가정한다. 중첩 의존 이름은 기본적으로 타입이 아닌 것으로 해석된다.

이를 바로 잡으려면 한 가지 방법밖엔 없다. C++에게 `C::const_iterator`가 타입이라고 말해주는 것이다. 즉, `C::const_iterator`앞에다가 `typename`이라는 키워드를 붙인다.

```cpp
template<typename C>
void print2nd(const C& container)
{
	if(container.size() >= 2) {
		typename C::const_iterator iter(container.begin());
		...
	}
}
```

템플릿 안에서 중첩 의존 이름을 참조할 경우에는, 그 앞에 `typename` 키워드를 붙여줘야 한다. 그 외의 이름은 `typename`을 가져서는 안 된다. 또한, 중촙 의존 이름이 기본 클래스의 리스트에 있거나 멤버 초기화 리스트 내의 기본 클래스 식별자로서 있을 경우에는 `typename`을 붙여 주면 안 된다. 아래의 예제를 보자.

```cpp
template<typename T>
class Derived: public Base<T>::Nested { // typename 쓰면 안 됨
public:
	explicit Derived(int x) : Base<T>::Nested(x) // typename 쓰면 안 됨
	{
		typename Base<T>::Nested temp; // typename 사용해야 됨
		...
	}
	...
};
```

> 템플릿 매개변수를 선언할 때, `class`및 `typename`은 서로 바꾸어 써도 무방하다.
중첩 의존 타입 이름을 식별하는 용도에는 반드시 `typename`을 사용한다. 중첩 의존 이름이 기본 클래스 리스트에 있거나 멤버 초기화 리스트 내의 기본 클래스 식별자로 있는 경우에는 예외이다.