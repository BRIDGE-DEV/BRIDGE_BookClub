## 1장 객체, 설계

> 이론이 먼저일까, 실무가 먼저일까?

다른 공학 분야에 비해 역사가 짧은 소프트웨어 분야는 아직은 걸음마 단계이기에 이론보다 실무가 더 앞서 있으며 실무가 더 중요하다는 점이다.

*어떤 분야든 초기 단계에서는 아무것도 없는 상태에서 이론을 정립하기보다는 실무를 관찰한 결과를 바탕으로 이론을 정립하는 것이 최선이다.*

소프트웨어 개발에서 실무가 이론보다 앞서 있는 대표적인 분야는 `소프트웨어 설계`와 `소프트웨어 유지보수`를 들 수 있다. (소프트웨어 공학) 이론은 실무에서 반복적으로 적용되는 기법들을 이론화한 것이 대부분이며 규모가 커질수로 소프트웨어 설계 분야에서 이론이 실무를 추월할 가능성은 적다.

이 책은 훌륭한 객체지향 프로그램을 설계하고 유지보수하는 데 필요한 원칙과 기법을 설명하기 위해 쓰여진 책이다. 일반적으로 이런 종류의 책들은 객체지향의 역사를 장황하게 설명하거나 기억하기조차 버거운 용어와 난해한 개념들을 줄줄이 나열하는 것으로 시작하지만, 앞서 말한 설계 분야에서 실무는 이론을 압도하기에 개념과 용어가 아닌 **코드**가 핵심이다.

### 티켓 판매 애플리케이션 구현하기

*저자는 Java코드를 사용해지만, 이해를 위해 C#코드로 대체하여 표기한다.*

- 도메인 정리
  - 소극장을 운영중이며, 관람객은 티켓을 통해 입장할 수 있다.
  - 티켓은 이벤트로 발송한 초대장이나 티켓의 가격을 지불하고 얻을 수 있다.
  - 정리하면 초대장, 티켓, 가방(돈, 티켓, 초대장을 담는), 관람객, 티켓 부스, 티켓 판매원, 소극장으로 구성된다.

```cs
public class Invitation
{
    private LocalDateTime when;
    // C#은 LocalDateTime이 없어서 DateTime으로 대체
}
```

```cs
public class Ticket 
{
    public float Fee { get; }
}
```

```cs
public class Bag {
    private float amount;
    private Invitation invitation;
    private Ticket ticket;

    public Bag(float amount) : this(null, amount) { }

    public Bag(Invitation invitation, float amount) 
    {
        this.invitation = invitation;
        this.amount = amount;
    }

    public bool HasInvitation() => invitation is not null;
    public bool HasTicket() => ticket is not null;
    public void SetTicket(Ticket ticket) => this.ticket = ticket;
    public void PlusAmount(float amount) => this.amount += amount;
    public void MinusAmount(float amount) => this.amount -= amount;
}
```

```cs
public class Audience
{
    public readonly Bag Bag { get; }

    public Audience(Bag bag)
    {
        this.Bag = bag;
    }
}
```

```cs
public class TicketOffice
{
    private float amount;
    private List<Ticket> tickets = new();

    public TicketOffice(float amount, params Ticket[] tickets)
    {
        this.amount = amount;
        this.tickets.AddRange(tickets);
    }

    public Ticket GetTicket()
    {
        if (tickets.Count == 0) //throw가 적합하지만 예제를 위해 null을 반환
        {
            return null;
        }

        var ticket = tickets[0];
        tickets.RemoveAt(0);
        return ticket;
    }

    public void PlusAmount(float amount) => this.amount += amount;
    public void MinusAmount(float amount) => this.amount -= amount;
}
```

```cs
public class TicketSeller
{
    public readonly TicketOffice TicketOffice { get; }

    public TicketSeller(TicketOffice ticketOffice)
    {
        this.ticketOffice = ticketOffice;
    }
}
```

```cs
public class Theater
{
    private TicketSeller ticketSeller;

    public Theater(TicketSeller ticketSeller)
    {
        this.ticketSeller = ticketSeller;
    }

    public void Enter(Audience audience)
    {
        if (audience.Bag.HasInvitation())
        {
            Ticket ticket = ticketSeller.TicketOffice.GetTicket();
            audience.Bag.SetTicket(ticket);
        }
        else
        {
            Ticket ticket = ticketSeller.TicketOffice.GetTicket();
            audience.Bag.MinusAmount(ticket.Fee);
            ticketSeller.TicketOffice.PlusAmount(ticket.Fee);
            audience.Bag.SetTicket(ticket);
        }
    }
}
```

