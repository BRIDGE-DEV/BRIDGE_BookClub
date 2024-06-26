## 15장 디자인 패턴과 프레임워크

디자인 패턴이란, 소프트웨어 설계에서 반복적으로 발생하는 문제에 대해 반복적으로 적용할 수 있는 해결 방법을 **디자인 패턴**이라고 부른다. 디자인 패턴의 목적은 설계를 재사용하는 것으로 다양한 변경을 다루기 위해 반복적으로 재사용할 수 있는 설계의 묶음이다.

디자인 패턴이 설계를 재사용하기 위한 것이라면 **프레임워크**는 설계와 코드를 함께 재사용하기 위한것이다. 프레임워크는 애플리케이션의 아키텍처를 구현 코드의 형태로 제공한다. 프레임워크가 제공하는 아키텍처가 요구사항에 적합하다면 다양한 환경에서 테스트를 거친 견고한 구현 코드를 쉽고 빠르게 재사용할 수 있다.

### 디자인 패턴과 설계 재사용

#### 소프트웨어 패턴

패턴이란 무엇인가를 논의할 때면 반복적으로 언급되는 몇 가지 핵심적인 특징이 있다.

- 패턴은 반복적으로 발생하는 문제와 해법의 쌍으로 정의된다.
- 패턴을 사용함으로써 이미 알려진 문제와 이에 대한 해법을 문서로 정리할 수 있으며, 이 지식을 다른 사람들과 의사소통할 수 있다.
- 패턴은 추상적인 원칙과 실제 코드 작성 사이의 간극을 메워주며 실질적인 코드 작성을 돕는다.
- 패턴의 요점은 패턴이 실무에서 탄생했다는 점이다.

하나의 실무 컨텍스트에서 유용하게 사용해 왔고 다른 실무 컨텍스트에서도 유용할 것이라고 예상되는 아이디어다. 아이디어라는 용어를 사용한 이유는 어떤 것도 패턴이 될 수 있기 때문이다. 프로젝트 실무 패턴, 디자인 패턴, 견습자 패턴 등 다양한 패턴이 존재한다.

*정말 중요한 단락으로 패턴이란 소프트웨어의 코드 영역에서만 존재하는 것이 아닌 더 넓은 반복적으로 나타나는 현상을 말한다.*

*개인적으로 가장 도움이 된 견습자 패턴은 `프로그래머의 길, 멘토에게 묻다.`라는 책에 등장한다.*

패턴은 한 컨텍스트에서 유용한 동시에 다른 컨텍스트에서도 유용한 '아이디어'다. 일반적으로 패턴으로 인정하기 위한 조건으로 `3의 규칙`을 언급한다. 이 규칙에 따르면 최소 세 가지의 서로 다른 시스템에 특별한 문제 없이 적용할 수 있고 유용한 경우에만 패턴으로 간주할 수 있다.

패턴이 지닌 가장 큰 가치는 경험을 통해 축적된 실무 지식을 효과적으로 요약하고 전달할 수 있다는 점이다. **패턴은 경험의 산물이다. 책상 위에서 탄생한 이론이나 원리와 다릴 패턴은 치열한 실무 현장의 역학관계 속에서 검증되고 입증된 자산이다.** 따라서 실무 경험이 적은 초보자라고 하더라도 패턴을 익히고 반복적으로 적용하는 과정 속에서 유연하고 품질 높은 소프트웨어를 개발하는 방법을 익힐 수 있다.

패턴이라는 추상화, 청킹을 통해 지식 전달과 커뮤니케이선의 수단으로 활용할 수 있기 때문에 패턴에서 이름은 매우 중요한 요소이다. "인터페이스 하나 추가하고 이 인터페이스를 구체화하는 클래스를 만든 후 객체의 생성자나 setter를 통해 할당하여 런타임에 알고리즘을 변경할 수 있게 하자."는 `STRATEGY` 패턴을 적용하자는 단순한 대화로 바뀐다.

