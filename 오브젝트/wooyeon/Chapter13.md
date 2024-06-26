# 오브젝트

## 13장. 서브클래싱과 서브타이핑

객체지향 커뮤니티에 널리 퍼진 상속에 대한 해묵은 불신과 오해를 풀기 위해서는 상속이 두 가지 용도로 사용된다는 사실을 이해하는 것이 중요하다.

<br>

상속의 첫 번째 용도는 **타입 계층**을 구현하는 것이다.

타입 계층 안에서 부모 크래스는 일반적인 개념을 구현하고 자식 클래스는 특수한 개념을 구현한다. 타입 계층의 관점에서 부모 클래스는 자식 클래스의 일반화(generalization)이고 자식 클래스는 부모 클래스의 특수화(specialization)이다.

<br>

상속의 두 번째 용도는 **코드 재사용**이다.

상속은 간단한 선언만으로 부모 클래스의 코드를 재사용할 수 있다.

상속을 사용하면 점진적으로 애플리케이션의 기능을 확장할 수 있다.

하지만 재사용을 위해 상속을 사용할 경우 부모 클래스와 자식 클래스가 강하게 결합되기 때문에 변경하기가 어려운 코드를 얻게 될 확률이 높다.

<br>

상속을 사용하는 일차적인 목표는 코드 재사용이 아니라 타입 계층을 구현하는 것이어야 한다.

상속은 코드를 쉽게 재사용할 수 있는 방법을 제공하지만 부모 클래스와 자식 클래스를 강하게 결합시키기 때문에 설계의 변경과 진화를 방해한다.

반면 타입 계층을 목표로 상속을 사용하면 다형적으로 동작하는 객체들의 관계에 기반해 확장 가능하고 유연한 설계를 얻을 수 있게 된다.

<br>

결론부터 말하자면 동일한 메시지에 대해 서로 다르게 행동할 수 있는 다형적인 객체를 구현하기 위해서는 객체의 행동을 기반으로 타입 계층을 구성해야 한다.

상속의 가치는 이러한 타입 계층을 구현할 수 있는 쉽고 편안한 방법을 제공하는 데 있다.

타입 사이의 관계를 고려하지 않은 채 단순히 코드를 재사용하기 위해 상속을 사용해서는 안 된다.

<br>

이번 장에서는 올바른 타입 계층을 구성하는 원칙을 살펴보기로 한다.

이번 장을 읽고 나면 상속이 서브타입 다형성과 동적 메서드 탐색에 밀접하게 연관돼 있다는 사실을 알게 될 것이다.

그렇다면 타입 계층이란 무엇인가? 상속을 이용해 타입 계층을 구현한다는 것이 무엇을 의미하는가? 이 질문의 답을 찾기 위해 먼저 타입과 타입 계층의 개념을 알아보자.

<br>

```
객체기반 프로그래밍이란 상태와 행동을 캡슐화한 객체를 조립해서 프로그램을 구성하는 방식을 가리킨다.
이 정의에 따르면 객체지향 프로그래밍 역시 객체기반 프로그래밍의 한 종류다.

객체지향 프로그래밍은 객체기반 프로그래밍과 마찬가지로 객체들을 조합해서 애플리케이션을 개발하지만
상속과 다형성을 지원한다는 점에서 객체기반 프로그래밍과 차별화된다.
간단히 말해서 객체지향 프로그래밍은 상속과 다형성을 지원하지만 객체기반 프로그래밍은 지원하지 않는다.
```

<br>

### 01. 타입

객체지향 프로그래밍에서 타입의 의미를 이해하려면 프로그래밍 언어 관점에서 타입과 개념 관점에서의 타입을 함께 살펴볼 필요가 있다.

<br>

#### 개념 관점의 타입

개념 관점에서 타입이란 우리가 인지하는 세상의 사물의 종류를 의미한다.

다시 말해 우리가 인식하는 객체들에 적용하는 개념이나 아이디어를 가리켜 타입이라고 부른다.

예를 들어, 자바, 루비, 자바스크립트, C를 프로그래밍 언어라고 부를 때 우리는 이것들을 프로그래밍 언어라는 타입으로 분류하고 있는 것이다.

<br>

어떤 대상이 타입으로 분류될 때 그 대상을 타입의 **인스턴스(instance)** 라고 부른다.

자바, 루비, 자바 스크립트, C는 프로그래밍 언어의 인스턴스다.

일반적으로 타입의 인스턴스를 **객체**라고 부른다.

<br>

지금까지의 설명을 통해 타입이 심볼, 내연, 외연의 세 가지 요소로 구성된다는 사실을 알 수 있다.

