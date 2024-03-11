## 4장 설계 품질과 트레이드 오프

객체지향 설계의 핵심은 역할, 책임, 협력이다. 협력은 애플리케이션의 기능을 구현하기 위해 메시지를 주고받는 객체들 사이의 상호작용이다. 책임은 객체가 다른 객체와 협력하기 위해 수행하는 행동이고, 역할은 대체 가능한 책임의 집합이다.

- 앞 장의 내용 요약
  - 가장 중요한 것은 책임
  - 낮은 결합도와 높은 응집도
  - 트레이드 오프 고려
  - 행동에 초점을 맞춘다

가끔씩은 좋은 설계보다는 나쁜 설계를 살펴보는 과정에서 통찰을 얻기도 한다. 특히 좋은 설계와 나쁜 설계를 비교하면서 살펴볼 때 효과가 좋은데, 나쁜 설계와 좋은 설계에 대한 명암의 대비가 좀 더 또렷해지기 때문이다.

이번 장은 영화 예매 시스템을 책임이 아닌 상태를 표현하는 데이터 중심의 설계를 살펴보고 객체지향적으로 설계한 구조와 어떤 차이점이 있는지 살펴본다. 상태 중심의 설계를 살펴보면 훌륭한 객체지향 설계의 다양한 특징과 훌륭한 설계를 달성하기 위해 이용할 수 있는 책임 할당 원칙을 좀 더 쉽게 이해할 수 있다.

*좋은 글을 쓰기 위해선 나쁜 글을 읽어봐야 한다.*

### 데이터 중심의 영화 예매 시스템

객체지향 설계에서는 두 가지 방법을 이용해 시스템을 객체로 분할할 수 있다. 첫 번째 방법은 상태를 분할의 중심축으로 삼는 방법이고, 두 번째 방법은 책임을 중심축으로 삼는 방법이다.

데이터 중심의 관점에서는 객체는 자신이 포함하고 있는 데이터를 조작하는 데 필요한 오퍼레이션을 정의한다. **책임 중심의 관점에서는 객체는 다른 객체가 요청할 수 있는 오퍼레이션을 위해 필요한 상태를 보관한다.** 데이터 중심의 관점은 객체의 상태에 초점을 맞추고 책임 중심의 관점은 객체의 행동에 초점을 맞춘다. 전자는 객체를 독립된 데이터 덩어리로 바라보고 후자는 객체를 협력하는 공동체의 일원으로 바라본다.

**시스템을 분할하기 위해서는 데이터가 아니라 책임에 초점을 맞춰야 한다.**

객체의 상태는 구현에 속한다. 구현은 불안정하기 때문에 변하기 쉽다. 상태를 객체 분할의 중심축으로 삼으면 구현에 관한 세부사항이 객체의 인터페이스로 스며들게 되어 캡슐화의 원칙이 무너진다. 결과적으로 상태 변경은 인터페이스의 변경을 초래하며 이 인터페이스에 의존하는 모든 객체에게 변경의 영향을 미치게 된다. 따라서 데이터에 초점을 맞추는 설계는 취약하다.

그에 비해 객체의 책임은 인터페이스에 속한다. 객체는 책임을 드러내는 안정적인 인터페이스 뒤로 책임을 수행하는 데 필요한 상태를 캡슐화함으로써 구현 변경에 대한 파장이 외부로 퍼져나가는 것을 방지한다. 따라서 책임에 초점을 맞추면 상대적으로 변경에 안정적인 설계를 얻을 수 있게 된다.

#### 데이터를 준비하자

데이터 중심의 설계란 객체 내부에 저장되는 데이터를 기반으로 시스템을 분할하는 방법이다. 책임 중심의 설계가 '책임이 무엇인가'를 묻는 것으로 시작한다면 데이터 중심의 설계는 객체 내부에 저장해야 하는 '데이터가 무엇인가'를 묻는 것으로 시작한다.

*자바의 예제를 C#의 예제로 변환하면 접근자와 수정자는 사실 프로퍼티로 대체 가능하지만 부정적인 측면을 강조하기 위해 컨벤션만 옮긴다.*

```csharp
public class Movie
{
  private string title;
  private Duration runningTime;
  private Money fee;
  private List<DiscountCondition> discountConditions;

  private MovieType movieType;
  private Money discountAmount;
  private double discountPercent;
}
```

데이터 중심의 `Movie`클래스 역시 책임 중심의 `Movie`클래스와 마찬가지로 영화를 표현하는 가장 기본적인 정보인 영화 제목, 상영시간, 기본 요금을 인스턴스 변수로 저장한다. 또한 할인 조건의 목록, 할인 금액, 할인 비율, 할인 정책을 저장하는 인스턴스 변수도 추가했다.

