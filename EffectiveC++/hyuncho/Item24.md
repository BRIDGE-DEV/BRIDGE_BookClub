# Item24. 타입 변환이 모든 매개변수에 대해 적용되어야 한다면 비멤버 함수를 선언하자
```cpp
class Rational {
public:
	Rational(int numerator = 0, int denominator = 1);
	int numerator() const;
	int denominator() const;
}
```
위는 유리수를 나타내는 클래스로 덧셈이나 곱셈 등의 수치 연산을 기본으로 지원하려 한다. 그러나 어떤 식으로 지원할지 혼란스럽다. 멤버함수가 나을지, 비멤버 함수가 나을지 아니면 비멤버 프렌드 함수가 좋을지.

```cpp
class Rational {
public:
	...
	const Rational operator*(const Rational& rhs) const;
};
```
이렇게 설계해두면 유리수 곱셈을 아주 쉽게 할 수 있다.
```cpp
Rational oneEight(1, 8);
Rational oneHalf(1, 2);

Rational result = oneHalf * oneEighth;

result = result * oneEighth;
```
혼합형 수치 연산도 가능했으면 좋겠다고 생각된다. 즉 Rational 과 int 와 같은 것을 곱하고 싶다.
```cpp
result = oneHalf * 2;

result = 2 * oneHalf;    //에러 발생!
```
곱셈은 기본적으로 교환법칙이 성립해야 할 것 같지만 에러가 발생한다.
```cpp
result = oneHalf.operator*(2);    //좋은 경우

result = 2.operator*(oneHalf);    //에러 발생!
```
위와 같이 풀어서 써보면 왜 에러가 나는지 바로 이해가 가능하다. 정수 2에서는 클래스 관련된 것이 있지 않기 때문이다.

그렇다면 operator* 의 매개변수의 타입이 Rational 인데도 불구하고 정수 2를 대입하였을 때 잘 동작한 이유는 **암시적 타입 변환**이 일어났기 때문이다. 

즉 컴파일러가 함수 쪽에선 Rational 타입을 원하지만 int가 대입된 상황에서 Rational의 생성자가 int를 필요로 하며 이를 생성자에 대입시에 Rational로 둔갑한다는 사실을 알고 있어 암시적 타입 변환이 가능했던 것이다.
```cpp
const Rational temp(2);    //2로부터 임시 Rational 객체를 생성한다.

result = oneHalf * temp;   //oneHalf.operator*(temp); 와 같다.
```
물론 위와 같이 동작하는 것은 명시호출(explicit)로 선언되지 않은 생성자가 있기 때문이다. 만약 명시 호출 생성자였다면 위 두가지의 경우 모두 에러가 발생한다.

동작도 일관되게 유지하면서 혼합형 수치 연산도 제대로 지원하도록 하려면 결국 operator* 를 비멤버 함수로 만들어서, 컴파일러 쪽에서 모든 인자에 대해 암시적 타입 변환을 수행하도록 내버려 두는 것이다.
```cpp
class Rational {
	...
};

const Rational operator* (const Rational& lhs, const Rational& rhs)   //비멤버 함수
{
	return Rational(lhs.numerator() * rhs.numerator(), 
						lhs.denominator() * rhs.denominator());
}

Rational oneFourth(1, 4);
Rational result;

result = oneFourth * 2;    //가능
result = 2 * oneFourth;    //가능
```



+ 어떤 함수에 들어가는 모든 매개변수(this 포인터가 가리키는 객체도 포함해서)에 대해 타입 변환을 해 줄 필요가 있다면, 그 함수는 비멤버이어야 한다.