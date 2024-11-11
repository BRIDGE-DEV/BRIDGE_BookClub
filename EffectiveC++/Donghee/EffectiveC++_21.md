# 챕터4: 설계 및 선언

## 항목 21: 함수에서 객체를 반환해야 할 경우에 참조자를 반환하려고 들지 말자

모든 코드는 오직 ‘참조에 의한 전달’만으로 이루어지지 않으면 안된다고 생각하는 경우가 있다. 참조자는 그냥 존재하는 객체에 붙는 다른 이름에 불가하다. 어떤 함수가 참조자를 반환하도록 만들어졌다면, 그 참조자는 반드시 이미 존재하는 객체의 참조자여야 한다.

아래 유리수를 나타내는 Rational 클래스의 연산자 * 예제를 보자.

```cpp
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
	Rational result(lhs.n * rhs.n, lhs.d * rhs.d);
	return result;
}
```

이 코드는 결국 생성자가 호출이 된다. result는 다른 객체처럼 생성되고, 지역 객체이기 때문에 함수가 끝날 때 소멸된다. 결국 operator*는 온전한 Rational 객체에 대한 참조자를 반환하지 않는다. 이미 쓸모없는 값을 가리키는 메모리를 반환할 뿐이라는 것이다.

그럼 객체를 힙에 만들고 그것을 참조자로 반환하는 방법은 어떨까?

```cpp
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
	Rational *result = new Rational(lhs.n * rhs.n, lhs.d * rhs.d);
	return *result;
}
```

여전히 생성자는 한 번 호출된다. 그보다 큰 문제는 여기서 new로 만든 객체는 누가 delete로 해제시켜주냐이다. 이를 이용한 코드를 보자.

```cpp
Rational w, x, y, z;
w = x * y * z;
```

여기서는 한 문장에서 operator* 호출이 두 번 일어나고 있기 때문에 new에 짝을 맞추어 delete를 호출하는 작업도 두 번이 필요하다. 하지만 사용자 쪽에서는 숨겨진 포인터에 대해 접근할 방법이 없기 때문에, 해제할 방법이 존재하지 않는다.

새로운 객체를 반환해야 하는 함수를 작성하는 것에는 올바른 방법이 있다. ‘새로운 객체를 반환하게 만드는 것’이다.

```cpp
inline const Rational operator*(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
}
```

이 코드에도 반환 값을 생성하고 소멸시키는 비용이 들어있다. 하지만 컴파일러에서 최적화가 일어나는 경우가 대부분이다. 몇몇 조건하에서는 이 최적화 매커니즘에 의해 operator*의 반환 값에 대한 생성과 소멸 동작이 안전하게 제거될 수 있다. 이것이 Return Value Optimization, RVO라고 한다.

https://sigcpp.github.io/2020/06/08/return-value-optimization

RVO는 위의 예제처럼 익명 객체를 반환하는 경우에 발생하고, RVO의 또다른 일종인 NRVO(Named Return Value Optimization)은 이름이 있는 객체를 반환하는 경우에 최적화가 적용된다. 이는 분기에 따라 반환되는 객체가 달라질 때, 또는 반환 타입이 객체 타입과 달라 암시적 변환이 필요할 때는 적용되지 않음에 주의하자.

최대한 저비용으로 만들려면 어떻게 해야 하는지 파악하는 일은 컴파일러 제작사에게 맡기자.

> 지역 스택 객체에 대한 포인터나 참조자를 반환하는 것, 혹은 힙에 할당된 객체에 대한 참조자를 반환하는 것, 지역 정적 객체에 대한 포인터나 참조자를 반환하는 것은 객체가 두 개 이상 필요해질 가능성이 있다면 절대로 하지 말자.