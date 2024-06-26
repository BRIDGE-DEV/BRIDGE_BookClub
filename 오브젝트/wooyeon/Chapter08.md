# 오브젝트

## 8장. 의존성 관리하기

잘 설계된 객체지향 애플리케이션은 작고 응집도 높은 객체들로 구성된다.

작고 응집도 높은 객체란 책임의 초점이 명확하고 한 가지 일만 잘 하는 객체를 의미한다.

이런 작은 객체들이 단독으로 수행할 수 있는 자업은 거의 없기 때문에 일반적인 애플리케이션의 기능을 구현하기 위해서는 다른 객체에게 도움을 요청해야 한다.

이런 요청이 객체 사이의 협력을 낳는다.

<br>

협력은 필수적이지만 과도한 협력은 설계를 곤경에 빠트릴 수 있다.

협력은 객체가 다른 객체에 대해 알 것을 강요한다.

다른 객체와 협력하기 위해서는 그런 객체가 존재한다는 사실을 알고 있어야 한다.

객체가 수신할 수 있는 메시지에 대해서도 알고 있어야 한다.

이런 지식이 객체 사이의 의존성을 낳는다.

<br>

협력을 위해서는 의존성이 필요하지만 과도한 의존성은 애플리케이션을 수정하기 어렵게 만든다.

객체지향 설계의 핵심은 협력을 위해 필요한 의존성을 유지하면서도 변경을 방해하는 의존성은 제거하는데 있다.

이런 관점에서 객체지향 설계란 의존성을 관리하는 것이고 객체가 변화를 받아들일 수 있게 의존성을 정리하는 기술이라고 할 수 있다.

이번 장에서는 충분히 협력적이면서도 유연한 객체를 만들기 위해 의존성을 관리하는 방법을 살펴본다. 먼저 의존성이란 무엇인지를 알아보는 것으로 시작하자.

<br>

### 01. 의존성 이해하기

#### 변경과 의존성

어떤 객체가 협력하기 위해 다른 객체를 필요로 할 때 두 객체 사이에 의존성이 존재하게 된다.

의존성은 실행 시점과 구현 시점에 서로 다른 의미를 가진다.

- **실행 시점**: 의존하는 객체가 정상적으로 동작하기 위해서는 실행 시에 의존 대상 객체가 반드시 존재해야 한다.
- **구현 시점**: 의존 대상 객체가 변경될 경우 의존하는 객체도 함께 변경된다.

<br>

어떤 객체가 예정된 작업을 정상적으로 수행하기 위해 다른 객체를 필요로 하는 경우 두 객체 사이에 의존성이 존재한다고 말한다.

의존성은 방향성을 가지며 항상 단방향이다.

(점선 화살표로 표시 의존받는것->의존하는 것)

<br>

(설계와 관련된 대부분의 용어들은 변경과 관련이 있다. 의존성도 마찬가지다.)

두 요소 사이의 의존성은 의존되는 요소가 변경될 때 의존하는 요소도 함께 변경될 수 있다는 것을 의미한다.

따라서 의존성은 변경에 의한 영향의 전파 가능성을 암시한다.

<br>

#### 의존성 전이

의존성은 전이될 수 있다.

**의존성 전이(transive dependency)** 가 의미하는 것은 A가 B에 의존할 경우 A는 B가 의존하는 대상에 대해서도 자동적으로 의존하게 된다는 것이다.

의존성은 함께 변경될 수 있는 _가능성_ 을 의미하기 때문에 모든 경우에 의존성이 전이되는 것은 아니다.

의존성이 실제로 전이될지 여부는 변경의 방향과 캡슐화의 정도에 따라 달라진다.

(B가 의존하고 있는 어떤 요소의 구현이나 인터페이스가 변경되는 경우에 B가 내부 구현을 효과적으로 캡슐화하고 있다면 B에 의존하고 있는 A까지는 변경이 전파되지 않을 것이다.)

<br>

의존성은 전이될 수 있기 때문에 의존성의 종류를 **직접 의존성(direct dipendency)** 과 **간접 의존성(indirect dependency)** 으로 나누기도 한다.

- 직접 의존성: (말 그대로) 한 요소가 다른 요소에 직접 의존하는 경우
- 간접 의존성: 직접적인 관계는 존재하지 않지만 의존성 전이에 의해 영향이 전파되는 경우

의존성의 대상은 클래스 뿐만 아니라 객체나 모듈, 더 큰 규모의 실행 시스템일 수도 있다.

