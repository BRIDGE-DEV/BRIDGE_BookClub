# Item31. 파일 사이의 컴파일 의존성을 최대로 줄이자
클래스에 있는 구현부를 잠깐 수정하고 다시 빌드를 할 경우 다른 것들까지 몽땅 컴파일 되고 링크 되어버리는 일이 발생한다. 

위와 같은 문제의 핵심은 C++이 인터페이스와 구현을 깔끔하게 분리하는 일에 별로 일가견이 없다는 것이다.

C++의 클래스 정의는 클래스 인터페이스만 지정하는 것이 아니라 구현 세부사항까지 상당히 많이 지정하고 있다.
```cpp
class Person {
public:
	Person(const std::string& name, const Date& birthday, const Addresss& addr);
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
	..
private:
	std::string theName;  //구현 세부사항
	Date theBirthDate;    //구현 세부사항
	Address theAddress;   //구현 세부사항
}
```
위의 코드만 갖고 컴파일이 가능할까? 그렇지 않다. Person의 구현 세부사항에 속하는 것들, 다시 말해 string, Date, Address가 어떻게 정의됐는지를 모르면 컴파일이 불가능 하다. 결국 이들이 정의된 정보를 가져와야 하고, 이때 쓰는 것이 \#include 지시자 이다. 따라서 대개 아래와 비슷한 코드를 발견하게 된다.
```cpp
#include <string>
#include "date.h"
#include "address.h"
```
이것들이 골치덩이가 되는데 \#include 문은 Person을 정의한 파일과 위의 헤더 파일 사이에 컴파일 의존성이란 것을 엮어버린다.

이렇게 꼬리에 꼬리는 무는 방식으로 연결되어 있다보니 하나를 수정하면 몽땅 컴파일이 되어버리는 경우가 발생하게 된다.

그렇다면 Person 클래스를 정의할 때 구현 세부사항을 따로 떼어서 지정하는 식으로 하면 안되는가?
```cpp
namespace std {
	class string;  //전방선언(뒤에서 보겠지만 틀린 방식임.)
}

class Date; //전방선언
class Address;  //전방선언

class Person{
public:
	Person(const std::string& name, const Date& birthday, const Address& addr);
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
};
```
위와 같이 된다면 Person 클래스의 인터페이스가 바뀌었을 때만 컴파일을 다시 하면 되니 좋겠다고 생각되지만 이는 희망사항일 뿐이다.

두 가지의 문제점이 존재한다.

첫 번째로 string은 사실 클래스가 아니라 typedef로 정의한 타입 동의어이다. (basic_string\<char> 를 typedef한 것이다.) 그래서 제대로 전방선언을 하기 위해서는 템플릿을 추가로 끌고 들어와야 하기 때문에 더 복잡해진다.

표준 라이브러리 헤더는 어지간한 경우만 아니면 컴파일 시 병목 요인이 되지 않는다. 특히 빌드 환경이 컴파일 헤더를 쓸 수 있는 환경이면 더 그렇다.
>[!note]
>왜 표준 라이브러리 헤더만 컴파일 시 병목요인이 잘 발생하지 않는가?
>

두 번째로 컴파일러가 컴파일 도중에 객체들의 크기를 전부 알아야 한다는 데 있다. 
```cpp
int main()
{
	int x;   //int 하나를 정의

	Person p { params };  //Person 하나를 정의
	...
}
```
컴파일러가 Person 하나를 담을 공간을 할당해야 한다. 얼만큼의 크기인지 알려면 Person 클래스가 정의된 정보를 보는 수 밖에 없다. 

자바의 경우는 객체가 정의될 때 컴파일러가 그 객체의 포인터를 담을 공간만 할당한다. 다시 말하면 아래와 같이 쓰인 것으로 판단한다.
```cpp
int main()
{
	int x;

	Person *p;
}
```

위와 같은 방법을 이용해 한쪽은 인터페이스만 제공하고 한쪽은 인터페이스의 구현을 맡도록 만들어 보겠다. 구현을 맡은 클래스의 이름이 PersonImpl라고 하면 Person 클래스는 다음과 같이 정의할 수 있다.
```cpp
#include <string>
#include <memory>

class PersonImpl;

class Date;
class Address;

class Person {
public:
	Person(const std::string& name, const Date& birthday, const Address& addr);
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
	...
private:
	std::tr1::shared_ptr<PersonImpl> pImpl;
};
```
위의 코드를 보면 주 클래스에 들어 있는 데이터 멤버라고는 구현 클래스에 대한 포인터 뿐이다. 이런 설계는 거의 패턴으로 굳어져 있을 정도여서 'pimpl 관용구' 라는 이름도 있다. 이때 포인터의 이름은 대개 pImpl라고 붙이는 게 일반적이다.