*사용한 코드 스타일에 관하여, 단순 예제의 풀이라 상관이 없지만 이를 왜곡해서 해석할까봐 적어둔다. 기본적인 컨벤션, 가독성은 그 팀에 맞춰서 작성하는 것이 좋다.*

*예를 들어 `is not`의 경우 9.0이후의 기능이라 많은 개발자가 익숙치 않을 수 있다. 이는 오히려 더 가독성을 떨어뜨리는 요소로 작용할 수 있다.*

*람다의 경우도 지금은 단순 geter,seter의 형태라 변경했지만, 작서당시에 변경 가능성이 크다고 한다면 사용하지 않고 두는 편이 더 올바를 것이다.*

*이러한 방식이 균형잡기에 중요한 부분으로 우리가 기술이 아닌 기예, 예술로 부르는 이유다.*

*vscode에서 디버깅 없이 작성한 코드라 실제에서 동작하지 않을 수 있다. 설계관점에서 실습이라 실행은 중요하지 않음.*

### 무엇이 문제인가

> 모든 소프트웨어 모듈에는 세 가지 목적이 있다. 첫 번째 목적은 실행 중에 제대로 동작하는 것이다. 두 번째 목적은 변경을 위해 존재하는 것이다. 마지막 목적은 코드를 읽는 사람과 의사소통하는 것이다.

앞에서 작성한 프로그램은 필요한 기능을 오류 없이 정확하게 수행하게 있다. (가정한다.) 따라서 1번의 조건은 만족하지만, 변경 용이성과 가독성의 목적은 달성하지 못했다.

*논외이지만, 위 코드는 할당 그리고 예외에 대한 처리가 없음으로 오류없이 정학하게 수행한다고 보기 어렵다. 하지만 앞에서 계속 강조했듯이 이 책은 이론에 관한 책이고 그것을 효과적으로 설명하기 위해 실습하는 것이지 본질은 결국 이론이다. 따라서 손으로 치는 것이 아닌 머리속으로 가정하며 따라간다.*

#### 예상을 빗나가는 코드

> 소극장은 관람객의 가방을 열어 그 안에 초대장이 들어 있는지 살펴보고 가방 안에 초대장이 들어 있으면 판매원은 매표소에 보관돼 있는 티켓을 관람객의 가방 안으로 옮긴다. 가방 안에 초대장이 들어 있지 않다면 관람객의 가방에서 티켓 금액만큼의 현금을 꺼내 매표소에 적립한 후에 매표소에 보관돼 있는 티켓을 관람객의 가방 안으로 옮긴다.

이 코드는 절차적이고 수동적이다. 객체끼리 협력하며 동작해야 하는 반면 소극장이 모든 일을 처리해버린다.

이해 가능한 코드란, 그 동작이 예상을 크게 벗어나지 않는 코드다. 하지만 이 코드는 예상을 벗어나고 현재의 상식과 다르기에 코드를 읽는 사람과 의사소통하지 못한다.

이 코드를 이해하기 위해서는 여러 가지 세부적인 내용들을 한꺼번에 기억하고 있어야 한다는 점이다. (STM의 개수 초과, 청크 실패) 따라서 이 코드는 하나의 클래스나 메서드에서 너무 많은 세부사항을 다루기 때문에 코드를 작성하는 사람뿐만 아니라 코드를 읽고 이해해야 하는 사람 모두에게 큰 부담을 준다.

하지만 가장 심각한 문제는 `Audience`와 `Theater`가 `TicketSeller`의 내부 구현에 너무 의존적이라는 것이다. 이는 `TicketSeller`의 내부 구현이 변경되면 `Audience`와 `Theater`도 함께 변경되어야 한다는 것을 의미한다. (SRP를 위반하고 있다.)

#### 변경에 취약한 코드

- 만약 관람객이 가방을 들고 있지 않다면?
- 현금이 아닌 신용카드로 결제수단이 변경된다면?
- 판매원이 매표소 밖에서 티켓을 판매해야 한다면?

