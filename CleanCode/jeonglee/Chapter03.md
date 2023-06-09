## 3장 함수

예제에서 주어진 함수가 읽기 쉽고 이해하기 쉬운 이유는 무엇일까?  

의도를 분명히 표현하는 함수를 어떻게 구혀할 수 있을까?  

함수에 어떤 속성을 부여해야 사람이 프로그램 내부를 직관적으로 파악할 수 있을까?  

### 작게 만들어라  

함수를 만드는 첫째 규칙은 '작게!'다. 함수를 만드는 둘째 규칙은 '더 작게!'다.  

이 규칙에 대해서는 매우 동의한다..  

`프로그래머의 뇌`라는 코드를 잘 읽는 방법에도 나오지만 사람은 생각보다 더 멍청하기 때문에 메모리와 하드디스크에 비유하여 읽을 수 있는 한계량이 정해진다.  

`LTM`, `STM`으로 읽을 때 함수의 길이가 5줄, 10줄 이상으로 길어지면 이해가 안되는 순간 다시 위로 올라가야 하기 때문에 함수를 작성할 때 사람이 읽는 순서, 맥락을 만지는 것이 중요하다.  

너무 길다 싶으면 분활하여 작성하는 것이 현명..  

앞서 말한 한가지 역할을 하는 클래스는 한가지 역할을 하는 함수와 같다.  

하지만 작성된 여러가지 객체들과 협력하여 프로그램이 동작하는 것.  

### 한 가지만 해라  

> "함수는 한 가지를 해야 한다. 그 한 가지를 잘 해야 한다. 그 한가지만을 해야 한다."  

여기서 한가지의 개념을 명확하게 해야한다.  

이는 **지정된 함수 이름 아래에서 추상화 수준이 하나인 단계만 수행**한다면 그 함수는 한 가지 작업만 한다.  

우리가 함수를 만드는 이유는 큰 개념을 다음 추상화 수준에서 여러 단계로 나눠 수행하기 위해서다.  

또 다른 방법으로 의미있는 이름으로 다른 함수를 추출할 수 있다면 그 함수는 여러가지 작업을 하는 셈이다.  

이름이 진짜 핵심..  

### 함수 당 추상화 수준은 하나로  

함수가 확실히 `한 가지`작업만 하려면 함수 내 모든 문장의 추상화 수준이 동일해야 한다.  

한 함수 내에 추상화 수준을 섞으면 코드를 읽는 사람이 헷갈린다.  

특정 표현이 근본 개념인지 아니면 세부사항인지 구분하기 어려운 탓이다.  

근본 개념과 세부사항을 뒤섞기 시작하면, 깨어진 창문처럼 사람들이 함수에 세부사항을 점점 더 추가한다.  

깨진 유리창 이론..

*함수 당 추상화 수준은 하나라는.. 생각을 안해봐서 예제를 보니 감동받았다.. 명심할 것*  

### 위에서 아래로 코드 읽기: 내려가기 규칙

코드는 위에서 아래로 이야기처럼 읽혀야 좋다.  

함 함수 다음에는 추상화 수준이 한 단계 낮은 함수가 온다.  

즉, 위에서 아래로 프로그램을 읽으면 함수 추상화 수준이 한 번에 한 단계씩 낮아진다.  

이를 **내려가기**규칙이라고 부른다.  

함수만 적용되는 규칙이 아니라 코드를 위에서 아래로 읽기 때문에 클래스 단위에서도 적용되어야 한다.  

물론 클래스가 함수의 개념 자체가 유사할 수 있지만..  

#### Switch 문  

switch 문은 작게 만들기 어렵다.  

case분기가 두 개 이상이라도 길고 한 가지 작업만 하는 switch문도 만들기 어렵다.  

switch문을 완전히 피할 방법은 없지만 각 switch문을 저차원 클래스에 숨기고 절대로 반복하지 않는 방법이 있다.  

이 예제에 관해서 공부한 적이 있다.  

`팩토리 메서드 패턴`이 예제인 경우 같은데..  

따로 글을 쓰기보다 전에 썼던 글을 첨부한다.

<https://fkdl0048.github.io/patterns/Patterns_FactoryMethod/>

