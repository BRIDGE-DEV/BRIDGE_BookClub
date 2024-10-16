## Item 17: new로 생성한 객체를 스마터 포인터에 저장하는 코드는 별도의 한 문장으로 만들자

```cpp
int priority();

void processWidget(std::shared_ptr<Widget> pw, int priority);

processWidget(new widget, priority());
```

위 코드는 컴파일도 되지 않는다. 이는 `shared_ptr`의 생성자는 **explicit**으로 선언되어 있기 때문에, `new Widget`표현식에 의해 만들어진 포인터가 `shared_ptr`로 암시적으로 변환되는 것을 허용하지 않기 때문이다.

반면 다음 코드는 컴파일이 된다.

```cpp
processWidget(std::shared_ptr<Widget>(new Widget), priority());
```

이 처럼 활용하는 코드는 자원을 흘릴 가능성이 있는 코드이다. **컴파일러는 `processWidget` 호출 코드를 만들기 전에 우선 이 함수의 매개변수로 넘겨지는 인자를 평가하는 순서를 밟는다.** 여기서 `std::shared_ptr`는 두 부분으로 나누어져 있다.

- `new Widget` 표현식을 실행하는 부분
- `std::shared_ptr` 생성자를 호출하는 부분

실제 컴파일러는 다음과 같은 순서로 연산을 위한 코드를 생성한다.

- `priority()`를 호출
- `new Widget`을 실행
- `std::shared_ptr` 생성자를 호출

여기서 중요한 점은 각각의 연산이 실행되는 순서는 컴파일러마다 제각가이기 때문에 `new Widget`이 먼저 실행되고 그 결과로 생성된 포인터가 `std::shared_ptr` 생성자에 전달된다는 보장이 없다는 점이다. 만약 순서가 변경되고 `priority`부분에서 에외가 발생한다면 앞서 생성한 객체는 포인터가 유실되는 결과를 낳는다.

이런 문제를 피하는 방법은 `Widget`을 생성해서 스마터 포인터에 저장하는 별도의 문장 하나로 만들고, 그 스마터 포인터를 `processWidget`에 넘겨주는 것이다.

```cpp
std::shared_ptr<Widget> pw(new Widget);
processWidget(pw, priority());
```

이렇게 하면 컴파일러는 두 번째 문장을 만나기 전에 첫 번째 문장을 먼저 실행하고, 그 결과로 생성된 포인터가 `std::shared_ptr` 생성자에 전달된다는 보장이 있다.

### 정리

- new로 생성한 객체를 스마터 포인터로 넣는 코드는 별도의 한 문장으로 만들자. 이것이 안 되어 있으면 예외가 발생될 때 디버깅하기 힘든 자원 누출이 초래될 수 있다.
