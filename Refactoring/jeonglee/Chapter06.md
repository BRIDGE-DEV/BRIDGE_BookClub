## 6. 기본적인 리팩터링

카탈로그의 첫머리는 가장 기본적이고 많이 사용해서 제일 먼저 배워야 하는 리팩터링들로 시작한다.

### 6.1 함수 추출하기(Extract Function)

- 반대 리팩터링: 함수 인라인하기

```csharp
void PrintOwing()
{
    PrintBanner();

    // 미해결 채무(outstanding)를 계산한다.
    var outstanding = CalculateOutstanding();

    // 세부 사항을 출력한다.
    Console.WriteLine($"고객명: {name}");
    Console.WriteLine($"채무액: {outstanding}");
}
```

```csharp
void PrintOwing()
{
    PrintBanner();
    PrintDetails(GetOutstanding());
}

void PrintDetails(double outstanding)
{
    Console.WriteLine($"고객명: {name}");
    Console.WriteLine($"채무액: {outstanding}");
}
```

#### 배경

함수 추출하기는 매우 많이 사용되는 리팩터링 중 하나로 코드 조각을 찾아 무슨 일을 하는지 파악한 다음, 독립된 함수로 추출하고 목적에 맞는 이름을 붙인다.

*여기서 함수란, 객체지향 언어에서는 메서드, 절차형 언어의 프로시저/서브루틴에도 똑같이 해당되는 말이다.*

코드를 언제 독립된 함수로 묶어야 할지에 관한 의견은 수없이 많다.(길이, 중복, 화면 기준 등등)

하지만 **목적과 구현을 분리**하는 방식이 가장 합리적인 기준으로 생각된다.

코드를 보고 무슨일을 하는지 한참 걸린다면 그 부분을 함수로 추출한 뒤 '무슨 일'에 걸맞는 이름을 짓는다.

이렇게 해두면 나중에 코드를 다시 읽을 때 함수의 목적이 눈에 확 들어오고, 본문 코드(그 함수가 목적을 이루기 위해 구체적으로 수행하는 일)에 대해서는 더 이상 신경 쓸 일이 거의 없다.

짧은 함수를 만드는 것에 두려움을 가지면 안된다.

이런 짧은 함수의 이점은 이름을 잘 지어야만 발휘되므로 이름 짓기에 특별히 신경 써야 한다.

이름을 잘 짓기까지는 어느 정도 훈련이 필요하다.

하지만 일단 요령을 터득한 후에는 별도 문서 없이 코드 자체만으로 내용을 충분히 설명되게 만들 수 있다.

#### 절차

- 함수를 새로 만들고 목적을 잘 드러내는 이름을 붙인다. ('어떻게'가 아닌 '**무엇을**' 하는지가 드러나야 한다.)
  - 대상 코드가 함수 호출문 하나처럼 매우 간단하더라도 함수로 뽑아서 목적이 더 잘 드러나는 이름을 붙일 수 있다면 추출한다.
  - 이런 이름이 떠오르지 않는다면 함수로 추출하면 안된다는 신호다.
  - 하지만 추출하는 과정에서 좋은 이름이 떠오를 수도 있으니 처음부터 최선의 이름부터 짓고 시작할 필요는 없다. **그 과정에서 조금이라도 깨달은 게 있다면 시간 낭비는 아니다.**
- 추출할 코드를 원본 함수에서 복사하여 새 함수에 붙여넣는다.
- 추출할 코드 중 원본 함수의 지역 변수를 참조하거나 추출한 함수의 유효범위를 벗어나는 변수는 없는지 검사한다. 있다면 매개변수로 전달한다.
  - 원본 함수의 중첩 함수로 추출할 때는 이런 문제가 생기지 않는다.
  - 일반적으로 함수에는 지역 변수와 매개변수가 있기 마련이다. 가장 일반적인 처리 방법은 모두 인수로 전달하는 것(그렇게 매력적인 방법은 아니라고 판단된다.)
  - 추출한 코드에서만 사용하는 변수가 추출한 함수 밖에 선언되어 있다면 추출한 함수 안에서 선언 하도록 수정한다.
- 변수를 다 처리했다면 컴파일한다.
  - 컴파일되는 언어로 개발 중이라면 변수를 모두 처리하고 나서 한번 컴파일해보자. 제대로 처리하지 못한 변수를 찾는 데 도움될 때가 많다.
- 원본 함수에서 추출한 코드 부분을 새로 만든 함수를 호출하는 문장으로 바꾼다(즉, 추출한 함수로 일을 위임한다.)
- 테스트한다.
- 다른 코드에 방금 추출한 것과 비슷한 코드가 없는지 살핀다. 있다면 방금 추출한 새 함수를 호출하도록 바꾼다.
  - 중복 혹은 비슷한 코드를 찾아주는 리팩터링 도구도 있다.

#### 예시: 유효범위를 벗어나는 변수가 없을 때

아주 간단한 코드여서 함수 추출하기가 쉽다. (해당 로직에서 완전 분리가 가능한 형태로 출력 -> 목적과 구현이 분리되어 있다.)

#### 예시: 지역 변수를 사용할 때

