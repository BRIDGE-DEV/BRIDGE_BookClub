
## 01 개방-폐쇄 원칙

**개방-폐쇄 원칙(Open-Closed Principle, OCP)** : 소프트웨어 개체(클래스, 모듈, 함수 등등)는 확장에 대해 열려 있어야 하고, 수정에 대해서는 닫혀 있어야 한다.

- 확장에 대해 열려 있다: 애플리케이션의 요구사항이 변경될 때 이 변경에 맞게 새로운 '동작'을 추가해서 애플리케이션의 기능을 확장할 수 있다.
- 수정에 대해 닫혀 있다: 기존의 '코드'를 수정하지 않고도 애플리케이션의 동작을 추가하거나 변경할 수 있다.

#### 컴파일타임 의존성을 고정시키고 런타임 의존성을 변경하라

개방-폐쇄 원칙은 런타임 의존성과 컴파일타임 의존성에 관한 이야기다. 
 

#### 추상화가 핵심이다

개방-폐쇄 원칙의 핵심은 *추상화에 의존하는 것*이다. 

개방-폐쇄 원칙의 관점에서 생략되지 않고 남겨지는 부분은 다양한 상황에서의 공통점을 반영한 추상화의 결과물이다. 공통적인 부분은 문맥이 바뀌더라도 변하지 않아야 한다. 따라서 추상화 부분은 수정에 닫혀있다. 하지만 추상화를 통해 생략된 부분들은 확장의 여지를 남긴다. -> 추상화가 개방-폐쇄원칙이 가능한 이유

```java
public abstract class DiscountPolicy {

    private List<DiscountCondition> conditions = new ArrayList<>();
    
    public DiscountPolicy(DiscountCondition ... conditions) {
        this.conditions = Arrays.asList(conditions);
    }
    public Money calculateDiscountAmount(Screening screening) {
        for(DiscountCondition each : conditions) {
            if (each.isSatisfiedBy(screening)) {
                return getDiscountAmount(screening);
            }
        }
        
        return screening.getMovieFee();

    }

    abstract protected Money getDiscountAmount(Screening Screening);

}
```

`DiscountPolicy`는 할인 여부를 판단해서 요금을 계산하는 `calculateDiscountAmount` 메서드와 조건이 만족할 때 요금을 계산하는 `getDiscountAmount` 로 구성돼있다.

여기서 변하지 않는 부분은`calculateDiscountAmount`이고 `getDiscountAmount`는 확장 가능하다. 따라서 `DiscountPolicy`는 추상화다.

단순히 추상화를 했다고 개방-폐쇄 원칙이 되는 것은 아니다. 폐쇄를 가능케 하는 것은 의존성의 방향이다. 수정에 대한 영향을 최소화하기 위해서는 모든 요소가 추상화에 의존해야 한다.

중점은 추상화다 변하는 것과 변하지 않는 것을 신중하게 선택하고 이를 추상화의 목적으로 삼아야 한다.

## 02 생성 사용 분리

메시지를 전송하지 않고 객체를 생성하기만 하거나 객체를 생성하지 않고 메시지를 전송하기만 한다면 결합도를 낮출 수 있다.

유연하고 재사용 가능한 설계를 원한다면 객체를 생성하는 것과 객체를 사용하는 것의 책임을 분리시켜야 한다.

가장 보편적으로는 객체를 생성할 책임은 클라이언트가 가져간다.

#### FACTORY 추가하기

생성 책임을 클라이언트가 생성의 책임을 가진다고 해도 사용의 책임을 피할 수는 없다. 이를 해결하기 위해선 객체 생성과 관련된 책임만 전담하는 별도의 객체를 추가해 클라이언트가 이 객체를 사용하도록 만드는 것이다.

*생성과 사용을 분리하기 위해 객체 생성에 특화된 객체를 FACTORY라고 한다.

#### 순수한 가공물에게 책임 할당하기

**표현적 분해( representational decomposition)**: 도메인에 존재하는 사물이나 개념을 표현하는 객체를 이용해 분해하는 것 -> 도메인과 소프트웨어 사이의 표현적 차이를 최소화하는 것
**행위적 분해( bahavioral decomposition)**:


