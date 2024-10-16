## Item 15: 자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자

자원 관리 클래스에 대해서 알아봤지만 실제로 현장에서 사용되는 API나 코드들은 자원을 직접 참조하기도 한다. [Item13](https://github.com/fkdl0048/BookReview/issues/295)에서 다룬 팩토리 함수의 경우를 다시 한번 살펴보자.

```cpp
std::shared_ptr<Investment> pInv(createInvestment());
```

이때 어떤 함수가 `Investment` 객체을 사용한다면 다음과 같이 사용할 수 있다.

```cpp
int daysHeld(const Investment *pInvestment);

int days = daysHeld(pInv); // 오류!
```

이 코드는 컴파일 자체가 안되는 코드로 `daysHeld`함수는 `Investment*` 타입의 실제 포인터를 원하는데, `pInv`은 `std::shared_ptr<Investment>` 타입이기 때문이다.

따라서 RAII 클래스의 객체를 그 객체가 감싸고 있는 실제 자원으로 변환할 방법이 필요해진다. 이런 목적에 일반적으로 사용하는 방법에는 두 가지가 있는데, 하나는 **명시적 변환(explicit conversion)**이고 다른 하나는 **암시적 변환(implicit conversion)**이다.

스마터 포인터의 경우 명시적 변환을 수행하는 get이라는 멤버 함수를 제공한다. 이 함수를 사용하면 각 타입으로 만든 스마터 포인터 객체에 들어 있는 실제 포인터를 얻어낼 수 있다.

```cpp
int days = daysHeld(pInv.get());
```

*[헷갈릴 수 있는 .의 접근과 ->의 접근](https://github.com/fkdl0048/CodeReview/issues/70)*

스마터 포인터도 역참조 연산자(operator->, operator*)도 오버로딩하고 있다. 따라서 자신이 관리하는 실제 포인터에 대한 암시적 변환도 쉽게 할 수 있다.

```cpp
class Investment {              // 최상위 클래스
public:
    bool isTaxFree() const;
    ...
};

Investment* createInvestment(); // 팩토리 함수

std::tr1::shared_ptr<Investment> pi1(createInvestment());

bool taxable1 = !(pi1->isTaxFree()); // -> 연산자 사용

std::auto_ptr<Investment> pi2(createInvestment());

bool taxable2 = !(*pi2).isTaxFree(); // * 연산자 사용
```

RAII 객체 안에 들어 있는 실제 자원을 얻어낼 필요가 종종 생기기 때문에 RAII 클래스 설계자 중에는 암시적 변환 함수를 제공하여 자원 접근을 매끄럽게 할 수 있도록 만들기도 한다.

RAII 클래스르 실제 자원으로 바꾸는 방법으로서 명시적 변환을 제공할 것인지(get 멤버 함수) 아니면 암시적 변환을 허용할 것인지에 대한 결정은 그 RAII 클래스만의 특정한 용도와 사용 환경에 따라 달라진다.

암시적 형변환은 말 그대로 암시적이기 때문에 가능하다면 명시적 형변환을 사용하는 것이 좋다. (but 암시적 형변환을 사용하는 것이 더 편리할 때도 있다. 이건 항상 트레이드 오프를 고려해야 한다.)

### RAII가 위반하는 캡슐화

RAII 클래스에서 직접적으로 자원 접근 함수를 열어 주는 설계가 캡슐화를 위반하는 것은 아닐까? 라는 생각이 들 수 있지만 RAII의 목적은 데이터 은닉이 목적이 아니라는 점을 명심하자.

물론 shared_ptr의 경우 엄격한 캡슐화와 느슨한 캡슐화를 동시에 지원한다. 참조 카운팅 메커니즘에 필요한 장치들은 모두 캡슐화하고 있지만, 그와 동시에 자신이 관리하는 포인터를 쉽게 접근할 수 있는 통로는 여전히 제공하고 있다.

### 정리

- 실제 자원을 직접 접근해야 하는 기존 API들도 많기 때문에, RAII 클래스를 만들 때는 그 클래스가 관리하는 자원을 얻을 수 있는 방법을 열어 주어야 한다.
- 자원 접근은 명시적 변환 혹은 암시적 변환을 통해 가능하다. 안정성만 따지면 명시적 변환이 대체적으로 더 낫지만, 고객 편의성을 보면 암시적 변환이 괜찮다.
  - but 명시적 변환을 사용하는 것이 더 낫다. explicit 키워드를 사용하면 암시적 변환을 막을 수 있다.

확실히 과거의 내용이 많긴 하지만, 당장 more, 모던을 공부하기 보다 왜 그렇게 발전했는지 이해하니 좀 더 이해가 잘 되고 지식이 늘어나는 느낌이다.
