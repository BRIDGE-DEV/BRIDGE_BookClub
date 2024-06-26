## 12장 다형성

상속의 목적은 코드 재사용이 아니다. 상속은 타입 계층을 구조화하기 위해 사용해야 한다. 상속이 단순히 코드 재사용이 목적이라면 사용하지 말아야 한다.

### 다형성

객체지향 프로그래밍에서 사용되는 **다형성(Polymorphism)**은 **유니버셜(Universal)** 다형성과 **임시 (Ad Hoc)** 다형성으로 분류할 수 있다. 유니버셜 다형성은 다시 **매개변수(Parametric)** 다형성과 **포함(Inclusion)** 다형성으로 나눌 수 있다. 임시 다형성은 **오버로딩(Overloading)**과 **강제(Coercion)** 다형성으로 나눌 수 있다.

일반적으로 하나의 클래스 안에 동일한 이름의 메서드가 존재하는 경우를 가리켜 **오버로딩 다형성**이라고 부른다. 흔히 메서드 오버로딩에 해당되며, 동작을 일관되게 하거나 이름의 수준을 추상화로 올릴 때 많이 사용한다.

**강제 다형성**은 언어가 지원하는 자동적인 타입 변환이나 사용자가 직접 구현한 타입 변환을 이용해 동일한 연산자를 다양한 타입에 사용할 수 있는 방식을 가리킨다. 자바의 이항 연산자의 피연산자가 모두 정수일 때와 하나만 문자열일 때 강제 다형성이 나타난다. 이를 이용해 오퍼레이터를 재정의하여 다형성을 나타내기도 한다.

**매개변수 다형성**은 제네릭 프로그래밍과 연관이 깊으며, 클래스의 인스턴스 변수나 메서드의 매개변수 타입을 임의의 타입으로 지정하고 사용하는 시점에서 구체적인 타입으로 지정하는 방식을 말한다. C#의 콜렉션들이 여기에 해당된다.

**포함 다형성**은 메시지가 동일하더라도 수신한 객체의 타입에 따라 실제로 수행되는 행동이 달라지는 능력을 의미한다. 포함 다형성은 **서브타입(Subtype) 다형성**이라고도 불린다. 객체지향에서 특별한 언급 없이 말하는 다형성이 여기에 해당된다.

포함 다형성을 구현하는 가장 일반적인 방법이 상속을 사용하는 것으로 두 클래스를 상속 관계로 연결하고 자식 클래스에서 부모 클래스의 메서드를 오버라이딩한 후 클라이언트는 부모 클래스만 참조하면 포함 다형성을 구현할 수 있다.

포함 다형성을 위해 상속을 사용하는 가장 큰 이유는 상속이 클래스들을 계층으로 쌓아 올린 후 상황에 따라 적절한 메서드를 선택할 수 있는 메커니즘을 제공하기 때문이다. 객체가 메시지를 수신하면 객체지향 시스템은 메시지를 처리할 적절한 메서드를 상속 계층 안에서 탐색한다. 실행할 메서드를 선택하는 기준은 어떤 메시지를 수신했는지에 따라, 어떤 클래스의 인스턴스에 따라, 상속 계층이 어떻게 구성돼 있는지에 따라 달라진다.

### 상속의 양면성

객체지향 패러다임의 근간을 이루는 아이디어는 데이터와 행동을 객체라고 불리는 하나의 실행 단위안으로 통합하는 것이다. 따라서 객체지향 프로그램을 작성하기 위해서는 항상 데이터와 행동이라는 두 가지 관점을 함께 고려해야 한다.

상속 역시 예외는 아니다. 상속을 이용하면 부모 클래스에서 정의한 모든 데이터를 자식 클래스의 인스턴스에 자동으로 포함시킬 수 있다. 이것이 데이터 관점의 상속이다. 데이터뿐만 아니라 부모 클래스에서 정의한 일부 메서드 역시 자동으로 자식 클래스에 포함시킬 수 있다. 이것이 행동 관점의 상속이다.

단순히 데이터와 행동의 관점에서만 바라보면 상속이란 부모 클래스에서 정의한 데이터와 행동을 자식클래스에서 자동적으로 공유할 수 있는 재사용 메커니즘으로 보일 것이다. 하지만 이 관점은 상속을 오해한 것으로 상속의 목적은 코드 재사용이 아니다. 상속은 프로그램을 구성하는 개념들을 기반으로 다형성을 사능하게 하는 타입 계층을 구축하기 위한 것이다.