지역 변수와 관련하여 가장 간단한 경우는 변수를 사용하지만 다른 값을 다시 대입하지는 않을 때다.

이 경우에는 지역 변수들을 그냥 매개변수로 넘기면 된다.

#### 예시: 지역 변수의 값을 변경할 때

지역 변수에 값을 대입하게 되면 문제가 복잡해진다.

지금은 임시 변수만을 취급하겠지만 만약 매개변수에 값을 대입하는 코드를 발견하면 곧바로 그 변수를 쪼개서 임시 변수를 새로 하나 만들어 그 변수에 대입하게 한다.

대입 대상이 되는 임시 변수는 크게 두 가지로 나눌 수 있다.

먼저 간단한 경우는 변수가 추출된 코드안에서만 사용될 때다.

즉, 이 변수는 추출된 코드 안에서만 존재한다.

이보다 특이한 경우는 변수가 추출한 함수 밖에서 사용될 때다.

이럴 때는 변수가 대입된 새 값을 반환해야 한다.

```csharp
void PrintOwing()
{
    PrintBanner();
    var outstanding = GetOutstanding();
    PrintDetails(outstanding);
}

void PrintBanner()
{
    Console.WriteLine("*****************");
    Console.WriteLine("**** 고객 채무 ****");
    Console.WriteLine("*****************");
}

double GetOutstanding()
{
    double result = 0;
    foreach (var o in _orders)
    {
        result += o.Amount;
    }
    return result;
}

void PrintDetails(double outstanding)
{
    Console.WriteLine($"고객명: {name}");
    Console.WriteLine($"채무액: {outstanding}");
}
```

#### 값을 반환할 변수가 여러 개라면?

이 부분은 함수가 값 하나만 반환하는 방식이 좋은 코드에 가깝기 때문에 코드 자체를 재구성하는 방향으로 가는 것이 좋다.

굳이 한 함수에서 여러 값을 반환해야 한다면 레코드나 튜플로 반환할 수 있지만 단계를 작게 나누고 작게 쪼개는 방식이 더 좋다.

### 6.2 함수 인라인하기(Inline Function)

- 반대 리팩터링: 함수 추출하기

```csharp
double GetRating()
{
    return (MoreThanFiveLateDeliveries()) ? 2 : 1;
}

bool MoreThanFiveLateDeliveries()
{
    return _numberOfLateDeliveries > 5;
}
```

```csharp
double GetRating()
{
    return (_numberOfLateDeliveries > 5) ? 2 : 1;
}
```

#### 배경

책에서는 계속해서 목적이 분명하게 드러나는 이름의 짤막한 함수를 이용하기를 권한다.

그래야 코드가 이해하기 쉬워지고 명료해지기 때문이다.

하지만 때로는 함수 본문이 이름만큼 명확한 경우도 있다.

또는 함수 본문 코드를 이름만큼 깔끔하게 리팩터링할 때도 있다.

이럴 때는 그 함수를 제거한다.

간접 호출은 유용할 수 있지만 쓸데없이 간접 호출은 거슬릴 뿐이다.

리팩터링 과정에서 잘못 추출된 함수들도 다시 인라인 한다.

간접 호출을 너무 과하게 쓰는 코드도 흔한 인라인 대상이다.

#### 절차

- 다형 메서드인지 확인한다.
  - 서브클래스에서 오버라이드하는 메서드는 인라인하면 안된다.
- 인라인할 함수를 호출하는 곳을 모두 찾는다.
- 각 호출문을 함수 본문으로 교체한다.
- 하나씩 교체할 때마다 테스트한다.  
  - 인라인 작업을 한 번에 처리할 필요는 없다. 인라인하기가 까다로운 부분이 있다면 일단 남겨두고 여유가 생길 때마다 틈틈히 처리한다.
- 함수 정의(원래 함수)를 삭제한다.

간단해 보일 수 있어도 다양한 예외상황이 있을 수 있다.

너무 복잡한 상황이라면 하지 않는 것이 바람직하다.

#### 예시

```csharp
double GetRating()
{
    return (MoreThanFiveLateDeliveries()) ? 2 : 1;
}

bool MoreThanFiveLateDeliveries()
{
    return _numberOfLateDeliveries > 5;
}
```

첫 예제와 같이 본문 그대로 복사하여 인라인 하는 방법이 가장 간단한 예이다.

다른 예제로는 변수를 매개변수로 전달받아 참조하고 있는 경우가 있는데 이런 경우는 한 단계식 처리하는 것이 좋다.

### 6.3 변수 추출하기(Extract Variable)

- 반대 리팩터링: 변수 인라인하기

```csharp
double Price()
{
    // 가격(price) = 기본 가격 - 수량 할인 + 배송비
    return _quantity * _itemPrice -
        Math.Max(0, _quantity - 500) * _itemPrice * 0.05 +
        Math.Min(_quantity * _itemPrice * 0.1, 100.0);
}
```

```csharp
double Price()
{
    // 가격(price) = 기본 가격 - 수량 할인 + 배송비
    var basePrice = _quantity * _itemPrice;
    var quantityDiscount = Math.Max(0, _quantity - 500) * _itemPrice * 0.05;
    var shipping = Math.Min(basePrice * 0.1, 100.0);
    return basePrice - quantityDiscount + shipping;
}
```

