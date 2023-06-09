## 7장 오류 처리

> 오류 처리는 프로그램에 반드시 필요한 요소 중 하나일 뿐이다.

프로그램은 뭔가 잘못될 가능성은 늘 존재한다.  

*슈퍼마리오 64의 버그문제, 만조에 일어나는 서버문제 등등 예상조차 할 수 없는 문제도 있다*

뭔가 잘못되면 바로 잡을 책임은 바로 우리 프로그래머에게 있다.

깨끗한 코드와 오류 처리는 확실히 연관성이 있다.

상당수 코드 기반은 전적으로 오류 처리 코드에 좌우된다.

하지만 오류 처리 코드로 인해 프로그램의 논리를 이해하기 어려워진다면 깨끗한 코드라 부르기 어렵다.

### 오류 코드보다 예외를 사용하라

분기로 오류를 잡아서 처리하는 방법과 try/catch 블록을 사용하는 방법이 있다.

예제 1번같은 경우엔 호출자 코드가 복잡해지면서 역순으로 타고 가야하는 계층의 문제도 발생할 수 있다.

따라서 오류가 발생하면 예외를 던지는 방법이 더 좋다.

이런 예외 처리의 부분은 게임쪽에선 서버, I/O, 파일 입출력 부분에서 많이 사용되는 것 같다.

게임 루틴자체에선 사용하기 무거운 느낌이라 테스트 코드로 잡고 예외가 발생하는 지점만 체크하는 방식.

### Try-Catch-Finally 문부터 작성하라

예외에서 프로그램 안에다 범위를 정의한다는 사실이 매우 흥미롭다.

try-catch-finally 문에서 try블록에 들어가는 코드를 실행하면 어느 시점에서든 실행이 중단된 후 catch 블록으로 이동한다.

*트랜잭션과 비슷*

try블록에서 무슨 일이 생기든지 catch 블록은 프로그램 상태를 일관성 있게 유지해야 한다.

그러므로 예외가 발생할 코드를 짤 때는 try-catch-finally 문으로 시작하는 편이 낫다..!

### 미확인 예외를 사용하라

확인된 예외는 OCP를 위반한다.

메서드에서 확인된 예외를 던졌는데 catch블록이 세 단계 위에 있다면 그 사이 메서드 모두가 선언부에 해당 예외를 정의해야 한다.

때로는 확인된 예외도 유용하지만 의존성이 필수적으로 발현되기 때문에 미확인 예외를 사용해라

*실제로 `C#`은 미확인 예외만 지원하며 확인된 예외를 지원하지 않음*

### 예외에 의미를 제공하라

예외를 던질 때는 전후 상황을 충분히 덧붙인다.

그러면 오류가 발생한 위치를 찾기 쉬워진다.

즉, 오류 메세지에 정보를 담아 예외와 함께 던진다.

### 호출자를 고려해 예외 클래스를 정의하라

오류를 분류하는 방법은 수없이 많다.

오류가 발생한 위치로 분류가 가능하다.

오류가 발생한 컴포넌트, 유형으로 분류가 가능하지만 가장 주된 관심사는 오류를 잡아내는 방법이 되어야 한다.

### 정상 흐름을 정의하라

오류처리에 대한 논의대로 작성하다 보면 코드가 깨긋해 보이고 간결한 알고리즘으로 분류되기 시작한다.

하지만 그러다 보면 오류 감지가 프로그램 언저리로 밀려난다.

외부 API를 감싸 독자적인 예외를 던지고, 코드 위에 처리기를 정의해 중단된 계산을 처리한다.

대개는 멋진 처리 방식이지만, 때로는 중단이 적합하지 않은 때도 있다..

### null을 반환하지 마라

오류 처리를 논하는 장이라면 우리가 흔히 저지르는 바람에 오류를 유발하는 행위도 언급해야 한다고 생각한다.

그 중 첫째가 null을 반환하는 습관이다.

null을 반환하는 코드는 일거리를 늘릴 뿐만 아니라 호출자에게 문제를 떠넘긴다.

확실히 null이 불러오는 문제는 덩치가 커질 수 있고, 그 당시에는 알고리즘이 간단해 보일 수 있지만 결국에는 일거리가 늘어나는 것 같다.

나도 지금 짠 코드 중에 null을 반환하는 메서드가 종종 있던 것 같다.

**메서드에서 null을 반환하고 싶은 유혹이 든다면 그 대신 예외를 던지거나 특수 사례 객체를 반환하라.**

예제 처럼 몬스터 리스트를 반환 받는 경우 해당 리스트의 개수만큼 크기, 개수에 종속되지 않고 있는 만큼만 실행하는 로직으로 만들어 두면 이후에 수정할 필요가 전혀 없어지고 null 반환할 필요도 없다.

### null을 전달하지 마라

메서드에서 null을 반환하는 것도 나쁘지만, 메서드로 null을 전달하는 행위는 더 나쁘다.

이 부분은 예외 처리로 잡기보다 애초에 null을 전달하는 행위 자체가 이해가 되지 않는다..

따라서 null을 넘기지 못하도록 금지하는 것이 적당하다.

### 결론

깨끗한 코드는 읽기도 좋아야 하지만 안정성도 높아야 한다.

이 둘은 상충하는 목표가 아니다.

오류 처리 프로그램 논리와 분리해 독자적인 사안으로 고려하면 튼튼하고 깨끗한 코드를 작성할 수 있다.

오류 처리 프로그램 논리와 분리하면 독립적인 추론이 가능해지며 코드 유지보수성이 크게 높아진다.

#### 논의사항

null값 체크 자체가 비용이 든다고 생각을 안했었는데 책을 읽고 다시 생각해보니 null을 반환하는 메서드를 만드는 것 자체가 무책임하다고 느끼게 된 것 같습니다..

null 체크에 대한 생각이 궁금합니다!
