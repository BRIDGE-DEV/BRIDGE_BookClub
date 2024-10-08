# Effective C++
## 1장. C++에 왔으면 C++의 법을 따릅시다.
### 항목 1: C++를 언어들의 연합체로 바라보는 안목은 필수

초창기의 C++은 단순히 C 언어에 객체 지향 기능 몇 가지가 결합된 형태였다. 그 후 C++은 꾸준한 성장을 거쳐 다중패러다임 프로그래밍 언어라고 불린다. (절차적 프로그래밍을 기본으로 하여 객체 지향, 함수식, 일반화 프로그래밍을 포함하여 메타프로그래밍 개념까지 지원하고 있다.)

C++를 단일 언어로 바라보는 눈을 넓혀, 상관 관계가 있는 여러 언어들의 연합체(federation)로 봐라. 그러고 나서 각 언어에 관한 규칙을 각개 격파하면 시각이 단순해지고 명확해지며, 기억하기도 편해진다.

C++를 제대로 따라잡으려면, 이 언어가 여러 개의 하위 언어를 제공한다는 점을 새겨야 한다.

- C
   - C++는 여전히 C를 기본으로 하고 있다. 블록, 문장, 선행 처리자, 기본제공 데이터타입, 배열, 포인터 등 모든 것이 C에서 왔다.
- 객체 지향 개념의 C++
   - '클래스를 쓰는 C'에 관한 모든 것이 해당된다. 클래스(생성자와 소멸자의 개념까지), 캡슐화, 상속, 다형성, 가상 함수(동적 바인딩) 등.
- 템플릿 C++
   - C++의 일반화 프로그래밍 부분으로, 많은 프로그래머들이 경험해 보지 않은 영역 중 하나.
- STL
   - 템플릿 라이브러리. 컨테이너, 반복자, 알고리즘과 함수 객체가 얽혀 돌아가는 것을 규약으로 삼고 있으나, 템플릿과 라이브러리는 얼마든지 다른 아이디어를 중심으로 만들어질 수 있다.

이렇게 네 가지 하위 언어들이 C++을 이루고 있다는 점을 마음에 새겨라. 그리고 이제는 효과적인 프로그램 개발을 위해 한 하위 언어에서 다른 하위 언어로 옮겨 가면서 대응 전략을 바꾸어야 하는 상황이 오더라도 당황하지 말아야 한다.

> C++를 사용한 효과적인 프로그래밍 규칙은 경우에 따라 달라진다. 그 경우란, 바로 C++의 어느 부분을 사용하느냐이다.