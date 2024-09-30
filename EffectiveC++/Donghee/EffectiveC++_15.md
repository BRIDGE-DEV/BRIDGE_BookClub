# 챕터3: 자원 관리

## 항목15: 자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자

항목 13에서는 auto_ptr, tr1::shared_ptr 같은 스마트 포인터를 사용하는 아이디어가 소개되었다. 여기서 daysHeld라는 함수가 Investment를 포인터 형태로 인자로 받는다고 가정해보자.

```cpp
std::tr1::shared_ptr<Investment> pInv(createInvestment());
int daysHeld(const Investment *pi);
int days = daysHeld(pInv); // 오류!
```

다음이 잘 진행되길 원하지만, 마지막 열에서 컴파일 오류가 난다. Investment* 타입을 원하지만, tr1::shared_ptr<Investment> 타입의 객체를 넘기고 있기 때문이다.

결국 우리는 RAII 클래스의 객체를 실제 자원으로 변환할 방법이 필요하다. 명시적 변환(explicit), 암시적 변환(implicit) 두 가지 방법이 존재한다.

tr1::shared_ptr 및 auto_ptr은 명시적 변환을 수행하는 get이라는 멤버 함수를 제공한다. 이 함수를 통해 스마트 포인터 객체에 들어있는 실제 포인터를 얻어낼 수 있다.

```cpp
int days = daysHeld(pInv.get());
```

물론 제대로 만들어진 스마트 포인터 클래스라면, 포인터 역참조 연산자(operator→, operator*)도 오버로딩하고 있다. 즉 암시적 변환도 쉽게 할 수 있다.

```cpp
// 최상위 클래스
class Investment{
public:
	bool isTaxFree() const;
	...
};

// 팩토리 함수
Investment* createInvestment();

// tr1::shared_ptr을 이용한 자원 관리
std::tr1::shared_ptr<Investment> pi1(createInvestment());
// operator->를 이용한 자원 접근
bool taxable1 = !(pi1->isTaxFree());
...
// auto_ptr을 이용한 자원 관리
std::auto_ptr<Investment> pi2(createInvestment));
// operator*를 이용한 자원 접근
bool taxable2 = !((*pi2).isTaxFree());
...
```

RAII 객체 안에 들어 있는 실제 자원을 얻어낼 필요도 종종 생긴다. 따라서 RAII 클래스 설계자 중에는 암시적 변환 함수를 제공하여 자원 접근을 매끄럽게 하는 사람도 있다.

물론 암시적 변환이 들어가면 실수를 저지를 여지가 늘어난다. RAII 클래스를 실제 자원으로 바꾸는 방법으로 명시적 변환을 제공할지, 혹은 암시적 변환을 허용할 것인지에 대한 결정은 용도와 사용 환경에 따라 달라진다. 보통은 암시적 변환보다는 get 등의 명시적 변환 함수를 제공하는 쪽이 나을 때가 많다. 하지만 암시적 타입 변환에서 생기는 사용 시의 자연스러움이 빛을 발하는 경우도 분명 있다.

혹시 자원 접근 함수를 열어 주는 설계가 캡슐화를 위반하는 것은 아닌지 하는 생각이 있을 수 있다. 하지만 RAII 클래스는 애초부터 데이터 은닉이 목적이 아니다. 원하는 동작이 실수 없이 이루어지도록 하면 OK이다. 고객 차원에서 꼭 접근해야 하는 데이터는 열어 주어야 한다.

> 따라서 RAII 클래스를 만들 때는 관리 자원에 접근하는 방법을 열어 줘야 한다.
자원 접근은 명시적/암시적 변환을 통해 가능하다. 안전성만 따지면 명시적 변환이 대체적으로 낫고, 고객 편의성을 놓고 보면 암시적 변환이 괜찮다.