타입 계층에 대한 고민 없이 코드를 재사용하기 위해 상속을 사용하면 이해하기 어렵고 유지보수하기 버거운 코드가 만들어질 확률이 높다. 문제를 피할 수 있는 유일한 방법은 상속이 무엇이고 언제 사용해야 하는지를 이해하는 것뿐이다.

*상속으로 다형성을 나타내는 문제점을 더 보여줄려고 하는 것 같다.*

#### 상속을 사용한 강의 평가

##### Lecture 클래스 살펴보기

수강생들의 성적을 계산하는 간단한 예제 프로그램으로 설명한다.

##### 상속을 이용해 Lecture 클래스 재사용하기

Lecture 클래스는 새로운 기능을 구현하는 데 필요한 대부분의 데이터와 메서드를 포함하고 있다. 따라서 Lecture 클래스를 상속받으면 새로운 기능을 쉽고 빠르게 추가할 수 있을 것이다. 따라서 Lecture를 상속받은 GradeLecture 클래스를 만들어 새로운 기능을 추가한다.

예약어인 `super`를 이용해서 부모 클래스의 메서드를 호출할 수 있다. 중요한 점은 부모와 자식 클래스 모두 같은 메서드 시그너치를 공유한다는 점이다. 이런 경우 자식 클래스의 메서드 우선순위가 더 높게 적용되기에 만약 부모 클래스의 필수 동작이 있다면 `super`를 이용해 호출해야 한다. 예약어를 사용하지 않는다면 원하는 대로 동작하지 않을 수 있다.

*이게 어려운 점이 어떤 메서드는 사용하지 않고 직접 재 구현을 권장하고, 어떤 메서드는 예약어를 넣어줘야지만 원하는 대로 동작한다는 것이다.*

*C#은 `base` 예약어를 사용한다.*

결과적으로 동일한 시그니처를 가진 자식 클래스의 메서드가 부모 클래스의 메서드를 가리게 된다. 이를 **메서드 오버라이딩(Method Overriding)**이라고 부른다. 오버로딩과 오버라이딩의 차이점은 이미 잘 알것이라고 생각하고.. 넘어간다.

#### 데이터 관점의 상속

`GradeLecture`는 실제 메모리 상에도 `Lecture`의 데이터를 포함하고 있다. (*집합의 포함관계*) 정리하면 데이터 관점에선 상속은 자식 클래스의 인스턴스 안에 부모 클래스의 인스턴스를 포함하는 것으로 볼 수 있다. 따라서 자식 클래스의 인스턴스는 자동으로 부모 클래스에서 정의한 인스턴스 변수를 내부에 포함하게 되는 것이다.

#### 행동 관점의 상속

행동 관점의 상속은 부모 클래스가 정의한 일부 메서드를 자식 클래스의 메서드로 포함시키는 것을 의미한다. 공통적인 부모의 퍼블릭 메서드는 자식 클래스의 퍼블릭 인터페이스에 포함된다. 따라서 외부의 객체가 부모 클래스의 인스턴스에게 전송할 수 있는 모든 메시지는 자식 클래스의 인스턴스에게도 전송할 수 있다.

부모 클래스의 퍼블릭 인터페이스가 자식 클래스의 퍼블릭 인터페이스에 합쳐진다고 표현했지만 실제로 클래스의 코드를 합치거나 복사하는 작업이 수행되는 것은 아니다. 부모 클래스에서 구현한 메서드를 자식 클래스의 인스턴스에서 수행할 수 있는 것은 런타임에 시스템이 자식 클래스에 정의되지 안은 메서드가 있을 경우 이 메서드를 부모 클래스 안에서 탐색하기 때문이다.

객체의 경우에는 서로 다른 상태를 저장할 수 있도록 각 인스턴스별로 독립적인 메모리를 할당받아야 한다. **하지만 메서드의 경우에는 동일한 클래스의 인스턴스끼리 공유가 가능하기 때문에 클래스는 한 번만 메모리에 로드하고 각 인스턴스별로 클래스를 가리키는 포인터를 갖게 하는 것이 경제적이다.**