하지만 의존성의 본질은 변하지 않는다. 의존성이란 의존하고 있는 대상의 변경에 영향을 받을 수 있는 가능성이다.

<br>

#### 런타임 의존성과 컴파일 의존성

의존성과 관련해서 다뤄야 하는 또 다른 주제는 **런타임 의존성(run-time dependency)** 과 **컴파일타임 의존성(compile-time dependency)** 의 차이다.

런타임은 간단하다. 말 그대로 애플리케이션이 실행되는 시점을 가리킨다.

컴파일타임은 일반적으로 작성된 코드를 컴파일하는 시점을 가리키지만 문맥에 따라서는 코드 그 자체를 가리키기도 한다.

컴파일타임 의존성이라는 용어가 중요하게 생각하는 것은 시간이 아니라 우리가 작성한 코드의 구조이기 때문이다.

또한 동적 타입 언어의 경우에는 컴파일타임이 존재하지 않기 때문에 컴파일타임 의존성이라는 용어를 실제로 컴파일이 수행되는 시점으로 이해하면 의미가 모호해질 수 있다.

<br>

객체지향 애플리케이션에서 런타임의 주인공은 객체다. 따라서 런타임 의존성이 다루는 주제는 객체 사이의 의존성이다.

반면 코드 관점에서 주인공은 클래스다. 따라서 컴파일타임 의존성이 다루는 주제는 클래스 사이의 의존성이다.

여기서 중요한 것은 런타임 의존성과 컴파일타임 의존성이 다를 수 있다는 것이다.

사실 유연하고 재사용 가능한 코드를 설계하기 위해서는 두 종류의 의존성을 서로 다르게 만들어야 한다.

(Movie가 DiscountPolicy(추상 클래스)에 의존하면 _Movie 클래스_ 는 AmountDiscountPolicy 와 PercentDiscountPolicy 두 클래스 모두 알지 못하지만, _Movie 객체_ 는 두 클래스의 인스턴스와 협력할 수 있다.)

유연하고 재사용 가능한 설계를 창조하기 위해서는 동일한 소스코드 구조를 가지고 다양한 실행 구조를 만들 수 있어야 한다.

<br>

어떤 클래스의 인스턴스가 다양한 클래스의 인스턴스와 협력하기 위해서는 협력할 인스턴스의 구체적인 클래스를 알아서는 안 된다.

실제로 협력할 객체가 어떤 것인지는 런타임에 해결해야 한다.

클래스가 협력할 객체의 클래스를 명시적으로 드러내고 있다면 다른 클래스의 인스턴스와 협력할 가능성 자체가 없어진다.

따라서 컴파일타임 구조와 런타임 구조 사이의 거리가 멀면 멀수록 설계가 유연해지고 재사용 가능해진다.

<br>

#### 컨텍스트 독립성

이제 유연하고 확장 가능한 설계를 만들기 위해서는 컴파일타임 의존성과 런타임 의존성이 달라야 한ㄴ다는 사실을 이해했을 것이다.

클래스는 자신과 협력할 객체의 구체적인 클래스에 대해 알아서는 안 된다.

구체적인 클래스를 알면 알수록 그 클래스가 사용되는 특정한 문맥에 강하게 결합되기 때문이다.

<br>

구체적인 클래스에 대해 의존하는 것은 클래스의 인스턴스가 어떤 문맥에서 사용될 것인지를 구체적으로 명시하는 것과 같다.

클래스가 특정한 문맥에 강하게 결합될수록 다른 문맥에서 사용하기는 더 어려워진다.

클래스가 사용될 특정한 문맥에 강하게 결합될수록 다른 문맥에서 사용하기는 더 어려워진다.

클래스가 사용될 특정한 문맥에 대해 최소한의 가정만으로 이뤄져 있다면 다른 문맥에서 재사용하기가 더 수월해진다.

이를 **컨텍스트 독립성**이라고 부른다.

<br>

설계가 유연해지기 위해서는 가능한 자신이 실행될 컨텍스트에 대한 구체적인 정보를 최대한 적게 알아야 한다.

컨텍스트에 대한 정보가 적으면 적을수록 더 다양한 컨텍스트에서 재사용될 수 있기 때문이다.

결과적으로 설계는 더 유연해지고 변경에 탄력적으로 대응할 수 있게 될 것이다.

> 컨텍스트 독립성을 따르면 다양한 컨텍스트에 적용할 수 있는 응집력 있는 객체를 만들 수 있고 객체 구성 방법을 제설정하여 변경 가능한 시스템으로 나아갈 수 있다.

