# Item18. 인터페이스 설계는 제대로 쓰기엔 쉽게, 엉터리로 쓰기엔 어렵게 하자
C++에서는 발에 치이고 손에 잡히는 것이 인터페이스이다. 함수도 인터페이스이고, 클래스도, 템플릿 또한 인터페이스이다.
행여 잘못 사용했을 경우에 인터페이스가 최소한 항의의 몸부림이라도 보여주는 것은 어떻게 보면 의무이다. 이상적으로는, 어떤 인터페이스를 어떻게 써 봤는데 결과 코드가 사용자가 생각한 대로 동작하지 않는다면 그 코드는 컴파일되지 않아야 맞다. 거꾸로 어떤 코드가 컴파일된다면 그 코드는 사용자가 원하는 대로 동작해야 할 것이다.
사용자 쪽에서 뭔가를 외워야 제대로 쓸 수 있는 인터페이스는 잘못 쓰기 쉽다.
```cpp
class Date {
public:
	Date(int month, int day, int year);
	...
};

//매개 변수의 전달 순서가 잘못될 여지가 존재한다.
Date d(30, 3, 1995);  //"3, 30" 이어야 하는데 잘못 전달되었지만 아무 항의의 몸부림이 없다.

//위의 문제점을 랩퍼(wrapper) 타입을 각각 만들어 해결할 수 있다.
struct Day{
	explicit Day(int d) : val(d) {}
	int val;
};
struct Month{
	explicit Month(int m) : val(m) {}
	int val;
};
struct Year{
	explicit Day(int y) : val(y) {}
	int val;
};

class Date {
public:
	Date(const Month& m, const Day& d, const Year& y);
	...
};

Date d(30, 3, 1995);   //에러 발생
Date d(Day(30), Month(3), Year(1995));   //에러 발생
Date d(Month(3), Day(30), Year(1995));   //타입이 전부 맞음
//Day, Month, Year에 데이터를 이것저것 숨겨 넣어 제몫을 하는 온전한 클래스를 만들면 훨씬 낫긴하다.
```
**인터페이스의 올바른 사용을 이끄는 방법**
1. 인터페이스 사이의 일관성 잡아주기
   예를 들면 STL컨테이너의 인터페이스는 전반적으로 일관성을 갖고 있으며 사용하는데 부담이 없다. 
2. 기본제공 타입과의 동작 호환성 유지하기
   그렇게 하지 않을 번듯한 이유가 없다면 사용자 정의 타입은 기본제공 타입처럼 동작하게 만들자. 결국 이는 일관성 있는 인터페이스 제공으로 이어진다.

```cpp
Investment* createInvestment();
```
위와 같이 함수를 사용할 때는 자원 누출을 피하기 위해서는 반환된 포인터를 나중에 삭제해야한다. 이 점은 두가지의 문제점을 야기할 수 있는데 포인터 삭제를 깜빡할 수도 있고, 똑같은 포인터에 대해 delete가 두 번 이상 적용될 수도 있다.
이를 해결하기 위해서는 아래처럼 애초부터 팩토리 함수가 스마트 포인터를 반환하게 하면 된다.
```cpp
std::tr1::shared_ptr<Investment> createInvestment();
```

**교차 DLL 문제**
객체 생성시에 어떤 동적 링크 라이브러리(dynamically linked llibrary: DLL)의 new를 썼는데 그 객체를 삭제할 때는 이전의 DLL과 다른 DLL에 있는 delete를 썼을 경우이다. 이렇게 new/delete 짝이 실행되는 DLL이 달라서 꼬이게 되면 대다수의 플랫폼에서 런타임 에러가 일어난다.
그러나 tr1::shared_ptr의 기본 삭제자는 tr1::shared_ptr이 생성된 DLL과 동일한 DLL에서 delete를 사용하도록 만들어졌기 때문에 이 문제를 피할 수 있다.


+ 좋은 인터페이스는 제대로 쓰기에 쉬우며 엉터리로 쓰기에 어렵다. 인터페이스를 만들 때는 이 특성을 지닐 수 있도록 고민하고 또 고민하자.
+ 인터페이스의 올바른 사용을 이끄는 방법으로는 인터페이스 사이의 일관성 잡아주기, 그리고 기본제공 타입과의 동작 호환성 유지하기가 있다.
+ 사용자의 실수를 방지하는 방법으로는 새로운 타입 만들기, 타입에 대한 연산을 제한하기, 객체의 값에 대해 제약 걸기, 자원 관리 작업을 사용자 책임으로 놓지 않기가 있다.
+ tr1::shared_ptr은 사용자 정의 삭제자를 지원한다. 이 특징 때문에 tr1::shared_ptr은 교차 DLL문제를 막아주며, 뮤텍스 등을 자동으로 잠금 해제하는 데(항목 14 참조) 쓸 수 있다.