메세지를 수시한 객체는 class 포인터로 연결된 자신의 클래스에서 적절한 메서드가 존재하는지를 찾는다. 만약 메서드가 존재하지 않으면 클래스의 parent 포인터를 따라 부모 클래스를 차례대로 탐색한다. 자식 클래스에서 부모 클래스로의 탐색이 가능하기 때문에 자식 클래스는 마치 부모 클래스에 구현된 메서드의 복사본을 가지고 있는 것처럼 보이게 된다.

따라서 각 객체에 포함된 class 포인터와 클래스에 포함된 parent 포인터를 조합하면 현재 인스턴스의 클래스에서 최상위 부모 클래스에 이르기까지 모든 부모 클래스에 접근하는 것이 가능하다.

### 업캐스팅과 동적 바인딩

#### 같은 메시지, 다른 메서드

책에서 예시로 보여주는 코드와 같이 실제 동작에 관련된 행위를 DI를 통해 넣어주고 이를 해당 객체가 담당하도록 설정하는 것에 대한 좋은 이해는 실제 `C#` 정렬 코드를 참고해도 좋다. 이를 좀 더 확장하여 아이템과 플레이어의 관계를 생각해봐도 좋다.

코드 안에서 선언된 참조 타입과 무관하게 실제로 메시지를 수신하는 객체의 타입에 따라 실행되는 메서드가 달라질 수 있는 것은 업캐스팅과 동적 바인딩이라는 메커니즘이 작용하기 때문이다.

- 부모 클래스 타입으로 선언된 변수에 자신 클래스의 인스턴스를 할당하는 것이 가능하다. 이를 **업캐스팅**이라고 부른다.
- 선언된 변수의 타입이 아니라 메시지를 수신하는 객체의 타입에 따라 실행되는 메서드가 결정된다. 이것은 객체지향 시스템이 메시지를 처리할 적절한 메서드를 컴파일 시점이 아니라 실행 시점에 결정하기 때문에 가능하다. 이를 **동적 바인딩**이라고 부른다.

동일한 수신자에게 동일한 메시지를 전송하는 동일한 코드를 이용해 서로 다른 메서드를 실행할 수 있는 이유는 업캐스팅과 동적 메서드 탐색이라는 기반 메커니즘이 존재하기 때문이다. 업캐스팅은 서로 다른 클래스의 인스턴스를 동일한 타입에 할당하는 것을 가능하게 해준다.

따라서 부모 클래스에 대해 작성된 코드를 전혀 수정하지 않고도 자식 클래스에 적용할 수 있다. 동적 메서드 탐색은 부모 클래스의 타입에 대해 메시지를 전송하더라도 실행 시에는 실제 클래스를 기반으로 실행될 메서드가 선택되게 해준다. 따라서 코드를 변경하지 않고도 실행되는 메서드를 변경할 수 있다.

##### 개방-폐쇄 원칙과 의존성 역전 원칙

업캐스팅과 동적 메서드탐색에 대한 설명은 개방-폐쇄 원칙의 의도와 일치한다. 부모 클래스를 수정하지 않고도 행위를 변경할 수 있다는 맥락에서 정확하게 일치하고 업캐스팅과 동적 메서드 탐색은 상속을 이용해 개방-폐쇄 원칙을 따르는 코드를 작성할 때 하부에서 동작하는 기술적인 내부 메커니즘을 제공한다.

#### 업캐스팅

상속을 이용하면 부모 클래스의 퍼블릭 인터페이스가 자식 클래스의 퍼블릭 인터페이스에 합쳐지기 때문에 부모 클래스의 인스턴스 대신 자식 클래스의 인스턴스를 사용하더라도 메시지를 처리하는 데는 아무런 문제가 없다.

이런 특성을 활용할 수 있는 대표적인 두 가지가 대입문과 메서드의 파라미터 타입이다. 모든 객체지향 언어는 명시적으로 타입을 변환하지 않고도 부모 클래스 타입의 참조 변수에 자식 클래스의 인스턴스를 대입할 수 있게 허용한다.

업캐스팅과 반대로 부모 클래스의 인스턴스를 자식 클래스 타입으로 변환하기 위해서는 명시적인 타입 캐스팅이 필요한데 이를 **다운 캐스팅** 이라고 부른다. *(두 캐스팅 모두 오류의 가능성은 열려 있다.)*