- **심볼(symbol)**: 타입에 이름을 붙인 것. ('프로그래밍 언어')
- **내연(intenstion)**: 타입의 정의로서 타입에 속하는 객체들이 가지는 공통적인 속성이나 행동. (프로그래밍 언어의 정의인 '컴퓨터에게 특정한 작업을 지시하기 위한 어휘와 문법적 규칙의 집합')
- **외연(extention)**: 타입에 속하는 객체들의 집합이다. (자바, 루비, 자바스크립트, C가 속한 집합)

<br>

#### 프로그래밍 언어 관점의 타입

프로그래밍 언어 관점에서 타입은 연속적인 비트에 의미와 제약을 부여하기 위해 사용된다.

하드웨어는 데이터를 0과 1로 구성된 일련의 비트 조합으로 취급한다.

하지만 비트 자체에는 타입이라는 개념이 존재하지 않는다.

비트에 담긴 데이터를 문자열로 다룰지, 정수로 다룰지는 전적으로 데이터를 사용하는 애플리케이션에 의해 결정된다.

따라서 프로그래밍 언어의 관점에서 타입은 비트 묶음에 의미를 부여하기 위해 정의된 제약과 규칙을 가리킨다.

<br>

프로그래밍 언어에서 타입은 두 가지 목적을 위해 사용된다.

##### 타입에 수행될 수 있는 유효한 오퍼레이션의 집합을 정의한다

자바에서 '+' 연산자는 원시형 숫자 타입이나 문자열 타입의 객체에는 사용할 수 있지만 다른 클래스의 인스턴스에 대해서는 사용할 수 없다. 하지만 C++와 C#에서는 연산자 오버로딩을 통해 '+' 연산자를 사용하는 것이 가능하다. 여기서 중요한 것은 모든 객체지향 언어들은 객체의 타입에 따라 적용 가능한 연산자의 종류를 제한함으로써 프로그래머의 실수를 막아준다는 것이다.

##### 타입에 수행되는 오퍼레이션에 대해 미리 약속된 문맥을 제공한다

예를 들어 자바에서 a + b라는 연산이 있을 때 a와 b의 타입이 int라면 두 수를 더할 것이다. 하지만 a와 b의 타입이 String이라면 두 문자열을 하나의 문자열로 합칠 것이다. 따라서 a와 b에 부여된 타입이 '+' 연산자의 문맥을 정의한다. 비슷한 예로 자바와 C#의 new 연산자는 타입에 정의된 크기만큼 저장 공간을 할당하고 생성된 객체를 초기화하기 위해 타입의 생성자를 자동으로 호출한다. 이 경우 객체를 생성하는 방법에 대한 문맥을 결정하는 것은 바로 객체의 타입이다.

정리하면 타입은 적용 가능한 오퍼레이션의 종류와 의미를 정의함으로써 코드의 의미를 명확하게 전달하고 개발자의 실수를 방지하기 위해 사용된다. 이제 타입의 개념을 객체지향 패러다임의 관점에서 확장해보자.

<br>

#### 객체지향 패러다임 관점의 타입

지금까지의 내용을 바탕으로 타입을 다음과 같은 두 가지 관점에서 정의할 수 있다.

- 개념 관점에서 타입이란 공통의 특징을 공유하는 대상들의 분류다.
- 프로그래밍 언어 관점에서 타입이란 동일한 오퍼레이션을 적용할 수 있는 인스턴스들의 집합이다.

이제 이 두 정의를 객체지향 패러다임의 관점에서 조합해보자.

프로그래밍 언어의 관점에서 타입은 호출 가능한 오퍼레이션의 집합을 정의한다.

객체지향 프로그래밍에서 오퍼레이션은 객체가 수신할 수 있는 메시지를 의미한다.

따라서 객체의 타입이란 객체가 수신할 수 있는 메시지의 종류를 정의하는 것이다.

<br>

우리는 이미 객체가 수신할 수 있는 메시지의 집합을 가리키는 멋진 용어를 알고 있다.

바로 **퍼블릭 인터페이스**다.

객체지향 프로그래밍에서 타입을 정의하는 것은 객체의 퍼블릭 인터페이스를 정의하는 것과 동일하다.

<br>

개념 관점에서 타입은 공통의 특성을 가진 객체들을 분류하기 위한 기준이다.

그렇다면 여기서 공통의 특성이란 무엇인가?

타입이 오퍼레이션을 정의한다는 사실을 기억하면 쉽게 답을 구할 수 있을 것이다.

객체지향에서는 객체가 수신할 수 있는 메시지를 기준으로 타입을 분류하기 때문에 동일한 퍼블릭 인터페이스를 가지는 객체들은 동일한 타입으로 분류할 수 있다.

<br>

객체지향 프로그래밍 관점에서 타입을 다음과 같이 정의할 수 있다.

> 객체의 퍼블릭 인터페이스가 객체의 타입을 결정한다. 따라서 동일한 퍼블릭 인터페이스를 제공하는 객체들은 동일한 타입으로 분류된다.

타입의 정의는 지금까지 줄곧 강조해왔던 객체에 관한 한 가지 사실을 다시 한번 강조한다.

