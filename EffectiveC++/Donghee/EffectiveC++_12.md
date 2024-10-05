# 챕터2: 생성자, 소멸자 및 대입 연산자

## 항목 12: 객체의 모든 부분을 빠짐없이 복사하자

설계가 잘 된 객체 지향의 클래스를 보면, 객체를 복사하는 함수가 딱 둘만 있다. 복사 생성자, 복사 대입 연산자이다. 이 둘을 통틀어 **객체 복사 함수**라고 부른다.

컴파일러가 생성한 복사 함수는 비록 저절로 만들어졌지만 동작은 기본적인 요구에 아주 충실하다. 객체 복사 함수를 직접 선언한다는 것은, 컴파일러가 만든 기본 동작에 뭔가 마음에 안 드는 것이 있다는 이야기이다. 컴파일러는 이제 직접 구현한 복사 함수가 거의 틀렸을 경우에도 별 경고를 주지 않는다. 다음의 예제를 보자.

```cpp
void logCall(const std::string& funcName);

class Customer {
public:
	...
	Customer(const Customer& rhs);
	Customer& operator=(const Customer& rhs);
	...
private:
	std::string name;
};

Customer::Customer(const Customer& rhs) : name(rhs.name)
{
	logCall("Customer copy constructor");
}

Customer& Customer::operator=(const Customer& rhs)
{
	logCall("Customer copy assignment operator");
	
	name = rhs.name;
	
	return *this;
}
```

이 코드는 별 문제가 없어보인다. 여기서 데이터 멤버를 추가해보자.

```cpp
class Date { ... };

class Customer {
public:
	...
private:
	std::string name;
	Date lastTransaction;
};
```

Date 객체를 데이터 멤버로 추가했다. 이제 복사 함수 동작은 완전 복사가 아니라 부분 복사가 된다. 이런 상황이 되더라도, 대부분의 컴파일러는 경고하지 않는다.

결국 우리가 할 일은, 데이터 멤버가 추가되었다면 추가한 데이터 멤버를 처리하도록 복사 함수를 다시 작성하는 것밖에는 없다.

이 문제가 더 심해지는 경우는, 클래스 상속의 경우다.

```cpp
class PriorityCustomer: public Custome {
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

PriorityCustomer 클래스의 복사 함수는 언뜻 보기엔 모든 것을 복사하고 있는 것처럼 보인다. 하지만 Customer로부터 상속한 데이터 멤버들은 복사가 되지 않고 있다. PriorityCustomer 객체의 Customer 부분은 기본 생성자에 의해 초기화된다. 이 생성자는 당연히 name, lastTransaction에 대해 **기본적인 초기화**만 수행한다. 결국 복사 대입 연산자는 기본 클래스의 데이터 멤버를 건드릴 시도조차 하지 않는다.

물론 기본 클래스의 데이터 멤버는 private 멤버일 가능성이 아주 높다. 따라서 이들을 직접 건드리기 보다는, 파생 클래스의 복사 함수에서 기본 클래스의 복사 함수를 호출하도록 만들면 된다.

```cpp
PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs) : Customer(rhs), priority(rhs.priority)
{
	logCall("PriorityCustomer copy constructor");
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
	logCall("PriorityCustomer copy assignment operator");
	
	Customer::operator=(rhs);
	priority = rhs.priority;
	
	return *this;
}
```

객체의 복사 함수를 작성할 때는 다음 두 가지를 꼭 확인하자.

1. 해당 클래스의 데이터 멤버를 모두 복사
2. 이 클래스가 상속한 기본 클래스의 복사 함수도 호출

혹시나 복사 생성자와 복사 대입 연산자의 본문이 비슷한 경우가 있어 한 쪽에서 다른 쪽을 호출하는 식은 안될까 생각할 수 있다. 하지만 복사 대입 연산자에서 복사 생성자를 호출하는 것부터 말이 안되는 발상이다. 이미 만들어져 버젓이 존재하는 객체를 ‘생성’하고 있기 떄문이다.

반대는 어떨까? 복사 생성자는 새로 만들어진 객체를 초기화하는 것이지만, 대입 연산자는 이미 초기화된 객체에 값만 넘겨주는 것이다. 생성 중인 객체에 대입하라니, 이미 말이 안된다.

결국 이렇게 복사 생성자와 복사 대입 연산자의 코드 본문이 비슷하게 나온다는 느낌이 들면, 겹치는 부분을 별도의 멤버 함수로 분리해 이 함수를 호출하게 만들자.

> 객체 복사 함수는 주어진 객체의 모든 데이터 멤버 및 모든 기본 클래스 부분을 빠뜨리지 말고 복사해야 한다.
클래스의 복사 함수 두 개를 구현할 때, 한쪽을 이용해서 다른 쪽을 구현하려는 시도는 절대 하지 말자. 대신 공통된 동작을 제3의 함수에 분리해 이것을 호출하도록 하자.