패턴의 범위는 소프트웨어 개발과 직접적인 연관성을 가진 분석, 설계, 구현 영역만으로 한정되는 것은 아니다. 다양한 크기의 프로젝트 조직을 구성하는 방법, 프로젝트 일정을 추적하는 방법, 스토리 카드나 백로그를 통해 요구사항을 관리하는 방법과 같이 **반복적인 규칙을 발견할 수 있는 모든 영역이 패턴의 대상**이 될 수 있다.

패턴은 홀로 존재하지 않는다. 특정 패턴 내에 포함된 컴포넌트와 컴포넌트 간의 관계는 더 작은 패턴에 의해 서술될 수 있으며, 패턴들을 포함하는 더 큰 패턴 내에 통합될 수 있다. *모듈과 같은 느낌*

#### 패턴 분류

패턴을 분류하는 가장 일반적인 방법은 패턴의 범위나 적용 단계에 따라 아키텍처 패턴(Architecture Pattern), 분석 패턴(Analysis Pattern), 디자인 패턴(Design Pattern), 이디엄(Idiom)으로 구분하는 것이다.

4가지 중 가장 널리 알려진 것인 디자인 패턴으로 특정 정황 내에서 일반적인 설계 문제를 해결하며, 협력하는 컴포넌트들 사이에서 반복적으로 발생하는 구조를 서술한다. 디자인 패턴은 중간 규모의 패턴으로 특정한 설계 문제를 해결하는 것을 목적으로 하며, **프로그래밍 언어나 프로그래밍 패러다임에 독립적**이다.

디자인 패턴의 상위에는 소프트웨어의 전체적인 구조를 결정하기 위해 사용할 수 있는 **아키텍처 패턴**이 위치한다. 아키텍처 패턴은 미리 정의된 서브시스템들을 제공하고, 각 서브시스템들의 책임을 정의하며, 서브시스템들 사이의 관계를 조직화하는 가이드라인을 포함한다. 구체적인 소프트웨어 아키텍처를 위한 탬플릿을 제공하며 마찬가지로 언어나 프로그래밍 패러다임에 독립적이다.

디자인 패턴의 하위에는 **이디엄**이 위치한다. 이디엄은 특정 프로그래밍 언어에만 국한된 하위 레벨 패턴으로, 주어진 언어의 기능을 사용해 컴포넌트, 혹은 컴포넌트 간의 특정 측면을 구현하는 방법을 서술한다. 이디엄은 언어에 종속적이므로 특정 언어에선 무용지물이 되기도 한다. C++의 `COUNT POINTER`은 가비지 컬렉션 메커니즘을 가진 자바에서는 유용하지 않다.

위 3가지 패턴은 모두 기술적인 문제를 해결하는데 집중한다면 분석 패턴은 도메인 내의 개념적인 문제를 해결하는 데 초점을 맞춘다. 분석 패턴은 업무 모델링 시에 발견되는 공통적인 구조를 표현하는 개념들의 집합이다.

#### 패턴과 책임-주도 설계

객체지향 설계에서 가장 중요한 일은 올바른 책임을 올바른 객체에게 할당하고 객체 간의 유연한 협력 관계를 구축하는 일이다. **책임과 협력의 윤곽은 캡슐화, 크기, 의존성, 성능, 확장 가능성, 재사용성 등의 다양한 요소들의 트레이드 오프를 통해 결정된다.**

*이런 트레이드 오프의 능력이 좋은 개발자가 숙련된 개발자라고 생각한다.*

가끔씩 책임과 협력을 결정하는 작업이 손쉽게 진행될 때도 있지만 대부분의 경우에는 훌륭한 품질의 설계를 얻기 위해 많은 시간과 노력을 들여야만 한다.

예를 들어 `STRATEGY` 패턴은 다양한 알고리즘을 동적으로 교체할 수 있는 역할과 책임의 집합을 제공한다. `BRIDGE` 패턴은 추상화의 조합으로 인한 클래스의 폭발적인 증가 문제를 해결하기 위해 역할과 책임을 추상화와 구현의 두 개의 커다란 집합으로 분해한다. `OBSERVER` 패턴은 유연한 통지 메커니즘을 구축하기 위해 객체 간의 결합도를 낮출 수 있는 역할과 책임의 집합을 제공한다.