객체에게 중요한 것은 속성이 아니라 행동이라는 사실이다.

어떤 객체들이 동일한 상태를 가지고 있더라도 퍼블릭 인터페이스가 다르다면 이들은 서로 다른 타입으로 분류된다.

반대로 어떤 객체들이 내부 상태는 다르지만 동일한 퍼블릭 인터페이스를 공유한다면 이들은 동일한 타입으로 분류된다.

<br>

객체를 바라볼 때는 항상 객체가 외부에 제공하는 행동에 초점을 맞춰야 한다.

객체의 타입을 결정하는 것은 내부의 속성이 아니라 객체가 외부에 제공하는 행동이라는 사실을 기억하라.

<br>

### 02. 타입 사이의 포함관계
#### 타입 사이의 포함관계

수학에서 집합은 다른 집합을 포함할 수 있다.

타입 역시 객체들의 집합이기 때문에 다른 타입을 포함하는 것이 가능하다.

타입 안에 포함된 객체들을 좀 더 상세한 기준으로 묶어 새로운 타입을 정의하면 이 새로운 타입은 자연스럽게 기존 타입의 부분집합이 된다.

이 집합의 원소들을 좀 더 상세한 기준에 따라 분류할 수 있다.

<br>

타입이 다른 타입에 포함될 수 있기 때문에 동일한 인스턴스가 하나 이상의 타입으로 분류되는 것도 가능하다.

다른 타입을 포함하는 타입은 포함되는 타입보다 좀 더 일반화된 의미를 표현할 수 있다. 반면 포함되는 타입은 좀 더 특수하고 구체적이다.

다른 타입을 포함하는 타입은 포함되는 타입보다 더 많은 인스턴스를 가진다.

다시 말해서 포함하는 타입은 외연 관점에서는 더 크고 내연 관점에서는 더 일반적이다. 이와 반대로 포함되는 타입은 외연 관점에서는 더 작고 내연 관점에서는 더 특수하다.

이것은 포함 관계로 연결된 타입 사이에 개념적으로 일반화와 특수화 관계가 존재한다는 것을 의미한다.

<br>

타입들을 일반화와 특수화 관계를 가친 계층으로 표현할 수 있다. (일반적인 타입을 위로, 특수한 타입을 아래쪽에 배치하는 것이 관례)

타입 계층을 구성하는 두 타입 간의 관계에서 더 일반적인 타입을 **슈퍼타입(supertype)** 이라고 부르고 더 특수한 타입을 **서브타입(subtype)**이라고 부른다.

<br>

이제 내연과 외연의 관점에서 일반화와 특수화를 정의해보자.

객체의 정의를 의미하는 내연 관점에서 일반화란 어떤 타입의 정의를 좀 더 보편적이고 추상적으로 만드는 과정을 의미한다. 반대로 특수화란 어떤 타입의 정의를 좀 더 구체적이고 문맥 종속적으로 만드는 과정을 의미한다.

내연의 관점에서 특수한 타입의 언어는 일반적인 타입의 정의를 좀 더 구체화한 것이다.

집합을 의미하는 외연의 관점에서 일반적인 타입의 인스턴스 집합은 특수한 타입의 인스턴스 집합을 포함하는 슈퍼셋이다. 반대로 특수한 타입의 인스턴스 집합은 일반적인 타입의 인스턴스 집합에 포함된 서브셋이다.

따라서 특수한 타입에 속한 인스턴스는 동시에 더 일반적인 타입의 인스턴스이기도 한다.

<br>

일반화와 특수화를 다음과 같이 정의할 수 있다.

> 일반화는 다른 타입을 완전히 포함하거나 내포하는 타입을 식별하는 행위 또는 그 행위의 결과를 가리킨다. 특수화는 다른 타입 안에 전체적으로 포함되거나 완전히 내포되는 타입을 식별하는 행위 또는 그 행위의 결과를 가리킨다.

<br>

(쉽게 예상할 수 있겠지만 슈퍼타입과 서브타입이라는 용어는 슈퍼셋과 서브셋으로부터 유래한 것이다.)

- 슈퍼타입은 다음과 같은 특징을 가지는 타입을 가리킨다
   - 집합이 다른 집합의 모든 멤버를 포함한다.
   - 타입 정의가 다른 타입보다 좀 더 일반적이다.
- 서브타입은 다음과 같은 특징을 가지는 타입을 가리킨다.
   - 집합에 포함되는 인스턴스들이 더 큰 집합에 포함된다.
   - 타입 정의가 다른 타입보다 좀 더 구체적이다.

<br>

#### 객체지향 프로그래밍과 타입 계층

이제 객체지향 프로그래밍 관점에서 타입 정의가 더 일반적이고 더 특수하다는 사실이 어떤 의미를 가지는지 살펴보자.

객체의 타입을 결정하는 것은 퍼블릭 인터페이스다.

