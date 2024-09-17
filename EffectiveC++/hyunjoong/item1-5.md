
벌써 출간된지 10년이 된 오래된 책이네요. 내용이 핵심들을 잘 짚어주고 좋은 내용이 많아 아직도 인기 도서인 것 같습니다.

# 항목 1
항목 1은 딱히 얘기할만한 내용은 없는 것 같습니다.
다만 STL이라는 용어가 나오는데, STL은 정확히는 standard template library로 c++ 내장 standard library에 영향을 준 라이브러리입니다. c++에 들어있는 것은 standard library라고 합니다. 궁금하신 분들은 아래 링크를 읽어보시면 좋을 것 같네요.

https://en.wikipedia.org/wiki/Standard_Template_Library

https://learn.microsoft.com/en-us/cpp/standard-library/cpp-standard-library-overview?view=msvc-170
아래 note에 자세히 나와있습니다. msvc에서는 stl이라고 하지만 standard library의 준말이라고 합니다.

# 항목 2
C#과 c++의 가장 큰 차이 중 하나가 const의 의미라고 할 수 있습니다. C#에서는 const가 컴파일 타임 치환인데, c++에서는 불변(immutable)의 의미를 가지기 때문입니다. 그래서 C#의 const에 대응하는 것은 c++에서 constexpr(c++11 이상)이 되겠네요. 안타깝게도 옛날 책이라 그런지 constexpr에 대해 여기선 다루지 않지만 알아두면 좋을 것 같아 올려둡니다.

https://en.cppreference.com/w/cpp/language/constexpr

---

```cpp
static const int NumTurns = 5;
```
여기 부분도 흥미로웠습니다. 정의된(defined) 것이 아니라 선언된(declared)된 것이라는 점이 신기했습니다.

아래 링크에서도 보시면 static data member은 그냥 써 두면 정의가 아니라 선언만 된다고 하네요.

https://en.cppreference.com/w/cpp/language/definition

실제로 컴파일 해보면 링커에서 문제가 생깁니다.

