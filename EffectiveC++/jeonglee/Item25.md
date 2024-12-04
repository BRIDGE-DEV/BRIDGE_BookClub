## Item 25: 예외를 던지지 않는 swap 함수에 대한 지원도 생각하자

이번 항목의 주제는 자주 사용하게 되는 swap함수에 대해서 어떻게 쓸만한 swap함수를 만들 수 있는지 알아본다.

```cpp
template<typename T>
void swap(T& a, T& b)
{
    T temp(a);
    a = b;
    b = temp;
}
```

실제로 표준 라이브러리에서 제공하는 함수와 똑같이 동작한다. *C++11 이상은 move를 사용한다. 현재 Effective C++의 버전이 낮기에 여기에 맞춰서 진행*

위 코드를 보면 한번 호출 시 복사가 세 번 발생한다. a에서 temp로 b에서 a로, temp에서 b로 진행된다. 이 때문에 복사를 하면 손해가 큰 경우가 다른 타입의 실제 데이터를 가리키는 포인터이다.

만약 `pimpl`을 사용하고 있다면, `pimpl`이 가리키는 데이터를 바꾸는 것이 아니라 포인터 자체를 바꾸는 것이 더 효율적이다. 이 때문에 `swap`함수를 사용할 때 `pimpl`을 사용하는 경우에는 `swap`함수를 재정의해야 한다.

```cpp
class Widget
{
public:
    ...
    void swap(Widget& other)
    {
        using std::swap;
        swap(pimpl, other.pimpl);
    }
    ...
};
```

```cpp
template<>
void swap<Widget>(Widget& a, Widget& b)
{
    a.swap(b);
}
```

이 경우 올바른 코드처럼 보이지만, 문제는 `Widget`이나 `WidgetImpl`이 클래스가 아닌 클래스 템플릿으로 만들어져 있다면 저장된 데이터 타입을 매개 변수로 바꿀 수 있게 되면서 문제가 발생한다.

함수 템플릿을 부분적으로 특수화하여 사용하고 싶다면 오버로드 버전을 하나 추가하면 된다. 이 경우에도 std 내의 템플릿에 대한 완전 특수화는 가능하지만, std에 새로운 템플릿을 추가하는 것은 안된다.

swap을 호출해서 효율 좋은 테플릿 전용 버전을 쓰고 싶다면 멤버 swap을 호출하는 비멤버 swap을 선언해 놓되, 이 비멤버 함수를 std::swap의 특수화 버전이나 오버로딩 버전으로 선언하지만 않으면 된다.

```cpp
namespace WidgetStuff
{
    template<typename T>
    class Widget { ... };

    template<typename T> // 비멤버
    void swap(Widget<T>& a, Widget<T>& b)
    {
        a.swap(b);
    }
}
```

만약 swap함수를 사용할 때 T 전용 버전이 있으면 그것을 호출하고 없다면 std의 일반형 버전이 호출되도록 코드를 작성해야 한다면 아래와 같이 사용한다.

```cpp
template<typename T>
void doSomething(T& w1, T& w2)
{
    using std::swap;
    swap(w1, w2);
}
```

컴파일러는 위 swap호출문을 만났을 때 현재 상황에 딱 맞는 swap을 찾는다. 이는 C++ 이름 탐색 규칙(인자 기반 탐색, 쾨니그 탐색)에 따라 우선 전역 유효범위 혹은 타입 T와 동일한 네임스페이스 안에 T 전용 swap 규칙을 찾는다.

### 정리

- 표준으로 제공하는 swap이 작성한 클래스 및 클래스 템플릿에 대해 납득할 만한 효율을 보인다면 그대로 사용하자.
- 만약 swap의 효율이 기대한 만큼 충분하지 않다면 새로 정의한 swap을 public 멤버 함수로 두고 같은 네임스페이스에 비멤버 swap을 만들고 public 멤버 함수를 호출하게 하자. 새로운 클래스를 만들고 있다면 해당 클래스에 대한 swap특수화 버전을 준비한다.
- 사용자 입장에서 swap을 호출할 때, swap을 호출하는 함수가 using선언을 포함하도록 한다.