이렇게 설계하면 자질구레한 세부사항과 완전히 갈라선다. Person 클래스에 대한 구현 클래스 부분은 생각만 있으면 마음대로 고칠 수 있지만, 그래도 Person의 사용자 쪽에서는 컴파일을 다시 할 필요가 없다. 게다가 Person이 어떻게 구현되어 있는지를 들여다볼 수 없기 때문에, 구현 세부사항에 어떻게든 직접 발을 걸치는 코드를 작성할 여지가 사라진다. 이것이 인터페이스와 구현이 분리되듯 떨어진 경우이다.

결국 이렇게 인터페이스와 구현을 둘로 나누는 키는 '정의부에 대한 의존성'을 '선언부에 대한 의존성'으로 바꾸어 놓는 데 있다. 

즉, 헤더 파일을 만들 때는 실용적으로 의미를 갖는 한 자체조달 형태로 만들고, 정 안되면 다른 파일에 대한 의존성을 갖도록 하되 정의부가 아닌 선언부에 대해 의존성을 갖도록 만들면 된다.

정리를 하면 다음과 같다.

**객체 참조자 및 포인터로 충분한 경우에 객체를 직접 쓰지 말자.**

**할 수 있으면 클래스 정의 대신 클래스 선언에 최대한 의존하도록 만들자.**
어떤 클래스를 사용하는 함수를 선언할 때는 그 클래스의 정의를 가져오지 않아도 된다. 심지어 그 클래스 객체를 값으로 전달하거나 반환하더라도 클래스 정의가 필요 없다.
```cpp
class Date;  //클래스 선언

Date today();  //Date 클래스의 정의를 가져오지 않아도 된다.
void clearAppointments(Date d);
```
Date를 정의하지 않고도 today와 clearAppointments 함수를 선언할 수 있다는 데 놀랄수도 있다. 누군가가 이들의 함수를 호출한다면 호출하기 전에 Date의 정의가 파악되어야 한다. 그렇다면, 어째서 아무도 호출할 것 같지 않은 함수를 이렇게까지 애써서 선언하려는 건가? 호출하는 사람이 없어서가 아닌, 호출하는 사람이 모두가 아니기 때문에 이렇게 사용하는 것이다.

제품을 만들려면 클래스 정의를 제공하는 일을 어딘가에서 해야 한다. 함수 선언이 되어 있는 라이브러리의 헤더 파일 쪽에 그 부담을 주지 않고 실제 함수 호출이 일어나는 사용자의 소스 파일 쪽에 전가하는 방법을 사용한 것이다. 이렇게 하면 실제로 쓰지도 않을 타입 정의에 대해 사용자가 의존성을 끌어오는 거추장스러움을 막을 수 있다.

**선언부와 정의부에 대해 별도의 헤더 파일을 제공한다.**
"클래스를 둘로 쪼개자"라는 지침을 제대로 쓸 수 있도록 하려면 헤더 파일이 짝으로 있어야 한다. 하나는 선언부를 위한 헤더 파일이고, 또 하나는 정의부를 위한 헤더 파일이다. 이 두 파일은 관리도 짝 단위로 해야한다. 그렇기에 라이브러리 사용자 쪽에서는 전방 선언 대신에 선언부 헤더 파일을 항상 \#include해야 할 것이다. 
```cpp
#include "datefwd.h"  //Date 클래스를 선언하고 있는(그러나 정의는 하지 않는) 헤더 파일

Date today();
void clearAppointments(Date d);
```
pimpl 관용구를 사용하는 Person 같은 클래스를 가리켜 핸들 클래스 라고 한다. 핸들 클래스에서 어떤 함수를 호출하게 되어 있다면, 핸들 클래스에 대응되는 구현 클래스 쪽으로 그 함수 호출을 전달해서 구현 클래스가 실제 작업을 수행하게 만들어라.
```cpp
#include "Person.h". //Person 클래스를 구현하고 있는 중이기 때문에, 이 Person의 클래스 정의를 #include해야 한다
#include "PersonImpl.h" //이와 동시에 PersonImpl의 클래스 정의도 #include해야 하는데, 이렇게 하지 않으면 멤버 함수를 호출할 수 없다. 잘보면 PersonImpl의 멤버 함수는 Person의 멤버 함수와 일대일로 대응되고 있음을 알 수 있다. 인터페이가 똑같음.

Person::Person(const std::string& name, const Date& birthday, const Address& addr) : pImpl(new PersonImpl(name, birthday, addr))
{}

std::string Person::name() const
{
	return pImpl->name();
}
```
핸들 클래스 방법 대신에 다른 방법을 쓰고 싶다면 Person을 특수 형태의 추상 기본 클래스인 인터페이스 클래스로 만드는 방법도 생각해 볼 수 있겠다. 어떤 기능을 나타내는 인터페이스를 추상 기본 클래스를 통해 마련해 놓고, 이 클래스로부터 파생 클래스를 만들 수 있게 하자는 것이다. 파생이 목적이기 때문에 이런 클래스에는 데이터 멤버도 없고, 생성자나 가상 소멸자도 없으며, 인터페이스를 구성하는 순수 가상 함수만 들어있다.

C++는 자바 및 닷넷처럼 인터페이스에 대해 제약을 가하지 않는다. 자바 혹은 닷넷의 인터페이스는 언어 차원에서 데이터 멤버나 함수 구현을 아예 가질 수 없지만 C++에는 이러한 제약이 없다.