위 내용들에 대한 해결책은 바로 **의존성**이다. 이 말은 어떤 객체가 변경될 때 그 객체에게 의존하는 다른 객체도 함께 변경될 수 있다는 사실이 내포돼 있다.

그렇다고 의존성을 완전히 없애는 것은 정답이 아니다. (트레이드 오프) 객체지향의 설계는 서로 의존하면서 협력하는 객체들의 공동체를 구축하는 것이다. 따라서 애플리케이션의 기능을 구현하는 데 최소한의 의존성만 유지하고 불필요한 의존성을 제거하는 것이다.

*다시한번 강조하지만, 은총알은 없다. 정답도 없다. 정답에 가까워질려고 노력만 할 뿐, 가장 좋은 방향은 단순하고 명확한 형태이다. 그리고 트레이드 오프이다. 그 상황에서 더 좋은 쪽을 선택할 뿐이다.*

객체 사이의 의존성이 과한 경우를 가리켜 결합도가 높다고 말한다. 반대로 객체들이 합리적인 수준으로 의존할 경우는 결합도가 낮다고 말한다. (좋은 객체지향을 말할 때 응집도가 높고 결합도가 낮다고 말한다.) 결합도는 의존성과 관련돼 있기 때문에 결합도 역시 변경과 관련이 있다. 두 객체 사이의 결합도가 높으면 높을수록 함께 변경될 확률도 높아지기에 변경하기 어려워진다.

### 설계 개선하기

위 코드가 의도를 정확하게 의사소통하지 못하기 때문에 문제라는 점을 인지했다. 따라서 소극장 객체가 관람객의 가방과 판매원의 매표소에 직접 접근하는 것이 아닌 관람객이 자율적으로 동작하고, 판매원이 자율적으로 동작하도록 변경해야 한다. 그래야 깊게 이어진 사슬이 끊어지고 연관관계가 캡슐화로 가려지며 다형성을 통한 유연한 설계가 가능해진다.

해결방법은 간단하게 세세한 부분까지 이어진 정보를 차단하고 각 객체가 적절한 책임, 역할을 수행하도록 만드는 것이다. 즉, 해당 객체가 알아야할 정보만 알도록 만드는 것이다.

#### 자율성을 높이자

```cs
class TicketSeller
{
    private TicketOffice ticketOffice;

    public TicketSeller(TicketOffice ticketOffice)
    {
        this.ticketOffice = ticketOffice;
    }

    public void SellTo(Audience audience)
    {
        if (audience.Bag.HasInvitation())
        {
            Ticket ticket = ticketOffice.GetTicket();
            audience.Bag.SetTicket(ticket);
        }
        else
        {
            Ticket ticket = ticketOffice.GetTicket();
            audience.Bag.MinusAmount(ticket.Fee);
            ticketOffice.PlusAmount(ticket.Fee);
            audience.Bag.SetTicket(ticket);
        }
    }
}
```

```cs
public class Theater
{
    private TicketSeller ticketSeller;

    public Theater(TicketSeller ticketSeller)
    {
        this.ticketSeller = ticketSeller;
    }

    public void Enter(Audience audience)
    {
        ticketSeller.SellTo(audience);
    }
}
```

`TicketOffice`에 대한 접근이 오직 `TicketSeller`에만 제한되어 있다. 이를 **캡슐화**라고 하며 목적은 변경하기 쉬운 객체를 만드는 것이다. 캡슐화를 통해 객체 내부로의 접근을 제한하면 객체와 객체 사이의 결합도를 낮출 수 있기 때문에 설계를 좀 더 쉽게 변경할 수 있다.

수정된 `Theater`는 `TicketSeller`에게 손님만 전달할 뿐, 어떻게 판매하는지, `TicketOffice`를 어떻게 사용하는지는 알 필요가 없다. 단지 `TicketSeller`가 `SellTo()` 메시지를 이해하고 응답할 수 있다는 사실만 알고 있을 뿐이다.

이를 `Theater`는 오직 `TicketSeller`의 **인터페이스**에만 의존한다는 것이다. `TicketSeller`가 내부에 `TicketOffice` 인스턴스를 포함하고 있다는 사실은 **구현**의 영역에 속한다.

객체를 인터페이스와 구현으로 나누고 인터페이스만을 공개하는 것은 객체 사이의 결합도를 낮추고 변경하기 쉬운 코드를 작성하기 위해 따라야 하는 기본적인 설계 원칙이다.