<br>

이제 마지막 연결 고리만 남았다. 클래스가 실행 컨텍스트에 독립적인데도 어떻게 런타임에 실행 컨텍스트에 적절한 객체들과 협력할 수 있을까?

<br>

#### 의존성 해결하기

컴파일타임 의존성은 구체적인 런타임 의존성으로 대체돼야 한다.

컴파일타임 의존성을 실행 컨텍스트에 맞는 적절한 런타임 의존성으로 교체하는 것을 **의존성 해결**이라고 부른다.

의존성을 해결하기 위한 세 가지 방법
- 객체를 생성하는 시점에 생성자를 통해 의존성 해결
- 객체 생성 후 setter 메서드를 통해 의존성 해결
- 메서드 실행 시 인자를 이용해 의존성 해결

<br>

setter 메서드를 이용하는 방법은 실행 시점에 의존 대상을 변경할 수 있기 때문에 설계를 좀 더 유연하게 만들 수 있다.

단점은 객체가 생성된 후에 협력에 필요한 의존 대상을 설정하기 때문에 객체를 생성하고 의존 대상을 설정하기 전까지는 객체의 상태가 불완전할 수 있다는 점이다.

더 좋은 방법은 생성자 방식과 setter 방식을 혼합하는 것이다.

항상 객체를 생성할 때 의존성을 해결해서 완전한 상태의 객체를 생성한 후, 필요에 따라 setter 메서드를 이용해 의존 대상을 변경할 수 있게 할 수 있다.

이 방법은 시스템의 상태를 안정적으로 유지하면서도 유연성을 향상시킬 수 있기 때문에 의존성 해결을 위해 가장 선호되는 방법이다.

<br>

메서드 인자를 사용하는 방식은 협력 대상에 대해 지속적으로 의존 관계를 맺을 필요 없이 메서드가 실행되는 동안만 일시적으로 의존 관계가 존재해도 무방하거나, 메서드가 실행될 때마다 의존 대상이 매번 달라져야 하는 경우에 유용하다.

하지만 클래스의 메서드를 호출하는 대부분의 경우에 매번 동일한 객체를 인자로 전달하고 있다면 생성자나 setter 메서드를 이용하는 방식으로 변경하는 것이 좋다.

<br>

### 02. 유연한 설계

설계를 유연하고 재사용 가능하게 만들기로 결정했다면 의존성을 관리하는 데 유용한 몇 가지 원칙과 기법을 익힐 필요가 있다. 먼저 의존성과 결합도의 관계를 살펴보는 것으로 시작하자.

<br>

#### 의존성과 결합도

객체지향 패러다임의 근간은 협력이다.

객체들은 협력을 통해 애플리케이션에 생명력을 불어넣는다.

객체들이 협력하기 위해서는 서로의 존재와 수행 가능한 책임을 알아야 한다.

이런 지식들이 객체 사이의 의존성을 낳는다. 따라서 모든 의존성이 나쁜 것은 아니다.

의존성은 객체들의 협력을 가능하게 만드는 매개체라는 관점에서는 바람직한 것이다.

하지만 의존성이 과하면 문제가 될 수 있다.

(구체적인 클래스에 의존하게 만들었다면 다른 문맥에서 해당 재사용할 수 없다.)

<br>

해결 방법은 의존성을 바람직하게 만드는 것이다.

(자신이 전송하는 메시지를 이해할 수만 있다면 어떤 타입의 객체와 협력하더라도 상관이 없다.)

의존성 자체는 나쁜 것이 아니며, 협력을 위해 반드시 필요한 것이다.

단지 바람직하지 못한 의존성이 문제일 뿐이다.

<br>

그렇다면 바람직한 의존성이란 무엇인가?

바람직한 의존성은 **재사용성**과 관련이 있다.

다양한 환경에서 클래스를 재사용할 수 없도록 제한한다면 그 의존성은 바람직하지 못한 것이다.

어떤 의존성이 다양한 환경에서 재사용할 수 있다면 그 의존성은 바람직한 것이다.

_항상 적용되는 것은 아니고 변경 가능성이 큰 설계에서의 이야기가 아닐까.._

다시 말해 컨텍스트에 독립적인 의존성은 바람직한 의존성이고 특정한 컨텍스트에 강하게 결합된 의존성은 바람직하지 않은 의존성이다.

