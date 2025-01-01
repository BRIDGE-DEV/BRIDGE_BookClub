# 챕터6: 상속, 그리고 객체 지향 설계

## 항목 36: 상속받은 비가상 함수를 파생 클래스에서 재정의하는 것은 절대 금물!

다음처럼 `B`라는 클래스가 있고, `mf`라는 이름의 public 멤버 함수가 있다고 가정하자.

```cpp
class B {
public:
	void mf();
	...
};
```

여기서 `D`라는 `B`를 public 상속한 클래스가 `mf`함수를 또 정의한다고 해보자.

```cpp
class D: public B {
public:
	void mf(); // B:mf를 가림
	...
};
```

위 같은 상황에서는 `D`의 `mf`가 `B`의 `mf`를 가리게 된다. 하지만 비가상 함수이기 때문에, 정적 바인딩으로 묶인다. 즉, 아래와 같은 상황이 벌어진다.

```cpp
D x;
B* pB = &x;
D* pD = &x;
pB->mf(); // B::mf를 호출
pD->mf(); // D::mf를 호출
```

`pB`는 `B`에 대한 포인터 타입이기 때문에, `pB`를 통해 호출되는 비가상 함수는 항상 `B`클래스에 정의되어 있을 것이라고 생각한다. 만약 `mf`가 가상 함수였다면, 동적 바인딩으로 묶였을 것이다. 그렇다면 `mf`가 `pB`에서 호출되든, `pD`에서 호출되든 `D::mf`가 호출되었을 것이다. 참조자 또한 포인터를 기반으로 만들어졌기 때문에 동일한 문제가 발생한다.

물론 public 상속의 의미는 “is-a”이다. 기본 클래스의 비가상 함수는 파생 클래스에서 인터페이스와 구현을 모두 물려받아야 한다. 예제처럼 `B`의 비가상 함수인 `mf`를 재정의하게 된다면, ‘모든 D는 B의 일종’이라는 명제 자체가 거짓이 된다. 만약 모든 `D`가 `B`의 일종이고 정말 `mf`가 클래스 파생에 상관없는 `B`의 불변동작에 해당한다면, `D`에서는 `mf`를 재정의할 시도도 하지 말아야 한다.

이 항목의 내용은 다형성을 부여한 기본 클래스의 소멸자를 반드시 가상 함수로 만들어 두어야 하는 이유이기도 하다. 만약 기본 클래스에서 소멸자가 비가상 함수라면, 파생 클래스에서는 상속받은 비가상 함수, 즉 비가상 소멸자를 재정의할 것이 뻔하기 때문이다.

> 상속받은 비가상 함수를 재정의하는 일은 절대로 하지 말자.