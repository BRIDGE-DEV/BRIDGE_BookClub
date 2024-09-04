초창기의 C++은 단순히 C 언어에 객체 지향 기능 몇 가지가 결합된 형태였으나 꾸준히 성장하여 예외, 템플릿, STL을 적용하였고 오늘날의 C++은 다중패러다임 프로그래밍 언어로 불린다.

절차적 프로그래밍을 기본으로하여 객체 지향, 함수식, 일반화 프로그래밍을 포함하여 메타프로그래밍 개념까지 지원한다.

C++는 한가지 프로그래밍 규칙 아래 뭉친 통합 언어가 아니라 네가지 하위 언어들의 연합체이다. 각각의 하위 언어가 자신만의 규칙을 갖고 있기 때문에 이를 주의해야한다.
+ C
+ 객체 지향 개념의 C++
+ 템플릿 C++
+ STL
### 궁금증
**메타 프로그래밍이란?**
자기 자신 혹은 다른 컴퓨터 프로그램을 데이터로 취급하며 프로그램을 작성·수정하는 것을 말한다. 다른 코드를 조작하는 코드를 작성하는 것.
예시로는 언리얼의 리플렉션 시스템?

**pass-by-value는 기본타입(built-in types)의 경우에는 pass-by-reference 보다 더 효율적이다.**
이유는 pass-by-value는 값에 대한 참조만 이루어지지만 pass-by-reference의 경우에는 주소에 대한 참조가 이루어져 조회하는 비용이 더 발생하고 built-in type의 경우 데이터의 크기가 주소 데이터의 크기와 같거나 작은 경우이기 때문이다.
[C++: Why pass-by-value is generally more efficient than pass-by-reference for built-in (i.e., C-like) types](https://stackoverflow.com/questions/5346853/c-why-pass-by-value-is-generally-more-efficient-than-pass-by-reference-for-bu)