일반적인 타입이란 비교하려는 타입에 속한 객체들의 퍼블릭 인터페이스보다 더 일반적인 퍼블릭 인터페이스를 가지는 객체들의 타입을 의미한다.

특수한 타입이란 비교하려는 타입에 속한 객체들의 퍼블릭 인터페이스보다 더 특수한 퍼블릭 인터페이스를 가지는 객체들의 타입을 의미한다.

<br>

> 슈퍼타입이란 서브타입이 정의한 퍼블릭 인터페이스를 일반화시켜 상대적으로 범용적이고 넓은 의미로 정의한 것이다.

> 서브타입이란 슈퍼타입이 정의한 퍼블릭 인터페이스를 특수화시켜 상대적으로 구체적이고 좁은 의미로 정의한 것이다.

<br>

서브타입의 인스턴스는 슈퍼타입의 인스턴스로 간주될 수 있다. 이 사실이 이번 장의 핵심이다. 그리고 상속과 다형성의 관계를 이해하기 위한 출발점이다.

<br>

### 03. 서브클래싱과 서브타이핑

객체지향 프로그래밍 언어에서 타입을 구현하는 일반적인 방법은 클래스를 이용하는 것이다.

그리고 타입 계층을 구현하는 일반적인 방법은 상속을 이용하는 것이다.

상속을 이용해 타입 계층을 구현한다는 것은 부모 클래스가 슈퍼타입의 역할을, 자식 클래스가 서브타입의 역할을 수행하도록 클래스 사이의 관계를 정의한다는 것을 의미한다.

<br>

그렇다면 어떤 타입이 다른 타입의 서브타입이 되기 위해서는 어떤 조건을 만족해야 할까? 서브 타입의 퍼블릭 인터페이스가 슈퍼타입의 퍼블릭 인터페이스보다 더 특수하다는 것은 어떤 의미일까?

이제부터 타입 계층을 구현할 때 지켜야 하는 제약사항을 클래스와 상속의 관점에서 살펴보자.

<br>

#### 언제 상속을 사용해야 하는가?

반복해서 강조하지만 상속의 올바른 용도는 타입 계층을 구현하는 것이다.

그렇다면 어떤 조건을 만족시켜야만 타입 계층을 위해 올바르게 상속을 사용했다고 말할 수 있을까?

마틴 오더스키는 다음과 같은 질문을 해보고 두 질문에 모두 '예'라고 답할 수 있는 경우에만 상속을 사용하라고 조언한다.

##### 상속 관계가 is-a 관계를 모델링하는가?

이것은 애플리케이션을 구성하는 어휘에 대한 우리의 관점에 기반한다. 일반적으로 "[자식 클래스]는 [부모 클래스]다"라고 말해도 이상하지 않다면 상속을 사용할 후보로 간주할 수 있다.

##### 클라이언트 입장에서 부모 클래스의 타입으로 자식 클래스를 사용해도 무방한가?

상속 계층을 사용하는 클라이언트의 입장에서 부모 클래스와 자식 클래스의 차이점을 몰라야 한다. 이를 자식 클래스와 부모 클래스 사이의 **행동 호환성**이라고 부른다.

<br>

설계 관점에서 상속을 적용할지 여부를 결정하기 위해 첫 번째 질문보다는 두 번째 질문에 초점을 맞추는 것이 중요하다.

뒤에서 자세히 살펴보겠지만 클라이언트의 관점에서 두 클래스에 대해 기대하는 행동이 다르다면 비록 그것이 어휘적으로 is-a 관계로 표현할 수 있다고 하더라도 상속을 사용해서는 안 된다.

<br>

#### is-a 관계

어떤 타입 S가 다른 타입 T의 일종이라면 당연히 "타입 S는 타입 T다(S is-a T)"라고 말할 수 있어야 한다.

<br>

하지만 is-a 관계가 생각처럼 직관적이고 명쾌한 것은 아니다.

(스콧 마이어스의 <이펙티브 C++>의 예: 펭귄은 새다 / 새는 날 수 있다)

이 예는 어휘적인 정의가 아니라 기대되는 행동에 따라 타입 계층을 구성해야 한다는 사실을 잘 보여준다.

어휘적으로 펭귄은 새지만 만약 새의 정의에 날 수 있다는 행동이 포함된다면 펭귄은 새의 서브타입이 될 수 없다.

만약 새의 정의에날 수 있다는 행동이 포함되지 않는다면 펭귄은 새의 서브타입이 될 수 있다. 이 경우에는 어휘적인 관점과 행동 관점이 일치하게 된다.

<br>

따라서 타입 계층의 의미는 행동이라는 문맥에 따라 달라질 수 있다.

그에 따라 올바른 타입 계층이라는 의미 역시 문맥에 따라 달라질 수 있다.

