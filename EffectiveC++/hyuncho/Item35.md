# Item35. 가상 함수 대신 쓸 것들도 생각해 두는 자세를 시시때때로 길러 두자
```cpp
class GameCharacter {
public:
	virtual int heathValue() const;  //캐릭터의 체력치를 반환하는 함수로 파생클래스는 이함수를 재정의 가능
	...
};
```
캐릭터의 체력이 얼마나 남았는지를 나타내는 정수 값을 반환하는 함수로 캐릭터마다 계산 방식이 다를 것이므로 가상 함수로 선언하였다. 또한 healthValue 함수가 순수 가상 함수로 선언되지 않은 것으로 보아, 체력치를 계산하는 기본 알고리즘이 제공된다는 사실을 알 수 있다.

위의 방법 말고 이제 다른 방법들을 살펴볼 것이다.

**비가상 인터페이스 관용구를 통한 템플릿 메서드 패턴**
```cpp
class GameCharacter {
public:
	int healthValue() const  //파생 클래스는 이제 이 함수를 재정의할 수 없다.
	{
		...  //"사전" 동작을 수행
		int retVal = doHealthValue();  //실제 동작을 수행
		...  //"사후" 동작을 수행
		return retVal;
	}
	...
private:
	virtual int doHealthValue() const  //파생 클래스는 이 함수를 재정의 할 수 있다.
	{
		...
	}
};
```
위 방법은 사용자로 하여금 public 비가상멤버함수를 통해 private 가상 함수를 간접적으로 호출하게 만드는 방법이다. 비가상 함수 인터페이스 관용구(non-virtual interface : NVI) 라고 알려져 있다. 이 관용구는 사실 템플릿 메서드라 불리는 고전 디자인 패턴을 C++식으로 구현한 것이다. 이 관용구에 쓰이는 비가상 함수를 가상함수의 래퍼라고도 한다.

NVI 관용구의 이점은 래핑을 통한 가상 함수 호출하기 전과 후인 "사전 동작", "사후 동작" 처리의 공간적 보장이다.

예시로 뮤텍스 잠금, 로그 정보, 클래스의 불변속성과 함수의 사전조건이 만족되었나를 검증하는 작업 등이 "사전 동작"에 들어갈 수 있다. "사후 동작"으로는 뮤텍스 잠금 해제, 함수의 사후 조건을 점검, 클래스의 불변속성 재점검 등의 작업을 할 수 있다.

NVI 관용구를 쓰면 private 가상 함수를 파생클래스에서 정의하겠구나 라고 생각할 수도 있지만 이 함수는 재정의 해놓고 호출 할 수도 없다. 그렇다면 이게 잘못된 구조인가? 아니다. 왜냐하면 NVI 관용구에서는 파생클래스의 가상 함수 재정의를 허용하기 때문에 어떤 기능을 어떻게 조정할지는 파생클래스의 권한이지만, 함수를 언제 호출 할 지 결정하는 것은 기본 클래스 만의 고유권한이다.

```cpp
class Base {
private:
	virtual void privateVirtualFunction() const {
		cout << "Base privateVirtualFunction" << endl;
	}
public:
	void callPrivateFunction() const {
		privateVirtualFunction();
	}
};

class Derived : public Base {
private:
	void privateVirtualFunction() const override {
		cout << "Derived privateVirtualFunctioin" << endl;
	}
};

int main() {
	Derived d;
	d.callPrivateFunction();  //출력결과 -> Derived privateVirtualFunction

	return 0;
}
```

