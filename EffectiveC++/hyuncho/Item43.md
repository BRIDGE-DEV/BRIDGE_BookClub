# Item43. 템플릿으로 만들어진 기본 클래스 안의 이름에 접근하는 방법을 알아 두자
```cpp
class CompanyA {
public:
	...
	void sendClearText(const std::string& msg);
	void sendEncrypted(const std::string& msg);
	...
};

class CompanyB {
public:
	...
	void sendClearText(const std::string& msg);
	void sendEncrypted(const std::string& msg);
	...
};

class MsgInfo { ... };

template <typename Company>
class MsgSender {
public:
	...
	void sendClear(const MsgInfo& info)
	{
		std::string msg;

		Company c;
		c.sendClearText(msg);
	}

	void sendSecret(const MsgInfo& info)
	{ ... }
};

template <typename Company>
class LoggingMsgSender:public MsgSender<Company> {
public:
	...
	void sendClearMsg(const MsgInfo& info)
	{
		sendClear(info);  //기본 클래스의 함수를 호출하는데, 이 코드는 컴파일되지 않는다.
	}
	...
};
```
이 코드는 컴파일 되지 않는다. 적어도 표준을 따르는 컴파일러를 쓴다면 컴파일이 안 될 것이다. 'sendClear 함수가 존재하지 않는다' 라는 것이 컴파일이 안 되는 이유이다.

문제는 컴파일러가 LoggingMsgSender 클래스 템플릿의 정의와 마주칠 때, 컴파일러는 대체 이 클래스가 어디서 파생된 것인지를 모른다는 것이다. MsgSender\<Company> 인 것은 분명히 맞다. 하지만 Company는 템플릿 매개변수 이고 이 템플릿 매개변수는 나중(LoggingMsgSender가 인스턴스로 만들어질 때)까지 무엇이 될지 알 수 없다. Company가 정확히 무엇인지 모르는 상태에서 MsgSender\<Company> 클래스가 어떤 형태인지 알 방법이 있을 리가 없다. 그래서 sendClear 함수가 들어있는지 없는지 알아낼 방법이 없는 것도 당연하다.

CompanyZ라는 클래스가 있고 이 클래스는 암호화된 통신만을 사용한다고 하자.
```cpp
class CompanyZ{
public:
	...
	void sendEncrypted(const std::string& msg);
	...
};
```
조금 전에 봤던 일반형 MsgSender 템플릿은 그대로 CompanyZ 클래스에 쓰기엔 좀 그렇다. 왜냐하면 sendClear 함수를 제공하고 있기 때문이다. 이를 바로 잡기 위해, CompanyZ를 위한 MsgSender의 특수화 버전을 만들 수 있다.
```cpp
template<>    //MsgSender 템플릿의 완전 특수화 버전.
class MsgSender<CompanyZ> {
public:
	...
	void sendSecret(const MsgInfo& info)
	{ ... }
};
```
"template<>"구문은 '이건 템플릿도 아니고 클래스도 아니다'라는 것이다. 정확히 말하면 위의 코드는 MsgSender 템플릿을 템플릿 매개변수가 CompanyZ일 때 쓸 수 있도록 특수화한 버전이다. 지금 보는 특수화는 완전 템플릿 특수화(total template specialization)라고 한다. 즉, MsgSender 템플릿이 CompanyZ 타입에 대해 특수화되었고, 이때 이 템플릿의 매개변수들이 하나도 빠짐없이 구체적인 타입으로 정해졌다는 뜻이다. 타입 매개변수가 CompanyZ로 정의된 이상 이 템플릿의 매개변수로는 다른 것이 올 수 없게 된다는 이야기다.

기본 클래스가 MsgSender\<CompanyZ>이면 sendClear 함수가 없기 때문에 LoggingMsgSender의 sendClear 호출은 말이 되지 않는다. 이렇게 기본 클래스 템플릿은 언제라도 특수화 될 수 있고, 이런 특수화 버전에서 제공하는 인터페이스가 원래의 일반형 템플릿과 꼭 같으리란 법은 없다.

그렇기에 C++ 컴파일러는 템플릿으로 만들어진 기본 클래스를 뒤져서 상속된 이름을 찾는 것을 거부한다. 그래서 어떻게든 C++의 "난 템플릿화된 기본 클래스는 멋대로 안 뒤질 거야" 동작이 발현되지 않도록 해야한다.

이에 대한 방법이 세가지 존재한다.
1. 기본 클래스 함수에 대한 호출문 앞에 "this->"를 붙인다.
2. using 선언을 사용한다.
3. 호출할 함수가 기본 클래스의 함수라는 점을 명시적으로 지정하는 것 => 가상 함수 바인딩이 무시되는 단점 존재.

기본 클래스의 멤버에 대한 참조가 무효한지를 컴파일러가 진단하는 과정이 미리 들어간다.(파생 클래스 템플릿의 정의가 구문 분석될 때) 즉, C++는 '이른 진단(early diagnose)'를 선호하는 정책으로 결정한 것이다. 그러면 파생 클래스가 템플릿으로부터 인스턴스화될 때 컴파일러가 기본 클래스의 내용에 대해 아무것도 모르는 이유를 알 수 있다.


+ 파생 클래스 템플리셍서 기본 클래스 템플릿의 이름을 참조할 때는, "this->"를 접두사로 붙이거나 기본 클래스 한정문을 명시적을 써주는 것으로 해결하자.