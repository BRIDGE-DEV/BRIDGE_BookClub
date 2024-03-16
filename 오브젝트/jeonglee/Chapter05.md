## 5장 책임 할당하기

이번 장은 `GRASP`패턴을 통해 책임 할당의 어려움을 해결하기 위한 답을 알아볼 것이다. 이를 통해 응집도와 결합도, 캡슐화 같은 다양한 기준에 따라 책임을 할당하고 결과를 트레이드오프할 수 있는 기준을 배우게 될 것이다.

### 책임 주도 설계를 향해

데이터 중심의 설계에서 책임 중심의 설계로 전환하기 위해서는 다음의 원칙을 따라야 한다.

- 데이터보다 행동을 먼저 결정하라
- 협력이라는 문맥 안에서 책임을 결정하라

#### 데이터보다 행동을 먼저 결정하라

*모든 내용이 반복이지만, 그만큼 중요한 내용이기에 내가 말로 내뱉고 직접 적용할 수 있을 떄까지 공부하자.*

객체에게 중요한 것은 데이터가 아니라 외부에 제공하는 행동이다. 객체는 협력에 참여하기 위해 존재하며 협력 안에서 수행하는 책임이 객체의 존재가치를 증명한다.

데이터는 객체가 책임을 수행하는 데 필요한 재료를 제공할 뿐이다. 이러한 데이터에 초점을 맞추게 되면 객체의 캡슐화가 약화되고 낮은 응집도와 높은 결합도를 가진 객체들로 넘쳐나게 된다.

우리에게 필요한 것은 객체의 데이터에서 행동으로 무게 중심을 옮기기 위한 기법이다. 가장 기본적인 해결 방법은 객체를 설계하기 위한 순거를 바꾸는 것이다. (패러다임의 전환)

객체지향에서 가장 중요한 것은 적절한 객체에게 적절한 책임을 할당하는 능력이다. 객체에게 어떤 책임을 할당해야 하는지는 협력을 통해 알아내야 한다. (문맥)

#### 협력이라는 문맥 안에서 책임을 결정하라

**객체에게 할당된 책임의 품질은 협력에 적합한 정도로 결정된다.** 객체에게 할당된 책임이 협력에 어울리지 않는다면 그 책임은 나쁜 것이다. 객체의 입장에서는 조금 어색해 보이더라도 협력에 적합하다면 그 책임이 좋은 것이다. 책임은 객체의 입장이 아니라 객체가 참여하는 협력에 적합해야 한다.

이 사실을 통해 객체의 책임을 협력이라는 문맥을 통해 알아내고 협력을 시작하는 주체가 메시지 전송자이기 때문에 협력에 적합한 책임이란 메시지 수신자가 아니라 **메시지 전송자에게 적합한 책임을 의미한다.** 다시 말해서 **메시지를 전송하는 클라이언트의 의도에 적합한 책임을 할당해야 한다는 것이다.**

즉, 객체를 결정한 후에 메시지를 선택하는 것이 아니라 메시지를 결정한 후에 객체를 선택해야 한다는 것이다.

메시지가 클라이언트의 의도를 표현해준다는 사실을 주목하라. 객체를 결정하기 전에 객체가 수신할 메시지를 먼저 결정한다는 점 역시 주목하라. 클라이언트는 어떤 객체가 메시지를 수신할지 알지 못한다. 클라이언트는 단지 임의의 객체가 메시지를 수신할 것이라는 사실을 믿고 자신의 의도를 표현한 메시지를 전송할 뿐이다.

그리고 메시지를 수신하기로 결정된 객체는 메시지를 처리할 '책임'을 할당 받게 된다.

**메시지를 먼저 결정하기 때문에 메시지 송신자는 메시지 수신자에 대한 어떠한 가정도 할 수 없다. 메시지 전송자의 관점에서 메시지 수신자가 깔끔하게 캡슐화되는 것이다. 이렇게 해야 협력이라는 문맥 안에서 메시지에 집중하는 책임 중심의 캡슐화의 원리를 지키기가 쉬워진다.**

#### 책임 주도 설계

*3장에서 설명한 책임 주도 설계의 흐름이다.*

- 시스템이 사용자에게 제공해야 하는 기능인 시스템 책임을 파악한다.
- 시스템 책임을 더 작은 책임으로 분할한다.
- 분할된 책임을 수행할 수 있는 적절한 객체 또는 역할을 찾아 책임을 할당한다.
- 객체가 책임을 수행하는 도중 다른 객체의 도움이 필요한 경우 이를 책임질 적절한 객체 또는 역할을 찾는다.
- 해당 객체 또는 역할에게 책임을 할당함으로써 두 객체가 협력하게 된다.

책임 주도 설계의 핵심은 책임을 결정한 후에 책임을 수행할 객체를 결정하는 것이다. 그리고 협력에 참여하는 객체들의 책임이 어느 정도 정리될 때까지는 객체의 내부 상태에 대해 관심을 가지지 않는 것이다. (TDD와 비슷한)

### 책임 할당을 위한 GRASP 패턴

객체지향이 성숙해지면서 사람들은 다양한 책임 할당 기법을 고안했는데, 그중에서 대중적으로 가장 널리 알려진 것은 **GRASP**(General Responsibility Assignment Software Patterns)패턴이다. 객체에게 책임을 할당할 때 지침으로 삼을 수 있는 원칙들의 집합을 패턴 형식으로 정리한 것이다.

#### 도메인 개념에서 출발하기

설계를 시작하기 전에 도메인에 대한 개략적인 모습을 그려 보는 것은 매우 유용하다. 도메인 안에는 무수히 많은 개념들이 존재하며 이 도메인 개념들을 책임 할당의 대상으로 사용하면 코드에 도메인의 모습을 투영하기가 좀 더 수월해진다. **따라서 어떤 책임을 할당해야 할 때 가장 먼저 고민해야 하는 유력한 후보는 도메인 개념이다.**

**설계를 시작하는 단계에서는 개념들의 의미와 관계가 정확하거나 완벽할 필요가 없다.** 단지 출발점이 필요할 뿐이다.(시작하고 수정하자.) 이 단계에서는 책임을 할당받을 객체들의 종류와 관계에 대한 유용한 정보를 제공할 수 있다면 충분하다.

