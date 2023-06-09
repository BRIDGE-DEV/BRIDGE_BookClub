﻿10장 클래스
=============
* 클래스의 체계.
클래스를 정의하는 표준 자바 관례에 따르면, 가장 먼저 변수 목록이 나온다.
정적 공개 상수, 정적 비공개 변수, 비공개 인스턴스 변수 순서로 나오며 공개 변수가 필요한 경우는 거의 없다. 변수 목록 다음에는 공개 함수, 비공개 함수는 자신을 호출하는 공개 함수 직후에 넣는다. 즉, 추상화 단계가 순차적으로 내려간다. 신문 기사처럼.
   +  캡슐화.
   변수와 유틸리티 함수는 가능한 공개하지 않는 편이 낫지만 반드시 숨겨야 한다는 법칙도 없다. 테스트 코드가 함수를 호출하거나 변수를 사용해야 한다면 그 함수나 변수를 protected로 선언하거나 패키지 전체를 공개한다. 하지만 그 전에 비공개 상태를 유지할 온갖 방법을 강구한다. 캡슐화를 풀어주는 결정은 언제나 최후의 수단이다.

* 클래스는 작아야 한다!
클래스를 만들 때 첫 번째 규칙은 크기다. 클래스는 작아야 한다.
클래스도 함수와 마찬가지로 작게가 기본 규칙이다. 함수는 물리적인 행 수로 크기를 측정했다. 클래스는 다른 척도인 맞는 책임을 센다. 행이 짧고 메서드가 적어도 책임이 많으면 안된다. 
클래스 이름은 해당 클래스 책임을 기술해야 한다. 간결한 이름이 떠오르지 않으면 클래스 크기가 너무 커서 그렇다. 이름이 모호하다면 클래스 책임이 너무 많아서다. 예를들어 Processor, Manager, Super 등과 같이 모호한 단어가 있다면 클래스에 여러 책임을 떠안긴 증거다. 또한, 클래스를 설명할때 접속사를 사용하지 않고 25단어 내외로 설명 가능해야 한다.

   + 단일 책임 원칙.
   단일 책임 원칙(SRP)은 클래스나 모듈을 변경할 이유가 하나뿐이어야 한다는 원칙이다. SPR은 책임이라는 개념을 정의하며 적절한 클래스 크기를 제시한다. 클래스는 책임이 하나여야 한다.
   책임, 즉 변경할 이유를 파악하려 애쓰다 보면 코드를 추상화하기도 쉬워진다.
    
     SRP는 객체 지향 설계에서 더욱 중요한 개념이고 이해하고 지키기도 수월한 개념이다. 하지만 SRP는 가장 무시하는 규칙 중 하나다. 우리들 대다수가 프로그램이 돌아가면 일이 끝났다고 여긴다. 깨끗하고 체계적인 소프트웨어라는 다음 관심사로 전환하지 않는다. 

     큰 클래스 몇 개가 아니라  작은 클래스 여럿으로 이뤄진 시스템이 더 바람직하다. 작은 클래스는 각자 맡은 책임이 하나며, 변경할 이유가 하나며, 다른 작은 클래스와 협력해 시스템에 필요한 동작을 수행한다.

  + 응집도.
  클래스는 인스턴스 변수 수가 작아야 한다. 각 클래스 메서드는 클래스 인스턴스 변수를 하나 이상 사용해야 한다. 일반적으로 메서드가 변수를 더 많이 사용할수록 메서드와 클래스는 응집도가 더 높다. 
  우리는 응집도가 높은 클래스를 선호한다. 응집도가 높다는 말은 클래스에 속한 메서드와 변수가 서로 의존하며 논리적인 단위로 묶인다는 의미기 때문이다.
  함수를 작게, 매개변수 목록을 짧게라는 전략을 따르다 보면 때때로 몇몇 메서드만 사용하는 인스턴스 변수가 아주 많아진다. 이는 새로운 클래스로 쪼개야 한다는 신호다. 응집도가 높아지도록 변수와 메서드를 적절히 문리해 새로운 클래스 두세 개로 쪼개준다.
  
  + 응집도를 유지하면 작은 클래스 여럿이 나온다.  
  큰 함수를 작은 함수 여럿으로 나누기만 해도 클래스 수가 많아진다. 변수가 많은 큰 함수 일부를 작은 함수로 빼낼 때 변수를 클래스 인스턴스 변수로 승격한다면 새 함수는 인수가 필요없다. 그만큼 함수를 쪼개기 쉬워진다.
  불행히도 이렇게 하면 클래스가 응집력을 잃는다. 몇몇 함수만 사용하는 인스턴스 변수가 점점 늘어나기 때문이다. 그런데 클래스가 응집력을 잃는다면 쪼개면 된다. 그래서 큰 함수를 작은 함수로 여럿 쪼개다 보면 종종 작은 클래스 여럿으로 쪼갤 기회가 생긴다.

