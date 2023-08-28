## 8. 기능 이동

지금까지는 프로그램 요소를 생성 혹은 제거하거나 이름을 변경하는 리팩터링을 다뤘다.

여기에 더해 요소를 다른 컨텍스트로 옮기는 일 역시 리팩터링의 중요한 축이다.

### 8.1 함수 옮기기(Move Function)

```csharp
class Account
{
    public GetDraftCharge() {...}
}
```

```csharp
class AccountType
{
    public GetDraftCharge() {...}
}
```

#### 배경

모듈성이란 프로그램의 어딘가를 수정하려 할 때 해당 기능과 깊이 관련된 작은 일부만 이해해도 가능하게 해주는 능력이다.

모듈성을 높이려면 서로 연관된 요소들을 함께 묶고, 요소 사이의 연결 관계를 쉽게 찾고 이해할 수 있도록 해야 한다.

하지만 프로그램을 얼마나 잘 이해했느냐애 따라 구체적인 방법이 달라질 수 있다.

보통은 이해도가 높아질수록 소프트웨어 요소들을 더 잘 묶는 새로운 방법을 깨우치게 된다.

그래서 높아진 이해를 반여하려면 요소들을 이리저리 옮겨야 할 수 있다.

모든 함수는 컨텍스트 안에 존재한다.

객체 지향 프로그래밍의 **핵심 모듈화 컨텍스트는 클래스**다.

어떤 함수가 자신이 속한 모듈 A의 요소 보다 B모듈의 요소를 더 많이 참조한다면 모듈 B로 옮겨야 마땅하다.

*이렇게 되면 캡슐화가 좋아져서 소프트웨어의 나머지 부분은 모듈 B의 세부사항에 덜 의존하게 된다.*

#### 절차

- 선택한 함수가 현재 컨텍스트에서 사용 중인 모든 프로그램 요소를 살펴본다. 이 요소들 중에도 함께 옮겨야 할 게 있는지 고민해본다.
- 선택함 함수가 다형 메서드인지 확인한다.
- 선택한 함수를 타깃 컨텍스트로 복사한다. 타깃 함수가 새로운 터전에 잘 자리 잠도록 다듬는다.
- 정적 분석을 수행한다.
- 소스 컨텍스트에서 타깃 함수를 참조할 방법을 찾아 반영한다.
- 소스 함수를 타깃 함수의 위임 함수가 되도록 수정한다.
- 테스트한다.
- 소스 함수를 인라인할지 고민해본다.

### 8.2 필드 옮기기(Move Field)

```csharp
class Customer
{
    private Plan plan;
    private string discountRate;

    public Plan GetPlan() { return plan; }
    public string GetDiscountRate() { return discountRate; }
}
```

```csharp
class Customer
{
    private Plan plan;

    public Plan GetPlan() { return plan; }
    public string GetDiscountRate() { return plan.GetDiscountRate(); }
}
```

#### 배경

프로그램의 상당 부분이 동작을 구현하는 코드로 이뤄지지만 프로그램의 진짜 힘은 데이터 구조에서 나온다.

주어진 문제를 적합한 데이터 구조를 활용하면 동작 코드는 자연스럽게 단순하고 직관적으로 짜여진다.

반면 데이터 구조를 잘못 선택하면 아귀가 맞지 않는 데이터를 다루기 위한 코드로 범벅이 된다.

이해하기 어려운 코드가 만들어지는 데서 끝나지 않고, 데이터 구조 자체도 그 프로그램이 어떤 일을 하는지 파악하기 어렵게 만든다.

그래서 데이터 구조가 매우 중요하지만, 훌룡한 프로그램이 갖춰야 할 다른 요인들과 마찬가지로, 제대로 하기가 어렵다.

현재 데이터 구조가 적절치 않다고 판단되면 바로 수정해야 한다. (이후에는 늦다.)

고치지 않고 데이터 구조에 남겨진 흠들은 우리 머릿속을 혼란스럽게 하고 훗날 작성하게 될 코드를 더욱 복잡하게 만든다.

`필드 옮기기`리팩터링은 대체로 더 큰 변경의 일환으로 수행된다.

예컨대 필드 하나를 잘 옮기면, 그 필드를 사용하던 많은 코드가 원래 위치에서 사용하는 게 더 수월할 수 있다.

그렇다면 리팩타링을 마저 호출 진행하여 호출 코드들까지 모두 변경한다.

#### 절차

