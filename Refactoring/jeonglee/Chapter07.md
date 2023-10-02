## 7. 캡슐화

### 7.1 레코드 캡슐화하기(Encapsulate Record)

```csharp
public class Organization
{
    public string Name { get; set; }
    public string Country { get; set; }
}
```

```csharp
public class Organization
{
    public string Name { get; set; }
    public Country Country { get; set; }
}

public class Country
{
    public string Name { get; set; }
}
```

#### 배경

대부분의 프로그래밍 언어는 데이터 레코드를 표현하는 구조를 제공한다.

레코드는 연관된 데이터를 직접적인 방식으로 묶을 수 있어서 각각을 따로 취급할 때보다 훨씬 의미있는 단어로 전달할 수 있게 해준다.

하지만 레코드는 계산하여 얻을 수 있는 값과 그렇지 않은 값을 명확하게 구분해 저장하는 점이 번거롭다.

때문에 **가변 데이터**를 저장하는 용도로는 레코드보다 객체가 좋을 수 있다.

객체를 사용하면 어떻게 저장했는지를 숨긴 채 세 가지 값을 각각의 메서드로 제공할 수 있다.

#### 절차

- 레코드를 담은 변수를 캡슐화한다.
- 레코드를 감싼 단순한 클래스로 해당 변수의 내용을 교체한다. 이 클래스에 원본 레코드를 반환하는 접근자도 정의하고, 변수를 캡슐화하는 함수들이 이 접근자를 사용하도록 수정한다.
- 테스트한다.
- 원본 레코드 대신 새로 정의한 클래스 타입의 객체를 반환하는 함수들을 새로 만든다.
- 레코드를 반환하는 예전 함수를 사용하는 코드를 새 함수를 사용하도록 바꾼다.
- 클래스에서 원본 데이터를 반환하는 접근자와 원본 레크드를 반환하는 함수들을 제거한다.
- 테스트한다.
- 레코드의 필드도 데이터 구조인 중첩 구조라면 레코드 캡슐화하기와 컬렉션 캡슐화하기를 재귀적으로 적용한다.

#### 예시: 간단한 레코드 캡슐화하기

```csharp
public class Organization
{
    public string Name { get; set; }
    public string Country { get; set; }
}
```

```csharp
public class Organization
{
    public string Name { get; set; }
    public Country Country { get; set; }
}

public class Country
{
    public string Name { get; set; }
}
```

불변 데이터는 앞 장에서 다룬 것과 같이 `C#`의 record를 사용하면 되고 가변 데이터에 대한 캡슐화는 프로퍼티로 처리할 수 있다.

### 7.2 컬렉션 캡슐화하기(Encapsulate Collection)

```csharp
public class Person
{
    public List<Course> Courses { get; set; }
}
```

```csharp
public class Person
{
    private List<Course> _courses = new List<Course>();
    public List<Course> Courses
    {
        get => _courses;
        set => _courses = value;
    }
}
```

*이 예제는 사실 틀린 예제이지만 자바스크립트와 최대한 비슷하게..*

- 책 에서 원하는 것 처럼 컬렉션을 제어할 수 없게 만들려면 `C#`에선 `IEnumerable`이나 `ReadOnlyCollection`을 이용해야 한다.