#### 동적 바인딩

전통적인 언어에서 함수를 실행하는 방법은 함수를 호출하는 것이다. 객체지향 언어에서 메서드를 실행하는 방법은 메시지를 전송하는 것이다. 함수 호출과 메시지 전송의 차이는 생각보다 크고 프로그램 안에 작성된 함수 호출 구문과 실제로 실행되는 코드를 연결하는 언어적인 메커니즘은 완전히 다르다.

*메시지와 메서드의 차이는 실제 동작과정과 똑같이 다르며, 언어적인 차이도 존재한다.*

함수를 호출하는 전통적인 언어들은 호출될 함수를 컴파일 타임에 결정한다. 즉, 코드를 작성하는 시점에 호출될 코드가 결정된다. 이처럼 컴파일타임에 호출할 함수를 결정하는 방식을 **정적 바인딩**, **초기 바인딩** 또는 **컴파일 타임 바인딩**이라고 부른다.

객체지향 언어에서는 메시지를 수신했을 때 실행할 메서드가 런타임에 결정된다. `foo.bar()`이란 코드를 읽는 것으로는 실행되는 `bar`가 어떤 클래스의 어떤 메서드인지 판단하기 어렵다. 이처럼 런타임에 메시지를 수신한 객체의 타입에 따라 실행할 메서드를 결정하는 방식을 **동적 바인딩** 또는 **지연 바인딩**이라고 부른다.

객체지향 언어가 제공하는 업캐스팅과 동적 바인딩을 이용하면 부모 클래스 참조에 대한 메시지 전송을 자식 클래스에 대한 메서드 호출로 변환할 수 있다.

### 동적 메서드 탐색과 다형성

객체지향 시스템은 다음 규칙에 따라 실행할 메서드를 선택한다.

- 메시지를 수신한 객체는 먼저 자신을 생성한 클래스에 적합한 메서드가 존재하는지 검사한다. 존재하면 메서드를 실행하고 탐색을 종료한다.
- 메서드를 찾지 못했다면 부모 클래스에서 메서드 탐색을 계속한다. 이 과정은 적합한 메서드를 찾을 때까지 상속 계층을 따라 올라가며 찾는다.
- 상속 계층의 가장 최상위 클래스에 이르렀지만 메서드를 발견하지 못한 경우 예외를 발생시키며 탐색을 중단한다.

메시지 탐색과 관련해서 이해해야 하는 중요한 변수가 하나 있다. `self 참조`가 바로 그것이다. 객체가 메시지를 수신하면 컴파일러 self 참조라는 임시 변수를 자동으로 생성한 후 메시지를 수신한 객체를 가리키도록 설정한다. 동적 메서드 탐색은 self가 가리키는 객체의 클래스에서 시작해서 상속 계층의 역방향으로 이뤄지며 메서드 탐색이 종료되는 순간 self 참조는 자동으로 소멸된다.

메서드 탐색은 자식 클래스에서 부모 클래스의 방향으로 진행되며 항상 자식 클래스의 메서드가 부모 클래스의 메서드보다 먼저 탐색되기 때문에 자식 클래스에 선언된 메서드가 부모 클래스의 메서드보다 더 높은 우선순위를 가진다.

지금까지의 설명을 종합해보면 동적 메서드 탐색은 두 가지 원리로 구성된다는 것을 알 수 있으며, 첫 번째 원리는 **자동적인 메시지 위임**이다. 자식 클래스는 자신이 이해할 수 없는 메시지를 전송받은 경우 상속 계층을 따라 부모 클래스에게 위임한다. 클래스 사이의 위임은 프로그래머의 개입 없이 상속 계층을 따라 자동으로 이뤄진다.

두 번째 원리는 메서드를 탐색하기 위해 **동적인 문맥**을 사용한다는 것이다. 메시지를 수신했을 때 실제로 어떤 메서드를 실행할지를 결정하는 것은 컴파일 시점이 아닌 실행 시점에 이뤄지며, 메서드를 탐색하는 경로는 self 참조를 이용해서 결정한다.