**함수 포인터로 구현한 전략 패턴**
조금 더 극적인 설계 쪽으로 간다면, 캐릭터의 체력치를 계산하는 작업은 캐릭터의 타입과 별개로 놓는 편이 맞다. 즉, 체력치 계산이 어떤 캐릭터의 일부일 필요가 없다. 아래는 각 캐릭터의 생성자에 체력치 계산용 함수의 포인터를 넘기게 만들고, 이 함수를 호출해서 실제 계산을 수행하도록 한 예이다.
```cpp
class GameCharacter;

int defaultHealthCalc(const GameCharacter& gc);

class GameCharacter {
public:
	typedef int (*HealthCalcFunc) (const GameCharacter&);

	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf)
	{}

	int healthValue() const
	{ return healthFunc(*this); }

private:
	HealthCalcFunc healthFunc;
};
```
위 방법은 주변에서 많이들 쓰고 있는 디자인 패턴인 전략(stragy)패턴의 단순한 응용 예이다.

이것은 같은 캐릭터 타입으로부터 만들어진 객체들도 체력치 계산 함수를 각각 다르게 가질 수 있다.
```cpp
class EvilBadGuy: public GameCharacter {
public:
	explicit EvilBadGuy (HealthCalcFunc hcf = defaultHealthCalc) : Gamecharacter(hcf)
	{ ... }
	...
};

int loseHealthQuickly(const Gamecharacter&);
int loseHealthSlowly(const Gamecharacter&);

EvilBadGuy ebg1(loseHealthQuickly);  //같은 타입인데도
EvilBadGuy ebg2(loseHealthSlowly);   //체력치 변화가 다르게 나오는 캐릭터들
```
게임이 실행되는 도중에 특정 캐릭터에 대한 체력치 계산 함수를 바꿀 수 있다. 예를 들어 GameCharacter 클래스에서 setHealthCalculator라는 멤버 함수를 제공하고 있다면 이를 통해 현재 쓰이는 체력치 계산 함수의 교체가 가능해진다.

단점으로는 체력치 계산 함수가 이제 GameCharacter클래스 계통의 멤버 함수가 아니라는 점은, 체력치가 계산되는 대상 객체의 비공개 데이터는 이 함수로 접근할 수 없다는 뜻도 된다.

예시로 defaultHealthCalc 함수는 EvilBadGuy 객체의 public 멤버가 아닌 부분을 건드릴 수 없다.

해결방법으로는 public 영역에 없는 부분을 비멤버 함수도 접근할 수 있게 하려면 그 클래스의 캡슐화를 약화시키는 방법 밖에는 없다는 것이 일반적이 법칙이다. 이를 테면 비멤버 함수를 프렌드로 선언해 놓는다던지, 지금처럼 부득이한 이유가 아니면 숨겨 놓는 것이 더 나을지도 모르는 세부 구현사항에 대한 접근자 함수를 public 멤버로 제공하는 일 등이 있다. 

함수 포인터를 통해 얻는 이점들이 과연 GameCharacter 클래스의 캡슐화를 떨어뜨리면서 얻는 불이익을 채워줄지 아닐지는 실제로 맡은 설계를 보면서 스스로 판단해야 한다.

**tr1::function 으로 구현한 전략 패턴**
tr1::function 타입의 객체를 사용하여 기존의 함수 포인터를 대신하게 만드는 방법이 있다. 이 계열의 객체는 함수 호출성 개체(callable entity)(풀어서 말하면 함수 포인터, 함수 객체 혹은 멤버 함수 포인터)를 가질 수 있다. 
```cpp
class GameCharacter;
int defaultHealthCalc(const GameCharacter& gc);

class GameCharacter {
public:
	//HealthCalcFunc는 함수호출성 개체로서, GameCharacter와 호환되는 어떤 것이든 넘겨받아서 호출 될 수 있으며 int와 호환되는 모든 타입의 객체를 반환한다.
	typedef std::tr1::function<int (const GameCharacter&)> HealthCalcFunc;

	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf)
	{}

	int healthValue() const
	{ return healthFunc(*this); }

private:
	HealthCalcFunc healthFunc;
};
```
HealthCalcFunc는 tr1::function 템플릿을 인스턴스화 한 것에 대한 typedef 타입이다. 다시말해 이 타입을 일반화된 함수 포인터처럼 동작한다는 뜻이다.