할인 정책은 영화별로 오직 하나만 지정할 수 있기 때문에 한 시점에 하나의 값만 사용될 수 있다. 그렇다면 영화에 사용된 할인 정책의 종류를 어떻게 알 수 있을까? 할인 정책의 종류를 결정하는 것이 바로 `MovieType`이다.

```csharp
public enum MovieType
{
  AMOUNT_DISCOUNT,
  PERCENT_DISCOUNT,
  NONE_DISCOUNT
}
```

이것은 말 그대로 데이터 중심의 접근 방법이다. 데이터 중심의 설계에서는 객체가 포함해야 하는 데이터에 집중한다.

이후 데이터 준비가 끝났다면 캡슐화의 원칙을 지키기 위해 접근자와 수정자를 추가한다.

```csharp
public class Movie
{
  private string title;
  private Duration runningTime;
  private Money fee;
  private List<DiscountCondition> discountConditions;

  private MovieType movieType;
  private Money discountAmount;
  private double discountPercent;

  public MovieType getMovieType()
  {
    return movieType;
  }

  public void setMovieType(MovieType movieType)
  {
    this.movieType = movieType;
  }

  public Money getDiscountAmount()
  {
    return discountAmount;
  }

  public void setDiscountAmount(Money discountAmount)
  {
    this.discountAmount = discountAmount;
  }

  public double getDiscountPercent()
  {
    return discountPercent;
  }

  public void setDiscountPercent(double discountPercent)
  {
    this.discountPercent = discountPercent;
  }
}
```

이제는 부터 할인 조건을 구현해본다. 데이터 중심의 설계 방법을 따르기 때문에 할인 조건을 설계하기 위해 데이터 타입을 먼저 만든다.

```csharp
public enum DiscountConditionType
{
  SEQUENCE,
  PERIOD
}
```

할인 조건을 구현하는 `DiscountCondition`은 할인 조건의 타입을 저장할 인스턴스 변수인 type을 포함한다. 또한`movieType`의 경우와 마찬가지로 순번 조건에서만 사용되는 데이터인 상영 순번과 기간 조건에서만 사용되는 데이터인 요일, 시작 시간, 종료시간을 포함한다.

```csharp
public class DiscountCondition
{
  private DiscountConditionType type;
  private int sequence;
  private DayOfWeek dayOfWeek;
  private LocalTime startTime;
  private LocalTime endTime;
}
```

마찬가지로 캡슐화에 맞게 접근자와 수정자를 추가한다.

```csharp
public class DiscountCondition
{
  private DiscountConditionType type;
  private int sequence;
  private DayOfWeek dayOfWeek;
  private LocalTime startTime;
  private LocalTime endTime;

  public DiscountConditionType getType()
  {
    return type;
  }

  public void setType(DiscountConditionType type)
  {
    this.type = type;
  }

  public int getSequence()
  {
    return sequence;
  }

  public void setSequence(int sequence)
  {
    this.sequence = sequence;
  }

  public DayOfWeek getDayOfWeek()
  {
    return dayOfWeek;
  }

  public void setDayOfWeek(DayOfWeek dayOfWeek)
  {
    this.dayOfWeek = dayOfWeek;
  }

  public LocalTime getStartTime()
  {
    return startTime;
  }

  public void setStartTime(LocalTime startTime)
  {
    this.startTime = startTime;
  }

  public LocalTime getEndTime()
  {
    return endTime;
  }

  public void setEndTime(LocalTime endTime)
  {
    this.endTime = endTime;
  }
}
```

이어서 `Screening` 클래스를 구현한다. 동일하게 어떤 데이터를 포함해야 하는지 결정하고 데이터를 캡슐화하기 위해 메서드를 추가한다.

```csharp
public class Screening
{
  private Movie movie;
  private int sequence;
  private LocalDateTime whenScreened;
  
  public Movie getMovie()
  {
    return movie;
  }

  public void setMovie(Movie movie)
  {
    this.movie = movie;
  }

  public int getSequence()
  {
    return sequence;
  }

  public void setSequence(int sequence)
  {
    this.sequence = sequence;
  }

  public LocalDateTime getWhenScreened()
  {
    return whenScreened;
  }

  public void setWhenScreened(LocalDateTime whenScreened)
  {
    this.whenScreened = whenScreened;
  }
}
```

이번엔 영화 예매를 위해 `Reservation` 클래스를 구현한다.

```csharp
public class Reservation
{
  private Customer customer;
  private Screening screening;
  private Money fee;
  private int audienceCount;

  public Customer getCustomer()
  {
    return customer;
  }

  public void setCustomer(Customer customer)
  {
    this.customer = customer;
  }

  public Screening getScreening()
  {
    return screening;
  }

  public void setScreening(Screening screening)
  {
    this.screening = screening;
  }

  public Money getFee()
  {
    return fee;
  }

  public void setFee(Money fee)
  {
    this.fee = fee;
  }

  public int getAudienceCount()
  {
    return audienceCount;
  }

  public void setAudienceCount(int audienceCount)
  {
    this.audienceCount = audienceCount;
  }
}
```

