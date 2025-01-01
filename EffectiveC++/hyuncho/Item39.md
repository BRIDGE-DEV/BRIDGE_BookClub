# Item39. private 상속은 심사숙고해서 고려하자
private 상속은 분명히 is-a 를 뜻하지 않는다. => 다른 뜻이 존재함.
```cpp
class Person {...};

class Student : private Person { ... };

void eat(const Person& p);
void study(const Student& s);

Person p;
Student s;

eat(p);
eat(s);   //에러! Student는 Person의 일종이 아니다.
```
1. public 상속과 대조적으로, 클래스 사이의 상속 관계가 private이면 컴파일러는 일반적으로 파생클래스 객체(Student)를 기본 클래스 객체(Person)로 변환하지 않는다.
2. 기본 클래스로부터 물려받은 멤버는 파생클래스에서 모조리 private가 된다. (기본 클래스에서 원래 protected 멤버였거나 public 멤버였어도)

private 상속의 의미는 **is-implemented-in-terms-of** 이다.

B클래스로부터 private 상속을 통해 D클래스를 파생시킨 것은, B클래스에서 쓸 수 있는 기능들 몇 개를 활용할 목적으로 한 행동이지, B타입 D타입에 두 관계 사이에 개념적 관계가 있어서 한 행동이 아니다.

private 상속은 소프트웨어 설계(design) 도중에 아무런 의미도 갖지 않으며, 단지 소프트웨어 구현(implementation) 중에만 의미를 가진다.

그런데 private 상속의 의미가 is-implemented-in-terms-of 라는 사실은 다소 헷갈리는 부분이 있기도 한다. 항목 38에서 객체 합성도 같은 의미를 가진다고 했기 때문.

is-implemented-in-terms-of 의 의미를 가지는 경우
1. private 상속
2. 객체 합성

할 수 있다면 객체 합성을 하자. 꼭 해야하는 경우라면(비공개 멤버를 접근 할 때 혹은 가상함수를 재정의 하는 경우) private 상속을 사용하자. 

```cpp
class Timer {
public:
	explicit Timer(int tickFrequency);

	virtual void onTick() const;  // 일정시간 경과할 때마다 자동으로 이것이 호출된다.
	...
}
```
Widget 클래스에서 Timer의 가상 함수를 재정의 할 수 있어야 하므로, Widget 클래스는 어쨌든 Timer 에서 상속을 받아야 한다. 하지만 지금 상황에서는 public 상속이 맞지 않다. Widget이 Timer의 일종(is-a)은 아니기 때문. 게다가 Widget 객체를 통해 onTick 함수를 호출하면 안된다. 왜냐하면 이 함수는 개념적으로 Widget 인터페이스의 일부로 볼 수 없기 때문이다.

이대로 두면 onTick 함수를 Widget을 통해 호출할 수도 있는 여지를 주기 때문에 위험하다. 잘못 사용하기가 쉬워짐.

해결법은 결국 public 상속은 처음부터 틀린 선택이고 private 상속을 하는 것.
```cpp
class Widget:private Timer {
private:
	virtual void onTick() const;   //Widget 사용자료 등을 수집한다.
	...
};
```
상속 방식을 private 으로 바꾸었기 때문에 Timer의 public 멤버 onTick 함수는 Widget에서 private 멤버가 되었다.

하지만 꼭 private을 사용해야 하나? -> 대신에 객체 합성을 써도 된다. Timer로 부터 public 상속을 받은 클래스를 Widget 안에 private 중첩 클래스로 선언해놓고, 이 클래스에서 onTick을 재정의한 다음, 이 타입(클래스)의 객체 하나를 Widget 안에 데이터 멤버로서 넣는 것이다.
```cpp
class Widget {
private:
	class WidgetTimer:public Timer{
	public:
		virtual void onTick() const;
		...
	};

	WidgetTimer timer;
	...
};
```
현실적으로 private 상속 대신에 public 상속에 객체 합성 조합이 더 자주 즐겨 쓰이긴 한다.