DI와 인터페이스를 사용해 추상화 수준을 높여서 관리하는 방법이다.

다형적 객체를 생성하는 코드안에서 switch문을 꼭 사용하는 것 보다 위 링크의 방법을 사용하는 것이 더 좋을 수 있다..  

### 서술적인 이름을 사용하라  

서술적인 이름을 사용하기 위해선.. 영어를 잘해야 할 것 같다..  

좋은 이름이 주는 가치는 아무리 강조해도 지나치지 않다..  

> "코드를 읽으면서 짐작했던 기능을 각 루틴이 그대로 수행한다면 깨끗한 코드라 불러도 되겠다."  

확실히 짧은 이름을 가진 함수들은 해당 클래스가 성격을 나타낸다고 해도 쉽게 오용될 수 있다.  

이름이 서술적일 경우엔 해당 기능을 예측하고 해당 기능대로 동작하기 때문에 읽기 쉽다.  

이를 실현하려면 앞 서 말한 함수는 작아야 하고 한 기능만을 수행해야 한다.

서술적인 이름을 사용하면 개발자 머릿속에서도 설계가 뚜렷해지므로 코드를 개선하기 쉬워진다.  

이름을 붙일 땐 일관성이 있어야 한다.  

모듈 내에서 함수 이름은 같은 문구, 명사, 동사를 사용한다.  

includeSetupPage, includeSetupAndTeardownPages 처럼..  

### 함수 인수  

함수에서 이상적인 인수의 개수는 0개(무항)이다..  

다음은 1개(단항)이고, 다음은 2개(이항)이다..  

3개 이상은 가능한 피하는 편이 좋다.  

4개 이상은 특별한 이유가 필요하고 있더라도 사용해서는 안된다.  

**인수는 어렵다. 인수는 개념을 이해하기 어렵게 만든다.**  

만약 인수로 함수를 넘긴다면 해당 코드를 읽는 사람은 해당 코드가 어떤 동작을 하는지 알아야 한다.  

이는 함수 당 추상화 수준 자체를 바꿔버릴 수 있다.

이런 인수를 줄이는 방법에는 여러가지가 있지만 `C#`의 선택적 매개변수 기능을 추천한다.  

#### 많이 쓰는 단항 형식  

함수에 인수 1개를 넘기는 가장 흔한 이유는 두가지다.  

1. 인수에 질문을 던지는 경우  

       boolean fileExists("MyFile");

2. 인수를 변형하는 경우  

       InputStream fileOpen("MyFile");

이 두 가지 경우는 읽을 때 당연하게 받아들인다.  

해당 함수의 동작 과정 자체가 이해가 되고 결과 값도 명확하기 때문  

이벤트 함수에 관련한 내용이 나오는데..  

이벤트 기반 프로그래밍 같은 패러다임도 있는 만큼 유용한 건 사실이다.  

`C#`에서도 많이 사용하고 `On`과 같은 접두사를 붙여서 명확하게 드러낸다.  

위에서 말한 경우가 아닌 단항함수는 피해야 한다.  

#### 플래그 인수  

**플래그 인수는 추하다.**  

함수가 한꺼번에 여러 가지를 처리한다고 대놓고 공표하는 셈이라 플래그가 참이면 이걸 하고 거짓이면 저걸한다는 말이니까..  

#### 이항 함수  

인수가 2개인 함수는 인수가 1개인 함수보다 이해하기 어렵다..  

이항함수가 필요한 경우도 있지만 이항함수는 말 그대로 이해해야 하는 영역이 두가지가 추가된 것이다.  

STM에 정보를 2개를 더 넣어야 하는 만큼 읽을 수 있는 영역이 줄어든다.  

그렇다고 무조건 나쁘다는 것은 아니고 불가피한 경우도 생긴다.  

하지만 그 만큼 위험이 따른다는 사실을 이해하고 가능하면 단항함수로 바꾸도록 애써야 한다.  

#### 삼항 함수  

인수가 3개인 함수는 당연하게 2개보다 이해하기 어렵다.  

여기서 부터는 고칠 것을 권장보다 권고..  

#### 인수 객체  

인수가 2~3개 필요하다면 일부를 독자적인 클래스 변수로 선언할 가능성을 짚어본다.  