#### 배경

표현식이 너무 복잡해서 이해하기 어려울 때가 있다.

이럴 때 지역변수를 활용하여 표현식을 쪼개 관리하기 더 쉽게 만들 수 있다.

그러면 복잡한 로직을 구성하는 단계마다 이름을 붙일 수 있어서 코드의 목적을 훨씬 명확하게 드러낼 수 있다.

*이 과정에서 추가한 변수는 디버겅에서도 도움이 된다. 계산과정이 원자적으로 이뤄지지 않고 단계로 쪼개져 있기 때문에 중단점을 설정하는데 도움이 됨*

변수 추출을 고려한다고 한다면 표현식에 이름을 붙이고 싶다는 뜻이다.

이름을 붙이기로 했다면 그 이름이 들어갈 문맥도 살펴야 한다.

현재 함수 안에서만 의미가 있다면 변수로 추출하는 것이 좋다.  

하지만 함수를 벗어난 **넓은 문맥에서까지 의미가 된다면 그 넓은 범위에서 통용되는 이름**을 생각해야 한다.

다시 말해 이 경우는 변수가 아닌 함수로 추출해야 함을 의미한다.

이름이 통용되는 문맥을 넓히면 다른 코드에서 사용할 수 있기 때문에 같은 표현식을 중복해서 작성하지 않아도 된다.

#### 절차

- 추출하려는 표현식에 부작용은 없는지 확인한다.
- 불변 변수를 하나 선언하고 이름을 붙일 표현식의 복제본을 대입한다.
- 원본 표현식을 새로 만든 변수로 교체한다.
- 테스트한다.
- 표현식을 여러 곳에서 사용한다면 각각을 새로 만든 변수로 교체한다. 하나 교체할 때마다 테스트한다.

#### 예시

```csharp
double Price()
{
    // 가격(price) = 기본 가격 - 수량 할인 + 배송비
    return _quantity * _itemPrice -
        Math.Max(0, _quantity - 500) * _itemPrice * 0.05 +
        Math.Min(_quantity * _itemPrice * 0.1, 100.0);
}
```

이런 복잡한 표현식을 발견하면 먼저 표현식을 복제하고 변수로 추출한다.

```csharp
double Price()
{
    // 가격(price) = 기본 가격 - 수량 할인 + 배송비
    var basePrice = _quantity * _itemPrice;
    var quantityDiscount = Math.Max(0, _quantity - 500) * _itemPrice * 0.05;
    var shipping = Math.Min(basePrice * 0.1, 100.0);
    return basePrice - quantityDiscount + shipping;
}
```

- 먼저 도메인 즉 요구사항을 파악하고 기본 가격이 수량*단가라는 것을 알아낸다.
- 따라서 기본 가격을 계산하는 표현식을 복제하고 basePrice라는 이름의 변수에 대입한다.
- 그 다음으로 수량 할인을 계산하는 표현식을 복제하고 quantityDiscount라는 이름의 변수에 대입한다.
- 마지막으로 배송비를 계산하는 표현식을 복제하고 shipping이라는 이름의 변수에 대입한다.
- 이제 원래 표현식을 새로 만든 변수로 교체한다.

중간 중간 변수를 치환하는 과정에서 테스트를 수행한다.

#### 예시: 클래스 안에서

```csharp
class Order
{
    private Data _data;

    public Order(Data data)
    {
        _data = data;
    }
    
    public int Quantity => _data.Quantity;
    public int ItemPrice => _data.ItemPrice;

    public double Price()
    {
        // 가격(price) = 기본 가격 - 수량 할인 + 배송비
        return Quantity * ItemPrice -
            Math.Max(0, Quantity - 500) * ItemPrice * 0.05 +
            Math.Min(Quantity * ItemPrice * 0.1, 100.0);
    }
}
```

```csharp
class Order
{
    private Data _data;

    public Order(Data data)
    {
        _data = data;
    }
    
    public int Quantity => _data.Quantity;
    public int ItemPrice => _data.ItemPrice;

    public double Price()
    {
        return BasePrice() - QuantityDiscount() + Shipping();
    }

    public double BasePrice() => Quantity * ItemPrice;
    public double QuantityDiscount() => Math.Max(0, Quantity - 500) * ItemPrice * 0.05;
    public double Shipping() => Math.Min(Quantity * ItemPrice * 0.1, 100.0);
}
```

이렇게 작성하게 되면 객체지향의 장점을 잘 살린 코드라고 할 수 있다.

객체는 특정 로직과 데이터를 외부와 공유하려 할 때 공유할 정보를 설명해주는 **적당한 크기의 문맥**이 되어준다.

이 예처럼 간단한 경우라면 효과가 크지 않지만, 덩치가 큰 클래스에서 공통 동작을 별도 이름으로 뽑아내서 추상화해두면 그 객체를 다룰 때 쉽게 활용할 수 있어서 매우 유용하다.

### 6.4 변수 인라인하기(Inline Variable)

