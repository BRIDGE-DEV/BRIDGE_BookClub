# 챕터4: 설계 및 선언

## 항목 24: 타입 변환이 모든 매개변수에 대해 적용되어야 한다면 비멤버 함수를 선언하자

우리가 Rational이라는 유리수를 나타내는 클래스를 제작한다고 해보자. 아래는 이에 대한 곱셈 연산자인 operator* 예제이다.

```cpp
class Rational {
public:
	...
	const Rational operator*(const Rational& rhs) const;
};
```

이러면 Rational 객체끼리의 계산은 잘 된다. 그렇다면 혼합형 수치 연산은 어떨까? 예를 들어 이런 식이다.

```cpp
Rational onehalf(1, 2);
Rational result = oneHalf * 2; // 정상
result = 2 * oneHalf; // 에러
```

oneHalf가 먼저 나오면 정상적으로 진행되고, 2가 먼저 나오면 에러가 난다. 이 문제의 원인은 위의 예제를 함수 형태로 바꾸어 써 보면 금방 이해 된다.

```cpp
Rational result = oneHalf.operator*(2);
result = 2.operator*(oneHalf);
```

첫 번째 줄에서 oneHalf 객체는 operator* 함수를 멤버로 갖고 있는 객체이므로 정상 호출이 된다. 하지만 두 번째 줄의 정수 2는 클래스 같은 것이 연관이 없기 때문에, operator* 멤버 함수도 있을 리가 없다. 컴파일러는 아래처럼 비멤버 버전의 operator*도 찾아본다.

```cpp
result = operator*(2, oneHalf);
```

그러나 비멤버 버전의 operator*가 없기 때문에 실패한다. 암시적 타입 변환이 일어나지도 않는다. 호출되는 멤버 함수를 갖고 있는 객체(this)에 해당하는 암시적 매개변수에는 암시적 변환이 먹히지 않는다.

결국 operator*를 비멤버 함수로 만들어서 컴파일러 쪽에서 모든 인자에 대해 암시적 타입 변환을 수행하도록 만든다.

```cpp
const Rational operator*(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

Rational oneFourth(1, 4);
Rational result;

result = oneFourth * 2;
result = 2 * oneFourth; // 정상 실행
```

여기서 operator* 함수는 Rational 클래스의 프렌드 함수로 두어도 될까? 아니다. operator*는 지금 완전히 Rational의 퍼블릭 인터페이스만을 써서 구현할 수 있기 때문이다.

물론 어떤 상황에서는 프렌드 관계를 꼭 맺을 필요도 있다. 그러나 ‘멤버 함수이면 안되니까’가 반드시 ‘프렌드 함수이어야 해’를 뜻하진 않는다.

> 어떤 함수에 들어가는 모든 매개변수에 대해 타입 변환을 해줄 필요가 있다면, 그 함수는 비멤버이어야 한다.