# Item40. 다중 상속은 심사숙고해서 사용하자
C++ 에서 다중 상속에 관한 견해 두 가지
1. 단일 상속이 좋다면 다중 상속은 더 좋을 것
2. 단일 상속은 좋지만 다중 상속은 골칫거리 밖에 안된다.

'다중 상속'을 하면 둘 이상의 기본 클래스로부터 똑같은 이름을 물려받을 가능성이 생긴다. 즉, 다중 상속 때문에 모호성이 생기는 것이다.
```cpp
class BorrowableItem {
public:
	void checkOut();
	...
};

class ElectronicGadget{
private:
	bool checkOut() const;
	...
};

class MP3Player:
	public BorrowableItem,
	public ElectronicGadget
	{ ... };

MP3Player mp;

mp.checkOut();  //모호성 발생!
```
checkOut 호출 부분에서 모호성이 발생하는데 여기서 눈여겨둘 사실을 두 checkOut 함수들 중에서 파생클래스가 접근할 수 있는 함수가 딱 결정되는 것이 분명한데도(BorrwableItem에서는 public 멤버이지만, ElectronicGadget 에서는 private 멤버) 모호성이 생긴다. 이것은 중복된 함수 호출 중 하나를 골라내는 C++의 규칙을 따른 결과이다.

어떤 함수가 접근 가능한 함수인지를 알아 보기 전에, C++ 컴파일러는 이 규칙을 써서 주어진 호출에 대해 최적으로 일치하는 함수인지를 먼저 확인한다. 다시 말해 최적 일치 함수를 찾고 난 후에 함수의 접근 가능성을 점검한다는 것이다.

지금의 경우는 C++ 규칙에 의한 일치도가 같아 최적일치 함수가 결정되지 않는다. 그래서 접근 가능성이 점검되는 순서조차 오지 않는 것이다.

모호성을 해결하기 위해서는 호출할 함수를 손수 지정해주어야 한다.
```cpp
mp.BorrowableItem::checkOut();
```
이렇게 되면 private 멤버를 호출하기 때문에 컴파일 에러가 발생한다.
```cpp
class File { ... };
class InputFile : public File { ... };
class OutputFile : public File { ... };
class IOFile : public InputFile,
				public OutputFile
{ ... };
```
마름모 꼴의 다중 상속을 갖게 된다면 기본 클래스의 데이터멤버가 경로의 개수만큼 있을까? 하나만 존재할까?

C++은 이 논란으로부터 두 방향 모두를 지원한다. 기본적으로는 데이터를 중복 생성하는 쪽이다. 만약 데이터 멤버의 중복 생성을 원한 것이 아니였다면 해당 데이터 멤버를 가진 클래스를 가상 기본 클래스로 만드는 것으로 해결을 볼 수 있다. 즉, 가상 상속을 하게 만드는 것이다.
```cpp
class File { ... };
class InputFile : virtual public File { ... };
class OutputFile : virtual public File { ... };
class IOFile : public InputFile,
				public OutputFile
{ ... };
```
정확한 동작 관점에서 보면 public 상속은 반드시 항상 가상 상속이어야 하는 것이 맞다. 정확성 외의 측면들을 고려한다면 그렇지만은 않다. 가상 상속을 사용하면 크기가 더 커지고 데이터 멤버에 접근하는 속도도 느리다. 즉, 가상 상속은 비싸다.

가상 클래스의 초기화 관련 규칙은 비가상 기본 클래스의 초기화 규칙보다 훨씬 복잡한데다가 직관성도 더 떨어진다.