- 반대 리팩터링: 변수 추출하기

```csharp
int basePrice = anOrder.BasePrice;
return (basePrice > 1000);
```

```csharp
return (anOrder.BasePrice > 1000);
```

#### 배경

변수는 함수 안에서 표현식을 가리키는 이름으로 쓰이며, 대체로 긍정적인 효과를 준다.

하지만 그 이름이 원래 표현식과 다를 바 없을 때도 있다.

또 변수가 주변 코드를 리팩터링하는 데 방해가 되기도 한다.

이럴 때는 변수를 인라인하는 것이 좋다.

#### 절차

- 대입문의 우변에서 부작용이 생기지는 않는지 확인한다.
- 변수가 불변으로 선언되지 않았다면 불변으로 만든 후 테스트한다.
  - 이렇게 되어야 변수에 값이 단 한 번만 대입되는지 확인할 수 있다.
- 이 변수를 가장 처음 사용하는 코드를 찾아서 대입문 우번의 코드로 바꾼다.
- 테스트한다.
- 변수를 사용하는 부분을 모두 교체할 때까지 이 과정을 반복한다.
- 변수 선언문과 대입문을 지운다.
- 테스트한다.

### 6.5 함수 선언 바꾸기(Change Function Declaration)

- 다른 이름
  - 함수 이름 바꾸기
  - 시그니처 바꾸기

```csharp
public double Circum(int radius) {...}
```

```csharp
public double CircumFerence(int radius) {...}
```

#### 배경

함수는 프로그램을 작은 부분으로 나누는 주된 수단이다.

함수 선언은 각 부분이 서로 맞물리는 방식을 표현하며, 실질적으로 소프트웨어 시스템의 구성 요소를 조립하는 연결부 역할을 한다.

건축과 마찬가지로 소프트웨어도 이러한 연결부에 상당히 의존적이다.

즉 인터페이스를 절 정의하면 시스템에 새로운 부분을 추가하기가 쉬워지는 반면, 잘못 정의하면 지속적인 방해 요인으로 작용한다.

이러한 연결부에서 가장 중요한 부분이 함수 이름이다.

이름이 좋으면 함수의 구현 코드를 살펴볼 필요 없이 호출문만 보고도 무슨 일을 하는지 파악할 수 있다.

하지만 좋은 이름을 떠올리기란 쉽지 않다. (가장 어려운 문제)

함수의 매개변수도 마찬가지다.

**매개변수는 함수가 외부 세계와 어우러지는 방식을 정의한다.**

메게변수는 함수를 사용하는 문맥을 설정한다.

이 리팩터링은 사실 가장 어려운 리팩터링이 아닐까 싶다.

내 기준에선 내가 한국인이고 외국에서 일할 생각이 크게 없기 때문에 이름에 대한 명명 규칙은 대부분 친숙한 단어 위주로 사용한다.

물론 서술적이고 간단한 이름이 좋다는 것을 알고, 그 수준을 목표로 하지만 따라오는 코스트가 객체지향에 대한 이해와 영어의 전반적인 이해가 필요하다고 생각된다.

#### 절차

이 리팩터링은 약간 성격이 다르다.

먼저 변경 사항을 살펴보고 함수 선언과 호출문들을 단번에 고칠 수 있는지 가늠해본다.

가능할 것 같다면 간단한 절차를 따른다.

마이그레이션 절차를 적용하면 호출문들을 점진적으로 수정할 수 있다.

호출하는 곳이 많거나, 호출 과정이 복잡하거나, 호출 대상이 다형 메서드거나, 선언이 복잡할 때는 이렇게 해야한다.

##### 간단한 절차

- 매개변수를 제거하려거든 먼저 함수 본문에서 제거 대상 매개변수를 참조하는 곳은 없는지 확인한다.
- 메서드 선언을 원하는 형태로 바꾼다.
- 기존 메서드 선언을 참조하는 부분을 모두 찾아서 바뀐 형태로 수정한다.
- 테스트한다.

변경할 게 둘 이상이면 나눠서 처리하는 편이 나을 때가 많다.

따라서 이름 변경과 매개변수 추가를 모두 하고 싶다면 각각 독립적으로 처리하자.

(그러다 문제가 생기면 작업을 되돌리고 마이그레이션 절차를 따른다.)

사람은 기본적으로 멀티에 약하고 하면 안된다. 각 단계를 작게 나누고 독립적으로 처리할 것

##### 마이그레이션 절차

- 이어지는 추출 단계를 수월하게 만들어야 한다면 함수의 본문을 적절히 리팩터링한다.
- 함수 본문을 새로운 함수로 추출한다.
  - 새로 만들 함수 이름이 기존 함수와 같다면 일단 검색하기 쉬운 이름을 임시로 붙여둔다.
- 추출한 함수에 매개변수를 추가해야 한다면 '간단한 절차'를 따라 추가한다.
- 테스트한다.
- 기존 함수를 인라인 한다.
- 이름을 임시로 붙여뒀다면 함수 선언 바꾸기를 통해 원래 이름으로 되돌린다.
- 테스트한다.

#### 예시: 함수 이름 바꾸기(간단한 절차)

