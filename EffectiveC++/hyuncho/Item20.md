# Item20. '값에 의한 전달'보다는 '상수 객체 참조자에 의한 전달' 이 대개 낫다
일반적으로, '값에 의한 전달'이 저비용이라고 가정해도 괜찮은 유일한 타입은 기본제공 타입, STL 반복자, 함수 객체 타입, 이렇게 세 가지 뿐이다. 이 외의 타입에 대해서는 이번 항목에 나온 이야기를 따르는게 좋다. '값에 의한 전달'보다는 '상수객체 참조자에 의한 전달'을 선택하라.
```cpp
class Person {
public:
	Persion();
	virtual ~Person();
	...
private:
	std::string name;
	std::string address;
};

class Student : public Person {
public:
	Student();
	~Student();
	...
private:
	std::string schoolName;
	std::string schoolAddress;	
}

bool validateStudent(Student s);

Student plato;
//plato로 부터 매개변수 s를 초기화하기 위해 Student의 복사생성자가 호출 한번, Person복사생성자 호출한번, string 복사생성자 호출 4번이 이루어지며 소멸이 될 때도 소멸자 호출이 대응 된다.
bool platoIsOK = validateStudent(plato);

//아래와 같이 '상수 객체 참조자'에 의한 전달을 통해서 const로 안정성을 보장받고, &로 비용을 절감한다.
bool validateStudent(const Student& s);
```
```cpp
class Window {
public:
	...
	std::string name() const;
	virtual void display() const;
};

class WindowWithScrollBars : public Window {
public:
	...
	virtual void display() const;
};

void printNameAndDisplay(Window w)
{
	std::cout << w.name();
	w.display();
}

WindowWithScrollBars wwsb;
//매개변수가 Window 객체로 만들어지면서 WindowWithScrollBars 객체의 구실을 할 수 있는 부속 정보가 싹둑 썰려나간다.(복사손실 발생)
printNameAndDisplay(wwsb);

//아래와 같이 상수객체에 대한 참조자로 전달하면 좋다.
void printNameAndDisplay(const Window& w)
{
	std::cout << w.name();
	w.display();
}
```


+ '값에 의한 전달'보다는 '상수 객체 참조자에 의한 전달'을 선호하자. 대체적으로 효율적일 뿐만 아니라 복사손실 문제까지 막아준다.
+ 이번 항목에서 다룬 법친은 기본제공 타입 및 SRL 반복자, 그리고 함수 객체 타입에는 맞지 않는다. 이들에 대해서는 '값에 의한 전달'이 더 적절하다.
