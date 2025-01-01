# 챕터6: 상속, 그리고 객체 지향 설계

## 항목 37: 어떤 함수에 대해서도 상속받은 기본 매개변수 값은 절대로 재정의하지 말자

C++에서 상속받을 수 있는 함수는, 가상 함수와 비가상 함수 두 가지 뿐이다. 이들 중 비가상 함수는 언제라도 재정의해서는 안 되는 함수이므로, 재정의하는 함수는 가상 함수밖에 없다. 즉, 이 항목은 ‘기본 매개변수 값을 가진 가상 함수’를 상속하는 경우만 해당하는 이야기이다.

항목 제목의 이유를 바로 이야기해보자면, 가상 함수는 동적으로 바인딩되지만, 기본 매개변수 값은 정적으로 바인딩된다. 아래의 예제를 보자.

```cpp
class Shape {
public:
	enum ShapeColor { Red, Green, Blue };
	virtual void draw(ShapeColor color=Red) const = 0;
	...
};
class Rectangle: public Shape {
public:
	virtual void draw(ShapeColor color=Green) const = 0;
	...
};
class Circle: public Shape {
public:
	virtual void draw(ShapeColor color) const = 0;
	...
};
```

객체의 정적 타입은 프로그램 소스 안에 선언문을 통해 그 객체가 갖는 타입이고, 동적 타입은  그 객체가 진짜로 무엇이냐에 따라 결정되는 타입이다.

가상 함수는 ‘동적’으로 바인딩된다. 하지만 기본 매개변수는 ‘정적’으로 바인딩되어 있다. 즉, 파생 클래스에 정의된 가상 함수를 호출하면서 기본 클래스에 정의된 기본 매개변수 값을 사용해버릴 수 있다는 것이다.

```cpp
Shape* pr = new Rectangle;
pr->draw(); // Rectangle::draw(Shape::Red)를 호출한다
```

만약 함수의 기본 매개변수가 동적으로 바인딩된다면, 프로그램 실행 중에 가상 함수의 기본 매개변수 값을 결정할 방법을 컴파일러 쪽에서 정해줘야 한다. 이 방법은 현재의 매커니즘보다는 느리고 복잡할 것이기 때문에, 반영되지 않았다.

결국 기본 매개변수 값은 똑같이 제공을 해야 한다. 하지만 이 경우에는 기본 매개변수 값이 변하기라도 하면, 파생 클래스도 모두 그 값을 변경해야 한다.

이것을 해결하는 방법은 앞에서도 나왔던 **비가상 인터페이스 관용구(NVI)**를 활용하는 것이다. 재정의할 수 있는 가상함수를 private으로 두고, 이 가상 함수를 호출하는 public 비가상 함수를 기본 클래스에 만들어둔다. 이것을 응용해 비가상 함수가 기본 매개변수를 지정하도록 하면, 기본 매개변수 값을 깔끔하게 고정할 수 있다.

```cpp
class Shape {
public:
	enum ShapeColor { Red, Green, Blue };
	void draw(ShapeColor color=Red) const
	{
		doDraw(color);
	}
	...
private:
	virtual void doDraw(ShapeColor color) const = 0;
};
class Rectangle: public Shape {
public:
	...
private:
	virtual void doDraw(ShapeColor color) const = 0;
	...
};
```

> 상속받은 기본 매개변수 값은 절대로 재정의해서는 안 된다. 기본 맥개변수 값은 정적 바인딩되지만, 가상 함수는 동적으로 바인딩되기 때문이다.