특정한 컨텍스트에 강하게 의존하는 클래스를 다른 컨텍스트에서 재사용하고 싶다면 구현을 변경(코드를 수정)할 수 밖에 없다. 결국 이는 바람직하지 못한 의존성을 바람직하지 못한 또 다른 의존성으로 대체한 것 뿐이다.

<br>

바람직한 의존성과 바람직하지 못한 의존성을 가리키는 좀 더 세련된 요어가 존재한다. **결합도**가 바로 그것이다.

어떤 두 요소 사이에 존재하는 의존성이 바람직할 때 두 요소가 **느슨한 결합도(loose coupling)** 또는 **약한 결합도(weak coupling)**을 가진다고 말한다.

반대의 경우 **단단한 결합도(tight coupling)** 또는 **강한 결합도(strong coupling)**를 가진다고 말한다.

> 하지만 의존성은 두 요소 사의의 관계 유무를, 결합도는 두 요소 사이에 존재하는 의존성의 정도를 상대적으로 표현하기 때문에 관점이 다르다.

<br>

#### 지식이 결합을 낳는다

결합도의 정도는 한 요소가 자신이 의존하고 있는 다른 요소에 대해 알고 있는 정보의 양으로 결정된다.

정보가 많을수록 두 요소는 강하게, 적을수록 두 요소는 약하게 결합된다.

더 많이 알수록 더 많이 결합된다.

더 많이 알고 있다는 것은 더 적은 컨텍스트에서 재사용 가능하다는 것을 의미한다.

<br>

결합도를 느슨하게 만들기 위해서는 협력하는 대상에 대해 필요한 정보 외에는 최대한 감추는 것이 중요하다. <br>
=> 효과적인 방법: 추상화

<br>

#### 추상화에 의존하라

추상화란 어떤 양상, 세부사항, 구조를 좀 더 명확하게 이해하기 위해 특정 절차나 물체를 의도적으로 생략하거나 감춤으로써 복잡도를 극복하는 방법이다.

추상화를 사용하면 현재 다루고 있는 문제를 해결하는 데 불필요한 정보를 감출 수 있다.

따라서 대상에 대해 알아야 하는 지식의 양을 줄일 수 있기 때문에 결합도를 느슨하게 유지할 수 있다.

<br>

일반적으로 추상화와 결합도의 관점에서 의존 대상을 다음과 같이 구분하는 것이 유용하다.

목록에서 아래쪽으로 갈수록 클라이언트가 알아야 하는 지식의 양이 적어지기 때문에 결합도가 느슨해진다.

- 구체 클래스 의존성(concerte class dependency)
- 추상 클래스 의존성(abstract class dependency)
- 인터페이스 의존성(interface class dependency)

추상 클래스의 클라이언트는 협력하는 대상이 속한 클래스 상속 계층이 무엇인지에 대해서는 알고 있어야 한다.

인터페이스에 의존하면 상속 계층을 모르더라도 협력이 가능해진다.

이것은 다양한 클래스 상속 계층에 속한 객체들이 동일한 메시지를 수신할 수 있도록 컨텍스트를 확장하는 것을 가능하게 한다.

<br>

중요한 것은 실행 컨텍스트에 대해 알아야 하는 정보를 줄일수록 결합도가 낮아진다는 것이다. 의존하는 대상이 더 추상적일수록 결합도는 더 낮아진다.

<br>

#### 명시적인 의존성

결합도를 느슨하게 만들기 위해서는 인스턴스 변수의 타입을 추상 클래스나 인터페이스로 선언하는 것만으로는 부족하다.

클래스 안에서 구체 클래스에 대한 모든 의존성을 제거해야만 한다.

트릭은 인스턴스 변수의 타입은 추상 클래스나 인터페이스로 정의하고 생성자, setter 메서드, 메서드 인자로 의존성을 해결할 때는 추상 클래스를 상속받거나 인터에피스를 실체화한 구체 클래스를 전달하는 것이다.

<br>

의존성의 대상을 생성자의 인자로 전달받는 방법과 생성자 안에서 직접 생성하는 방법 사이의 가장 큰 차이점은 퍼블릭 인터페이스를 통해 방법을 제공하는지 여부다.

모든 경우에 의존성은 명시적으로 퍼블릭 인터페이스에 노출된다. 이를 **명시적인 의존성(explicit dependency)** 이라고 부른다.

의존성이 퍼블릭 인터페이스에 표현되지 않는 경우 이를 **숨겨진 의존성(hidden dependency)** 이라고 부른다.

<br>