마지막으로 고객의 정보를 담는 `Customer` 클래스를 구현한다.

```csharp
public class Customer
{
  private String name;
  private String id;

  public Customer(String name, String id)
  {
    this.name = name;
    this.id = id;
  }
}
```

#### 영화를 예매하자

`ReservationAgency` 클래스를 구현한다. 이 클래스는 데이터 클래스를 조합하여 영화 예매 절차를 구현하는 클래스이다.

```csharp
public class ReservationAgency
{
  public Reservation Reserve(Screening screening, Customer customer, int audienceCount)
  {
    Movie movie = screening.getMovie();
    
    boolean discountable = false;
    foreach (DiscountCondition condition in movie.getDiscountConditions())
    {
      if (condition.getType() == DiscountConditionType.PERIOD)
      {
        discountable = screening.getWhenScreened().getDayOfWeek().equals(condition.getDayOfWeek()) &&
          condition.getStartTime().compareTo(screening.getWhenScreened().toLocalTime()) <= 0 &&
          condition.getEndTime().compareTo(screening.getWhenScreened().toLocalTime()) >= 0;
      }
      else
      {
        discountable = condition.getSequence() == screening.getSequence();
      }
      if (discountable)
      {
        break;
      }
    }

    Money fee;
    if (discountable)
    {
      Money discountAmount = Money.ZERO;
      switch (movie.getMovieType())
      {
        case AMOUNT_DISCOUNT:
          discountAmount = movie.getDiscountAmount();
          break;
        case PERCENT_DISCOUNT:
          discountAmount = movie.getFee().times(movie.getDiscountPercent());
          break;
        case NONE_DISCOUNT:
          discountAmount = Money.ZERO;
          break;
      }
      fee = movie.getFee().minus(discountAmount).times(audienceCount);
    }
    else
    {
      fee = movie.getFee();
    }

    return new Reservation(customer, screening, fee, audienceCount);
  }
}
```

`Reserve`메서드는 크게 두 부분으로 나눠서 생각이 가능하다. 첫 번째로 `DiscountCondition`을 이용해 할인 가능 여부를 판단하고, 두 번째로 할인된 요금을 계산한다.

이제 이 두가지 방법에 대한 장단점을 파악해보자

### 설계 트레이드오프

객체지향 커뮤니티에서는 오랜 기간 동안 좋은 설계의 특징을 판단할 수 있는 기준에 관한 다양한 논의가 있어 왔다. 여기서는 데이터 중심 설계와 책임 중심 설계의 장단점을 비교하기 위해 **캡슐화**, **응집도**, **결합도**를 사용한다.

#### 캡슐화

상태와 행동을 하나의 객체 안에 모으는 이유는 객체의 내부 구현을 외부로부터 감추기 위해서다. 여기서 구현이란 나중에 변경될 가능성이 높은 어떤 것을 가리킨다. 객체지향이 강력한 이유는 한 곳에서 일어난 변경이 전체 시스템에 영향을 끼치지 않도록 파급효과를 적절하게 조절할 수 있는 장치를 제공하기 때문이다. **객체를 사용하면 변경 가능성이 높은 부분은 내부에 숨기고 외부에는 상대적인 부분만 공개함으로써 변경의 여파를 통제할 수 있다.**

변경될 가능성이 높은 부분을 **구현**이라고 부르고 상대적으로 안정적인 부분을 **인터페이스**라고 부른다는 사실을 기억하라. 객체를 설계하기 위한 가장 기본적인 아이디어는 변경의 정도에 따라 구현과 인터페이스를 분리하고 외부에서는 인터페이스에만 의존하도록 관계를 조절하는 것이다.

지금까지 설명한 내용에서 알 수 있는 것처럼 객체지향에서 가장 중요한 원리는 캡슐화다. 캡슐화는 외부에서 알 필요가 없는 부분을 감춤으로써 대상을 단순화하는 추상화의 한 종류다. 객체지향 설계의 가장 중요한 원리는 불안정한 구현 세부사항을 안정적인 인터페이스 뒤로 캡슐화하는 것이다.

> 복잡성을 다루기 위한 가장 효과적인 도구는 추상화다. 다양한 추상화 유형을 사용할 수 있지만 객체지향 프로그래밍에서 복잡성을 취급하는 주요한 추상화 방법은 캡슐화다. 그러나 프로그래밍할 때 객체지향 언어를 사용한다고 해서 애플리케이션의 복잡성이 잘 캡슐화될 것이라고 보장할 수는 없다. 훌륭한 프로그래밍 기술을 적용해서 캡슐화를 향상시킬 수 있겠지만 객체지향 프로그래밍을 통해 전반적으로 얻을 수 있는 장점은 오직 설계 과정 동안 캡슐화를 목표로 인식할 때만 달성될 수 있다.

