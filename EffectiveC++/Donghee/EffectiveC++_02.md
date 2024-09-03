## 항목2: #define을 쓰려거든 const, enum, inline을 떠올리자

다음 줄과 비슷한 코드를 썼다고 가정해 보자.

```cpp
#define ASPECT_RATIO 1.653
```

컴파일러에겐 ASPECT_RATIO가 전혀 보이지 않는다. 소스 코드가 컴파일러에게 넘어가기 전에 선행 처리자가 이를 밀어버리고 숫자 상수로 바꾸어 버리기 때문이다. 때문에 컴파일 에러라도 나게 되면, ASPECT_RATIO 대신 1.653이 에러 메세지에 뜨는 등 혼란이 발생한다.

이 문제에 해결법은 매크로 대신 상수를 쓰는 것이다.

```cpp
const double AspectRatio = 1.653;
```

이는 언어 차원에서 지원하는 상수 탕비의 데이터이기 때문에, 컴파일러의 눈에 보인다. 또한 상수가 부동소수점 실수 타입일 경우에는 위의 코드가 #define을 썼을 때보다 컴파일 최종 코드 크기가 더 작게 나올 수 있다. 매크로를 쓰면 ASPECT_RATIO가 모두 1.653으로 바뀌며 1.653의 사본이 등장 횟수만큼 들어가지만, 상수 타입은 아무리 여러 번 쓰이더라도 사본은 한 개만 생기기 때문이다.

#define을 상수로 교체할 때는 두 가지 경우만 조심하자.

첫째는 상수 포인터를 정의하는 경우다.  포인터는 꼭 const로 선언해 주어야 하고, 포인터가 가리키는 대상까지 const로 선언하는 것이 보통이다.

```cpp
const char * const authorName = "Scott Meyers";
```

char* 기반의 문자열 상수를 정의한다면 위와 같이 const를 두 번 써야 한다.

두 번째 경우는 클래스 멤버로 상수를 정의하는 경우이다.

```cpp
class GamePlayer{
private:
	static const int NumTurns = 5;
	int scores[NumTurns];
	...	
};
```

위의 NumTurns는 **선언**된 것이다. **정의**가 아니다. C++에서는 정의가 마련되어 있어야 하는 게 보통이지만, 정적 멤버로 만들어지는 정수류 타입의 클래스 내부 상수는 예외다. 이들에 대해 주소를 취하지 않는 한, 정의 없이 선언만 해도 아무 문제가 없다. 단, 주소를 구하거나, 컴파일러의 문제로 정의를 제공해야 할 경우가 있다.

```cpp
const int GamePlayer::NumTurns;
```

클래스 상수의 정의는 헤더 파일이 아닌 구현 파일에 둔다.

정의에는 상수의 초기값이 있으면 안된다. 클래스 상수의 초기값은 해당 상수가 선언된 시점에서 바로 주어지기 때문이다. 즉, 선언되면서 바로 초기화된다는 것이다. 

그러나 클래스 내부 초기화를 허용하는 경우는 정수 타입의 상수에 대해서만 국한되어 있다. 이럴 때엔 초기값을 상수 **정의** 시점에 주자.

```cpp
class CostEstimate{
private:
	static const double FudgeFactor; // 헤더 파일에서의 선언
	...
};
const double CostEstimate::FudgeFactor = 1.35; // 구현 파일에서의 정의
```

예외가 있다면 클래스를 컴파일 하는 중에 해당 클래스의 클래스 상수가 필요할 때이다. 정수 타입의 정적 클래스 상수에 대한 클래스 내 초기화를 금지하는 구식 컴파일러라면, **나열자 둔갑술(enum hack)**이라는 기법을 생각할 수 있다. 이는 나열자(enumerator) 타입의 값은 int가 놓일 곳에도 쓰일 수 있다는 것을 활용한 것이다.

```cpp
class GamePlayer{
private:
	enum { NumTurns = 5 };
	int scores[NumTurns];
	...	
};
```

이는 동작 방식이 const보다는 #define에 가깝다. enum의 주소를 얻는 것은 불가능하고, 컴파일러가 enum에 대한 메모리 할당을 저지르지 않는다. 또한 많은 코드에서 이 기법이 쓰이고 있으므로 눈을 단련시켜 둬야하는 의미도 있다.

#define 지시자의 또 다른 오용 사례는 매크로 함수다. 다음 코드를 보자. 매크로 인자들 중 큰 것을 사용해 어떤 함수 f를 호출하는 매크로다.

```cpp
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))
```

이는 인자마다 괄호를 씌워줘야 하는데, 이 때문에 인자를 여러번 평가하게 된다.

```cpp
int a = 5, b = 0;
CALL_WITH_MAX(++a, b); // a 두 번 증가
CALL_WITH_MAX(++a, b+10); // a 한 번 증가
```

위의 코드를 보면, 저런 사소한 차이에도 예측하기 어려운 결과가 나온다는 것이다. 이를 대체하는 좋은 방법으로 **템플릿 인라인 함수**가 있다. 위의 매크로 함수를 변경해보자.

```cpp
template<typename T>
inline void callWithMax(const T& a, const T& b)
{
	f(a > b ? a : b);
}
```

이는 괄호도 필요 없고, 인자를 여러번 평가하는 경우도 없다. 또한 진짜 함수이기 때문에 유효범위와 접근 규칙을 그대로 따라간다.

> 단순한 상수를 쓸 때는, #define보다 const 객체 혹은 enum을 생각하자.
> 함수처럼 쓰이는 매크로를 만들 땐, #define 매크로보다 인라인 함수를 생각하자.