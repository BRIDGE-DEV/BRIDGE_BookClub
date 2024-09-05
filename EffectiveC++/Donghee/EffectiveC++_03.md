## 항목3: 낌새만 보이면 const를 들이대 보자!

const는 어떤 값이 불변이어야 한다는 제작자의 의도를 컴파일러 및 다른 프로그래머와 나눌 수 있는 수단이다.

포인터에 대한 상수는 기본적으로는 포인터 자체를 상수로, 혹은 포인터가 가리키는 데이터를 상수로 지정할 수 있는데, 둘 다 지정할 수도 있고 아무것도 지정하지 않을 수도 있다.

```cpp
char *p = "Hello"; // 비상수 포인터, 비상수 데이터
const char *p = "Hello"; // 비상수 포인터, 상수 데이터
char * const p = "Hello"; // 상수 포인터, 비상수 데이터
const char * const p = "Hello"; // 상수 포인터, 상수 데이터
```

const 키워드가 *표의 왼쪽에 있으면 **포인터가 가리키는 대상**이 상수, const가 *표의 오른쪽에 있는 경우엔 **포인터 자체**가 상수다. 포인터가 가리키는 대상을 상수로 만들 때엔 타입 앞에 const를 붙이기도 하고, 뒤에 붙이기도 한다. 스타일의 차이이다.

```cpp
// 둘의 의미는 같다.
void f1(const Widget *pw);
void f2(Widget const *pw);
```

STL 반복자는 포인터를 본뜬 것이기 때문에, 기본적인 동작 원리가 T* 포인터와 흡사하다. 어떤 반복자를 const로 선언하는 것은 **포인터 자체를 상수로 선언하는 것**(T* const 포인터)과 같다. 이 경우에 반복자가 가리키는 대상의 값 변경하는 것은 가능하지만, 반복자의 대상을 변경하는 것은 불가능하다. 만약 상수 객체를 가리키는 반복자가 필요하다면 const_iterator를 쓰자.

가장 강력한 const의 용도는 함수 선언에 쓰는 경우다. const는 함수 반환 값, 각각의 매개변수, 멤버 함수 앞에 붙을 수 있다. 함수 반환 값을 상수로 정해주면, 안정성을 포기하지 않고도 사용자측의 에러 돌발 상황을 줄이는 효과를 자주 볼 수 있다. 눈 딱 감고 여섯 글자만 눌러보자.

### 상수 멤버 함수

멤버 함수에 붙는 const 키워드의 역할은 **”해당 멤버 함수가 상수 객체에 대해 호출될 함수이다”**라는 사실을 알려주는 것이다. 이런 함수가 왜 중요할까?

첫째는 클래스의 인터페이스를 이해하기 좋게 하기 위해서다. 그 클래스로 만들어진 객체를 변경할 수 있는 함수는 무엇이고, 변경할 수 없는 함수는 무엇인지 사용자 쪽에서 알기 쉽게 한다.

둘째는 이 키워드를 통해 상수 객체를 사용할 수 있게 하자는 의미도 있다. C++ 프로그램의 퍼포먼스를 높이는 핵심 기법 중 하나가 객체 전달을 **상수 객체에 대한 참조자**로 진행하는 것이기 때문이다. 이 기법이 제대로 적용되려면 상수 상태로 전달된 객체를 조작할 수 있는 const 멤버 함수가 준비되어 있어야 한다.

또한 const 키워드가 있고 없고의 차이만 있는 멤버 함수들은 오버로딩이 가능하다. 실제 프로그램에서 상수 객체가 생기는 경우는 **상수 객체에 대한 포인터** 혹은 **상수 객체에 대한 참조자**로 객체가 전달될 때이다.

어떤 멤버 함수가 상수 멤버라는 것이 대체 어떤 의미일까? 여기에는 **비트수준 상수성**, **논리적 상수성**이라는 개념이 존재한다.

**비트 수준 상수성**은 어떤 멤버 함수가 그 객체의 어떤 데이터 멤버도 건드리지 않아야 그 멤버 함수가 **‘const’**임을 인정하는 개념이다. 즉, 그 객체를 구성하는 비트들 중 어떤 것도 바꾸면 안 된다. 사실 C++에서 정의하고 있는 상수성이 비트수준 상수성이다. 비트수준 상수성을 지키는 다음 예제를 살펴보자.

```cpp
class CTextBlock{
public:
	...
	char& operator[](std::size_t position) const { return pText[position]; }
	
private:
	char *pText;
};

const CTextBlock cctb("Hello");
char *pc = &cctb[0]; // 내부 데이터의 포인터를 얻는다.
*pc = 'J'; // 이제 cctb는 "Jello"라는 값을 갖는다.
```