어떤 어플리케이션에서 새에게 날 수 있다는 행동을 기대하지 않고 단지 울음 소리를 낼 수 있다는 행동만 기대한다면 새와 펭귄을 타입 계층으로 묶어도 무방하다.

따라서 슈퍼타입과 서브타입 관계에서는 is-a보다 행동 호환성이 더 중요하다.

<br>

이 예는 is-a라는 말을 너무 단편적으로 받아들일 경우에 어떤 혼란이 벌어질 수 있는지를 잘 보여준다.

따라서 어떤 두 대상을 언어적으로 is-a라고 표현할 수 있더라도 일단은 상속을 사용할 예비 후보 정도로만 생각하라.

너무 성급하게 상속을 적용하려고 서두르지 마라.

여러분의 애플리케이션 안에서 두 가지 후보 개념이 어떤 방식으로 사용되고 협력하는지 살펴본 후에 상속의 적용 여부를 결정해도 늦지 않다.

<br>

#### 행동 호환성

펭귄이 새가 아니라는 사실을 받아들이기 위한 출발점은 타입이 행동과 관련이 있다는 사실에 주목하는 것이다.

타입의 이름 사이에 개념적으로 어떤 연관성이 있다고 하더라도 행동에 연관성이 없다면 is-a 관계를 사용하지 말아야 한다.

<br>

결론은 두 타입 사이에 행동이 호환될 경우에만 타입 계층으로 묶어야 한다는 것이다.

그렇다면 행동이 호환된다는 것은 무슨 의미일까? 단순히 동일한 메서드를 구현하고 있으면 행동이 호환되는 것일까?

여기서 중요한 것은 행동의 호환 여부를 판단하는 기준은 **클라이언트의 관점**이라는 것이다.

클라이언트가 두 타입이 동일하게 행동할 것이라고 기대한다면 두 타입을 타입 계층으로 묶을 수 있다.

클라이언트가 두 타입이 동일하게 행동하지 않을 것이라고 기대한다면 두 타입을 타입 계층으로 무어서는 안된다.

<br>

#### 클라이언트의 기대에 따라 계층 분리하기

행동 호환성을 만족시키지 않는 상속 계층을 그대로 유지한 채 클라이언트의 기대를 충족시킬 수 있는 방법을 찾기란 쉽지 않다.

문제를 해결할 수 있는 방법은 클라이언트의 기대에 맞게 상속 계층을 분리하는 것뿐이다.

<br>

클라이언트에 따라 인터페이스를 분리하면 변경에 대한 영향을 더 세밀하게 제어할 수 있게 된다.

대부분의 경우 인터페이스는 클라이언트의 요구가 바뀜에 따라 변경된다.

클라이언트에 따라 인터페이스를 분리하면 각 클라이언트의 요구가 바뀌더라도 영향의 파급 효과를 효과적으로 제어할 수 있게 된다.

이처럼 인터페이스를 클라이언트의 기대에 따라 분리함으로써 변경에 의해 영향을 제어하는 설계 원칙을 **인터페이스 분리 원칙(Interface Segregation Principle, ISP)** 이라고 부른다.

<br>

여기서 한 가지 주의해야 할 점이 있다. 설계가 꼭 현실 세계를 반영할 필요는 없다는 것이다.

중요한 것은 설계가 반영할 도메인의 요구사항이고 그 안에서 클라이언트가 객체에게 요구하는 행동이다.

현실을 정확하게 묘사하는 것이 아니라 요구사항을 실용적으로 수용하는 것을 목표로 삼아야 한다.

<br>

요점은 자연어에 현혹되지 않고 요구사항 속에 클라이언트가 기대하는 행동에 집중하라는 것이다.

클래스의 이름 사이에 어떤 연관성이 있다는 사실은 아무런 의미도 없다.

두 클래스 사이에 행동이 호환되지 않는다면 올바른 타입 계층이 아니기 때문에 상속을 사용해서는 안 된다.

<br>

#### 서브클래싱과 서브타이핑

그래서 언제 상속을 사용해야 하는가?

이번 장을 처음 시작할 때 언급한 것처럼 상속은 코드 재사용과 타입 계층을 구성하기 위해 사용된다.

사람들은 상속을 사용하는 두 가지 목적에 특별한 이름을 붙였는데 **서브클래싱**과 **서브타이핑**이 그것이다.

- **서브클래싱(subclassing)**: 다른 클래스의 코드를 재사용할 목적으로 상속을 사용하는 경우를 가리킨다. 자식 클래스와 부모 클래스의 행동이 호환되지 않기 때문에 자식 클래스의 인스턴스가 부모 클래스의 인스턴스를 대체할 수 없다. 서브클래싱을 **구현 상속** 또는 **클래스 상속**이라고 부르기도 한다.
- **서브타이핑(subtyping)**: 타입 계층을 구성하기 위해 상속을 사용하는 경우를 가리킨다. 서브타이핑에서는 자식 클래스와 부모 클래스의 행동이 호환되기 때문에 자식 클래스의 인스턴스가 부모 클래스의 인스턴스를 대체할 수 있다. 이때 부모 클래스는 자식 클래스의 슈퍼타입이 되고 자식 클래스는 부모 클래스의 서브타입이 된다. 서브타이핑을 **인터페이스 상속**이라고 부르기도 한다.