**순수한 가공물(PURE FABRICATION) :**  도메인 개념을 표현한 객체가 아닌 설계자가 편의를 위해 임의로 만들어낸 가공의 객체 즉 도메인과 무관하게 책임할당을 위해 창조된 객체

객체지향 애플리케이션은 도메인 개념뿐 아니라 설계자들이 임의적으로 창조한 인공적 추상화들도 포함하며 오히려 인공물이 더 많은 것이 일반적이다.

설계자로서의 우리의 역할은 도메인 추상화를 기반으로 로직을 설계하는 동시에 품질의 측면에서 균형을 맞추는 데 필요한 객체들을 창조해 내는 것이다. 도메인 개념을 갖는 객체와 순수하게 창조된 인공 객체들이 모여 협력하는 애플리케이션을 설계하는 것이 목표이다.

## 03 의존성 주입

**의존성 주입(Dependency Injection)**: 사용하는 객체가 아닌 외부의 독립적인 객체가 인스턴스를 생성한 후 이를 전달해서 의존성을 해결하는 방법

8장의 의존성 해결방법과 관련이 깊다.

- 생성자 주입(constructor injection) : 객체를 생성하는 시접에 생성자를 통한 의존성 해결
- setter 주입(setter injection): 객체 생성 후 setter 메서드를 통한 의존성 해결
- 메서드 주입(method injection) : 메서드 실행 시 인자를 이용한 의존성 해결

-> 명시적인 의존성이 중요한 이유와 동일해 보인다.

#### 숨겨진 의존성은 나쁘다.

**SERVICE LOCATOR** : 의존성을 해결할 객체들을 보관하는 일종의 저장소


```java
public class Movie{

private DiscountPolicy discountPolicy;

public Movie(String title, Duration runningTime,Money fee){
this.title=title;
this.runningTime=runningTime;
this.fee=fee;
this.discountPolicy=ServiceLocator.discountPolicy();
	}
}
```

`ServiceLocator`는 `DiscountPolicy`의 인스턴스를 등록하기 위한 provide 메서드와 인스턴스를 반환하는 discountPolicy 메서드를 구현한다.

```java
public class ServiceLocator {

    private static ServiceLocator soleInstance = new ServiceLocator();

    private DiscountPolicy discountPolicy;

  

    public static DiscountPolicy discountPolicy() {

        return soleInstance.discountPolicy;

    }

  

    public static void provide(DiscountPolicy discountPolicy) {

        soleInstance.discountPolicy = discountPolicy;

    }

  

    private ServiceLocator() {

    }

}
```

Movie가 어떤 할인 정책의 인스턴스를 사용할지에 따라 ServiceLocator.provide()메서드를 사용하면 된다.

*단점*

SERVICE LOCATOR 패턴은 의존성을 감춘다는 것이 가장 큰 특징이다.
의존성을 감춘다는 것은 객체가 생성될 때 불완전한 상태로 생성되며 이를 예측하기가 어렵다는 뜻이다.

의존성을 구현 내부로 숨기면 의존성 문제는 컴파일 타임이 아닌 런타임에 발견된다.
숨겨진 의존성을 이해하기 위해 내부 구현을 이해할 것을 강조하며 이는 결국 캡슐화를 위반하는 것으로 이어진다. 즉 SERVICE LOCATOR는 캡슐화를 위반할 수 밖에 없다.

어쩔 수 없이 SERVICE LOCATO패턴을 사용해야 하는 경우는 의존성 주입을 지원하는 프레임워크를 사용하지 못하는 경우나 깊은 호출 계층에 걸쳐 동일한 객체를 계속해서 전달해야 하는 고통이 있는 경우가 될 수 있다.

## 04 의존성 역전 원칙

#### 추상화와 의존성 역전