실제로 책에 나온 도메인 모델은 2장에서 그린 모델과 다른 형태를 가지고 있다. **즉, 올바른 도메인 모델이란 존재하지 않으며 필요한 것은 도메인 모델을 그대로 투영한 모델이 아니라 구현에 도움이 되는 모델이다.** 다시 말해서 실용적이면서도 유용한 모델이 필요하다.

*개인적으로 UML도 하나의 도구이기에 자신이 보여주고자 하는 도메인모델은 다양한 형태로 그려내거나 적을 수 있다고 생각한다.*

#### 정보 전문가에게 책임을 할당하라

사용자에게 제공해야 하는 기능은 영화를 예매하는 것이다. 이를 책임으로 간주하면 애플리케이션은 영화를 예매할 책임이 있다고 말할 수 있다. **이 책임을 수행하는데 필요한 메시지는 수신할 객체가 아니라 전송할 객체의 의도를 반영하여 결정되어야 한다.**

- 메시지를 전송할 객체는 무엇을 원하는가?

이 객체는 영화를 예매하고 싶어하기에 `예매하라`라는 메시지가 적합하다.

- 메시지를 수신할 적합한 객체는 누구인가?

책임을 수행할 정보를 알고 있는 객체에게 책임을 할당해야 한다. GRASP에서 이를 INFORMATION EXPERT 패턴으로 부른다.

정보와 행동을 최대한 가까운 곳에 위치시키기 때문에 캡슐화를 유지할 수 있다. 필요한 정보를 가진 객체들로 책임이 분산되기에 더 응집력이 있고, 이해하기 쉬워진다. 따라서 높은 응집도가 가능하다. 결과적으로 결합도도 낮아져서 간결하고 유지보수하기 쉬운 시스템을 구축할 수 있다.

**여기서 이야기 하는 정보는 데이터와 다르다.** 책임을 수행하는 객체가 정보를 '알고'있다고 해서 그 정보를 '저장'하고 있을 필요는 없다. 객체는 해당 정보를 제공할 수 있는 다른 객체를 알고 있거나 필요한 정보를 계산해서 제공할 수도 있다. 어떤 방식이건 정보 전문가가 데이터를 반드시 저장하고 있을 필요는 없다는 사실을 이해하자.

따라서 INFORMATION EXPERT 패턴에 따르면 예매하는 데 필요한 정보를 가장 많이 알고 있는 객체에게 `예매하라` 메시지를 처리할 책임을 할당해야 한다. 따라서 `상영(screening)`이라는 객체에게 `예매하라`라는 책임을 할당하는 것이 적합하다.

`예매하라`라는 메시지를 수신했을 때 `Screening`이 수행해야 하는 작업의 흐름을 생각해보면 이제부터는 외부의 인터페이스가 아닌 `Screening`의 내부로 들어가 메시지를 처리하기 위해 필요한 절차와 구현을 고민해보는 것이다.

지금은 동적 모델을 만드는 과정이며, 책임을 결정하는 단계이기에 너무 세세한 부분까지 고민할 필요는 없다. ekswl `Screening`이 책임을 수행하는 데 필요한 작업을 구상해보고 스스로 처리할 수 없는 작업이 무엇인지를 파악하면 된다.

만약 스스로 처리할 수 없는 작업이 있다면 외부에 도움을 요청해야 한다. 이 요청이 외부로 전송되는 또 다른 메시지가 되며 결국 이 메시지가 새로운 객체의 책임을 할당한다. 이런 연쇄적인, 창발성을 지닌 협력 공동체를 만들어야 한다.

*위 메시지에 맞는 책임을 할당하게 된다면 결국 SOLID의 리스코프를 제외한 나머지 원칙들이 자동으로 지켜진다.*

`예매하라`라는 메시지를 완료하기 위해 예매 가격을 계산하는 작업이 필요하다. 예매 가격은 영화 한 편의 가격을 계산한 금액에 예매 인원수를 곱한 값으로 구할 수 있다. 따라서 영화 한편의 가격을 알아야 한다. 안타깝게도 `Screening`은 가격을 계산하는 데 필요한 정보를 모르기 때문에 `가격을 계산하라`라는 메시지를 외부로 전송한다.

다시 이 메시지를 책임질 객체를 선택해야 한다. 기본 원칙인 INFORMATION EXPERT 패턴을 다시 따라서 영화 가격을 알고 있는 전문가는 영화 자체이다. 따라서 `영화`에게 `가격을 계산하라`라는 책임을 할당하는 것이 적합하다. (객체지향 세계에선 수동적인 객체는 없다.)

이제 가격을 계산하기 위해 Movie는 영화가 할인 가능한지 판단한 후 할인 정책에 따라 할인 요금을 제외한 금액을 계산하면 된다. 이 중에서 영화가 스스로 처리할 수 없는 일이 한 가지가 있다. 바로 할인 여부를 판단하는 일이다. 따라서 `할인 여부를 판단하라`라는 메시지를 전송해 외부의 도움을 요청해야 한다.

위 과정에서 가장 중요하게 생각해야 하는 부분은 메시지에 의해 책임이 선택되고 이런 과정을 스스로 도메인에 맞게 만들어 가며 책임을 할당하는 것이다. 이 흐름, 문맥이 가장 중요하며 실제로 몇 번 해보는 것이 좋을 것 같다.

할인 여부를 판단하는 데 필요한 정보를 가장 많이 알고 있는 객체는 할인 조건이므로 이 객체에 책임을 할당해야 한다. `DisconutCondition`은 자체적으로 할인 여부를 판단하는 데 필요한 모든 정보를 알고 있기에  외부의 도움 없이도 스스로 할인 여부를 알아낼 수 있다. 즉, 외부로 메시지를 전송하지 않는다.

`Movie`는 `DiscountCondition`에 전송한 `할인 여부를 판단하라`메시지의 결과로 할인 여부를 반환받는다. `DiscountCondition` 중에서 할인 가능한 조건이 하나라도 존재하면 금액 할인 정책이나 비율 할인 정책에 정해진 계산식에 따라 요금을 계산한 후 반환한다.

INFORMATION EXPERT 패턴은 객체에게 책임을 할당할 때 가장 기본이 되는 책임 할당 원칙이다. 객체란 상태와 행동을 함께 가지는 단위라는 객체지향의 가장 기본적인 원리를 책임 할당의 관점에서 표현한다. 이를 지키기만 해도 자율성이 높은 객체들로 구성된 협력 공동체를 구축할 가능성이 높아지는 것이다.

#### 높은 응집도와 낮은 결합도

