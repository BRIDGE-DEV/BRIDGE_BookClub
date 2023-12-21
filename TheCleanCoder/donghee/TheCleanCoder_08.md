# 8장 테스트 전략

## 정리

프로 개발자는 작성한 코드를 테스트한다.

프로 개발팀이라면 훌륭한 테스트 전략이 필요하다.

### QA는 오류를 찾지 못해야 한다

개발팀은 QA가 잘못된 점을 찾지 못하는 상태를 목표로 삼아야 한다.

> 물론 마음먹었다고 척척 달성할 수 있는 목표는 아니다.

### QA는 같은 팀이다

QA와 개발자는 서로 대립하는 사이가 아니다.

QA와 개발자는 시스템 품질 향상을 위해 힘을 합쳐야 한다.

### QA의 명세 서술

QA의 역할은 사업부와 함께 자동화된 인수 테스트를 만드는 일이다.

그렇게 만든 인수 테스트는 시스템에 대한 명세서이자 요구사항 문서다.

### QA의 특징 묘사

QA의 또 다른 역할은 탐색 테스트를 수행해 시스템의 실제 동작을 묘사해 보고하는 일이다.

### 테스트 자동화 피라미드

QA가 오류를 찾지 못하리라는 확신을 가지려면 상위 계층 테스트 또한 필요하다.

### 단위 테스트

단위 테스트는 프로그래머에 의해, 프로그래머를 위해 시스템 프로그래밍 언어로 만든 테스트다.

단위 테스트의 커버리지는 최대한 100%에 가까워야 한다.

### 컴포넌트 테스트

컴포넌트 테스트의 대상은 시스템의 독립 컴포넌트다.

컴포넌트에 입력 데이터를 넣고 출력 값을 받아 모은다. 그리고 입력 값에 대해 출력 값이 올바른지 테스트한다.

### 통합 테스트

통합 테스트는 여러 컴포넌트로 이루어진 큰 시스템에서만 의미가 있다.

업무 규칙은 테스트하지 않고 조립한 컴포넌트 묶음끼리 얼마나 잘 어우러지는지 테스트한다.

### 시스템 테스트

시스템 테스트는 통합한 시스템 전체를 대상으로 하는 자동화 테스트다. 다시 말해 궁극적인 통합 테스트다.

시스템이 올바로 동작하는지보다는 시스템을 올바르게 빌드했는지를 확실히 하려는 목적이다.

### 수동 탐색 테스트

수동 테스트는 키보드에 손을 얹고 모니터를 직접 보며 하는 테스트다.

이 테스트의 목적은 시스템이 기대한 대로 동작하는지 확인하는 동시에 예상치 못한 오류를 찾아내는 것이다.

### 결론

TDD와 인수 테스트는 강력하지만, 이는 전체 테스트 전략의 일부분일 뿐이다.

‘QA는 오류를 찾지 못해야 한다’는 목표를 달성하기 위해서는 개발팀과 QA가 손잡고 단위, 컴포넌트, 통합, 시스템, 탐색 테스트의 계층을 만들어야 한다.

---

## 느낀 점

> 프로 개발자는 작성한 코드를 테스트한다.

진짜 그래야만 할 것 같다. 요새 프로젝트를 하면서 느끼는 거지만… 전부 수동 탐색 테스트로 하다간 너무 비효율적이다. 또한 코드도 어느샌가 마구잡이로 써지는 것 같고..

그러다가 이 장을 딱 봤는데! 과연 내가 ‘이 코드로 단위 테스트를 작성할 수 있을까?’ 라는 생각이 들었다. 물론 절대 안된다고 생각했다.. 그냥 대충 알았을 때는 ‘이게 뭔소리야..’ 했지만 점점 윤곽이 잡히는 것 같아서 재밌다! 제대로 연습해서 바로 적용시켜보고 싶다는 생각이 들었다.

---

## 논의사항

- 테스트 코드를 실전에 활용해본 경험은 어떠셨나요?

저는 아직 못해봤습니다! 하하. 여러분들은 프로젝트에 활용하고 있다고 들어서! 테스트 코드를 통과하기 위해 코드를 짜보고, 다시 테스트 코드를 짜고, 이 과정을 반복해봤을 때 실제로 잘 되었는지, 아니면 무언가 막히지만 도움은 되는 것 같다든지! 아니면 아직 잘 모르겠다든지! 전부 들어보고 싶네용 ^ㅡ^