메시지가 처리되는 문맥을 이해하기 위해서는 정적인 코드를 분석하는 것만으로는 충분하지 않다. 런타임에 실제로 메시지를 수신한 객체가 어떤 타입인지를 추적해야 한다. 이 객체의 타입에 따라 메서드를 탐색하는 문맥이 동적으로 결정되며, 여기사 가장 중요한 역할을 하는 것이 바로 self참조다.

*실제 코드에서도 이런 영역이 눈에 바로 보이지는 않지만 어떻게 동적 바인딩이 설정되는지에 대한 이해로는 적합한 것 같다.*

#### 자동적인 메시지 위임

동적 메서드 탐색은 적절한 메서드를 찾을 때까지 상속 계층을 따라 부모 클래스로 처리가 위임된다는 것이고, 상속을 이용할 경우 프로그래머가 메시지 위임과 관련된 코드를 명시적으로 작성할 필요가 없다. 결국 메시지는 상속 계층을 따라 부모 클래스에게 자동으로 위임되는 것이고 상속 계층을 정의하는 것은 메서드 탐색 경로를 정의하는 것과 동일하다.

자식 클래스에서 부모 클래스 방향으로 자동으로 메시지 처리가 위임되기에 동적 바인딩이 자동적으로 발생하는 것이다. 이와 다르게 같은 이름을 공유하지만, 시그니처가 다른 메서드들은 상속 계층에 걸쳐서 다르게 공존할 수 있다. 이것이 바로 메서드 오버로딩이다.

##### 메서드 오버라이딩

자식 클래스가 부모 클래스의 메서드를 오버라이딩하면 자식 클래스에서 부모 클래스로 향하는 메서드 탐색 순서 때문에 자식 클래스의 메서드가 부모 클래스의 메서드를 감추게 된다.

##### 메서드 오버로딩

메서드의 시그니처가 다르기 때문에 동일한 이름의 메서드가 공존하는 경우를 메서드 오버로딩이라고 부른다. 메서드 오버라이딩은 메서드를 감추지만 메서드 오버로딩은 사이좋게 공존한다. 다시 말해서 클라이언트 관점에서 오버로딩된 모든 메서드를 호출할 수 있다는 것이다.

대부분의 사람들은 하나의 클래스 안에서 같은 이름을 가진 메서드들을 정의하는 것을 메서드 오버로딩으로 생각하고 상속 계층 사이에서 같은 이름을 가진 메서드를 정의하는 것을 오버로딩으로 생각하지 않는 경향이 있다. 이것은 일부 언어에서 상속 계층 사이의 메서드 오버로딩을 지원하지 않기 때문이다. (`C++`이 그러하다.)

`C++`은 상속 계층 안에서 동일한 이름을 가진 메서드가 공존해서 발생하는 혼란을 방지하기 위해 부모 클래스에 선언된 이름이 동일한 메서드 전체를 숨겨서 클라이언트가 호출하지 못하도록 막는다. 이를 **이름 숨기기(name hiding)**이라고 부른다.

*실제로 왜 상속 구조에서 오버로딩을 잘 사용하지 않는지에 대해 생각해보니.. 그런 경우 자체를 많이 보지 못한 것 같다. 해당 오버로딩 자체를 다형성으로 봐도 좋겠지만, 애초에 오버라이딩으로 해결할 수 있는 문제가 많기 때문에 오버로딩을 사용하지 않는 것이 아닐까 생각한다.*

중요한 점은 언어마다의 차이점을 명확하게 이해하고 자신이 사용하는 언어의 특성에 맞게 객체지향을 가져가는 것이 중요하다.

#### 동적인 문맥

메시지를 수신한 객체가 무엇이냐에 따라 메서드 탐색을 위한 문맥이 동적으로 바뀐다는 것이다. 그리고 이 동적인 문맥을 결정하는 것은 바로 메시지를 수신한 객체를 가리키는 self 참조이다.

동일한 코드라고 하더라도 self 참조가 가리키는 객체가 무엇인지에 따라 메서드 탐색을 위한 상속 계층의 범위가 동적으로 변한다. 따라서 self 참조가 가리키는 객체의 타입을 변경함으로써 객체가 실행될 문맥을 동적으로 바꿀 수 있다.

self 참조가 동적 문맥을 결정한다는 사실은 종종 어떤 메서드가 실행될지를 예상하기 어렵게 만든다. 대표적인 사례가 **self 전송**이다. 이 경우 자신의 메서드를 호출했다고 생각할 수 있지만 실제로는 현재 객체에게 메시지를 전송하는 것이다.