분명 비트수준 상수성을 지키는 코드이지만, 상수 멤버 함수를 호출했더니 상수 객체의 값이 바뀌어버린 상황이다. 논리적 상수성은 이런 상황을 보완하는 개념이다. 상수 멤버 함수라고 해서 객체의 한 비트라도 수정할 수 없는 것이 아니라, 몇 비트 정도는 바꿀 수 있되, 그것을 사용자측에서 알아채지 못하게만 하면 상수 멤버 자격이 있다는 것이다. 다음 예제를 보자.

```cpp
class CTextBlock{
public:
	...
	std::size_t length() const;
	
private:
	char *pText;
	std::size_t textlength;
	bool lengthIsValid;
};

std::size_t CTextBlock::length() const
{
	if (!lengthIsValid) {
		textLength = std::strlen(pText); // 상수 멤버 함수 안에서는 대입 불가
		lengthIsValid = true; // 상수 멤버 함수 안에서는 대입 불가
	}
	
	return textLength;
}
```

다음은 논리적 상수성을 지키지만, C++의 비트수준 상수성을 지키지는 못한다. textLength와 lengthIsValid가 비트수준에서 이미 변하기 때문이다. 하지만 mutable 키워드를 사용하면 이를 해결할 수 있다. mutable는 비정적 데이터 멤버를 비트수준 상수성의 족쇄에서 풀어 주는 키워드이다.

```cpp
class CTextBlock{
public:
	...
	std::size_t length() const;
	
private:
	char *pText;
	mutable std::size_t textlength;
	mutable bool lengthIsValid;
};

std::size_t CTextBlock::length() const
{
	if (!lengthIsValid) {
		textLength = std::strlen(pText); // mutable 멤버들은 수정 가능
		lengthIsValid = true; // mutable 멤버들은 수정 가능
	}
	
	return textLength;
}
```

다음과 같이 수정하면 C++의 상수성을 벗어나지 않으면서, 논리적 상수성을 만족하는 상수 멤버 함수를 만들 수 있다.

### 상수 멤버 및 비상수 멤버 함수에서 코드 중복 현상을 피하는 방법

mutable은 위의 문제를 해결하는 데엔 괜찮은 방법이지만, 이것으로 const에 관한 골칫거리를 모두 해결하진 못한다. 앞서 있었던 TextBlock 클래스의 operator []를 상수/비상수 버전으로 나눈다고 가정해보자.

```cpp
class TextBlock{
public:
	...
	const char& operator[](std::size_t position) const 
	{
		...
		return pText[position];
	}
	char& operator[](std::size_t position)
	{
		...
		return pText[position];
	}
	
private:
	char *pText;
};
```

대강 보아도 코드 중복이 심하다. 이 코드를 볼 때, operator[]의 양 버전 중 하나만 제대로 만들고 다른 버전은 이것을 호출하는 식으로 만들고 싶지 않은가? const 껍데기를 캐스팅으로 날려버리는 식으로 해결해보자.

```cpp
class TextBlock{
public:
	...
	const char& operator[](std::size_t position) const 
	{
		...
		return pText[position];
	}
	char& operator[](std::size_t position)
	{
		...
		return const_cast<char&>(
			static_cast<const TextBlock&>(*this)[position]
		);
	}
	
private:
	char *pText;
};
```

보면 캐스팅이 한 번이 아니라 두 번이 호출된다. 곰곰히 생각해보면, 비상수 operator[] 속에서 그냥 operator[]를 사용하면 자신이 무한 재귀 호출될 것이다. 따라서 **”상수 operator[]를 호출하고 싶다.”**를 표현해주어야 하는데, 이것을 표현하는 방법이 *this의 타입 캐스팅인 것이다. 정리하면, 두 캐스팅 중 첫 번째 것은 *this에 const를 붙이는 것이고, 두 번째 것은 상수 operator[]의 반환 값에서 const를 떼어내는 캐스팅이다.

const를 붙이는 캐스팅은 안전한 타입 변환을 강제로 진행하는 것뿐이기 때문에 static_cast만 써도 맞는다. 반면 const를 제거하는 캐스팅은 const_cast밖에 없으므로 선택의 여지가 없다.

그렇다면 상수 버전이 비상수 버전을 호출하는 방법은 안될까? 이는 우리가 원하는 바가 아니다. 어쩌다가 상수 멤버에서 비상수 멤버를 호출하게 되면, 그 객체는 변경될 위험에 빠질 수 있다. 또한 이 방법은 const_cast를 이용해 *this에 붙은 const를 떼어내어야 하는데, 이게 온갖 재앙의 씨앗이다.

> const는 어떤 유효범위에 있는 객체에도 붙을 수 있으며, 함수 매개변수 및 반환 타입에도 붙을 수 있으며, 멤버 함수에도 붙을 수 있다.
>컴파일러 쪽에서 보면 비트수준 상수성을 지켜야 하지만, 우리는 논리적 상수성을 사용해 프로그래밍해야 한다.
>상수/비상수 멤버 함수가 똑같게 구현되어 있을 때는 코드 중복을 피해야 하자. 이때는 비상수 버전이 상수 버전을 호출하도록 하자.