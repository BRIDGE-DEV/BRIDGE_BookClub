
객체간 협력을 위해서는 의존성이 필요하지만 과도한 의존성은 수정을 어렵게 만든다.
객체지향 설계의 핵심은 협력을 위해 필요한 의존성을 유지하고 변경을 방해하는 의존성은 제거하는 데 있다.

## 01 의존성 이해하기

#### 변경과 의존성

의존성은 실행 시점과 구현 시점에 서로 다른 의미를 가진다.
- **실행시점** : 의존하는 객체가 정상적으로 동작하기 위해 실행 시에 의존 대상 객체가 반드시 존재해야 한다.
- **구현 시점** : 의존 대상 객체가 변경될 경우 의존하는 객체도 함께 변경된다.

``` java
public class PeriodCondition implements DiscountCondition{
private DayOfWeek dayOfWeek;
private LocalTime startTime;
private LocalTime endTime;

public boolean isSatisfiedBy (Screen screening){
return screening.getStartTime().getDayOfWeek().equals(dayOfWeek)&&
	startTime.compareTo(screening.getStartTime().toLocalTime())<=0&&
	endTime.compareTo(screening.getStartTime().toLocalTime())>=0;

	}
}
```

실행시점에 PeriodCondition은 Screen 객체가 필요하다. 만약 실행시점에 Screen객체가 없거나 getStartTime 메시지를 이해하지 못한다면 제대로 동작하지 않을 것이다.

이렇게 객체가 작업을 수행하기 위해 다른 객체를 필요로 하는 것이 의존성이다.
의존성은 방향성을 가지며 항상 단방향이다. PeriodCondition은 Screening으로 방향성을 가진다.

*의존성은 의존되는 요소가 변경될 때 의존하는 요소도 함께 변경될 수 있음을 의미한다.*

DayOfWeek과 LocalTime, PeriodCondition에 의존성을 가지는 PeriodCondition은 해당 클래스들이 변경되면 PeriodCondition도 함께 변경돼야 한다.

#### 의존성 전이

의존성은 전이될 수 있다.

- **직접 의존성(direct dependency)** : 한 요소가 다른 요소에 직접 의존하는 경우 PeriodCondition가 Screening에 의존하는 경우
- **간접 의존성(indirect dependency)** : 직접적인 관계는 존재하지 않지만 의존성 전이에 의해 영향이 전파되는 경우

#### 런타임 의존성과 컴파일타임 의존성

**런타임 의존성(run-time dependency)** : 애플리케이션이 실행되는 타이밍에 정해지는 의존성
**컴파일 타임 의존성(compile-time dependency)** : 컴파일 타임은 동적언어의 경우 존재하지 않거나 존재하더라도 사실상 코드 그 자체의 구조를 가리킴. 즉 코드상에서 정해진 의존성

유연하고 재사용 가능한 코드를 설계하기 위해선 둘의 의존성을 다르게 해야 한다.

```java
public class Movie{

private DiscountPolicy discountPolicy;

public Movie(String title, Duration runningTime,Money fee, DiscountPolicy discountPolicy){ 
...
this.discountPolicy=discountPolicy;
}
public Money calculateMovieFee(Screening screening){
return fee.minus(discountPolicy.calculateDiscountAmount(screening));

	}
}

```

`movie` 클래스는 `AmountDiscountPolicy`나 `PercentDiscountPolicy`에 어떠한 의존성도 존재하지 않는다. 코드 작성 시점에서는 `movie`는 `AmountDiscountPolicy` 나`PercentDiscountPolicy`의 존재에 대해 알지 못하지만 `DiscountPolicy`를 통해 협력을 하고 있다.

추상적으로 두 할인정책을 모두 포괄하는 `DiscountPolicy`라는 추상 클래스에 의존하다가 코드 실행시 `AmountDiscountPolicy`나 `PercentDiscountPolicy`에 런타임 의존으로 대체한다.

어떤 클래스가 다양한 클래스의 인스턴스와 협력하기 위해서는 협력할 인스턴스의 구체적인 클래스를 알아서는 안 된다. 실제 협력할 객체가 어떤 것인지는 런타임에 결정해야 한다.

#### 컨텍스트 독립성

**컨텍스트 독립성** : 클래스가 특정 문맥에 최소한의 가정만으로 이뤄져 다른 문맥에서 재사용되기 수월한 성질