가상 기본 클래스는 결국 구태여 쓸 필요가 없다면 사용하면 안되고 비가상 상속을 기본으로 삼아야 한다. 또한 가상 기본 클래스를 쓰지 않으면 안 될 상황이라면, 가상 기본 클래스에는 데이터를 넣지 않는 쪽으로 최대한 신경써야 한다. 데이터가 들어가지 않아야 복잡한 가상 기본클래스의 초기화 규칙으로부터 벗어날 수 있다.
```cpp
class IPerson{
public:
	virtual ~IPerson();

	virtual std::string name() const = 0;
	virtual std::string birthDate() const = 0;
};

//유일한 데이터 베이스 ID로부터 IPerson 객체를 만들어내는 팩토리 함수이다.
std::tr1::shared_ptr<IPerson> makePerson(DatabaseID personIdentifier);

DatabaseID askUserForDatabaseID();

DatabaseID id(askUserForDatabaseID());
std::tr1::shared_ptr<IPerson> pp (makePerson(id));

class PersonInfo{
public:
	explicit PersonInfo (DatabaseID pid);
	virtual ~PersonInfo();

	virtual const char * theName() const;
	virtual const char * theBirthDate() const;
	...
private:
	virtual const char * valueDelimOpen() const;
	virtual const char * valueDelimClose() const;
	...
};

const char * PersonInfo::valueDelimOpen() const
{
	return "[";
}

const char * PersonInfo::valueDelimClose() const
{
	return "]";
}

const char * PersonInfo::theName() const
{
	static char value[Max_Formatted_Field_Value_Length];

	std::strcpy(value, valueDelimOpen());
	std::strcat(value, valueDelimClose());

	return value;
}
```
theName은 valueDelimOpen을 호출해서 시작 구분자를 만들고, name 값 자체를 만든 다음, valueDelimClose를 호출하도록 구현되었다.

PersonInfo 클래스는 CPerson 을 구현하기 편하게 만들어주는 함수를 어쩌다 갖고 있는 것이고 이는 is-implemented-in-terms-of 관계이다. 결국 is-implemented-in-terms-of 관계를 표현하는 것은 두가지 인데 (객체 합성, private 상속) 여기서 CPerson 클래스는 valueDelimOpen 및 valueDelimClose 를 반드시 재정의해야 하므로 가상 함수를 재정의 할 때 사용하는 private 상속을 사용하면 된다.

```cpp
class IPerson{
public:
	virtual ~IPerson();

	virtual std::string name() const = 0;
	virtual std::string birthDate() const = 0;
};

class DatavaseID { ... };

class PersonInfo{
public:
	explicit PersonInfo(DatabaseID pid);
	virtual ~PersonInfo();

	virtual const char * theName() const;
	virtual const char * theBirthDate() const;

	virtual const char * valueDelimOpen() const;
	virtual const char * valueDelimClose() const;
	...
};

class CPerson : public IPerson, private PersonInfo{   //다중상속 사용
public:
	explicit CPerson(DatabaseID pid) : PersonInfo(pid) { }
	
	virtual std::string name() const
	{ return PersonInfo::theName(); }
	
	virtual std::string birthDate() const
	{ return PersonInfo::theBirthDate(); }
private:
	const char * valueDelimOpen() const { return ""; }
	const char * valueDelimClose() const [ return ""; }
}
```
웬만한 경우에는 SI 방법으로 할 수 있다. 그러나 가장 적합한 방법이 MI 일 경우도 존재한다. 다중 상속을 사용할 때는 확인하고 또 확인하고 또 확인하라.


+ 다중 상속은 단일 상속보다 확실히 복잡하다. 새로운 모호성 문제를 일으킬 뿐만 아니라 가상 상속이 필요해질 수도 있다.
+ 가상 상속을 쓰면 크기 비용, 속도 비용이 늘어나며, 초기화 및 대입 연산의 복잡도가 커진다. 따라서 가상 기본 클래스에는 데이터를 두지 않는 것이 현실적으로 가장 실용적이다.
+ 다중 상속을 적법하게 쓸 수 있는 경우가 있다. 여러 시나리오 중 하나는, 인터페이스 클래스로부터 public 상속을 시킴과 동시에 구현을 돕는 클래스로부터 private 상속을 시키는 것이다.