객체 사이의 협력에서 협력의 본질을 담고 있는 것은 상위 수준의 정책이다. 상위 수준의 정책이 협력에서 중요한 의사결정과 비즈니스 본질을 담고 있다는 것이다. 그러나 상위 수준의 클래스가 하위 수준의 클래스에 의존한다면 하위 수준의 변경에 의해 상위 수준 클래스가 영향을 받게 된다.
의존성은 변경의 전파와 관련되어 변경의 영향을 최소화하도록 의존성을 관리해야 한다.

재사용성에도 영향을 끼친다. 상위 수준의 클래스가 하위 수준의 클래스에 의존하면 상위 수준의 클래스를 재사용하려 할 때 하위 수준의 클래스도 필요하기 때문에 재사용하기 어려웢니다. 

해결방법은 역시 *추상화*이다. 하위 수준도 상위 수준도 모두 추상화에 의존한다면 재사용이 가능하며 변경의 영향을 상위 수준의 클래스가 받는 것을 방지할 수 있다.

정리하면
1. 상위 수준의 모듈은 하위 수준의 모듈에 의존해서는 안 된다. 모두 추상화에 의존해야 한다.
2. 추상화는 구체적인 사항에 의존해서는 안 된다. 구체적인 사항은 추상화에 의존해야 한다.

이를 **의존성 역전 원칙(Dependency Inversion Principle, DIP)** 라고 부른다.

#### 의존성 역전 원칙과 패키지

유연하고 재사용 가능하며 컨텍스트에 독립적인 설계는 전통적인 패러다임이 고수하는 의존성을 역전시킨다. 객체지향 패러다임에서는 상위 수준의 모듈과 하위 수준의 듈이 모두 추상화에 의존한다. 또한 인터페이스가 상위 수준의 모듈에 속한다.

## 05 유연성에 대한 조언

#### 유연한 설계는 유연성이 필요할 때만 옳다.

유연하고 재사용 가능한 설계는 코드의 단순함과 명확함을 잃게 만든다. 즉 코드가 복잡해진다. 객체지향의 설계는 코드에 표현된 정적인 구조와 실행시의 동적인 구조가 다르다. 설계가 유연할수록 클래스 구조와 객체 구조 사이의 거리가 멀어진다.

불필요한 유연성은 불필요한 복잡성을 낳는다. 명확한 해법이 만족스럽다면 유연성을 제거하는 것이 낫다. 유연성은 코드를 읽는 사람이 복잡함을 수용할 수 있을 때 가치가 생긴다.

#### 협력과 책임이 중요하다.

객체를 생성할 책임을 담당할 객체나 객체 생성 메커니즘을 결정하는 시점은 책임 할당의 마지막 단계로 미뤄야 한다. 중요한 비즈니스 로직을 처리하기 위해 책임을 할당하고 협력의 균형을 맞추면 생성과 관련된 책임을 지게 될 객체를 선택하는 것은 간단하다.

책임의 불균형이 심화될 때 객체 생성의 책임을 지는 것은 설계를 하부의 특정한 메커니즘에 종속적으로 만들 확률이 높다.

*의존성을 관리해야 하는 이유는 역할, 책임, 협력의 관점에서 설계가 유연하고 재사용 가능해야 하기 때문이다.* 


## 느낀 점

개방-폐쇄 원칙이 사실 SOLID 중에서 제일 난해하게 느껴졌는데 결국 답은 추상화였다는 걸 깨닫게 됐습니다. "변하는 것과 변하지 않는 것을 신중하게 택하고 추상화를 한다","객체 생성과 사용의 분리가 결합도를 낮춘다","의존성의 방향과 명시가 유연한 설계를 만든다" 이렇게 세 문장으로 본 챕터를 요약할 수 있을 것 같습니다.

## 논의사항

>유연한 설계는 유연성이 필요할 때만 옳다

유연성이 필요하지 않겠다! 라고 확신할 수 있는 로직들이 어떤 것들이 있을까요?

확실히 뭐든지 유연하게 만들려고 하다보면 코드가 굉장히 복잡해지는 것을 얼마전에 느꼈습니다. 아직까지는 최소 단위의 로직들이 아니라면 어떤 것이 유연성이 필요할 지 필요 없을지 확신할 수 가 없는 것 같습니다.