_아까 이름만 봤을 때는 서로 반대일 줄 알았다.. 타이핑을 타자 치는 걸로 헷갈려서 ㅎㅎ.. 아까 타입에 대해서 계속 이야기했는데 이럴수가 하하_

<br>

서브클래싱과 서브타이핑을 나누는 기준은 상속을 사용하는 목적이다.

타입을 설명할 때 강조했던 것처럼 슈퍼타입과 서브타입 사이의 관계에서 가장 중요한 것은 퍼블릭 인터페이스다.

슈퍼타입 인스턴스를 요구하는 모든 곳에서 서브타입의 인스턴스를 대신 사용하기 위해 만족해야 하는 최소한의 조건은 서브타입의 퍼블릭 인터페이스가 슈퍼 타입에서 정의한 퍼블릭 인터페이스와 동일하거나 더 많은 오퍼레이션을 포함해야 한다는 것이다.

따라서 개념적으로 서브타입이 슈퍼타입의 퍼블릭 인터페이스를 상속받는 것처럼 보이게 된다.

이것이 서브타이핑을 인터페이스 상속이라고 부르는 이유다.

그에 반해 서브클래싱은 클래스의 내부 구현 자체를 상속받는 것에 초점을 맞추기 때문에 구현 상속 또는 클래스 상속이라고 부른다.

<br>

서브타이핑 관계가 유지되기 위해서는 서브타입이 슈퍼타입이 하는 모든 행동을 동일하게 할 수 있어야 한다.

즉, 어떤 타입이 다른 타입의 서브타입이 되기 위해서는 **행동 호환성(behavioral substitution)** 을 만족시켜야 한다.

자식 클래스와 부모 클래스 사이의 행동 호환성은 부모 클래스에 대한 자식 클래스의 **대체 가능성(substitutability)**을 포함한다.

<br>

행동 호환성과 대체 가능성은 올바른 상속 관계를 구축하기 위해 따라야 할 지침이라고 할 수 있다.

오랜 시간 동안 이 지침은 리스코프 치환 원칙이라는 이름으로 정리되어 소개돼 왔다. 이제 리스코프 치환 원칙을 통해 지금까지 살펴본 is-a 관계와 행동 호환성의 의미를 다시 한번 정리해 보자.

<br>

### 04. 리스코프 치환 원칙

1988년 바바라 리스코프는 올바른 상속 관계의 특징을 정의하기 위해 **리스코프 치환 원칙(Liskov Substitution Principle, LSP)** 을 발표했다.

_리스코프가 뭔 뜻인가 했는데 사람 이름이었구나.._

바바라 리스코프에 의하면 상속 관계로 연결한 두 클래스가 서브타이핑 관계를 만족시키기 위해서는 다음의 조건을 만족시켜야 한다.

> S형의 각 객체 o1에 대해 T형의 객체 o2가 하나 있고, T에 의해 정의된 모든 프로그램 P에서 T가 S로 치환될 때, P의 동작이 변하지 않으면 S는 T의 서브타입이다.

리스코프 치환 원칙을 한 마디로 정리하면 "서브타입은 그것의 기반 타입에 대해 대체 가능해야 한다"는 것으로 "클라이언트가 차이점을 인식하지 못한 채 기반 클래스의 인터페이스를 통해 서브클래스를 사용할 수 있어야 한다"는 것이다.

리스코프 치환 원칙은 앞에서 논의한 행동 호환성을 설계 원칙으로 정리한 것이다.

리스코프 치환 원칙에 따르면 자식 클래스가 부모 클래스와 행동 호환성을 유지함으로써 부모 클래스를 대체할 수 있도록 구현된 상속 관계만을 서브타이핑이라고 불러야 한다.

<br>

(예제: "정사각형은 직사각형이다", 하지만 resize 메서드에서 불가능해짐)

두 클래스는 리스코프의 치환 원칙을 위반하기 때문에 서브타이핑 관계가 아니라 서브클래싱 관계다.

`Rectangle`은 is-a라는 말이 얼마나 우리의 직관에서 벗어날 수 있는지를 잘 보여준다.

중요한 것은 클라이언트 관점에서 행동이 호환되는지 여부다.

그리고 행동이 호환될 경우에만 자식 클래스가 부모 클래스 대신 사용될 수 있다.

<br>

#### 클라이언트와 대체 가능성

