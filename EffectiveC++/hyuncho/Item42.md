# Item42. typename의 두 가지 의미를 제대로 파악하자
```cpp
template<class T> class Widget;
template<typename T> class Widget;
```
위 선언문에 쓰인 class와 typename의 차이점은 무엇일까? => 차이가 없다. 완전히 같은 의미.
그렇다고 언제나 class와 typename이 c++ 앞에서 동등한 것만은 아니다. typename을 쓰지 않으면 안되는 때가 있다.
```cpp
template <typename C>
void print2nd(const C& container)
{
	if (container.size() >= 2){
		C::const_iterator iter(container.begin());

		++iter;
		int value = *iter;
		std::cout << value;
	}
}
```
iter의 타입은 보다시피 C::const_iterator 인데 템플릿 매개변수인 C에 따라 달라지는 타입이다. 템플릿 내의 이름 중에 이렇게 템플릿 매개변수에 종속된 것을 가리켜 의존 이름(dependent name)이라고 한다. 의존 이름이 어떤 클래스에 중첩되어 있는 경우가 있는데 이 경우의 이름을 중첩 의존 타입 이름(nested dependent type name) 이라고 한다.

print2nd 함수 에서 쓰이는 또 하나의 지역변수, value는 int 타입이다. int는 템플릿 매개변수가 어떻든 상관없는 타입이름이다. 이러한 이름은 비의존 이름(non-dependent name) 이라고 한다.

코드 안에 중첩 의존 이름이 있으면 골치 아픈 일이 발생한다. 컴파일러가 구문 분석을 할 때 애로사항이 발생한다.
```cpp
template<typename C>
void print2nd(const C& container)
{
	C::const_iterator *x;
	...
}
```
언뜻 보기에는 C::const_iterator 에 대한 포인터인 지역 변수로서 x를 선언하고 있는 것 같다. 근데 포인터인 지역변수가 아니라면? 우연히 const_iterator 라는 이름을 가진 정적 데이터 멤버가 들어있다면? 그리고 x가 다른 전역 변수의 이름이라면 곱셈연산이 발생 할 수도 있다.
```cpp
template<typename C>
void print2nd(const C& container)
{
	if(container.size() >= 2){
		typename C::const_iterator iter(container.begin());
		...
	}
}
```
이렇게 typename을 사용하여 C++에게 C::const_iterator가 타입이라고 말해주는 것이다. 

"typename은 중첩 의존 타입 이름 앞에 붙여 주어야 한다"는 규칙에 예외가 하나 있다. 이 예외란, 중첩 의존 타입 이름이 기본 클래스의 리스트에 있거나 멤버 초기화 리스트 내의 기본 클래스 식별자로서 있을 경우에는 typename을 붙여주면 안된다 라는 것이다.
```cpp
template<typename T>
class Derived : public Base<T>::Nested{   //상속되는 기본 클래스 리스트: typename 쓰면 안됨.
public:
	explicit Derived(int x)
	: Base<T>::Nested(x)  //멤버 초기화 리스트에 있는 기본 클래스 식별자: typename 쓰면 안됨.
	{
		typename Base<T>::Nested temp;
		...
	}
	...
};
```
이번 항목에서 나온 typename에 대한 규칙을 얼마나 강조하는지는 컴파일러마다 조금씩 차이가 있다.


+ 템플릿 매개변수를 선언할 때, class 및 typename은 서로 바꾸어 써도 무방하다.
+ 중첩 의존 타입 이름을 식별하는 용도에는 반드시 typename을 사용한다. 단, 중첩 의존 이름이 기본 클래스 리스트에 있거나 멤버 초기화 리스트 내의 기본 클래스 식별자로 있는 경우에는 예외이다.