크게 다를게 없으나 GameCharacter가 이제는 tr1::function 객체, 그러니까 좀 더 일반화된 함수 포인터를 물게 된다.

이점으로 사용자 쪽에서 체력치 계산 함수를 지정하는데 있어 융통성을 만끽 할 수 있다.

즉, 가상 함수를 tr1::function 데이터 멤버로 대체하여, 호환되는 시그너처를 가진 함수호출성 개체를 사용할 수 있도록 만든다. 이는 전략패턴의 한 형태이다.

tr1::function은 함수 호출자를 추상화하는 객체이다. 함수 포인터, 멤버 함수 포인터, 람다 표현식, 함수 객체 등 다양한 호출 가능 객체를 저장하고 호출 할 수 있다.

**"고전적인" 전략 패턴**
체력치 계산 함수를 나타내는 클래스 계통을 아예 따로 만들고, 실제 체력치 계산 함수는 이 클래스 계통의 가상 함수 멤버로 만든다.
![[IMG-Item35. 가상 함수 대신 쓸 것들도 생각해 두는 자세를 시시때때로 길러 두자-20241217203243962.png]]
GameCharacter가 상속 계통의 최상위 클래스이고 HealthCalcFunc도 최상위 클래스이다.
GameCharacter 타입을 따르는 모든 객체는 HealthCalcFunc 타입의 객체에 대한 포인터를 포함한다.
```cpp
class GameCharacter;
class HealthCalcFunc {
public:
	...
	virtual int calc(const GameCharacter& gc) const
	{ ... }
	...
};

HealthCalcFunc defaultHealthCalc;

class GameCharacter {
public:
	explicit GameCharacter(HealthCalcFunc *phcf = &defaultHealthCalc) : pHealthCalc(phcf)
	{}

	int healthValue() const
	{ return pHealthCalc->calc(*this); }
	...
private:
	HealthCalcFunc *pHealthCalc;
};
```
**요약 정리**
핵심은 '어떤 문제를 해결 하기 위한 설계를 찾을 때 가상 함수를 대신하는 방법들도 고려하자'이다.
+ **비가상 인터페이스 관용구(NVI 관용구)** 를 사용한다: 공개되지 않은 가상 함수를 비가상 public 멤버 함수로 감싸서 호출하는, 템플릿 메서드 패턴의 한 형태이다.
+ 가상 함수를 **함수 포인터 데이터 멤버**로 대체한다: 군더더기 없이 전략 패턴의 핵심만을 보여주는 형태이다.
+ 가상 함수를 **tr1::function 데이터 멤버**로 대체하여, 호환되는 시그너처를 가진 함수호출성 개체를 사용할 수 있도록 만든다. 역시 전략 패턴의 한 형태이다.
+ 한쪽 클래스 계통에 속해 있는 가상 함수를 **다른 쪽 계통에 속해 있는 가상 함수**로 대체한다. : 전략 패턴의 전통적인 구현이다.

객체지향의 설계의 여정은 길다. 알아보느라 시간 좀 들인다해도 나중엔 절대로 시간낭비가 아니였다는 생각이 들 것이다. 들인 만큼 얻게 된다.


+ 가상 함수 대신에 쓸 수 있는 다른 방법으로 NVI 관용구 및 전략 패턴을 들 수 있다. 이 중 NVI 관용구는 그 자체가 템플릿 메서드 패턴의 한 예이다.
+ 객체에 필요한 기능을 멤버 함수로부터 클래스 외부의 비멤버 함수로 옮기면, 그 비멤버 함수는 그 클래스의 public 멤버가 아닌 것들을 접근할 수 없다는 단점이 생긴다.
+ tr1::function 객체는 일반화된 함수 포인터처럼 동작한다. 이 객체는 주어진 대상 시그너처와 호환되는 모든 함수호출성 개체를 지원한다.