(정사각형을 추상화한 `Square`는 직사각형을 추상화한 `Rectangle`과 동일하지 않음. `Rectangle`을 사용하는 클라이언트는 `Rectangle`의 너비와 높이가 다를 수 있다는 가정하에 코드를 개발한다. 반면 `Square`는 너비와 높이가 항상 같다. 따라서 `Rectangle`을 `Square`로 대체할 경우 `Rectangle`에 대해 세워진 가정을 위반할 확률이 높다.)

<br>

리스코프 치환 원칙은 "클라이언트와 격리한 채로 본 모델은 의미 있게 검증하는 것이 불가능하다"는 아주 중요한 결론을 이끈다.

어떤 모델의 유효성은 클라이언트의 관점에서만 검증 가능하다는 것이다.

리스코프 치환 원칙은 상속 관계에 있는 두 클래스 사이의 관계를 클라이언트와 떨어트려 놓고 판단하지 말라고 속삭인다.

상속 관계는 클라이언트 관점에서 자식 클래스가 부모 클래스를 대체할 수 있을 때만 올바르다.

행동 호환성과 리스코프 치환 원칙에서 한 가지만 기억해야 한다면 이것을 기억하라.

대체 가능성을 결정하는 것은 클라이언트다.

<br>

#### is-a 관계 다시 살펴보기

is-a 관계로 표현된 문장을 볼 때마다 문장 앞에 "클라이언트 입장에서"라는 말이 빠져 있다고 생각하라.

클라이언트를 배제한 is-a 관계는 여러분을 혼란으로 몰아갈 가능성이 높다.

<br>

is-a 관계는 객체지향에서 중요한 것은 객체의 속성이 아니라 객체의 행동이라는 점을 강조한다.

일반적으로 클라이언트를 고려하지 않은 채 개념과 속성의 측면에서 상속 관계를 정할 경우 리스코프 치환 원칙을 위반하는 서브클래싱에 이르게 될 확률이 높다.

<br>

결론적으로 상속이 서브타이핑을 위해 사용될 경우에만 is-a 관계다.

서브클래싱을 구현하기 위해 상속을 사용했다면 is-a 관계라고 말할 수 없다.

<br>

#### 리스코프 치환 원칙은 유연한 설계의 기반이다

지금까지 살펴본 것처럼 리스코프 치환 원칙은 클라이언트가 어떤 자식 클래스와도 안정적으로 협력할 수 있는 상속 구조를 구현할 수 있는 가이드라인을 제공한다.

새로운 자식 클래스를 추가하더라도 클라이언트의 입장에서 퍼블릭 인터페이스의 행동 방식이 변경되지 않는다면 클라이언트의 코드를 변경하지 않고도 새로운 자식 클래스와 협력할 수 있게 된다는 것이다.

<br>

리스코프 치환 원칙을 따르는 설계는 유연할뿐만 아니라 확장성이 높다.

자식 클래스가 클라이언트의 관점에서 부모 클래스를 대체할 수 있다면 기능 확장을 위해 자식 클래스를 추가하더라도 코드를 수정할 필요가 없어진다.

따라서 리스코프 치환 원칙은 개방-폐쇄 원칙을 만족하는 설계를 위한 전제 조건이다.

일반적으로 리스코프 치환 원칙 위반은 잠재적인 개방-폐쇄 원칙 위반이다.

<br>

#### 타입 계층과 리스코프 치환 원칙

한 가지 잊지 말아야 하는 사실은 클래스 상속은 타입 계층을 구현할 수 있는 다양한 방법 중 하나일 뿐이라는 것이다.

자바와 C#의 인터페이스나 스칼라의 트레이트, 동적 타입 언어의 덕 타이핑 기법 등의 기법을 사용하면 클래스 사이의 상속을 사용하지 않고 서브타이핑 관계를 구현할 수 있다.

물론 이런 기법을 사용하는 경우에도 리스코프 치환 원칙을 준수해야만 서브타이핑 관계라고 말할 수 있다.

구현 방법은 중요하지 않다. 핵심은 구현 방법과 무관하게 클라이언트의 관점에서 슈퍼타입에 대해 기대하는 모든 것이 서브타입에게도 적용돼야 한다는 것이다.

<br>

리스코프 치환 원칙을 위반하는 예를 설명하는 데 클래스 상속을 자주 사용하는 이유는 대부분의 객체지행 언어가 구현 단위로서 클래스를 사용하고 코드 재사용의 목적으로 상속을 지나치게 남용하는 경우가 많기 때문이다.

상속이 아닌 다른 방법을 이용하더라도 클라이언트의 관점에서 서로 다른 구성 요소를 동일하게 다뤄야 한다면 서브타이핑 관계의 제약을 고려해서 리스코프 치환 원칙을 준수해야 한ㄴ다.

<br>

마지막 질문만이 남았다.

클라이언트 관점에서 자식 클래스가 부모 클래스를 대체할 수 있다는 것은 무엇을 의미하는가? 클라이언트 관점에서 자식 클래스가 부모 클래스의 행동을 보존한다는 것은 무엇을 의미하는가?