[관련 글](https://www.csharpstudy.com/Mistake/Article/17)

아니면 해당 프로퍼티에서 DeepCopy 객체를 반환하는 Get만 두고 Set을 삭제하는 방법이 있을 것 같다.

#### 배경

가변 데이터 또한 캡슐화를 해 놓으면 데이터 구조가 언제 어떻게 수정되는지 추적하기 쉬워진다.

객체지향에서도 캡슐화는 적극 권장되며 컬렉션을 다룰 때 일어나는 실수를 방지할 수 있다.

사실 이보다 Add, Remove같은 메서드를 제공하는 것이 더 바람직한 방법으로 컬렉션 자체를 반환하게 되면 변경될 가능성이 항상 존재하기에 실수 자체를 차단하는 것이 좋다.

위에서 언급한 복제된 객체를 반환하거나 이터레이터를 써서 접근을 막는 방법..

게임에서는 이런 데이터를 매우 많이 만지기 때문에 불변 데이터를 보장하기 위해 복사를 사용한다면 부담이 될 것 같다는 생각도 든다.

#### 절차

- 아직 컬레션을 캡슐화하지 않았다면 변수 캡슐화하기부터 한다.
- 컬렉션에 원소를 추가/제거하는 함수를 추가한다.
- 정적 검사를 수행한다.
- 컬렉션을 참조하는 부분을 모두 찾는다. 컬렉션의 변경자를 호출하는 코드가 모두 앞에서 추가한 추가/제거 함수를 호출하도록 수정한다. 하나씩 수정할 때마다 테스트한다.
- 컬렉션 게터를 수정해서 원본 내용을 수정할 수 없는 읽기전용 프락시나 복제본을 반환하게 한다.
- 테스트한다.

#### 예시

```csharp
public class Person
{
    public List<Course> Courses { get; set; }
}
```

```csharp
public class Person
{
    private List<Course> _courses = new List<Course>();
    public List<Course> Courses
    {
        get => _courses.DeepCopy();
    }

    public void AddCourse(Course course)
    {
        _courses.Add(course);
    }

    public void RemoveCourse(Course course)
    {
        // 삭제 예외처리
        _courses.Remove(course);
    }
}
```

or 접근 제한은 위 [링크 참조](https://www.csharpstudy.com/Mistake/Article/17)

### 7.3 기본형을 객체로 바꾸기(Replace Primitive with Object)

```csharp
public class Order
{
    public string Customer { get; set; }
}
```

```csharp
public class Order
{
    public Customer Customer { get; set; }
}

public class Customer
{
    public string Name { get; set; }
}
```

#### 배경

개발 초기에는 단순한 정보를 문자나 숫자로 표현하는 경우가 많다.

이후 개발이 진행되면서 해당 정보들이 더이상 간단하지 않게 변하게 된다.

단순 출력 이상의 성능이 필요해지는 순간 데이터를 표현하는 전용 클래스로 정의하는 것이 좋다.

기본형 데이터를 감싼 형태라 효과가 미미하지만 이후에 특별한 동작을 추가하다 보면 유용한 도구가 된다.

`C#`에서는 enum을 사용해서 Entity의 State를 정의하거나, 상태 관련을 열거형으로 다루는 경우가 많다.

하지만 상태끼리의 상호작용이나 상태에 따른 공통적인, 부가적인 행동이 필요할 때는 enum을 벗어나 클래스로 업그레이드 하는 것이 좋을 수 있을 것 같다.

#### 절차

- 아직 변수를 캡슐화하지 않았다면 캡슐화한다.
- 단순한 값 클래스를 만든다. 생성자는 기존 값을 인수로 받아서 저장하고, 이 값을 반환하는 게터를 추가한다.
- 정적 검사를 수행한다.
- 값 클래스의 인스턴스를 새로 만들어서 필드에 저장하도록 세터를 수정한다. 이미 있다면 필드의 타입을 적절히 변경한다.
- 새로 만든 클래스의 게터를 호출한 결과를 반환하도록 게터를 수정한다.
- 테스트한다.
- 함수 이름을 바꾸면 원본 접근자의 동작을 더 잘 드러낼 수 있는지 검토한다.

#### 예시

```csharp
enum State
{
    STATE_STOP,
    STATE_START,
    STATE_PAUSE,
    STATE_RESUME
}

public class Player
{
    public State State { get; set; }
}
```

```csharp
public class Player
{
    public PlayerState State { get; set; }
}

public class PlayerState
{
    public State State { get; set; }
}
```

### 7.4 임시 변수를 질의 함수로 바꾸기

```csharp
public class Order
{
    public double GetPrice()
    {
        double basePrice = _quantity * _itemPrice;
        if (basePrice > 1000)
        {
            return basePrice * 0.95;
        }
        else
        {
            return basePrice * 0.98;
        }
    }
}
```

```csharp
public class Order
{
    public double GetPrice()
    {
        if (BasePrice() > 1000)
        {
            return BasePrice() * 0.95;
        }
        else
        {
            return BasePrice() * 0.98;
        }
    }

    private double BasePrice()
    {
        return _quantity * _itemPrice;
    }
}
```

#### 배경

함수 안에서 어떤 코드의 결과값을 뒤에서 다시 참조할 목적으로 임시 변수를 쓰기도 한다.

이런 임시 변수가 3진 아웃, 두번 이상 사용된다면 함수로 추출하는 것이 좋다.

이 리팩터링은 클래스 내부에서 적용할 때 효과가 크다.

쿨랴수눈 추출할 메서드들에 공유 컨텍스트를 제공하기 때문이다.

클래스 바깥의 최상위 함수로 추출하면 매개변수가 너무 많아져서 함수를 사용하는 장점이 줄어든다.

#### 절차

- 변수가 사용되기 전에 값이 확실히 결정되는지, 변수를 사용할 때마다 계산 로직이 매번 다른 결과를 내는지 않는지 확인한다.
- 읽기전용으로 만들 수 있는 변수는 읽기전용으로 만든다.
- 테스트한다.
- 변수 대입문을 함수로 추출한다.
- 테스트한다.
- 변수 인라인하기로 변수를 제거한다.

#### 예시

```csharp
public class Order
{
    public double GetPrice()
    {
        double basePrice = _quantity * _itemPrice;
        if (basePrice > 1000)
        {
            return basePrice * 0.95;
        }
        else
        {
            return basePrice * 0.98;
        }
    }
}
```

```csharp
public class Order
{
    public double GetPrice()
    {
        if (BasePrice() > 1000)
        {
            return BasePrice() * 0.95;
        }
        else
        {
            return BasePrice() * 0.98;
        }
    }

    private double BasePrice()
    {
        return _quantity * _itemPrice;
    }
}
```

### 7.5 클래스 추출하기(Extract Class)

```csharp
public class Person
{
    public string OfficeAreaCode { get; set; }
    public string OfficeNumber { get; set; }
}
```

```csharp
public class Person
{
    private TelephoneNumber _officeTelephone = new TelephoneNumber();

    public string OfficeAreaCode
    {
        get => _officeTelephone.AreaCode;
        set => _officeTelephone.AreaCode = value;
    }

    public string OfficeNumber
    {
        get => _officeTelephone.Number;
        set => _officeTelephone.Number = value;
    }
}

public class TelephoneNumber
{
    public string AreaCode { get; set; }
    public string Number { get; set; }
}
```

#### 배경

클래스는 반드시 명확하고 추상화하고 소수의 주어진 역할만 처리해야 한다는 가이드라인을 따라야 한다.

하지만 실무에서는 연산을 추가하고 데이터를 추가하다 보면 클래스가 점점 비대하지곤 한다.

그러다 보면 나중엔 손쓸 틈도 없이 딱딱한 덩어리로 변해버린다.

**특히 일부 데이터와 메서드를 따로 묶을 수 있다면 어서 분리하라는 신호다.**

#### 절차

- 클래스의 역할을 분리할 방법을 정한다.
- 분리될 역할을 담당할 클래스를 새로 만든다.
- 원래 클래스의 생성자에서 새로운 클래스의 인스턴스를 생성하여 필드에 저장해둔다.
- 분리될 역할에 필요할 필드들을 새 클래스로 옮긴다. 하나씩 옮길 때마다 테스트한다.
- 메서드들도 새 클래스로 옮긴다. 이때 저수준 메서드, 즉 다른 메서드를 호출하기보다는 호출당하는 일이 많은 메서드부터 옮긴다. 하나씩 옮길 때마다 테스트한다.
- 양쪽 클래스의 인터페이스를 살펴보면서 불필요한 메서드를 제거하고, 이름도 새로운 환경에 맞게 바꾼다.
- 새 클래스를 외부로 노출할지 정한다. 노출하려거든 새 클래스에 참조를 값으로 바꾸기를 적용할지 고려한다.

#### 예시

```csharp
public class Person
{
    public string OfficeAreaCode { get; set; }
    public string OfficeNumber { get; set; }
}
```

```csharp
public class Person
{
    private TelephoneNumber _officeTelephone = new TelephoneNumber();

    public string OfficeAreaCode
    {
        get => _officeTelephone.AreaCode;
        set => _officeTelephone.AreaCode = value;
    }

    public string OfficeNumber
    {
        get => _officeTelephone.Number;
        set => _officeTelephone.Number = value;
    }
}
```

### 7.6 클래스 인라인하기(Inline Class)

```csharp
public class Person
{
    private TelephoneNumber _officeTelephone = new TelephoneNumber();

    public string OfficeAreaCode
    {
        get => _officeTelephone.AreaCode;
        set => _officeTelephone.AreaCode = value;
    }

    public string OfficeNumber
    {
        get => _officeTelephone.Number;
        set => _officeTelephone.Number = value;
    }
}
```

```csharp
public class Person
{
    public string OfficeAreaCode { get; set; }
    public string OfficeNumber { get; set; }
}
```

#### 배경

클래스 인라인하기는 클래스 추출하기를 거꾸로 돌리는 리팩터링이다.

더 이상 제 역할을 못 해서 그대로 두면 안 되는 클래스는 인라인해버린다.

*이런 역설적인 상황 때문에 아마 모든 경우를 설계하지 말고(처음부터 자동차를 만들려고 하지 말고) 필요할 때 설계해야 하는 것 같다.*

#### 절차

- 소스 클래스의 각 public 메서드에 대응하는 메서드들을 타깃 클래스에 생성한다. 이 메서드들은 단순히 작업을 소스 클래스로 위임해야 한다.
- 소스 클래스의 메서드를 사용하는 코드를 모두 타킷 클래스의 위임 메서드를 사용하도록 바꾼다. 하나씩 바꿀 때마다 테스트한다.
- 소스 클래스의 메서드와 필드를 모두 타깃 클래스로 옮긴다. 하나씩 옮길 때마다 테스트한다.
- 소스 클래스를 삭제한다. (조의를 표한다..ㅠ)

#### 예시

```csharp
public class Person
{
    private TelephoneNumber _officeTelephone = new TelephoneNumber();

    public string OfficeAreaCode
    {
        get => _officeTelephone.AreaCode;
        set => _officeTelephone.AreaCode = value;
    }

    public string OfficeNumber
    {
        get => _officeTelephone.Number;
        set => _officeTelephone.Number = value;
    }
}
```

```csharp
public class Person
{
    public string OfficeAreaCode { get; set; }
    public string OfficeNumber { get; set; }
}
```

### 7.7 위임 숨기기(Hide Delegate)

```csharp
public class Person
{
    public Department Department { get; set; }
}

public class Department
{
    public Person Manager { get; set; }
}
```

```csharp
public class Person
{
    public Department Department { get; set; }

    public Person GetManager()
    {
        return Department.Manager;
    }
}

public class Department
{
    public Person Manager { get; set; }
}
```

#### 배경

모듈화 설계를 제대로 하는 핵심은 캡슐화다.

모듈들이 시스템의 다른 부분에 대해 알아야할 내 내용을 줄여준다.

캡슐화가 잘 되어 있다면 무언가를 변경해야 할 때 함께 고려해야 할 모듈 수가 적어져서 코드를 변경하기가 훨씬 쉬워진다.

객체 지향을 처음 배울 때는 캡슐화란 필드를 숨기는 것이라고 배운다.

그러다 경험이 쌓이면서 캡슐화의 역할이 그보다 많다는 사실을 깨닫는다.

서버 객체의 필드가 가리키는 객체의 메서드를 호출하려면 클라이언트는 이 위임 객체를 알아야 한다.

위임 객체의 인터페이스가 바뀌면 클라이언트가 코드를 수정해야 한다.

이러한 의존성을 없애려면 서버 자체에 위임 메서드를 만들어서 위임 객체의 존재를 숨기면 된다.

그러면 위임 객체가 수정되더라도 서버 코드만 고치면 되며, 클라이언트는 아무런 영향을 받지 않는다.

#### 절차

- 위임 객체의 각 메서드에 해당하는 위임 메서드를 서버에 생성한다.
- 클라이언트가 위임 객체 대신 서버를 호출하도록 수정한다. 하나씩 수정할 때마다 테스트한다.
- 모두 수정했다면, 서버로부터 위임 객체를 얻는 접근자를 제거한다.
- 테스트한다.

#### 예시

```csharp
public class Person
{
    public Department Department { get; set; }
}

public class Department
{
    public Manager Manager { get; set; }
}

public class Manager
{
    public string Name { get; set; }
}
```

```csharp
public class Person
{
    public Department Department { get; set; }

    public string GetManagerName()
    {
        return Department.Manager.Name;
    }
}
```

### 7.8 중개자 제거하기(Remove Middle Man)

```csharp
public class Person
{
    public Department Department { get; set; }

    public string GetManagerName()
    {
        return Department.Manager.Name;
    }
}
```

```csharp
public class Person
{
    public Department Department { get; set; }

    public string GetManagerName()
    {
        return Department.GetManagerName();
    }
}

public class Department
{
    public Manager Manager { get; set; }

    public string GetManagerName()
    {
        return Manager.Name;
    }
}
```

#### 배경

위임 숨기기와 반대되는 리팩터링으로 앞서 설명한 캡슐화의 이점이 또다른 방해요소로 작용하게 되면 적용할 수 있다.

클라이언트가 위임 객체의 또 다른 기능을 사용하고 싶을 때 마다 서버에 위임 메서드를 추가해야 하는데, 이렇게 기능을 추가하다 보면 단순히 전달만 하는 위임 메서드들이 성가셔진다.

그러면 서버 클래스는 그저 중개자 역할로 전락하여, 차라리 클라이언트가 위임 객체를 직접 호출하는 편이 낫다.

#### 절차

- 위임 객체를 얻는 게터를 만든다.
- 위임 메서드를 호출하는 클라이언트가 모두 이 게터를 거치도록 수정한다. 하나씩 바꿀 때마다 테스트한다.
- 모두 수정했다면 위임 메서드를 삭제한다.

#### 예시

```csharp
public class Person
{
    public Department Department { get; set; }

    public string GetManagerName()
    {
        return Department.GetManagerName();
    }
}

public class Department
{
    public Manager Manager { get; set; }

    public string GetManagerName()
    {
        return Manager.Name;
    }
}
```

```csharp
public class Person
{
    public Department Department { get; set; }

    public string GetManagerName()
    {
        return Department.Manager.Name;
    }
}
```

### 7.9 알고리즘 교체하기(Substitute Algorithm)

```csharp
public string FoundPerson(string[] people)
{
    for (int i = 0; i < people.Length; i++)
    {
        if (people[i].Equals("Don"))
        {
            return "Don";
        }
        if (people[i].Equals("John"))
        {
            return "John";
        }
        if (people[i].Equals("Kent"))
        {
            return "Kent";
        }
    }
    return "";
}
```

```csharp
public string FoundPerson(string[] people)
{
    string[] candidates = { "Don", "John", "Kent" };
    for (int i = 0; i < people.Length; i++)
    {
        if (candidates.Contains(people[i]))
        {
            return people[i];
        }
    }
    return "";
}
```

#### 배경

어떤 목적을 달성하는 방법은 여러 가지가 있기 마련이다.

그중에서도 다른 방법보다 쉬운 방법이 있다.

알고리즘도 마찬가지다.

#### 절차

- 교체할 코드를 함수 하나에 모은다.
- 이 함수만을 이용해 동작을 검증하는 테스트를 마련한다.
- 대체할 알고리즘을 준비한다.
- 정적 검사를 수행한다.
- 기존 알고리즘과 새 알고리즘의 결과를 비교하는 테스트를 수행한다. 두 결과가 같다면 리팩터링이 끝난다. 그렇지 않다면 기존 알고리즘을 참고해서 새 알고리즘을 테스트하고 디버깅한다.

### 느낀점

- 이번 챕터도 역시 당연하게 생각한 리팩터링도 있고 더 깊은 뜻이 있던 리팩터링도 있어서 얻어가는게 많았다.
- 계속해서 언어를 `C#`으로 작성하다 보니 좀 더 유연해진 것 같은..?

#### 논의사항

`컬렉션 캡슐화하기`에 대한 논의가 항상 많았던 것 같은데 이 부분에 대해서 이야기 해보면 좋을 것 같습니다..!

실제 프로젝트에서 DeepCopy방식으로 반환하여 불변을 보장했던 것 같은데 다른 분들은 불변 데이터 객체에 대해서 어떻게 생각하시나요?