**설계가 필요한 이유는 요구사항이 변경되기 때문이고, 캡슐화가 중요한 이유는 불안정한 부분과 안정적인 부분을 분리해서 변경의 영향을 통제할 수 있기 때문이다.** 따라서 변경의 관점에서 설계의 품질을 판단하기 위해 캡슐화를 기준으로 삼을 수 있다.

정리하자면 캡슐화란, 변경 가능성이 높은 부분을 객체 내부로 숨기는 추상화 기법이다. 객체 내부에 무엇을 캡슐화해야 하는가? 변경될 수 있는 어떤 것이라도 캡슐화해야 한다. 이것이 바로 객체지향 설계의 핵심이다.

> 유지보수성이 목표다. 여기서 유지보수성이란 두려움 없이, 주저함 없이 저항감 없이 코드를 변경할 수 있는 능력을 말한다. 가장 중요한 동료는 캡슐화다. 캡슐화란 어떤 것을 숨긴다는 것을 의미한다. 우리는 시스템의 한 부분을 다른 부분으로부터 감춤으로써 뜻밖의 피해가 발생할 수 있는 가능성을 사전에 방지할 수 있다. 만약 시스템이 완전히 캡슐화가 된다면 우리는 변경으로부터 자유로워질 것이다. 만약 시스템의 캡슐화가 크게 부족하다면 우리는 변경으로부터 자유로워질 수 없고, 결과적으로 시스템은 진화할 수 없을 것이다. 응집도, 결합도, 중복 역시 흘룽한 코드를 규정하는 데 핵심적인 품질인 것이 사실이지만 캡슐화는 우리 좋은 코드로 안내하기 때문에 가장 중요한 1원리다.

#### 응집도와 결합도

응집도와 결합도는 구조적인 설계 방법이 주도하던 시대에 소프트웨어 품질을 측정하기 위해 소개된 기준이지만 객체지향의 시대에서도 여전히 유효하다.

**응집도**는 모듈에 포함된 내부 요소들이 연관돼 있는 정도를 나타낸다. 모듈 내의 요소들이 하나의 목적을 위해 긴밀하게 협력한다면 그 모듈은 높은 응집도를 가진다. 모듈 내의 요소들이 서로 다른 목적을 추구한다면 그 모듈은 낮은 응집도를 가진다. **객체지향의 관점에서 응집도는 객체 또는 클래스에 얼마나 관련 높은 책임들을 할당했는지 나타낸다.**

**결합도**는 의존성의 정도를 나타내며 다른 모듈에 대해 얼마나 많은 지식을 갖고 있는지를 나타내는 척도다. 어떤 모둘이 다른 모듈에 대해서 너무 자세한 부분까지 알고 있다면 두 모듈은 높은 결합도를 가진다. 어떤 모듈이 다른 모듈에 대해 꼭 필요한 지식만 알고 있다면 두 모듈은 낮은 결합도를 가진다. **객체지향의 관점에서 결합도는 객체 또는 클래스가 협력에 필요한 적절한 수준의 관계만 유지하고 있는지를 나타낸다.**

응집도와 결합도의 의미를 이해하기 위한 첫 걸음은 두 개념 모두 설계와 관련 있다는 사실을 이해하는 것이다. 일반적으로 좋은 설계란 높은 응집도와 낮은 결합도를 가진 모듈로 구성된 설계를 의미한다. 다시 말해 애플리케이션을 구성하는 요소의 응집도가 높고 서로 느슨하게 결합되어 있다면 그 애플리케이션은 좋은 설계를 가졌음을 의미한다.

여기서 좋은 설계란, 오늘의 기능을 수행하면서 내일의 변경을 수용할 수 있는 설계다. 그리고 좋은 설계를 만들기 위해서는 높은 응집도와 낮은 결합도를 추구해야 한다.

높은 응집도와 낮은 결합도를 가진 설계를 추구해야 하는 이유는 단 한 가지다. 그것이 설계를 변경하기 쉽게 만들기 때문이다. 변경의 관점에서 응집도란 **변경이 발생할 때 모듈 내부에서 발생하는 변경의 정도**로 측정할 수 있다. 간단하게 하나의 변경을 수용하기 위해 모듈 전체가 함께 변경된다면 응집도가 높은 것이고 모듈의 일부만 변경된다면 응집도가 낮은 것이다.

*이에 대해서 데이터 중심과 책임 중심의 설계를 대입하여 생각해보면 좋다.*

응집도가 높을수록 변경의 대상과 범위가 명확해지기 때문에 코드를 변경하기 쉬워진다. 변경으로 인해 수정되는 부분을 파악하기 위해 코드 구석구석을 헤매고 다니거나 여러 모듈을 동시에 수정할 필요가 없으며 변경을 위해 오직 하나의 모듈만 수정하면 된다.