여기서 패턴의 세부적인 내용이 중요한 것이 아니다. 중요한 것은 특정한 상황에 적용할 수 있는 설계를 쉽고 빠르게 떠올릴 수 있다는 사실이다. 특정한 상황에 적용 가능한 패턴을 잘 알고 있다면 책임 주도 설계의 절차를 하나하나 따르지 않고도 시스템 안에 구현할 객체들의 역할과 책임, 협력 관계를 빠르고 손쉽게 구성할 수 있다.

**패턴의 구성 요소는 클래스가 아니라 '역할'이다.**

*매우 중요한 점으로 디자인 패턴을 공부할 때, 해당 클래스 자체를 이해하기 보다 해당 객체의 역할을 이해하고 현재 프로젝트에선 어떤 형태로 나올 것인지 생각해봐야 한다.*

#### 캡슐화와 디자인 패턴

몇 가지 이례적인 경우를 제외하고 널리 알려진 **대부분의 디자인 패턴은 협력을 일관성 있고 유연하게 만드는 것을 목적으로 한다.** 따라서 각 디자인 패턴은 특정한 변경을 캡슐화하기 위한 독자적인 방법을 정의하고 있다.

- 변경하지 않는 부분은 부모 클래스로, 변하는 부분은 자식 클래스로 분리함으로써 변경을 캡슐화하기 위해 합성이 아닌 상속을 사용하는 `TEMPLATE METHOD` 패턴
- 부모 클래스가 알고리즘의 기본 구조를 정의하고 구체적인 단계는 자식 클래스에게 정의하게 함으로써 변경을 캡슐화할 수 있는 디자인 패턴이다.
- 다만 합성보다 결합도가 높은 상속을 사용하여 `STRATEGY` 패턴과 같이 런타임에 객체의 알고리즘을 변경하는 것은 불가능하다.
- 하지만 알고리즘 교체와 같은 요구사항이 없다면 상대적으로 `STRATEGY` 패턴보다 복잡도를 낮출 수 있다는 면에서는 장점이라고 할 수 있다.

핸드폰 과금 시스템의 설계는 `DECORATOR` 패턴을 기반으로 한다. 객체의 행동을 동적으로 추가할 수 있게 해주는 패턴으로서 기본적으로 객체의 행동을 결합하기 위해 객체 합성을 사용한다. `DECORATOR` 패턴은 선택적인 행동의 개수와 순서에 대한 변경을 캡슐화할 수 있다.

디자인 패턴에서 중요한 것은 디자인 패턴의 구현 방법이나 구조가 아니다. 어떤 디자인 패턴이 어떤 변경을 캡슐화하는지를 이해하는 것이 중요하다. 그리고 각 디자인 패턴이 변경을 캡슐화하기 위해 어떤 방법을 사용하는지를 이해하는 것이 더 중요하다.

#### 패턴은 출발점이다

패턴은 출발점이지 목적지가 아니다. 많은 전문가들이 널리 요구되는 유연성이나 공통적으로 발견되는 특정한 설계 이슈를 해결하기 위해 적절한 디자인 패턴을 이용해 설계를 시작한다. 그러나 **패턴은 설계의 목표가 돼서는 안 된다.** 패턴은 단지 목표로 하는 설계에 이를 수 있는 방향을 제시하는 나침반에 불과하다.

**디자인 패턴이 현재의 요구사항이나 적용 기술, 프레임워크에 적합하지 않다면 패턴을 그대로 따르지 말고 목적에 맞게 패턴을 수정하라.**

패턴을 사용하면서 부딪히게 되는 대부분의 문제는 패턴을 맹목적으로 사용할 때 발생한다. 대부분의 패턴 입문자가 빠지기 쉬운 함정은 패턴을 적용하는 컨텍스트의 적절성을 무시한 채 패턴의 구조에만 초점을 맞추는 것이다.

*이 경험은 나에게 좋은 반면교사이기도 하다. 패턴 만능주의에 빠지지 않으려면 패턴을 먼저 공부하기 이전에 객체지향에 대한 이해가 바탕이 되어야 한다.*