*객체지향의 사실과 오해에서 언급하지만, 설계의 기초는 객체의 동적 모델을 먼저 도메인 모델에 맞게 만들고, 그에 맞는 인터페이스(메시지)를 만든 뒤 이 객체들 사이의 협력 공동체를 설계하는 것이다. 그 이후에 정적모델인 클래스로 동적 모델을 투사하여 각각 객체에 올바른 책임을 할당한 뒤 객체들의 협력에서 스스로, 자율적으로 역할을 수행하는 것이다.*

수정된 코드는 `Theater`에서 접근하는 `TicketOffice`의 의존성이 제거되었다.

마찬가지로 `Audience`도 `Bag`에 대한 접근을 열어두었기 때문에 자율적이지 못하다. 따라서 `TicketSeller`가 직접 `Bag`에 접근하는 것이 아닌 `Audience`에게 `Bag`를 통해 티켓을 구매하도록 변경해야 한다.

```cs
class Audience
{
    private Bag bag;

    public Audience(Bag bag)
    {
        this.bag = bag;
    }

    public float Buy(Ticket ticket)
    {
        if (bag.HasInvitation())
        {
            bag.SetTicket(ticket);
            return 0;
        }
        else
        {
            bag.MinusAmount(ticket.Fee);
            bag.SetTicket(ticket);
            return ticket.Fee;
        }
    }
}
```

```cs
class TicketSeller
{
    private TicketOffice ticketOffice;

    public TicketSeller(TicketOffice ticketOffice)
    {
        this.ticketOffice = ticketOffice;
    }

    public void SellTo(Audience audience)
    {
        ticketOffice.PlusAmount(audience.Buy(ticketOffice.GetTicket()));
    }
}
```

변경된 코드는 `Audience`가 직접 자신의 가방 안에 초대장이 들어있는지를 스스로 확인한다. (이는 합성을 통해 `Audience`가 `Bag`를 포함하고 있다는 사실을 알 수 있다.) 캡슐화를 통해 2가지를 이뤄냈다. 먼저 객체의 자율성을 보장하여 변경하기 쉬운 객체를 만들었고, `Bag`에 대한 접근을 제한하여 객체 사이의 결합도를 낮췄다. (해당 객체의 소유자를 명확히 알 수 있다.)

`SellTo`메서드를 한번 읽어보면 객체간의 자율성이 높아진 것을 알 수 있다. `TicketSeller`와 `Audience` 사이의 결합도가 낮아졌다.

#### 무엇이 개선됐는가

수정된 `Audience`와 `TicketSeller`는 자신이 가지고 있는 소지품을 스스로 관리한다. (합성의 이점) 이것은 실제 세상과 정확하게 일치하기 때문에 의사소통 관점에서도 확실히 개선되었다.

중요한 점은 각각의 객체의 내부 구현이 변경되더라도 `Theater`는 변경할 필요가 없다는 것이다. (SRP를 준수하고 있다.) 이는 `Theater`가 `TicketSeller`의 인터페이스에만 의존하기 때문이다.

만약 `Audience`가 가방이 아니라 작은 지갑을 소지하도록 코드를 변경하고 싶다면 `Audience`의 내부만 변경하면 된다. 따라서 변경의 용이성 측면에서도 확실히 개선됐다고 말할 수 있다.

*여기서 저자가 중요한 부분을 말해주는데, 만약 가방이 아닌 작은 지갑의 경우엔 조금 더 나아가 이를 인터페이스나 추상 클래스로 만들어 DI를 통한 더 상위의 결합도를 낮출 수 있다.*

#### 어떻게 한 것인가

이는 아주 간단한 리팩터링으로 실제 리팩터링 책에 기본 원칙으로 등장한다. 다만 설계 관점에서 트레이드 오프를 고려하여 의존성을 관리했다는 점이 다르다.

처음 목적대로 객체의 자율성을 높이는 방향으로 설계를 개선했다. 그 결과, 이해하기 쉽고 유연한 설계를 얻을 수 있었다.

#### 캡슐화와 응집도

핵심은 객체 내부의 상태를 캡슐화하고 객체 간에 오직 메시지를 통해서만 상호작용하도록 만드는 것이다.