```cs
Circle makeCircle(double x, double y, double radius);

Circle makeCircle(Point center, double radius);
```

위 두 함수는 동일한 기능을 수행하지만 두번째 함수가 더 이해하기 쉽다.

#### 인수 목록

때로는 인수 개수가 가변적인 함수도 필요하다.  

가변 인수를 취하는 모든 함수에 같은 원리가 적용된다.  

가변 인수를 취하는 함수는 단항, 이항, 삼항 함수로 취급할 수 있다.  

가변인수.. c프로그래밍 할 때 이후로 처음 본다.  

시스템적인 부분을 설계할 때는 필요할 것 같은데..

#### 동사와 키워드

함수의 의도나 인수의 순서와 의도를 제대로 표현하려면 좋은 이름이 필수다.  

단항 함수는 함수와 인수가 동사/명사 쌍을 이뤄야 한다.  

예를 들어, write(name)은 곧바로 이해한다.  

이름을 쓴다라는 뜻이지만 좀 더 좋은 이름은 writeField(name)이다.  

그러면 이름이 필드라는 사실이 분명하게 드러난다.  

다른 예제로 함수 이름에 키워드를 넣는 방식이다.  

assertEquals보다 assertExpectedEqualsActual이 더 좋다.  

(expected, actual) 순서로 인수를 넘기는 것도 좋다.  

그러면 인수 순서를 기억할 필요가 없이 함수 이름만 보고도 이해할 수 있다.  

*이렇게 사용하고 싶은데 왜 이렇게 어렵지,,*  

### 부수 효과를 일으키지 마라

부수 효과(Side Effect)는 거짓말이다.  

함수에서 한 가지를 하겠다고 약속하고선 남몰래 다른짓도 하니까..  

때로는 예상치 못하게 클래스 변수를 수정한다.  

때로는 함수로 넘어온 인수나 시스템 전역 변수를 수정한다.  

어느 쪽이든 교활하고 해로운 거짓말이다.  

이는 **시간적인 결합**이나 **순서 종속성**을 초래한다.  

앞에서 다룬 플래그 인수나 전역 변수들이 이런 부수 효과를 일으키는 주범이다.  

#### 출력 인수

일반적으로 우리는 인수를 함수 입력으로 해석한다.  

인수를 출력으로 사용하는 경우는 거의 없지만 `C#`은 이런 경우를 위해 `out` 키워드를 제공한다.  

사실 객체지향적인 코딩을 지향한다면 이런 경우는 거의 없을 것이다.  

appendFooter(s) 함수가 있다고 가정하자.  

report.appendFooter(s)가 더 자연스럽다.  

일반적으로 출력 인수는 피해야 한다.  

함수에서 상태를 변경해야 한다면 함수가 속한 객체 상태를 변경하는 방식을 택한다.  

### 명령과 조회를 분리하라  

함수는 뭔가를 수행하거나 뭔가에 답하거나 둘 중 하나만 해야 한다.  

둘 다 하면 안된다.  

명령과 조회를 명확하게 구분 한다면 함수 자체를 오용할 일이 없다.  

오용은 side effect를 일으키는 주범이다.

오용을 예방하기 위해선 명령과 조회를 분리해야 한다.. ++ 위에서 말한 규칙들

### 오류 코드보다 예외를 사용하라

명령 함수에서 오류 코드를 반환하는 방식은 명령/조회 분리 규칙을 미묘하게 위반한다.  

오류 코드 대신 예외를 사용하면 오류 처리 코드가 원래 코드에서 분리되므로 코드가 깔끔해진다.

#### try/catch 블록 뽑아내기  

try/catch 블록은 원래 추하다..?!

코드 구조에 혼란을 일으키며, 정상 동작과 오류 처리 동작을 뒤섞는다.  

그러므로 try/catch 블록을 별도의 함수로 뽑아내는 편이 좋다.  

#### 오류 처리도 한 가지 작업이다  

함수는 `한 가지` 작업만 해야 한다.  

오류 처리도 `한 가지` 작업에 속한다.  

그러므로 오류를 처리하는 함수는 오류만 처리해야 마땅하다.  

함수에 try가 있다면 catch/finally도 함께 있어야 한다.  

