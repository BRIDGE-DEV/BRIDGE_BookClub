## 9. 데이터 조직화

데이터 구조는 프로그램의 중요한 역할을 수행하니 데이터 구조에 집중한 리팩터링만 모아놨다.

### 9.1 변수 쪼개기

```csharp
int temp = 2 * (height + width);
Console.WriteLine(temp);
temp = height * width;
Console.WriteLine(temp);
```

```csharp
const int perimeter = 2 * (height + width);
Console.WriteLine(perimeter);
const int area = height * width;
Console.WriteLine(area);
```

#### 배경

변수는 다양한 용도로 쓰이는데, 가끔 변수에 여러 번 값을 대입할 수밖에 없는 상황도 있다.

예를 들어 반복문의 경우 `i`라는 변수는 루프변수로 반복문을 반복할때 마다 값이바뀐다.

수집 변수의 경우는 메서드가 동작하는 중간중간 값을 저장한다.

그 외에도 변수는 긴 코드의 결과를 저장했다가 나중에 쉽게 참고하려는 목적으로 흔히 쓰인다.

**이런 변수에는 값을 단 한 번만 대입해야 한다.**

대입이 두 번 이상 이뤄진다면 여러 가지 역할을 수행한다는 신호다.

역할이 둘 이상인 변수가 있다면 쪼개야 한다.

예외는 없다.

역할 하나당 변수 하나다.

여러 용도로 쓴 변수는 코드를 읽는 이에게 커다란 혼란을 주기 때문이다.

#### 절차

- 변수를 선언한 곳과 값을 처음 대입하는 곳에서 변수 이름을 바꾼다.
- 가능하면 이때 불변으로 선언한다.
- 이 변수에 두 번째로 값을 대입하는 곳 앞까지의 모든 참조를 새로운 변수 이름으로 바꾼다.
- 두 번째 대입 시 변수를 원래 이름으로 다시 선언한다.
- 테스트한다.
- 반복한다.

#### 예시

> 이번 예는 해기스라는 음식이 다른 지역으로 전파된 거리를 구하는 코드를 살펴본다.

```csharp
public void DistanceTravelled(Scenario scenario, int time)
{
    int result;
    int acc = scenario.primaryForce / scenario.mass; // 가속도 = 힘 / 질량
    int primaryTime = Math.Min(time, scenario.delay);
    result = 0.5 * acc * primaryTime * primaryTime; // 전파된 거리
    int secondaryTime = time - scenario.delay;
    if (secondaryTime > 0) // 두 번째 힘을 반영해 다시 계산
    {
        int primaryVelocity = acc * scenario.delay;
        acc = (scenario.primaryForce + scenario.secondaryForce) / scenario.mass;
        result += primaryVelocity * secondaryTime + 0.5 * acc * secondaryTime * secondaryTime;
    }
    return result;
}
```

이 함수를 살펴보면 acc변수에 값이 두 번 대입되는 것을 알 수 있다.

즉, 역할이 두개라는 신호로 하나는 첫 번째 힘을 유발한 가속도를 저장하는 역할이고, 다른 하나는 두 번째 힘까지 반영된 후의 가속도를 저장하는 역할이다.

여기서 사실 최근의 IDE는 변수 이름을 일괄변경하는 고급진 기술을 가지고 있다.

```csharp
public void DistanceTravelled(Scenario scenario, int time)
{
    int result;
    const int primaryAcceleration = scenario.primaryForce / scenario.mass; // 가속도 = 힘 / 질량
    int primaryTime = Math.Min(time, scenario.delay);
    result = 0.5 * primaryAcceleration * primaryTime * primaryTime; // 전파된 거리
    int secondaryTime = time - scenario.delay;
    if (secondaryTime > 0) // 두 번째 힘을 반영해 다시 계산
    {
        int primaryVelocity = primaryAcceleration * scenario.delay;
        const int secondaryAcceleration = (scenario.primaryForce + scenario.secondaryForce) / scenario.mass;
        result += primaryVelocity * secondaryTime + 0.5 * secondaryAcceleration * secondaryTime * secondaryTime;
    }
    return result;
}
```

### 9.2 필드 이름 바꾸기

```csharp
public class Organization
{
    public string Name { get; set; }
}
```

```csharp
public class Organization
{
    public string Title { get; set; }
}
```

#### 배경