현재 객체란 self 참조가 가리키고 있는 객체로 이 객체는 처음 메시지를 수신했던 객체이다. 자기 자신에게 메시지를 전송하는 것을 self 전송이라고 부른다.

메시지 탐색의 과정을 self 전송의 사례로 본다면 동적 바인딩의 구조를 이해할 수 있다. 문제가 되는 부분은 self 전송을 통해 상속 계층의 복잡함을 숨겨놓는다면 극단적으로 이해하기 어려운 코드가 만들어진다.

#### 이해할 수 없는 메시지

최상위 부모까지 올라갔지만 이해할 수 없는 메시지가 처리된다면 프로그래밍 언어의 타입에 따라 다르게 처리된다.

##### 정적 타입 언어와 이해할 수 없는 메시지

정적 타입 언어에서는 코드를 컴파일할 때 상속 계층 안의 클래스들이 이해할 수 있는지 여부를 판단한다. 따라서 상속 계층 전체를 탐색한 후에도 메시지를 발견하지 못한다면 에러를 발생시킨다.

##### 동적 타입 언어와 이해할 수 없는 메시지

동적 타입 언어 역시 메시지를 수신한 객체의 클래스로부터 부모 클래스의 방향으로 메서드를 탐색한다 차이점이라면 동적 타입 언어에는 컴파일 단계가 존재하지 않기 때문에 실제로 코드를 실행해보기 전에는 메시지 처리 가능 여부를 판단하기 어렵다.

#### self 대 super

self 참조의 가장 큰 특징은 동적이라는 점이다. self 참조는 메시지를 수신한 객체의 클래스에 따라 메서드 탐색을 위한 문맥을 실행 시점에 결정한다.

super 클래스도 self와 마찬가지로 메시지의 전송으로 이해해야 한다. 부모 클래스의 메서드를 실행하기 위한 것이 아닌 '지금 이 클래스의 부모에서부터 메서드 탐색을 시작하세요'라고 이해해야 한다. (이후에는 똑같이 재귀적인 탐색)

**즉 super 클래스로 호출하는 메서드는 반드시 부모 클래스에 위치하지 않아도 되는 유연성을 제공한다.** 그 메서드가 조상 클래스 어딘가에 있기만 하면 성공적으로 탐색될 것이기 때문이다. 부모 클래스의 메서드를 호출하는 것과 부모 클래스에서 메서드 탐색을 시작하는 것은 의미가 매우 다르다. 부모 클래스의 메서드를 호출한다는 것은 그 메서드가 반드시 부모에 정의돼 있어야 한다는 것을 의미한다. 그에 비해 부모 클래스에서 메서드 탐색을 시작한다는 것은 그 클래스의 조상 어딘가에 그 메서드가 정의돼 있기만 하면 실행할 수 있다는 것을 의미한다.

self 전송에서 메시지 탐색을 시작하는 클래스는 미정이지만 super 전송에서는 미리 정해진다는 것이다. 따라서 self 전송의 경우 메서드 탐색을 시작할 클래스를 반드시 실행 시점에 동적으로 결정해야 하지만 super 전송의 경우에는 컴파일 시점에 미리 결정해 놓을 수 있다.

### 상속 대 위임

결국 다형성은 self 참조가 가리키는 현재 객체에게 메시지를 전달하는 특성을 기반으로 한다. 동일한 타입의 객체 참조에게 동일한 메시지를 전송하더라도 self 참조가 가리키는 객체의 클래스가 무엇이냐에 따라 메서드 탐색을 위한 문맥이 달라진다.

일단 self 참조가 동적인 문맥을 결정한다는 사실을 이해하고 나면 상속을 바라보는 새로운 시각이 형성된다. 바로 자식 클래스에서 부모 클래스로 self 참조를 전달하는 메커니즘으로 상속을 바라보는 것이다.

#### 위임과 self 참조

`Lecture`를 상속받은`GradeLecture`을 그림으로 나타내면 `Lecture`클래스는 집합으로 포함관계를 가진다. 이때, `GradeLecture`는 `Lecture`의 인스턴스를 포함하고 있다고 말할 수 있다. `GradeLecture`의 self 참조는 자신을 가리킨다. `Lecture`의 self 참조가 똑같이 자신을 가리킨다고 생각할 수 있지만, 실제로는 `GradeLecture`의 인스턴스를 가리킨다.