Person 클래스의 인터페이스 클래스는 다음과 같이 만들 수 있다.
```cpp
class Person {
public:
	virtual ~Person();
	virtual std::sttring name() const = 0;
	virtual std::string birthDate() const = 0;
	virtual std::string address() const = 0;
};
```
인터페이스 클래스를 사용하기 위해서는 객체 생성 수단이 최소한 하나는 있어야 한다. 대개 이 문제는 파생 클래스의 생성자 역할을 대신하는 어떤 함수를 만들어 놓고 이것을 호출함으로써 해결하고자 한다. 많은 사람들이 이런 함수를 가리켜 팩토리 함수 혹은 가상 생성자라고 부른다. 역할은 주어진 인터페이스 클래스의 인터페이스를 지원하는 객체를 동적으로 할당한 후, 그 객체의 포인터를 반환하는 것이다. 이런 함수는 인터페이스 클래스 내부에 정적 멤버로 선언되는 경우가 많다.
```cpp
class Person {
public:
	...
	static std::tr1::shared_ptr<Person> create(const std::string& name, const Date& birthday, const Address& addr);  //주어진 매개변수로 초기화되는 Person 객체를 새로 만들고 그것에 대한 tr1::shared_ptr을 반환한다.
	...
}
```
사용자쪽에서는 다음과 같이 사용하면 된다.
```cpp
std::string name;
Date dateOfBirth;
Address address;
...

//Person 인터페이스를 지원하는 객체 한 개를 생성한다.
std::tr1::shared_ptr<Person> pp(Person::create(name, dateOfBirth, address));
...
std::cout << pp->name()    //Person 인터페이스를 통해 그 객체를 사용한다.
		  << " was born on"
		  << pp->birthDate()
		  << " and now lives at "
		  << pp->address();
```
해당 인터페이스 클래스의 인터페이스를 지원하는 구체 클래스(concrete class)가 어디엔가 정의되어야 할 것이다. 예를 들어 Person클래스로부터 파생된 RealPerson이라는 구체 클래스가 있다면, 이 클래스는 자신이 상속받은 가상함수(순수 가상 함수)에 대한 구현부를 제공하는 식으로 만들어졌을 것이다.
```cpp
class RealPerson: public Person {
public:
	RealPerson(const std::string& name, const Date& birthday, const Address& addr) : theName(name), theBirthDate(birthday), theAddress(addr)
{}

	virtual ~RealPerson() {}

	std::string name() const;
	std::string birthDate() const;
	std::string address() const;

private:
	std::string theName;
	Date theBirthDate;
	Address theAddress;
};
```
이제 RealPerson은 준비되었고 남은 것은 Person::create 함수인데 간단하게 만들 수 있다.
```cpp
std::tr1::shared_ptr<Person> Person::create(const std::string& name, const Date& birthday, const Address& addr)
{
	return std::tr1::shared_prt<Person>(new RealPerson(name, birthday, addr));
}
```
위의 방법말고 인터페이스 클래스를 구현하는 두번째 방법은 다중 상속을 이용하는 것이다.(항목40에서 다룸)

결론은 핸들 클래스와 인터페이스 클래스는 구현부로부터 인터페이스를 뚝 떼어 놓음으로써 파일들 사이의 컴파일 의존성을 완화시키는 효과를 가져다준다.

핸들 클래스와 인터페이스 클래스가 똑같이 갖고 있는 약점이 있다. 바로 인라인 함수의 도움을 제대로 끌어내기 힘들다는 것이다. 인라인이 되게 만들려면 함수 본문을 대개 헤더 파일에 두어야 한다고 항목30에서 이야기를 했다는데 그렇지만 핸들 클래스와 인터페이스 클래스는 함수 본문과 같은 구현부를 사용자의 눈으로부터 차단하는 데 중점을 둔 설계이다. 

핸들 클래스와 인터페이스 클래스가 비용 소모를 가져오긴 하지만 개발 도중에 핸들 클래스 혹은 인터페이스 클래스를 사용하면 좋다. 구현부가 바뀌었을 때 사용자에게 미칠 파급 효과를 최소한으로 만드는 것이 좋기 때문이다. 그러다가 실행 속력이나 파일 크기에서 많이 손해를 보지는 않는지 나중에 제품을 출시할 때 확인하여 통짜 구체 클래스로 바꾸는 것은 그때 하여도 괜찮다.


+ 컴파일 의존성을 최소화하는 작업의 배경이 되는 가장 기본적인 아이디어는 '정의' 대신에 '선언'에 의존하게 만들자는 것이다. 이 아이디어에 기반한 두 가지 접근 방법은 핸들 클래스와 인터페이스 클래스이다.
+ 라이브러리 헤더는 그 자체로 모든 것을 갖추어야 하며 선언부만 갖고 있는 형태여야 한다. 이 규칙은 템플릿이 쓰이거나 쓰이지 않거나 동일하게 적용하자.