```
Undefined symbols for architecture arm64:
  "GamePlayer::NumTurns", referenced from:
      _main in chapter2-3e12bc.o
ld: symbol(s) not found for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

책에서도 보면 주소를 가져가지 않는 한 문제가 없다고 하는데요, 실제로 -S 플래그로 어셈블리로 컴파일을 해 보면, &(address-of) 연산자를 달지 않으면 TEXT 섹션에 NumTurns를 알아서 만들어 주는데, 달기만 하면 만들어지지 않습니다.

왜 이런일이 일어나는지는 아무리 찾고 연구해봐도 알 수가 없었는데요.. 혹시 아시는 분이 계신다면 제보 바랍니다.

그리고 애초에 이런 경우에는 constexpr을 사용하면 이런 문제가 애초에 안생기므로 constexpr의 사용이 더 적절하다고 생각되네요.

어떤 컴파일러는 까다로워서 구현 파일에서 값을 초기화해줘야한다고 써 있는데,  이 역시 constexpr을 사용하면 무조건 헤더 파일에 클래스 안에 써야 하므로 고민이 하나 줄겠습니다.
또한 enum hack이라고 소개하는 것도 마찬가지로 constexpr로 해결되지만, 옛날 코드를 읽을 때를 대비해서 알아두면 좋겠습니다.

> tmi...
constexpr은 기본적으로 컴파일 타임 치환이지만, & 연산자로 주소를 얻어내면 알아서 TEXT 섹션 const에 하나 메모리 공간을 만들어줍니다. 그래서 enum hack은 enum이 rvalue라서 주소를 얻어낼 수 없지만, 여긴 가능하다는 차이가 있긴 합니다... 그래서 책에서 설명하는 쓸데없는 메모리 할당이 constexpr에서는 일어날 수도 있다는 차이가 있겠다만, 너무 hacky한 방법이라 저는 평소에 잘 쓸지 모르겠네요.

---

그다음은 preproc(전처리기)에 대한 이야기가 또 나오는데요, 역시 이렇게 a가 2번 증가하는 일은... 언제 봐도 머리가 아프네요. inline 함수나 이렇게 상수가 들어갈 때는 constexpr 함수를 사용하면 이런 골치아픈 일도 안녕이겠군요.

정리

#define 대신에
- constexpr을 쓰자
- inline을 (잘 따져보고) 쓰자
- enum hack의 존재를 알아두자

# 항목 3
iterator에 대한 이야기인데, 인간적으로 이걸 다 쓰면 코드도 지저분해지고 너무 읽기가 힘듭니다.

```cpp
const std::vector<int>::const_iterator cIter = vec.begin();
```

사실 이보다는 이렇게 쓰는걸 저는 선호합니다.

```cpp
const auto cIter = vec.cbegin();
```

cbegin()도 c++11부터 등장했고, auto도 마찬가지라서 책에서 소개하진 않았지만, 만약 그 당시에 있었다면 분명 소개했을 것이라고 생각합니다.

저도 왠만하면 const를 붙이는게 좋다는 것에 매우 동의합니다. 물론 짧은 로컬 변수까지 하는 건 코드도 더러워지고 좀 생략할 수도 있다는 생각은 듭니다. rust같이 기본적으로 const고 변경 가능한 것에 mut를 붙이는 방식이 그래서 참 좋다는 생각이 듭니다.

---
operator overloading은 정말 사람을 깜짝깜짝 놀라게 하는 것 같군요.. 이럴 때는 const를 붙이는 편이 확실히 더 좋겠네요.

매개변수도 const &로 하는것도 참 중요한 것 같습니다. const로 하는 것도요. 나중에 또 나오니깐 간단히 리마인드만 하고 넘어갑시다.

함수 뒤에 const를 붙여 const 함수로 만드는 것도 마찬가지로 참 중요한 것 같습니다. 일단 호출하는 입장에서도 side-effect를 생각하지 않아도 돼서 참 좋습니다. 컴파일러에게 최적화 기회도 제공합니다.
또 const를 붙이고 안붙이고가 책에서 나오듯 다른 함수 호출할때가 다르기도 하고 참 미묘하지만 중요한 부분이네요.

---

operator[]를 const와 non-const 버젼의 중복을 줄이는 얘기를 하는 부분입니다. (사실 저는 개인적으론 여기에서 로깅과 무결성 검증까지 했었어야 하는 생각이 들긴 합니다..) 이런 일이 일어날 수 있으니 알아두면 좋겠네요. \*this를 static_cast하는 트릭 배워갑니다.

정리
- 가능하면 항상 const를 쓰자.
- \*this를 static_cast해서 operator[] const를 호출한 방법을 알아두자.

# 항목 4

C#에서는 역시 int x, y;라고 쓰고 변수를 쓰려 하면 컴파일 에러가 뜹니다. 이 역시 c++과 가장 큰 차이 중 하나입니다. 이렇게 쓰면 그냥 현재 스택 프레임에 x와 y라는 오브젝트만 생성되고, 그 안에는 아무 값이나 들어가 있을 수 있습니다. 책에도 나오지만 중요한 부분이므로 짚고 넘어가 봅니다.

대입과 초기화가 다르다. 역시 별표를 치고 넘어가야겠네요.
특히 여기 예시에 나온 생성자의 경우도, 초기화, 대입을 모두 해서 메모리에 2번 쓰는 불상사가 일어나지 않도록 해야겠네요.

객체 초기화 순서도 매우 중요하니깐 책에 나왔지만, 한번 적으면서 한번 더 정리해 보겠습니다.
1. base 클래스는 derived 클래스보다 먼저 초기화된다
2. 클래스 데이터 멤버는 *선언된* 순서대로 초기화된다

스태틱도 마찬가지로 중요합니다. static storage duration에 들어가는 것들:
1. global object들과 namespace scope, file scope static인 친구들
2. static members
3. 함수 안의 static objects (local static)

translation unit도 매우 중요한 개념이죠. preproc(전처리)가 끝난 상태가 하나의 translation unit이죠.

서로 다른 translation unit끼리는 초기화 서순은 알 수 없다. (Unity에서 Awake 서순이 미정의된거랑 같죠.) Local static은 해당 블럭에 처음 들어가기 전에 초기화된다. 이것만 머리에 넣어두고 넘어가면 될 듯 합니다.

쓰레딩에 대한 이야기가 그 다음 나오는데, c++11에 추가된 thread_local을 사용하면 해결될 문제라고 생각됩니다.

정리
- 대입과 초기화는 다르다
- 초기화 리스트를 잘 쓰자
- 다른 translation unit끼리는 static object 초기화 순서는 알 수 없다

# 항목 5
생성자, 소멸자, 대입연산자. c++의 가장 중요한 부분이자 동시에 가장 골치아픈 부분이죠. c++11부터 추가된 이동 대입 연산자와 이동 생성자까지 합하면...

책에 나온 내용은 아니지만, (복사 생성자, 복사 대입 연산자, 소멸자) 3개를 항상 묶어서 외워 봅시다. 이 셋 중 하나라도 내가 써야 한다면 나머지도 왠만하면 써야한다. 이를 rule of three라고 하죠. 여기에 이동 semantic을 써야 한다면 5개를 다 써야한다가 rule of five이고요. 애초에 다섯 중 하나라도 안써도 되면 쓰지 않는게 정신건강에 좋다가 rule of zero이죠.

https://en.cppreference.com/w/cpp/language/rule_of_three

예제에 나온 NamedObject도 굉장히 흥미로운 예시네요. const와 &reference로 만들면 c++11 이상에서는 다음과 같은 컴파일 에러가 나옵니다.
```
Object of type 'NamedObject<int>' cannot be assigned because its copy assignment operator is implicitly deleted [ovl_deleted_special_oper]
```
컴파일러가 자동으로 생성자도 만들어주고, 복사 생성자/연산자도 만들어 주지만, 특정 상황에서는 삭제한다는 얘기입니다. 지금처럼 non-static data member이고, const인 non-class type(int)일 경우, 또 reference type의 멤버가 있을 경우입니다. 그리고 자잘한 경우가 더 있는데, 더 자세한건 아래 링크에 더 있고 머리에 항상 넣어둘 필요는 일단 없는 것 같네요.

https://en.cppreference.com/w/cpp/language/copy_assignment

정리
- 기본 생성자랑, (복사 생성자, 복사 대입 연산자, 소멸자)는 암시적으로(implicitly) 컴파일러가 만들어줄 수 있다.

- non-static, **const-qualified, non-class** data member가 있거나
- non-static **reference type** data member가 있으면
- 복사 대입 연산자는 안만들어진다. (정확히는 = delete)


