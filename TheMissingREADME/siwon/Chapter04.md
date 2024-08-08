# Chapter04

---

널 검사는 메서드의 시작부터 하기.

 불변 변수 사용하자.

타입 힌트와 정적 타입 검사를 활용하자. -> C#에서는 is, as라고 한다.

입력 값을 검사하자.

### 예외를 활용하자.

예외는 어떤 문제가 발생했는지 명확히 알 수 있도록 구체적으로 사용하자.

예외는 일찍 던지고 최대한 나중에 처리하자. 

일찍 -> 에러가 발생한 지점으로부터 최대한 가까이
나중에 -> 예외를 처리할 적절한 위치에 도착할 때 까지

### 재시도

재시도는 현명하게 -> 시기와 빈도 파악이 어렵기 때문에 노하우가 필요하다. 백오프 전략 사용.

재시도를 위해 멱등성(실행하면 항상 같은 값이 출력됨)있는 시스템을 구현하자.

**장애가 발견하면 리소스(메모리 등)를 해제하자.**

문제 원인을 찾기 위한 로깅방안.

로그는 원자적으로 작성. -> 한 로그에 하나의 문제씩. 줄바꿈 금지.

로그는 신속하게 기록하자.

# 논의사항

---

try catch 예외 문을 활용하고 계신가요? 활용한다면 어떻게 활용하고 계신가요?

저 같은 경우는 비동기 메서드를 실행시킬 때 타이밍이 안 맞아 특정 객체에 Null 값이 들어가는 경우에도 문제 없이 특정 메서드를 실행시키기 위해 편법식으로 사용한 적이 있습니다. 딱 봐도 안 좋은 예시죠. 이것이 삼켜버리는 경우인 것 같습니다. 여러분은 어떠신가요.