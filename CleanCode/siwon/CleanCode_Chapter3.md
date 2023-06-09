# Clean Code Chapter 3

# CHAPTER 3 : 함수

### 느낀 점

늘 필요한 것만 검색해서 긁어다 쓰고, 따르기만 하면서 코딩해왔던 저에게 이 챕터는 정말 많은 깨우침을 주네요…

당연하다고 여기고, 왜 이렇게 하는지 정확한 이유도 모른 채 써왔던 것들도 많이 있었는데, 알게 되니 감회가 새롭습니다. 이 책을 완독 이후에도 여러 번 정독하게 될 것 같습니다.

### 논의 내용

보통 함수나 코드를 짤 때, 어떤 방식으로 시작하시나요? 저 같은 경우는 메모장에 떠오르는 대로. 대화하듯이 글로 적고 단계적으로 구체화하곤 합니다.

### 내용정리

- 함수는 되도록이면 작게 만들어라.
- 들여쓰기 수준은 2단을 넘어서면 안된다. (if/else, while 등)
- 함수는 한가지 작업만을 잘 해야한다. (추상화 수준이 하나인 단계만 수행)
단순히 다른 표현이 아니라 의미 있는 이름으로 다른 함수를 추출할 수 있다면, 그 함수는 여러작업을 하는 셈이다.
- 함수 내 모든 문장의 추상화 수준이 동일해야한다 → 함수 당 추상화 수준은 하나여야 한다.
- 내려가기 규칙을 잘 지켜라. 각 함수는 다음 함수를 소개하는 형식으로 작성한다. 또한 각 함수는 일정한 추상화 수준을 유지한다.
- switch 문을 쓸 때는 추상 팩토리를 활용하라. switch문은 다형적 객체를 생성하는 코드 안에서 상속관계로 한번 정도만 써라.
- 길고 서술적인 이름이 짧고 어려운 이름보다 좋다. 길고 서술적인 이름이 길고 서술적인 주석보다 낫다.
- 함수 이름을 정할 때는 여러 단어가 쉽게 읽히는 명명법을 사용한다. 그런 다음, 여러 단어를 사용해 함수 기능을 잘 표현하는 이름을 선택해라.
- 이름을 붙일 때는 일관성이 있어야 한다. 모듈 내에서 함수 이름은 같은 문구, 명사, 동사를 활용한다.
- 함수에서 이상적인 인수 개수는 0개이다. 차선은 1개인 경우이다.
- 함수 이름과 인수 사이에 추상화 수준이 같아야한다.
- 출력 인수는 입력 인수보다 이해하기 어렵다. 출력 인수는 독자가 코드를 재확인하게 만든다.
- 함수에 인수 1개를 넘기는 이유로 가장 흔한 경우는 두 가지다. 
인수에게 질문을 던지는 경우. 인수를 뭔가로 변환해 결과를 반환하는 경우.
- 특별한 경우는 이벤트 형식이다. 입력 인수만 존재한다. 입력 인수로 시스템 상태를 바꾼다.
- 위에 3가지 경우가 아니라면 단항 함수는 가급적 피한다.
ex) 변환 함수에서 출력 인수 사용하는 경우. 사용 비추천
void includeSetupPageInto(StringBuffer pageText)
ex) 옳은 예
StringBuffer transform(StringBuffer in)
- 플래그 인수는 피해라. → 함수로 부울 값 넘기기
함수가 한꺼번에 여러 가지를 처리하게 된다.
- 인수 2개가 한 값을 표현하는 두 요소가 아니라면 이항 함수 사용을 지양해라
불가피하게 써야하는 경우는 함수 이름에 인수의 순서를 배치하여 이해를 도와라.
ex) assertExpectedEqualsActual(expected, actual)
- 삼항 함수는 훨씬 더 이해하기 어렵다. 만들 때는 신중히 고려하라.
일부를 독자적인 클래스 변수로 선언하여 인수를 줄이는 방법도 추천한다.
ex) double x, double y → Point center
- 때로는 인수 개수가 가변적인 함수도 필요하다.
ex) public String format(String format, Object… args)
- 단항 함수는 함수와 인수가 동사/명사 쌍을 이뤄야 한다.
ex) writeField(name)
- 함수 이름에 나타나지 않는 부수효과를 일으키지 마라 → “함수는 한 가지만 해야한다.”
- 출력 인수는 피해야한다. 함수에서 상태를 변경해야 한다면 함수가 속한 객체 상태를 변경하는 방식을 택한다. → this 사용
- 명령과 조회를 분리하라. 함수는 뭔가를 수행하거나 답하거나 둘 중 하나만 해야한다.
- try catch 예외를 사용해라. 단 정상 동작과 오류 처리 동작을 함수로 뽑아내어 분리하라.
- 오류 처리도 한 가지 작업이다. 함수는 한 가지 작업만 해야한다.
함수에 키워드 try가 있다면 함수는  try문으로 시작해 catch/finally 문으로 끝나야한다.
- 중복을 없애라. 코드 길이가 늘어날 뿐 아니라 알고리즘이 변하면 여러 곳이나 손봐야한다.
- 함수를 크게 만들경우 구조적 프로그래밍의 목표와 규율을 참고하라.
→ 함수는 return 문이 하나여야 한다. 루프 안에서 break나 continue를 사용해선 안되며, goto는 절대로 안된다.
- 소프트웨어를 짜는 행위는 글짓기와 비슷하다.