**설계는 트레이드오프 활동이라는 것을 기억하라. (은총알은 없다.)** 동일한 기능을 구현할 수 있는 무수히 많은 설계가 존재한다. **따라서 실제로 설계를 진행하다 보면 몇 가지 설계 중에서 한 가지를 선택해야 하는 경우가 빈번하게 발생한다.** 이 경우 올바른 책임 할당을 위해 INFORMATION EXPERT 패턴 이외의 다른 책임 할당 패턴을 함께 고려해야 한다.

실제로 객체지향이 매력적인 이유와 좋은 구조, 코드를 쉽게 말할 수 없는 이유는 설계하는 사람의 관점과 그 때의 상황에 따라 매번 다른 결과가 나오기 때문이다. 이를 좀더 디커플링하여 생각할 수 있게 해주는 패턴들을 잘 활용하는 것이 중요하다.

현재까지 나온 동적모델에서 지금은 `Movie`가 `DiscountCondition`에게 `할인 여부를 판단하라`라는 메시지를 전송하고 있다. 대신에 `Screening`에서 직접 `DiscountCondition`과 협력하는 것도 같은 결과를 출력하긴 한다. **내부적인 동작의 차이만 있을 뿐, 결과적으로는 같은 결과를 출력한다.**

하지만 `Movie`가 `DiscountCondition`에게 직접 메시지를 전송하는 방식을 선택한 이유는 응집도와 결합도에 있다. 높은 응집도와 낮은 결합도는 객체에 책임을 할당할 때 항상 고려해야 하는 기본 원리다. 책임을 할당할 수 있는 다양한 대안들이 존재한다면 응집도와 결합도 측면에서 더 나은 대안을 선택하는 것이 좋다.

즉, 두 협력 패턴에서 높은 응집도와 낮은 결합도에 더 가까운 설계를 선택한느 것이 좋다는 것이다. GRASP에서는 이를 **LOW COUPLING 패턴**과 **HIGH COHESION 패턴**이라고 부른다

- LOW COUPLING 패턴
  - 의존성을 낮추고 변화의 영향을 줄이며 재사용성을 증가시키는 것이 목적이다.
  - 설계 전체적인 결합도가 낮게 유지되도록 책임을 할당하라
  - 낮은 결합도는 모든 설계 결정에서 염두에 둬야 하는 원리다. 다시 말해 설계 결정을 평가할 때 적용할 수 있는 평가 원리다.
  - 현재의 책임 할당을 검토하거나 여러 설계 대안들이 있을 때 낮은 셜합도를 유지할 수 있는 설계를 선택하라.

이러한 패턴으로 `Movie`가 `Discountcondition`과 협력하는 것이 더 좋은 설계 대안인 것이다. (그림 참고)

- HIGH COHESION 패턴
  - 복잡성을 관리할 수 있는 수준으로 유지하기 위해선 높은 응집도를 유지할 수 있게 책임을 할당하라
  - 낮은 결합도처럼 높은 응집도 역시 모든 설계 결정에서 둬야 할 원리다.
  - 설계 결정을 평가할 때 적용할 수 있는 평가 원리다.
  - 현재의 책임 할당을 검토하고 있거나 여러 설계 대안 중 하나를 선택해야 한다면 높은 응집도를 유지할 수 있는 설계를 선택하라.

`Screening`의 가장 중요한 책임은 예매를 생성하는 것이다. (그런 메시지를 받았기 때문에) 만약 `Screening`이 `DiscountCondition`과 협력해야 한다면 `Screening`은 영화 요금 계산과 관련된 책임을 떠안아야 할 것이다. (책임의 과부화)

다시 말해서 예매 요금을 계산하는 방식이 변경될 경우 `Screening`의 변경이 필요하다. 결과적으로 변경되는 책임까지 짊어지게 되면서 응집도또한 낮아질 수 밖에 없다.

반면 `Movie`는 영화 요금을 계산하는 것으로 영화 요금을 계산하는 데 필요한 할인 조건을 판단하기 위해 `Movie`가 `DiscountCondition`과 협력하는 것은 응집도에 아무런 문제가 되지 않는다.

따라서 LOW COUPLING 패턴과 HIGH COHESION 패턴을 고려하여 설계를 진항하면 책임과 협력의 품질을 향상시킬 수 있고 이는 결과적으로 유연한 코드를 만들 수 있게 된다.

#### 창조자에게 객체 생성 책임을 할당하라

영화 예매 협력의 최종 결과물은 `Reservaton` 인스턴스를 생성하는 것이다. 이것은 협력에 참여하는 어떤 객체에게는 `Reservaton` 인스턴스를 생성할 책임을 할당해야 한다는 것을 의미한다. GRASP의 CREATOR 패턴은 이 같은 경우에 사용할 수 있는 책임 할당 패턴으로서 객체를 생성할 책임을 어떤 객체에게 할당할지에 대한 지침을 제공한다.

- CREATOR 패턴
  - 객체 A를 생성해야 할 때 어떤 객체에게 생성 책임을 할당해야 하는가?
    - B가 A객체를 포함하거나 참조한다.
    - B가 A객체를 기록한다.
    - B가 A객체를 긴밀하게 사용한다.
    - B가 A객체를 초기화하는 데 필요한 데이터를 가지고 있다.(이 경우 B는 A에 대한 전문가다)
  - 위와 같은 조건을 가장 많이 만족하는 B에게 객체 생성 책임을 할당하라.
  - 이 패턴은 어떤 방식으로든 생성되는 객체와 연결되거나 관련될 필요가 있는 객체에 해당 객체를 생성할 책임을 맡기는 것이다.
  - 생성될 객체에 대해 잘 알고 있어야 하거나 그 객체를 사용해야 하는 객체는 어떤 방식으로든 생성될 객체와 연결될 것이다. 다시 말해서 두 객체는 서로 결합된다.
- 이미 결합돼 있는 객체에게 생성 책임을 할당하는 것은 설계의 전체적인 결합도에 영향을 미치지 않는다.

`Reservation`을 잘 알고 있거나, 긴밀하게 사용하거나, 초기화에 필요한 데이터를 가지고 있는 객체는 바로 `Screening`이다. `Screening`은 예매 정보를 생성하는 데 필요한 영화, 상영 시간, 상영 순번 등의 정보에 대한 전문가이며, 예매 요금을 계산하는 데 필수적인 `Movie`도 알고 있다. 따라서 `Screening`에게 `Reservation`의 CREATOR로 선택하는 것이 적절하다.

