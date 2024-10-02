# Item15. 자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자
수많은 API들이 자원을 직접 참조하도록 만들어져 있어서, 자원 관리 객체의 보호벽을 넘어가서 실제 자원을 직접 만져야 할 일이 있다.

**명시적 변환(explicit conversion)**
tr1::shared_ptr 및 auto_ptr은 명시적 변환을 수행하는 get이라는 멤버함수를 제공한다. 이 함수를 사용하여 각 타입으로 만든 스마트 포인터 객체에 들어 있는 실제 포인터(의 사본)를 얻어낼 수 있다.
```cpp
std::tr1::shared_ptr<Investment> pInv(createInvestment());
int daysHeld(const Investment *pi);
int days = dayHeld(pInv.get());    //명시적 형변환
```
**암시적 변환(implicit conversion)**
변환할 때마다 명시적 변환으로 get() 을 호출하면 자원이 누출될 가능성이 높아지기도 한다. 이에 대한 대안으로 암시적변환 함수를 클래스에서 제공하도록 하면 된다.
```cpp
void changeFontSize(FontHandle f, int newSize);
class Font {
public:
	...
	opearator FontHandle() const    //암시적 변환 함수
	{ return f; }
	...
};
Font f(getFont ());
int newFontSize;
...

changeFontSize(f, newFontSize);    //Font에서 FontHandle로 암시적 변환을 수행

//아래와 같은 문제가 발생할 수 있다.
//원래의도는 Font객체를 복사하려는 것이였는데 f1이 FontHandle로 바뀌고 복사가 된 경우.
Font f1(getFont());
...
FontHandle f2 = f1;
```

결국 RAII 클래스를 실제 자원으로 바꾸는 방법으로서 명시적 변환을 제공할 것인지 아니면 암시적 변환을 허용할 것인지에 대한 결정은 그 RAII 클래스만의 특정한 용도와 사용 환경에 따라 달라진다.

 + 실제 자원을 직접 접근해야 하는 기존 API들도 많기 때문에, RAII 클래스를 만들 때는 그 클래스가 관리하는 자원을 얻을 수 있는 방법을 열어 주어야 한다.
 + 자원 접근은 명시적 변환 혹은 암시적 변환을 통해 가능하다. 안전성만 따지면 명시적 변환이 대체적으로 더 낫지만, 고객 편의성을 놓고 보면 암시적 변환이 괜찮다.
