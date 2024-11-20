# 챕터5: 구현

## 항목 28: 내부에서 사용하는 객체에 대한 ‘핸들’을 반환

다음의 코드를 보자.

```cpp
struct RectData {
	Point ulhc;
	Point lrhc;
};
class Rectangle {
public:
	...
	Point& upperLeft() const { return pData->ulhc; }
	Point& lowerRight() const { return pData->lrhc; }
	...
private:
	std::tr1::shared_ptr<RectData> pData;
};
```

이 코드는 자기모순적인 코드이다. `upperLeft` 함수와 `lowerRight` 함수는 상수 멤버 함수이다. 이 함수들이 반환하는 것은 private 멤버인 내부 데이터에 대한 참조자이다. 결국 private 멤버임에도 불구하고, 이 데이터를 퍼블릭 인터페이스 등을 통해 조작할 수 있다.

우리는 여기서 두 가지 교훈을 얻을 수 있다. 첫째, 클래스 데이터 멤버는 아무리 숨겨봤자 그 멤버의 참조자를 반환하는 함수들의 최대 접근도에 따라 캡슐화 정도가 정해진다. `ulrc`, `lrhc`는 private으로 선언되어 있지만, 실질적으로는 public 멤버이다. 둘째, 어떤 객체에서 호출한 상수 멤버 함수의 참조자 반환 값의 실제 데이터가 그 객체 바깥에 저장되어 있다면, 함수의 호출부에서 그 데이터의 수정이 가능하다는 점이다.

참조자, 포인터 및 반복자는 어쨌든 모두 **핸들**이고, 어떤 객체의 내부요소에 대한 핸들을 반환하게 만들면 언제든지 그 객체의 캡슐화를 무너뜨릴 수 있다. 이것 때문에 상수 멤버 함수조차도 객체 상태의 변경을 허용하는 지경에까지 이를 수 있다.

외부 공개가 차단된 멤버 함수에 대해, 이들의 포인터를 반환하는 멤버 함수를 만드는 일이 절대로 없어야 한다. 이런 함수가 하나라도 들어가는 순간부터 실질적인 접근 수준이 바뀐다. 이런 함수의 문제를 해결하는 방법은, 반환 타입에 const 키워드만 붙여주면 된다.

```cpp
class Rectangle {
public:
	...
	const Point& upperLeft() const { return pData->ulhc; }
	const Point& lowerRight() const { return pData->lrhc; }
	...
};
```

사용자는 사각형을 정의하는 꼭짓점 쌍을 읽을 수는 있지만, 쓸 수는 없게 됩니다. 그럼에도 아직 내부 데이터에 대한 핸들을 반환하는 부분이 남아있다. 이로 인한 가장 큰 문제가 **무효참조 핸들(dangling handle)**로서, 핸들이 있기는 하지만 그 핸들을 따라갔을 때 실제 객체의 데이터가 없는 것이다.

```cpp
class GUIObject { ... };
const Rectangle boundingBox(const GUIObject& obj);
GUIObject *pgo;
...
const Point *pUpperLeft = &(boundingBox(*pgo).upperLeft());
```

`boundingBox` 함수를 호출하면 `Rectangle` 임시 객체가 새로 만들어진다. 이 객체는 겉으로 드러나는 이름 같은 것이 없으므로 `temp`라고 하자. 이 `temp`에 대해 `upperLeft`가 호출될 텐데, 그렇다면 이 `temp`의 내부 데이터가 나온다.

하지만 이 문장이 끝날 무렵, `boundingBox` 함수의 반환 값은 소멸된다. `temp`가 소멸되니, 그 안에 들어있는 `Point` 객체들도 덩달아 없어진다. 이제 `pUpperLeft` 포인터가 가리키는 객체는 날아가고 없게 된다.

이처럼 객체의 내부에 대한 핸들을 반환하는 함수는 어떻게든 위험하다. 포인터이든, 참조자이든, 반복자이든 위험하기는 마찬가지다. 핸들에 `const`를 붙였느냐 안 붙였느냐도 상관없다. 핸들을 반환하는 함수라는 사실, 그것 빼고는 아무것도 중요치 않다.

> 어떤 객체의 내부요소에 대한 핸들(참조자, 포인터, 반복자)을 반환하는 것은 되도록 피하자. 캡슐화 정도를 높이고, 상수 멤버 함수가 객체의 상수성을 유지한 채로 동작할 수 있도록 하며, 무효참조 핸들이 생기는 경우를 최소화할 수 있다.