다시 한번 강조하지만 이름은 중요하다.

그리고 특히 프로그램 곳곳에서 쓰이는 레코드 구조체의 필드 이름들은 더욱 중요하다.

데이터 구조가 중요하다는 이유는 다들 알테니 이러한 구조를 잘 관리하는 것도 중요하다.

#### 절차

- 레코드의 유효 범위가 제한적이라면 필드에 접근하는 모든 코드를 수정한 후 테스트한다.
- 레코드가 캡슐화되지 않았다면 먼저 캡슐화를 한다.
- 캡슐화된 객체 안의 private 필드명을 변경하고, 그에 맞게 내부 메서드들을 수정한다.
- 테스트한다.
- 생성자의 매개변수 중 필드와 이름이 겹치는 게 있다면 함수 선언 바꾸기로 변경한다.
- 접근자들의 이름도 바꿔준다.

#### 예시

```csharp
public class Organization
{
    public string Name { get; set; }
}
```

```csharp
public class Organization
{
    public string Title { get; set; }
}
```

여기서 `Name`을 `Title`로 바꾸는 것은 쉽다.

이 객체가 코드 베이스 곳곳에서 사용되어 `Name`이라는 이름이 충돌이 날 수 있다면, 먼저 캡슐화를 한다.

```csharp
public class Organization
{
    private string _title;
    public string Title
    {
        get => _title;
        set => _title = value;
    }
}
```

사실 이 부분에서 캡슐화만 진행해도 사용되는 부분이 전부 드러나고 해당 코드를 변경하는게 더 유리해 보인다.

백개라고 해서 내부 클래스에서 name과 title을 둘다 사용가능하게 하는 것은 비효율적이라고 판단된다.

### 9.3 파생 변수를 질의 함수로 바꾸기

```csharp
get
{
    return _quantity * _itemPrice -
        Math.Max(0, _quantity - 500) * _itemPrice * 0.05 +
        Math.Min(_quantity * _itemPrice * 0.1, 100.0);
}
```

```csharp
get
{
    return BasePrice - QuantityDiscount + Shipping;
}
```

#### 배경

가변 데이터는 소프트웨어에 문제를 일으키는 경우 가장 큰 골칫거리에 속한다.

가변 데이터는 서로 다른 두 코드를 이상한 방식으로 결합하기도 하는데, 예컨대 한 쪽 코드에서 수정한 값이 연쇄 효과를 일으켜 다른 쪽 코드에 원인을 찾기 어려운 문제를 야기하기도 한다.(사이드 이펙트)

**그렇다고 가변 데이터를 완전히 배제하기란 현실적으로 불가능할 때가 많지만, 가변 데이터의 유효 범위를 가능한 한 좁혀야 한다고 힘주어 주장해본다.**

효과가 좋은 방법으로, 값을 쉽게 계산해낼 수 있는 변수들을 모두 제거할 수 있다.

계산 과정을 보여주는 코드 자체가 데이터의 의미를 더 분명히 드러내는 경우도 자주 있으며 변경된 값을 깜빡하고 결과 변수에 반영하지 않는 실수를 막아준다.

여기에는 합당한 예외가 존재하는데 피연산자 데이터가 불변이라면 계산 결과도 일정하므로 역시 불변으로 만들 수 있다. (보장된다.)

그래서 새로운 데이터 구조를 생성하는 변형 연산이라면 비록 계산 코드로 대체할 수 있더라도 그대로 두는 편이 좋다.

#### 절차

- 변수 값이 갱신되는 지점을 모두 찾는다.
- 해당 변수값을 계산해주는 함수를 만든다.
- 해당 변수가 사용되는 모든 곳에 어서션을 추가하여 함수의 계산 결과가 변수의 값과 같은지 확인한다.
- 테스트한다.
- 변수를 읽는 코드를 모두 함수 호출로 대체한다.
- 테스트한다.
- 변수를 선언하고 갱신하는 코드를 죽은 코드 제거하기로 없앤다.

### 9.4 참조를 값으로 바꾸기

```csharp
public class Product
{
    public void ApplyDiscount(int discount)
    {
        this.price.amount -= discount;
    }
}
```

```csharp
public class Product
{
    public void ApplyDiscount(int discount)
    {
        this.price = new Money(this.price.amount - discount);
    }
}
```

#### 배경

