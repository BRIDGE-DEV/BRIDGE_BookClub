# Item21. 함수에서 객체를 반환해야 할 경우에 참조자를 반환하려고 들지 말자
유리수를 나타내는 클래스가 있다고 가정하자. 이 클래스에는 두 유리수를 곱하는 멤버 함수가 선언되어 있다.
```cpp
class Rational {
public:
	Rational(int number = 0, int denominator = 1);
	
private:
	int n, d;
friend
	const Rational operator*(const Rational& lhs, const Rational& rhs);
};
```
Rational 객체의 생성과 소멸에 들어가는 비용이 발생한다. 정말 여기에 비용을 들여야 할까?

값이 아닌 참조자를 반환할 수 있다면 비용 부담을 없앨 수 있을 것이다. 하지만 참조자는 그냥 이름이다. 존재하는 객체에 붙는 다른 이름이다. 이는 함수가 반환하는 참조자는 반드시 이미 존재하는 Rational 객체의 참조자여야 한다는 뜻이다. 

함수 수준에서 새로운 객체를 만드는 방법은 딱 두가지이다.
1. 스택에서 만들기
2. 힙에서 만들기

스택에 객체를 만들려면 지역 변수를 정의하면 된다.
```cpp
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
	Rational result(lhs.n * rhs.n, lhs.d * rhs.d);
	return result;
}
```
위의 방법은 연산자 함수는 result에 대한 참조자를 반환하는데, result는 지역 객체이다. 다시 말해 함수가 끝날 때 덩달아 소멸되는 객체다. 결국 온전한 Rational 객체에 대한 참조자를 반환하지 않는다.

이번에는 함수가 반환할 객체를 힙에 생성해 두었다가 참조자를 반환하는 방법으로 new 연산자를 통해 힙기반 객체를 불러온다.
```cpp
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
	Rational *result = new Rational(lhs.n * rhs.n, lhs.d * rhs.d);
	return *result;
}
```
여기서는 생성자가 한 번 호출이 되고 다른 문제가 또 있는데 바로 delete로 언제 처리를 해주어야 할지 애매해져버리는 문제이다. 아래와 같은 코드에서 메모리 누수문제가 발생한다.
```cpp
Rational w, x, y, z;
w = x * y * z;  //메모리 누수 발생
```

이번에는 생성자 호출도 일어나지 않도록 Rational 객체를 정적 객체로 함수 안에 정의해 놓고 이것의 참조자를 반환하는 식으로 operator* 를 만든다.
```cpp
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
	static Rational result;

	resutl = ...;

	return result;
}
```
정적 객체를 사용하는 설계는 스레드 안정성 문제가 얽혀 있다. 또한 이보다 더 확실한 약점이 존재하는데 아래의 멀쩡한 코드를 보면 알 수 있다.
```cpp
bool operator==(const Rational& lhs, const Rational& rhs);

Rational a, b, c, d;

if ((a * b) == (c * d)) {
	...;
}
else {
	...;
}
```
여기서 문제는 *(a * b) == (c * d)* 이부분이 항상 true 값을 낸다는 것이 문제이다. 이유는 같은 정적 Rational에 대한 비교를 수행하기 때문이다.

결국 operator* 등의 함수에서 참조자를 반환하는 것만큼 시간낭비는 없다. 새로운 객체를 반환해야 하는 함수를 작성하는 방법에는 정도가 있다. 바로 '새로운 객체를 반환하게 만드는 것'이다.
```cpp
inline const Rational operator*(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
}
```
위 코드 역시 반환 값을 생성하고 소멸시키는 비용이 든다. 그러나 이것 저것 따져서 보면 결국 여기에 들어가는 비용은 올바른 동작에 지불되는 작은 비용이다. 컴파일러에 따라서도 몇몇 조건하에 최적화 매커니즘에 의해 operator* 의 반환 값에 대한 생성과 소멸 동작이 안전하게 제거 될 수 있다.


+ 지역 스택 객체에 대한 포인터나 참조자를 반환하는 일, 혹은 힙에 할당된 객체에 대한 참조자를 반환하는 일, 또는 지역 정적 객체에 대한 포인터나 참조자를 반환하는 일은 그런 객체가 두 개 이상 필요해질 가능성이 있다면 절대로 하지 마세요