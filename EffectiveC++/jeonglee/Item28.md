## Item 28: 내부에서 사용하는 객체에 대한 '핸들'을 반환하는 코드는 되도록 피하자

이번 아이템은 꼭 `C++`에서만 해당하는 것이 아닌 다른 언어(`C#`)에서도 해당하는 내용이다.

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
public:
    const Point& upperLeft() const { return pData->ulhc; }
    const Point& lowerRight() const { return pData->lrhc; }

private:
    std::shared_ptr<RectData> pData;
};
```

*shared_ptr에 대한 내용은 [Item 13](https://github.com/fkdl0048/BookReview/issues/295)을 참고하면 되지만, 여기서는 플라이웨이트 패턴과 같이 사용되었다. 정리예정 [Flyweight Pattern](https://github.com/fkdl0048/CodeReview/issues/85)*

이 코드는 컴파일은 문제없이 동작하지만, 자기모순적인 코드이다. `upperLeft`와 `lowerRight`는 상수 멤버 함수이다. 이는 Rectangle의 꼭지점 정보만을 노출하고 수정하는 일이 없도록 하기 위한 설계임을 알 수 있다. 하지만 **이 함수들이 반환하는 값은 내부 데이터에 대한 참조자로 호출부에서 이 참조자를 써서 내부 데이터를 맘대로 수정할 수 있게 된다.**

이러한 사실로 다음과 같은 아이디어를 도출할 수 있다. 첫째, **클래스 데이터 멤버는 아무리 숨겨봤자 그 멤버의 참조자를 반환하는 함수들의 최대 접근도에 따라 캡슐화 정도가 정해진다는 점이다.** 즉, 현재 `ulhc`와 `lrhc`는 `private`으로 선언되어 있지만, `upperLeft`와 `lowerRight`를 통해 접근할 수 있기 때문에 `public`으로 선언된 것과 다를 바 없다. 둘째, **어떤 객체에서 호출한 상수 멤버 함수의 참조자 반환 값의 실제 데이터가 그 객체의 바깥에 저장되어 있다면, 이 함수의 호출부에서 그 데이터의 수정이 가능하다는 점이다.** *이는 비트수준 상수성의 한계를 가진 부수적 성질이다.*

- [Item 3: 낌새만 보이면 const를 들이대 보자!](https://github.com/fkdl0048/BookReview/issues/279)
  - 비트수준 상수성에 대한 내용이 있다.

예제와 같이 참조자를 반환하는 함수만 이야기했지만 포인터나 반복자도 마찬가지 이유로 문제가 발생한다. 이들을 모두 묶어서 **핸들**이라고 말한다. 이것이 위험한 이유는 앞에서도 계속 말했지만 해당 객체의 캡슐화를 깨뜨리기 때문이다.

핸들에 관한 이야기는 어떤 객체의 내부요소의 이야기로 이어진다. 내부요소라고 하면 흔히 데이터 멤버만 생각할 수 있지만 일반적인 수단으로 접근이 불가능한 private으로 선언도니 멤버 함수도 객체의 내부요소로 볼 수 있다.

하지만 `C++`의 아주 큰 장점인 `const`키워드를 잘 활용만 한다면 이러한 문제를 해결할 수 있다.

```cpp
class Rectangle {
    ...
public:
    const Point& upperLeft() const { return pData->ulhc; }
    const Point& lowerRight() const { return pData->lrhc; }
    ...
};
```

*const가 멤버 함수 앞에 붙는다고 특별해지는 것이 아닌 반환값이 `const`로 된다는 것이다. 즉, 반환값을 통해 객체의 내부를 수정할 수 없다는 것이다.*

이를 통해 호출부에서 객체의 상태를 바꾸지 못하도록 컴파일러 수준에서 막고 있다. 그리고 캡슐화의 문제로 사용자들이 Rectangle을 구성하는 Point를 들여다보도록 하자는 것은 처음부터 알고 시작한 설계이기 때문에, 이 부분은 의도적인 완화라고 할 수 있다. **이보다 더 중요한 것은 느슨하게 만든 데에도 제한을 두고 있다는 것이다.**

### 두 번째 문제

`upperLeft`와 `lowerRight`함수를 보면 내부 데이터에 대한 핸들을 반환하고 있는 찝찝함은 남아있다. 불변을 보장하더라도 해당 핸들이 **무효참조 핸들(dangling handle)**가 될 수 있기 때문이다. *핸들에 접근하여 값을 확인했지만 핸들이 물고 있는 객체의 데이터가 없는 경우를 말한다.*

```cpp
class GUIObject { ... };

const Rectangle boundingBox(const GUIObject& obj);

GUIObject* pgo;
...
const Point* pUpperLeft = &(boundingBox(*pgo).upperLeft());
```

이런 코드가 있을 때, `boundingBox`함수를 호출하면 Rectangle 임시 상수 객체가 새로 만들어진다. 이 객체는 겉으로는 드러나는 이름 같은 것이 없으므로 임시 객체 temp로 지정된다. 이 temp에 대해 upperLeft함수를 호출하게 되고 이 호출로 인해 temp의 내부 데이터인 Point객체에 대한 참조자가 나오게 된다. 마지막으로 이 참조자에 대한 & 연산자를 건 결과 값(주소)가 pUpperLeft에 저장된다.

**이 코드는 사실 boundingBox에 의해 생성된 함수의 임시 값이 소멸된다**. temp의 값이 소멸되니 그 안에 들어있는 값도 덩달아 없어질 것이다. 결국 이 문장은 pUpperLeft에게 객체를 달아 줬다가 주소 값만 남기고 몽땅 빼앗아 버리는 것이다.

객체의 내부에 대한 핸들 반환은 결국 cosnt를 붙이던 안붙이던 위험하다는 것이다. 그렇다고 핸들을 반환하는 함수를 절대로 두지 말라는 이야기는 아니다. 예를 들어 operator[] 연산자는 string이나 vector등의 클래스에서 개개의 원소를 참조할 수 있게 만드는 용도로 제공되고 있다.

*하지만 이러한 함수는 예외적인 것으로 일반적이지 않다.*

### 정리

- 어떤 객체의 내부요소에 대한 핸들을 반환하는 것은 되도록 피하자. 캡슐화 정도를 높이고, 상수 멤버 함수가 객체의 상수성을 유지한 채로 동작할 수 있도록 하며, 무효참조 핸들이 생기는 경우를 최소화할 수 있다.
