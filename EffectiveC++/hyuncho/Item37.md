# Item37. 어떤 함수에 대해서도 상속 받은 기본 매개 변수 값은 절대로 재정의하지 말자.
상속 받을 수 있는 함수의 종류는 가상함수, 비가상 함수이다. 하지만 비가상함수는 언제라도 재정의해서는 안된다.
```cpp
class Shape {
public:
	enum ShapeColor { Red, Green, Blue };

	//모든 도형은 자기 자신을 그리는 함수를 제공해야 한다.
	virtual void draw(ShapeColor color = Red) const = 0;
	...
};

class Rectangle : public Shape {
public:
	//기본 매개변수 값이 달라짐.
	virtual void draw(ShapeColor color = Green) const;
	...
};

class Circle : public Shape {
public:
	virtual void draw(ShapeColor color) const;
	...
};
```
이들을 포인터를 써서 나타내면
```cpp
Shape *ps;  //정적 타입 = Shape*
Shape *pc = new Circle;  //정적 타입 = Shape*
Shape *pr = new Rectangle;  //정적 타입 = Shape*
```
객체의 동적 타입은 현재 그 객체가 진짜로 무엇이냐에 따라 결정되는 타입이다. '이 객체가 어떻게 동작할 것이냐'를 가리키는 타입이 동적 타입니다.

위의 예에서 pc의 동적 타입은 Circle* 이고, pr의 동적 타입은 Rectangle* 이다.

동적 타입은 이름과 같이 프로그램 실행 도중에 바뀔 수 있다.
```cpp
ps = pc;  //ps의 동적 타입은 이제 Circle* 가 된다
ps = pr;  //ps의 동적 타입은 이제 Rectangle* 이 된다.
```
가상 함수는 동적으로 바인딩 된다. (가상 함수의) 호출이 일어난 객체의 동적 타입에 따라 어떤 (가상) 함수가 호출될지가 결정된다는 의미이다.
```cpp
pc->draw(Shape::Red);  //Circle::draw(Shape::Red)를 호출한다
pr->draw(Shape::Red);  //Rectangle::draw(Shape::Red)를 호출한다

pr->draw();  //Rectangle::draw(Shape::Red)를 호출...!
```
'기본 매개 변수 값이 설정된' 가상 함수로 오게 되면 문제가 발생한다. 이유는 가상 함수는 동적으로 바인딩 되어 있지만 기본 매개변수는 정적으로 바인딩되어 있기 때문이다.

즉, 파생클래스에 정의된 가상 함수를 호출하면서 기본 클래스에 정의된 기본 매개변수 값을 사용해버릴 수 있다. 왜 이런 일이 발생하냐하면 런타임 효율이라는 요소가 깊이 숨어있다.

함수의 기본 매개변수가 동적으로 바인딩 된다면, 프로그램 실행 중에 가상함수의 기본 매개변수 값을 결정할 방법을 컴파일러쪽에서 마련해주어야 한다. 이는 결국 현재 메커니즘보다 느리고 복잡할 것이다. 속도 유지와 구현 간편성을 위해 현재의 메커니즘이 만들어져 효율 좋은 실행 동작을 이용하는 것이다.
```cpp
class Shape {
public:
	enum ShapeColor { Red, Green, Blue };

	void draw(ShapeColor color = Red) const
	{
		doDraw(color);
	}
	...
private:
	virtual void doDraw(ShapeColor color) const = 0;
};

class Rectangle : public Shape {
public:
	...
private:
	virtual void doDraw(ShapeColor color) const;
	...
};
```
위와 같이 NVI를 이용하여 래핑을 한다면 파생클래스에서 재정의 할 수 있는 함수를 private로 놓고 이 가상함수를 호출하는 public 비가상 함수를 기본클래스에 만들어 두는 것이다.

비가상함수 안에서 기본 매개변수를 지정하도록 할 수 있고 이 비가상 함수의 내부에서는 진짜 일을 맡은 가상함수를 호출하게 한다. 비가상함수는 파생클래스에서 오버라이드 되면 안 되기 때문에 위와 같이 설계하면 draw함수의 color 매개변수에 대한 기본값을 깔끔하게 Red 로 고정 가능하다.


+ 상속받은 기본 매개변수 값은 절대로 재정의해서는 안된다. 왜냐하면 기본 매개변수 값은 정적으로 바인딩되는 반면, 가상 함수(오버라이드 할 수 있는 유일한 함수)는 동적으로 바인딩되기 때문이다.