이렇게 예매에 필요한 책임들이 객체들에게 할당되었지만, 책임 분배는 설계를 시작하기 위한 대략적인 스케치에 불과하다. **진짜 설계는 코드를 작성하는 동안 이뤄진다.** 그리고 협력과 책임이 제대로 동작하는지 확인할 수 있는 유일한 방법은 코드를 작성하고 실행해 보는 것뿐이다.

### 구현을 통한 검증

앞선 동적 모델에서 나온 것처럼 `Screening`은 영화를 예매할 책임을 맡으며 그 결과로 `Reservation`을 생성할 책임을 수행해야 한다. 풀어서 말하면 `Screening`은 예매에 대한 정보 전문가인 동시에 `Reservation`의 창조자다.

처음 메시지를 보내고 수신할 객체의 책임을 할당하듯이 먼저 `Screening`이 `예매하라`라는 메시지를 응답할 수 있어야 한다.

```csharp
public class Screening
{
    public Reservation Reserve(Customer customer, int audienceCount)
    {
        ...
    }
}
```

이렇게 책임이 결정되었다면 책임을 수행할 데이터(인스턴스 변수)를 결정해야 한다. `Screening`의 책임을 수행하기 위해 필요한 데이터는 상영시간과 상영순번을 포함한다. 또한 가격을 계산하라라는 메시지를 송신해야 하기에 `Movie`에 대한 참조도 필요하다.

```csharp
public class Screening
{
    private Movie movie;
    private int sequence;
    private DateTime whenScreened;

    public Reservation Reserve(Customer customer, int audienceCount)
    {
        ...
    }
}
```

다음은 영화를 예매하기 위해서 `Movie`에게 `가격을 계산하라`라는 메시지를 전송해서 계산된 영화 요금을 반환받아야 한다. `calculateFee`라는 메서드는 반환된 요금에 예매 인원 수를 곱해서 전체 예매 요금을 계산한 후 `Movie`을 생성해 반환한다.

*이 부분 오타인지, 잘못 적은 것 같다. `Reservation`을 반환하는 것이 아닌 `Movie`를 반환해야 한다.*

```csharp
public class Screening
{
    private Movie movie;
    private int sequence;
    private DateTime whenScreened;

    public Reservation Reserve(Customer customer, int audienceCount)
    {
        return new Reservation(customer, this, CalculateFee(audienceCount), audienceCount);
    }

    private Money CalculateFee(int audienceCount)
    {
        return movie.CalculateFee(this).Times(audienceCount);
    }
}
```

`Screening`을 구현하는 과정에서 `Movie`에 전송하는 메시지의 시그니처를 `calculateMovieFee(Screening screening)`으로 선언한 이유는 이 **메시지 수신자인 `Movie`가 아니라 송신자인 `Screening`의 의도를 표현한다.** 여기서 중요한 것은 `Screening`이 `Movie`의 내부 구현에 대한 어떤 지식도 없이 전송할 메시지를 결정했다는 것이다. 이처럼 `Movie`의 구현을 고려하지 않고 필요한 메시지를 결정하면 `Movie`의 내부 구현을 깔끔하게 캡슐화할 수 있다.

*즉, 송신자의 입장에서 명확한 메시지를 선택하여 외부로 보내면 이를 수신한 객체의 책임으로 적절하게 구현한다. (캡슐화) 지금은 public메서드로 결합도가 이어져 있지만, Movie자체가 추상적이거나 계산 메서드가 인터페이스라면 DI를 통해 더욱더 결합도를 낮출 수 있을 것 같다. 마찬가지로 트레이드오프를 고려하라.*

현재 `Screening`과 `Movie`를 연결하는 유일한 연결 고리는 메시지뿐이다. 따라서 메시지가 변경되지 않는 한 `Movie`에 어떤 수정을 가하더라도 `Screening`에는 영향을 미치지 않는다. 메시지가 객체를 선택하도록 책임 주도 설계의 방식을 따르면 캡슐화와 낮은 결합도라는 목표를 비교적 손쉽게 달성할 수 있다.

이제는 `Screening`이 `Movie`와 협력하기 위해 전송한 `CalculateFee`에 대해 응답하기 위해 `Movie`에게도 책임이 생기게 된다.

```csharp
public class Movie
{
    public Money CalculateFee(Screening screening)
    {
        ...
    }
}
```

요금을 계산하기 위해 Movie는 기본 금액, 할인 조건, 할인 정책 등의 정보를 알아야 한다. 현재 설계에서 할인 정책을 `Movie`의 일부로 구현하고 있기 때문에 할인 정책을 구성하는 **할인 금액**과 **할인 비율**을 `Movie`의 인스턴스 변수로 선언한다. (구성/합성으로 가져감) 그리고 현재 어떤 할인 정책이 적용될 영화인지를 나타내기 위한 영화 종류를 나타내는 `MovieType`을 추가한다.

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

    public Money CalculateFee(Screening screening)
    {
        ...
    }
}
```

```csharp
public enum MovieType
{
    AMOUNT_DISCOUNT, // 금액 할인 정책
    PERCENT_DISCOUNT, // 비율 할인 정책
    NONE_DISCOUNT // 할인 정책 없음
}
```

`Movie`는 먼저 `discountconditions`의 원소를 차례대로 순회하면서 `DiscountCondition` 인스턴스에게 `isSatisfiedBy`라는 메시지를 전송하여 할인 여부를 판단하도록 요청한다. 만약 할인 조건을 만족하는 `DiscountCondition` 인스턴스가 존재한다면 할인 요금을 계산하기 위해 `CalculateDiscountAmount`라는 메서드를 호출하고 만약 할인 조건이 존재하지 않는다면 기본 금액인 `fee`를 반환한다.

```csharp
public class Movie
{
    public Money CalculateMovieFee(Screening screening)
    {
        if (isDiscountable(screening))
        {
            return fee.minus(calculateDiscountAmount());
        }
        return fee;
    }

    private bool IsDiscountable(Screening screening)
    {
        return discountConditions.Any(condition => condition.IsSatisfiedBy(screening));
    }
}
```

실제로 할인 요금을 계산하는 `CalculateDiscountAmount` 메서드는 `MovieType`의 값에 따라 적절한 메서드를 호출한다. (지금은 스위치문이지만 인터페이스나 추상클래스를 통해 결합도를 낮춰야 한다.)

```csharp
public class Movie
{
    private Money CalculateDiscountAmount()
    {
        switch (movieType)
        {
            case MovieType.AMOUNT_DISCOUNT:
                return CalculateAmountDiscountAmount();
            case MovieType.PERCENT_DISCOUNT:
                return CalculatePercentDiscountAmount();
            case MovieType.NONE_DISCOUNT:
                return CalculateNoneDiscountAmount();
        }

        throw new IllegalArgumentException();
    }

