﻿11장 시스템
=============
"복잡성은 죽음이다. 개발자에게서 생기를 앗아가며, 제품을 계획하고 제작하고 테스트하기 어렵게 만든다."

* 도시를 세운다면?
도시가 잘 돌아가는 이유는 각 분야를 관리하는 팀이 있기 때문이다. 큰 그림을 그리는 사람들도 있으며 작은 사항에 집중하는 사람들도 있다. 또 다른 이유는 적절한 추상화와 모듈화 때문이다. 그래서 큰 그림을 이해못해도 개인과 개인이 관리하는 구성요소는 효율적으로 돌아간다.
흔히 소프트웨어 팀도 도시처럼 구성한다. 그런데 팀이 제작하는 시스템은 비슷한 수준으로 관심사를 분리하거나 추상화를 이뤄내지 못한다. 깨끗한 코드를 구현하면 낮은 추상화 수준에서 관심사를 분리하기 쉬워진다. 이 장에서는 높은 추상화 수준, 즉 시스템 수준에서도 깨끗함을 유지하는 방법을 살펴본다.

* 시스템 제작과 시스템 사용을 분리하라.
제작은 사용과 아주 다르다는 사실을 명심한다. 소프트웨어 시스템은 준비 과정과 런타임 로직을 분리해야 한다. 
시작 단계는 모든 애플리케이션이 풀어야 할 관심사다. 관심사 분리는 우리 분야에서 가장 오래되고 중요한 설계 기법 중 하나다. 불행히도 대다수 애플리케이션은 시작 단계라는 관심사를 분리하지 않는다. 준비 과정 코드를 주먹구구식으로 구현할 뿐만 아니라 런타임 로직과 마구 뒤섞는다.
체계적이고 탄탄한 시스템을 만들고 싶다면 흔히 쓰는 좀스럽고 손쉬운 기법으로 모듈성을 깨서는 절대로 안 된다. 객체를 생성하거나 의존성을 연결할 때도 마찬가지다. 설정 논리는 일반 실행 논리와 분리해야 모듈성이 높아진다. 또한 주요 의존성을 해소하기 위한 방식, 즉 전반적이며 일관적인 방식도 필요하다.

* Main 분리.
시스템 생성과 시스템 사용을 분리하는 한 가지 방법으로, 생성과 관련한 코드는 모두 main이나 main이 호출하는 모듈로 옮기고, 나머지 시스템은 모든 객체가 생성되었고 모든 의존성이 연결되었다고 가정한다. main 함수에서 시스템에 필요한 객체를 생성한 후 이를 애플리케이션에 넘긴다. 애플리케이션은 그저 객체를 사용할 뿐이고, 모든 객체가 적절히 생성되었다고 가정한다.

* 팩토리.
때로는 객체가 생성되는 시점을 애플리케이션이 결정할 필요도 생긴다. 추상 팩토리 패턴을 사용하면 생성 시점은 애플리케이션이 결정하지만 코드는 모르게 할 수 있다.

* 의존성 주입.
사용가 제작을 분리하는 강력한 메커니즘 하나가 의존성 주입(DI)이다. 의존성 주입은 제어 역전 기법을 의존성 관리에 적용한 메커니즘이다. 

* 확장.
'처음부터 올바르게' 시스템을 만들 수 있다는 믿음은 미신이다. 필요에 따라 확장할 수 있게 만드는게 중요하다. TDD, 리팩터링으로 얻어지는 깨끗한 코드는 코드 수준에서 시스템을 조정하고 확장하기 쉽게 만든다.
소프트웨어 시스템은 물리적인 시스템과 다르다. 관심사를 적절히 분리해 관리한다면 소프트웨어 아키텍처는 점진적으로 발전할 수 있다. 소프트웨어 시스템은 '수면이 짧다'는 본질로 인해 아키텍처의 점진적인 발전이 가능하다.

  + 횡단 관심사.
  원론적으로 모듈화되고 캡슐화된 방식으로 영속성 방식을 구상할 수 있다. 하지만 현실적으로는 영속성 방식을 구현한 코드가 온갖 객체로 흩어진다. 여기서 횡단 관심사라는 용어가 나온다.

* 테스트 주도 시스템 아키텍처 구축.
코드 수준에서 아키텍처 관심사를 분리할 수 있다면, 진정한 테스트 주도 아키텍처 구축이 가능해진다. 그때그때 새로운 기술을 채택해 단순한 아키텍처를 복잡한 아키텍처로 키워갈 수도 있다. BDUF(구현을 시작전에 앞으로 벌어질 모든 상항을 설계하는 기법)를 추구할 필요가 없다. 오히려 해롭다. 처음에 쏟은 노력을 버지리 않으려는 심리적 저항으로, 처음 선택한 아키텍처가 향후 사고 방식에 미치는 영향으로 변경을 쉽사리 수용하지 못한다.
그렇다고 아무 방향 없이 프로젝트에 뛰어들어도 좋다는 소리는 아니다. 일반적인 구조는 생각하되 변하는 환경에 대처해 진로를 변경할 능력도 반드시 유지해야 한다.

* 의사 결정을 최적화하라.
모듈을 나누고 관심사를 분리하면 지엽적인 관리와 결정이 가능해진다. 가장 적합한 사람에게 책임을 맡기면 가장 좋다. 가능한 마지막 순간까지 결정을 미루는 방법이 최선이라는 사실을 까먹곤한다. 최대한 정보를 모아 최선의 결정을 내리기 위해서다.

* 명백한 가치가 있을 때 표준을 현명하게 사용하라.
아주 과장되게 포장된 표준에 집착하는 바람에 고객 가치가 뒷전으로 밀려난 사례를 많이 봤다. 표준을 사용하면 아이디어와 컴포넌트를 재사용하기 쉽고, 적절한 경험을 가진 사람을 구하기 쉬우며, 좋은 아이디어를 캡슐화하기 쉽고, 컴포넌트를 엮기 쉽다. 하지만 때로는 표준을 만드는 시간이 너무 오래 걸려 업계가 기다리지 못한다. 어떤 표준은 원래 표준을 제정한 목적을 잊어버리기도 한다.

* 시스템은 도메인 특화 언어가 필요하다.
좋은 DSL은 도메인 개념과 그 개념을 구현한 코드 사이에 존재하는 의사소통 간극을 줄여준다. 효과적으로 사용한다면 DSL은 추상화 수준을 코드 관용구나 디자인 패턴 이상으로 끌어올린다.

* 결론.
시스템 역시 깨끗해야 한다. 모든 추상화 단계에서 의도는 명확히 표현해야 한다. 시스템을 설계하든 개별 모듈을 설계하든, 실제로 돌아가는 가장 단순한 수단을 사용해야 한다는 사실을 명심하자.


느낀점
=============
시스템과 아키텍처 부분도 지식이 깊지 않아 잘 이해한건지 모르겠다. 이번 장도 나중에 다시 읽어볼 필요가 있어보인다.
그렇지만 확장에 관한 부분은 흥미로웠다. 처음부터 너무 먼 미래를 생각해서 설계가 어려웠던 점도 있었다. 하지만 애초에 처음부터 모든 상황을 고려하는건 좋지도 않고 가능한지도 모르겠다. 소프트웨어는 설계를 변경해 나갈 수 있는 분야고 이를 이를 이용해야 한다는 생각이 흥미로웠다.
  

논의 사항
=============
게임 설계에 대해 어떤 식으로 공부하셨는지 궁금합니다.
