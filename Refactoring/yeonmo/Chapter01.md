# 리팩터링

## 리팩터링이란?

겉으로 드러나는 코드의 기능(겉보기 동작)은 바꾸지 않으면서 내부 구조를 개선하는 방식으로 소프트웨어 시스템을 수정하는 과정이다.

### 예시 프로그램에서 발견한 수정할 부분

프로그램이 새로운 기능을 추가하기에 편한 구조가 아니라면, 먼저 기능을 추가하기 쉬운 형태로 리팩터링 하고나서 원하는 기능을 추가한다.

1)HTML로 출력하는 기능을 위한 **복사본**

로직을 변경할 일이 절대 없다면 상관없지만, **오래 사용할 프로그램이라면 중복 코드는 골칫거리가 된다.**

2)연극 장르와 공연료 정책이 달라지는 **변경사항**

리팩터링이 필요한 이유는 바로 변경 때문이다. 다른 사람이 읽고 이해해야 할 일이 생겼는데로직을 파악하기 어렵다면 대책을 마련해야 한다.

‘~~디지털 시대의 연약한 자여, 그대 이름은 소프트웨어’~~

조금씩 변경하고 매번 테스트하는 것은 리팩터링 절차의 핵심이다.

리팩터링은 프로그램 수정을 작은 단계로 나눠 진행한다. 그래서 중간에 실수하더라도 버그를 쉽게 찾을 수 있다.

저자는 함수의 반환 값에는 항상 result라는 이름을 쓴다. 그러면 그 변수의 역할을 쉽게 알 수 있다.

또한 자바스크립트와 같은 동적 타입 언어를 사용할 때는 타입이 드러나게 작성하면 도움이 된다. 매개변수 이름에 접두어로 타입 이름을 적는데, 매개변수의 역할이 뚜렷하지 않을 때는 부정관사(a/an)를 붙인다.

컴퓨터가 이해하는 코드는 바보도 작성할 수 있다. 사람이 이해하도록 작성하는 프로그래머가 진정한 실력자다.

지역 변수를 제거해서 얻는 가장 큰 장점은 추출 작업이 훨씬 쉬워진다는 것이다. 유효범위를 신경 써야 할 대상이 줄어들기 때문이다.

반복문이 중복되는 것을 꺼리는 이들이 많지만, 사소한 중복은 성능에 미치는 영향이 미미할 때가 많다. 

리팩터링으로 인한 성능 문제에 대한 저자의 조언은 ‘특별한 경우가 아니라면 일단 무시하라’라는 것이다.

### 변수 제거하기 작업의 단계를 잘게 나눈 예시

1. 반복문 쪼개기
2. 문장 슬라이드하기
3. 함수 추출하기
4. 변수 인라인 하기

상황이 복잡해지면 단계를 더 작게 나누는 일을 가장 먼저 하라. 테스트에 실패했을 때 최근 커밋으로 돌아가 리팩터링의 단계를 더 작게 나누어 다시 시도할 수 있다. 또한 코드가 복잡할 수록 단계를 작게 나누면 작업 속도가 빨라지기 때문이다.

느낀 점: 꼭 코드 리팩터링이 아니더라도 인생의 모든 목표들은 잘게 나눌수록 달성하기 쉬운 것 같다고 생각하는데 다른 분들은 어떠신가요? 

공연 정보 레코드에 연극 데이터를 추가할 때 공연 객체를 복사했다. 그 이유는 가변 데이터는 금방 상하기 때문에 데이터를 최대한 불변처럼 취급하는 것이 좋다. 

### 모듈화

계산하는 부분과 출력 형식을 다루는 부분을 분리했다.

이렇게 **모듈화**하면 각 부분이 하는 일과 그 부분들이 맞물려 돌아가는 과정을 파악하기 쉬워진다.

간결함이 지혜의 정수일지 몰라도, 프로그래밍에서만큼은 명료함이 진화할 수 있는 소프트웨어의 정수다.

캠핑자들에게는 “도착했을 때보다 깔끔하게 정돈하고 떠난다”는 규칙이 있다. 프로그래밍도 마찬가지다. 항시 코드베이스를 작업 시작 전보다 건강하게 만들어놓고 떠나야 한다.

‘컴파일-테스트-커밋’  잊지말고 기회가 될 때마다 실행해야 한다.

### 다형성을 활용해 계산 코드 재구성하기

일반적인 경우를 기본으로 삼아 슈퍼클래스에 남겨두고, 장르마다 달라지는 부분은 필요할 때 오버라이드하게 만드는 것이 좋다.

### 서브클래스를 언제 사용하면 좋을까?

같은 타입의 다형성을 기반으로 실행되는 함수가 많을수록.

좋은 코드를 가늠하는 확실한 방법은 ‘얼마나 수정하기 쉬운가’다.

## 논의사항

코딩테스트 문제를 풀 때 성능에 집중하며 간결한 코드를 작성하는 편입니다.

하지만 이런 경우에도 리팩터링 책에서 조언하는 것처럼 조금 성능이 느려지더라도 가독성 좋은 답안을 제출하는 것이 더 좋을까요?

프로젝트가 아닌 알고리즘 문제를 위한 코드를 작성할 때 여러분은 어떤 부분에 집중하시는지 궁금합니다.