의존성이 명시적이지 않으면 내부 구현을 뜯어봐야 하고, 심지어는 다른 컨텍스트에서 재사용하기 위해 내부 구현을 직접 변경해야 할 수도 있다.

(코드 수정은 잠재적으로 버그의 발생 가능성을 내포한다.)

의존성을 명시적으로 드러내면 코드를 직접 수정해야 하는 위험을 피할 수 있다.

실행 컨텍스트에 적절한 의존성을 선택할 수 있기 때문이다.

<br>

의존성은 명시적으로 표현돼야 한다. 의존성을 구현 내부에 숨겨두지 마라.

유연하고 재사용 가능한 설계란 퍼블릭 인터페이스를 통해 의존성이 명시적으로 드러나는 설계다.

명시적인 의존성을 사용해야만 퍼블릭 인터페이스를 통해 컴파일타임 의존성을 적절한 런타임 의존성으로 교체할 수 있다.

<br>

의존성은 다른 객체와의 협력을 가능하게 해주기 때문에 바람직한 것이다.

경계해야 할 것은 의존성 자체가 아니라 의존성을 감추는 것이다. 의존성을 드러내고 알려라. 그렇게 하면 설계가 유연하고 재사용 가능해질 것이다.

#### new는 해롭다

대부분의 언어에서는 클래스의 인스턴스를 생성할 수 있는 `new` 연산자를 제공한다.

하지만 안타깝게도 new를 잘못 사용하면 클래스 사이의 결합도가 극단적으로 높아진다.

결합도 측면에서 new가 해로운 이유는 크게 두 가지다.
- new 연산자를 사용하기 위해서는 구체 클래스의 이름을 직접 기술해야 한다. 따라서 new를 사용하는 클라이언트는 추상화가 아닌 구체 클래스에 의존할 수밖에 없기 때문에 결합도가 높아진다.
- new 연산자는 생성하려는 구체 클래스뿐만 아니라 어떤 인자를 이용해 클래스의 생성자를 호출해야 하는지도 알아야 한다. 따라서 new를 사용하면 클라이언트가 알아야 하는 지식의 양이 늘어나기 때문에 결합도가 높아진다.

<br>

구체 클래스에 직접 의존하면 결합도가 높아진다. (너무 많은 지식을 알도록 강요)

new는 여기에다가 구체 클래스를 생성하는 데 어떤 정보가 필요한지에 대해서도 알아야 한다. (더 큰 문제)

_예제를 보니 문제가 확 다가왔다. (이렇게 짜는 사람은 없겠고 완전 나쁜 케이스의 코드지만)_

해결 방법은 인스턴스를 생성하는 로직과 생성된 인스턴스를 사용하는 로직을 분리하는 것이다. (사용과 생성의 책임 분리)

인스턴스를 생성하는 책임을 옮기면 인스턴스를 사용하는 책임만 남는다.

<br>

사용과 생성의 책임을 분리하고, 의존성을 생성자에 명시적으로 드러내고, 구체 클래스가 아닌 추상 클래스에 의존하게 함으로써 설계를 유연하게 만들 수 있다.

올바른 객체가 올바른 책임을 수행하게 하는 것이 훌륭한 설계를 창조하는 기반이다.

<br>

#### 가끔은 생성해도 무방하다

클래스 안에서 객체의 인스턴스를 직접 생성하는 방식이 유용한 경우도 있다.

주로 협력하는 기본 객체를 설정하고 싶은 경우가 여기에 속한다.

(클래스가 A 인스턴스와 협력하고 가끔씩만 B 인스턴스와 협력한다면? 모든 경우에 인스턴스를 생성하는 책임을 클라이언트로 옮긴다면 클라이언트들 사이의 중복 코드가 늘어나고 클래스의 사용성도 나빠질 것<br>
=> 기본 객체를 생성하는 생성자를 추가하고 이 생성자에서 (A, B의 부모) 추상 클래스의 인스턴스를 인자로 받는 생성자를 체이닝)