`movie` 클래스가  추상 클래스인 `DiscountPolicy`에 의존해 구체적인 문맥은 런타임에 결정하게 한 것이 그 예다.

#### 의존성 해결하기

컴파일타임 의존성을 실행 컨텍스트에 맞게 적절한 런타임 의존성으로 교체하는 것을 **의존성 해결**이라고 한다.

- 객체를 생성하는 시점에 생성자를 통해 의존성 해결
- 객체 생성 후 setter 메서드를 통해 의존성 해결
- 메서드 실행 시 인자를 이용해 의존성 해결

생성자를 통해 인자를 전달받아 의존성을 해결하는 방법이 존재하며
인스턴스를 생성한 후 인스턴스 안의 setter 메서드의 인자를 전달시키는 방식이 있다.
setter메서드를 통한 의존성 해결은 중간에 의존대상을 변경할 수 있는 장점이 있지만 setter 메서드를 호출하기 전까진 인스턴스가 불완전한 상태라는 단점이 있다.(의존 대상이 초기화되지 않은 상태에서 접근하려 하면 nullreference가 될 것이다.)

두 방식을 혼합해 사용하는 방법이 시스템의 상태를 안정적으로 유지하면서 유연성을 향상시키는 방법이다. <- 가장 선호됨.

객체가 항상 의존대상에 대해 알 필요가 없다면 메서드를 실행시킬 때, 의존성을 만들어(메서드의 인자를 통해)해결할 수 있다. 항상 지속적으로 의존 관계를 맺을 필요가 없거나 메서드를 실행시킬때 마다 의존대상이 달라질 경우에 유용하다.

## 02 유연한 설계

#### 의존성과 결합도

모든 의존성은 나쁜 것이 아니다. 문제는 의존성의 정도다.
의존성이 과하면 문제가 되며 바람직한 의존성으로 만들기 위해서는 *재사용성*을 고려해야 한다.

다양한 환경에서 클래스를 재사용할 수없도록 제한한다면 그 의존성은 바람직하지 못하다. 즉 컨텍스트 독립적인 의존성은 바람직한 의존성이다.

의존성은 바람직할 때는 **느슨한 결합도(loose coupling)** , 바람직하지 못할 때는 **단단한 결합도(tight coupling)** 이라고 부른다. 

#### 지식이 결합을 낳는다.

한 요소가 다른 요소에 대해 더 적은 정보를 알 수록 두 요소는 약하게 결합된다.
*지식의 양이 결합도를 결정한다.*
결합도를 느슨하게 만들기 위해서는 협력 대상에 대해 필요한 정보만을 남기고 최대한 감추는 것이 중요하다.

#### 추상화에 의존한다.

추상화란 어떤 양상, 세부사항, 구조를 좀 더 명확하게 이해하기 위해 특정 절차나 물체를 의도적으로 생략하거나 감춰 복잡도를 극복하는 방법이다.

`DiscountPolicy` 클래스는 `PercentDiscountPolicy` 클래스보다 `movie`클래스의 입장에서는 알아야 할 정보가 더 적다. `movie`와 `DiscountPolicy`사이에 결합도가 느슨한 이유는 `movie`클래스가 추상화에 의존했기 때문이다.

추상화와 결합도의 관점에서 의존 대상을 다음과 같이 구분하면 유용하다.
아래로 갈수록 결합도는 느슨해진다.

- 구체 클래스 의존성(concrete class dependency)
- 추상 클래스 의존성(abstract class dependency)
- 인터페이스 의존성(interface dependency)
#### 명시적인 의존성

**명시적 의존성(explicit dependency)** : 퍼블릭 인터페이스, setter 메서드, 메서드의 인자 등으로 의존하는 대상을 명시적으로 퍼블릭 인터페이스에 노출시키는 것

**숨겨진 의존성(hidden dependency)** : 객체 내부에서 인스턴스를 직접 생성해 의존하는 것

의존성은 명시적으로 표현돼야 한다. 의존성이 내부 구현에 숨겨져 있다면 다른 컨텍스트에서 재사용되기 위해 내부 구현이 변경되어야 한다. 유연하고 재사용 가능한 설계는 퍼블릭 인터페이스에 의존성이 명시적으로 드러나는 설계이다. *명시적인 의존성이 컴파일타임 의존성을 런타임 의존성으로 교체할 수 있다.*

부끄러운 일은 객체가 다른 객체에 의존하는 것이 아니라  의존성을 감추는 것이다.

