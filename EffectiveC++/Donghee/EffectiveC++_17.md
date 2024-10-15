# 챕터3: 자원 관리

## 항목 17: new로 생성한 객체를 스마트 포인터에 저장하는 코드는 별도의 한 문장으로 만들자

```cpp
int priority();
void processWidget(std::tr1::shared_ptr<Widget> pw, int priority);
```

위와 같이 처리 우선순위를 알려주는 함수와, Widget 객체에 대해 어떤 우선순위에 따라 처리를 적용하는 함수가 있다고 해보자. 이를 아래의 코드로 호출해보자.

```cpp
processWidget(new Widget, priority());
```

이 코드는 컴파일 에러가 난다! tr1::shared_ptr의 생성자는 explicit로 선언되어 있기 때문에, ‘new Widget’ 표현식에 의해 만들어진 포인터가 tr1::shared_ptr 타입의 객체로 바꾸는 암시적인 변환이 있을 리가 없기 때문이다. 반면 이 코드는 컴파일된다.

```cpp
processWidget(std::tr1::shared_ptr<Widget>(new Widget), priority());
```

processWidget 함수 호출이 이루어지기 전에 컴파일러는 세 가지 연산을 위한 코드를 만들어야 한다.

- priority 호출
- ‘new Widget’을 실행
- tr1::shared_ptr 생성자 호출

각각의 연산이 실행되는 순서는 컴파일러 제작사마다 다르다는 게 문제다. `new Widget` 표현식은 tr1::shared_ptr 생성자가 실행될 수 있기 전에 호출되어야 한다. 그러나 priority의 호출은 처음, 혹은 두 번째, 세 번째에 호출될 수도 있다. 그렇다면 순서가,

- ‘new Widget’을 실행
- priority 호출
- tr1::shared_ptr 생성자 호출

이런 식으로 될 수 있다. 하지만 priority 호출 부분에서 예외가 발생한다면, `new Widget`으로 만들어졌던 포인터가 유실될 수 있다. 자원이 생성되는 시점 → 자원이 자원 관리 객체로 넘어가는 시점 사이에 예외가 끼어들 수 있기 때문이다.

해결책은 Widget을 생성해서 스마트 포인터에 저장하는 코드를 별도의 문장 하나로 만들고, 그 스마트 포인터를 processWidget에 넘기는 것이다.

```cpp
std::tr1::shared_ptr<Widget> pw(new Widget);
processWidget(pw, priority());
```

위의 코드는 문장과 문장 사이에 있는 연산들이 컴파일러의 재조정을 받을 여지가 적다. 따라서 자원 누출 가능성이 없다.

> new로 생성한 객체를 스마트 포인터로 넣는 코드는 별도의 한 문장으로 만들자. 이것이 안 되어 있다면, 예외가 발생될 때 디버깅하기 힘든 자원 누출이 초래될 수 있다.