![KakaoTalk_20240328_055750895](https://github.com/BRIDGE-DEV/BRIDGE_BookClub/assets/80298207/ce786167-cdc9-489d-b82f-02cbed11a1ef)

_체이닝이 뭔가 했는데 이해하기 정말 좋은 예제!_

눈여겨볼 부분은 첫 번째 생성자의 내부에서 두 번째 생성자를 호출한다는 것이다.

다시 말해 생성자가 체인처럼 연결된다.

(이 방법은 메서드를 오버로딩하는 경우에도 사용할 수 있다.)

<br>

구체 클래스에 의존하게 되더라도 클래스의 사용성이 더 중요하다면 결합도를 높이는 방향으로 코드를 작성할 수 있다. (결합도와 사용성의 트레이드 오프)

그럼에도 가급적으로 구체 클래스에 대한 의존성을 제거할 수 있는 방법을 찾아보기 바란다.

종종 모든 결합도가 모이는 새로운 클래스를 추가함으로써 사용성과 유연성이라는 두 마리 토끼를 잡을 수 있는 경우도 있다.

<br>

#### 표준 클래스에 대한 의존은 해롭지 않다

의존성이 불편한 이유는 그것이 항상 변경에 대한 영향을 암시하기 때문이다.

따라서 변경될 확률이 거의 없는 클래스라면 의존성이 문제가 되지 않는다.

(구체 클래스에 의존하거나 직접 인스턴스를 생성하더라도 ok)

<br>

#### 컨텍스트 확장하기

- 할인 혜택을 제공하지 않는 영화 예매 구현 예제
   - null로 두고 null 체크하는 방식은 코드 내부를 직접 수정 -> 버그의 발생 야기
   - 할인 정책이 없다는 것 자체를 하나의 할인 정책으로 간주 -> 새 클래스 생성 => 예외처리 필요 X
- 중복 적용이 가능한 할인 정책 구현 예제
   - 앞선 예제처럼 중복 할인 정책 또한 할인 정책의 한 가지로 간주 => 기존의 협력 방식(코드)을 수정하지 않아도 됨

설계를 유연하게 만들 수 있었던 이유는 추상화, 명시적으로 드러낸 의존성, 책임 이동 덕분이다.

결합도를 낮춤으로써 얻게 되는 컨텍스트의 확장이라는 개념이 유연하고 재사용 가능한 설계를 만드는 핵심이다.

<br>

#### 조합 가능한 행동

어떤 객체와 협력하느냐에 따라 객체의 행동이 달라지는 것은 유연하고 재사용 가능한 설계가 가진 특징이다.

유연하고 재사용 가능한 설계는 응집도 높은 책임들을 가진 작은 객체들을 다양한 방식으로 연결함으로써 애플리케이션의 기능을 쉽게 확장할 수 있다.

<br>

유연하고 재사용 가능한 설계는 객체가 어떻게(how) 하는지를 장황하게 나열하지 않고도 객체들의 조합을 통해 무엇(what)을 하는지를 표현하는 클래스들로 구성된다.

따라서 클래스의 인스턴스를 생성하는 코드를 보는 것만으로 객체가 어떤 일을 하는지를 쉽게 파악할 수 있다.

코드에 드러난 로직을 해석할 필요 없이 객체가 어떤 객체와 연결됐는지를 보는 것만으로도 객체의 행동을 쉽게 예상하고 이해할 수 있기 때문이다.

다시 말해 선언적으로 객체의 행동을 정의할 수 있는 것이다.

<br>

유연하고 재사용 가능한 설계는 작은 객체들의 행동을 조합함으로써 새로운 행동을 이끌어낼 수 있는 설계다.

훌륭한 객체지향 설계란 객체가 어떻게 하는지를 표현하는 것이 아니라 객체들의 조합을 선언적으로 표현함으로써 객체들이 무엇을 하는지를 표현하는 설계다.

그리고 지금까지 설명한 것처럼 이런 설계를 창조하는 데 있어서의 핵심은 의존성을 관리하는 것이다.

<br>

### 생각

다시 영화 예매 예제가 등장한다. _재사용 잘하는 거 보면 잘 짠듯.._

의존성 관리도 내가 알고싶었던 내용이기도 한데,
아직 이렇게 유연한 설계가 필요했던 적이 없어서 한 번 경험해보고 싶다고 생각했다.

그리고 또 다시 추상화에 대한 중요성도 깨달았다.

장의 마지막에 항상 예외나 중점을 한 번씩 짚어줘서 좋다.

### 논의사항

> 클래스가 사용될 특정한 문맥에 대해 최소한의 가정만으로 이뤄져 있다면 다른 문맥에서 재사용하기가 더 수월해진다. 이를 **컨텍스트 독립성**이라고 부른다.

- 컨텍스트 독립성을 잘 생각하며 코드를 짜고 계신가요?

저는 아직 미숙한 것 같습니다..

고치면 재사용하기 좀 더 좋겠다 싶어 필요할 때 고쳤던 적도 많았네요.