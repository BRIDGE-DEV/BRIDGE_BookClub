## 2장 객체지향 프로그래밍

기술적인 글을 슬 때 어려운 부분은 적당한 수준의 난이도와 복잡도를 유지하면서 이해하기 쉬운 예제를 선택하는 것이다. 예제가 너무 복잡하면 주제를 효과적으로 전달하기 어렵고, 너무 간단하면 현실성이 떨어지기에 그 균형을 맞추기가 어렵다.

이 책 역시 일반적인 기술 서적이 가지는 한계를 벗어나지 못한다는 점을 미리 밝혀 두고자 한다. 이번 장에서 다루는 내용 역시 복잡하지는 않지만 매우 크고 복잡한 시스템이라고 최면을 걸어주길 바란다.

### 영화 예매 시스템

#### 요구사항 살펴보기

- 영화 예매 시스템 요구사항 분석
  - '영화' 영화에 대한 기본 정보를 표현한다.
    - 기본적인 제목, 상영시간, 가격 정보와 같이 영화가 가지고 있는 정보를 가리킬 때 '영화'라는 단어를 사용한다.
  - '상영'은 실제로 관객들이 영화를 관람하는 사건을 표현한다.
    - 상영 일자, 시간, 순번 등을 가리키기 위해 '상영'이라는 단어를 사용한다.
    - 사용자가 실제로 예매하는 대상은 영화가 아닌 상영이다.
  - 하나의 영화는 하루 중 다양한 시간대에 걸쳐 한 번 이상 상영될 수 있다.
  - 특정한 조건을 만족하는 예매자는 할인받을 수 있다.
    - 할인 조건(discount condition)
      - 할인조건은 가격의할인 여부를 결정하며 순서 조건과 기간 조건으로 나뉜다.
        - 순서 조건은 상영 순번을 이용해 할인 여부를 결정한다.
        - 기간 조건은 영화 상영 시작 시간을 이용해 할인 여부를 결정한다.
          - 기간 조건은 요일, 시작 시간, 종료 시간의 세 부분으로 구성되며 영화 시작 시간이 해당 기간안에 포함될 경우 할인을 적용한다.
    - 할인 정책(discount policy)
      - 할인 정책은 금액 할인 정책과 비율 할인 정책이 있다.
        - 금액 할인 정책은 예매 요금에서 일정 금액을 할인해주는 방식
        - 비율 할인 정책은 예매 요금에서 일정 비율을 할인해주는 방식
    - 영화별로 하나의 할인 정책만 할당할 수 있다. 지정하지 않는 것도 가능
    - 할인 조건은 다수의 할인 조건을 함께 지정할 수 있으며, 순서 조건과 기간 조건을 섞는 것도 가능하다.

위 요구사항대로 할인을 적용하기 위해서는 할인 조건과 할인 정책을 함께 조합해서 사용한다. 먼저 사용자의 예매 정보를 통해 할인 조건 중 하나라도 만족하는지 검사한다. 할인 조건을 만족할 경우 할인 정책을 이용해 할인 요금을 계산한다. 할인 정책은 적용돼 있지만 할인 조건을 만족하지 못하는 경우나 아예 할인 정책이 적용돼 있지 않은 경우엔 할인하지 않는다.

### 객체지향 프로그래밍을 향해

#### 협력, 객체, 클래스

대부분의 사람이 객체지향 언어로 코딩할 때 가장 먼저 작성하게 되는 것은 클래스로 클래스가 결정된 이후에 속성과 메서드를 결정한다. 하지만 이는 객체지향의 본질과 거리가 있으며 객체지향은 말 그대로 객체를 지향하는 것이다.

진정한 객체지향 패러다임의 전환은 클래스가 아닌 객체에 초점을 맞출 때에만 얻을 수 있다. 이를 위해선 다음에 집중해야 한다.

- 어떤 클래스가 필요한지를 고민하기 전에 어떤 객체들이 필요한지 고민하라.
  - 클래스는 공통적인 상태와 행동을 공유하는 객체들을 추상화한 것이다. (정적모델)
  - 클래스의 윤곽을 잡기 위해서는 어떤 객체들이 어떤 상태와 행동을 가지는지를 먼저 결정해야 한다.
  - 객체를 중심에 두는 접근 방법은 설계를 단순하고 깔끔하게 만든다. (즉, 필요 이상의 구현을 하지 않음)
- 객체는 독립적인 존재가 아니라 기능을 구현하기 위해 협력하는 공동체의 일원으로 봐야 한다. (어떤 객체도 섬이 아니다.)
  - 객체를 협력하는 공동체의 일원으로 바라보는 것은 설계를 유연하고 확장 가능하게 만든다.
  - 객체지향적으로 생각하고 싶다면 객체를 고립된 존재로 바라보지 말고 협력에 참여하는 협력자로 바라봐야 한다.
  - 객체들의 모양과 윤곽이 잡히면 공통된 특성과 상태를 가진 객체들을 타임으로 분류하고 이 타입을 기반으로 클래스를 구현한다.

*1장에서 정리했지만 중요하기에 반복해서 적는다. 설계의 기초는 객체의 동적 모델을 먼저 도메인 모델에 맞게 만들고, 그에 맞는 인터페이스(메시지)를 만든 뒤 이 객체들 사이의 협력 공동체를 설계하는 것이다. 그 이후에 정적모델인 클래스로 동적 모델을 투사하여 각각 객체에 올바른 책임을 할당한 뒤 객체들의 협력에서 스스로, 자율적으로 역할을 수행하는 것이다.*

#### 도메인의 구조를 따르는 프로그램 구조

이 시점에서 **도메인(domain)**이라는 용어를 살펴보는 것이 도움이 될 것이다. 소프트웨어는 사용자가 원하는 어떤 문제를 해결하기 위해 만들어진다. 영화 예매 시스템의 목적은 영화를 좀 더 쉽고 빠르게 예매하려는 사용자의 문제를 해결하는 것이다.

이처럼 문제를 해결하기 위해 사용자가 프로그램을 사용하는 분야를 **도메인**이라고 부른다.

객체지향 패러다임이 강력한 이유는 요구사항을 분석하는 초기 단계부터 프로그램을 구현하는 마지막 단계까지 객체라는 동일한 추상화 기법을 사용할 수 있기 때문이다. 요구사항과 프로그램 객체라는 동일한 관점에서 바라볼 수 있기 때문에 도메인을 구성하는 개념들이 프로그램의 객체와 클래스로 매끄럽게 연결될 수 있다.