```csharp
public double Circum(int radius) {...}
```

```csharp
public double CircumFerence(int radius) {...}
```

다음으로 Circum을 호출한 부분을 모두 찾아서 변경한다.(요즘은 IDE가 좋아져서 일괄 변경을 사용)

#### 예시: 함수 이름 바꾸기(마이그레이션 절차)

```csharp
public double Circum(int radius) {...}
```

```csharp
public double GetCircumFerence(int radius) {...}
```

```csharp
public double Circum(int radius) => GetCircumFerence(radius);
```

API처럼 래퍼클래스와 같은 형태로 생각하면 좋다

좀 더 안전한 방식, 폐기 예정을 생각하고 작업하는 방식

#### 예시: 매개변수 추가하기

```csharp
public void AddReservation(Reservation reservation)
{
    AddReservation(reservation, false);
}

public void AddReservation(Reservation reservation, bool isPriority)
{
    if (isPriority)
    {
        // 우선순위 예약을 추가한다.
    }
    else
    {
        // 일반 예약을 추가한다.
    }
}
```

이 예제에서 내 생각은 if 조건문으로 분기보다 각 함수 이름이 좀 더 명확한 형태가 좋을 것 같다.

우선순위 예약과 일반 예약의 함수를 따로 만들고 직접 호출하는 방식이 더 좋아보인다.

#### 6.6 변수 캡슐화하기(Encapsulate Variable)

```csharp
public string Name;
```

```csharp
private string _name;
public string Name
{
    get => _name;
    set => _name = value;
}
```

#### 배경

리팩터링은 결국 프로그램의 요소를 조작하는 일이다.

함수는 데이터보다 다루기가 수월하다.

함수를 사용한다는 건 대체로 호출한다는 뜻이고, 함수의 이름을 바꾸거나 다른 모듈로 옮기기는 어렵지 않다.

여차하면 기존 함수를 그대로 둔 채로 전달함수로 활용할 수도 있기 때문이다.

반대로 데이터는 함수보다 까다로운데, 그 이유는 이런 식으로 처리할 수 없기 때문이다.

데이터는 참조하는 모든 부분을 한 번에 바꿔야 코드가 제대로 작동한다.

짧은 함수 안의 임시 변수처럼 유효범위가 아주 좁은 데이터는 어려울 게 없지만, 유효 범위가 넓어질수록 다루기 어려워진다.

전역 데이터가 골칫거리인 이유도 바로 여기에 있다.

따라서 접근할 수 있는 데이터를 옯길 때는 먼저 그 데이터로의 접근을 독접하는 함수를 만드는 식으로 캡슐화하는 것이 가장 좋은 방법일 때가 많다.

객체지향에서 private을 항상 유지해야 한다고 하는 이유가 바로 여기에 있다.

#### 절차

