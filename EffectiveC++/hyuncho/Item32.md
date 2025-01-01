# Item32. public 상속 모형은 반드시 "is-a"를 따르도록 만들자
public 상속은 반드시 "is-a" 관계를 뜻해야 하며, 이외의 의미를 붙이려고 하면 난처해질 수도 있다.

가상 함수의 의미는 "인터페이스가 상속되어야 한다"인 반면, 비가상 함수의 의미는 "인터페이스와 구현이 둘 다 상속 되어야 한다"이다.

만약 클래스 D("Derived")를 클래스 B("Base")로부터 public 상속을 통해 파생시켰다면, C++에게 이렇게 말한 것과 같다. D타입으로 만들어진 모든 객체는 또한 B타입의 객체이지만, 그 반대는 되지 않는다.

D is a B

C++는 public 상속을 이렇게 해석하도록 문법적으로 지원하고 있다.
```cpp
class Person { ... };

class Student : public Person { ... };
```
이는 모든 학생들은 사람이지만 모든 사람이 학생은 아니라는 사실을 제공한다.
```cpp
void eat(const Person& p);  //먹는 것은 누구든 한다.

void study(const Student& s);  //학과 공부는 학생만 한다.

Person p;
Student s;

eat(p);  //문제 없음
eat(s);  //문제 없음

study(s);  //문제 없음
study(p);  //문제 발생. p는 Student가 아니다.
```
public 상속과 is-a 관계가 똑같은 뜻이라는 이야기는 꽤 직관적이고 간단하긴 하지만, 그 직관 때문에 판단을 잘못하는 경우도 있다. 예를 들면 펭귄이 새의 일종이라는 점은 누구나 아는 사실이고, 새라는 개념만 보면 새가 날 수 있다는 점도 사실이다. 이것을 코드로 표현해보려고 하면 아래 코드처럼 된다.
```cpp
class Bird {
public:
	virtual void fly();  //새는 날 수 있다.
	...
};

class Penguin: public Bird {  //펭귄은 새이다.
	...
};
```
위의 클래스 계통에 의하면 펭귄은 날 수 있다. 하지만 이것은 맞지 않다. 우리는 명확치 않은 자연어의 표현에 낚이 것으로 "새는 날 수 있다"라고 말할 때 모든 새는 날 수 있다는 의미를 품은 것은 아니였다. 좀 더 명확히 할 필요가 있었다. 다음 코드는 좀 더 현실에 가까운 클래스 계통구조를 볼 수 있다.
```cpp
class Bird {
	...  //fly 함수가 선언되지 않았다.
};

class FlyingBird : public Bird {
public:
	virtual void fly();
	...
};

class Penguin : public Bird {
	...  //fly 함수가 선언되지 않았다.
};
```
비행 능력이 있는 새와 없는 새를 구분하지 않아도 될 수 있기 때문에 상황에 맞춰서 사용하면 된다.

또 다른 방법으로 펭귄의 fly 함수를 재정의해서 런타임 에러를 내도록 하는 방법도 있다.
```cpp
void error(const std::string& msg);

class Penguin : public Bird {
public:
	virtual void fly() { error("Attempt to make a penguin fly!"); }
	...
};
```
위의 코드는 우리가 생각하는 것과 조금 다르다. "펭귄은 날 수 없다"가 아니라 "펭귄은 날 수 있다. 그러나 펭귄이 실제로 날려고 하면 에러가 난다."라는 의미이다. 즉, "펭귄은 날 수 없다"라는 지령은 컴파일러가 내리지만 "펭귄이 실제로 날려고 하면 에러가 난다"라는 규칙을 위반하는 것은 프로그램이 실행될 때만 발견할 수 있다.

그렇다면 "펭귄은 날 수 없다 - 도장 꽝" 이라는 제약 사항도 같이 넣어보도록하자. Penguin 객체에 대해서는 비행과 관련된 함수를 정의하지 않도록 하면 된다.
```cpp
class Bird {
	...  //fly 함수가 선언되지 않음.
};

class Penguin : public Bird {
	...  //fly 함수가 선언되지 않음.
};
```
이렇게 하면 펭귄을 날려보려고 할때 컴파일 단계에서 컴파일러가 뭔가를 어겼다고 경고를 보낼 것이다.
```cpp
Penguin p;

p.fly();  //에러
```
이렇게 유효하지 않은 코드를 컴파일 단계에서 막아 주는 인터페이스가 좋은 인터페이스이다.

이번에는 Square 클래스는 Rectangle 클래스로부터 상속을 받아야 하는지 알아보겠다.
```cpp
class Rectangle {
public:
	virtual void setHeight(int newHeight);
	virtual void setWidth(int newWidth);

	virtual int height() const;
	virtual int width() const;
	...
};

void makeBigger(Rectangle& r)
{
	int oldHeight = r.height();

	r.setWidth(r.width() + 10);

	assert(r.height() == oldHeight);  //r의 세로 길이가 변하지 않는다는 조건에 단정문을 건다.
}
```
여기서 위의 단정문이 실패할 일이 없다는 것은 확실하다. makeBigger 함수는 r의 가로 길이만 변경할 뿐이고, 세로 길이는 바뀌지 않는다.

이제 public 상속을 써서 정사각형을 직사각형처럼 처리하게끔 허용하는 코드를 보자.
```cpp
class Square : public Rectangle { ... };

Square s;
...
assert(s.width() == s.height());  //이 단정문은 모든 정사각형에 대해 참이어야 한다.

makeBigger(s);

assert(s.width() == s.height());  //이번에도 이 단정문이 모든 정사각혀에 대해 참이어야 한다.
```
두 번째 단정문도 실패하면 안된다. 왜냐하면 정사각형의 정의가 가로길이와 세로길이가 같기 때문이다. 그런데 makeBigger함수 이후에 s의 가로 길이는 변하는데 세로 길이는 변하지 않아 문제가 발생한다.

public 상속에 대해서 제대로 사용하지 않으면 이런 문제가 발생할 수 있다. public 상속은 기본 클래스 객체가 가진 모든 것들이 파생 클래스 객체에도 그대로 적용된다고 단정하는 상속이다. 그런데 직사각형과 정사각형의 경우를 보면 이런 단정이 참이 될 수 없다.

클래스들 사이에 맺을 수 있는 관계로 is-a 관계만 있는 것은 아니다. 두 가지가 더 있는데, 하나는 has-a 이고 또 하나는 is-implemented-in-terms-of 이다. 이 두가지 항목은 38,39에서 볼 수 있다. C++ 코드를 보다 보면 is-a 이외의 나머지 두 관계를 is-a 관계로 모형화해서 설계가 이상하게 꼬이는 경우가 정말 많다.

그렇기에 클래스 사이에 맺을 수 있는 관계들을 명확하게 구분할 수 있도록 하고, 이 각각을 C++로 가장 잘 표현하는 방법도 공부해 둘 것을 권장한다.


+ public 상속의 의미는 "is-a"이다. 기본 클래스에 적용되는 모든 것들이 파생 클래스에 그대로 적용되어야 한다. 왜냐하면 모든 파생클래스 객체는 기본 클래스 객체의 일종이기 때문이다.