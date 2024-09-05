const는 어떤 값이 불변이어야 한다는 제작자의 의도를 컴파일러 및 다른 프로그래머와 나눌 수 있는 수단이다.
```cpp
char greeting[] "Hello";

char *p = greeting;                //비상수 포인터, 비상수 데이터

const char *p = greeting;          //비상수 포인터,  상수 데이터

char * const p = greeting;         //상수 포인터, 비상수 데이터

const char * const p = greeting;   //상수 포인터, 상수 데이터
```
함수 선언에 const를 사용하는 경우는 함수 반환값, 각각의 매개변수, 멤버 함수 앞에 붙을 수 있고 함수 전체에 대해 const의 성질을 붙일 수 있다.

```cpp
class Rational { ... };
const Rational operator*(const Rational& lhs, const Rational& rhs);
```
왜 위의 코드에서 반환값이 const여야 할까? const가 아니면 아래와 같은 게 가능하기 때문이다.
```cpp
Rational a, b, c;
...
(a * b) = c; // a*b의 결과에 operator=를 호출합니다!
```
곱한 값에 할당을 하는 것은 말도 안되는 것이기 때문에 const로 설정해준다.
### 멤버함수에 붙는 const
**용도**
1. 클래스의 인터페이스를 이해하기 좋게 하기 위함
2. 상수 객체를 사용할 수 있게 하자(코드의 효율성 측면에서 좋음, reference-to-const)

```cpp
class TextBlock { 
public:
    ...
    const char& operator[](std::size_t position) const { return text[position]; }      //이렇게 함수 뒤에 const가 나오는 경우는 함수내에 어떤 값도 바꿀 수 없다는 의미이다. 그리고 함수호출할때 const가 붙은 함수만 호출이 가능해짐
    char& operator[](std::size_t position) { return text[position]; }
private: 
    std::string text;
};

TextBlock tb("Hello);
std::cout << tb[0];            //const가 없는 함수 호출

const TextBlock ctb("World");
std::cout << ctb[0];           //const가 있는 함수 호출
```

멤버 함수가 const인 것은 무엇을 의미합니까? 두 가지 주류의 개념이 있다: 비트 단위 const성(또는 물리적 const성)과 논리적 const성이다.

어떤 멤버 함수가 상수 멤버라는 것에는, 비트수준 상수성(다른 말로 물리적 상수성)과 논리적 상수성이라는 두 개의 굵직한 개념이 자리 잡고 있다. 먼저 「비트수준 상수성」은 C++가 적용하고 있는 상수성인데,  (대부분의 프로그래밍 언어가 그렇다.  이유는 바로 밑에서 설명함) 뜻은 그리 거창한 것이 아닌, "그 객체의 어떤 데이터 멤버도 건드리지 않아야 그 함수가 'const'임을 인정하는 것" 뿐이다. 우리가 당연하다고 생각해왔다시피 했던 것을 이렇게 부르는 것이다. 비트수준 상수성을 따르는 상수 멤버 함수는 그 함수가 호출된 객체의 어떤 비정적 멤버도 수정할 수 없기 때문에 그 멤버 함수가 상수성을 위반했는지 안했는지를 쉽게 검사할 수 있다. 자 이렇게 비트수준 상수성에 대해 말을 해보았는데 지금 내가 무엇때문에 이것들을 길게 설명하고있는가?하면, 비트수준 상수성을 따르는 멤버 함수라 할지라도 다음 예처럼, 외부에서 호출한 객체의 private 멤버를 액세스할 수 있는 방법이 존재하기 때문에

```cpp
const CTextBlock cctb("Hello")
char *pc = &cctb[0];

*pc = 'J';                        //"Jello"로 변경됨
```

비트수준 상수성이 정말, 과연 상수성을 정의할 수 있는 제대로 방법인가에 대해 엄청난 논란이 오게 되며, 결국 이런 황당한 상황을 보완하는 대체 개념으로 나오게 된 것이 바로 「논리적 상수성」 이다. 논리적 상수성이라는 개념은 상수 멤버 함수라고 해서 객체의 한 비트도 수정할 수 없는 것이 아니라  (이래서 '비트수준'이란 이름이 붙여진듯) 일부 몇 비트 정도는 바꿀 수 있되, 그것을 사용자측에서 알아채지 못하게만 하면 상수 멤버 자격이 있다는 것이다. 즉, 논리적으로는 상수 멤버 함수의 성질을 지니고 있다는 뜻이기 때문에 상수 멤버 함수가 되어야 마땅하다는 것이다. 예를 하나 들면  문장 구역의 길이를 사용자들이 요구할 때마다 정보를 캐시해두는 방법을 쓰는 클래스의 멤버로 다음을 둘 수 있다.

```cpp
class CTextBlock { 
public:
    ...
    std::size_t length() const;
private:
    char *pText; 
    mutable std::size_t textLength; 
    mutable bool lengthIsValid; 
};
std::size_t CTextBlock::length() const {
    if (!lengthIsValid) { 
        textLength = std::strlen(pText); 
        lengthIsValid = true;
    }
    return textLength; 
}
```
mutable을 사용하는 이유 → const 함수안에서 뭔가 cache 처럼 사용할때 할당이 필요한데 이때 mutable을 사용해서 변경이 가능하도록 함.

[씹어먹는 C ++ - <4 - 6. 클래스의 explicit 과 mutable 키워드>](https://modoocode.com/253)
[[C++] mutable 키워드 :: 비트수준 상수성과 논리적 상수성](https://blog.naver.com/skout123/50143517472)