- 변수로의 접근과 갱신을 전담하는 캡슐화 함수들을 만든다. (게터와 세터 C#은 프로퍼티라는 강력한 기능이 있다)
- 정적 검사를 수행한다.
- 변수를 직접 참조하던 부분을 모두 적절한 캡슐화 함수 호출로 바꾼다. 하나씩 바꿀 때마다 테스트한다.
- 변수의 접근 범위를 제한한다.
  - 변수로의 직접 접근을 막을 수 없을 때도 있다. 그럴 때는 변수 이름을 바꿔서 테스트해보면 해당 변수를 참조하는 곳을 쉽게 찾아낼 수 있다.
- 테스트한다.
- 변수 값이 레코드라면 레코드 캡슐화하기를 적용할지 고려해본다.

#### 예시

이 부분은 C#의 좀 더 강력한 기능인 프로퍼티를 사용하면 된다.

```csharp
public string Name;
```

```csharp
private string _name;

public string Name
{
    get => _name;
    set => _name = value;
}
```

set이나 get을 제한하고 싶다면 아래와 같이 사용

```csharp
public string Name { get; private set; }
```

### 6.7 변수 이름 바꾸기(Rename Variable)

```csharp
int a = height * width;
```

```csharp
int area = height * width;
```

#### 배경

명확한 프로그래밍의 핵심은 이름짓기다.

변수는 프로그래머가 하려는 일에 관해 많은 것을 설명해준다.

단, 이름을 잘 지었을 때만 그렇다.

*이런 이름에 관한 인지작용은 `프로그래머의 뇌`라는 책을 참고하면 좋다.*

이 부분에서 조금 인지적인 부분이 설명되어야 하는데 프로그래머가 알고 있는 당연한 문법 람다식의 경우 x에 대한 변수는 바로 해석이 가능하지만 스피드하게 푸는 알고리즘 문제의 변수들은 각각 무슨 역할을 하는지 단번에 파악하기 어렵다.

맥락과 배경지식의 영역이 필요한 부분

#### 절차

- 폭넓게 쓰이는 변수라면 캡슐화를 고려한다.
- 이름을 바꿀 변수를 참조하는 곳을 모두 찾아서, 하나씩 변경한다.
  - 다른 코드베이스에서 참조하는 변수는 외부에 공개된 변수이므로 리팩터링을 적용할 수 없다.
  - 변수 값이 변하지 않는다면 다른 이름으로 복제본을 만들어서 하나씩 점진적으로 변경한다. 하나씩 바꿀 때마다 테스트한다.
- 테스트한다.

#### 예시

변수 이름 바꾸기의 가장 간단한 예는 임시 변수나 인수처럼 유효범위가 하나로 국한된 변수다.

예시도 필요없고 단지 이름만 잘 지으면 된다.

### 6.8 매개변수 객체 만들기(Introduce Parameter Object)

```csharp
private void AmountInvoicedIn(Date start, Date end) {...}
private void AmountReceivedIn(Date start, Date end) {...}
private void AmountOverdueIn(Date start, Date end) {...}
```

```csharp
private void AmountInvoicedIn(DateRange range) {...}
private void AmountReceivedIn(DateRange range) {...}
private void AmountOverdueIn(DateRange range) {...}
```

#### 배경

데이터 항목 여러 개가 이 함수에서 저 함수로 함께 몰려다니는 경우를 자주 본다.

이런 데이터 무리를 발견하면 데이터 구조를 하나로 모아주곤 한다.(매개변수 자체가 적은 것이 유리)

데이터 뭉치를 데이터 구조로 묶으면 데이터 사이의 관계가 명확해진다는 이점을 얻는다.

게다가 함수가 이 데이터 구조를 받게 하면 매개변수 수가 줄어든다.

같은 데이터 구조를 사용하는 모든 함수가 원소를 참조할 때 항상 똑같은 이름을 사용하기 때문에 일관성도 높여준다.

하지만 이 리팩터링의 진정한 힘은 코드를 더 근본적으로 바꿔준다는 데 있다.

이런 데이터구조를 발견하면 이 데이터 구조를 활용하는 형태로 프로그램 동작을 재구성한다.

데이터 구조에 담길 데이터에 공통으로 적용되는 동작을 추출해서 함수로 만드는 것이다.

이 과정에서 **새로 만든 데이터 구조가 문제 영역을 훨씬 간결하게 표현하는 새로운 추상개념으로 격상**되면서, 코드의 개념적인 그림을 다시 그릴 수도 있다.

#### 절차

- 적당한 데이터 구조가 아직 마련되어 있지 않다면 새로 만든다.
  - 개인적으로 클래스를 만드는 것을 선호한다. 나중에 동작까지 함께 묶기 좋기 때문이다. 주로 값 객체로 만든다.
- 테스트한다.
- 함수 선언 바꾸기로 새 데이터 구조를 매개변수로 추가한다.
- 테스트한다.
- 함수 호출 시 새 데이터 구조 인스턴스를 넘기도록 수정한다. 하나씩 수정할 때마다 테스트한다.
- 기존 매개변수를 사용하던 코드를 새 데이터 구조의 원소를 사용하도록 바꾼다.
- 다 바꿨다면 기존 매개변수를 제거한다.

#### 예시

온도 측정값 배열에서 정상 작동 범위를 벗어난 것이 있는지 검사하는 코드다.

```csharp
public class HeatingPlan
{
    private TempRange _range;

    public HeatingPlan(TempRange range)
    {
        _range = range;
    }

    public bool WithinRange(int low, int high)
    {
        return (low >= _range.GetLow() && high <= _range.GetHigh());
    }
}

public class TempRange
{
    private int _low;
    private int _high;

    public TempRange(int low, int high)
    {
        _low = low;
        _high = high;
    }

    public int GetLow() => _low;
    public int GetHigh() => _high;
}

public class Room
{
    private HeatingPlan _plan;

    public Room(HeatingPlan plan)
    {
        _plan = plan;
    }

    public bool WithinPlan(TempRange range)
    {
        return _plan.WithinRange(range.GetLow(), range.GetHigh());
    }
}
```

이 코드는 매개변수가 2개인 함수를 2개 호출하고 있다.

이런 경우는 매개변수를 객체로 만들면 편리하다.

```csharp
public class HeatingPlan
{
    private TempRange _range;

    public HeatingPlan(TempRange range)
    {
        _range = range;
    }

    public bool WithinRange(TempRange range)
    {
        return (range.GetLow() >= _range.GetLow() && range.GetHigh() <= _range.GetHigh());
    }
}

public class TempRange
{
    private int _low;
    private int _high;

    public TempRange(int low, int high)
    {
        _low = low;
        _high = high;
    }

    public int GetLow() => _low;
    public int GetHigh() => _high;
}

public class Room
{
    private HeatingPlan _plan;

    public Room(HeatingPlan plan)
    {
        _plan = plan;
    }

    public bool WithinPlan(TempRange range)
    {
        return _plan.WithinRange(range);
    }
}
```

#### 진정한 값 객체로 거듭나기

진정한 값 객체는 클래스로 만들어 두고 이후에 관련 동작들을 해당 클래스로 옮길 수 있다는 이점이 생긴다.

```csharp
public class TempRange
{
    private int _low;
    private int _high;

    public TempRange(int low, int high)
    {
        _low = low;
        _high = high;
    }

    public int GetLow() => _low;
    public int GetHigh() => _high;

    public bool Includes(int arg)
    {
        return arg >= GetLow() && arg <= GetHigh();
    }
}
```

### 6.9 여러 함수를 클래스로 묶기(Combine Functions into Class)

```csharp
private void base(aReading) {...}
private void taxableCharge(aReading) {...}
private void calculateBaseCharge(aReading) {...}
```

```csharp
class Reading
{
    ...

    public int GetBase();
    public int GetTaxableCharge();
    public int GetCalculateBaseCharge();
}
```

#### 배경

클래스는 대다수의 최신 언어가 지원하는 기본적인 빌딩 블록이다.

클래스는 데이터와 함수를 하나의 공유 환경으로 묶은 후, 다른 프로그램 요소와 어우러질 수 있도록 그중 일부를 외부에 제공한다.

클래스는 객체 지향 언어의 기본인 동시에 다른 패러다임 언어에도 유용하다.

이 리팩터링은 이미 만들어진 함수들을 재구성할 때는 물론, 새로 만든 클래스와 관련하여 놓친 연산자를 찾아서 새 클래스의 메서드로 뽑아내는 데도 좋다.

함수를 한데 묶는 또 다른 방법으로 `여러 함수를 변환 함수로 묶기`도 있다.

둘 중 어느 방식으로 리팩터링을 진행할지는 프로그램의 문맥을 넓게 파악하고 정해야 한다.

클래스로 묶는 경우는 클라이언트가 객체의 핵심 데이터를 변경할 수 있고, 파생 객체들을 일관되게 관리할 수 있다.

이런 함수들은 중첩 함수들로 묶어도 되지만 클래스로 묶는 것이 더 좋다(확장성)

#### 절차

- 함수들이 공유하는 공통 데이터 레코드를 캡슐화한다.
  - 공통 데이터가 레코드 구조로 묶여 있지 않다면 먼저 매개변수 객체 만들기로 데이터를 하나로 묶는 레코드를 만든다.
- 공통 레코드를 사용하는 함수 각각을 새 클래스로 옮긴다.
  - 공통 레코드의 멤버는 함수 호출문의 인수 목록에서 제거한다.
- 데이터를 조작하는 로직들은 함수로 추출해서 새 클래스로 옮긴다.

#### 예시

```csharp
public record Reading
{
    public int CustomerId { get; init; }
    public int Quantity { get; init; }
    public DateTime Date { get; init; }
}

public class ReadingCalculator
{
    private Reading _reading;

    public ReadingCalculator(Reading reading)
    {
        _reading = reading;
    }

    public int Base()
    {
        return _reading.Quantity * 2;
    }

    public int TaxableCharge()
    {
        return Math.Max(0, _reading.Quantity - 100);
    }

    public int CalculateBaseCharge()
    {
        return _reading.Quantity * 2;
    }
}
```

내가 만든 예제에서 활용된 `record`는 C# 9.0에서 추가된 기능으로 **불변 데이터**를 쉽게 만들 수 있게 해준다.

자세한 내용은 검색해서 참고!

### 6.10 여러 함수를 변환 함수로 묶기(Combine Functions into Transform)

```csharp
public int base(aReading) {...}
public int taxableCharge(aReading) {...}
```

```csharp
public Reading enrichReading(aReading) 
{
    const aReading = deepCopy(aReading);
    aReading.baseCharge = base(aReading);
    aReading.taxableCharge = taxableCharge(aReading);
    return aReading;
}
```

#### 배경

소프트웨어는 데이터를 입력받아서 여러 가지 정보를 도출하곤 한다.

이렇게 도출된 정보는 여러 곳에서 사용될 수 있는데, 그러다 보면 이 정보가 사용되는 곳마다 같은 도출 로직이 반복되기도 한다.

이런 작업을 한 곳에 모아두게 되면 검색과 갱신을 일관된 장소에서 처리할 수 있고 로직 중복도 막을 수 있다.

이렇게 하기 위한 방법으로 변환 함수를 사용할 수 있다.

변환 함수는 원본 데이터를 입력받아서 필요한 정보를 모두 도출한 뒤, 각각의 출력 데이터의 필드에 넣어 반환한다.

이것의 클래스로 묶기와 차이점은 원본 데이터가 코드 안에서 갱신될 때는 클래스로 묶기를 사용하고, 원본 데이터가 갱신되지 않을 때는 변환 함수를 사용한다.

#### 절차

- 변환할 레코드를 입력받아서 값을 그대로 반환하는 변환 함수를 만든다.
  - 이 작업은 대체로 깊은 복사로 처리해야 한다. 반환 함수가 원본 레코드를 바꾸지 않는지 검사하는 테스트를 마련해두면 도움될 때가 많다.
- 묶을 함수 중 하나를 골라서 본문 코드를 변환 함수로 옮기고, 처리 결과를 레코드에 새 필드로 기록한다. 그런 다음 클라이언트 코드가 이 필드를 사용하도록 수정한다.
  - 로직이 복잡하면 함수 추출하기 부터 한다.
- 테스트한다.
- 나머지 관련 함수도 위 과정에 따라 처리한다.

#### 예시

9번 예제와 비슷하여 패스

### 6.11 단계 쪼개기(Split Phase)

```csharp
const string[] orderData = orderString.Split(/\s+/);
const int productPrice = priceList[orderData[0].Split("-")[1]];
const int orderPrice = ParseInt(orderData[1]) * productPrice;
```

```csharp
const Order order = new Order(orderString);
const int orderPrice = order.Price(priceList);

public class Order
{
    private string _data;

    public Order(string data)
    {
        _data = data;
    }

    public int Price(Dictionary<string, int> priceList)
    {
        const string[] orderData = _data.Split(/\s+/);
        const int productPrice = priceList[orderData[0].Split("-")[1]];
        return ParseInt(orderData[1]) * productPrice;
    }
}
```

*이 부분은 변환이 생각보다 어렵다*

#### 배경

서로 다른 두 대상을 한꺼번에 다루는 코드를 발견하면 각각의 별개의 모듈로 나누는 방법을 모색한다.

코드를 수정해야 할 때 두 대상을 동시에 생각할 필요 없이 하나에만 집중하기 위해서다.

분리하는 가장 간편한 방법은 동작을 연이은 두 단계로 쪼개는 것이다.

입력이 처리 로직에 적합하지 않은 형태로 들어오는 경우를 예로 생각해보자. 이럴 때는 본 작업에 들어가기 전에 입력값을 다루기 편한 형태로 가공한다.

아니면 순차적인 단계들로 분리해도 된다.

가장 대표적인 예로 `컴파일러`다.

기본적으로 어떤 텍스트를 입력받아 실행 가능한 형태로 변환하는데 이 과정이 순차적이라는 것

각 단계는 자신만의 문제에 집중하기에 다른 단계에 관해서는 몰라도 이해할 수 있다.

이렇게 단계를 쪼개는 기법은 주로 덩치 큰 소프트웨어에 적용된다.

#### 절차

- 두 번째 단계에 해당하는 코드를 독립 함수로 추출한다.
- 테스트한다.
- 중간 데이터 구조를 만들어서 앞에서 추출한 함수의 인자로 추가한다.
- 테스트한다.
- 추출한 두 번째 단계 함수의 매개변수를 하나씩 검토한다. 그중 첫 번째 단계에서 사용되는 것은 중간 데이터 구조로 옮긴다. 하나씩 옮길 때마다 테스트한다.
- 첫 번째 단계 코드를 함수로 추출하면서 중간 데이터 구조를 반환하도록 만든다.

#### 예시

상품의 결제 금액을 계산하는 코드로 살펴본다.

```csharp
public int PriceOrder(Product product, int quantity, ShippingMethod shippingMethod)
{
    int basePrice = product.BasePrice * quantity;
    int discount = Math.Max(quantity - product.DiscountThreshold, 0) * product.BasePrice * product.DiscountRate;
    int shippingPerCase = (basePrice > shippingMethod.DiscountThreshold) ? shippingMethod.FeePerCase - 1 : shippingMethod.FeePerCase;
    int shippingCost = quantity * shippingPerCase;
    int price = basePrice - discount + shippingCost;
    return price;
}
```

코드를 살펴보면 계산이 두 단계로 이뤄지는데 앞 두줄은 상품 가격을 계산하고, 나머지는 배송비를 계산한다.

- 먼저 배송비 계산부분을 함수로 추출한다.

```csharp
public int PriceOrder(Product product, int quantity, ShippingMethod shippingMethod)
{
    int basePrice = product.BasePrice * quantity;
    int discount = Math.Max(quantity - product.DiscountThreshold, 0) * product.BasePrice * product.DiscountRate;
    int price = basePrice - discount + ShippingCost(quantity, shippingMethod);
    return price;
}

private int ShippingCost(int quantity, ShippingMethod shippingMethod)
{
    int shippingPerCase = (quantity > shippingMethod.DiscountThreshold) ? shippingMethod.FeePerCase - 1 : shippingMethod.FeePerCase;
    int shippingCost = quantity * shippingPerCase;
    return shippingCost;
}
```

두 번째 단계에 필요한 데이터를 모두 개별 매개변수로 전달했다.

실전에서는 이런 데이터가 상당히 많을 수 있는데, 어차피 나중에 걸러내기 때문에 문제없다.

*여기서 말하는 걸러내기 작업은 두 가지 이상 리팩터링을 동시에 하지말고 우선 한가지에 집중하라는 것*

- 다음으로 첫 번째 단계와 두 번째 단계가 주고받을 중간 데이터 구조를 만든다.

뒤 두가지 예제는 따로 CodeReview에서 다룰 예정

### 느낀점

논의사항으로

#### 논의사항

앞 3장에서 코드 스멜에 대해 이야기하면서 대부분 짧게 나왔던 내용을 다시 풀어서 예시와 자세한 설명이 있어서 좋았습니다..

마찬가지로 한번에 다 읽고 이해하기 보다 필요할 때 찾아보기 좋을 것 같은 내용이네요!

이런 부분도 읽고 넘기는게 아닌 실천이 가장 중요할 것 같습니다.

**기본적인 리팩터링**에서 가장 많이 사용하시는 리팩터링은 무엇인가요?
