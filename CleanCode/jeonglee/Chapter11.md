## 11장. 시스템

> 복잡성은 죽음이다.  
> 개발자에게서 생기를 앗아가며, 제품을 계획하고 제작하고 테스트하기 어렵게 만든다.

### 도시를 세운다면?

도시를 세운다면 온갖 세세한 사항을 혼자서 직접 관리할 수 있을까?

한 사람의 힘으로는 절대 불가능하며 그럼에도 도시는 문제없이 돌아간다.

이는 각 분야로 나눠진 전문기관이 존재하기 때문이다.

또 다른 이유로는 적절한 추상화와 모듈화 때문이다.

그래서 큰 그림을 이해하지 못할지라도 개인과 개인이 관리하는 구성요소는 효율적으로 동작한다.

소프트웨어도 마찬가지로 팀을 도시처럼 구성해야 한다.  

하지만 팀이 제작하는 시스템은 비슷한 수준으로 관심사를 분리하거나 추상화를 이뤄내지 못한다.

깨끗한 코드를 구현하면 **낮은 추상화 수준에서 관심사를 분리하기 쉬워진다**.

### 시스템 제작과 시스템 사용을 분리하라

제작과 사용은 아주 다르다는 사실을 명심하라

> 소프트웨어 시스템은 (애플리케이션 객체를 제작하고 의존성을 서로 `연결`하는) 준비과정과 (준비 과정 이후에 이어지는) 런타임 로직을 분리해야 한다.

시작단계는 모든 애플리케이션이 풀어야 할 관심사이다.

불행히도 대다수 애플리케이션은 시작 단계라는 관심사를 분리하지 않는다.

- 초기화 지연
  - 실제로 객체가 필요할 때 초기화하여 객체를 생성하는 기법

초기화 지연은 사실 테스트 코드에 적합하지 않으며 단일 책임 원칙을 위반한다.

초기화 지연이 사용되는 기능 자체에는 크게 문제없지만 이러한 작은 단위의 `룰`들이 큰 스노우 볼을 만드는 법이다.

프로젝트마다의 컨벤션이 있는 이유도 마찬가지로 쳬계적이고 탄탄한 시스템을 만들고 싶다면 흔히 쓰는 좀스럽고 손쉬운 기법으로 모둘성을 깨서는 절대로 안 된다.

간단하게 초기화 지연을 예로 들었지만 이 부분은 사실 앞서 다룬 오용될 수 있는 부분을 없애는 것과 같은 맥락이다.

관심사를 분리하는 것부터 시작해야 프로그램에서 원하는 도메인을 잘 설계할 수 있다.

### Main 분리

시스템 생성과 시스템 사용을 분리하는 방법 중 하나는 `main`을 분리하는 것이다.

이러한 방법은 제어흐름을 따라가기 쉽고 모든 화살표가 한 방향을 가리키는 코드를 작성할 수 있게 해준다.

### 팩토리

객체의 생성이 런타임 도중에 결정되어야 하는 부분이 있다.

이 때 팩토리 메서드 패턴을 사용하면 생성하는 시점은 애플리케이션이 결정하지만 생성하는 코드는 전혀 모른다.

*추상수준으로 연결되어 있기 때문에*

### 의존성 주입(DI)

사용과 제작을 분리하는 강력한 메커니즘 중 하나는 **의존성 주입**이다.  

의존성 주입은 제어 역전기법을 의존성 관리에 적용한 메커니즘으로 제어 역전에서는 한 개체가 맡은 보조 책임을 새로운 객체에게 전적으로 떠넘긴다.

새로운 객체는 넘겨받은 책임만 맡으므로 단일 책임 원칙을 지키게 된다.

의존성 관리 맥락에서 객체는 의존성 자체를 인스턴스로 만드는 책임은 지지 않는다.

대신에 이런 책임을 다른 전담 메커니즘에 넘겨야만 한다.

그렇게 함으로써 제어를 역전한다.  

호출하는 객체는 실제로 반환되는 객체의 유형을 제어하지 않는다.

개신 호출하는 객체는 능동적으로 해결한다.

진정한 의존성 주입은 여기서 한 걸음 더 나간다.

클래스가 의존성을 해결하려 하지 않고 완전히 수동적인 형태를 가진다.

대신 의존성을 주입하는 방법으로 설정자 메서드를 통해 생성자 인수를 제공한다.

의존성 주입에 대한 심화내용이라 조금 어려울 수 있는 내용인 것 같다..

과거에 의존성 주입에 관해 정리한 내용을 첨부

