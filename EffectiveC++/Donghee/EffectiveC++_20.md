# 챕터4: 설계 및 선언

## 항목 20: ‘값에 의한 전달’보다는 ‘상수객체 참조자에 의한 전달’ 방식을 택하는 편이 대개 낫다

C++는 함수로부터 객체를 전달받거나 함수에 객체를 전달할 때 ‘값에 의한 전달’ 방식을 사용한다. 함수 매개변수는 실제 인자의 **‘사본’**을 통해 초기화되며, 함수를 호출한 쪽은 그 함수가 반환한 값의 **‘사본’**을 돌려받는다. 이들 사본을 만들어내는 원천이 바로 복사 생성자인데, 이 점 때문에 ‘값에 의한 전달’이 고비용의 연산이 되기도 한다. 다음 예제를 보자.

```cpp
class Person {
public:
	Person();
	virtual ~Person();
	...
private:
	std::string name;
	std::string address;
};
class Student: public Person {
public:
	Student();
	~Student();
	...
private:
	std::string schoolName;
	std::string schoolAddress;
};

bool validateStudent(Student s);
```

클래스 Person, 그를 상속하는 파생크래스 Student, 그리고 그를 인자로 받는 validateStudent라는 함수가 있다. 이 함수가 호출될 때 어떤 일이 벌어질까?

```cpp
Student plato;
bool platoIsOK = validateStudent(plato);
```

plato로부터 매개변수 s를 초기화시키기 위해 Student의 복사 생성자가 호출된다. 또한 s는 validateStudent가 복귀할 때 소멸될 것이다. 상속 관계와 멤버 변수까지 생각해보자.

Student 복사 생성자, 이에 들어있는 String 복사 생성자 2번, Person 복사 생성자, 이에 들어있는 String 복사 생성자 2번, 다 합치면 복사 생성자만 6번 호출된다. 소멸자도 같은 횟수일 것이다. Student 객체 하나를 전달하는데 이렇게나 많은 생성자와 소멸자가 호출되는 것이다.

이에 대한 명확한 해결 방법이 존재한다. **상수객체에 대한 참조자**로 전달하게 만드는 것이다.

```cpp
bool validateStudent(const Student& s);
```

이제 새로 만들어지는 객체 같은 것이 없기 때문에, 생성자와 소멸자가 전혀 호출되지 않는다. 새겨둬야 할 부분이 매개변수 선언문에 있는 const다. 원래는 사본의 전달이기 때문에 변경을 두려워하지 않아도 되지만, 이제는 참조자가 전달되기 때문에 변경의 걱정을 해야하기 때문이다. const가 붙으면 이런 문제도 날아간다.

참조에 의한 전달 방식으로 매개변수를 넘기면 **복사손실 문제(slicing problem)**가 없어지는 장점도 있다. 이는 파생 클래스 객체가 기본 클래스 객체로 전달될 때 일어나는 문제다. 객체가 값으로 전달된다면, 기본 클래스의 복사 생성자가 호출되므로 파생 클래스 객체만이 가지고 있던 특징들이 다 사라진다. 이를 테면 가상 함수도 파생 클래스가 아닌 기본 클래스 객체인 것처럼 작동하는 것이다. 이럴 때에 상수객체에 대한 참조자로 전달하면 문제를 해결할 수 있다. 참조자는 그 객체의 특성을 그대로 유지하기 때문이다.

참조자는 보통 포인터를 써서 구현된다. 즉, 참조자를 전달한다는 것은 결국 포인터를 전달한다는 것과 일맥상통한다는 이야기다. 전달하는 타입이 기본제공 타입일 경우에는 참조자로 넘기는 것보다 값으로 넘기는 편이 더 효율적일 때가 많다. ‘값에 의한 전달’과 ‘상수객체의 참조에 의한 전달’을 고민 중이라면 기본제공 타입에 대해서는 전자가 정답일 경우도 있다는 것이다. 이 점은 STL의 반복자와 함수 객체에도 마찬가지이다.

기본제공 타입은 작다. 이 점 때문에 타입 크기가 작으면 전부 ‘값에 의한 전달’을 할 수 있다고 착각한다. 데이터 멤버가 포인터 하나라고 해도, 객체를 복사할 때는 포인터 멤버가 가리키는 대상까지 복사해야하기 때문에 비용이 상당할 수 있다.

컴파일러 중에는 기본제공 타입과 사용자 정의 타입을 아예 다르게 취급하는 것들이 있다. 이를테면 진짜 double은 레지스터에 넣어 주지만, double 하나로만 만들어진 객체는 레지스터에 넣지 않는 경우다. 이런 환경에서는 차라리 참조에 의한 전달을 쓰는 편이 낫다.

사용자 정의 타입의 크기는 언제든 변화에 노출되어 있다. 지금은 크기가 작을지 몰라도 나중에는 커질 수 있다. 또한 C++ 구현 환경이 바뀔 때에도 사정이 변할 수 있다. 따라서 일반적으로, ‘값에 의한 전달’이 괜찮아 보일 때도 다시 한번 고려하자.

‘값에 의한 전달’이 저비용이라도 가정해도 괜찮은 유일한 타입은 기본제공 타입, STL 반복자, 함수 객체 타입, 이렇게 세 가지뿐이다.

> ‘값에 의한 전달’보다는 ‘상수 객체 참조자에 의한 전달’을 선호하자.
이 항목의 법칙은 기본제공 타입, STL 반복자, 함수 객체 타입에는 맞지 않는다. 이들에 대해서는 ‘값에 의한 전달’이 더 적절하다.