public 상속에 객체 합성 조합의 장점
1. Widget 클래스를 설계하는 데 있어서 파생은 가능하게 하되, 파생 클래스에서 onTick을 재정의 할 수 없도록 설계 차원에서 막고 싶을 때 유용하다.
2. Widget의 컴파일 의존성을 최소화 하고 싶을 때 좋다. 만약 Widget이 Timer에서 파생된 상태라면, Widget이 컴파일 될 때 Timer의 정의도 끌어 올 수 있어야 한다. 결국 Widget의 정의부 파일에서 Timer.h 같은 헤더를 \#include 해야 할지도 모른다. 해결법으로 WidgetTimer의 정의를 Widget으로부터 빼내고 Widget이 WidgetTimer 객체에 대한 포인터만 갖도록 만들어두면, WidgetTimer 클래스를 간단히 선언하는 것만으로도 컴파일 의존성을 슬쩍 피할 수 있다.

객체의 합성보다 private 상속을 선호할 수 밖에 없는 공간 최적화가 얽힌 '만약의 경우'도 존재한다.

공백클래스(empty class)는 개념적으로 차지하는 공간이 없는 클래스인데 기술적인 우여곡절에 의하여 "독립 구조(freestanding)의 객체는 반드시 크기가 0을 넘어야 한다"라는 요상한 금기사항이 있다.
```cpp
class Empty{};  //정의된 데이터가 없으므로 객체는 메모리를 사용하지 말아야 한다.

class HoldsAnInt {
private:
	int x;
	Empty e;  //메모리 요구가 없어야 한다.
};
```
하지만 결과는 sizeof(HoldsAnInt) > sizeof(int) 가 되는 괴현상을 목겨하게 된다. Empty 타입의 데이터 멤버가 발칙하게 메모리를 요구한다. 대부분의 컴파일러에서 sizeof(Empty)의 값이 1이 나온다.

이유는 크기가 0인 독립구조의 객체가 생기는 것을 금지하는 C++의 제약을 지키기 위해, 컴파일러는 이런 "공백" 객체에 char 한개를 슬그머니 끼워넣는 식으로 처리한다. 바이트 정렬이 필요하다고 판단되면 컴파일러는 HoldsAnInt 등의 클래스에 바이트 패딩 과정을 추가할 수도 있어서 HoldsAnInt 객체의 크기는 char 하나의 크기를 넘게 된다.

해결방법으로는 다음과 같다.
```cpp
class HoldsAnInt:private Empty{
private:
	int x;
};
```
sizeof(HoldsAnInt) == sizeof(int)를 확인가능. 이 공간 절약 기법을 공백 기본 클래스 최적화(Empty Base Optimization : EBO)라고 한다.

사실 아무것도 없는 클래스를 사용하는 것은 정말 드물다. 그렇기 때문에 EBO 하나만 갖고 private 상속이 뭔가 합법적으로 정당화된 것인 양 생각하는 것은 무리에 가깝다.

결국 "private 상속을 심사숙고해서 구사하자"라는 말의 의미는 섣불리 이것을 쓸 필요가 없다는 생각을 갖고 모든 대안을 고민하는 연후에, 주어진 상황에서 두 클래스 사이를 나타낼 가장 좋은 방법이 private 상속이라는 결론이 나면 사용하라.


+ private 상속의 의미는 is-implemented-in-terms-of 이다. 대개 객체 합성과 비교해서 쓰이는 분야가 많지는 않지만, 파생 클래스 쪽에서 기본 클래스의 protected 멤버에 접근해야 할 경우 혹은 상속받은 가상 함수를 재정의해야 할 경우에는 private 상속이 나름대로 의미가 있다.
+ 객체 합성과 달리, private 상속은 공백 기본 클래스 최적화(EBO)를 활성화시킬 수 있다. 이 점은 객체 크기를 가지고 고민하는 라이브러리 개발자에게 꽤 매력적인 특징이 되기도 한다.