*이에 대해서 객체지향의 사실과 오해에도 다뤘지만 흔하게 객체지향에서 배우는 캡슐화의 개념으로 단순하게 이해하면 안된다. 캡슐화의 이점은 객체지향적으로 설계할 때 비로소 나온다.*

- `Theater`는 `TicketSeller`의 인터페이스에만 의존한다. (내부는 전혀 알지 못한다. 응답한다는 사실만 알 뿐이다.)
- `TicketSeller` 역시 `Audience`의 인터페이스에만 의존한다. (내부는 전혀 알지 못한다. Buy메시지에 응답할 수 있고 원하는 결과를 반환한다는 사실만 알 뿐이다.)

밀접하게 연관된 작업만을 수행하고 연관성 없는 작업은 다른 객체에게 위임하는 객체를 가리켜 응집도가 높다고 말한다. 자신의 데이터를 스스로 처리하는 자율적인 객체를 만들면 결합도를 낮출 수 있을뿐더러 응집도를 높일 수 있다.

객체의 응집도를 높이기 위해서 객체 스스로 자신의 데이터를 책임져야 한다. 객체는 기본적으로 자신의 데이터를 스스로 처리하는 자율적인 존재여야 한다. 그것이 객체의 응집도를 높이는 첫걸음이다.

외부 간섭을 최대한 배제하고 메시지를 통해서만 협력하는 자율적인 객체들의 공동체를 만드는 것이 훌륭한 객체지향 설계를 얻을 수 있는 지름길인 것이다.

> 어떠한 객체도 섬이 아니다.  

#### 절차지향과 객체지향

수정하기 전 코드는 `Theater`의 `enter()`메서드 안에서 `Audience`와 `TicketSeller`로부터 `Bag`과 `TicketOffice`를 가져와 관람객을 입장시키는 절차를 구현했다. `Audience`, `TicketSeller`, `Bag`, `TicketOffice`는 관람객을 입장시키는 데 필요한 정보를 제공하고 모든 처리는 `Theater`의 `enter()`메서드 안에 존재했다는 점을 주목하라.

이 관점에서 `Theater`의 `enter()`메서드는 **프로세서(Process)**이며 `Audience`, `TicketSeller`, `Bag`, `TicketOffice`는 **데이터(Data)**이다. 이처럼 프로세스와 데이터를 별도의 모듈에 위치시키는 방식을 **절차적 프로그래밍**이라고 부른다.

*절차적 프로그래밍 방식으로 작성된 코드의 전형적인 의존성 구조를 보여준다. 모든 처리가 단일 클래스에서 이뤄지고 나머지 클래스는 단지 데이터 역할만 수행할 뿐이다.*

이러한 코드는 앞서 말한 직관에 위배되고, 관람객과 판매원이 수동적인 존재로 전락하게 된다. 이는 코드를 읽는 사람이 이해하기 어렵게 만들 뿐만 아니라 변경하기 어렵게 만든다.

따라서 자신의 데이터를 스스로 처리하도록 프로세스와 데이터를 적절하게 분리하는 것이 객체지향의 핵심이다. 객체지향 코드는 자신의 문제를 스스로 처리해야 한다는 우리의 예상을 만족시켜주기 때문에(이는 앞서 언급한 패러다임의 이점과 동일하다.) 이해하기 쉽고, 객체 내부의 변경이 객체 외부에 파급되지 않도록 제어할 수 있기 때문에 변경하기가 수월하다.

#### 책임의 이동

두 방식 사이에 근본적인 차이를 만드는 것은 **책임의 이동(shift of responsibility)**이다. 여기서 '책임'을 기능을 가리키는 객체지향 세계의 용어로 생각해고 무방하다.

