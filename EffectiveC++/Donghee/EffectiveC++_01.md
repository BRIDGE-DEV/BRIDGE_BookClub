# 챕터1: C++에 왔으면 C++의 법을 따릅시다

## 항목1: C++를 언어들의 연합체로 바라보는 안목은 필수

오늘날의 C++는 다중패러다임 프로그래밍 언어라고 불린다. 절차적 프로그래밍, 객체 지향, 함수식, 일반화, 메타프로그래밍 개념까지 지원한다.

C++를 단일 언어로 바라보는 눈을 넓혀, 상관 관계가 있는 여러 언어들의 연합체로 보자. C++를 제대로 따라잡으려면, 이 언어가 네 가지의 하위 언어를 제공한다는 점을 새기고 있어야 한다.

- C: C++는 여전히 C를 기본으로 하고 있다.
- 객체 지향 개념의 C++: ‘클래스를 쓰는 C’에 관한 것이 모두 해당된다. 클래스, 캡슐화, 상속, 다형성, 가상 함수 등이다.
- 템플릿 C++: C++의 일반화 프로그래밍 부분이다.
- STL: 이름에서 알 수 있듯이 템플릿 라이브러리다. STL은 나름대로 독특한 사용규칙이 있어서, 이를 써서 프로그래밍하려면 그 규약을 따르면 된다.

한 하위 언어에서 다른 하위 언어로 옮겨 가면서 대응 전략을 바꿔야 하는 상황이 오더라도 당황하지 말아야 한다.

예를 들어, C 스타일로만 쓰고 있으면 기본 제공 타입에 대해서는 “**값 전달이 참조 전달보다 대개 효율이 더 좋다**”라는 규칙이 통한다. 하지만 객체 지향 C++로 옮겨 가면 사용자 정의 생성자/소멸자 개념이 생기면서 **상수 객체 참조아에 의한 전달**이 더 좋은 효율을 보인다. 템플릿 C++에서도 객체의 타입을 알 수 없기 때문에, 이 점이 두드러진다. 하지만 STL 쪽으로 넘어오면, 반복자와 함수 객체가 C의 포인터를 본떠 만든 것이기 때문에 값 전달에 대한 규칙이 다시 힘을 발휘한다.

> C++를 사용한 효과적인 프로그래밍 규칙은, C++의 어떤 부분을 사용하느냐에 따라 달라진다.