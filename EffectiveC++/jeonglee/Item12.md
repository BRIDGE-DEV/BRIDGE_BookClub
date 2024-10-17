## Item 12: 객체의 모든 부분을 빠짐없이 복사하자

객체의 안쪽 부분을 캡슐화한 객체 지향 시스템 중 설계가 잘 된 것들을 보면, 객체를 복사하는 함수가 복사 생성자와 복사 대입 연산자만 있는 것을 알 수 있다. 이 둘을 통틀어 객체 복사 함수(object copy function)라고 부른다. 사용자가 정의하지 않는 이상 컴파일러가 필요에 의해 만들어내기도 한다. *기본적인 요구는 충실하게 수행함*

객체 복사 함수를 사용자 정의로 생성한다는 것 자체가 우선 컴파일러 동작에서 수정하고 싶은 사항이 존재한다는 것이고, 이 부분이 이번 챕터의 주제이다.

```cpp
class Customer {
public:
    Customer(const Customer& rhs);
    Customer& operator=(const Customer& rhs);
    ...
private:
    std::string name;
}
```

```cpp
Customer::Customer(const Customer& rhs)
: name(rhs.name)
{
    ...
}

Customer& Customer::operator=(const Customer& rhs)
{
    name = rhs.name;
}
```

지금까지는 전혀 문제가 되지 않지만, 여기서 데이터 멤버를 하나 추가하면서 부터 문제가 생긴다. `Data lastTransaction` 멤버를 추가하면 복사 생성자와 복사 대입 연산자가 모두 재정의되어야 한다. 재정의되지 않는다면 이 복사함수의 동작은 완전 복사(깊은 복사)가 아닌 부분 복사(partial copy)가 된다. 결국 멤버가 추가될 때마다 복사 생성자와 복사 대입 연산자를 재정의해야 하는 번거로움이 생긴다.

이 문제의 확장판으로 클래스 상속까지 들어가면 더욱 골치아프다.

```cpp
class PriorityCustomer: public Customer {
public:
    PriorityCustomer(const PriorityCustomer& rhs);
    PriorityCustomer& operator=(const PriorityCustomer& rhs);
    ...
private:
    int priority;
}
```

```cpp
PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
: Customer(rhs),
  priority(rhs.priority)
{
    ...
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
    Customer::operator=(rhs);
    priority = rhs.priority;
    return *this;
}
```

이 코드의 가장 큰 문제점은 `Customer`로부터 상속한 데이터 멤버들의 사본도 엄연히 `PriorityCustomer`클래스에 들어 있는데, 이들은 복사가 안 되고 있다. `PriorityCustomer` 의 복사 생성자에는 기본 클래스 생성자에 넘길 인자들도 명시되어 있지 않아서 `PriorityCustomer` 객체의 `Customer` 부분은 인자 없이 실행되는 `Customer` 생성자, 즉 **기본 생성자에 의해 초기화된다.**

이 생성자는 당연히 name 및 last-Transaction에 대해 '기본적인' 초기화를 해 줄 것이다. 하지만 `PriorityCustomer` 의 복사 대입 연산자의 경우에는 사정이 다소 다르다. 복사 대입 연산자는 기본 클래스의 데이터 멤버를 건드릴 시도도 하지 않기 때문에, 기본 클래스의 데이터 멤버는 변경되지 않고 그대로 있게 된다.

정리하자면 파생 클래스에 대한 복사 함수를 스스로 만들어야 한다면 기본 클래스 부분을 복사에서 빠뜨리지 않도록 주의해야 한다. *초기화 멤버 리스트를 사용해 기본 클래스 생성자를 호출하는 것을 잊지 말자.*

객체의 복사 함수를 작성할 때는 다음의 두 가지를 꼭 확인하자.

- 해당 클래스의 데이터 멤버를 모두 복사하고
- 이 클래스가 상속한 기본 클래스의 복사 함수도 꼬박꼬박 호출하자.

### 복사 생성자와 복사 대입 연산자 중복에 대하여

클래스의 복사 생성자와 복사 대입 연산자를 보고 비슷한 로직이기에 한쪽에서 다른 한쪽을 호출하는 코드를 만들 수 있는데, 이는 매우 위험한 코드이다. 복사 대입 연산자에서 복사 생성자를 호출하는 것부터 말이 안되는 발생이고, 이미 만들어져 버졋이 존재하는 객체를 '생성'하고 있기 때문에 불가능한 문법이다.

반대의 경우도 이뤄질 수 없는 조건이기에 잘 생각해서 만들자. *중복을 줄이는 것만이 좋은 코드는 아니다.*

### 정리

- 객체 복사 함수는 주어진 객체의 모든 데이터 멤버 및 모든 기본 클래스 부분을 빠뜨리지 말고 복사해야 한다.
- 클래스의 복사 함수 두 개를 구현할 때, 한쪽을 이용해서 다른 쪽을 구현하려는 시도는 절대로 하지 말자.

깊은 복사와 얕은 복사의 개념보다. 사용자 정의 복사 함수가 불러올 수 있는 위험성에 대한 이야기였다.
