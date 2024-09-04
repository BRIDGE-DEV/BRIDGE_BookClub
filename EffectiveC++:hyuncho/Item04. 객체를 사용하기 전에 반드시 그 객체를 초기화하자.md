```cpp
int x; //어떤 상황에서는 0으로 초기화 되지만 항상 보장되지 않는다. 
class Point { int x, y; };
... 
Point p; //이 또한 어떤 상황에서만 초기화 되고 항상 보장되지 않음.
```
### 모든 객체를 사용하기 전에 항상 초기화하자.
1. int의 직접 초기화
2. 포인터의 직접 초기화
3. 입력 스트림에서 초기화
4. 생성자에서 객체의 모든 것을 초기화
### 대입을 초기화와 헷갈리면 안된다
```cpp
class ABEntry{
public:
		ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones);
private:
		std::string theName;
		std::string theAddress;
		std::list<PhoneNumber> thePhones;
		int nuumTimesConsulted;
};

ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones)
{
		theName = name;
		theAddress = address;
		thePhones = phones;
		numTimesConsulted = 0;
}
// 위 함수(ABEntry) 경우에는 초기화가 아닌 대입을 하고 있다.

ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones) : theName(name), theAddress(address), Phones(phones), numTimesConsulted(0)
{}
// 위 함수처럼 해야 초기화가 가능. 첫번째 것보다 효율적임.

ABEntry::ABEntry() : theName(), theAddress(), Phones(), numTimesConsulted(0)
{}
// 기본생성자의 경우도 이렇게 초기화 해주면 좋다.

```
### 상수이거나 참조자로 되어 있는 데이터 멤버의 경우에 반드시 초기화되어야 한다.
**이유는 상수나 참조자는 대입 자체가 불가능하다.**
### 객체를 구성하는 데이터의 초기화 순서
1. 기본 클래스는 파생 클래스보다 먼저 초기화
2. 클래스 데이터 멤버는 그들이 선언된 순서대로 초기화(멤버 초기화 리스트에 넣는 멤버들의 순서도 클래스에 선언한 순서와 동일하게 맞춰주는 것을 습관화하자)
### 정적 객체
자신이 생성된 시점부터 프로그램이 끝날 때까지 살아 있는 객체. 프로그램이 끝날 때 자동으로 소멸됨. main함수가 실행이 끝날 때 정적 객체의 소멸자가 호출된다.
1. 전역객체
2. 네임스페이스 유효범위에서 정의된 객체
3. 클래스 안에서 static으로 선언된 객체
4. 함수 안에서 static으로 선언된 객체
5. 파일 유효범위에서 static으로 정의된 객체
이들 중 함수 안에 있는 정적 객체는 **지역 정적 객체** 라고 하고 나머지는 **비지역 정적 객체** 라고 한다.
### 번역 단위
컴파일을 통해 하나의 목적 파일을 만드는 바탕이 되는 소스코드.
### 서로 다른 번역 단위에 정의된 비지역 정적 객체들 사이의 상대적인 초기화 순서는 정해져 있지 않다.
이에 대한 해결 방법으로 비지역 정적 객체를 하나씩 맡는 함수를 준비하고 이 안에 각 객체를 넣는 것이다. 함수 속에서도 이들은 정적 객체로 선언하고, 그 함수에서는 이들에 대한 참조자를 반환하게 만든다. 사용자 쪽에서는 비지역 정적 객체를 직접 참조하는 과거의 폐단을 버리고 이제는 함수 호출로 대신한다. 정리하면 ‘비지역 정적 객체’가 ‘지역 정적 객체’로 바뀐것이다.(이는 디자인 패턴중 하나인 단일체 패턴과 유사한 방식임) **지역 정적 객체는 함수 호출 중에 그 객체의 정의에 최초로 닿았을 때 초기화되도록 만들어져 있다.**
```cpp
class FileSystem {...};                    

FileSystem& tfs()                          
{
		static FileSystem fs;                  //지역 정적 객체를 정의하고 초기화
		return fs;                             //이객체에 대한 참조자를 반환
}

class Directory {...};

Directory::Directory ( params )
{
		...
		std::size_t disks = tfs().numDisks();
		...
}

Directory& tempDir()
{
		static Directory td;
		return td;
}
```
### 정리
1. 기본 제공 타입의 객체는 직접 손으로 초기화한다. 경우에 따라 저절로 되기도 하고 안되기도 하기 때문.
2. 생성자에서는, 데이터 멤버에 대한 대입문을 생성자 본문 내부에 넣는 방법으로 멤버를 초기화하지 말고 멤버 초기화 리스트를 즐겨 사용하자. 그리고 초기화 리스트에 데이터 멤버를 나열할 때는 클래스에 각 데이터 멤버가 선언된 순서와 똑같이 나열하자
3. 여러 번역 단위에 있는 비지역 정적 객체들의 초기화 순서 문제는 피해서 설계해야한다. 비지역 정적 객체를 지역 정적 객체로 바꾸면 된다.