예제에서 처럼 오류를 enum값으로 들고 있게 되면 의존성이 생기게 되고 재컴파일/재배치가 이뤄져야 한다.  

하지만 예외는 Exception 클래스를 상속받아서 만들 수 있기 때문에 이런 문제가 발생하지 않는다.

### 반복하지 마라

중복은 문제다.

코드 길이가 늘어날 뿐 아니라 알고리즘이 변하면 연관된 코드를 전부 고쳐야 한다.  

상속도 이런 측면에서 나온 개념이겠지만.. 많이 이야기하는 상속의 문제점들도 남은 챕터들에서 해결되면 좋겠다..

AOP, OOP모두 이러한 중복 제거 전략이다.  

### 구조적 프로그래밍

구조적 프로그래밍 원칙 중 모든 함수와 함수 내 모든 블록에 입구와 출구가 하나만 존재해야 하는 원칙이 있다.

즉, 함수는 return문이 하나여야 한다는 말이다.  

해당 함수에서 발생할 수 있는 다른 return은 또 다른 함수로 분리..  

루프 안에서 break나 continue를 사용해서는 안되거 goto는 절대로 안된다.  

구조적 프로그래밍의 목표와 규율에는 공감하지만, 함수가 작다면 그렇게 큰 이익을 제공하지 못한다.

그러므로 함수를 작게 만다는다면 사용해도 괜찮다.. *goto는 나가라!*

### 함수를 어떻게 짜죠?

소프트웨어를 짜는 행위는 글짓기와 비슷하다.  

논문이나 기사를 작성할 때는 먼저 생각을 기록한 후 읽기 좋게 다듬는다.  

초안은 대게 서투르고 어수선하므로 원하는 대로 읽힐 때까지 맣을 다듬고 고치고 문단을 정리한다.  

함수를 짤 때도 마찬가지다.  

처음에는 길고 복잡하지만 서투른 코드가 많지만 그런 코드들을 단위 테스트 케이스로 만든 뒤 코드를 다듬고 함수를 만들고, 이름을 바꾸고, 메서드의 순서를 바꾸고, 클래스를 쪼갠다.  

이와중에도 단위 테스트는 통과한다.  

이게 TDD의 핵심아닐까.. 기능을 동작하게 만든 뒤 테스트를 통과시킨다.  

이후에 리팩터링을 하면서 실시간으로 유닛테스트를 거치면 문제가 될 수 없다..  

하지만 이런 방법은 처음부터 쉽게 할 수 있는 과정이 아니며, 궤도에 오르고 스스로 성장한다고 느끼며 계속 벽을 마주해야 한다.  

피하지 말고 극복해야 한다.  

### 결론  

모든 시스템은 특정 응용 분야 시스템을 기술할 목적으로 프로그래머가 설계한 도메인 특화 언어DSL로 만들어진다.  

함수는 그 언어에서 동사며, 클래스는 명사다.  

프로그래밍의 기술은 언제나 언어 설계의 기술이다..  

대가 프로그래머는 시스템 프로그램이 아니라 이야기로 여긴다.  

프로그래밍 언어라는 수단으로 좀 더 풍부하고 좀 더 표현력이 강력한 언어를 만들어 이야기를 풀어간다.  

> "여러분이 작성하는 함수가 분명하고 정확한 언어로 깔끔하게 같이 맞아떨어져야 이야기를 풀어가기가 쉬워진다는 사실을 기억하기 바란다."  

### 느낀점

가장 중요한 챕터가 아닐까 싶다..  

객체지향적 설계뿐만 아니라 가장 기본이 되는 코드를 작성하는 방법들을 알려줘서 제일 읽을 때 영양가가 있었다.  

물론 이미 나름 지키고 있는 룰도 있고 알고 있지만 지키고 있지 않은 방법, 처음 알게된 방법들도 있어서 좋았다..!

#### 논의사항

사이드 이펙트를 경험해보셨다면 해당 이야기를 들어보고 싶습니다..!

저는 전역 상태와 각 객체마다 상태를 따로둬서 같은 상태값을 두개로 분리했었는데 이후에 오용되거나 헷갈려서 발생하는 사이드 이펙트를 경함한 적이 있습니다..  

찾기 정말 힘들었던 기억이..