![의존성 주입이란..?](https://fkdl0048.github.io/patterns/Patterns_DI/)

### 확장

군락은 마을로, 마을은 도시로 성장한다.

시스템도 마찬가지이다.

처음부터 모든 상황을 예측하고 완벽한 시스템을 만들 수는 없다..!

자동차를 만드는 그림이 있는데 처음에는 킥보드부터 시작해서 자전거, 오토바이, 자동차까지 확장되는 그림이다.

그렇다면 여기서 주는 교훈은 이런 변화를 유연하게 대체하기 위해선 생성과 사용을 분리하고, 컨벤션을 지키고, 수준을 낮고 작게 유지하는 것이 핵심이다.

이러한 개발 프로세스가 가장 돋보이는 것이 바로 TDD..

> 소프트웨어 시스템은 물리적인 시스템과 다르다.  
> 관심사를 적절히 분리해 관리 한다면 소프트웨어 아키텍처는 점지적으로 발전할 수 있다.

소프트웨어 시스템은 수명이 짧다라는 본질로 인해 아키텍처의 점진적인 발전이 가능하다.

### 횡단 관심사

영속성과 같은 관심사는 애플리케이션의 자연스러운 객체 경계를 넘나드는 경향이 있다.

모든 객체가 전반적으로 동일한 방식을 이용하게 만들어야 한다.

원론적으로는 모듈화되고 캡슐화된 방식으로 영속성 방식을 구상할 수 있다.

하지만 현실적으로는 영속성 방식을 구현한 코드가 온갖 객체로 흩어진다.

여기에 **횡단 관심사**라는 키워드가 나온다.

도메인 논리도 모듈화할 수 있다.

문제는 이 두 영역이 세밀한 단위로 겹친다는 것이다.

영속성을 예로 들면, 프로그래머는 영속적으로 저장할 객체와 속성을 선언한 후 영속성 책임을 영속성 프레임 워크에 위임한다.

아래는 자바에서 사용하는 관점 호근 관점 과 유사한 메커니즘 세 개를 살펴본다.

- **자바 프록시** : 객체를 감싸서 객체에 대한 접근을 제어한다.

내부 구현하는 방식을 보니.. `C#`에서는 리플렉션을 사용하여 좀 더 유연한 구조를 가져갈 수 있을 것 같다.

이후 등장하는 내용이 자바와 스프링에 관련된 세부사항 내용들이라 조금 아쉽다..

### 테스트 주도 시스템 아키텍처 구축

관점으로 관심사를 분리하는 방식은 그 위력이 막강하다.

즉, 코드 수준에서 아키텍처 관심사를 분리할 수 있다면 진정한 테스트 주도 아키텍처 구축이 가능해진다.

다시 말해, 아주 단순하면서 멋지게 우아하게 분리된 아키텍처로 소프트웨어 프로젝트를 진행해 결과물을 재빨리 출시한 후, 기반 구조를 추가하며 조금씩 확장해 나가는 괜찮다는 방식이다.

*애자일 방식..*

### 의사 결정을 최적화하라

모듈을 나누고 관심사를 분리하면 지엽적인 관리와 결정이 가능해진다.

도시든 소프트웨어 프로젝트든, 아주 큰 시스템에서 한 사람이 모든 결정을 내리기 어렵다.

가장 적합한 사람에게 책임을 맡기면 가장 좋다.

이 말이 몇몇 소프트웨어 개발자들이 공부하면서 인생의 많은 부분이 소프트웨어 개발론과 관련이 많다고 입을 모아 이야기 한다.

예술적, 기예적이라는 말도 많이 들어보고 문제를 해결하기 위한 최적의 방법을 계속 찾다보니 범용적으로 인간관계나 다른 문제를 해결할 때도 적용이 가능해진 듯 하다..

### 명백한 가치가 있을 때 표준을 현명하게 사용하라

표준을 사용하면 아이디어와 컴포넌트를 재사용하기 쉽고, 절절한 경험을 가진 사람을 구하기 쉬우며, 좋은 아이디어를 캡슐화하기 좋고, 컴포넌트를 엮기 쉽다.

하지만 이러한 표준을 만드는 시간이 너무 오래 걸려 기다리지 못한다.

### 결론

시스템은 역시 깨끗해야 한다.

깨끗하지 못한 아키텍처는 도메인 논리를 흐리며, 기민성을 떨어뜨린다.

도메인 논리가 흐려지면 제품 품질이 떨어진다.

버그가 숨어들기 쉬워지고, 스토리를 구현하기 어려워지는 탓이다.

모든 추상화 단계에서 의도는 명확히 표현해야 한다.

시스템을 설계하든 개별 모듈을 설계하든, 실제로 돌아가는 가장 단순한 수단을 사용해야 한다는 사실을 명심하자

### 느낀점

처음 구조를 잡는 방법에 있어서 사용과 생성을 분리하는 부분은 많이 도움이 된 것 같다.

중간에도 몇가지 생각을 적었지만 이 챕터에선 자바와 스프링에 대한 세부사항이 많아서 조금 아쉬웠다.

#### 논의사항

저는 요즘 설계를 할 때 모든 걸 예측할 수 없음을 깨닫고 열려있는 작은 단위로 코드를 많이 짜려고 노력하는데 앞서 나온 테스트코드나 좀 더 유연하고 확실하게 가져가는 방법들을 보니 조금 더 고민해봐야겠다는 생각이 들었습니다..

이번 챕터에서 하나만 제대로 챙겨가는 개념이 있다면 뭐가 있을까요?