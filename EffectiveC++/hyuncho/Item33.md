# Item33. 상속된 이름을 숨기는 일은 피하자
```cpp
int x;    //전역 변수

void someFunc()
{
	double x;    //지역 변수

	std::cin >> x; //입력을 받아 지역변수 x에 값을 저장함.
}
```
값을 읽어 x에  넣는 위의 문장에서 실제로 참조하는 x는 전역 변수 x가 아닌 지역변수 x이다. 왜냐하면 안쪽 유효범위에 있는 이름이 바깥쪽 이름을 가리기 때문이다.

컴파일러가 someFunc에 있는 x를 만나면 현재 처리하고 있는 유효 범위인 지역 유효범위를 뒤져 같은 이름이 있는가를 탐색한다. x라는 이름이 있기 때문에 더 이상의 탐색은 멈추게 된다. 만약 지역 유효범위에 x가 없었다면 더 바깥쪽 유효범위에서 찾게 된다.
```cpp
class Base {
private:
	int x;

public:
	virtual void mf1() = 0;
	virtual void mf1(int);

	virtual void mf2();
	
	void mf3();
	void mf3(double);
	...
};

class Derived: public Base {
public:
	virtual void mf1();
	void mf3();
	void mf4();
	...
};
```
기본 클래스에 있는 함수들 중에 mf1과 mf3 이름이 붙은 것은 파생클래스의 함수인 mf1, mf3에 의해 가려지고 만다.
```cpp
Derived d;
int x;
...
d.mf1();  //Derived::mf1 호출
d.mf1(x); //에러발생! Derived::mf1 이 Base::mf1을 가린다.

d.mf2();  //Base::mf2 호출

d.mf3();  //Derived::mf3 호출
d.mf3(x); //에러발생! Derived::mf3이 Base::mf3를 가린다.
```
가려진 이름을 using 선언을 사용하여 끄집어 낼 수 있다.
```cpp
class Base {
private:
	int x;

public:
	virtual void mf1() = 0;
	virtual void mf1(int);
	virtual void mf2();
	void mf3();
	void mf3(double);
	...
};

class Derived : public Base {
public:
	using Base::mf1;  //Base에 있는 것들 중 mf1과 mf3를 이름으로 가진 것들을 Derived의 유효범위에서 볼 수 있도록 만든다.
	using Base::mf3;

	virtual void mf1();
	void mf3();
	void mf4();
	...
};
```
```cpp
Derived d;
int x;
...
d.mf1();  //Derived::mf1 호출
d.mf1(x); //이제는 괜찮다. Base::mf1 호출.

d.mf2();  //Base::mf2 호출

d.mf3();  //Derived::mf3 호출
d.mf3(x); //이제는 괜찮다. Base::mf3 호출.
```
오버로드된 함수가 들어있는 클래스를 상속 받는 다고 했을 때 그 중 몇 개만 재정의를 한다고 했을 때 각 이름에 대해 using을 선언해주어야 한다. 이렇게 하지 않으면 이름에 가려져 버린다.
```cpp
class Base {
public:
	virtual void mf1() = 0;
	virtual void mf1(int);
	...
};

class Derived: private Base {
public:
	virtual void mf1()
	{ Base::mf1(); }
	...
};

Derived d;
int x;

d.mf1();  //Derived::mf1(매개변수 없는 버전) 호출

d.mf1(x);  //에러! Base::mf1은 가려져 있다.
```
Derived가 Base로 부터 private 상속이 이루어졌고 Derived가 상속했으면 하는 mf1함수는 매개변수가 없는 버전 하나 밖에 없다고 치자. 이때는 using으로 해결할 수 없다. 그 이유는 using으로 선언해버리면 그 이름에 해당하는 모든 함수가 파생 클래스로 내려가 버리기 때문이다. 그래서 위와 같이 간단한 전달함수를 만들어서 사용하였다.


+ 파생클래스의 이름은 기본클래스의 이름을 가린다. public 상속에서는 이런 이름 가림 현상은 바람직하지 않다.
+ 가려진 이름을 다시 볼 수 있게 하는 방법으로, using선언 혹은 전달 함수를 쓸 수 있습니다.