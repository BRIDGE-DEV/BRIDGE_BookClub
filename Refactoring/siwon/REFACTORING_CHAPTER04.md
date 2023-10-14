# REFACTORING_CHAPTER04

# 테스트 구축하기

## 내용 정리

---

### **자주 테스트하기**

작성 중인 코드는 최소한 몇 분 간격으로 테스트하고, 적어도 하루에 한 번은 전체 테스트를 돌려보자. 

### **테스트가 실패하는 모습을 직접 확인하기**

일부러 주입한 오류를 테스트가 걸러내는 게 확인되면, 원래 코드로 되돌린다.

### 테스트는 위험 요인 중심으로 작성하기.

테스트의 목적은 향후 발생할 버그를 찾는 데 있다. 따라서 단순히 필드를 읽고 쓰기만 하는 접근자는 테스트할 필요가 없다.

테스트를 너무 많이 만들다보면 오히려 필요한 테스트를 놓치기 쉽다.

나는 적은 수의 테스트만으로 큰 효과를 얻고 있다. 잘못될까봐 가장 걱정되는 영억을 집중적으로 테스트하는데,

이렇게 해서 테스트에 쏟는 노력의 효과를 극대화하는 것이다.

또 테스트를 너무 많이 작성하다 보면 오히려 의욕이 떨어져 나중에는 하나도 작성하지 않게 될 위험도 있다.

따라서 위험한 부분에 집중하는 게 좋다.

코드에서 처리과정이 복잡한 부분, 함수에서 오류가 생길만한 부분을 찾아보자

### **경계 조건 검사하기**

경계를 확인하는 테스트를 작성해보면 프로그램에서 이런 특이 상황을 어떻게 처리하는 게 좋을 지 생각해볼 수 있다.

### **버그 리포트를 받으면 가장 먼저 그 버그를 드러내는 단위 테스트부터 작성하기**

버그를 발견하는 즉시 발견한 버그를 명확히 잡아내는 테스트부터 작성하는 습관을 들여라.

버그를 고치기 전에 항상 이런 테스트부터 만든다. 또한 그 버그와 테스트를 계기로 테스트 스위트에 또 다른 구멍은 없는 지 살펴본다.

### **리팩토링 전, 리팩토링 하는 동안 테스트 추가하기**

항상 테스트 스위트부터 갖춘 뒤에 리팩터링 해야하지만, 리팩터링하는 동안에도 계속해서 테스트를 추가 해야한다.

### **기존 테스트 관리**

새로운 기능을 추가할 때, 새로운 테스트도 추가하지만 기존 테스트도 다시 살펴본다.

테스트 과정을 더 이해하기 쉽게 리팩터링 할 수 는 없는지, 제대로 검사하는 지 등을 확인한다.

## 느낀 점

---

이 챕터에서는 “버그를 발견하는 즉시, 발견한 버그를 명확히 잡아내는 테스트부터 작성하자.”

이 말이 가장 마음에 와닿았습니다. 평소 버그를 발견하면 바로 고치려고 하기만 하지 재발생을 막기 위한 노력을 안하고 있었네요…

앞으로 더욱 신경써야할 것 같습니다. 이 챕터에서는 자바스크립트 테스트 프레임워크인 mocha ([mochajs.org](https://mochajs.org/)) 를 써서 테스트 하는 방법을 보여주는데, C#에서 쓰이는 테스트 프레임워크에 대해서 궁금해지네요..? 

## 논의 내용

---

C# 테스트 프레임 워크에 대해서 알고 사용하고 계신 분이 계실까요?

있다면 장단점을 들어보고 싶습니다!