결합도 역시 변경의 관점에서 설명할 수 있다. 결합도는 한 모듈이 변경되기 위해서 다른 모듈의 변경을 요구하는 정도로 측정할 수 있다. 다시 말해 하나의 모듈을 수정할 때 얼마나 많은 모듈을 함께 수정해야 하는지를 나타낸다. 따라서 결합도가 높으면 높을수록 함께 변경해야 하는 모듈의 수가 늘어나기 때문에 변경하기가 어려워진다.

영향을 받는 모듈의 수 외에도 변경의 원인을 이용해 결합도의 개념을 설명할 수도 있다. 내부 구현을 변경했을 때 이것이 다른 모듈에 영향을 미치는 경우에는 두 모듈 사이의 결합도가 높다고 표현한다. 반면 퍼플릭 인터페이스를 수정했을 때만 다른 모듈에 영향을 미치는 경우에는 결합도가 낮다고 표현한다.

**따라서 클래스의 구현이 아닌 인터페이스에 의존하도록 코드를 작성해야 낮은 결합도를 얻을 수 있다. 이것은 "인터페이스에 대해 프로그래밍하라"라는 격언으로도 잘 알려져 있다.**

결합도가 높아도 상관 없는 경우도 있다. 일반적으로 변경될 확률이 매우 적은 안정적인 모듈에 의존하는 것은 아무런 문제도 되지 않는다. 표준 라이브러리에 포함된 모듈이나 성숙 단계에 접어든 프레임워크에 의존하는 경우가 여기에 속한다. (자바의 String같은 경우)

그러나 직접 작성한 코드의 경우에는 이야기가 다르다. 그런 코드는 항상 불안정하며 언제라도 변경될 가능성이 높다. 코드 안에 버그가 존재할 수 있고 갑자기 요구사항이 변경될 수도 있다. 코드를 완성한 그 순간부터 코드를 수정할 준비를 해야 한다. 따라서 직접 작성한 코드의 경우에는 낮은 결합도를 유지하려고 노력해야 한다.

강조하지만 응집도와 결합도는 변경과 관련이 깊다. 어떤 설계를 쉽게 변경할 수 있다면 높은 응집도를 가진 요소들로 구성돼 있고 요소들 사이의 결합도가 낮을 확률이 높다. 만약 코드가 변경에 강하게 저항하고 있다면 구성 요소들의 응집도가 낮고 요소들이 강하게 결합돼 있을 확률이 높다.

마지막으로 결합도의 정도가 응집도와 결합도에 영향을 미친다는 사실을 알아야 한다. 캡슐화를 지키면 모듈 안의 응집도는 높아지고 모듈 사이의 결합도는 낮아진다. 즉, 캡슐화를 향상시키기 위해 노력하라.

### 데이터 중심의 영화 예매 시스템의 문제점

**기능적인 측면에서만 데이터 중심과 책임 중심의 설계는 완전히 동일하다.** (동작하며, 같은 기능을 함) 근본적인 차이점은 캡슐화를 다루는 방식이다. 데이터 중심의 설계는 캡슐화를 위반하고 객체의 내부 구현을 인터페이스의 일부로 만든다. 반면 **책임 중심의 설계는 객체의 내부 구현을 안정적인 인터페이스 뒤로 캡슐화한다.**

정리하자면 데이터 중심의 설계가 가진 대표적인 문제점은 다음과 같다.

- 캡슐화 위반
- 높은 결합도
- 낮은 응집도

#### 캡슐화 위반

데이터 중심으로 설계한 `Movie`클래스를 보면 오직 메서드를 통해서만 객체의 냐부 상태에 접근할 수 있다는 것을 알 수 있다. 과연 이게 캡슐화를 잘 준수한 것일까?

```csharp
public class Movie
{
  private Money fee;

  public Money getFee()
  {
    return fee;
  }

  public void setFee(Money fee)
  {
    this.fee = fee;
  }
}
```

안타깝게도 접근자와 수정자 메서드는 객체 내부의 상태에 대한 어떤 정보도 캡슐화하지 못한다. `GetFee`메서드와 `SetFee`메서드는 `Movie`내부에 `Money`타입의 `fee`라는 인스턴스 변수가 존재한다는 사실을 퍼블릭 인터페이스에 노골적으로 노출한다.

`Movie`가 캡슐화의 원칙을 어기게 된 근본적인 원인은 객체가 수행할 책임이 아니라 내부에 저장할 데이터에 초점을 맞췄기 때문이다. **객체에게 중요한 것은 책임이다. 그리고 구현을 캡슐화할 수 있는 적절한 책임은 협력이라는 문맥을 고려할 때만 얻을 수 있다.**

설계할 때 협력에 관해 고민하지 않으면 캡슐화를 위반하는 과도한 접근자와 수정자를 가지게 되는 경향이 있다. 객체가 사용될 문맥을 추측할 수밖에 없는 경우 개발자는 어떤 상황에서도 해당 객체가 사용될 수 있게 최대한 많은 접근자 메서드를 추가하게 되는 것이다. (일종의 오용, 추측에 의한 설계 전략)