    private Money CalculateAmountDiscountAmount()
    {
        return discountAmount;
    }

    private Money CalculatePercentDiscountAmount()
    {
        return fee.times(discountPercent);
    }

    private Money CalculateNoneDiscountAmount()
    {
        return Money.ZERO;
    }
}
```

여기서 조금은 고민해봐야 하는 문제가 발생하는데 영화의 할인 주체가 영화 자체마다 다르다면 지금처럼 영화에 Type에 따라 `discountAmount`값에 따라 할인되는 방법이 더 좋은 설계라고 할 수 있다. 애초에 `DiscountCondition`에게 전송한 메시지는 할인 조건을 판단하는 책임만 물었으니 `Movie`의 책임인 가격을 계산하는 것만 수행해야 한다.

만약 설계에서 할인 조건인 금액 할인 정책, 비율 할인 정책, 할인 정책 없음이 확장 가능성이 높다면 이 책임을 `DiscountCondition`에게 넘겨서 `할인 여부를 판단하라`가 아닌 `할인 정책을 적용하라`라는 메시지로 넘겨서 `CalculateDiscount`로 처리하여 자율적인 객체로 만드는 것이 효율적일 수 있다.

*항상 트레이드 오프를 생각하자.*

현재 코드로 돌아가서 `DiscountCondition`은 `할인 여부를 판단하라`라는 책임을 수행하기 위해 `IsSatisfiedBy`라는 메서드를 구현해야 한다.

```csharp
public class DiscountCondition
{
    public bool IsSatisfiedBy(Screening screening)
    {
        ...
    }
}
```

`DiscountCondition`은 은 기간 조건을 위한 요일, 시작 시간, 종료 시간과 순번 조건을 위한 상영 순번을 인스턴스 변수로 포함한다. 추가적으로 할인 조건의 종류를 인스턴스 변수로 포함한다.

```csharp
public class DiscountCondition
{
    private DiscountConditionType type;
    private int sequence;
    private DayOfWeek dayOfWeek;
    private LocalTime startTime;
    private LocalTime endTime;

    public bool IsSatisfiedBy(Screening screening)
    {
        if (type == DiscountConditionType.PERIOD)
        {
            return isSatisfiedByPeriod(screening);
        }
        return isSatisfiedBySequence(screening);
    }

    private bool isSatisfiedByPeriod(Screening screening)
    {
        return screening.GetWhenScreened().GetDayOfWeek() == dayOfWeek &&
            startTime.compareTo(screening.GetWhenScreened().toLocalTime()) <= 0 &&
            endTime.compareTo(screening.GetWhenScreened().toLocalTime()) >= 0;
    }

    private bool isSatisfiedBySequence(Screening screening)
    {
        return sequence == screening.GetSequence();
    }
}
```

`DiscountCondition`은 할인 조건을 판단하기 위해 `Screening`의 상영 시간과 상영 순번을 알아야 한다. 두 정보를 제공하는 메서드를 `Screening`에 추가한다. (멤버 변수의 접근자를 열어서 사용한다.)

```csharp
public class Screening
{
    public DateTime GetWhenScreened()
    {
        return whenScreened;
    }