<br>

### 05. 계약에 의한 설계와 서브타이핑

클라이언트와 서버 사이의 협력을 의무와 이익으로 구성된 계약의 관점에서 표현하는 것을 **계약에 의한 설계(Design By Contract, DBC)**라고 부른다.

계약에 의한 설계는 클라이언트가 정상적으로 메서드를 실행하기 위해 만족시켜야 하는 **사전조건**과 메서드가 실행된 후에 서버가 클라이언트에게 보장해야 하는 **사후조건**, 메서드 실행 전과 실행 후에 인스턴스가 만족시켜야 하는 **클래스 불변식**의 세 가지 요소로 구성된다.

<br>

리스코프 치환 원칙은 어떤 타입이 서브타입이 되기 위해서는 슈퍼타입의 인스턴스와 협력하는 '클라이언트'의 관점에서 서브타입의 인스턴스가 슈퍼타입을 대체하더라도 협력에 지장이 없어야 한다는 것을 의미한다.

따라서 계약에 의한 설계를 사용하면 리스코프 치환 원칙이 강제하는 조건을 계약의 개념을 이용해 좀 더 명확하게 설명할 수 있다.

<br>

리스코프 치환 원칙과 계약에 의한 설계 사이의 관계를 다음과 같은 한 문장으로 요약할 수 있다.

> 서브타입이 리스코프 치환 원칙을 만족시키기 위해서는 클라이언트와 슈퍼타입 간에 체결된 '계약'을 준수해야 한다.

<br>

계약에 의한 설계에 따르면 협력하는 클라이언트와 슈퍼타입의 인스턴스 사이에는 어떤 계약이 맺어져 있다.

클라이언트와 슈퍼타입은 이 계약을 준수할 때만 정상적으로 협력할 수 있다.

클라이언트의 입장에서 서브타입은 정말 슈퍼타입의 '한 종류'여야 한다.

<br>

이제 여러분은 서브클래스와 서브타입은 서로 다른 개념이라는 사실을 잘 알고 있을 것이다.

어떤 클래스가 다른 클래스를 상속받으면 그 클래스의 자식 클래스 또는 서브클래스가 되지만 모든 서브클래스가 서브타입인 것은 아니다.

코드 재사용을 위해 상속을 사용했다면, 그리고 클라이언트 관점에서 자식 클래스가 부모 클래스를 대체할 수 없다면 서브타입이라고 할 수 없다.

<br>

서브타입이 슈퍼타입처럼 보일 수 있는 유일한 방법은 클라이언트가 슈퍼타입과 맞은 계약을 서브타입이 준수하는 것 뿐이다.

<br>

#### 서브타입과 계약

계약의 관점에서 상속이 초래하는 가장 큰 문제는 자식 클래스가 부모 클래스의 메서드를 오버라이딩할 수 있다는 것이다.

자식 클래스가 부모 클래스의 서브타입이 되기 위해서는 다음 조건을 만족시켜야 한다.

- 사전조건
   - 서브타입에 더 강력한 사전조건을 정의할 수 없다.
   - 서브타입에 슈퍼타입과 같거나 더 약한 사전조건을 정의할 수 있다.
- 사후조건
   - 서브타입에 더 약한 사후조건을 정의할 수 없다.
   - 서브타입에 슈퍼타입과 같거나 더 강한 사전조건을 정의할 수 있다.

<br>

지금까지 살펴본 것처럼 리스코프 치환 원칙을 설명하기 위해 계약에 의한 설계 개념을 이용할 수 있다.

계약에 의한 설계는 클라이언트 관점에서의 대체 가능성을 계약으로 설명할 수 있다는 사실을 잘 보여준다.

따라서 서브타이핑을 위해 상속을 사용하고 있다면 부모 클래스가 클라이언트와 맺고 있는 계약에 관해 깊이 있게 고민하기 바란다.

<br>

### 생각

이전 책을 포함하여 과하게 반복적으로 설명하는 부분이 있다는 생각을 했었는데, 역시 이 방식이 이해가 가장 잘 되는 것 같다.
상속에 대해서는 앞에서도 계속 언급됐었는데 이번 장으로 상속을 좀 더 정확하게 바라볼 수 있을 것 같다.

상속은 계속 관심있던 부분이라 정말 재밌게 잘 읽었다.
(하지만 이해한답시고 타이핑을 너무 많이 함...)

### 논의사항

- 여러분은 is-a 관계를 어떻게 생각하고 있었나요?

저는 사실 책에 언급되는 것처럼 '단편적'으로 생각하고 있었는데 펭귄과 새, 정사각형과 직사각형에 대한 예제를 읽으면서 그동안 잘 모르고 있었다는 생각이 들었습니다.
읽고 나서 시야가 넓어진 기분이 들어 즐거웠습니다.