#### 높은 결합도

데이터 중심의 설계는 접근자와 수정자를 통해 내부 구현을 인터페이스의 일부로 만들기 때문에 캡슐화를 위반한다. 객체 내부의 구현이 객체의 인터페이스에 드러난다는 것은 클라이언트가 구현에 강하게 결합된다는 것을 의미한다. 그리고 단지 객체의 내부 구현을 변경했음에도 이 인터페이스에 의존하는 모든 클라이언트들도 함께 변경해야 한다는 것이다.

`ReservationAgency`코드의 일부분 중 한 명의 예매 요금을 계산하기 위해 `Movie`의 `getFee`메서드를 호출하며 계산된 결과를 `Money`타입의 `fee`변수에 저장한다. 이때 `fee`의 타입을 변경한다고 가정한다면 이를 위해서 `getFee` 메서드의 반환 타입도 함께 수정해야 할 것이다. 그리고 `getFee`메서드를 호출하는 모든 클라이언트도 함께 수정해야 한다.

이처럼 데이터 중심의 설계는 객체의 캡슐화를 약화시키기 때문에 클라이언트가 객체의 구현에 강하게 결합된다.

결합도 측면에서 데이터 중심의 설계가 가지는 또 다른 단점은 여러 데이터 객체들을 사용하는 제어 로직이 특정 객체 안에 집중되기 때문에 하나의 제어 객체가 다수의 데이터 객체에 강하게 결합된다는 것이다. 이 결합도로 인해 어떤 데이터 객체를 변경하더라도 제어 객체를 함께 변경할 수밖에 없다.

#### 낮은 응집도

서로 다른 이유로 변경되는 코드가 하나의 모듈 안에 공존할 때 모듈의 응집도가 낮다고 말한다. 따라서 각 모듈의 응집도를 살펴보기 위해서는 코드를 수정하는 이유가 무엇인지 살펴봐야 한다.

`ReservationAgency`를 예로 들어 변경과 응집도 사이의 관계를 살펴보자. 다음과 같은 수정사항이 발생하는 경우에 `ReservationAgency`의 코드를 수정해야 한다.

- 할인 정책이 추가될 경우
- 할인 정책별로 할인 요금을 계산하는 방법이 변경될 경우
- 할인 조건이 추가되는 경우
- 할인 조건별로 할인 여부를 판단하는 방법이 변경될 경우
- 예매 요금을 계산하는 방법이 변경될 경우

낮은 응집도는 두 가지 측면에서 설계에 문제를 일으킨다.

- 변경의 이유가 서로 다른 코드들을 하나의 모듈 안에 뭉쳐놓았기 때문에 변경과 아무 상관이 없는 코드들이 영향을 받게 된다. **어떤 코드를 수정한 후에 아무런 상관도 없던 코드에 문제가 발생하는 것은 모듈의 응집도가 낮을 때 발생하는 대표적인 증상이다.**
- **하나의 요구사항 변경을 반영하기 위해 동시에 여러 모듈을 수정해야 한다.** 응집도가 낮을 경우 다른 모듈에 위치해야 할 책임의 일부가 엉뚱한 곳에 위치하게 되기 때문이다.

현재의 설계는 새로운 할인 정책을 추가하거나 새로운 할인 조건을 추가하기 위해 하나 이상의 클래스를 동시에 수정해야 한다.

### 자율적인 객체를 향해

#### 캡슐화를 지켜라

캡슐화는 설계의 제 1원리다. 게이터 중심의 설계가 낮은 응집도와 높은 결합도라는 문제로 몸살을 앓게 된 근본적인 원인은 바로 캡슐화의 원칙을 위반했기 때문이다. 객체는 자신이 어떤 데이터를 가지고 있는지를 내부에 캡슐화하고 외부에 공개해서는 안된다. 객체는 스스로 상태를 책임져야 하며 외부에서는 인터페이스에 정의된 메서드를 통해서만 상태에 접근할 수 있어야 한다.

여기서 말하는 메서드란 단순히 속성 하나의 값을 반환하거나 변경하는 접근자나 수정자를 의미하는 것은 아니다. 객체에게 의미 있는 메서드는 객체가 책임져야 하는 무언가를 수행하는 메서드다. 속성의 가시성을 private으로 설정했다고 해도 접근자와 수정자를 통해 속성을 외부로 공개하고 있다면 캡슐화를 위반하는 것이다.

#### 스스로 자신의 데이터를 책임지는 객체

**우리가 상태와 행동을 객체라는 하나의 단위로 묶는 이유는 객체 스스로 자신의 상태를 처리할 수 있게 하기 위해서다.** 객체는 단순한 데이터 제공자가 아니다. 객체 내부에 저장되는 데이터보다 객체가 협력에 참여하면서 수행할 책임을 정의하는 오퍼레이션이 더 중요하다.

