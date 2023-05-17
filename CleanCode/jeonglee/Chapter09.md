## 9장 단위 테스트

TDD란, 테스트가 주도하는 개발이다.

서비스를 제작하기전 테스트를 먼저 만들고, 테스트를 통과하는 코드를 작성하는 것이다.

이런 플로우를 가지게 되면 이후에 구현부가 수정되어 세부동작이 달라져도 테스트만 통과한다면 시스템 자체의 문제가 없어지게 된다.

예제에선 테스트코드가 없는 개발이 불러올 수 있는 문제점을 보여준다.

현재의 개발추세는 애자일과 TDD덕택에 단위 테스트를 자동화하는 프로그래머가 많아졌다.

CI/CD, 데브옵스와 같이 게임쪽에서도 젠킨스 GameCI가 주목받고 있다.

### TDD 법칙 세 가지

1. 실패하는 단위 테스트를 작성할 때까지 실제 코드를 작성하지 않는다.
2. 컴파일은 실패하지 않으면서 실행이 실패하는 정도로만 단위 테스트를 작성한다.
3. 현재 실패하는 테스트를 통과할 정도로만 실제 코드를 작성한다.

위 세가지 규칙을 따르면 개발과 테스트가 대략 30초 주기로 묶인다.

아직 테스트코드를 주도적으로 짜본 경험이 없어서 이 세가지 법칙에 대해 감이 안집히는 것 같다.  

웹 상에서도 게임 개발에 TDD를 사용하는 예제가 적다보니 더욱 멀게 느껴진다.

### 깨끗한 테스트 코드 유지하기

역설적이게도 실제 코드베이스의 코드가 변경되면서 테스트 코드 마찬가지로 도메인이 원하는 형태로 변경되어야 한다.

그렇다면 테스트 코드도 앞서 다룬 유지보수를 위한 가독성 좋은 코드를 짜야한다는 결론이 나온다.

이 이야기에서 주는 교훈은 더러운 테스트 코드는 안짜는 것보다 못하다는 결론이다.

깨끗한 테스트 코드를 유지하기 위해선 코드 자체를 작고, 한가지 기능만 할 수 있도록 짜야한다.

> 테스트 코드는 실제 코드 못지 않게 중요하다.

*테스트는 유연성, 유지보수성, 재사용성을 제공한다.*

이런 이점을 제공하는 버팀목이 바로 **단위 테스트**이다.  

이유는 위에서 설명했듯이 테스트 케이스 코드가 있다면 변경이 두럽지 않다.

테스트 코드의 이점은 이 부분과 처음 설계를 유연하게 가져갈 수 있다는 점에서 매우 유용한 것 같다.

반대로 테스트 케이스가 없다면 모든 변경이 버그를 유발할 수 있는 가능성이 있고, 설계를 잘해도 변경을 두려워하게 된다.

### 깨끗한 테스트 코드

그렇다면 깨끗한 테스트 코드를 만드려면..?  

가독성, 가독성, 가독성이 가장 중요하다 (*3)

테스트 코드는 최소의 표현으로 많은 것을 나타내야 한다.

책에서 나오는 테스트 코드의 리팩터링 과정을 보니,,? 리팩터링 책도 빨리 읽어보고 싶다는 생각이 든다..

### 테스트 당 assert 하나

함수마다 assert문 단 하나만 사용해야 한다고 주장하는 사람도 있다.

아마 예상하기론 함수당 기능을 하나, 클래스당 기능을 하나만 가지는 것과 같은 이유가 아닐까 싶다..  

마찬가지로 비슷한 이점을 가지는데 assert문이 단 하나인 함수는 결론이 하나라서 코드를 이해하기 쉽다는 장점이 있다.

하지만 하나의 테스트 함수에 assert가 하나만 들어가지 못하는 경우도 있는데 이런 상충되는 부분을 쉽게 생각할 수 있는 것이 **테스트 당 개념 하나**이다.

#### 테스트 당 개념 하나

`테스트당 한 개념만 테스트하라`라는 규칙이 있다면 현재 작성한 코드에서 개념들을 분리할 수 있을 것이다.

이 과정에서 코드를 어떻게 설계할지, 재구성할지 조금 가닥이 잡히지 않을까?

### F.I.R.S.T

깨끗한 테스트 코드를 만들기 위한 다섯 가지 규칙이다.

- Fast: 테스트는 빨라야 한다.
- Independent: 각 테스트는 서로 의존하면 안된다.
- Repeatable: 테스트는 어떤 환경에서도 반복 가능해야 한다.
- Self-Validating: 테스트는 bool 값으로 결과를 내야 한다.
- Timely: 테스트는 적시에 작성해야 한다.

### 결론

사실상 TDD나 테스트 코드에 관한 내용은 책이 따로 있을 정도로 중요한 내용이라 이번 챕터에선 가볍게 다룬 것이 사실이다.

### 느낀점

테스트 코드, 테스트 코드 해서 조금 알아보고 내용 자체는 알고 있었지만 각 잡고 제대로 TDD개발을 해본적이 없어서 많이 아쉬운 것 같다.

웹상에서도 정보가 적어서.. 다음 북클럽에 TDD를 주제로 한 책을 읽어보면 좋을 것 같다.  

게임 개발자끼리 이런 내용을 실제 프로젝트에 적용해보며 공유하는 시간을 가지고 싶다..!

#### 논의사항

이런 분야의 새로운 패러다임을 공부할 때 어떻게 공부하는지 궁금합니다..!

좋은 접근방법이 있으면 같이 이야기 해보면 좋을 것 같습니다.