- [객체지향의 사실과 오해 도메인 관련 글](https://github.com/fkdl0048/BookReview/blob/main/Object-oriented_Facts_and_Misunderstandings/Chapter06.md#%EB%8F%84%EB%A9%94%EC%9D%B8-%EB%AA%A8%EB%8D%B8)

![image](https://github.com/fkdl0048/BookReview/assets/84510455/ac0b5692-34a6-4aef-ae3c-ac2592b67627)

이 그림은 영화 예매 도메인을 구성하는 개념과 관계를 표현한 것이다. 영화는 여러 번 상영될 수 있고 상영은 여러 번 예매될 수 있다는 것을 알 수 있다. 영화에는 할인 정책을 할당하지 않거나 할당하더라도 오직 하나만 할당할 수 있고, 할인 정책이 존재하는 경우에는 하나 이상의 할인 조건이 반드시 존재한다는 것을 알 수 있다.

*이러한 도메인 모델은 설계 레벨에서 바로 작성하는 것이 아닌 요구사항을 충분히 분석 후 글로 적어도 문제가 없다면 그림으로 그려보는 것도 좋다. 가장 좋은 점은 이런 다이어그램은 이해관계자들에게 설명할 때 효과적이라는 것이다. 지금 이 책을 읽고 있는 나에게 저자는 가장 효과적인 방법을 사용한 것.*

자바나 C#같은 클래스 기반의 객체지향 언어에 익숙하다면 도메인 개념을 구현하기 위해 클래스를 사용한다는 사실이 낯설지는 않을 것이다. 일반적으로 클래스의 이름은 대응되는 **도메인 개념의 이름과 동일하거나 적어도 유사하게 지어야 한다.** 클래스 사이의 관계도 최대한 도메인 개념 사이에 맺어진 관계와 유사하게 만들어서 프로그램의 구조를 이해하고 예상하기 쉽게 만들어야 한다.

#### 클래스 구현하기

도메인 개념들의 구조를 반영하는 적절한 클래스 구조를 만들었다면 이제 남은 일은 적절한 프로그래밍 언어를 이용해 이 구조를 표현하는 것이다.

*구현하기 앞서 뒤에서 설명할지 모르겠지만, 객체간의 협력의 메시지를 결정하는 것이 우선이 되어야 한다. 이를 꼭 유스케이스 형태로 표현할 필요는 없지만, 객체간의 메시지를 통한 객체의 역할과 책임을 결정하는 것이 선행되어야 한다. 아마 책에선 뒷 부분에서 나올 것이라 예상되지만 이번 장은 들어가는 말에서 언급한 것 처럼 객체지향 프로그래밍을 보여주기 위한 챕터인 듯 하다.*

`Screening` 클래스는 사용자들이 예매하는 대상인 '상영'을 구현한다. Screening은 상영할 영화(movie), 순번(sequence), 상영 시작 시간(whenScreened)을 인스턴스 변수로 포함한다. `Screening`은 상영 시작 시간을 반환하는 `GetStartTime()` 메서드, 순번의 일치 여부를 검사하는 `IsSequence()` 메서드, 기본 요금을 반환하는 `GetMovieFee()` 메서드를 포함한다.

```cs
class Screening
{
    private Movie movie;
    private int sequence;
    private DateTime whenScreened;

    public Screening(Movie movie, int sequence, DateTime whenScreened)
    {
        this.movie = movie;
        this.sequence = sequence;
        this.whenScreened = whenScreened;
    }

    public DateTime GetStartTime() => whenScreened;
    public bool IsSequence(int sequence) => this.sequence is sequence;
    public Money GetMovieFee() => movie.GetFee();
}
```

여기서 주목할 점은 인스턴스 변수의 가시성은 private이고 메서드의 가시성은 public이라는 것이다. **클래스를 구현하거나 다른 개발자에 의해 개발된 클래스를 사용할 때 가장 중요한 것은 클래스의 경계를 구분 짓는 것이다.**

클래스는 내부와 외부로 구분되며 훌륭한 클래스를 설계하기 위한 핵심은 어떤 부분을 외부에 공개하고 어떤 부분을 감출지를 결정하는 것이다. Screening에서 알 수 있는 것처럼 외부에서는 객체의 속성에 직접 접근할 수 없도록 막고 적절한 public 메서드를 통해서만 내부 상태를 변경할 수 있게 해야 한다.

**이렇게 내부와 외부를 구분하는 이유는 경계의 명확성이 객체의 자율성을 보장하기 때문이다. 그리고 더 중요한 이유로 프로그래머에게 구현의 자유를 제공하기 때문이다.**

##### 자율적인 객체

자율적인 객체를 이해하기 앞서 두 가지 중요한 사실을 정리해야 한다.

- 첫 번째 사실은 객체가 **상태(state)**와 **행동(behavior)**을 함께 가지는 복합적인 존재라는 것이다.
- 두 번째 사실은 객체가 스스로 판단하고 행동하는 **자율적인 존재**라는 것이다.

*두 가지 사실은 서로 깊이 연관돼 있다.*

- 데이터와 기능을 객체 내부로 함께 묶는 것을 **캡슐화**라고 한다.
- 외부에서의 접근을 통제할 수 있는 **접근 제어** 메커니즘도 함께 제공한다.
  - public, protected, private와 같은 **접근 수정자**를 제공한다.

캡슐화와 접근 제어는 객체를 두 부분으로 나눈다. 하나는 외부에서 접근 가능한 부분으로 이를 **퍼블릭 인터페이스(public interface)**라고 부른다. 다른 하나는 외부에서는 접근 불가능하고 오직 내부에서만 접근 가능한 부분으로 이를 **구현(implementation)**이라고 부른다. (DIP원칙의 중요성은 뒤에서 다룸)

##### 프로그래머의 자유

프로그래머의 역할을 **클래스 작성자(class creator)**와 **클라이언트 프로그래머(client programmer)**로 구분하는 것이 유용하다. 클래스 작성자는 새로운 데이터 타입을 프로그램에 추가하고, 클라이언트 프로그래머는 클래스 작성자가 추사한 데이터 타입을 사용한다.

클라이언트 프로그래머의 목표는 필요한 클래스들을 엮어서 애플리케이션을 빠르고 안정적으로 구축하는 것이다. 클래스 작성자는 필요한 부분만 공개하고 나머지는 꽁꽁 숨겨야 한다. 숨겨진 나머지 부분을 클라이언트 프로그래머가 접근하지 못함으로서 그에 대한 영향을 걱정하지 않고도 내부 구현을 마음대로 변경할 수 있다. 이를 **구현 은닉(implementation hiding)**이라고 부른다.

접근 제어 메커니즘은 프로그래밍 언어 차원에서 클래스의 내부와 외부를 명확하게 경계 지을 수 있게 하는 동시에 클래스 작성자가 내부 구현을 은닉할 수 있게 해준다. 또한 클라이언트 프로그래머가 실수로 숨겨진 부분에 접근하는 것을 막아준다.

객체의 외부와 내부를 구분하면 클라이언트 프로그래머가 알아야 할 지식의 양이 줄고(추상화) 클래스 작성자가 자유롭게 구현을 변경할 수 있는 폭이 넓어진다. 따라서 클래스를 개발할 때마다 인터페이스와 구현을 깔끔하게 분리하기 위해 노력해야 한다.

설계가 필요한 이유는 변경을 관리하기 위해서라는 것을 기억하자. 객체지향 언어에서 객체 사이의 의존성을 적절히 관리함으로써 변경에 관리함으로써 변경에 대한 파급효과를 제어할 수 있는 다양한 방법을 제공한다. 객체의 변경을 관리할 수 있는 기법 중 가장 대표적인 것이 **접근 제어**이다.

*앞서 다룬 캡슐화에 관한 내용으로 프로그래머의 역할로 바라봤다.*

#### 협력하는 객체들의 공동체

```cs
class Screening
{
    public Resevation Reserve(Customer customer, int adienceCount)
    {
        return new Resevation(customer, this, CalculateFee(audienceCount), audienceCount);
    }

    private Money CalculateFee(int audienceCount)
    {
        return movie.CalculateFee(this).times(audienceCount);
    }
}
```

- `Screening`의 `Reserve()`메서드는 영화를 예매한 후 예매 정보를 담고 있는 `Reservation`의 인스턴스를 생성해서 반환한다.
- `CalculateFee()`메서드는 요금을 계산하기 위해 다시 `Movie`의 `CalculateFee()`메서드를 호출한다.
- `Movie`의 `CalculateFee()`는 1인당 예매 요금이다. 따라서 `Screening`은 전체 예매 요금을 구하기 위해 `CalculateFee()` 메서드의 반환값에 인원 수인 audienceCount를 곱한다.

```cs
class Money
{
    public static const Money ZERO = Money.Wons(0);

    private const BigDecimal amount;

    public static Money Wons(double amount) => return new Money(BigDecimal.valueOf(amount));
    
    public Money(BigDecimal amount)
    {
        this.amount = amount;
    }

    public Money Plus(Money amount)
    {
        return new Money(this.amount.add(amount.amount));
    }

    public Money Minus(Money amount)
    {
        return new Money(this.amount.subtract(amount.amount));
    }

    public Money Times(double percent)
    {
        return new Money(this.amount.multiply(BigDecimal.valueOf(percent)));
    }

    public bool IsLessThan(Money other)
    {
        return amount.compareTo(other.amount) < 0;
    }

    public bool IsGreaterThanOrEqual(Money other)
    {
        return amount.compareTo(other.amount) >= 0;
    }
}
```

객체지향의 장점은 객체를 이용해 도메인의 의미를 풍부하게 표현할 수 있다는 것이다. 따라서 의미를 좀 더 명시적이고 분명하게 표현할 수 있다면 객체를 사용해서 개념을 구현하는 것이 좋다. 그 개념이 비록 하나의 인스턴스 변수만을 포함하더라도 개념을 명시적으로 표현하는 것은 전체적인 설계의 명확성고 유연성을 높이는 방법이다.

*비슷한 예로 인터페이스가 단일적으로 필요하더라도 선언하여 사용하는 것이 좋을 수 있다는 예가 있다.*

```cs
class Reservation
{
    private Customer customer;
    private Screening screening;
    private Money fee;
    private int audienceCount;

    public Reservation(Customer customer, Screening screening, Money fee, int audienceCount)
    {
        this.customer = customer;
        this.screening = screening;
        this.fee = fee;
        this.audienceCount = audienceCount;
    }
}
```

영화를 예매하기 위해 `Screening`, `Moview`, `Reservation` 인스턴스들은 서로의 메서드를 호출하며 상호작용한다. 이 처럼 시스템의 어떤 기능을 구현하기 위해 객체들 사이에 이뤄지는 상호작용을 **협력(Collaboration)**이라고 부른다.

객체지향 프로그램을 작성할 때는 먼저 협력의 관점에서 어떤 객체가 필요한지를 결정하고, 객체들의 공통 상태와 행위를 구현하기 위해 클래스를 작성한다.

#### 협력에 관한 짧은 이야기

앞에서 설명한 것처럼 객체의 내부 상태는 외부에서 접근하지 못하도록 감춰야 한다. 대신 외부에 공개 하는 퍼블릭 인터페이스를 통해 내부 상태에 접근할 수 있도록 허용한다. 객체는 다른 객체의 인터페이스에 공개된 행동을 수행하도록 **요청(request)**할 수 있다. 요청을 받는 객체는 자율적인 방법에 따라 요청을 처리한 후 **응답(response)**한다.

- [협력에 관한 객체지향의 사실과 오해 관련 글](https://github.com/fkdl0048/BookReview/blob/main/Object-oriented_Facts_and_Misunderstandings/Chapter04.md#%ED%98%91%EB%A0%A5)

객체가 다른 객체와 상호작용할 수 있는 유일한 방법은 **메시지를 전송(send a message)**하는 것뿐이다. 다른 객체에게 요청이 도착할 때 해당 객체가 **메시지를 수신(receive a message)**했다고 이야기한다. 메세지를 수신한 객체는 스스로의 결정에 따라 자율적으로 메세지를 처리할 방법을 결정한다. 이처럼 수신된 메시지를 처리하기 위한 자신만의 방법을 **메서드(method)**라고 부른다.

**메세지와 메서드를 구분하는 것은 매우 중요하다.** 객체지향 패러다임이 유연하고, 확장 가능하며, 재사용 가능한 설계를 낳는다는 명성을 얻게 된 배경에는 메시지와 메서드를 명확하게 구분한 것도 단단히 한 몫한다. 뒤에서 나오지만 메세지와 메서드의 구분에서 **다형성(polymorphism)**의 개념이 출발한다.

*지금까지는 Screening이 Movie의 CalculateMovie 메서드를 호출한다고 말했지만 사실은 Screening이 Movie에게 CalculateMovieFee 메시지를 전송한다라고 말하는 것이 더 적절한 표현이다. 사실 Screening은 Movie안에 CalculateMovieFee 메서드가 존재하고 있는지조차 알지 못한다.단지 Movie가 CalculateMovieFee메시지에 응답할 수 있다고 믿고 메시지를 전송할 뿐이다.*

### 할인 요금 구하기

#### 할인 요금 계산을 위한 협력 시작하기

계속해서 예매 요금을 계산하는 협력을 알아보면, Movie는 제목, 상영시간, 기본요금, 할인 정책을 속성으로 가진다. 이 속성들의 값은 생성자를 통해 전달받는다.

```cs
class Movie
{
    private string title;
    private Duration runningTime;
    private Money fee;
    private DiscountPolicy discountPolicy;

    public Movie(string title, Duration runningTime, Money fee, DiscountPolicy discountPolicy)
    {
        this.title = title;
        this.runningTime = runningTime;
        this.fee = fee;
        this.discountPolicy = discountPolicy;
    }

    public Money GetFee() => fee;
    public Money CalculateMovieFee(Screening screening) => fee.minus(discountPolicy.CalculateDiscountAmount(screening));
}
```

`CalculateMovieFee()`메서드는 `discountPolicy`에 `CalculateDiscountAmount`메시지를 전송해 할인 요금을 반환받는다. Movie는 기본요금인 fee에서 반환된 할인 요금을 차감한다.

이 코드에서 중요한 점은 어떠한 할인 정책을 사용할 것인지에 대한 코드가 어디에도 존재하지 않는다. 도메인을 설명할 때 언급했던 것처럼 영화 예매 시스템에는 두 가지 종류의 할인 정책이 존재한다. 하나는 일정한 금액을 할인해주는 금액 할인 정책이고 다른 하나는 일정한 비율에 따라 할인해주는 비율 할인 정책이다.

따라서 예매 요금을 계산하기 위해서는 현재 영화에 적용돼 있는 할인 정책의 종류를 판단할 수 있어야 한다. 하지만 코드 어디에도 할인 정책을 판단하는 코드는 존재하지 않는다. 단지 `DiscountPolicy`에게 메시지를 전송할 뿐이다.

*여기서 바로 찾아낸다면 객체지향에 대한 기초는 있는 것이라 봐도 무방하지만 한번에 이해가 되지 않는다면 익숙하지 않은 것으로 봐야 한다.*

이 코드에는 **상속**과 **다형성**이라는 개념이 숨어있고 그 기반은 **추상화**라는 원리가 숨겨져 있다.

#### 할인 정책과 할인 조건

할인 정책은 금액 할인 정책과 비율 할인 정책으로 구분된다. 두 가지 할인 정책을 각각 `AmountDiscountPolicy`와 `PercentDiscountPolicy`라는 클래스로 구현한다. 두 클래스는 대부분의 코드가 유사하고 할인 요금을 계산하는 방식만 족므 다르다. 따라서 두 클래스 사이의 중복 코드를 제거하기 위해 공통으로 코드를 보관할 장소가 필요하다.

`DiscountPolicy`라는 추상 클래스를 만들어 두 클래스의 공통 코드를 이 클래스로 옮긴다.

```cs
abstract class DiscountPolicy
{
    private List<DiscountCondition> conditions = new();

    public DiscountPolicy(params DiscountCondition[] conditions)
    {
        this.conditions = conditions.ToList();
    }

    public Money CalculateDiscountAmount(Screening screening)
    {
        foreach (var each in conditions)
        {
            if (each.IsSatisfiedBy(screening))
            {
                return GetDiscountAmount(screening);
            }
        }
        return Money.ZERO;
    }

    protected abstract Money GetDiscountAmount(Screening screening);
}
```

- `DiscountPolicy`는 `DiscountCondition`의 리스트인 `conditions`를 가지고 있기 때문에 하나의 할인 정책은 여러 개의 할인 조건을 포함할 수 있다. (다이어 그램에서 1..n의 관계)
- `CalculateDiscountAmount`는 전체 할인 조건에 대해 차례대로 `DiscountCondition`의 `IsSatisfiedBy`메서드를 호출해 할인 조건을 만족하는지 검사한다. 만족하는 조건이 있다면 `GetDiscountAmount`를 호출해 할인 요금을 계산한다.

이 과정은 추상 메서드(동적 바인딩)의 형태로 호출되어 동작한다. 실제로 요금 계산하는 부분은 추상 메서드인 `GetDiscountAmount` 메서드에게 위임한다. 실제 내부는 상속 받은 자식 클래스에서 오버라이딩한 메서드가 실행 될 것이다.

이처럼 부모 클래스에 기본적인 알고리즘의 흐름을 구현하고 중간에 필요한 처리를 자식 클래스에게 위임하는 디자인 패턴을 **템플릿 메서드 패턴**이라고 부른다.

*탬플릿 메서드 패턴, 전략 패턴 두 가지 모두 동적 바인딩을 핵심으로 두고 상속이냐 합성이냐의 문제이다.*

`DiscountCondition`은 인터페이스를 이용하여 선언돼 있다. `IsSatisfiedBy`오퍼레이션은 인자로 전달된 screening이 할인이 가능한 경우 true를 반환하고 그렇지 않은 경우 false를 반환한다.

반환값은 bool이지만 내부 구현은 이를 상속받은 클래스에서 구현할 것이다. 이는 **다형성**의 개념이다.

```cs
public interface DiscountCondition
{
    bool IsSatisfiedBy(Screening screening);
}
```

- 영화 예매 시스템에는 순번 조건과 기간 조건의 두 가지 할인 조건이 존재한다. 두 가지 할인 조건은 각각 `DiscountCondition`을 상속받은 `SequenceCondition`과 `PeriodCondition`으로 구현된다.

```cs
class SequenceCondition : DiscountCondition
{
    private int sequence;

    public SequenceCondition(int sequence)
    {
        this.sequence = sequence;
    }

    public bool IsSatisfiedBy(Screening screening) => screening.IsSequence(sequence);
}
```

```cs
class PeriodCondition : DiscountCondition
{
    private DayOfWeek dayOfWeek;
    private LocalTime startTime;
    private LocalTime endTime;

    public PeriodCondition(DayOfWeek dayOfWeek, LocalTime startTime, LocalTime endTime)
    {
        this.dayOfWeek = dayOfWeek;
        this.startTime = startTime;
        this.endTime = endTime;
    }

    public bool IsSatisfiedBy(Screening screening)
    {
        return screening.GetStartTime().getDayOfWeek() == dayOfWeek &&
            startTime.compareTo(screening.GetStartTime().toLocalTime()) <= 0 &&
            endTime.compareTo(screening.GetStartTime().toLocalTime()) >= 0;
    }
}
```

- `SequenceCondition`은 할인 여부를 판단하기 위한 순서를 받아 실제 상영 순번과 일치한다면 할인 가능한 것으로 판단한다.
- `PeriodCondition`은 할인 여부를 판단하기 위한 요일, 시작 시간, 종료 시간을 받아 실제 상영 시작 시간이 해당 기간에 포함된다면 할인 가능한 것으로 판단한다.

이제 할인 조건에 대한 구현이 끝났다면 할인 정책을 구현할 차례이다. 앞서 작성한 `DiscountPolicy`을 상속받아 `AmountDiscountPolicy`와 `PercentDiscountPolicy`를 구현한다.

```cs
class AmountDiscountPolicy : DiscountPolicy
{
    private Money discountAmount;

    public AmountDiscountPolicy(Money discountAmount, params DiscountCondition[] conditions) : base(conditions)
    {
        this.discountAmount = discountAmount;
    }

    protected override Money GetDiscountAmount(Screening screening) => discountAmount;
}
```

```cs
class PercentDiscountPolicy : DiscountPolicy
{
    private double percent;

    public PercentDiscountPolicy(double percent, params DiscountCondition[] conditions) : base(conditions)
    {
        this.percent = percent;
    }

    protected override Money GetDiscountAmount(Screening screening) => screening.GetMovieFee().Times(percent);
}
```

- `AmountDiscountPolicy`는 할인 요금을 계산하기 위해 고정된 금액을 사용한다. 따라서 할인 요금을 계산하기 위해 `GetDiscountAmount`메서드는 `discountAmount`를 반환한다.
- `PercentDiscountPolicy`는 할인 요금을 계산하기 위해 일정 비율을 사용한다. 따라서 할인 요금을 계산하기 위해 `GetDiscountAmount`메서드는 `screening.GetMovieFee().Times(percent)`를 반환한다.

정리하자면 `Movie`에서 할인 정책그리고 할인 요금으로 가는 과정에서 인터페이스를 통한 합성 구현 그리고 추상클래스를 이용한 탬플릿 메서드 패턴등 실제 다형성이 어떻게 객체지향에서 활용되는지 알아봤다.

#### 할인 정책 구성하기

앞서 다이어그램에서 단 하나의 할인 정책만 설정할 수 있지만 할인 조건의 경우 여러 개를 설정할 수 있다고 했다. `Movie`와 `DiscountPolicy`의 생성자는 이런 제약을 강제한다. 반면 `DiscountPolicy`의 생성자는 여러 개의 할인 조건을 받을 수 있도록 구현되어 있다.

이처럼 생성자의 파라미터 목록을 이용해 초기화에 필요한 정보를 전달하도록 **강제**하면 올바른 상태를 가진 객체의 생성을 보장할 수 있다.

다음은 실제 예제 영화의 생성 컨테이너의 예시이다.

```cs
class Program
{
    static void Main(string[] args)
    {
        var avatar = new Movie("아바타",
            Duration.ofMinutes(120),
            Money.Wons(10000),
            new AmountDiscountPolicy(Money.Wons(800),
                new SequenceCondition(1),
                new SequenceCondition(10),
                new PeriodCondition(DayOfWeek.MONDAY, LocalTime.of(10, 0), LocalTime.of(11, 59)),
                new PeriodCondition(DayOfWeek.THURSDAY, LocalTime.of(10, 0), LocalTime.of(20, 59))));
    }
}
```

*보면 알 수 있듯이 모든 것이 객체로 동작하며, 할인 정책은 1개로 나머지 할인 조건은 개수가 상관이 없다. 실제 동작에선 할인 조건을 시퀀싱하며 검사하여 동작하기 때문이다.*

### 상속과 다형성

앞 `Movie`클래스 어디에서도 할인 정책이 금액 할인 정책인지, 비율 할인 정책인지를 판단하지 않는다. Movie 내부에 할인 정책을 결정하는 조건문이 없는데도 이를 알아서 처리한다.

이 개념은 상속과 다형성에 대해서 명확하게 이해가 되어야 한다.

#### 컴파일 시간 의존성과 실행 시간 의존성

> 실행시간 == 런타임

앞서 다룬 다이어그램에서 알 수 있듯이 `Movie`클래스는 `DiscountPolicy`에 의존하고 있다. 그리고 `AmountDiscountPolicy`와 `PercentDiscountPolicy`는 `DiscountPolicy`을 상속받아 구현하고 있다.

`DiscountPolicy`는 추상클래스이기 `Movie`의 인스턴스는 실행 시에 실질적인 객체가 무엇인지 알 수 없지만, 실질적인 객체가 필요하다. 즉, 런타임에 `PercentDiscountPolicy`, `DiscountPolicy`에 의존하게 된다. 하지만 재밌는 점은 코드 수준에서 `Movie`는 두 클래스 중 어떤 것에도 의존하지 않는다. 오직 `DiscountPolicy`에만 의존한다. (다형성)

*실제 아바타 영화의 생성을 보면 new를 통한 동적할당을 통해 런타임에 의존성을 옮긴다.*

즉, **코드의 의존성과 실행 시점의 의존성이 서로 다를 수 있다는 것이다. 다시 말해 클래스 사이의 의존성과 객체 사이의 의존성은 동일하지 않을 수 있다. 그리고 유연하고, 쉽게 재사용할 수 있으며, 확장 가능한 객체지향 설계가 가지는 특징은 코드의 의존성과 실행 시점의 의존성이 다르다는 것이다.**

한 가지 간과해서는 안 되는 사실은 **코드의 의존성과 실행 시점의 의존성이 다르면 다를수록 코드를 이해하기 어려워진다는 것이다.** 코드를 이해하기 위해서는 코드뿐만 아니라 객체를 생성하고 연결하는 부분을 찾아야 하기 때문이다. 반면 코드의 의존성과 실행 시점의 의존성이 다르면 다를수록 코드는 더 유연해지고 확장 가능해진다. 이와 같은 의존성의 양면성은 설계가 트레이드 오프의 산물이라는 사실을 보여준다.

설계가 유연해질수록 코드를 이해하고 디버깅하기는 점점 더 어려워진다는 사실을 기억하라. 번면 유연성을 억제하면 코드를 이해하고 디버깅하기는 쉬워지지만 재사용성과 확장성은 낮아진다는 사실도 기억하자. 매번 강조하지만 프로그래머는 이 사이의 경계에서 줄타기를 해야 한다. 무조건 유연한 설계도, 무조건 읽기 쉬운 코드도 정답이 아니다. 이것이 객체지향 설계가 어려우면서도 매력적인 이유다.

> 은총알은 없다. 트레이드오프만 있을 뿐

#### 차이에 의한 프로그래밍

객체지향 언어를 배우면서 가장 먼저 배우는 개념인 상속은 클래스간의 중복성을 줄이고 재사용하기 위해서 사용한다고 한다. 실제 코드에서도 많이 사용되고 가장 널리 알려진 개념이다.

이처럼 부모 클래스와 다른 부분만을 추가해서 새로운 클래스를 쉽고 빠르게 만드는 방법을 **차이에 의한 프로그래밍(programming by difference)**이라고 부른다.

#### 상속과 인터페이스

상속이 가치 있는 이유는 부모 클래스가 제공하는 모든 인터페이스를 자식 클래스가 물려받을 수 있기 때문이다. (코드의 중복이 효과적으로 줄어듬) 대부분의 사람들은 상속의 목적이 메서드나 인스턴스 변수를 재사용하는 것이라고 생각하기 때문이다.

인터페이스는 객체가 이해할 수 있는 메시지의 목록을 정의한다는 것을 기억하자. 상속을 통해 자식 클래스는 자신의 인터페이스에 부모 클래스의 인터페이스를 포함하게 된다. 결과적으로 자식 클래스는 부모 클래스가 수신할 수 있는 모든 메시지를 수신할 수 있게 때문에 외부 객체는 자식 클래스를 부모 클래스와 동일한 타입으로 간주할 수 있다.

```cs
class Movie
{
    public Money CalculateMovieFee(Screening screening) => fee.minus(discountPolicy.CalculateDiscountAmount(screening));
}
```

`Movie`가 `DiscountPolicy`의 인터페이스에 정의된 `CalculateDiscountAmount`에 **메시지**를 전송하고 있다.

*이 부분이 정말 중요하다. 앞서 언급한 메시지와 메서드의 차이는 이 다형성을 설명할 때 도움이 된다. 좀 더 들어가 실제 구현도 메시지와 메서드 형태로 구성되며 해당 참조에 메시지를 전송하고 이를 바인딩 형태로 올바른 메서드를 실행한다.*

`DiscountPolicy`를 상속받는 `AmountDiscountPolicy`와 `PercentDiscountPolicy`의 인터페이스에도 이 오퍼레이션이 포함돼 있다는 사실에 주목하자. `Movie`의 **입장에선 자신과 협력하는 객체가 어떤 클래스의 인스턴스인지는 전혀 중요하지 않다.** 오직 메시지를 수신할 수 있다는 사실이 중요하다. 즉, `Movie`는 협력 객체가 `CalculateDiscountAmount`라는 메시지를 이해할 수만 있다면 그 객체가 어떤 클래스의 인스턴스인지는 상관하지 않는다는 것이다.

따라서 `CalculateDiscountAmount`메시지를 수신할 수 있는 `AmountDiscountPolicy`, `PercentDiscountPolicy`의 인스턴스는 `Movie`와 협력할 수 있는 것이다.

*이것이 다형성이고 C#, Java의 인터페이스 기본 개념이다.*

이처럼 자식 클래스가 부모 클래스를 대신한느 것을 **업캐스팅(upcasting)**이라고 부른다. 책의 예제에서 업 캐스팅은 당시 할당 관계에서 부모 참조 변수를 통해(템플릿 메서드 패턴) 사용하였기에 자연스럽고 이해가 가지만, 강제적인 업캐스팅은 위험하다.

#### 다형성

다시 한번 강조하지만 메시지와 메서드는 다른 개념이다.

다형성은 객체지향 프로그램의 컴파일 시간 의존성과 실행 시간 의존성이 다를 수 있다는 사실을 기반으로 한다. 프로그램을 작성할 때 `Movie`클래스는 추상 클래스인 `DiscountPolicy`에 의존한다. 따라서 컴파일 파일 시간 의존성은 `Movie`에서 `DiscountPolicy`로 향한다. 반면 실행 시점에 `Movie`의 인스턴스와 실제로 상호작용하는 객체는 `DiscountPolicy`의 서브클래스인 `AmountDiscountPolicy`와 `PercentDiscountPolicy`이다. 따라서 실행 시점의 의존성은 `Movie`에서 `AmountDiscountPolicy`와 `PercentDiscountPolicy`로 향한다.

다형성이란 동일한 메시지를 수신했을 때 객체의 타입에 따라 다르게 응답할 수 있는 능력을 의미한다. 따라서 다형적인 협력에 참여하는 객체들은 모두 같은 메시지를 이해할 수 있어야 한다. 다시 말해 인터페이스가 동일해야 한다는 것이다.

다형성을 구현하는 방법은 매우 다양하지만 메시지에 응답하기 위해 실행될 메서드를 컴파일 시점이 아닌 실행 시점에 결정한다는 공통점이 있다. 다시 말해 메시지와 메서드를 실행 시점에 바인딩한다는 것이다. 이를 **지연 바인딩(lazy binding)** 또는 **동적 바인딩(dynamic binding)**이라고 부른다.

그에 반해 전통적인 함수 호출처럼 컴파일 시점에 실행될 함수나 프로시저를 결정하는 것을 **초기 바인딩(early binding)** 또는 **정적 바인딩(static binding)**이라고 부른다.

객체지향이 컴파일 시점의 의존성과 실행 시점의 의존성을 분리하고, 하나의 메시지를 선택적으로 서로 다른 메서드에 연결할 수 있는 이유가 바로 지연 바인딩이라는 메커니즘을 사용하기 때문이다.

- 구현 상속과 인터페이스 상속
  - 상속을 구현 상속과 인터페이스 상속으로 분류할 수 있다.
  - 구현 상속을 서브 클래싱이라고 부르고 인터페이스 상속을 서브 타이핑이라고 부른다.
  - 순수하게 코드를 재사용하기 위한 목적은 구현 상속(서브 클래싱)이 적합다.
  - 다형적인 협력을 위해 부모 클래스와 자식 클래스가 인터페이스를 공유할 수 있도록 상속을 이용하는 것을 인터페이스 상속(서브 타이핑)이라고 부른다.

*게임 엔진의 내부는 복잡한 구현 상속의 장이다. 하지만 책에선 변경에 취약한 코드를 낳게 된다고 하는데, 내 생각엔 상속의 구조에서 은총알은 없다. 개발 과정에서 불확실성이 매우 다양하기 때문에 상속을 멀리하고 합성을 주로 사용하는 이유도 있을 것이다. 하지만 게임엔진과 같이 매우 복잡한 설계에 복잡성을 줄이기 위해선 구현 상속을 사용하는 것도 좋은 방법이라 생각한다.*

#### 인터페이스와 다형성

`DiscountPolicy`를 추상 클래스로 구현함으로써 자식 클래스들이 인터페이스와 내부 구현을 함께 상속받도록 만들었다. 그러나 종종 구현은 공유할 필요가 없고 순수하게 인터페이스만 공유하고 싶을 때가 있다. 이를 위해 C#, Java에선 강력한 기능인 **인터페이스**를 제공한다. (C++은 추상 기반 클래스를 통해 구현한다.)

### 추상화와 유연성

#### 추상화의 힘

지금까지 살펴본 것처럼 할인 정책은 구체적인 금액 할인 정책과 비율 할인 정책을 포괄하는 추상적인 개념이다.

- `DiscountPolicy`는 `AmountDiscountPolicy`와 `PercentDiscountPolicy`보다 추상적이다.
- `DiscountCondition`은 `SequenceCondition`과 `PeriodCondition`보다 추상적이다.

프로그래밍 언어 측면에서 `DiscountPolicy`와 `DiscountCondition`이 더 추상적인 이유는 인터페이스에 초점을 맞추기 때문이다. `DiscountPolicy`는 모든 할인 정책들이 수신할 수 있는 `CalculateDiscountAmount`라는 메시지를 정의하고, `DiscountCondition`은 모든 할인 조건들이 수신할 수 있는 `IsSatisfiedBy`라는 메시지를 정의한다.

둘 다 같은 계층에 속하는 클래스들이 공통으로 가질 수 있는 인터페이스를 정의하며 구현의 일부 또는 전체를 자식 클래스가 결정하도록 결정권을 위임한다.

![image](https://github.com/fkdl0048/BookReview/assets/84510455/1d39250b-d05f-4b02-9862-ddaecf3e6fc8)

위 그림은 추상화의 경우 두 가지 장점을 보여준다.

- 추상화 계층만 따로 떼어 놓고 살펴보면 요구사항의 정책을 높은 수준에서 서술할 수 있다는 것이다.
  - 객체간의 협력을 추상적으로 바라볼 수 있기 때문에 더욱 유리하다는 것이다. 설계 단계에서 이런 과정을 거쳐야 한다.
  - 하나의 문장으로 보면 "영화 예매 요금은 최대 하나의 '할인 정책'과 다수의 '할인 조건'을 이용해 계산할 수 있다."
- 추상화를 이용하면 설계가 좀 더 유연해진다는 것이다.

추상화를 사용하면 세부적인 내용을 무시한 채 상위 정책을 쉽고 간단하게 표현할 수 있다. 이런 특징이 세부사항에 억눌리지 않고 상위 개념만으로도 도메인의 중요한 개념을 설명할 수 있게 한다.

추상화를 이용해 상위 정책을 기술한다는 것은 기본적인 애플리케이션의 협력 흐름을 기술한다는 것을 의미한다. 영화 예매 가격을 계산하기 위한 흐름은 항상 `Movie`에서 `DiscountPolicy`에게, 그리고 다시 `DiscountPolicy`에서 `DiscountCondition`을 향해 흐른다.

*재사용 가능한 설계의 기본을 이루는 디자인 패턴(design pattern)이나 프레임워크(framework) 모두 추상화를 이용해 상위 정책을 정의하는 객체지향 메커니즘을 활용하고 있다.*

추상화를 이용해 표현하면 기존 구조를 수정하지 않고도 새로운 기능을 쉽게 추가할 수 있다. 다시 말해 유연한 설계를 만들 수 있다. (SRP, OCP)

#### 유연한 설계

영화 예매 시스템에서 아직 `스타워즈`의 할인 정책을 해결하지 못했다. 할인 정책이 적용되어 있지 않기 때문에 기본 금액을 그대로 가져가면 되지만 할인 정책이 없는 경우를 예외 케이스로 취급하게 되면 일관성이 있던 협력 방식이 무너지게 된다.

기존 할인 정책의 경우에는 할인 금액을 계산하는 책임이 `DiscountPolicy`의 자식 클래스에 있었지만 할인 정책이 없는 경우에는 할인 금액이 0원이라는 사실을 결정하는 책임이 `DiscountPolicy`가 아닌 `Movie`에게 있다.

따라서 책임의 위치를 결정하기 위해 조건문을 사용하는 것은 협력 측면에서 대부분의 경우 좋지 않은 선택이다. 항사 예외 케이스를 최소화하고 일관성을 유지할 수 있는 방법을 선택해야 한다.

```cs
class NoneDiscountPolicy : DiscountPolicy
{
    protected override Money GetDiscountAmount(Screening screening) => Money.ZERO;
}
```

이제는 `Movie`의 인스턴스에 `NoneDiscountPolicy`를 할당하면 된다. 중요한 것은 기존 `Movie`나 `DiscountPolicy`의 코드를 수정하지 않고 `NoneDiscountPolicy`를 추가할 수 있다는 것이다. (OCP)

추상화가 유연한 설계를 가능하게 하는 이유는 설계가 구체적인 상황에 결합되는 것을 방지하기 때문이다. `Movie`는 특정한 할인 정책에 묶이지 않는다. 할인 정책을 구현한 클래스가 `DiscountPolicy`를 상속받고 있다면 어떤 클래스와도 협력이 가능하다.

**결론은 간단하다. 유연성이 필요한 곳에 추상화를 사용하라!**

#### 추상 클래스와 인터페이스 트레이드오프

`NoneDiscountPolicy`클래스의 코드를 보면 `GetDiscountAmount()`메서드가 어떤 값을 반환하더라도 상관이 없다는 사실을 볼 수 있다. 부모 클래스인 `DiscountPolicy`에서 할인 조건이 없을 경우에는 `GetDiscountAmount()`메서드를 호출하지 않기 때문이다. 이것은 부모 클래스인 `DiscountPolicy`와 `NoneDiscountPolicy`를 개념적으로 결합시킨다. `NoneDiscountPolicy`의 개발자는 `GetDiscountAmount()`가 호출되지 않을 경우 `DiscountPolicy`가 0원을 반환한다는 사실을 가정하고 있기 때문이다.

이 문제를 해결하기 위해 `DiscountPolicy`를 인터페이스로 교체하고 `NoneDiscountPolicy`가 `DiscountPolicy`의 `GetDiscountAmount()`가 아닌 `CalculateDiscountAmount()`를 구현하도록 만들 수 있다.

```cs
interface DiscountPolicy
{
    Money CalculateDiscountAmount(Screening screening);
}
```

```cs
class abstract DefaultDiscountPolicy : DiscountPolicy
{
    ...
}
```

```cs
class NoneDiscountPolicy : DiscountPolicy
{
    public Money CalculateDiscountAmount(Screening screening) => Money.ZERO;
}
```

이렇게 하면 `NoneDiscountPolicy`가 `DiscountPolicy` 인터페이스를 구현하도록 변경하면 개념적인 혼란과 결합을 제거할 수 있다.

이상적으로는 인터페이스를 사용하도록 변경한 설계가 더 좋은 것이다. 현실적으로는 `NoneDiscountPolicy`만을 위해 인터페이스를 추가하는 것이 과하다는 생각이 들 수 있을 것이다. 변경전의 클래스 역시 할인 금액이 0원이라는 사실을 효과적으로 전달했기 때문이다.

여기서 중요하게 이야기 해야할 부분은 구현과 관련된 모든 것들이 트레이드오프의 대상이 될 수 있다는 사실이다. 내가 작성하는 모든 코드에는 합당한 이유가 있어야 하며 아주 사소한 결정이라도 트레이드오프를 통해 얻어진 결론과 그렇지 않은 결론 사이의 차이는 크다. 고민하고 트레이드 오프하라!

#### 코드 재사용

- [합성에 관한 글(객체지향 사고 프로세스)](https://github.com/fkdl0048/BookReview/blob/main/The_Object-Oriented_Thought_Process/Chapter01.md)

상속은 코드를 재사용하기 위해 널리 사용되는 방법이지만 가장 좋은 방법인 것은 아니다. 객체지향을 조금만 공부해도 상속보단 합성이 좋다라는 말을 자주 듣게 된다.

현재 `Movie`가 `DiscountPolicy`의 코드를 재사용하는 방법이 바로 합성이다. 이 설계를 상속을 사용하도록 변경할 수도 있다. 그럼에도 왜 다들 합성을 사용할까?

*앞 장에서 여러번 이야기 했듯이 상속의 개념보단 합성의 개념이 실세계를 추상화하여 그려내기 더 적합하기 때문이다. is-a의 관계보다 has-a의 관계가 더 많은 경우와 상속의 고질적인 문제점등을 지적할 수 있다.*

#### 상속

상속은 객체지향 코드를 재사용하기 위해 널리 사용되는 기법이다. 하지만 두 가지 관점에서 설계에 안 좋은 영향을 미친다.

- 캡슐화 위반
  - 상속을 사용하기 위해선 부모 클래스의 내부를 잘 알고 있어야 한다. `AmountDiscountPolicy`와 `PercentDiscountPolicy`를 구현하는 개발자는 부모 클래스인 `Movie`의 내부 구현을 알아야 한다.
  - 결과적으로 부모 클래스의 구현이 자식 클래스에게 노출되기 때문에 캡슐화가 약화된다. 캡슐화가 약화되면 자식 클래스가 부모 클래스에 강하게 결합되도록 만들기 때문에 부모 클래스를 변경할 때 자식 클래스도 함께 변경될 가능성이 높다.
  - 결과적으로 상속을 과도하게 사용한 코드는 변경하기도 어려워진다.
- 설계를 유연하게 만들지 못한다.
  - 상속은 부모 클래스와 자식 클래스 사이의 관계를 컴파일 시점에 결정한다. 따라서 실행 시점에 객체의 종류를 변경하는 것은 불가능하다.

#### 합성

`Movie`는 요금을 계산하기 위해 `DiscountPolicy`의 코드를 재사용한다. 이 방법이 상속과 다른 점은 이 부모 클래스의 코드와 자식 클래스의 코드를 컴파일 시점에 하나의 단위로 강하게 결합하는 데 비해 `Movie`가 `DiscountPolicy`의 **인터페이스를 통해 약하게 결합된다는 것이다.**

실제로는 `Movie`는 `DiscountPolicy`가 외부에 `CalculateDiscountAmount` 메시지를 수신한다는 사실만 알고 내부 구현에 대해서는 전혀 알지 못한다. 이처럼 인터페이스에 정의된 메시지를 통해서만 코드를 재사용하는 방법을 **합성**이라고 부른다.

합성은 상속이 가지는 두 가지 문제점을 모두 해결한다. **인터페이스에 정의된 메시지를 통해서만 재사용이 가능하기 때문에 구현을 효과적으로 캡슐화할 수 있다.** 또한 **의존하는 인스턴스를 교체하는 것이 비교적 쉽게 때문에 설계를 유연하게 만든다.**

그렇다고 상속을 절대로 사용하지 말라는 말은 아니다. 대부분의 설계에선 상속과 합성을 적절히 함께 사용해야 한다.

### 느낀점

이번 장은 객체지향을 실제 코드로 어떻게 나타내는지를 보여주고자 한 것 같다. 그 과정에서 상속과 인터페이스의 다형성, 캡슐화 등의 역할들을 보여준 것 같고, 유연한 설계에서 오는 트레이드오프에 대한 현실도 잘 보여준 것 같다.

#### 논의사항

> 설계가 유연해질수록 코드를 이해하고 디버깅하기는 점점 더 어려워진다는 사실을 기억하라. 번면 유연성을 억제하면 코드를 이해하고 디버깅하기는 쉬워지지만 재사용성과 확장성은 낮아진다는 사실도 기억하자.

- 여러분의 코드에서 유연성과 이해하기 쉬운 코드를 어떻게 트레이드오프하고 있나요?
  - 비율적인 부분이나 지금의 코드에서 나아가야할 방향에 대해서 같이 논의해보면 좋을 것 같습니다.
