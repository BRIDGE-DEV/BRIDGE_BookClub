# REFACTORING_CHAPTER06

# 기본적인 리팩터링

## 내용 정리

---

### 함수 추출하기

- 코드가 무슨 일을 하는지 파악하고, 독립된 함수로 추출하고 목적에 맞게 이름을 붙이자.
- 지역변수는 매개변수로 받도록 하자.

### 함수 인라인 하기

- 간접 호출은 유용할 수 있지만 쓸데없는 간접 호출, 과하게 쓰이는 간접 호출은 거슬리니 함수를 인라인 하자.

### 변수 추출하기

- 표현 식이 복잡해서 이해하기 어려울 때 지역 변수를 활용해 표현 식을 관리하기 쉽게 만들자.

### 변수 인라인 하기

- 추출한 변수가 표현 식과 다를 바 없을 때 변수를 인라인 하자.

### 함수 선언 바꾸기

- 더 좋은 함수 이름이 떠오른다면 바꾸자.
- 주석을 작성해보면 함수의 이름이 역으로 떠오를 수도 있다.

### 변수 캡슐화하기

- 데이터를 옮길(변경)때는 데이터로의 접근을 독점하는 함수(프로퍼티)를 만들어 캡슐화 해주는 것이 좋을 때가 많다.
- 함수를 통해 데이터를 캡슐화 하면 데이터 변경이 어디서 일어나는지 쉽게 파악이 가능하다. 
데이터 변경 전 검증이나 변경 후 추가 로직 등을 쉽게 끼워 넣을 수 있다.

### 변수 이름 바꾸기

### 매개변수 객체 만들기

- 데이터 항목들이 이 함수 저 함수로 함께 몰려 다니는 경우 데이터 구조를 하나로 모아주자.

### 여러 함수를 클래스로 묶기

- 클래스는 데이터와 함수를 하나의 공유 환경으로 묶고 다른 프로그램 요소와 어우러질 수 있도록 그 중 일부를 외부에 제공한다.
- 여러 함수를 클래스로 묶으면 이 함수들이 공유하는 공통 환경을 좀 더 명확하게 할 수 있다. 
각 함수에 전달되는 인수를 줄여서 객체 안에서 함수 호출을 간결하게 만들 수 있다.
- 이 기법의 장점으로는 클라이언트가 객체의 핵심 데이터를 변경할 수 있을 뿐만 아니라 파생된 객체들을 일관하게 관리할 수 있다는 것이다.

### 여러 함수를 변환 함수로 묶기

- 데이터가 사용되는 곳 마다 같은 도출 로직이 반복되면 이 도출 작업을 한 곳으로 모으자. 
이로 인해 검색과 갱신을 일관된 장소에서 처리할 수 있고 중복도 제거할 수 있다.
- 변환 함수에 원본 데이터를 매개변수로 전달해 필요한 정보를 모두 도출 하고 가공한 데이터를 새로운 레코드에 저장한 뒤 반환한다.
- 원본 데이터가 코드 안에서 갱신 되면 클래스 묶기로 처리한다.

### 단계 쪼개기

- 서로 다른 두 대상을 한꺼번에 다루는 코드가 있으면 각각 별개 모듈로 나누는 방법을 모색하자.

### 변수 추출하기

## 느낀 점

---

예시가 자바인 것은 늘 아쉽지만.. 그럼에도 불구하고 가독성이 좋고, 이해가 잘 될 정도로 설명을 잘해주신다고 느꼈습니다. 

평소에 대충 알고 적용하고 있던 부분도 있어서 재밌었네요. 책을 읽은 뒤로 리팩터링에 큰 도움 받고 있습니다.

일부 기법들이 서로를 반발하는 느낌이 없지 않아 있지만, 뭐든 적절히 사용하면 좋다는 뜻으로 받아들이겠습니다. 😎

최근에 함수를 추출하는 작업과 네이밍을 변경하는 작업을 많이 하고 있다 보니, 그 쪽 대목이 제일 눈에 들어왔는데요 .

> **언제 독립된 함수로 묶어야 하는가?**
1. 한 화면을 벗어나는 길이
2. 두 번 이상 사용될 코드
3. 코드를 보고 파악하는 데 한참이 걸린다면 함수로 추출한 뒤, 네이밍을 잘 짓는다.
4. 목적이 잘 드러나는 네이밍이 떠오르지 않는다면, 추출하지 않는다.
5. 함수를 설명하는 주석을 달다 보면 이름이 떠오를 수 있다.
> 

다시 한번 머리에 꼭 새기겠습니다!

## 논의 내용

---

이 챕터에 기법들 중에 특히나 주로 사용하게 되는 기법이 있다면 무엇인가요?