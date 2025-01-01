# 챕터7: 템플릿과 일반화 프로그래밍

## 항목 43: 템플릿으로 만들어진 기본 클래스 안의 이름에 접근하는 방법을 알아두자

아래 예제를 먼저 보자.

```cpp
template<typename Company>
class MsgSender {
public:
	...
	void sendClear(const MsgInfo& info)
	{
		std::string msg;
		...
		Company c;
		c.sendCleartext(msg);
	}
	
	void sendSecret(const MsgInfo& info) { ... }
};
```

이 `MsgSender`의 파생 클래스를 사용해, 또 다른 기능을 붙이려고 한다.

```cpp
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	...
	void sendClearMsg(const MsgInfo& info)
	{
		// 사전 행동
		sendClear(info); // 이 코드가 컴파일되지 않는다.
		// 사후 행동
	}
	
	void sendSecret(const MsgInfo& info) { ... }
};
```

여기서 `sendClear` 함수가 존재하지 않는 이유로 컴파일이 되지 않는다. 우리 눈에는 기본 클래스에 있는 `sendClear`가 보이지만, 컴파일러는 기본 클래스를 들여보지 않는다. 이는 컴파일러가 `LoggingMsgSender` 클래스 템플릿의 정의와 마주칠 때, 이 클래스가 어디서 파생된 것인지를 모르기 때문이다. `MsgSender<Company>`라는 것은 알지만, `Company`는 템플릿 매개변수이고, 이것이 무엇인지 모르는 상황에서는 `MsgSender<Company>` 클래스가 어떤 형태인지 알 방법이 없다.

구체적으로는, 템플릿 특수화 예시를 보면 이해가 빠르다.

```cpp
class CompanyZ {
public:
	...
	void sendEncrypted(const std::string& msg);
	...
};

template<>
class MsgSender<CompanyZ> {
public:
	...
	void sendSecret(const MsgInfo& info) { ... }
};
```

괄호 안에 아무것도 없는 `template`의 뜻은 ‘이건 템플릿도 아니고 클래스도 아니다’라는 것이다. 즉, 위의 코드는 `MsgSender` 템플릿을 템플릿 매개변수가 `CompanyZ`일 때 쓸 수 있도록 특수화한 버전이다. 이제 위의 파생 클래스 `LoggingMsgSender`를 다시 보자.

```cpp
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	...
	void sendClearMsg(const MsgInfo& info)
	{
		// 사전 행동
		sendClear(info); // 만약 Company == CompanyZ 라면 이 함수는 존재하지 않는다.
		// 사후 행동
	}
	...
};
```

기본 클래스가 `MsgSender<CompanyZ>`이면 이 코드는 말이 되지 않는다. 이런 일이 생길 수 있기 때문에 위와 같은 함수 호출을 C++가 받아주지 않는 것이다. 기본 클래스 템플릿은 언제라도 특수화될 수 있고, 이런 특수화 버전에서 제공하는 인터페이스가 원래의 일반형 템플릿과 꼭 같으리란 법은 없다는 점을 C++가 인식한다.

난국 돌파를 위해서는 세 가지 방법이 있다. 먼저 기본 클래스 함수에 대한 호출문 앞에 `this->`를 붙인다.

```cpp
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	...
	void sendClearMsg(const MsgInfo& info)
	{
		// 사전 행동
		this->sendClear(info); // sendClear가 상속되는 것으로 간주
		// 사후 행동
	}
	...
};
```

둘째, `using` 선언을 사용한다.

```cpp
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	using MsgSender<Company>::sendClear; // sendClear 함수가 기본 클래스에 있다고 가정
	...
	void sendClearMsg(const MsgInfo& info)
	{
		// 사전 행동
		sendClear(info);
		// 사후 행동
	}
	...
};
```

마지막으로는, 호출할 함수가 기본 클래스의 함수라는 점을 명시적으로 지정하는 것이다.

```cpp
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	...
	void sendClearMsg(const MsgInfo& info)
	{
		// 사전 행동
		MsgSender<Company>::sendClear(info); // 상속되는 것으로 가정
		// 사후 행동
	}
	...
};
```

이렇게 되면, 호출되는 함수가 가상 함수인 경우에는 가상 함수 바인딩이 무시되기 때문에 추천하지 않는다.

세 가지 방법은 모두 이름에 대한 가시성을 조작하는 것이다. 기본 클래스 템플릿이 이후에 어떻게 특수화되더라도 원래의 일반형 템플릿에서 제공하는 인터페이스를 그대로 제공할 것이라고 컴파일러에게 약속하는 것이다.

기본 클래스의 멤버에 대한 참조가 무효한지 컴파일러가 진단하는 과정이 미리 들어가느냐, 아니면 나중에(인스턴스화될 때) 들어가느냐가 바로 이번 항목의 핵심이다. C++는 ‘이른 진단’을 선호하는 쪽으로 결정했다.

> 파생 클래스 템플릿에서 기본 클래스 템플릿의 이름을 참조할 때는 ‘this→’를 접두사로 붙이거나 기본 클래스 한정문을 명시적으로 써 주는 것으로 해결하자.