- 소스 필드가 캡슐화되어 있지 않다면 캡슐화한다.
- 테스트한다.
- 타깃 객체에 필드를 생성한다.
- 정적 검사를 수행한다.
- 소스 객체에서 타깃 객체를 참조할 수 있는지 확인한다.
- 접근자들이 타깃 필드를 사용하도록 수정한다.
- 테스트한다.
- 소스 필드를 제거한다.
- 테스트한다.

#### 예시

```csharp
public class Customer
{
    private string name;
    private int discountRate;
    private CustomerContract contract;

    public Customer(string name, int discountRate)
    {
        this.name = name;
        this.discountRate = discountRate;
        this.contract = new CustomerContract(DateTime.Now);
    }

    public int GetDiscountRate()
    {
        return discountRate;
    }

    public void BecomePreferred()
    {
        ...
    }

    public void ApplyDiscount(int discountRate)
    {
        ...
    }
}

public class CustomerContract
{
    private DateTime startDate;

    public CustomerContract(DateTime startDate)
    {
        this.startDate = startDate;
    }

    public DateTime GetStartDate()
    {
        return startDate;
    }
}
```

여기서 할인율을 뜻하는 `discountRate` 필드를 `Customer`에서 `CustomerContract`로 옮기고 싶다.

```csharp
public class Customer
{
    private string name;
    private CustomerContract contract;

    public Customer(string name, int discountRate)
    {
        this.name = name;
        this.contract = new CustomerContract(DateTime.Now, discountRate);
    }

    public int GetDiscountRate()
    {
        return contract.GetDiscountRate();
    }

    public void BecomePreferred()
    {
        ...
    }

    public void ApplyDiscount(int discountRate)
    {
        ...
    }
}

public class CustomerContract
{
    private DateTime startDate;
    private int discountRate;

    public CustomerContract(DateTime startDate, int discountRate)
    {
        this.startDate = startDate;
        this.discountRate = discountRate;
    }

    public DateTime GetStartDate()
    {
        return startDate;
    }

    public int GetDiscountRate()
    {
        return discountRate;
    }
}
```

### 8.3 문장을 함수로 옮기기(Move Statements into Function)

```csharp
result.push("<p>제목: " + photo.title + "</p>");
result.concat(Format(photo));

public string Format(Photo photo)
{
    return "<p>위치: " + photo.location + "</p>";
}
```

```csharp
result.concat(FormatPhoto(photo));

public string FormatPhoto(Photo photo)
{
    return "<p>제목: " + photo.title + "</p>" 
    + "<p>위치: " + photo.location + "</p>";
}
```

#### 배경

중복 재고는 코드를 건강하게 관리하는 가장 효과적인 방법 중 하나다.

예컨대 특정 함수를 호출하는 코드가 나올 때마다 그 앞이나 뒤에서 똑같은 코드가 추가로 실행되는 모습을 보면 중복 재고가 있다는 신호다.

이 부분은 `함수로 추출하기`와 비슷하며 절차도 똑같다 (5,6번 제외)

#### 절차

- 반복 코드가 함수 호출 부분과 멀리 떨어져 있다면 문장 슬라이드하기를 적용해 근처로 옮긴다.
- 타깃 함수를 호출하는 곳이 한 곳뿐이면, 단순히 소스 위치에서 해당 코드를 잘라내어 피호출 함수로 복사하고 테스트한다. 이 경우라면 나머지 단계를 스킵한다.
- 호출자가 둘 이상이면 호출자 중 하나에서 '타깃 함수 호출 부분과 그 함수로 옮기려는 문장들을 함께'다른 함수로 추출한다. 추출한 함수에 기억하기 쉬운 임시 이름을 붙인다.
- 다른 호출자 모두가 방금 추출한 함수를 사용하도록 수정한다. 하나씩 수정할 때마다 테스트한다.
- 모든 호출자가 새로운 함수를 사용하게 되면 원래 함수를 새로운 함수 안으로 인라인한 후 원래 함수를 제거한다.
- 새로운 함수의 이름을 원래 함수의 이름으로 바꿔준다.

### 8.4 문장을 호출한 곳으로 옮기기(Move Statements to Callers)

```csharp
result.concat(FormatPhoto(photo));

public string FormatPhoto(Photo photo)
{
    return "<p>제목: " + photo.title + "</p>" 
    + "<p>위치: " + photo.location + "</p>";
}
```

```csharp
result.push("<p>제목: " + photo.title + "</p>");
result.concat(Format(photo));

public string Format(Photo photo)
{
    return "<p>위치: " + photo.location + "</p>";
}
```

#### 배경

*`문장을 함수로 옮기기`와 반대 방향으로 적용하는 리팩터링이다.*