객체를 다른 객체에 중첩하면 내부 객체를 참조 혹은 값으로 취급할 수 있다.

참조냐 값이냐의 차이는 내부 객체에 속성을 갱신하는 방식에서 가장 극명하게 드러난다.

참조로 다루는 경우에는 내부 객체는 그대로 둔 채 그 객체의 속성만 갱신하며, 값으로 다루는 경우에는 새로운 속성을 담은 객체로 기존 내부 객체를 통째로 대체한다.

필드를 값으로 다룬다면 내부 객체의 클래스를 수정하여 값 객체로 만들 수 있다.

값 객체는 대체로 자유롭게 활용하기 좋은데, 특히 불변이기 때문이다.

불변 데이터 값은 프로그램 외부로 건네줘도 나중에 그 값이 바뀌거나 영향을 주지 않을까 걱정하지 않아도 된다.

값을 복제해 이곳저곳 활용하더라도 서로 간의 참조를 관리하지 않아도 된다.

*값 객체는 분산 시스템과 동시성 시스템에서 특히 유용하다.*

#### 절차

- 후보 클래스가 불변인지, 혹은 불변이 될 수 있는지 확인한다.
- 각각의 세터를 하나씩 제거한다.
- 이 값 객체의 필드들을 사용하는 동치성 비교 메서드를 만든다.

#### 예시

```csharp
public class Person
{
    private TelephoneNumber telephoneNumber;

    pulbic Person()
    {
        this.telephoneNumber = new TelephoneNumber();
    }

    public string GetOfficeAreaCode()
    {
        return this.telephoneNumber.areaCode;
    }

    public void SetOfficeAreaCode(string arg)
    {
        this.telephoneNumber.areaCode = arg;
    }

    public string GetOfficeNumber()
    {
        return this.telephoneNumber.number;
    }

    public void SetOfficeNumber(string arg)
    {
        this.telephoneNumber.number = arg;
    }
}

public class TelephoneNumber
{
    public string areaCode;
    public string number;
}
```

이 코드에서 참조를 값으로 변경하기 위해선 가장 먼저 `TelephoneNumber` 클래스를 불변으로 만들어야 한다.

```csharp
public class TelephoneNumber
{
    private string _areaCode;
    private string _number;

    public TelephoneNumber(string areaCode, string number)
    {
        this._areaCode = areaCode;
        this._number = number;
    }

    public string GetAreaCode()
    {
        return this._areaCode;
    }

    public string GetNumber()
    {
        return this._number;
    }
}
```

이후 세터를 호출하는 부분에서 전화번호를 매번 다시 대입하도록 바꿔야 한다. (Set에서 항상 새로운 객체를 할당한다면 이는 불변이 보장됨)

```csharp
public class Person
{
    private TelephoneNumber telephoneNumber;

    pulbic Person()
    {
        this.telephoneNumber = new TelephoneNumber();
    }

    public string GetOfficeAreaCode()
    {
        return this.telephoneNumber.GetAreaCode();
    }

    public void SetOfficeAreaCode(string arg)
    {
        this.telephoneNumber = new TelephoneNumber(arg, this.telephoneNumber.GetNumber());
    }

    public string GetOfficeNumber()
    {
        return this.telephoneNumber.GetNumber();
    }

    public void SetOfficeNumber(string arg)
    {
        this.telephoneNumber = new TelephoneNumber(this.telephoneNumber.GetAreaCode(), arg);
    }
}
```

### 9.5 값을 참조로 바꾸기

```csharp
var customer = new Customer(customerData);
```

```csharp
var customer = customerRepository.Get(customerData.id);
```

#### 배경

하나의 데이터 구조 안에 논리적으로 똑같은 제3의 데이터 구조를 참조하는 레코드가 여러개 있을 때가 있다.

예컨대 주문 목록을 읽다 보면 같은 고객이 요청한 주문이 여러 개 섞여 있을 수 있다.

이때 고객을 값으로도, 혹은 참조로도 다룰 수 있다.

**값으로 다루게 다룬다면 고객 데이터가 각 주문에 복사되고, 참조로 다룬다면 여러 주문이 단 하나의 데이터 구조를 참조하게 된다.**

고객 데이터를 갱신할 일이 없다면 어느 방식이든 상관없다.

같은 데이터를 여러 벌 복사하는게 조금 꺼림칙할지 모르지만, 별달리 문제되는 경우는 많지 않아서 흔히 사용되는 방식이다.

