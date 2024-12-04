## Item 27: 캐스팅은 절약, 또 절약! 잊지 말자

> 어떤 일이 있어도 타입 에러가 생기지 않도록 보장한다.  
> C++ 동작 규칙

이러한 규칙을 아무렇지 않게 무시할 수 있는 친구가 바로 Cast이다. 다른 객체지향 언어 C#, Java와 다르게 C++에서의 캐스팅은 정말로 조심해야 한다. 우선 캐스팅 문법부터 정리하고 문제점에 대해서 알아보자.

### C 스타일 캐스팅

    (T) 표현식 // 표현식 부분을 T타입으로 캐스팅한다.

함수 방식 캐스트

    T (표현식) // 표현식 부분을 T타입으로 캐스팅한다.

이런 캐스팅을 통틀어 `구형 스타일의 캐스트`라고 칭한다.

### C++ 스타일 캐스팅

- `const_cast`: 객체의 상수성을 제거한다.
- `dynamic_cast`: 안전한 다운캐스팅을 지원한다. 주어진 객체가 어떤 상속 계통에 속한 특정 타입인지 아닌지를 결정한다. *런타임 비용이 매우 높다.*
- `reinterpret_cast`: 포인터를 int로 바꾸는 등의 하부 수준 캐스팅을 위해 만들어진 연산자이다. 따라서 하부 수준 코드 이외에는 없어야 한다.
- `static_cast`: 암시적 변환(비상수를 상수 객체로 변경하거나, int를 double로 변경하는 등)을 강제적으로 수행할 때 사용한다.

### C++에서 사용

C++에서는 C 스타일 캐스팅을 사용하지 않는 것이 좋다. C++ 스타일 캐스팅을 사용하자. 이는 다른 사람이 코드를 읽을 때 더 쉽게 읽을 수 있으며 캐스트를 사용한 목적을 더 좁혀서 지정할 수 있다.

캐스팅은 그냥 어떤 타입을 다른 타입으로 처리하라고 컴파일러에게 알려주는 것 뿐만 아니라 타입 변환이 있으면 런타임에 실행되는 코드가 만들어지는 경우가 있다.

#### 캐스팅을 조심해야 하는 이유

```cpp
int x, y;
...
double d = static_cast<double>(x) / y;
```

실제 이 동작은 int 타입 x를 double 타입으로 캐스팅한 부분에서 코드가 만들어진다.

```cpp
class Base { ... };

class Derived : public Base { ... };

Derived d;

Base *pb = &d;
```

이 경우에는 일반적인 파생 클래스 객체에 대한 기본 클래스 포인터를 만드는 코드이지만, 두 포인터의 값이 다를 수 있다. **이런 경우가 생기면 포인터 변위를 Derived* 포인터에 적용하여 실제 Base* 포인터의 값을 구하는 계산이 런타임에 일어난다.**

```cpp
class Window {
public:
    virtual void onResize() { ... }
    ...
};

class SpecialWindow : public Window {
public:
    virtual void onResize() {
        static_cast<Window>(*this).onResize();
        ...
    }
}
```

이런 코드가 있다고 가정할 때(동작하지 않음) 부모 메서드를 실행하기 위해서 다음과 같이 캐스팅을 사용할 수 있다. 하지만 실제 동작에서 `onResize`를 호출하는 객체는 현재의 객체가 아니다. 캐스팅이 일어나면서 `*this`의 기본 클래스 부분에 대한 **사본이 임시적으로 만들어지게 되어 있는데, 이 임시 객체에 호출한 것이기 때문에 현재의 객체에 대해 호출하지 않는다.**

```cpp
class SpecialWindow : public Window {
public:
    virtual void onResize() {
        Window::onResize();
        ...
    }
}
```

다른 동작없이 명확하게 위와 같이 사용하면 된다.

#### dynamic_cast를 사용하는 경우

물론 파생 클래스 객체임이 분명한 경우 이에 대해 파생 클래스의 함수를 호출하고 싶은데, 그 객체를 조작할 수 있는 수단으로 기본 클래스의 포인터빆에 없는 경우는 적지 않게 생긴다. 이런 문제를 피해가는 일반적인 방법이 있다.

첫 번째 방법으로 파생 클래스에 대한 포인터를 컨테이너에 담아둠으로써 각 객체를 기본 클래스 인터페이스를 통해 조작할 필요를 아예 없애버리는 것이다.

```cpp
std::vector<std::shared_ptr<SpecialWindow>> windows;

for (const auto& w : windows) {
    w->onResize();
}
```

#### 피해야 하는 설계

가장 피해야하는 설계는 `폭포식(cascading) dynamic_cast`이다.

```cpp
class Window { ... };

class SpecialWindow : public Window { ... };
class SpecialWindow2 : public SpecialWindow { ... };
class SpecialWindow3 : public SpecialWindow2 { ... };

typedef std::vector<std::shared_ptr<Window>> VPW;

VPW windows;

for (const auto& w : windows) {
    if (SpecialWindow *psw = dynamic_cast<SpecialWindow*>(w.get())) {
        psw->onResize();
    }
    else if (SpecialWindow2 *psw2 = dynamic_cast<SpecialWindow2*>(w.get())) {
        psw2->onResize();
    }
    else if (SpecialWindow3 *psw3 = dynamic_cast<SpecialWindow3*>(w.get())) {
        psw3->onResize();
    }
}
```

이런 코드는 크기만 크고, 속도도 느리며, 망가지기 쉬운 구조의 코드이다. Window클래스가 수정되거나 추가될 때마다 이 코드는 같이 수정되어야 한다. (강하게 SOLID를 지키지 않은 코드)

정말 잘 작성된 C++코드는 캐스팅을 거의 쓰지 않기에 최대한 멀리하며, 사용해야 할 때는 스스로 다시한번 물어보는 것이 좋다.

### 정리

- 다른 방법이 가능하다면 캐스팅은 피하자! 특히 수행 성능이 민감한 코드에서 dynamic_cast는 몇 번이고 다시 생각해보자. 설계 중에 캐스팅이 필요해졌다면 캐스팅을 쓰지 않는 다른 방법을 시도해보자.
- 캐스팅이 어쩔 수 없이 필요하다면, 함수 안에 숨길 수 있도록 하자. 이렇게 하면 최소한 사용자는 자신의 코드에 캐스팅을 넣지 않고 이 함수를 호출할 수 있다.
- 구현 스타일의 캐스팅을 쓰려거든 C++ 스타일의 캐스트를 선호하자. 발견하기도 쉽고 설계자가 어떤 의도를 가졌는지 더 명확하게 드러난다.