**해결하려는 문제가 아니라 패턴이 제시하는 구조를 맹목적으로 따르는 것은 불필요하게 복잡하고, 난해하며, 유지보수하기 어려운 시스템을 낳는다.** 따라서 부적절한 상황에서 사용된 패턴으로 인해 소프트웨어의 엔트로피가 증가하는 부작용을 낳기 쉽다. **패턴을 남용하지 않기 위해서는 다양한 트레이드오프 관계 속에서 패턴을 적용하고 사용해본 경험이 필요하다.**

정당한 이유 없이 사용된 패턴은 설계를 복잡하게 만드는 장애물이다. 패턴은 복잡성의 가치가 단순성을 넘어설 때만 정당화돼야 한다. 패턴을 적용할 때는 항상 설계를 좀 더 단순하고 명확하게 만들 수 있는 방법이 없는지를 고민해야 한다.

또한 코드를 공유하는 사람들이 적용된 패턴을 알고 있어야 한다. 패턴을 알고 있는 사람들은 코드를 쉽게 이해할 수 있지만 그렇지 못한 사람들은 복잡한 구조로 인해 코드를 쉽게 이해할 수 없게 된다. 패턴을 적용할 때는 함께 작업하는 사람들이 패턴에 익숙한지 여부를 확인하고, 그렇지 않다면 설계에 대한 지식과 더불어 패턴에 대한 지식도 함께 공유하는 것이 필요하다.

### 프레임워크와 코드 재사용

#### 코드 재사용 대 설계 재사용

디자인 패턴은 프로그래밍 언어에 독립적으로 재사용 가능한 설계 아이디어를 제공하는 것을 목적으로 한다. 따라서 언어에 종속적인 구현 코드를 정의하지 않기 때문에 디자인 패턴을 적용하기 위해서는 설계 아이디어를 프로그래밍 언어의 특성에 맞게 가공해야 하고 매번 구현 코드를 재작성해야 한다는 단점이 있다.

재사용 관점에서 설계 재사용보다 더 좋은 방법은 결국 코드 재사용이다. 오랜 시간동안 컴포넌트 기반의 조립식 개발을 추구해왔지만 이는 이상적이고 적용하는 과정에서 여러 현실적인 문제점이 나타난다.

가장 이상적인 형태의 재사용 방법은 설계 재사용과 코드 재사용을 적절한 수준으로 조합하는 것이다. *(결국은 균형잡기)* 코드 재사용만을 강조하는 컴포넌트는 실패했다. 추상적인 수준에서의 설계 재사용을 강조하는 디자인 패턴은 재사용을 위해 매번 유사한 코드를 작성해야만 한다. 설계를 재사용하면서도 유사한 코드를 반복적으로 구현하는 문제를 피할 수 있는 방법은 프레임워크를 사용하는 것이다.

**프레임워크**란, '추상 클래스나 인터페이스를 정의하고 인스턴스 사이의 상호작용을 통해 시스템 전체 혹은 일부를 구현해 놓은 재사용 가능한 설계', 또는 '애플리케이션 개발자가 현재의 요구사항에 맞게 커스터마이징할 수 있는 애플리케이션의 뼈대'를 의미한다.

#### 상위 정책과 하위 정책으로 패키지 분리하기

**프레임워크의 핵심은 추상 클래스나 인터페이스와 같은 추상화라고 할 수 있다.** 그렇다면 추상 클래스와 인터페이스가 가지는 어떤 특징이 프레임워크의 재사용성을 향상시키는 것일까? 이 질문의 답은 일관성 있는 협력이라는 주제와 관련이 있다.

추상 클래스와 인터페이스가 일관성 있는 협력을 만드는 핵심 재료라는 것을 기억하자. **협력을 일관성 있고 유연하게 만들기 위해서는 추상화를 이용해 변경을 캡슐화해야 한다.** 그리고 협력을 구현하는 코드 안의 의존성은 가급적이면 추상 클래스나 인터페이스와 같은 추상화를 향하도록 작성해야 한다.

객체지향 이전의 구조적인 설계와 같은 전통적인 소프트웨어 개발 방법의 경우 상위 레벨 모듈이 하위 레벨 모듈에, 그리고 상위 정책이 구체적인 세부적인 사항에 의존하도록 소프트웨어를 구성한다. 하지만 상위 정책은 상대적으로 변경에 안정적이지만 세부 사항은 자주 변경된다.