self참조는 항상 메시지를 수신한 객체를 가리키기 때문이다. 따라서 메서드 탐색 중에는 자식 클래스의 인스턴스와 부모 클래스의 인스턴스가 동일한 self 참조를 공유하는 것으로 봐도 무방하다.

![image](https://github.com/fkdl0048/BookReview/assets/84510455/2ab7b712-7059-4391-a64d-4584640c46e3)

자신이 수신한 메시지를 다른 객체에게 동일하게 처리를 요청하는 것을 **위임(delegation)**이라고 한다. (포워딩과의 차이점을 이해할 것, 참조를 전달한다 안한다.)

결국 위임이 객체 사이의 동적인 연결 관계를 이용해 상속을 구현하는 방법이라는 사실을 이해했을 것이다. 상속이 매력적인 이유는 직접 구현해야 하는 이런 과정을 자동으로 처리해주기 때문이다.

**상속은 동적으로 메시지를 탐색하기 위해 현재의 실행 문맥을 가지고 있는 self 참조를 전달한다. 그리고 이 객체들 사이에서 메시지를 전달하는 과정은 자동으로 이뤄진다.** 따라서 **자동적인 메시지 위임**이라고 부르는 것이다.

*상속 구조를 흉내내는 과정이 되게 새로웠다. 중요한 4가지다 포함관계로 상속을 흉내내고 나타낼 수 있다니.. 생각하지 못했다.*

#### 프로토타입 기반의 객체지향 언어

프로토타입(prototype) 기반의 언어는 클래스가 존재하지 않고 오직 객체만 존재하는 언어를 지칭하며, 앞서 클래스를 사용하지 않고도 상속을 구현할 수 있는 것을 확인했기 때문에 프로토타입 기반의 언어에선 위임이 상속을 구현하는 유일한 방법이다.

클래스 기반의 객체지향 언어들이 상속을 이용해 클래스 사이에 self 참조를 자동으로 전달하는 것처럼 프로토타입 기반의 객체지향 언어들 역시 위임을 이용해 객체 사이에 self 참조를 자동으로 전달한다.

메서드를 탐색하는 과정은 클래스 기반 언어의 상속과 거의 동일하다. 단지 정적인 클래스 간의 관계가 아니라 동적인 객체 사이의 위임을 통해 상속을 구현하고 있을 뿐이다.

**결국 객체지향은 객체를 지향하는 것이다. 클래스는 객체를 편리하게 정의하고 생성하기 위해 제공되는 프로그래밍의 구성 요소일 뿐이며 중요한 것은 메시지와 협력이다. 클래스 없이도 객체 사이의 협력 관계를 구축하는 것이 가능하며 상속 없이도 다형성을 구현하는 것이 가능하다.**

### 느낀점

객체지향이라는 프로그래밍 패러다임을 다시한번 멀리서 바라볼 수 있던 챕터인 것 같다. 언어나 툴은 도구에 가깝다는 말을 항상 기억하고 공부하는데, 객체지향은 도구보다 프로그래밍 가치관에 가까운 것 같다. 본질적이며 설계적이고 매우 치밀하다.

유연한 협력을 만들기 위해 생각해야 하는 구조는 사람마다 다르게 나올 수 있어도 모두가 똑같이 바라봐야 하는 청사진은 객체이며, 이들간의 유기적인 협력 그리고 그 객체들이 가지는 책임을 잘 이해하고 설계하는 것이 중요한 것 같다.

개인적으로 계속해서 객체지향에 대한 공부를 진행하면서 점점 더 멀리서 바라보게 되는 것 같다. 가장 중요한 점은 이 책은 코딩을 잘하게 해주는 책이 아니라는 점.

#### 논의사항

- 최근에 멘토님과 대화하다 나온 이야기로 인터페이스를 통한 퍼블릭 메서드 호출과 델리게이트의 호출에 대한 차이점을 고민해보면 좋을 것 같다는 이야기가 나왔습니다. 두 개의 차이점을 이야기 해보고 언제 선택해서 사용해야 할지 논의해보면 좋을 것 같습니다.
