# 챕터6: 상속, 그리고 객체 지향 설계

## 항목 35: 가상 함수 대신 쓸 것들도 생각해 두는 자세를 시시때때로 길러 두자

게임 개발 중 체력을 반환하는 함수를 만든다고 해보자. `healthValue` 라는 이름의 멤버 함수를 만들고, 체력이 얼마나 남았는지 제공한다. 캐릭터마다 체력 계산 방법이 다를 수 있기 때문에, 가상 함수로 선언한다.

```cpp
class GameCharacter {
public:
	virtual int healthValue() const;
	...
};
```

너무나 당연한 설계지만, 다른 방법이 없는지 생각해보자.

### 비가상 인터페이스 관용구를 통한 템플릿 메서드 패턴

이 방법을 간단히 설명하면, `helathValue`를 public 멤버 함수로 두되 비가상 함수로 선언하고, 내부적으로는 실제 동작을 맡은 private 가상 함수를 호출하는 식으로 만드는 것이다. private 가상 함수는 파생 클래스에서 호출은 불가능하지만 재정의는 가능하다.

```cpp
class GameCharacter {
public:
	int healthValue() const
	{
		... // 사전 동작
		int retVal = doHealthValue(); // 실제 동작 수행
		... // 사후 동작
		return retVal;
	}
	...
private:
	virtual int doHealthValue() const // 재정의해야하는 함수
	{
		...
	}
};
```

이는 사용자로 하여금 public 비가상 멤버 함수를 통해 private 가상 함수를 간접적으로 호출하게 만드는 방법으로, ‘**비가상 함수 인터페이스(NVI)**’ 관용구로 알려져 있다. NVI 관용구의 이점은 위의 코드의 주석처럼, 사전 동작 및 사후 동작이 가능하다는 점이다.

private 가상 함수는 재정의해 놓고 호출할 수도 없다. 하지만 이 행동은 어떤 동작을 어떻게 구현할 것인가를 지정하는 것이고, 가상 함수를 호출하는 일은 그 동작이 수행될 시점을 지정하는 것이다. NVI 관용구에서는 함수를 언제 호출할지에 대한 결정을 기본 클래스의 권한으로 제한한다.

### 함수 포인터로 구현한 전략 패턴

극적인 설계 쪽으로 가면, 체력치의 계산은 캐릭터의 타입과 별개로 놓는 것이 맞을 것이다. 즉, 체력치 계산이 구태여 어떤 캐릭터의 일부일 필요가 없다는 것이다.  각 캐릭터의 생성자에 체력치 계산용 함수의 포인터를 넘기게 만들고, 이 함수를 호출해서 계산을 수행하도록 하자.

```cpp
class GameCharacter; // 전방 선언
int defaultHealthCalc(const GameCharacter& gc);

class GameCharacter {
public:
	typedef int(*HealthCalcFunc) (const GameCharacter&);
	explicit GameCharacter(HealthCalcFunc hcf = defaulthealthFunc) : healthFunc(hcf) {}
	
	int helathValue() const { return healthFunc(*this); }
	...
	
private:
	HelathCalcFunc healthFunc;
};
```

이 방법은 디자인 패턴인 전략 패턴의 단순한 응용 예시이다. 이는 그냥 가상 함수를 사용하는 방법과 비교하면 융통성이 더욱 존재한다. 먼저 같은 캐릭터 타입으로부터 만들어진 객체들도 계산 함수를 다르게 가질 수 있다. 또한 런타임에 특정 캐릭터에 대한 체력치 계산 함수를 바꿀 수 있다.

물론 단점도 존재한다. 체력치 계산 함수가 이제 `GameCharacter` 클래스 계통의 멤버 함수가 아니라는 점은, 대상 객체의 비공개 데이터는 이 함수로 접근할 수 없다는 뜻이다. 이 때문에 정확한 체력치 계산을 위해 public 멤버가 아닌 정보를 써야 할 경우에는 문제가 발생한다. public 영역에 없는 부분을 비멤버 함수도 접근할 수 있게 하려면 그 클래스의 캡슐화를 약화시키는 방법밖에는 없다. 함수 포인터를 통해 얻는 이점들이 과연 `GameCharacter` 클래스의 캡슐화를 떨어뜨리면서 얻는 불이익을 채워 줄지 아닐지는 설계를 보면서 판단해야 한다.

### tr1::function으로 구현한 전략 패턴

tr1::function 타입의 객체를 써서 기존의 함수 포인터를 대신하게 만들 수 있다. tr1::function 계열의 객체는 함수호출성 개체를 가질 수 있고, 이들 개체는 주어진 시점에서 예상되는 시그니처와 호환되는 시그니처를 갖고 있다.

```cpp
class GameCharacter; // 전방 선언
int defaultHealthCalc(const GameCharacter& gc);

class GameCharacter {
public:
	typedef std::tr1::function<int (const GameCharacter&)> HealthCalcFunc;
	explicit GameCharacter(HealthCalcFunc hcf = defaulthealthFunc) : healthFunc(hcf) {}
	
	int helathValue() const { return healthFunc(*this); }
	...
	
private:
	HelathCalcFunc healthFunc;
};
```

`HealthCalcFunc`은 tr1::function 템플릿을 인스턴스화한 것에 대한 typedef 타입이다. 이 타입은 다시 말해 일반화된 함수 포인터 타입처럼 동작한다.

```cpp
std::tr1::function<int (const GameCharacter&)>
```

이 대상 시그니처를 그대로 읽으면 `const GameCharacter`에 대한 참조자를 받고, `int`를 반환하는 함수이다. 이렇게 정의된 tr1::function 타입으로 만들어진 객체는 앞으로 대상 시그니처와 호환되는 함수호출성 개체를 어떤 것도 가질 수 있다. 앞의 함수 포인터와 다른 점은, 좀더 일반화된 함수 포인터를 물게 된다는 것이다.

### “고전적인” 전략 패턴

더 전통적인 방법으로 구현한 전략 패턴을 보자. 체력치 계산 함수를 나타내는 클래스 계통을 아예 따로 만들고, 실제 체력치 계산 함수는 이 클래스 계통의 가상 멤버 함수로 만드는 것이다.

```cpp
class GameCharacter; // 전방 선언
class HealthCalcFunc {
public:
	...
	virtual int calc(const GameCharacter& gc) const { ... }
	...
};
HealthCalcFunc defaultHealthCalc;
class GameCharacter {
public:
	explicit GameCharacter(HealthCalcFunc *phcf = &defaultHealthCalc) : pHealthCalc(phcf) {}
	
	int helathValue() const { return pHealthCalc->calc(*this); }
	...
	
private:
	HelathCalcFunc *pHealthCalc;
};
```

> 어떤 문제를 해결하기 위한 설계를 찾을 때 가상 함수를 대신하는 방법도 고려하자.
비가상 인터페이스 관용구(NVI): 공개되지 않은 가상 함수를 비가상 public 멤버 함수로 감싸서 호출
가상 함수를 함수 포인터 데이터 멤버로 대체
가상 함수를 tr1::function 데이터 멤버로 대체
한쪽 클래스 계통에 속해 있는 가상 함수를 다른 쪽 계통에 속해 있는 가상 함수로 대체