#### new는 해롭다.

new 연산자는 잘못된 방법으로 사용된다면 결합도를 크게 높이게 된다.
결합도 측면에서 new연산자가 해로운 이유는 두 가지다.

- new 연산자를 사용하기 위해서는 구체 클래스의 이름을 직접 기술해야 한다. 따라서 new를 사용하는 클라이언트는 추상화가 아닌 구체 클래스에 의존할 수 밖에 없기 때문에 결합도가 높아진다.
- new 연산자는 생성하려는 구체 클래스 뿐 아니라 어떤 인자를 이용해 클래스의 생성자를 호출해야 하는지도 알아야 한다. 따라서 new를 사용하면 클라이언트가 알아야 하는 지식의 양이 늘어나기 때문에 결합도가 높아진다.

구체 클래스에 직접 의존하면 결합도가 높아진다. 구체 클래스가 협력자에게 많은 지식을 알아야 할 것을 강요하기 때문이다. *여기서 new는 구체 클래스를 생성하는데 필요한 정보를 요구하기 때문에 문제를 더 크게 만든다.*

사용과 생성의 책임을 분리해서 결합도를 낮출 수 있다. 생성의 책임을 클라이언트가 가져가 서버에게 인자로 전달하면 서버는 많은 정보를 알 필요 없이 필요한 정보만을 가지고 의존성을 가질 수 있다.

#### 가끔은 생성해도 무방하다.

클래스안에서 객체의 인스턴스를 직접 생성하는 것이 유용할 수 있다. 주로 협력하는 기본 객체를 설정하는 경우다. 

``` java
public class Movie{
	private DiscountPolicy discountPolicy;

	public Movie(String title,Duration runningTime,Money fee){
		this(title,runningTime,fee,new AmountDiscountPolicy(...));
	}

	public Movie(String title, Duration runningTime,Money,fee,DiscountPolicy discountPolicy){
		...
		this.discountPolicy=discountPolicy;

	}
}
```

`Movie`의 생성자 안에서 `AmountDiscountPolicy` 클래스의 인스턴스를 생성한다. 눈 여겨볼 점은 *첫 번째 생성자 안에서 두 번째 생성자를 호출하는 생성자 체이닝이다.*

이 방법으로 `AmountDisountPolicy`의 인스턴스와 협력하게 하면서 컨텍스트에 적절한 `DiscountPolicy`의 인스턴스로 의존성을 교체할 수 있다.  같은 방법으로 메서드 오버라이딩에서도 사용할 수 있다.

#### 조합 가능한 행동

유연한고 재사용 가능한 설계는 어떻게(how) 하는지를 나열하지 않고 객체들의 조합으로 무엇(what)을 하는지를 표현하는 클래스들로 구성된다. 

```java
new Movie("아바타",
		 Duration.ofMinutes(120),
		 Money.wons(10000),
		 new AmountDiscountPolicy(Money.wons(800)),
			 new SequenceCondition(1),
			 new SequenceCondition(10),
			 new PeriodCondition(DayOfWeek.MONDAY,LocalTime.of(10,0),LocalTime.of(12,0)),
			 PeriodCondition(DayOfWeek.THURSDAY,LocalTime.of(10,0),LocalTime.of(21,0)),
		 )

```

위의 코드를 보면 코드를 읽는 것만으로도 상영 순서와 시간 할인 등을 하는 것을 이해할 수 있다. 


## 느낀 점

명시적인 의존성의 장점이 제일 크게 와닿았습니다. 원래 저는 다른 객체의 정보가 필요하다 싶으면 구현 내부에서 몰래 쓰는 경향이 있었습니다.
물론 퍼블릭 인터페이스로 받거나 setter를 통해 받기도 했지만 이것이 '명시적인 의존성이 바람직해서'라는 근거가 뒷받침 되지는 않았습니다.

마지막 '조합 가능한 행동'에서 생성되는 객체의 인자들을 보니 깔끔하고 우아하다라는 생각이 절로 들었네요

## 논의 사항

> new 연산자는 잘못된 방법으로 사용된다면 결합도를 크게 높이게 된다.

저는 객체를 생성할 때 필요한 정보를 가장 많이 알고 있다면 new 연산자를 쓰는 것 같습니다. 여러분들은 new 연산자를 사용할 때의 조건으론 어떤 것을 생각하시나요?

