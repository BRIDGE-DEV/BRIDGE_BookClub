```cpp
HomeForSale h1;
HomeForSale h2;

HomeForSale h3(h1);   //컴파일 되면 안됨!

h1 = h2;              //컴파일 되면 안됨!
```
아무리 주석으로 막아보려하지만 야속하게도 그렇게 되지는 않는다. 복사 생성자와 복사 대입 연산자를 선언하지 않고 이들을 호출하면 컴파일러가 알아서 이를 선언해버리기 때문이다. 그렇다면 어떻게 하면 이 복사를 막을 수 있을까? 바로 **복사 생성자와 복사 대입 연산자에 private을 사용하는 것**이다. 이렇게 하면 클래스 멤버 함수가 명시적으로 선언되기 때문에 컴파일러는 자신의 기본 버전을 만들 수가 없다. 이 함수들은 비공개의 접근성을 가지기 때문에 외부로부터의 호출을 차단할 수 있다. 하지만 private 멤버 함수는 그 클래스의 멤버 함수 및 프렌드 함수가 호출할 수 있다는 점이 여전한 **허점**이 된다. 선언만 하고 정의를 하지 않는다면 멤버함수를 호출했을 때 링크 오류가 발생하도록 만드는 방법을 이전에 사용하기도 하였다. 이 링크 오류를 컴파일 오류로 미리 검출이 되도록 하는 방법으로는 **파생클래스를 이용하는 방법**이 있다.
```cpp
class Uncopyable {
protected:
	Uncopyable() {}
	~Uncopyable() {}
	
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};

class HomeForSale: private Uncopyable {    //복사 생성자도 복사대입연산자도 생성되지 않는다.
...
};
```