- [객체지향의 사실과 오해: 5장 책임에 관한 글](https://github.com/fkdl0048/BookReview/blob/main/Object-oriented_Facts_and_Misunderstandings/Chapter05.md#%EC%9E%90%EC%9C%A8%EC%A0%81%EC%9D%B8-%EC%B1%85%EC%9E%84)

절차적 프로그래밍 방식은 작업 흐름이 주로 `Theater`에 의해 제어된다는 사실을 알 수 있다. 객체지향 세계의 용어를 사용한다면 책임이 `Theater`에게 집중되어 있다고 말할 수 있다.

그에 반해 객체지향 설계에서는 제어 흐름이 각 객체에 적절하게 분산돼 있음을 알 수 있다. 다시 말해 하나의 기능을 완성하는 데 필요한 책임이 여러 객체에 걸쳐 분산돼 있는 것이다.

절차지향에선 `Theater`객체가 책임을 모두 짊어지고 있지만, 객체지향에선 `Theater`객체가 필요한 책임을 적절히 분산시키고 있다. 이것이 바로 **책임의 이동**이다.

객체지향 설계에서는 독재자가 존재하지 않고 각 객체에 책임이 적절하게 분배된다. 따라서 **각 객체는 자신을 스스로 책임진다.**

이런 관점에서 객체지향 프로그래밍을 흔히 데이터와 프로세스를 하나의 단위로 통합해 놓는 방식으로 표현하기도 한다. 비록 이 관점이 객체지향을 구현 관점에서만 바라본 지극히 편협한 시각인 것은 맞지만 객체지향에 갓 입문한 사람들에게 어느 정도 실용적인 조언인 것 또한 사실이다.

*하지만 설계 관점에선 다르게 바라봐야 한다.*

이 책을 읽고 객체지향 안에 단순히 데이터와 프로세스를 하나의 객체 안으로 모으는 것 이상의 무엇이 있다는 점을 알게 될 것이다. 사실 객체지향 설계의 핵심은 **적절한 객체에 적절한 책임을 할당하는 것**이다. 객체는 다른 객체와의 협력이라는 문맥 안에서 특정한 역할을 수행하는 데 필요한 적절한 책임을 수행해야 한다. 따라서 어떤 데이터를 가지느냐보다는 객체에 어떤 책임을 할당할 것이냐에 초점을 맞춰야 한다.

설계를 어렵게 만드는 것은 **의존성**이라는 것을 기억하자. 해결 방법은 불필요한 의존성을 제거함으로써 객체 사이의 **결합도**를 낮추는 것이다. 예제에서는 세부사항을 내부로 감춰서 캡슐화를 통해 의존성을 줄여 결합도를 낮췄다. (자율성은 올림)

*정리하자면 낮은 결합도와 높은 응집도를 가지고 협력할 수 있도록 최소한의 의존성을 남기는 것이 훌륭한 객체지향 설계이다.*

#### 더 개선할 수 있다

현재의 설계는 이전의 설계보단 좋아졌지만 아직도 개선할 부분이 남아있다. 여기서 객체지향이 실세계와 다른 부분을 알 수 있다.

객체지향은 이름과 똑같이 모든 것을 객체로 보기 때문에 가방, 티켓, 초대장 등도 객체로 봐야 한다. 또한 객체는 자신의 데이터를 스스로 처리하는 자율적인 존재여야 한다.

*이것은 한 예에 불과하며 데이터 하나하나 까지 전부 객체로 만들라는 것은 아니다. 모든지 극단적인 사례는 좋지 못하다. (극단적인 SRP, DI, 등등) 해당 도메인에 맞는 유지수준을 생각하여 항상 새롭게 설계하는 능력이 중요하다.*

```cs
class Bag
{
    private float amount;
    private Ticket ticket;
    private Invitation invitation;

    public float Hold(Ticket ticket)
    {
        if (HasInvitation())
        {
            SetTicket(ticket);
            return 0;
        }
        else
        {
            SetTicket(ticket);
            MinusAmount(ticket.Fee);
            return ticket.Fee;
        }
    }

    private bool HasInvitation() => invitation is not null;
    private void SetTicket(Ticket ticket) => this.ticket = ticket;
    private void MinusAmount(float amount) => this.amount -= amount;
}
```

public 메서드였던 `HasInvitation()`, `SetTicket()`, `MinusAmount()` 메서드들은 더 이상 외부에서 사용되지 않고 내부에서만 사용되기 때문에 가시성을 private으로 변경했다. 메서드들을 잘게 쪼개고 적절하게 네이밍 하는 것은 중요하지만 다른 영역이기에 생략한다.

이제 `Audience`는 Bag의 구현이 아닌 인터페이스에만 의존하도록 수정한다.

```cs
class Audience
{
    private Bag bag;

    public Audience(Bag bag)
    {
        this.bag = bag;
    }

    public float Buy(Ticket ticket) => bag.Hold(ticket);
}
```

`TicketSeller`역시 `TicketOffice`의 자율권을 침해한다. 현재의 `TicketSeller`는 `TicketOffice`에 있는 티켓을 마음대로 꺼내서 멋대로 판매하고 있다.

```cs
public class TicketOffice
{
    private float amount;
    private List<Ticket> tickets = new();

    public TicketOffice(float amount, params Ticket[] tickets)
    {
        this.amount = amount;
        this.tickets.AddRange(tickets);
    }

    public void SellTicketTo(Audience audience)
    {
        var ticket = GetTicket();
        if (ticket is null)
        {
            return;
        }
        PlusAmount(audience.Buy(ticket));
    }

    private Ticket GetTicket()
    {
        if (tickets.Count == 0)
        {
            return null;
        }

        var ticket = tickets[0];
        tickets.RemoveAt(0);
        return ticket;
    }

    private void PlusAmount(float amount) => this.amount += amount;
}
```

```cs
class TicketSeller
{
    private TicketOffice ticketOffice;

    public TicketSeller(TicketOffice ticketOffice)
    {
        this.ticketOffice = ticketOffice;
    }

    public void SellTo(Audience audience) => ticketOffice.SellTicketTo(audience);
}
```

이 과정에서 `TicketOffice`와 `Audience`간의 의존성이 생겼다. 변경 전에는 `TicketOffice`가 `Audience`에 대해서 알지 못했다.

변경 전에는 존재하지 않았던 의존성이 추가된 것은 높은 결합도가 생겼음을 의미하고 이는 변경하기 어렵다는 점을 의미한다.

이 시점이 트레이드오프를 생각해야 하는 시점으로 어떤 것을 우선해야 하는가를 선택하는 것이다. (TicketOffice의 자율성보다 Audience의 결합도를 낮추는 것이 좋다고 생각) 이러한 예제를 통해 다음과 같은 사실을 알 수 있다.

- 어떤 기능을 설계하던간에 방법은 한 가지 이상일 수 있다.
- 동일한 기능을 한 가지 이상의 방법으로 설계할 수 있기 때문에 결국 설계는 트레이드오프의 산물이다

어떠한 경우에도 모든 사람들을 만족시킬 수 있는 설계를 만들 수는 없으며, 설계는 균형의 예술이다. 훌륭한 설계는 적절한 트레이드 오프의 결과물이라는 사실을 명심하고, 이러한 과정이 프로그래밍의 가장 큰 매력이다.

#### 그래, 거짓말이다

앞에서 실생활의 관람객과 판매자가 스스로 일을 처리하기 때문에 코드에서의 `Audience`와 `TicketSeller`가 스스로 자신을 책임져야 한다고 했다. 이것은 세상을 바라보는 직관과 일치하고 그를 통해 코드를 더 쉽게 이해하는 경향이 있다.

그러나 `Theater`, `Bag`, `TicketOffice`는 어떠한가? 이들은 실세계에서 자율적인 존재가 아니다. 하지만 현실에서는 수동적인 존재라도 일단 객체지향 세계에 들어오면 모든 것이 능동적이고 자율적인 존재로 바뀐다. (의인화)

앞에서는 실세계에서의 생물처럼 스스로 생각하고 행동하도록 소프트웨어 객체를 설계하는 것이 이해하기 쉬운 코드를 작성하는 것이라고 말했다. 하지만 **훌륭한 객체지향 설계란, 소프트웨어를 구성하는 모든 객체들이 자율적으로 행동하는 설계를 가리킨다.** 그 대상이 비록 실세계에서는 생명이 없는 수동적인 존재라고 하더라도 객체지향에서는 그들은 생명과 지능을 가진 싱싱한 존재로 태어난다.

### 객체지향 설계

#### 설계가 왜 필요한가

> 설계란 코드를 배치하는 것이다.  
> : Metz12

어떤 사람들은 설계가 코드를 작성하는 것보다 높은 차원의 창조적인 행위라고 생각하는 것 같다. 하지만 **설계를 구현과 떨어트려서 이야기하는 것은 불가능하다.** 설계는 코드를 작성하는 매 순간 코드를 어떻게 배치할 것인지를 결정하는 과정에서 나온다. 설계는 코드 작성의 일부이며 코드를 작성하지 않고서는 검증할 수 없다.

절차지향과 객체지향의 예제로 돌아가서 두 코드의 실행한 결과는 완전히 같다. 두 코드 모두 소극장에 방문한 관람객들을 입장시키는 작업을 수행한다. 하지만 코드를 배치하는 방법에서의 차이가 있는데, 절차지향은 데이터와 프로세스를 함께 배치하였고, 객체지향은 필요한 데이터를 보유한 클래스 안에 프로세스를 함께 배치했다. 두 프로그램은 다른 설계를 가진 것이다.

좋은 설계란, 오늘 완성해야 하는 기능을 구현하는 코드를 짜야 하는 동시에 내일 쉽게 변경할 수 있는 코드를 짜야 한다. 즉, 오늘 요구하는 기능을 온전히 수행하면서 내일의 변경을 매끄럽게 수용할 수 있는 설계다.

변경을 수용할 수 있는 설계가 중요한 이유는 요구사항은 항상 변경되기 때문이다. (소프트웨어 개발에서 불확실성은 항상, 매번 발생한다.) 개발을 시작하는 시점에 구현에 필요한 모든 요구사항을 수집하는 것은 불가능에 가깝고, 모든 요구사항을 수집할 수 있다고 가정하더라도 개발이 진행되는 동안에 변경될 수 밖에 없다.

변경을 수용할 수 있는 설계가 중요한 이유는 버그에 관련되어 있다. 요구사항의 수정은 필연적으로 코드의 수정을 요구하고 그런 수정사항에서 유리하게 대처할 수 있는 설계가 바로 객체지향 설계이다. 앞서 절차지향이 수정에 유리하지 못한 이유는 SRP법칙을 통해 살펴봤고, 그런 수정이 어려움에 있어서 가장 큰 문제점은 두려움이다.(테스트 코드의 중요성에도 포함이 된다.)

*이러한 설계는 애자일 개발 방법론에도 매우 유리하다.*

#### 객체지향 설계

따라서 진정으로 원하는 것은 변경에 유리하게 대응할 수 있는 코드이다. 객체지향 프로그래밍은 의존성을 효율적으로 통제할 수 있는 다양한 방법을 제공함으로써 요구사항 변경에 좀 더 수월하게 대응할 수 있는 가능성을 보여준다.

변경 가능한 코드란 이해하기 쉬운 코드다. 만약 어떤 코드를 변경해야 하는데 그 코드를 이해할 수 없다면 당연하게 스트레스부터 받기 시작한다. 본인이 짠 코드가 일주일 뒤에 봤을 때 이해할 수 없는 코드라면, 다른 사람이 그 코드를 이해할 수 있을까?

객체지향 패러다임은 우리가 세상을 바라보는 방식대로 코드를 작성할 수 있게 해주기 때문에 세상을 좀 더 추상적으로 바라보고 이러한 추상적 개념들은 같은 객체지향 패러다임에 속해있는 프로그래머로 하여금 이해하기 쉽게 만들어준다.

그러나 우리가 쉽게 객체지향에 대해서 배우는 데이터와 프로세스를 몰아 넣는 덩어리가 아니라, 객체간의 상호작용을 통한 협력으로 바라봐야 한다.

### 느낀점

확실히 `객체지향의 사실과 오해`에 비해 이론적인 내용보단 실습위주의 내용이 많았어서 개념을 제대로 파악하는데 어려움이 없었다. 두 세번 읽을 필요 없이 중복적인 내용도 적고 언어적인 부분도 이미 사실과 오해에서 접했기 때문에 편했던 것 같다.

스스로 생각하고 답변할 수 있는 부분들이 많았고 뒤에서 내가 생각하는 내용과 일치하는지에 관한 내용이 나올지 궁금하다.

가장 좋았던 부분은 `책임의 이동`으로 그동안 머릿속의 개념적인 부분을 정의해준 내용이라 신선하게 느껴졌다.

또한 사례를 통해 트레이드오프의 핵심적인 부분을 보여준 것도 다른 사람들이 이해하기 좋은 예라고 생각한다.

#### 논의사항

> 이론이 먼저일까, 실무가 먼저일까?

- 여러분은 프로젝트를 제외한 개인적 공부와 실습(프로젝트, 현업) 중 %로 따진다면 어느정도의 비율을 가지고 계신가요?
  - 그렇게 비율이 나오는 이유에 대해서도 같이 이야기하면 좋을 것 같습니다.
