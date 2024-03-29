# The Clean Coder

## 7장. 인수 테스트

> 개발은 물론이고 의사소통 또한 프로 개발자의 임무다.

### 요구사항 관련 의사소통

> 프로그래머와 사업부 사이의 가장 흔한 의사소통 쟁점은 요구사항이다.

현실에서는 요구사항 관련 의사소통은 엄청나게 어렵고, 그 과정에는 오류가 가득하다.

### 시기상조와 정밀도

사업부와 프로그래머는 모두 시기상조의 정밀도라는 함정에 빠지기 쉽다.

### 불확실성의 원칙

요구사항이 실제 동작하는 모습을 보고 나면 더 나은 생각이 떠오르는데, 그 생각은 대개 눈앞의 시스템과 많이 다르다.

그러다 보면 요구사항이 정밀해질수록 최종 구현된 시스템과 초기 요구사항의 차이는 더 벌어진다.

### 불안한 추정

프로 개발자는 정밀도가 낮은 요구사항을 바탕으로 추정해야할 때가 많고, 그런 추정이 말 그대로 추정이라는 사실을 잘 안다. 프로 개발자는 이를 보강하려고 항상 추정에 오차범위를 추가해 사업부에서 불확실성을 이해하게 만든다.

### 때늦은 모호함

> 요구사항에서 모든 모호함을 제거하는 일이 프로 개발자의 책임이다.

### 인수 테스트

인수 테스트라는 용어는 사용자가 배포본을 인수하기 전에 시행하는 테스트라고 생각하기도, QA 테스트라고 여기기도 한다.

이 장에서는 요구사항이 언제 완료되는지를 정의하기 위해 이해당사자들과 프로그래머들이 힘을 모아 작성하는 테스트라고 정의한다.

### 인수 테스트와 단위 테스트

단위 테스트: 프로그래머가 프로그래머를 위해 작성, 코드의 최하위 구조와 행동을 설명하는 공식 디자인 문서

인수 테스트: 사업부가 사업부를 위해 작성

### GUI 및 다른 문제점

GUI는 제대로 명세하기 어렵다. 미학이라는 게 주관적이어서 논란의 여지가 있기 때문이다.

### 지속적 통합

CI를 통해 단위/인수 테스트를 하루에 몇번이라도 실행할 수 있도록 하라.

### 결론

세부사항에 대한 의사소통은 어렵다. 

양 당사자들이 완전히 다른 개념으로 이해하고 헤어지는 경우가 너무 흔하다.

### 느낀 점

이 책 중에 가장 안읽히는 장이었다. 

현업에서는 기획, 아트 직군 외에도 사업부 등과 이런 의사소통이 필요하다는 것을 조금 맛본 것 같다.

### 논의사항

*패스*