    public int GetSequence()
    {
        return sequence;
    }
}
```

`DiscountConditionType`은 단순 할인 조건의 종류를 나열하는 열거형이다.

```csharp
public enum DiscountConditionType
{
    PERIOD, // 기간 조건
    SEQUENCE // 순번 조건
}
```

이제 구현이 완료했지만, 사실 이 코드는 전에 본 데이터 기반의 설계와 크게 다르지 않다. 다만, 데이터 기반의 설계는 데이터를 중심으로 설계를 진행했다면, 책임 주도 설계는 책임을 중심으로 설계를 진행했다는 점에서 차이가 있다. 하지만 다형성을 활용하지 못해 결합도가 높은 설계가 되었고, 이를 해결하기 위해 인터페이스를 활용하여 결합도를 낮추는 방법을 생각해보자.

#### DiscountCondition 개선

가장 큰 문제점은 변경에 취약한 클래스를 포함하고 있다는 것이다. (SRP 위반) 문제가 되는 클래스를 알아보자.

- 새로운 할인 조건 추가
  - `isSatisfiedBy` 메서드에 안의 `if ~ else` 구문을 수정해야 한다. 물론 새로운 할인 조건이 새로운 데이터를 요구한다면 속성도 추가되어야 한다.
- 순번 조건을 판단하는 로직 변경
  - `isSatisfiedBySequence` 메서드를 수정해야 한다. 마찬가지로 순번 조건을 판단하는 데 필요한 데이터가 변경됨에 따라 속성도 변경해야 한다.
- 기간 조건을 판단하는 로직 변경
  - `isSatisfiedByPeriod` 메서드를 수정해야 한다. 마찬가지로 기간 조건을 판단하는 데 필요한 데이터가 변경됨에 따라 속성도 변경해야 한다.

`DiscountCondition`은 하나 이상의 변경 이유를 가지기 때문에 응집도가 낮다. 응집도가 낮다는 것은 서로 연관성이 없는 기능이나 데이터가 하나의 클래스 안에 뭉쳐져 있다는 것을 의미한다. 따라서 낮은 응집도가 초래하는 문제를 해결하기 위해서는 **변경의 이유에 따라 클래스를 분리해야 한다.**

위에서 말한 `DiscountCondition`의 두 가지 변경이 코드에 영향을 미치는 시점은 서로 다를 수 있다. 이러한 설계는 응집도를 더욱 더 낮게 만들게 된다.

지금의 문제 분석 과정처럼 일반적으로 설계를 개선하는 작업(리팩터링)에서는 변경의 이유가 하나 이상인 클래스를 찾는 것으로부터 시작하는 것이 좋다. 문제는 객체지향에 갓 입문한 개발자들은 클래스 안에서 변경의 이유를 찾는 것이 생각보다 어렵다는 것이다.

이러한 문제점을 찾는 방법에는 몇 가지 패턴이 존재하는데, 이 패턴을 이해하고 나면 클래스 안에 숨겨진 변형을 생각보다 쉽게 알아낼 수 있다.

코드를 통해 변경의 이유를 파악할 수 있는 첫 번째 방법은 **인스턴스 변수가 초기화되는 시점**을 살펴보는 것이다. 응집도가 높은 클래스는 인스턴스를 생성할 때 모든 속성을 함께 초기화한다. 반면 응집도가 낮은 클래스는 객체의 속성 중 일부는 초기화되지 않은 상태로 남겨진다.

**따라서 함께 초기화되는 속성을 기준으로 코드를 분리해야 한다.**

코드를 통해 변경의 이유를 파악할 수 있는 두 번째 방법은 **메서드들이 인스턴스 변수를 사용하는 방식**을 살펴보는 것이다. 모든 메서드가 객체의 모든 속성을 사용한다면 클래스의 응집도는 높다고 볼 수 있다. 반면 메서드들이 사용하는 속성에 따라 그룹이 나뉜다면 클래스의 응집도가 낮다고 볼 수 있다.

클래스의 응집도를 높이기 위해서는 속성 그룹과 해당 그룹에 접근하는 메서드 그룹을 기준으로 코드를 분리해야 한다.

- 다음과 같은 징후라면 클래스의 응집도가 낮다고 볼 수 있다.
  - 클래스가 하나 이상의 이유로 변경돼야 한다면 응집도가 낮은 것이다. 변경의 이유를 기준으로 클래스를 분리하라
  - 클래스의 인스턴스를 초기화 하는 시점에 경우에 따라 서로 다른 속성들을 초기화하고 있다면 응집도가 낮은 것이다. 초기화되는 속성의 그룹을 기준으로 클래스를 분리하라
  - 메서드 그룹이 속성 그룹을 사용하는지 여부로 나뉜다면 응집도가 낮은 것이다. 이들 그룹을 기준으로 클래스를 분리하라.

대부분 응집도가 낮은 클래스는 이 세가지 문제를 동시에 가지는 경우가 많다.

#### 타입 분리하기

`DiscountCondition`의 가장 큰 문제는 순번 조건과 기간 조건이라는 두 개의 독립적인 타입이 하나의 클래스 안에서 공존하고 있다는 것이다. (내부에서 Enum값으로 분기문을 통해 동작함) 해결 방법중 하나는 두개의 클래스로 분리하는 것이다.

```csharp
public class PeriodCondition
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
        return screening.GetWhenScreened().GetDayOfWeek() == dayOfWeek &&
            startTime.compareTo(screening.GetWhenScreened().toLocalTime()) <= 0 &&
            endTime.compareTo(screening.GetWhenScreened().toLocalTime()) >= 0;
    }
}
```

`SequenceCondition` 클래스도 마찬가지로 구현한다. 하나의 인스턴스 변수만 포함하는 간단한 클래스로 분리된다.

```csharp
public class SequenceCondition
{
    private int sequence;

    public SequenceCondition(int sequence)
    {
        this.sequence = sequence;
    }