따라서 객체를 설계할 때 "이 객체가 어떤 데이터를 포함해야 하는가?"라는 질문은 다음과 같은 두 개의 개별적인 질문으로 분리해야 한다.

- 이 객체가 어떤 데이터를 포함해야 하는가?
- 이 객체가 데이터에 대해 수행해야 하는 오퍼레이션은 무엇인가?

두 질문을 조합하면 객체의 내부 상태를 저장하는 방식과 저장된 상태에 대해 호출할 수 있는 오퍼레이션의 집합을 얻을 수 있다. 다시 말해 **새로운 데이터 타입을 만들 수 있다는 것**이다.

*대부분의 사람들이 이 레벨에서 코드를 작성하는것 같다.*

### 하지만 여전히 부족하다

분명히 캡슐화 관점에서 두 번째 설계가 첫 번째 설계보다 향상된 것은 사실이지만 그렇다고 만족스러울 정도는 아니다. 두 번째 역시 데이터 중심의 설계 방식에 속한다.

#### 캡슐화 위반

분명히 수정된 객체들은 자기 자신의 데이터를 스스로 처리한다. 예를 들어 `DiscountCondition`은 자기 자신의 데이터를 이용해 할인 가능 여부를 스스로 판단한다.

```csharp
public class DiscountCondition
{
  private DiscountConditionType type;
  private int sequence;
  private DayOfWeek dayOfWeek;
  private LocalTime startTime;
  private LocalTime endTime;

  public DiscountConditionType GetType() {...}
  public boolean IsDiscountable(DayOfWeek dayOfWeek, LocalTime time) {...}
  public boolean IsDiscountable(int sequence) {...}
}
```

객체지향이 자신의 상태를 스스로 관리하는 자율적인 객체를 지향하는 것이라고 한다면 분명 지금의 설계는 객체지향의 취지에 맞는 것처럼 보일 것이다. 하지만 `DiscountCondition`에 구현된 두 개의 `IsDiscountable`메서드를 자세히 살펴보면 이상한 점이 몇 군데 눈에 띈다.

- 기간 조건을 판단하는 `IsDiscountable(DayOfWeek dayOfWeek, LocalTime time)`메서드의 시그니처를 자세히 살펴보면 `DiscountCondition`에 속성으로 포함돼 있는 `DayOfWee`타입의 요일 정보와 `LocalTime`타입의 시간 정보가 인스턴스 변수로 포함돼 있다는 사실을 인터페이스를 통해 외부에 노출하고 있는 것이다.
- 두번 째 역시 `sequence`를 통해 외부에 노출한다.

만약 해당 클래스의 속성을 변경해야 한다면 두 메서드의 시그니처도 수정하게 되고 해당 메서드를 사용하는 모든 클라이언트도 수정되어야 할 것이다. 내부 구현의 변경이 외부로 퍼져나가는 **파급 효과(ripple effect)**는 캡슐화가 부족하다는 증거다. 따라서 변경 후의 설계는 자기 스스로 처리한다는 점에서는 개선됐지만 여전히 캡슐화를 위반하고 있다.

캡슐화에서 내부 속성을 외부로부터 감추는 것은 `데이터 캡슐화`라고 불리는 캡슐화의 한 종류일 뿐이다. **캡슐화란 변할 수 있는 어떤 것이라도 감추는 것이다. 그것이 속성의 타입이건, 할인 정책의 종류건 상관 없이 내부 구현의 변경으로 인해 외부의 객체가 영향을 받는다면 캡슐화를 위반한 것이다. 설계에서 변하는 것이 무엇인지 고려하고 변하는 개념을 캡슐화해야 한다. 이것이 캡슐화라는 용어를 통해 말하고자 하는 진정한 의미다.**

#### 높은 결합도

캡슐화 위반으로 인해 `DiscountCondition`의 내부 구현이 외부로 노출됐기 때문에 `Movie`와 `DiscountCodition` 사이의 결합도는 높을 수밖에 없다. 두 객체 사이의 결합도가 높을 경우 한 객체의 구현을 변경할때 다른 객체에게 변경의 영향이 전파될 확률이 높아진다는 사실을 기억하자.

`Movie`의 `isDiscountable`메서드는 `DiscountCondition`의 목록을 순회하면서 할인 조건의 종류에 따라 `DiscountCondition`에 구현된 두 개의 `isDiscountable` 메서드 중에서 적절한 것을 호출한다. 이 과정에서 현재는 분기문으로 처리하기 때문에 매번 수정이 필요하다.

정리하자면 모든 원인은 캡슐화를 지키지 않았기 때문으로 유연한 설계를 위해 캡슐화를 첫 번째 목표로 삼아야 한다.

#### 낮은 응집도