함수는 프로그래머가 쌓아 올리는 추상화의 기본 빌딩 블록이다.

하지만 추상화라는 것이 그 경계를 항상 올바르게 긋기가 만만치 않다.

그래서 코드베이스의 기능 범위가 달라지면 추상화의 경계도 움직이게 된다.

함수 관점에서 생각해보면, 초기에는 응집도 높고 한 가지 일만 수행하던 함수가 어느새 둘 이상의 다른 일을 수행하게 바뀔 수 있다는 것이다.

#### 절차

- 호출자가 한두 개뿐이고 피호출 함수도 간단한 단순한 상황이면, 피호출 함수의 처음 줄을 잘라내어 호출자로 복사해 넣는다. 테스트만 통과하면 리팩터링은 여기서 끝이다.
- 거 복잡한 상황에서는, 이동하지 `않길` 원하는 모든 문장을 함수로 추출한 다음 검색하기 쉬운 임시 이름을 지어준다.
- 원래 함수를 인라인한다.
- 추출된 함수의 이름을 원래 함수의 이름으로 변경한다.

### 8.5 인라인 코드를 함수 호출로 바꾸기(Replace Inline Code with Function Call)

```csharp
int basePrice = quantity * itemPrice;
if (basePrice > 1000)
    return basePrice * 0.95;
else
    return basePrice * 0.98;
```

```csharp
int basePrice = quantity * itemPrice;
return DiscountedPrice(basePrice);

public int DiscountedPrice(int basePrice)
{
    if (basePrice > 1000)
        return basePrice * 0.95;
    else
        return basePrice * 0.98;
}
```

#### 배경

함수는 여러 동작을 하나로 묶어준다. 그리고 함수의 이름이 코드의 동작 방식보다 목적을 말해주기 때문에 함수를 활용하면 코드를 이해하기가 쉬워진다.

이미 존재하는 함수와 똑같은 일을 하는 인라인 코드를 발견하면 보통은 해당 코드를 함수 호출로 대체하길 원할 것이다.

예외가 있다면, 순전히 우연히 비슷한 코드가 만들어졌을 때뿐이다.

즉, 기존 함수의 코드를 수정하더라도 인라인 코드의 동작은 바뀌지 않아야 할 때뿐이다.

이 경우인가를 판단하는 데는 함수의 이름이 힌트가 된다.

#### 절차

- 인라인 코드를 함수 호출로 대체한다.
- 테스트한다.

> 함수 추출하기와 차이점은 대체할 함수가 이미 존재하는지에 대한 여부다.  
> 아직 없어서 새로 만들어야 한다면 함수 추출하기를 적용하고, 이미 존재한다면 인라인 코드를 함수 호출로 바꾸기를 적용한다.

### 8.6 문장 슬라이드하기(Slide Statements)

```csharp
var pricingPlan = RetrievePricingPlan();
var order = RetrieveOrder();
int charge;
var chargePerUnit = pricingPlan.GetUnitCharge();
```

```csharp
var pricingPlan = RetrievePricingPlan();
var chargePerUnit = pricingPlan.GetUnitCharge();
var order = RetrieveOrder();

int charge;
```

#### 배경

관련된 코드들이 가까이 모여 있다면 이해하기가 더 쉽다.

예컨대 하나의 데이터 구조를 이용하는 문장들은 한데 모여 있어야 좋다.(읽기도, 수정하기도)

**관련 코드끼리 모으는 작업은 다른 리팩터링의 준비 단계로 자주 행해진다.**

#### 절차

- 코드 조각을 이동할 목표 위치를 찾는다. 코드 조각이 원래 위치와 목표 위치 사이의 코드들을 훑어보면서, 조각을 모으고 나면 동작이 달라지는 코드가 있는지 살핀다. 다음과 같은 간섭이 있다면 이 리팩터링을 포기한다.
  - 코드 조각에서 참조하는 요소를 선헌하는 문장 앞으로는 이동할 수 없다.
  - 코드 조각을 참조하는 요소의 뒤로는 이동할 수 없다.
  - 코드 조각에서 참조하는 요소를 수정하는 문장을 건너뛰어 이동할 수 없다.
  - 코드 조각이 수정하는 요소를 참조하는 요소를 건너뛰어 이동할 수 없다.
- 코드 조각을 원래 위치에서 잘라내어 목표 위치에 붙여 넣는다.
- 테스트한다.

만약 테스트가 실패한다면 더 작게 나눠서 시도해봐라.

### 8.7 반복문 쪼개기(Split Loop)

