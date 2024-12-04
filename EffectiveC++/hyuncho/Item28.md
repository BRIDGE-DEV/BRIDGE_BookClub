# Item28. 내부에서 사용하는 객체에 대한 '핸들'을 반환하는 코드는 되도록 피하자
```cpp
class Point {
public:
	Point(int x, int y);
	...
	void setX(int newVal);
	void setY(int newVal);
	...
};

struct RectData {
	Point ulhc;
	Point lrhc;
};

class Rectangle {
	...
private:
	std::tr1::shared_ptr<RectData> pData;
}
```
위와 같은 코드가 있을 때 사용자 정의에 의한 타입을 전달할 때는 값에 의한 전달보다 참조에 의한 전달방식을 쓰는 편이 더 효율적이다. 그래서 두 멤버 함수는 포인터로 물어둔 Point 객체에 대한 참조자를 반환하는 형태로 만들겠다.
```cpp
class Rectangle {
public:
	...
	Point& upperLeft() const { return pData->ulhc; }
	Point& lowerRight() const { return pData0>lrhc; }
	...
}
```
위 코드는 컴파일은 되지만 자기 모순적인 코드를 갖고 있다. 이유는 객체 수정이 되지 않도록 의도하고 설계를 했는데 핸들을 넘겨줌으로써 아래와 같은 코드에서 객체 수정인 내부 데이터 변경이 일어난다.
```cpp
Point coord1(0,0);
Point coord2(100, 100);

const Rectangle rec(coord1, coord2);

rec.upperLeft().setX(50);
```
여기서 두가지 교훈을 얻을 수 있다.
1. 클래스 데이터 멤버는 아무리 숨겨도 그 멤버의 참조자를 반환하는 함수들의 최대 접근도에 따라 캡슐화 정도가 정해진다.
2. 어떤 객체에서 호출한 상수 멤버 함수의 참조자 반환 값의 실제 데이터가 그 객체의 바깥에 저장되어 있다면, 이 함수의 호출부에서 그 데이터의 수정이 가능하다는 점이다.

아래와 같이 반환 타입에 const를 붙이면 멤버함수가 가진 두가지 문제를 해결가능하다.
```cpp
class Rectangle {
public:
	...
	const Point& upperLeft() const { return pData->ulhc; }
	const Point& lowerRight() const { return pData->lrhc; }
};
```
읽기 권한만 주고 쓰기 접근은 금지 시킨 경우이다.
이 경우도 핸들을 반환하기 때문에 발생하는 문제가 존재한다. 바로 무효참조 핸들(dangling handle)로서, 핸들이 있기는 하지만 그 핸들을 따라갔을 때 실제 객체의 데이터가 없는 것이다.
```cpp
class GUIObject { ... };

const Rectangle boundingBox(const GUIObject& obj);

GUIObject *pgo;

const Point *pUpperLeft = &(boundingBox(*pgo).upperLeft());
```
마지막 코드에서 boundingBox를 호출하면 임시 객체가 새로 만들어지고 해당하는 upperLeft()의 반환값을 부여받지만 임시 객체는 이후 사라져버리며 upperLeft()의 반환값 또한 소멸된다.

핸들을 반환하는 경우를 절대로 두지 말라는 이야기는 아니다. 최대한 피하자의 이야기이고 필요한 경우로는 예를 들면 operator[] 연산자는 string이나 vector 등의 클래스에서 개개의 원소를 참조할 수 있게 만드는 용도로 제공되고 있는데, 실제로 이 연산자는 내부적으로 해당 컨테이너에 들어 있는 개개의 원소 데이터에 대한 참조자를 반환하는 식으로 동작한다. 


+ 어떤 객체의 내부요소에 대한 핸들(참조자, 포인터, 반복자)을 반환하는 것은 되도록 피하세요. 캡슐화 정도를 높이고, 상수 멤버 함수가 객체의 상수성을 유지한 채로 동작할 수 있도록 하며, 무효참조 핸들이 생기는 경우를 최소화 할 수 있다.