    public bool IsSatisfiedBy(Screening screening)
    {
        return sequence == screening.GetSequence();
    }
}
```

이렇게 클래스를 분리하게 되면 앞에서 문제되었던 부분들이 모두 해결된다. 결과적으론 개별 클래스들의 응집도가 향상되며 분리함으로써 코드 자체의 품질도 높아졌다.

하지만 분리한 이후에 또 다른 문제가 발생하는데, 수정 전에는 `Movie`에서 협력하는 클래스는 `DiscountCondition`하나 뿐이였지만  지금은 두 개의 서로 다른 인스턴스 모두와 협력해야 한다.

이 문제를 해결하기 위해 첫 번째 방법은 `Movie`내부에서 각각의 목록을 따로 유지하는 것이다. 하지만 이 방법 또한 새로운 문제를 가져온다. 첫 번째 문제는 `Movie`클래스가 두 클래스 모두에게 결합된다는 것이다. (결합도 증가) 두 번째 문제는 수정 후에 새로운 할인 조건을 추가하기가 더 어려워졌다는 것이다. (매번 추가해야 함) 마지막으로 이 메서드를 호출하도록 `IsDiscountable`메서드를 수정해야 한다.

**결과적으로 응집도는 높아졌지만, 변경과 캡슐화의 관점으론 설계의 품질이 매우 떨어지게 된다.**

#### 다형성을 통해 분리하기

`Movie`입장에서 본다면 `SequenceCondition`와 `PeriodCondition`은 아무런 차이가 없다. **모두 할일 여부를 판단하는 동일한 책임을 수행하고 있을 뿐이다.** 두 클래스가 할인 여부를 판단하기 위해 사용하는 방법이 서로 다르다는 사실은 `Movie`입장에서 전혀 중요하지 않다.

*앞서 다뤘던 `Movie`입장에선 할인 조건을 알려달라는 메시지만 전송할 뿐 처리는 해당 객체가 담당한다. (동적 객체이기에 다형성을 생각하자..)*

이 시점이 되면 **역할**의 개념을 생각해야 한다. `Movie`입장에선 두 인스턴스가 동일한 책임을 수행한다는 것은 동일한 역할을 수행한다는 것을 의미한다. **역할은 협력 구조안에서 대체 가능성을 의미하기에 역할의 개념을 사용하여 의존성을 크게 떨어트릴 수 있다.**

이는 코드에 추상화를 사용하여 나타낼 수 있는데 (추상 클래스, 인터페이스) 지금의 설계에 맞게 책임들만 정의하고 이를 연결짓는 바인딩으로 나타낸다.

할인 조건의 경우에는 `SequenceCondition`과 `PeriodCondition` 클래스가 구현을 공유할 필요는 없다. 따라서 인터페이스를 사용하여 역할을 구현한다.

```cs
public interface DiscountCondition
{
    bool isSatisfiedBy(Screening screening);
}
```

이후에 앞서 작성한 `SequenceCondition`과 `PeriodCondition`에 상속하여 해당 메서드 구현을 강제함으로써 송신자가 정한 책임을 구현할 수 있도록 강제한다.

이렇게 객체의 타입에 따라 변화하는 행동이 있다면 타입을 분리하고 변화하는 행동을 각 타입의 책임으로 할당하라는 것이다. GRASP에서는 이를 **POLYMORPHISM(다형성)**패턴이라고 부른다.

- POLYMORPHISM(다형성)
  - 객체의 타입에 따라 변화하는 로직이 있을 때 변화하는 로직을 담당할 책임은 타입을 명시적으로 정의하고 각 타입에 다형적으로 행동하는 책임을 할당하라.
  - 조건에 따른 프로그램의 기본 논리다. 프로그램을 `if ~ else` 또는 `switch ~ case`등의 조건 논리를 사용해서 설계한다면 새로운 변화가 있을 땐 무조건 논리를 수정해야 한다. 즉 강하게 결합한다.
  - *이것에 대한 개인적인 생각은 [팩터리 메서드 패턴](https://fkdl0048.github.io/patterns/Patterns_FactoryMethod/)과 같이 인터페이스의 의존성을 매우 줄이는 방법에도 두가지 방향이 있다. 논리와 인터페이스로 나뉘는데 뭐가 맞고 틀리고 보단 설계 측면에서 유리하게 가져가는 것이 유리하다.*
  - POLYMORPHISM는 객체의 타입을 검사해서 타입에 따라 여러 대안들을 수행하는 조건적인 논리를 사용하지 말라고 경고한다.

#### 변경으로부터 보호하기

두 개의 서로 다른 변경이 두 개의 서로 다른 **클래스 안으로 캡슐화된다.** 만약 새로운 할인 조건이 추가되더라도 `Movie`는 `DiscountCondition`을 통해 접근하기에 영향을 받지 않는다는 점이 가장 중요하다. 오직 해당 인터페이스를 실체화하는 클래스를 추가하는 것으로 할인 조건의 종류를 확장할 수 있다.

이처럼 변경을 캡슐화하도록 책임을 할당하는 것을 GRASP에서는 **PROTECTED VARIATIONS(변경 보호)**패턴이라고 부른다.

- PROTECTED VARIATIONS(변경 보호) 패턴
  - 객체, 서브시스템, 그리고 시스템은 변화가 예상되는 지점들을 식별하고 그 주위에 안정된 인터페이스를 형성하도록 책임을 할당하라
  - 이 패턴은 책임 할당의 관점에서 캡슐화를 설명한 것이다. "설계에서 변하는 것이 무엇인지 고려하고 변하는 개념들을 캡슐화하라

**클래스를 변경에 따라 분리하고 인터페이스를 이용해 변경을 캡슐화하는 것은 설계의 결합도와 응집도를 향상시키는 매우 강력한 방법이다.** 하나의 클래스가 여러 타입의 행동을 구현하고 있다면 클래스를 분해하고 POLYMORPHISM 패턴에 따라 책임을 분산하라, 예측 가능한 변경으로 인해 여러 클래스들이 불안정해진다면 PROTECTED VARIATIONS 패턴으로 안정적인 인터페이스 뒤로 변경을 캡슐화하라. 적절한 상황에서 두 패턴을 잘 조합하면 코드 수정의 파급 효과를 조절할 수 있고 변경과 확장에 유연한 설계를 얻을 수 있다.

#### Movie 클래스 개선하기

`Movie`역시 `DiscountCodition`와 동일한 문제가 발생하고 있다. 두 가지 타입을 하나의 클래스 안에서 다루기 때문이다. (응집도가 낮음) 해결방법 역시 다형성을 생각하여 행동을 타입별로 구별하여 내부에서 캡슐화하여 해결할 수 있다.

금액 할인 정책과 관련된 인스턴스 변수와 메서드를 옮길 클래스의 이름으로는 `AmountDiscountMovie`로 설정하고 비율 할인 정책과 관련된 인스턴스 변수와 메서드를 옮겨 담을 클래스는 `PercentDiscountMovie`로 명명하자. 할인 정책을 적용하지 않은 경우는 `NoneDiscountMovie`클래스가 처리하게 된다. *(NoneDiscountMovie는 [NULL객체 패턴](https://github.com/fkdl0048/CodeReview/blob/main/ProgrammingPatterns/NullObjectPattern/README.md))*

`DiscountCondition`의 경우에는 역할을 수행할 클래스들 사이에 구현을 공유할 필요가 없었기 때문에 인터페이스를 이용해 구현했다. **`Movie`의 경우에는 구현을 공유할 필요가 있다.** (인터페이스와 추상클래스의 차이.. 하지만 인터페이스만으로도 가능하다.) 따라서 추상클래스를 이용해 역할을 구현한다.

```cs
public abstract class Movie
{
    private string title;
    private Duration runningTime;
    private Money fee;
    private List<DiscountCondition> discountConditions;

    public Movie(string title, Duration runningTime, Money fee, List<DiscountCondition> discountConditions)
    {
        this.title = title;
        this.runningTime = runningTime;
        this.fee = fee;
        this.discountConditions = discountConditions;
    }

    public Money CalculateMovieFee(Screening screening)
    {
        if (isDiscountable(screening))
        {
            return fee.minus(calculateDiscountAmount());
        }
        return fee;
    }

    private bool IsDiscountable(Screening screening)
    {
        return discountConditions.Any(condition => condition.IsSatisfiedBy(screening)); //LINQ
    }

    abstract protected Money CalculateDiscountAmount();
}
```

변경전 클래스와 비교하면 인스턴스 변수를 사용하는 부분들이 삭제되었고 이는 `Movie`역할을 수행하는 적절한 자식 클래스로 옮길 것이다.

할인 정책의 종류에 따라 할인 금액을 계산하는 로직은 달라져야 하기에 이를 위해 `CalculateDiscountAmount` 라는 메서드를 추상 메서드로 선언함으로써 서브클래스들이 할인 금액을 계산하는 방식을 원하는대로 오버라이딩할 수 있게 했다.

*개인적인 생각으로는 Movie클래스 내부에서 이를 구현하기 보다.. 인터페이스로 구분하여 합성형태로 들고 있도록 하는 것이 좀 더 좋을 것 같다는 생각.. 한 단계 더 올라가서 DI까지 생각하면 그렇다.*

```cs
public class AmountDiscountMovie : Movie
{
    private Money discountAmount;

    public AmountDiscountMovie(string title, Duration runningTime, Money fee, Money discountAmount, List<DiscountCondition> discountConditions)
        : base(title, runningTime, fee, discountConditions)
    {
        this.discountAmount = discountAmount;
    }

    protected override Money CalculateDiscountAmount()
    {
        return discountAmount;
    }
}
```

```cs
public class PercentDiscountMovie : Movie
{
    private double discountPercent;