```csharp
int averageAge = 0;
int totalSalary = 0;

foreach (var p in people)
{
    averageAge += p.age;
    totalSalary += p.salary;
}

averageAge = averageAge / people.Length;
```

```csharp
int averageAge = 0;
foreach (var p in people)
{
    averageAge += p.age;
}

int totalSalary = 0;
foreach (var p in people)
{
    totalSalary += p.salary;
}

averageAge = averageAge / people.Length;
```

#### 배경

종종 반복문 하나에서 두 가지 일을 수행하는 모습을 보게 된다.

그저 두 일을 한꺼번에 처리할 수 있다는 이유에서 말이다.

하지만 이렇게 반복문을 수정해야 할 때마다 두 가지 일 모두를 잘 이해하고 진행해야 한다.

반대로 각각의 바복문으로 분리해두면 수정할 동작 하나만 이해하면 된다.

반복문을 분리하면 사용하기도 쉬워진다. 한 가지 값만 계산하는 반복문이라면 그 값만 곧바로 반환할 수 있다.

반면 여러 일을 수행하는 반복문이라면 구조체를 반환하거나 지역 변수를 활용해야 한다.

참고로 반복문 쪼개기는 서로 다른 일들이 한 함수에서 이뤄지고 있다는 신호일 수 있고, 그래서 반복문 쪼개기와 함수 추출하기는 연이어 수행하는 일이 낮다.

*리팩터링 != 최적화*

#### 절차

- 반복문을 복제해 두 개로 만든다.
- 반복문이 중복되어 생기는 부수효과를 제거한다.
- 테스트한다.
- 완료됐으면, 각 반복문을 함수로 추출할지 고민해본다.

#### 예시

```csharp
int averageAge = 0;
int totalSalary = 0;

foreach (var p in people)
{
    averageAge += p.age;
    totalSalary += p.salary;
}

averageAge = averageAge / people.Length;
```

```csharp
int averageAge = 0;
foreach (var p in people)
{
    averageAge += p.age;
}

int totalSalary = 0;
foreach (var p in people)
{
    totalSalary += p.salary;
}

averageAge = averageAge / people.Length;
```

### 8.8 반복문을 파이프라인으로 바꾸기(Replace Loop with Pipeline)

```csharp
List<string> names = new List<string>();
foreach (var person in input)
{
    if (person.Job == "programmer")
    {
        names.Add(person.Name);
    }
}
```

```csharp
List<string> namesLinq = input
    .Where(person => person.Job == "programmer")
    .Select(person => person.Name)
    .ToList();
```

#### 배경

언어가 계속 발전함에 따라 더 나은 구조를 제공하는 쪽으로 발전해왔다.

반복문 대신에 논리를 파이프라인으로 표현하면 이해하기 쉬워진다.

*C#은 LINQ를 사용해서 쿼리식을 표현하는데 초기에 컨벤션으로 사용하지 말자고 합의보는 경우도 종종 있다고 한다.*

#### 절차

- 반복문에서 사용하는 컬렉션을 가리키는 변수를 하나 만든다.
- 반복문의 첫 줄부터 시작해서, 각각의 단위 행위를 적절한 컬렉션 파이프라인 연산으로 대체한다.
- 반복문의 모든 동작을 대체했다면 반복문 자체를 지운다.

### 8.9 죽은 코드 제거하기(Remove Dead Code)

```csharp
if (false)
{
    Console.WriteLine("unreachable code");
}
```

```csharp
...
```

#### 배경

*빌드전 Debug코드 제거하기 등..*

코드가 더 이상 사용되지 않는다면 지워야 한다.

#### 절차

- 죽은 코드를 외부에서 참조할 수 있는 경우라면 혹시라도 호출하는 곳이 있는지 확인한다.
- 없다면 죽은 코드를 제거한다.
- 테스트한다.

### 느낀점

- 이번 장은 이미 리팩터링 단계보다 그 전 단계에서 이뤄질 수 있는 작업 같다는 생각이 든다.
- 기능을 이동시키는 부분이 제대로 실행되려면 참조가 복잡하지 않고, 모듈화가 선행되어야 편할 것 같다는 느낌이 먼저 드는 것 같다. (엉킨 실타래)

#### 논의사항

과거 죽은 코드를 제거한다고 되게 많이 정리했다가 직렬화로 참조된 코드까지 지워버러서 곤란했던 경험이 있습니다.

그때의 경험으로 게임잼이나 단기 프로젝트말고는 대부분 코드레벨에서 데이터를 참조하고 다룰려고 하는 편입니다..

혹시 죽은 코드를 제거하실 때 어떤 방식으로 접근하시는지 궁금합니다.
