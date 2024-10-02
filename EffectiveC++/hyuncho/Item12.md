# Item12. 객체의 모든 부분을 빠짐없이 복사하자
### 복사 함수
객체의 안쪽 부분을 캡슐화한 객체 지향 시스템 중 설계가 잘 된 것들을 보면, 객체를 복사하는 함수가 딱 둘이 있다. 바로 복사 생성자와 복사 대입 연산자이다. 이 둘을 통틀어 객체 복사 함수라고 한다.
만약 클래스를 만들고 복사 함수들도 만들었는데 이후에 데이터 멤버를 하나 추가한다고 해보자 이럴 경우 컴파일러가 따로 초기화에 대한 에러 메시지를 띄우지 않는다. 결국 복사 함수의 동작은 완전 복사가 아닌 부분 복사가 되어 버린다. 그래서 추가한 데이터 멤버를 따로 복사함수에서 다시 작성해 처리를 해주어야 한다.

클래스 상속의 경우
```cpp
class PriorityCustomer: public Customer {
public:
	...
	PriorityCustomer(const PriorityCustomer& rhs);
	PriorityCustomer& operator=(const PriorityCustomer& rhs);
	...
private:
	int priority;
};

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs) : priority(rhs.priority)
{
	logCall("PriorityCustomer copy constructor");
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
	logCall("PriorityCustomer copy assignment operator");
	priority = rhs.priority;

	return *this;
}
```
위의 코드에서 문제점은 데이터 멤버를 모두 복사하고 있지만 Customer로부터 상속한 데이터 멤버들의 사본도 엄연히 PriorityCustomer 클래스에 들어 있는데 이들이 복사가 안되고 있다. 위의 복사생성자의 경우 Customer의 기본 생성자에 의해 초기화 된다. 위의 복사 대입 연산자의 경우 기본 클래스의 데이터 멤버를 건드릴 시도도 하지 않아 Customer의 데이터 멤버는 변경되지 않고 그대로 남는다.

위의 문제를 해결할 코드
```cpp
PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs) : Customer(rhs), priority(rhs.priority)    //기본 클래스의 복사 생성자를 호출
{
	logCall("PriorityCustomer copy constructor");
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
	logCall("PriorityCustomer copy assignment operator");    //기본 클래스 부분을 대입.
	Customer::operator=(rhs);
	priority = rhs.priority;

	return *this;
}
```
객체 복사 함수를 작성할 때는 다음의 두가지를 확인해라
1. 해당 클래스의 데이터 멤버를 모두 복사
2. 이 클래스가 상속한 기본 클래스의 복사 함수도 꼬박꼬박 호출

+ 객체 복사 함수는 주어진 객체의 모든 데이터 멤버 및 모든 기본 클래스 부분을 빠뜨리지 말고 복사해야 한다.
+ 클래스의 복사 함수 두 개를 구현할 때, 한쪽을 이용해서 다른 쪽을 구현하려는 시도는 절대로 하지 마라. 그 대신, 공통된 동작을 제3의 함수에다 분리해 놓고 양쪽에서 이것을 호출하게 만들어서 해결하자