이번에는 `Screening`을 살펴보자. 앞에서 설명한 것처럼 `DiscountCondition`이 할인 여부를 판단하는 데 필요한 정보가 변경된다면 `Movie`의 `isDiscountable`메서드로 전달해야 하는 파라미터의 종류를 변경해야 하고, 이로 인해 `Screening`에서 `Movie`의 `isDiscountable`메서드를 호출하는 코드도 함께 변경해야 한다.

### 데이터 중심 설계의 문제점

두 번째 설계가 변경에 유연하지 못한 이유는 캡슐화를 위반했기 때문이다. 캡슐화를 위반한 설계를 구성하는 요소들이 높은 응집도와 낮은 결합도를 가질 확률은 극히 낮다. 따라서 캡슐화를 위반한 설계는 변경에 취약할 수밖에 없다.

- 데이터 중심의 설계는 본질적으로 너무 이른 시기에 데이터에 관해 결정하도록 강요한다.
- 데이터 중심의 설계에서는 협력이라는 문맥을 고려하지 않고 객체를 고립시킨 채 오퍼레이션을 결정한다.

#### 데이터 중심 설계는 객체의 행동보다는 상태에 초점을 맞춘다

데이터 중심의 설계를 시작할 때 던졌던 첫 질문은 "이 객체가 포함해야 하는 데이터가 무엇인가?"다. **데이터는 구현의 일부라는사실을 명심해야 한다.**

데이터 중심 설계 방식에 익숙한 개발자들은 일반적으로 데이타와 기능을 분리하는 절차적 프로그래밍 방식을 따른다. 이것은 상태와 행동을 하나의 단위로 캡슐화하는 객체지향 패러다임에 반하는 것이다. 데이터 중심의 관점에서 객체는 단순 데이터의 집합체일 뿐이다. 이로 인해 접근자와 수정자를 과도하게 추가하게 되고 이 데이터 객체를 사용하는 절차를 분리된 별도의 객체 안에 구현하게 된다. (앞에서 설명한 캡슐화의 위반)

비록 데이터를 처리하는 작업과 데이터를 같은 객체 안에 두더라도 데이터에 초점이 맞춰져 있다면 만족스러운 캡슐화를 얻기 어렵다. 데이터를 먼저 결정하고 데이터를 처리하는 데 필요한 오퍼레이션을 나중에 결정하는 방식은 데이터에 관한 지식이 객체의 인터페이스에 고스란히 드러나게 된다. 결과적으로 객체의 인터페이스는 구현을 캡슐화하는 데 실패하고 코드는 변경에 취약해진다. 이것이 두 번째 설계가 실패한 이유다.

결론적으로 데이터 중심의 설계는 너무 이른 시기에 데이터에 대해 고민하기 때문에 캡슐화에 실패하게 된다. 객체의 내부 구현이 객체의 인터페이스를 어지럽히고 객체의 응집도와 결합도에 나쁜 영향을 미치기 때문에 변경에 취약한 코드를 낳게 된다.

#### 데이터 중심 설계는 객체를 고립시킨 채 오퍼레이션을 정의하도록 만든다

객체지향 애플리케이션을 구현한다는 것은 협력하는 객체들의 공동체를 구축한다는 것을 의미한다. 따라서 협력이라는 문맥 안에서 필요한 책임을 결정하고 이를 수행할 적절한 객체를 결정하는 것이 가장 중요하다. **올바른 객체지향 설계의 무게 중심은 항상 객체의 내부가 아니라 외부에 맞춰져 있어야 한다.** 객체가 내부에 어떤 상태를 가지고 그 상태를 어떻게 관리하는가는 부가적인 문제다. 중요한 것은 객체가 다른 객체와 협력하는 방법이다.

안탑깝게도 데이터 중심 설계에서 초점은 객체의 외부가 아니라 내부로 향한다. 실행 문맥에 대한 깊이 있는 고민 없이 객체가 관리할 데이터의 세부 정보를 먼저 결정한다. 객체의 구현이 이미 결정된 상태에서 다른 객체와의 협력 방법을 고민하기 때문에 이미 구현된 객체의 인터페이스를 억지로 끼워맞출수밖에 없다.

두 번째 설계가 변경에 유연하게 대처하지 못했던 이유가 바로 이 때문이다. 객체의 인터페이스에 구현이 노출돼 있었기 때문에 협력이 구현 세부사항에 족속돼 있고 그에 따라 객체의 내부 구현이 변경됐을 때 협력하는 객체 모두가 영향을 받을 수밖에 없었던 것이다.

### 느낀점

확실히 데이터 중심의 설계를 직접 따라해보면서 문제점을 인식하는 부분은 매우 좋았다. 실제 개발에서도 데이터 중심의 설계를 많이 보기도 하기도 했다. 그에 대한 문제점을 캡슐화를 통해서 잘 보여준 것 같다는 생각이다.

#### 논의사항

*늦게 올려서 패스합니다.*
