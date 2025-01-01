# Item38. "has-a(...는...를 가짐)" 혹은 "is-implemented-in-terms-of(...는...를 써서 구현됨)"를 모형화 할 때는 객체 합
합성(Composition)이란, 어떤 타입의 객체들이 그와 다른 타입의 객체들을 포함하고 있을 경우에 성립하는 그 타입들 사이의 관계를 일 컫는다. 포함된 객체를 모아서 다른 이들을 합성하는 것이다.
```cpp
class Address { ... };
class PhoneNumber { ... };
class Person {
public:
	...
private:
	std::string name;
	Address address;
	PhoneNumber voiceNumber;
	PhoneNumber faxNumber;
};
```
Person 객체가 string, Address, PhoneNumber 객체로 이루어져 있다.

객체 합성의 의미 두가지
1. has-a (...는 ...를 가짐)
2. is-implemented-in-terms-of (...는 ...를 써서 구현됨)

두 가지 의미를 갖는 이유는 소프트웨어 개발에서 대하는 영역(domain)이 두 가지이기 때문이다.

소프트웨어 영역
1. 응용영역: 객체 중에서 우리 일상생활에서 볼 수 있는 사물을 본 뜬 것들 (예시: 사람, 이동수단, 비디오 프레임 등)
2. 구현영역: 순수하게 시스템 구현만을 위한 인공물 (예시: 버퍼, 뮤텍스, 탐색트리 등)

여기에서 객체 합성이 응용 영역에서 일어나면 has-a 관계이다. 구현 영역에서 일어나면 is-implemented-in-terms-of 관계이다.

위에 있던 Person 클래스가 나타내는 관계는 has-a 관계이다.

```cpp
template<class T>
class Set{
public:
	bool member(const T& item) const;

	void insert(const T& item);
	void remove(const T& item);

	std::size_t size() const;

private:
	std::list<T> rep;  //Set 데이터의 내부 표현부
};
```
이들 두 클래스 사이의 관계가 is-a가 될 리 없으므로, public 상속은 지금의 관계를 모형화하는 데 맞지 않다. Set 객체를 list 객체를 사용하여 구현(is-implemented-in-terms-of)되는 형태의 설계가 가능하다.


+ 객체 합성(composition)의 의미는 public 상속이 가진 의미와 완전히 다르다.
+ 응용 영역에서 객체 합성의 의미는 has-a(...는 ...를 가짐)이다. 구현 영역에서는 is-implemented-in-terms-of(...는 ...를 써서 구현됨)의 의미를 갖는다.