* 변경하기 쉬운 클래스.
대다수 시스템은 지속적인 변경이 가해진다. 그리고 그때마다 시스템이 의도대로 동작하지 않을 위험이 따른다. 깨끗한 시스템은 클래스를 체계적으로 정리해 변경에 수반하는 위험을 낮춘다.
클래스 일부에서만 사용되는 비공개 메서드는 코드를 개선할 잠재적인 여지를 시사한다. 하지만 실제로 개선에 뛰어드는 계기는 시스템이 변해서라야 한다. 
OCP란 클래스는 확장에 개방적이고 수정에 폐쇄적이어야 한다는 원칙이다. 새 기능을 수정하거나 기존 기능을 변경할 때 건드릴 코드가 최소인 시스템 구조가 바람직하다. 이상적인 시스템이라면 새 기능을 추가할 때 시스템을 확장할 뿐 기존 코드를 변경하지 않는다.

  + 변경으로부터 격리.
  요구사항은 변하기 마련이다. 따라서 코드도 변하기 마련이다.
  우리는 구체적인 클래스와 추상 클래스가 있다고 배웠다. 구체적인 클래스는 상세한 구현을 포함하며 추상 클래스는 개념만 포함한다고도 배웠다. 상세한 구현에 의존하는 클라이언트 클래스는 구현이 바뀌면 위험에 빠진다. 그래서 우리는 인터페이스와 추상 클래스를 사용해 구현이 미치는 영향을 격리한다. 또 상세한 구현에 의존하는 코드는 테스트가 어렵다.
  
    시스템의 결합도를 낮추면 유연성과 재사용성도 더욱 높아진다. 결합도가 낮다는 소리는 각 시스템 요소가 다른 요소로부터 그리고 변경으로부터 잘 격리되어 있다는 의미다. 이러면 각 요소를 이해하기도 더 쉬워진다.
    
    결합도를 최소로 줄이면 자연스럽게 DIP를 따르는 클래스가 나온다. 본질적으로 DIP는 클래스가 상세한 구현이 아니라 추상화에 의존해야 한다는 원칙이다. 



느낀점
=============
'이름이 모호하다면 클래스 책임이 너무 많아서다. 예를들어 Manager...' 라는 구절이 있는데 실제 내가 ~Manager라고 이름지은 클래스에 기능이 너무 많아서 분리하는 작업 중에 이번 장을 읽어서 정말 공감도 많이 되고 도움도 됐다. 
지금까지 책에서 공감이 되던 내용도 있고 생소한 내용도 있었는데 이번 장을 읽어보니 생소한 내용들도 더 공부한 다음에 꼭 다시 읽어 봐야겠다는 생각이 든다.

  

논의 사항
=============
~Manager 같은 클래스를 많이 사용하시는지 사용한다면 보통 어느 정도 책임을 부여하시는지 궁금합니다.
