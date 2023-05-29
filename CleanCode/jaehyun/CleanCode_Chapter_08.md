8장 경계
=============
시스템에 들어가는 모든 소프트웨어를 직접 개발하는 경우는 드물다.
어떤 식으로든 외부 코드를 우리 코드에 깔끔하게 통합해야만 한다.

* 외부 코드 사용하기.
인터페이스 제공자와 사용자 사이에는 긴장이 존재한다.
패기지 제공자나 프레임워크 제공자는 적용성을 최대한 넓히려 애쓴다. 
반면, 사용자는 자신의 요구에 집중하는 인터페이스를 바란다. 
이런 긴장으로 인해 시스템 경계에서 문제가 생길 소지가 많다.

  외부 기능을 그대로 사용하면 모든 기능이 불필요하게 사용자에게 노출되고 유형을 제한 하기도 어렵다.
  제네릭스를 사용해도 불필요한 기능을 제공하는 문제는 해결이 안된다. 때문에 경계 인터페이스를 캡슐화 해서
  필요한 기능만 제공할 수 있다. 하지만 매번 그럴 필요가 있다는 것은 아니고 경계 인터페이스를 여기저기 넘기지 
  말라는 것이다.

* 경계 살피고 익히기.
외부 패키지 테스트가 우리 책임은 아니지만 우리가 사용할 코드를 테스트하는 편이 바람직하다.
곧바로 우리쪽 코드를 작성해 외부 코드를 호출하는 대신 먼전 간단한 테스트 케이스를 작성해 외부 코드를 
익히는 학습 테스트를 진행하면 좋다. 학습 테스트는 프로그램에서 사용하려는 방식대로 외부 API를 호출한다.
통제된 환경에서 API를 제대로 이해하는지 확인하는 셈이다. 학습 테스트는 API를 사용하려는 목적에 초점을 마춘다.

* log4j 익히기.

* 학습 테스트는 공짜 이상이다.
학습 테스트는 비용없이 필요한 지식만 확보하는 손쉬운 방법이다. 학습 테스트는 이해도를 높여주는 정확한 실험이다.
패키지 새 버전이 나온다면 학습 테스트를 돌려 차이가 있는지 확인하고 예상대로 도는지 검증한다.
학습이 필요 없더라도 실제 코드와 동일한 방식으로 인터페이스를 사용하는 테스트 케이스가 필요하다.
이런 경계 테스트가 있으면 패키지의 새 버전으로 이전하기 쉬워진다. 그렇지 않으면 낡은 버전을 필요 이상으로
오랫동안 사용하려는 유혹에 빠지기 쉽다.

* 아직 존재하지 않는 코드를 사용하기
경계와 관련해 또 다른 유형은 아는 코드와 모르는 코드를 분리하는 경계다.
우리 지식이 경계를 너머 미치지 못하는 코드 영역도 있다.
우리가 바라는 자체적인 인터페이스를 구현하면 인터페이스를 전적으로 통제할 수 있고 코드 가독성과 의도도 분명해진다.

* 깨끗한 환경
경계에서는 흥미로운 일이 많이 벌어진다. 변경이 대표적인 예다.
소프트웨어 설계가 우수하다면 변경하는데 많은 투자와 재작업이 필요하지 않다.
경계에 위치하는 코드는 깔끔히 분리한다. 또한 기대치를 정의하는 테스트 케이스도 작성한다.
통제 불가능한 외부 패키지에 의존하는 대신 통제가 가능한 우리 코드에 의존하는 편이 훨씬 좋다.

  외부 패키지를 호출하는 코드를 가능한 줄여 경계를 관리하자.
새로운 클래스로 경계를 감싸거나 ADAPTER 패턴을 사용해 우리가 원하는 인터페이스를 패키지가 제공하는
인터페이스로 변환하자. 어느 방법이든 코드 가독성이 높아지며, 경계 인터페이스를 사용하는 일관성도 높아지고
외부 패키지가 변했을 때 변경할 코드도 줄어든다.

 느낀점
=============
외부에서 가져다 쓰는 코드의 기능을 적절하게 제한할 필요가 있다는 생각은 못했던 것 같다.
아니면 내 꺼 만들기도 벅찬데 가져다쓰는 라이브러리까지 관리하고 싶지 않았던 걸지도 모르겠다..
어째든, 이번 기회에 이런 부분에도 신경을 쓸 필요가 있음을 알게되었다는 것 만으로 다행인듯 하다..


논의 사항
=============
외부 라이브러리 등을 사용할 때 내부 구현 코드까지 살펴보신 경험이 있으신지 궁금합니다.