    public PercentDiscountMovie(string title, Duration runningTime, Money fee, double discountPercent, List<DiscountCondition> discountConditions)
        : base(title, runningTime, fee, discountConditions)
    {
        this.discountPercent = discountPercent;
    }

    protected override Money CalculateDiscountAmount()
    {
        return fee.times(discountPercent);
    }
}
```

할인 요금을 계산하기 위해서는 영화의 기본 금액인 `fee`가 필요하고 이를 서브 클래스에서 참조할 수 있도록 `GetFee`함수를 추가한다. *이 과정을 통해서 추상클래스의 나름의? 이점이 있는 것 같다. Protected로 서브클래스의 접근만 열어서 캡슐화를 좀 더 유연하게 하는 부분..*

마지막 NULL객체는 0을 반환하도록 만들면 된다.

**이제 모든 클래스의 내부 구현은 캡슐화돼 있고 모든 클래스는 변경의 이유를 오직 하나씩만 가진다. 각 클래스는 응집도가 높고 다른 클래스와 최대한 느슨하게 결합돼 있다. 클래스는 작고 오직 한 가지 일만 수행한다. 책임이 적절하게 분배되어 있다.**

4장에서 살펴본 데이터 중심 설계는 정반대의 길을 걸으며, 데이터와 관련된 클래스의 내부 구현이 인터페이스에 여과 없이 노출되기 때문에 캡슐화를 지키기 어렵다. 이로 인해 응집도가 낮고 결합도가 높으며 변경에 취약한 코드가 만들어질 가능성이 높다.

결국 처음에 작성한 도메인 구조의 모습과 크게 다르지 않게 만들어지게 되었는데, 다시한번 정리하지만 설계는 해결하고자 하는 문제에 대해서 도메인을 분석하고 (일련의 흐름, 문맥의 과정을 동적 모델을 통해 책임과 역할을 할당한다.) 이를 코드로 옮겨 적는 실질적인 설계과정을 통해 정적 모델(클래스)을 만들어 낸다.

#### 변경과 유연성

설계를 주도하는 것은 변경이다. 개발자로서 변경에 대비할 수 있는 두 가지 방법이 있다. **하나는 코드를 이해하고 수정하기 쉽도록 최대한 단순하게 설계하는 것**이며 다른 하나는 **코드를 수정하지 않고도 변경을 수용할 수 있도록 코드를 더 유연하게 만드는 것**이다.

대부분의 경우에 전자가 더 좋은 방법이지만 유사한 변경이 반복적으로 발생하고 있다면 복잡성이 상승하더라도 유연성을 추가하는 두 번째 방법이 더 좋다.

예를 들어, 영화에 설정된 할인 정책이을 실행 중에 변경할 수 있어야 한다는 요구사항이 추가된다면 현재 설계에서는 할인 정책을 구현하기 위해 **상속**을 이용하고 있기 때문에 실행 중에 영화의 할인 정책을 변경하기 위해서는 새로운 인스턴스를 생성한 후 필요한 정보를 복사해야 한다. 또한 변경 전후의 **인스턴스가 개념적으로는 동일한 객체를 가리키지만 물리적으로는 서로 다른 객체이기 때문에 식별자의 관점에서 혼란스러울 수 있다.**

이런 일은 오류가 발생하기도 쉽기에 복잡성이 높아지더라도 할인 정책을 변경을 쉽게 수용할 수 있게 코드를 유연하게 만드는 것이 더 좋은 방법이다.

해결 방법은 상속 대신 **합성**을 사용하는 것이다.

```cs
Movie movie = new Movie("타이타닉", Duration.ofMinutes(120), Money.wons(10000), new AmountDiscountPolicy(...));
movie.ChangeDiscountPolicy(new PercentDiscountPolicy(...)))
```

*이 코드도 좀 더 유연성을 기르기 위해선 DI프레임워크를 도입해도 좋을 것 같다. 실제로 앞의 불안정한 설계를 할 때 여러번 언급했던 책임의 문제점들이 고쳐진 모습이다.*

유연성에 대한 압박이 설계에 어떤 영향을 미치는지를 잘 보여주며 실제로 유연성은 의존성의 관리 문제다. 요소들 사이의 의존성의 정도가 유연성의 정도를 결정한다. **유연성의 정도에 따라 결합도를 조절할 수 있는 능력은 객체지향 개발자가 갖춰야 하는 중요한 기술 중 하나다.** *(개발이 기예라고 불리는 이유이자 아름답거나 우아한, 보기 좋은 코드가 유연한 설계로 이어진다.)*

코드 구조가 바뀌면서 도메인에 대한 관점도 함께 바뀐다. (Fixed가 아닌 지속적인 수정) 코드를 치는 순간이 실질적인 설계라고 하는 이유가 이와 같다. 만약 실제 설계가 변경된다면 도메인 모델도 그에 맞게 변경되어야 한다.

객체지향에 어느정도 익숙해지더라도 책임을 올바르게 할당하는 것은 여전히 어렵다. 사실 대부분의 객체지향 프로그래밍 언어를 이용해 절차적 프로그램을 작성하는 이유가 바로 책임 할당의 어려움에서 기인한다.

만약 이번 장을 읽고도 책임을 할당하는데 어려움을 느꼈다면 절차형 코드로 프로그램을 빠르게 작성한 후 완성된 코드를 객체지향적인 코드로 변경하는 것이다. *(테스트 코드와 리팩터링의 개념이 좀 필요하다.)*

### 느낀점

책의 흐름을 그대로 따라가며 읽었는데, 앞에서 걱정한 설계들이 뒤에서 지속적으로 수정되는 모습을 보면서 내가 맞게 생각한 부분이 많아서 좋았다. 어느정도 감이 잡힌 부분도 있었고 아직은 작은 도메인의 실습이라 방심하지 말고, 좋은 설계를 위해 더 많이 공부해야할 것 같다.

#### 논의사항

- 여러분들은 1대1로 매칭되는 객체의 경우 인터페이스를 사용하는 것에 대해서 어떻게 생각하시나요?
  - 다른 책에선 단일 인터페이스라도 명확한 인터페이스를 사용하라고 하는데 이것에 대해서 논의하면 좋을 것 같습니다.
  - [GOOD Code, BAD Code](https://github.com/fkdl0048/BookReview/blob/main/GoodCode%2CBadCode/Chapter02.md#%EC%9D%B8%ED%84%B0%ED%8E%98%EC%9D%B4%EC%8A%A4)