복사본이 많이 생겨서 가끔은 메모리가 부족할 수도 있지만, 다른 성능 이슈와 마찬가지로 아주 드문 일이다.

논리적으로 같은 데이터를 물리적으로 복제해 사용할 때 가장 크게 문제되는 상황은 그 데이터를 갱신해야 할 때다.

모든 복제본을 찾아서 빠짐없이 갱신해야 하며, 하나라도 놓치면 데이터 일관성이 깨져버린다.

이런 상황이라면 데이터를 참조로 바꿔주는 것이 좋다. (데이터가 하나면 갱신된 내용이 해당 고객의 주문 모두에 곧바로 반영되기 때문이다.)

값을 참조로 바꾸면 엔티티 하나당 객체도 단 하나만 존재하게 되는데, 그러면 보통 이런 객체들을 한데 모아놓고 클라이언트의 접근을 관리해주는 일종의 저장소가 필요해진다.

각 엔티티를 표현하는 객체를 한 번만 만들고, 객체가 필요한 곳에서는 모두 이 저장소로부터 얻어 쓰는 방식이 된다.

#### 절차

- 같은 부류에 속하는 객체들을 보관할 저장소를 만든다.
- 생성자에서 이 부류의 객체들 중 특정 객체를 찾아내는 방법이 있는지 확인한다. (key 등등)
- 호스트 객체의 생성자들을 수정하여 필요한 객체를 이 저장소에서 찾도록 한다.

#### 예시

```csharp
public class Order
{
    public Order(Data data)
    {
        this.number = data.number;
        this.customer = new Customer(data.customer);
    }

    public Customer GetCustomer()
    {
        return this.customer;
    }
}

public class Customer
{
    public Customer(Data data)
    {
        this.id = data.id;
    }
}
```

이런 방식으로 생성한 고객 객체는 값이다.

고객 ID가 123인 주문을 다섯 개 생성한다면 독립된 고객 객체가 다섯 개 만들어진다.

이 중 하나를 수정하더라도 나머지 네 개에는 반영되지 않는다.

이 처럼 고객 객체의 중복이 발생할 수 있는 가능성이 있다면 고객 객체를 참조로 바꾸는 것이 좋다.

설상가상으로 불변이 보장되지 않기 때문에 스파게티 코드의 조짐이 보인다.

항상 물리적으로 똑같은 객체를 사용하고 싶다면 먼저 이 유일한 객체를 저장해둘 곳이 있어야 한다.

객체를 어디에 저장해야 할지는 애플리케이션에 따라 다르겠지만, 간단한 상황이라면 저장소 객체를 사용한다.

```csharp
public class Order
{
    public Order(Data data)
    {
        this.number = data.number;
        this.customer = CustomerRepository.Get(data.customerId);
    }

    public Customer GetCustomer()
    {
        return this.customer;
    }
}

public class Customer
{
    public Customer(Data data)
    {
        this.id = data.id;
    }
}
```

이렇게 특정 주문과 관련된 고객 정보를 갱신하면 같은 고객을 공유하는 주문 모두에서 갱신된 데이터를 사용하게 된다.

### 9.6 매직 리터럴 바꾸기

```csharp
public int PotentialEnergy(double mass, double height)
{
    return mass * 9.81 * height;
}
```

```csharp
public const double Gravity = 9.81;

public int PotentialEnergy(double mass, double height)
{
    return mass * Gravity * height;
}
```

#### 배경

매직 리터럴이란 소스 코드에 등장하는 일반적인 리터럴 값을 말한다.

예컨대 움직임을 계산하는 코드에서라면 9.80665라는 숫자가 산재해 있는 모습을 목격할 수 있다.

이 의미를 이해하고 알고 있더라도 코드 자체에서 뜻을 명확하게 해주는 것이 좋다.

상수를 정의하고 숫자 대신 상수를 사용하도록 바꾸면 될 것이다.

### 느낀점

개인적으로 데이터 불변에 관련해서 9.4, 9.5가 되게 흥미로웠다.

생각하지 못했던 부분도 있어서 시간이 생긴다면 한번 더 보게될 것 같은 내용이었다.

#### 논의사항

작성하신 코드 중에서 9.4, 9.5를 적용하면 좋아질 수 있는 구조가 보이시나요?