만약 변하지 않는 상위 정책이 자주 변하는 세부사항에 의존한다면 변경에 대한 파급효과로 인해 상위 정책이 불안정해질 것이다. 그리고 **상위 정책이 세부 사항에 비해 재사용될 가능성이 높다.** 기본 정책과 부가 정책을 조합하는 규칙은 모든 요금 계산 시에 재사용돼야 하는 협력 패턴이다. 그에 비해 시간대별 방식으로 요금을 계산하거나 세금을 부과하는 것은 특수한 경우에만 사용되는 기본 정책과 부가 정책의 한 예라고 할 수 있다.

- 변하는 것과 변하지 않는 것들은 서로 다른 주기로 배포할 수 있도록 별도의 '배포 단위'로 분리해야 한다.
- 이를 위해 변하는 부분과 변하지 않는 부분을 별도의 패키지를 분리하는 것이다.

*C#은 네임스페이스와 같이 패키지단위로 관리하여 별도의 배포단위로 만들고, 더 나아가 개인만의 모듈을 구축하기도 한다.*

#### 제어 역전 원리

**상위 정책을 재사용한다는 것은 결국 도메인에 존재하는 핵심 개념들 사이의 협력 관계를 재사용한다는 것을 의미한다.** 객체지향 설계의 재사용성은 개별 클래스가 아니라 객체들 사이의 공통적인 협력 흐름으로부터 나온다.

그리고 그 뒤에는 항상 의존성 역전 원리라는 아주 강력한 지원군이 존재한다. **의존성 역전 원리는 전통적인 설계 방법과 객체지향을 구분하는 가장 핵심적인 원리다.** 의존성 역전 원리에 따라 구축되지 않은 시스템은 협력 흐름을 재사용할 수도 없으며 변경에 유연하게 대처할 수도 없다.

시스템이 진화하는 방향에는 항상 의존성 역전 원리를 따르는 설계가 존재해야 한다. **만약 요구사항이 빠르게 진화하는 코드에서 의존성 역전 원리가 적절하게 지켜지지 않고 있다면 그곳에는 변경을 적절하게 수용할 수 없는 하향식의 절차적인 코드가 존재할 수밖에 없다.**

의존성 역전 원리는 프레임워크의 가장 기본적인 설계 메커니즘이다. 의존성 역전은 의존성의 방향뿐만 아니라 제어 흐름의 주체 역시 역전시킨다. 앞서 설명한 것처럼 상위 정책이 구체적인 세부사항에 의존하는 전통적인 구조에서는 상위 정책의 코드가 하부의 구체적인 코드를 호출한다.

의존성을 역전시킨 객체지향 구조에서는 반대로 프레임워크가 애플리케이션에 속하는 서브클래스의 메서드를 호출한다. 따라서 프레임워크를 사용할 경우 개별 애플리케이션에서 프레임워크로 제어 흐름의 주체가 이동한다. 즉, 의존성을 역전시키며 제어 흐름의 주체 역시 역전된다. 이를 **제어 역전(IoC)**또는 **할리우드(Hollywood)** 원리라고 한다.

프레임 워크를 사용하게 되면 우리는 적절한 시점에 실행될 것으로 예상되는 코드를 작성할 뿐이다. 협력을 제어하는 것은 프레임워크이기 때문에 그저 프레임워크가 호출하는 코드를 작성해야 한다. 이것이 제어가 우리에게서 프레임워크로 넘어가 버린 것이다. 이것이 바로 제어 역전의 핵심이다.

### 느낀점

개인적으로 많이 공감이 가기도 하고 대부분 멘토님이 당부해주신 말씀들이 들어 있다. 디자인 패턴을 바라보는 마음가짐과 제어의 역전에 대한 이해가 가장 중요한 파트인 것 같다.

#### 논의사항

- 개발중인 시스템에서 디자인 패턴을 도입하는 시기에 대해서 같이 이야기해보면 좋을 것 같습니다.
