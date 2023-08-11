## 1. 리팩터링: 첫 번째 예시

> 원칙은 지나치게 일반화되기 쉬워서 실제 적용 방법을 파악하기 어렵지만 예시가 있으면 모든 게 명확해진다.  

1장은 앞 서 말한대로 리팩터링의 예시를 보여주는 장이다.

### 1.1 자, 시작해보자

- 다양한 연극을 외주로 받아서 공연하는 극단이 있다.
- 공연 요청이 들어오면 연극의 장르와 관객 규모를 기초로 비용을 책정한다.
- 현재 이 극단은 두 가지 장르, 비극과 희극만 공연한다.
- 공연료와 별개로 포인트를 지급해서 다음번 의뢰 시 공연료를 할인받을 수도 있다.(충성도 시스템)

극단은 공연할 연극 정보를 다음과 같이 간단한 JSON 파일에 저장한다.

```json
// plays.json
{
    "hamlet": {"name": "Hamlet", "type": "tragedy"},
    "as-like": {"name": "As You Like It", "type": "comedy"},
    "othello": {"name": "Othello", "type": "tragedy"}
}
```

공연료 청구성에 들어갈 데이터도 다음과 같이 JSON 파일에 저장한다.

```json
// invoices.json
[
    {
        "customer": "BigCo",
        "performances": [
            {
                "playID": "hamlet",
                "audience": 55
            },
            {
                "playID": "as-like",
                "audience": 35
            },
            {
                "playID": "othello",
                "audience": 40
            }
        ]
    }
]
```

공연료 청구서를 출력하는 코드는 다음과 같다.

```javascript
// function statement

function statement(invoice, plays) {
    let totalAmount = 0;
    let volumeCredits = 0;
    let result = `청구 내역 (고객명: ${invoice.customer})\n`;
    const format = new Intl.NumberFormat("en-US", {
        style: "currency", currency: "USD",
        minimumFractionDigits: 2
    }).format;

    for (let perf of invoice.performances) {
        const play = plays[perf.playID];
        let thisAmount = 0;

        switch (play.type) {
            case "tragedy": // 비극
                thisAmount = 40000;
                if (perf.audience > 30) {
                    thisAmount += 1000 * (perf.audience - 30);
                }
                break;
            case "comedy": // 희극
                thisAmount = 30000;
                if (perf.audience > 20) {
                    thisAmount += 10000 + 500 * (perf.audience - 20);
                }
                thisAmount += 300 * perf.audience;
                break;
            default:
                throw new Error(`알 수 없는 장르: ${play.type}`);
        }

        // 포인트를 적립한다.
        volumeCredits += Math.max(perf.audience - 30, 0);
        // 희극 관객 5명마다 추가 포인트를 제공한다.
        if ("comedy" === play.type) volumeCredits += Math.floor(perf.audience / 5);

        // 청구 내역을 출력한다.
        result += `${play.name}: ${format(thisAmount / 100)} (${perf.audience}석)\n`;
        totalAmount += thisAmount;
    }
    result += `총액: ${format(totalAmount / 100)}\n`;
    result += `적립 포인트: ${volumeCredits}점\n`;
    return result;
}
```

자바 스크립트 코드도 어렵지 않게 이해가 되지만 좀 더 가독성 좋은 코드를 위해 구조를 수정하지 않고 `C#`으로 바꿔서 작성하였다.

```csharp
public class Play
{
    public string name;
    public string type;

    public Play(string name, string type)
    {
        this.name = name;
        this.type = type;
    }
}
```

```csharp
public class Performance
{
    public string playID;
    public int audience;

    public Performance(string playID, int audience)
    {
        this.playID = playID;
        this.audience = audience;
    }
}
```

```csharp
public class Invoice
{
    public string customer;
    public List<Performance> performances;

    public Invoice(string customer, List<Performance> performances)
    {
        this.customer = customer;
        this.performances = performances;
    }
}
```

```csharp
public class Account
{
    public String Statment(Invoice invoice, List<Play> plays)
    {
        int totalAmount = 0;
        int volumeCredits = 0;
        string result = $"청구 내역 (고객명:{invoice.customer})\n";

        foreach (var perf in invoice.performances)
        {
            var play = plays.FirstOrDefault(p => p.name == perf.playID);
            int thisAmount = 0;

            switch (play.type)
            {
                case "tragedy":
                    thisAmount = 40000;
                    if (perf.audience > 30)
                    {
                        thisAmount += 1000 * (perf.audience - 30);
                    }

                    break;
                case "comedy":
                    thisAmount = 30000;
                    if (perf.audience > 20)
                    {
                        thisAmount += 10000 + 500 * (perf.audience - 20);
                    }

                    thisAmount += 300 * perf.audience;
                    break;
                default:
                    throw new Exception($"알 수 없는 장르:{play.type}");
            }

            // 포인트를 적립한다.
            volumeCredits += Math.Max(perf.audience - 30, 0);
            // 희극 관객 5명마다 추가 포인트를 제공한다.
            if ("comedy" == play.type) volumeCredits += (int) Math.Floor((decimal) perf.audience / 5);

            // 청구 내역을 출력한다.
            result += $"{play.name}: ${thisAmount / 100} ({perf.audience}석)\n";
            totalAmount += thisAmount;
        }

        result += $"총액: ${totalAmount / 100}\n";
        result += $"적립 포인트: {volumeCredits}점\n";

        return result;
    }
}
```

```csharp
public class Program
{
    public static void Main()
    {
        List<Play> plays = new List<Play>();
        
        plays.Add(new Play("Hamlet", "tragedy"));
        plays.Add(new Play("As You Like It", "comedy"));
        plays.Add(new Play("Othello", "tragedy"));

        List<Performance> performances = new List<Performance>();

        performances.Add(new Performance("Hamlet", 55));
        performances.Add(new Performance("As You Like It", 35));
        performances.Add(new Performance("Othello", 40));

        Invoice invoices = new Invoice("BigCo", performances);

        Account account = new Account();
        Console.WriteLine(account.Statment(invoices, plays));
    }
}
```

![image](https://github.com/fkdl0048/ToDo/assets/84510455/90d1a10e-6b29-45ca-bfc8-92e9313d4795)

*json utill까지 설치하고 직렬화 과정까진 하지 않고 객체를 생성하여 동작만 동일하게 만들었다.*

정확한 동작을 실제로 보고 싶다면 [CodeReview](https://github.com/fkdl0048/CodeReview/tree/main/Refactoring)에서 확인할 수 있다.

뒤에서 등장하는 리팩터링 과정또한 해당 코드로 진행하며 진행과정 또한 커밋으로 기록할 예정

### 1.2 예시 프로그램을 본 소감

저자와 마찬가지로 코드가 짧아서 그런지 어렵지 않게 이해할 수 있었고,

다만 막히는 부분은 본문에 없던 도메인, 요구사항이 수식으로 나오는 부분을 제외하고 동작 자체는 크게 어려움 없었다.

과연 앞 장에서도 다룬 코드는 동작하기만 하면 문제가 없는 것일까?

컴파일러는 코드가 깔끔하든 지저분하든 상관없이 동작하며 대부분 사람이 문제이다.

사람은 코드를 눈으로 보고 풀이해야 하므로 가독성과 미적인 기준은 상당히 중요하기 때문에..

*코드가 실행안될 때, 버그가 많을 때 위안이 되는 말 중 하나로 "하나는 컴퓨터는 거짓말을 하지 않는다"*

저자는 수백 줄짜리 코드를 수정할 때면 먼저 프로그램의 작동 방식을 더 쉽게 파악할 수 있도록 코드를 여러 함수와 프로그램 요소로 재구성한다.

프로그램의 구조가 빈약하다면 대체로 구조부터 바로잡은 뒤에 기능을 수정하는 편이 작업하기가 훨씬 수월하다.

> 프로그램이 새로운 기능을 추가하기에 편한 구조가 아니라면, 먼저 기능을 추가하기 쉬운 형태로 리팩터링하고 나서 원하는 기능을 추가한다.

이제 코드를 수정할 부분을 살펴보자

#### HTML 출력 기능 추가하기

사용자의 요청에 따라 HTML 출력 기능이 필요하다고 가정하자

그렇다면 HTML태크를 삽입해야 하니 문자열을 추가하는 각각을 조건문으로 감싸게 된다면, Statement함수의 복잡도가 크게 증가한다.

이런 상황이라면 대부분 이 함수의 복사본을 만들고 복사본에서 HTML을 출력하려고 할 수 있는데

이 때 복사하는 일 자체는 큰 부담이 없지만 나중에 문제를 야기할 수 있다.

청구서 작성 로직을 변경할 때 마다 기존 함수와 HTML버전 함수 모두를 수정해야 하고, 항시 일관된지 수정해야 한다.

즉, 중복에 의한 사이드 이펙트가 발생할 확률이 매우 높다.

이는 두 번째 요구사항과도 관련이 있다.

#### 다양한 장르의 추가

이번엔 희극과 비극뿐만 아니라 다양한 장르의 연극을 공연하는 요구사항이 들어왔다.

장르가 늘어남에 따라 예측할 수 없을 때 조건문을 추가해야 한다면 이후에는 폭탄해체 작업을 해야할 수 있다.

> 새로운 요구사항은 수색 대원처럼 한두 명씩이 아니라, 한 부대씩 몰려오기 마련이다.

이처럼 연극 장르와 공연료 정책이 달라질 때마다 statement()함수를 수정해야 하므로 리팩터링이 필요하다.

### 1.3 리팩터링의 첫 단계

리팩터링의 첫 단계는 항상 똑같다.

리팩터링할 코드 영역을 꼼꼼하게 검사해줄 테스트 코드들부터 마련해야 한다.

리팩터링에서 테스트의 역할은 굉장히 **중요**하다.

리팩터링 기법들이 버그 발생 여지를 최소화하도록 구성됐다고는 하나 실제 작업은 사람이 수행하기 때문에 언제든 실수할 가능성이 농후..

> 프로그램이 클수록 수정 과정에서 예상치 못한 문제가 발생할 가능성이 크다.  
> '디지털 시대의 연약한 자여, 그대 이름은 소프트웨어'

statement() 함수의 테스트는 어떻게 준비하면 될까?

이 함수가 문자열을 반환하므로, 다양한 장르의 공연들로 구성된 공연료 청구서 몇 개를 작성하여 문자열 형태로 준비한다.

그 다음 statement()가 반환한 문자열과 준비한 정답을 비교 후 테스트 프레임워크를 이용해 모든 테스트를 단축키 하나로 실행할 수 있도록 한다.

> 리팩터링하기 전에 제대로 된 테스트부터 마련한다.  
> 테스트는 반드시 자가진단하도록 만든다.

### 1.4 statement() 함수 쪼개기

statement처럼 긴 함수를 리팩터링할 때는 먼저 동작을 부분으로 나눌 수 있는 지점을 찾는다.

중간 즘 분기문이 가장 먼저 눈에 띈다.

```csharp
    public String Statment(Invoice invoice, List<Play> plays)
    {
        int totalAmount = 0;
        int volumeCredits = 0;
        string result = $"청구 내역 (고객명:{invoice.customer})\n";

        foreach (var perf in invoice.performances)
        {
            var play = plays.FirstOrDefault(p => p.name == perf.playID);
            int thisAmount = 0;

            // 주목!
            switch (play.type) 
            {
                case "tragedy":
                    thisAmount = 40000;
                    if (perf.audience > 30)
                    {
                        thisAmount += 1000 * (perf.audience - 30);
                    }

                    break;
                case "comedy":
                    thisAmount = 30000;
                    if (perf.audience > 20)
                    {
                        thisAmount += 10000 + 500 * (perf.audience - 20);
                    }

                    thisAmount += 300 * perf.audience;
                    break;
                default:
                    throw new Exception($"알 수 없는 장르:{play.type}");
            }

            // 포인트를 적립한다.
            volumeCredits += Math.Max(perf.audience - 30, 0);
            // 희극 관객 5명마다 추가 포인트를 제공한다.
            if ("comedy" == play.type) volumeCredits += (int) Math.Floor((decimal) perf.audience / 5);

            // 청구 내역을 출력한다.
            result += $"{play.name}: ${thisAmount / 100} ({perf.audience}석)\n";
            totalAmount += thisAmount;
        }

        result += $"총액: ${totalAmount / 100}\n";
        result += $"적립 포인트: {volumeCredits}점\n";

        return result;
    }
```

이 switch문은 한 번의 공연에 대한 요금을 계산하고 있다.

> 이러한 정보는 머릿속 STM에 저장되기 때문에 잊지 않으려면 재빨리 코드에 반영해야 한다.

즉, 이 함수에서 분리 가능한 부분인 것으로 `함수 추출하기`과정을 거친다.

먼저 별도로 함수로 빼냈을 때 유효범위를 벗어나는 변수, 즉 새 함수에서 곧바로 사용할 수 없는 변수가 있는지 확인한다.

이번 예에서는 perf, play, thisAmount가 해당 되며, 추출한 새 함수에서도 필요하지만 값을 변경하지 않기 때문에 매개변수로 전달하면 된다.

한편 thisAmount는 함수 안에서 값이 바뀌는데, 이런 변수는 조심해서 다뤄야 한다.

이번 예제에서는 이런 변수가 하나이므로 반환하도록 작성했다.

```csharp
private int AmountFor(Performance perf, Play play)
{
    int thisAmount = 0;

    switch (play.type)
    {
        case "tragedy": // 비극
            thisAmount = 40000;
            if (perf.audience > 30)
            {
                thisAmount += 1000 * (perf.audience - 30);
            }

            break;
        case "comedy":
            thisAmount = 30000;
            if (perf.audience > 20)
            {
                thisAmount += 10000 + 500 * (perf.audience - 20);
            }

            thisAmount += 300 * perf.audience;
            break;
        default:
            throw new Exception($"알 수 없는 장르:{play.type}");
    }

    return thisAmount;
}
```

이제 원래 함수에서는 새로 만든 함수를 호출하도록 수정한다.

```csharp
public String Statment(Invoice invoice, List<Play> plays)
{
    int totalAmount = 0;
    int volumeCredits = 0;
    string result = $"청구 내역 (고객명:{invoice.customer})\n";

    foreach (var perf in invoice.performances)
    {
        var play = plays.FirstOrDefault(p => p.name == perf.playID) ?? throw new Exception($"연극이름:{perf.playID}를 찾을 수 없습니다.");
        int thisAmount = AmountFor(perf, play);

        // 포인트를 적립한다.
        volumeCredits += Math.Max(perf.audience - 30, 0);
        // 희극 관객 5명마다 추가 포인트를 제공한다.
        if ("comedy" == play.type) volumeCredits += (int) Math.Floor((decimal) perf.audience / 5);

        // 청구 내역을 출력한다.
        result += $"{play.name}: ${thisAmount / 100} ({perf.audience}석)\n";
        totalAmount += thisAmount;
    }

    result += $"총액: ${totalAmount / 100}\n";
    result += $"적립 포인트: {volumeCredits}점\n";

    return result;
}
```

이렇게 수정하고 나면 반드시 컴파일 후 테스트를 진행하여 실수한 게 없는지 확인한다.

아무리 간단한 수정이라도 리팩터링 후에는 테스트하는 습관을 들이는 것이 바람직하다.

사람은 실수하기 마련이다.

*Clean Code에서는 이런 의식적인 행위를 수술직전 손을 씻는 의사와 비유하였다.*

또한 한 가지를 수정할 때마다 테스트하면, 오류가 생기더라도 **변경 폭이 작기 때문**에 살펴볼 범위도 좁아서 문제를 찾고 해결하기가 훨씬 쉽다.

이처럼 조금씩 변경하고 매번 테스트하는 것은 리팩터링 절차의 핵심이다.

> 리팩터링은 프로그램 수정을 작은 단계로 나눠 진행한다.  
> 그래서 중간에 실수하더라도 버그를 쉽게 찾을 수 있다.

```
생각

리팩터링, 테스트코드에 대한 객체지향적 관점에서도 훌룡하다고 생각이 든다.

리팩터링과 테스트코드를 짜는 행위 자체가 클래스, 메서드를 더욱 세분화하여 작게 만들 수 있기 때문에 더 유리하다.
```

한 번에 너무 많이 수정하려다 실수를 저지르면 디버깅하기 어려워서 결과적으로 작업 시간이 늘어난다.

조금씩 수정하여 피드백 주기를 짧게 가져가는 습관이 재앙을 피하는 길이다.

*애자일과 관련된 이야기 같다고 생각이 들며, 유능한 개발자는 몇 만줄을 수정한 개발자 보다 2~3줄의 수정으로 이뤄진 커밋이라 생각한다.*

> 리팩터링은 프로그램 수정을 작은 단계로 나눠 진행한다.  
> 그래서 중간에 실수하더라도 버그를 쉽게 찾을 수 있다.

방금 수정한 사항을 테스트했을 때 문제가 없다면 코드베이스로 병합을 진행한다.

함수를 추출하고 나면 추출된 함수 코드를 자세히 들여다보면서 지금보다 명확하게 표현할 수 있는 간단한 방법은 없는지 검토한다.

가장 먼저 변수의 이름을 더 명확하게 바꿔보자

`thisAmount`를 `result`로 변경

*저자는 함수의 반환 값에는 항상 result라는 이름을 쓴다.*

result라는 이름이 통일성을 가지게 되면 함수를 읽을 때 한가지는 명확해지게 되며 해석할 한 가지가 줄어든다.

STM측면에서도 저장될 필요 없이 LTM단위에서 작업 기억 공간에서 해결할 문제라고 생각한다.

두 번째는 Perf를 aPerformance로 변경한다.

이 또한 코드를 읽는 사람이 이해하기 쉽도록 이름을 바꾼 것이다.

> 컴퓨터가 이해하는 코드는 바보도 작성할 수 있다.  
> 이해하도록 작성하는 프로그래머가 진정한 실력자다.

이렇게 이름을 바꾸는 행위가 가치가 있는가??

물론이다. 좋은 코드라면 하는 일이 명확히 드러나야 하며, 코드를 읽는 사람이 추리를 하게 해서는 안된다.

#### play 변수 제거하기

amountFor()의 매개변수를 살펴보면서 이 값들이 어디서 오는지 확인해보면 aPerformance는 루프 변수에서 오기 때문에 반복문을 한 번 돌 때마다 자연스레 값이 변경된다.

하지만 play는 개별 공연에서 얻기 때문에 애초에 매개변수로 전달할 필요가 없다.

긴 함수를 잘게 쪼갤 때마다 play 같은 변수를 최대한 제거한다.

이런 임시 변수들 때만에 로컬 볌위에 존재하는 이름이 늘어나서 추출 작업이 복잡해지기 때문이다.

이를 해결해주는 리팩터링으로는 **임시 변수를 질의 함수로 바꾸기**가 있다.

다음으로 컴파일-테스트-커밋한 다음 변수 인라인하기를 적용한다.

```csharp
public class Account
{
    public String Statment(Invoice invoice, List<Play> plays)
    {
        int totalAmount = 0;
        int volumeCredits = 0;
        string result = $"청구 내역 (고객명:{invoice.customer})\n";

        foreach (var perf in invoice.performances)
        {
            int thisAmount = AmountFor(perf, Playfor(perf, plays));

            // 포인트를 적립한다.
            volumeCredits += Math.Max(perf.audience - 30, 0);
            // 희극 관객 5명마다 추가 포인트를 제공한다.
            if ("comedy" == Playfor(perf, plays).type) volumeCredits += (int) Math.Floor((decimal) perf.audience / 5);

            // 청구 내역을 출력한다.
            result += $"{Playfor(perf, plays).name}: ${thisAmount / 100} ({perf.audience}석)\n";
            totalAmount += thisAmount;
        }

        result += $"총액: ${totalAmount / 100}\n";
        result += $"적립 포인트: {volumeCredits}점\n";

        return result;
    }

    private int AmountFor(Performance perf, Play play)
    {
        int result = 0;

        switch (play.type)
        {
            case "tragedy": // 비극
                result = 40000;
                if (perf.audience > 30)
                {
                    result += 1000 * (perf.audience - 30);
                }

                break;
            case "comedy":
                result = 30000;
                if (perf.audience > 20)
                {
                    result += 10000 + 500 * (perf.audience - 20);
                }

                result += 300 * perf.audience;
                break;
            default:
                throw new Exception($"알 수 없는 장르:{play.type}");
        }

        return result;
    }

    private Play Playfor(Performance perf, List<Play> plays)
    {   
        return plays.FirstOrDefault(p => p.name == perf.playID) ?? throw new Exception($"연극이름:{perf.playID}를 찾을 수 없습니다.");
    }
}
```

이후 amountFor()에 함수 선언 바꾸기를 적용해서 play 매개변수를 제거할 수 있게 되었다.

```csharp
public class Account
{
    private List<Play> plays;

    public Account(List<Play> plays)
    {
        this.plays = plays;
    }

    public String Statment(Invoice invoice)
    {
        int totalAmount = 0;
        int volumeCredits = 0;
        string result = $"청구 내역 (고객명:{invoice.customer})\n";

        foreach (var perf in invoice.performances)
        {
            int thisAmount = AmountFor(perf);

            // 포인트를 적립한다.
            volumeCredits += Math.Max(perf.audience - 30, 0);
            // 희극 관객 5명마다 추가 포인트를 제공한다.
            if ("comedy" == Playfor(perf).type) volumeCredits += (int) Math.Floor((decimal) perf.audience / 5);

            // 청구 내역을 출력한다.
            result += $"{Playfor(perf).name}: ${thisAmount / 100} ({perf.audience}석)\n";
            totalAmount += thisAmount;
        }

        result += $"총액: ${totalAmount / 100}\n";
        result += $"적립 포인트: {volumeCredits}점\n";

        return result;
    }

    private int AmountFor(Performance perf)
    {
        int result = 0;

        switch (Playfor(perf).type)
        {
            case "tragedy": // 비극
                result = 40000;
                if (perf.audience > 30)
                {
                    result += 1000 * (perf.audience - 30);
                }

                break;
            case "comedy":
                result = 30000;
                if (perf.audience > 20)
                {
                    result += 10000 + 500 * (perf.audience - 20);
                }

                result += 300 * perf.audience;
                break;
            default:
                throw new Exception($"알 수 없는 장르:{Playfor(perf).type}");
        }

        return result;
    }

    private Play Playfor(Performance perf)
    {   
        return plays.FirstOrDefault(p => p.name == perf.playID) ?? throw new Exception($"연극이름:{perf.playID}를 찾을 수 없습니다.");
    }
}
```

방금 수행한 Plays -> Playfor로 변경한 과정에서 따로 캐싱하지 않고 메서드를 바로 호출하기 때문에 반복에 의한 성능 저하가 있을 수 있다.

뒤에서 리팩터링과 성능 관계를 자세히 설명하겠지만, 일단 지금은 성능엔 큰 영향이 없다.

설사 심각하게 느려지더라도 제대로 리팩터링된 코드베이스는그렇지 않은 코드베이스보다 성능을 개선하기가 훨씬 수월하다.

**변수를 제거해서 얻는 가장 큰 장점은 추출 작업이 훨씬 쉬워진다는 것**이다.

유효범위를 신경써야 할 대상이 줄어들기 때문이다.

마찬가지로 amountFor함수도 변수를 제거하고 함수로 변경, 인라인하기를 적용한다.

```csharp
public class Account
{
    private List<Play> plays;

    public Account(List<Play> plays)
    {
        this.plays = plays;
    }

    public String Statment(Invoice invoice)
    {
        int totalAmount = 0;
        int volumeCredits = 0;
        string result = $"청구 내역 (고객명:{invoice.customer})\n";

        foreach (var perf in invoice.performances)
        {
            // 포인트를 적립한다.
            volumeCredits += Math.Max(perf.audience - 30, 0);
            // 희극 관객 5명마다 추가 포인트를 제공한다.
            if ("comedy" == Playfor(perf).type) volumeCredits += (int) Math.Floor((decimal) perf.audience / 5);

            // 청구 내역을 출력한다.
            result += $"{Playfor(perf).name}: ${AmountFor(perf) / 100} ({perf.audience}석)\n";
            totalAmount += AmountFor(perf);
        }

        result += $"총액: ${totalAmount / 100}\n";
        result += $"적립 포인트: {volumeCredits}점\n";

        return result;
    }

    private int AmountFor(Performance perf)
    {
        int result = 0;

        switch (Playfor(perf).type)
        {
            case "tragedy": // 비극
                result = 40000;
                if (perf.audience > 30)
                {
                    result += 1000 * (perf.audience - 30);
                }

                break;
            case "comedy":
                result = 30000;
                if (perf.audience > 20)
                {
                    result += 10000 + 500 * (perf.audience - 20);
                }

                result += 300 * perf.audience;
                break;
            default:
                throw new Exception($"알 수 없는 장르:{Playfor(perf).type}");
        }

        return result;
    }

    private Play Playfor(Performance perf)
    {   
        return plays.FirstOrDefault(p => p.name == perf.playID) ?? throw new Exception($"연극이름:{perf.playID}를 찾을 수 없습니다.");
    }
}
```

#### 적립 포인트 계산 코드 추출하기

앞에서 play변수를 제거한 결과 로컬 유효범위의 변수가 하나 줄어서 적립 포인트 계산 부분을 추출하기가 훨씬 쉬워졌다.

```csharp
public class Account
{
    private List<Play> plays;

    public Account(List<Play> plays)
    {
        this.plays = plays;
    }

    public String Statment(Invoice invoice)
    {
        int totalAmount = 0;
        int volumeCredits = 0;
        string result = $"청구 내역 (고객명:{invoice.customer})\n";

        foreach (var perf in invoice.performances)
        {
            // 포인트를 적립한다.
            volumeCredits += VolumeCreditsFor(perf);
            // 희극 관객 5명마다 추가 포인트를 제공한다.
            if ("comedy" == Playfor(perf).type) volumeCredits += (int) Math.Floor((decimal) perf.audience / 5);

            // 청구 내역을 출력한다.
            result += $"{Playfor(perf).name}: ${AmountFor(perf) / 100} ({perf.audience}석)\n";
            totalAmount += AmountFor(perf);
        }

        result += $"총액: ${totalAmount / 100}\n";
        result += $"적립 포인트: {volumeCredits}점\n";

        return result;
    }

    private int AmountFor(Performance aPerformance)
    {
        int result = 0;

        switch (Playfor(aPerformance).type)
        {
            case "tragedy": // 비극
                result = 40000;
                if (aPerformance.audience > 30)
                {
                    result += 1000 * (aPerformance.audience - 30);
                }

                break;
            case "comedy":
                result = 30000;
                if (aPerformance.audience > 20)
                {
                    result += 10000 + 500 * (aPerformance.audience - 20);
                }

                result += 300 * aPerformance.audience;
                break;
            default:
                throw new Exception($"알 수 없는 장르:{Playfor(aPerformance).type}");
        }

        return result;
    }

    private Play Playfor(Performance aPerformance)
    {   
        return plays.FirstOrDefault(p => p.name == aPerformance.playID) ?? throw new Exception($"연극이름:{aPerformance.playID}를 찾을 수 없습니다.");
    }

    private int VolumeCreditsFor(Performance aPerformance)
    {
        int result = 0;
        result += Math.Max(aPerformance.audience - 30, 0);
        if ("comedy" == Playfor(aPerformance).type) result += (int) Math.Floor((decimal) aPerformance.audience / 5);

        return result;
    }
}
```

#### format 변수 제거하기

앞에서 말했듯이 임시 변수는 나중에 문제를 일으킬 수 있다.

**임수 변수는 자신이 속한 루틴에서만 의미가 있어서 루틴이 길고 복잡해지기 쉽다.**

따라서 다음으로 할 리팩터링은 이런 변수들을 제거하는 것이다.

*C# 달러 표시 포멧팅을 따로 몰라서 임시 Tostring 래퍼로 작성*

```csharp
public class Account
{
    private List<Play> plays;

    public Account(List<Play> plays)
    {
        this.plays = plays;
    }

    public String Statment(Invoice invoice)
    {
        int totalAmount = 0;
        int volumeCredits = 0;
        string result = $"청구 내역 (고객명:{invoice.customer})\n";

        foreach (var perf in invoice.performances)
        {
            // 포인트를 적립한다.
            volumeCredits += VolumeCreditsFor(perf);
            // 희극 관객 5명마다 추가 포인트를 제공한다.
            if ("comedy" == Playfor(perf).type) volumeCredits += (int) Math.Floor((decimal) perf.audience / 5);

            // 청구 내역을 출력한다.
            result += $"{Playfor(perf).name}: ${Format(AmountFor(perf) / 100)} ({perf.audience}석)\n";
            totalAmount += AmountFor(perf);
        }

        result += $"총액: ${Format(totalAmount / 100)}\n";
        result += $"적립 포인트: {volumeCredits}점\n";

        return result;
    }

    private int AmountFor(Performance aPerformance)
    {
        int result = 0;

        switch (Playfor(aPerformance).type)
        {
            case "tragedy": // 비극
                result = 40000;
                if (aPerformance.audience > 30)
                {
                    result += 1000 * (aPerformance.audience - 30);
                }

                break;
            case "comedy":
                result = 30000;
                if (aPerformance.audience > 20)
                {
                    result += 10000 + 500 * (aPerformance.audience - 20);
                }

                result += 300 * aPerformance.audience;
                break;
            default:
                throw new Exception($"알 수 없는 장르:{Playfor(aPerformance).type}");
        }

        return result;
    }

    private Play Playfor(Performance aPerformance)
    {   
        return plays.FirstOrDefault(p => p.name == aPerformance.playID) ?? throw new Exception($"연극이름:{aPerformance.playID}를 찾을 수 없습니다.");
    }

    private int VolumeCreditsFor(Performance aPerformance)
    {
        int result = 0;
        result += Math.Max(aPerformance.audience - 30, 0);
        if ("comedy" == Playfor(aPerformance).type) result += (int) Math.Floor((decimal) aPerformance.audience / 5);

        return result;
    }

    private string Format(int aNumber)
    {
        // usd로 변환 과정
        return aNumber.ToString();
    }
}
```

작성하고 보니 Format이라는 메서드가 하는 일이 너무 불분명하다.

또한 FormatAsUSD는 너무 정황하다(지금처럼 가시 범위가 좁다면 더더욱 맞지 않다.)

**함수 선언 바꾸기**를 적용한다.

```csharp
private string USD(int aNumber)
{
    // usd로 변환 과정
    return aNumber.ToString();
}
```

이처럼 이름 짓기는 중요하면서도 어려운 작업이다.

긴 함수를 작게 쪼개는 리팩터링은 이름을 잘 지어야만 효과가 있다.

이름이 좋으면 본문을 읽지 않고도 무슨 일을 하는지 알 수 있다.

물론 단번에 좋은 이름을 짓는 것은 어렵기 때문에 처음에 당장 떠오른 이름으로 최선의 이름을 사용하다

더 좋은 이름이 떠오르면 바꾸는 것이 좋다.

*흔히 코드를 두 번 이상 읽고 나서야 가장 적합한 이름이 떠오르곤 한다.*

#### VolumeCredits 변수 제거하기

이 변수는 반복문을 한 바퀴 돌 때마다 값을 누적하기 때문에 리팩터링하기가 더 까다롭다.

따라서 먼저 **반복문 쪼개기**로 volumeCredits를 누적하는 부분을 분리한다.

```csharp
foreach (var perf in invoice.performances)
{
    // 청구 내역을 출력한다.
    result += $"{Playfor(perf).name}: ${USD(AmountFor(perf) / 100)} ({perf.audience}석)\n";
    totalAmount += AmountFor(perf);
}

foreach (var perf in invoice.performances)
{
    // 포인트를 적립한다.
    volumeCredits += VolumeCreditsFor(perf);
}
```

이어서 **문장 슬라이드하기**를 적용해서 volumeCredits 변수를 선언하는 문장을 반복문 바로 앞으로 옯긴다.

```csharp
int volumeCredits = 0;
foreach (var perf in invoice.performances)
{
    // 포인트를 적립한다.
    volumeCredits += VolumeCreditsFor(perf);
}
```

volumeCredits 값 갱신과 관련한 문장들을 한데 모아두면 **임시 변수를 질의 함수로 바꾸기**가 수월해진다.

이번에도 역시 volumeCredits 값 계산 코드를 함수로 추출하는 작업부터 한다.

```csharp
public class Account
{
    private List<Play> plays;
    private Invoice invoice;

    public Account(List<Play> plays, Invoice invoice)
    {
        this.plays = plays;
        this.invoice = invoice;
    }
    public String Statment()
    {
        int totalAmount = 0;
        string result = $"청구 내역 (고객명:{invoice.customer})\n";

        foreach (var perf in invoice.performances)
        {
            // 청구 내역을 출력한다.
            result += $"{Playfor(perf).name}: ${USD(AmountFor(perf) / 100)} ({perf.audience}석)\n";
            totalAmount += AmountFor(perf);
        }

        result += $"총액: ${USD(totalAmount / 100)}\n";
        result += $"적립 포인트: {totalVolumeCredits()}점\n";

        return result;
    }

    private int AmountFor(Performance aPerformance)
    {
        int result = 0;

        switch (Playfor(aPerformance).type)
        {
            case "tragedy": // 비극
                result = 40000;
                if (aPerformance.audience > 30)
                {
                    result += 1000 * (aPerformance.audience - 30);
                }

                break;
            case "comedy":
                result = 30000;
                if (aPerformance.audience > 20)
                {
                    result += 10000 + 500 * (aPerformance.audience - 20);
                }

                result += 300 * aPerformance.audience;
                break;
            default:
                throw new Exception($"알 수 없는 장르:{Playfor(aPerformance).type}");
        }

        return result;
    }

    private Play Playfor(Performance aPerformance)
    {   
        return plays.FirstOrDefault(p => p.name == aPerformance.playID) ?? throw new Exception($"연극이름:{aPerformance.playID}를 찾을 수 없습니다.");
    }

    private int VolumeCreditsFor(Performance aPerformance)
    {
        int result = 0;
        result += Math.Max(aPerformance.audience - 30, 0);
        if ("comedy" == Playfor(aPerformance).type) result += (int) Math.Floor((decimal) aPerformance.audience / 5);

        return result;
    }

    private string USD(int aNumber)
    {
        return aNumber.ToString();
    }

    private int totalVolumeCredits()
    {
        int result = 0;

        foreach (var perf in invoice.performances)
        {
            result += VolumeCreditsFor(perf);
        }

        return result;
    }
}
```

*C#언어로 작성하게 되면서 멤버 변수로 올리게 되었는데 더 좋은 방법이 있을까?*

여기서 생각할 수 있는 점은 반복문을 쪼개면서 성능이 느려지지 않을까 걱정할 수 있다.

이 정도 중복은 선응에 미치는 영향이 미미할 때가 많다.

다양한 경우가 있겠지만 저자의 조언은 `특별한 경우가 아니라면 일단 무시하라`는 것이다.

리팩터링 때문에 성능이 떨어진다면, 하던 리팩터링을 마무리하고 나서 성능을 개선하자.

```
생각

게임 관련 최적화에 대한 이슈도 알아본적이 있다.

유니티 프로파일링으로 코드의 문제되는 부분을 볼 수 있어 공부한 적이 있는데

미친 코드(이상한 반복, 무한루프)가 아니고서야 기본적인 룰 풀링이나 최적화 패턴, 캐싱을 잘 지킨다면

그 이상의 최적화는 무의미하다는 결론이 나왔다.

실제로 업계에서도 최적화를 진행할 때 코드레벨이 가장 후순위로 이펙트 관련 리소스부터 줄인다고 한다.
```

다시 한번 알아보자면 volumeCredits 변수를 제거하는 작업의 단계는 아래와 같다.

- 반복문 쪼개기
- 문장 슬라이드하기
- 함수 추출하기
- 변수 인라인하기

마찬가지로 totalAmount 변수도 제거해보자.

```csharp
public class Account
{
    private List<Play> plays;
    private Invoice invoice;

    public Account(List<Play> plays, Invoice invoice)
    {
        this.plays = plays;
        this.invoice = invoice;
    }
    public String Statment()
    {
        string result = $"청구 내역 (고객명:{invoice.customer})\n";

        foreach (var perf in invoice.performances)
        {
            // 청구 내역을 출력한다.
            result += $"{Playfor(perf).name}: ${USD(AmountFor(perf) / 100)} ({perf.audience}석)\n";
        }

        result += $"총액: ${USD(TotalAmount() / 100)}\n";
        result += $"적립 포인트: {totalVolumeCredits()}점\n";

        return result;
    }

    private int AmountFor(Performance aPerformance)
    {
        int result = 0;

        switch (Playfor(aPerformance).type)
        {
            case "tragedy": // 비극
                result = 40000;
                if (aPerformance.audience > 30)
                {
                    result += 1000 * (aPerformance.audience - 30);
                }

                break;
            case "comedy":
                result = 30000;
                if (aPerformance.audience > 20)
                {
                    result += 10000 + 500 * (aPerformance.audience - 20);
                }

                result += 300 * aPerformance.audience;
                break;
            default:
                throw new Exception($"알 수 없는 장르:{Playfor(aPerformance).type}");
        }

        return result;
    }

    private Play Playfor(Performance aPerformance)
    {   
        return plays.FirstOrDefault(p => p.name == aPerformance.playID) ?? throw new Exception($"연극이름:{aPerformance.playID}를 찾을 수 없습니다.");
    }

    private int VolumeCreditsFor(Performance aPerformance)
    {
        int result = 0;
        result += Math.Max(aPerformance.audience - 30, 0);
        if ("comedy" == Playfor(aPerformance).type) result += (int) Math.Floor((decimal) aPerformance.audience / 5);

        return result;
    }

    private string USD(int aNumber)
    {
        return aNumber.ToString();
    }

    private int totalVolumeCredits()
    {
        int totalAmount = 0;

        foreach (var perf in invoice.performances)
        {
            totalAmount += VolumeCreditsFor(perf);
        }

        return totalAmount;
    }

    private int TotalAmount()
    {
        int result = 0;

        foreach (var perf in invoice.performances)
        {
            result += AmountFor(perf);
        }

        return result;
    }
}
```

### 1.5 중간 점검: 난무하는 중첩 함수

지금까지의 리팩터링결과를 살펴보면 구조가 많이 좋아졌다.

```csharp
public class Account
{
    private List<Play> plays;
    private Invoice invoice;

    public Account(List<Play> plays, Invoice invoice)
    {
        this.plays = plays;
        this.invoice = invoice;
    }
    public String Statment()
    {
        string result = $"청구 내역 (고객명:{invoice.customer})\n";

        foreach (var perf in invoice.performances)
        {
            // 청구 내역을 출력한다.
            result += $"{Playfor(perf).name}: ${USD(AmountFor(perf) / 100)} ({perf.audience}석)\n";
        }

        result += $"총액: ${USD(TotalAmount() / 100)}\n";
        result += $"적립 포인트: {totalVolumeCredits()}점\n";

        return result;
    }

    private int AmountFor(Performance aPerformance)
    {
        int result = 0;

        switch (Playfor(aPerformance).type)
        {
            case "tragedy": // 비극
                result = 40000;
                if (aPerformance.audience > 30)
                {
                    result += 1000 * (aPerformance.audience - 30);
                }

                break;
            case "comedy":
                result = 30000;
                if (aPerformance.audience > 20)
                {
                    result += 10000 + 500 * (aPerformance.audience - 20);
                }

                result += 300 * aPerformance.audience;
                break;
            default:
                throw new Exception($"알 수 없는 장르:{Playfor(aPerformance).type}");
        }

        return result;
    }

    private Play Playfor(Performance aPerformance)
    {   
        return plays.FirstOrDefault(p => p.name == aPerformance.playID) ?? throw new Exception($"연극이름:{aPerformance.playID}를 찾을 수 없습니다.");
    }

    private int VolumeCreditsFor(Performance aPerformance)
    {
        int result = 0;
        result += Math.Max(aPerformance.audience - 30, 0);
        if ("comedy" == Playfor(aPerformance).type) result += (int) Math.Floor((decimal) aPerformance.audience / 5);

        return result;
    }

    private string USD(int aNumber)
    {
        return aNumber.ToString();
    }

    private int totalVolumeCredits()
    {
        int totalAmount = 0;

        foreach (var perf in invoice.performances)
        {
            totalAmount += VolumeCreditsFor(perf);
        }

        return totalAmount;
    }

    private int TotalAmount()
    {
        int result = 0;

        foreach (var perf in invoice.performances)
        {
            result += AmountFor(perf);
        }

        return result;
    }
}
```

최상위 Statement함수는 이제 단 7줄로 표현되고 있으며 출력할 문장을 생성하는 일만 담당한다.

계산 로직은 전부 보조함수로 빼내었다.

### 1.6 계산 단계와 포맷팅 단계 분리하기

지금까지는 프로그램의 **논리적인 요소를 파악하기 쉽도록 코드의 구조를 보강**하는 데 주안점을 두고 리팩터링 했다.

골격은 충분히 개선되었으니 이제 원하던 기능 statement()의 HTML버전을 만드는 작업을 시작해보자.

*C# 성격상 내가 작성한 코드는 이미 Statement()함수내에서 중첩함수로 설계하지 않았다.*

우리는 텍스트 버전과 HTML버전을 모두 똑같은 계산 함수들을 사용하게 만들고 싶다.

저자가 다양한 해결책 중 가장 선호하는 방식은 **단계 쪼개기**다.

statement()의 로직을 두 단계로 나누는 것으로 statement에서 필요한 데이터를 처리하고, 다음 단계에서 텍스트나 HTML로 표현하도록 한다.

단계를 쪼개려면 먼저 두 번째 단계가 될 코드들을 **함수 추출하기**로 뽑아내야 한다.

이 과정에서 두 번째 단계는 청구 내역을 출력하는 코드인데, 현재는 본문에 해당한다.

```csharp
public String Statment()
{
    return renderPlainText();
}

private string renderPlainText()
{
    string result = $"청구 내역 (고객명:{invoice.customer})\n";

    foreach (var perf in invoice.performances)
    {
        // 청구 내역을 출력한다.
        result += $"{Playfor(perf).name}: ${USD(AmountFor(perf) / 100)} ({perf.audience}석)\n";
    }

    result += $"총액: ${USD(TotalAmount() / 100)}\n";
    result += $"적립 포인트: {totalVolumeCredits()}점\n";

    return result;
}
```

역시 컴파일-테스트-커밋 단계를 거치고 두 단계 사이의 중간 데이터 구조 역할을 할 객체를 만들어서 renderPlainText()함수에 전달한다.

*좀 더 객체지향적, c#에 맞게 설계하려면 render쪽이 인터페이스처럼 제작되어 클래스 단위로 동작, 즉 협력 객체가 되어야 할 듯 하다.*

```csharp
public class Account
{
    private List<Play> plays;
    private Invoice invoice;

    public Account(List<Play> plays, Invoice invoice)
    {
        this.plays = plays;
        this.invoice = invoice;
    }
    public String Statment()
    {
        Invoice statementData = new Invoice(invoice.customer , invoice.performances);
        return renderPlainText(statementData);
    }

    private string renderPlainText(Invoice statementData)
    {
        string result = $"청구 내역 (고객명:{statementData.customer})\n";

        foreach (var perf in statementData.performances)
        {
            // 청구 내역을 출력한다.
            result += $"{Playfor(perf).name}: ${USD(AmountFor(perf) / 100)} ({perf.audience}석)\n";
        }

        result += $"총액: ${USD(TotalAmount() / 100)}\n";
        result += $"적립 포인트: {totalVolumeCredits()}점\n";

        return result;
    }

    private int AmountFor(Performance aPerformance)
    {
        int result = 0;

        switch (Playfor(aPerformance).type)
        {
            case "tragedy": // 비극
                result = 40000;
                if (aPerformance.audience > 30)
                {
                    result += 1000 * (aPerformance.audience - 30);
                }

                break;
            case "comedy":
                result = 30000;
                if (aPerformance.audience > 20)
                {
                    result += 10000 + 500 * (aPerformance.audience - 20);
                }

                result += 300 * aPerformance.audience;
                break;
            default:
                throw new Exception($"알 수 없는 장르:{Playfor(aPerformance).type}");
        }

        return result;
    }

    private Play Playfor(Performance aPerformance)
    {
        // 메서드 내부 메서드 불가능하기 때문에 클래스 멤버로 처리
        return plays.FirstOrDefault(p => p.name == aPerformance.playID) ?? throw new Exception($"연극이름:{aPerformance.playID}를 찾을 수 없습니다.");
    }

    private int VolumeCreditsFor(Performance aPerformance)
    {
        int result = 0;
        result += Math.Max(aPerformance.audience - 30, 0);
        if ("comedy" == Playfor(aPerformance).type) result += (int) Math.Floor((decimal) aPerformance.audience / 5);

        return result;
    }

    private string USD(int aNumber)
    {
        return aNumber.ToString();
    }

    private int totalVolumeCredits()
    {
        int totalAmount = 0;

        foreach (var perf in invoice.performances)
        {
            totalAmount += VolumeCreditsFor(perf);
        }

        return totalAmount;
    }

    private int TotalAmount()
    {
        int result = 0;

        foreach (var perf in invoice.performances)
        {
            result += AmountFor(perf);
        }

        return result;
    }
}
```

사실 지금 구조는 매우 불편한 구조라고 할 수 있다.

추상화 레벨도 다르고, 전혀 다형성을 고려하지 않았기 때문에 올바르지 못한 구조라고 생각된다.

하지만 뒤에서 더 이어나가는 부분이 있기 때문에 일단 따라가고 이후에 리팩토링을 진행해보자.

*언어의 차이 때문에 내부함수를 두지 못하기 때문에 단순하게 클래스로 구분하던가 인터페이스를 활용하여 이쁘게 가져가야 한다.*

연극 제목의 중간 데이터 구조에서 가져오기 위해 얕은 복사를 수행하는 모습도 있다.

가변 데이터에 대한 위험성과 불변 데이터로 처리하는 이유에 대해선 Clean Code나 C#의 레코드라는 type을 알아보면 좀 더 쉽게 이해가 된다.

#### C# 코드로 재구성

최대한 구조를 생각하면서 만들었는데 js코드의 특성을 잘 이해하지 못해서 조금 엉터리 코드가 된 것 같기도 하다.

문제가 된 부분은 Performace가 동적으로 확장되는 부분인 것 같은데 C#의 튜플처럼 동작하는 건지..

C#코드로 나타내기 위해서 새로운 클래스를 생성하여 책임을 분리하였다.

또한 각각 Statement를 인터페이스로 분리하였고 Stateprinter라는 클래스로 DI통한 의존성 역전 및 단일 책임을 부여하였다.

```csharp
// StatementData 클래스
public class StatementData
{
    public readonly string customer;
    public readonly List<EnrichPerformance> performances;
    public readonly int totalAmount;
    public readonly int totalVolumeCredits;

    public StatementData(Invoice invoice, List<Play> plays)
    {
        this.customer = invoice.customer;
        this.performances = new List <EnrichPerformance>();
        foreach (var perf in invoice.performances)
        {
            this.performances.Add(new EnrichPerformance(perf, plays));
        }
        this.totalAmount = TotalAmount();
        this.totalVolumeCredits = TotalVolumeCredits();
    }

    private int TotalAmount()
    {
        int result = 0;
        foreach (var perf in performances)
        {
            result += perf.amount;
        }
        return result;
    }

    private int TotalVolumeCredits()
    {
        int result = 0;
        foreach (var perf in performances)
        {
            result += perf.volumeCredits;
        }
        return result;
    }
}
```

```csharp
// EnrichPerformance 클래스
public class EnrichPerformance
{
    private List<Play> plays;
    public Play play;
    public int amount;
    public int volumeCredits;
    public int audience;

    public EnrichPerformance(Performance aPerformace, List<Play> plays)
    {
        this.plays = plays;
        this.play = PlayFor(aPerformace);
        this.amount = AmountFor(aPerformace);
        this.volumeCredits = VolumeCreditsFor(aPerformace);

        audience = aPerformace.audience;
    }

    private Play PlayFor(Performance aPerformance)
    {
        return plays.FirstOrDefault(p => p.name == aPerformance.playID) ?? throw new Exception ($"연극이름:{aPerformance.playID}를 찾을 수 없습니다.");
    }

    private int AmountFor(Performance aPerformance)
    {
        int result = 0;
        switch (play.type)
        {
            case "tragedy":
                result = 40000;
                if (aPerformance.audience > 30)
                {
                    result += 1000 * (aPerformance.audience - 30);
                }
                break;
            case "comedy":
                result = 30000;
                if (aPerformance.audience > 20)
                {
                    result += 10000 + 500 * (aPerformance.audience - 20);
                }
                result += 300 * aPerformance.audience;
                break;
            default:
                throw new Exception($"알 수 없는 장르:{play.type}");
        }
        return result;
    }

    private int VolumeCreditsFor(Performance aPerformance)
    {
        int result = 0;
        result += Math.Max(aPerformance.audience - 30, 0);
        if ("comedy" == PlayFor(aPerformance).type) result += (int) Math.Floor((decimal) aPerformance.audience / 5);

        return result;
    }

}
```

```csharp
// IStatement 인터페이스
public interface IStatement
{
    public string Statement();
}
```

```csharp
// TextStatement 클래스
public class TextStatement : IStatement
{
    private readonly Invoice invoice;
    private readonly List<Play> plays;

    public TextStatement(Invoice invoice, List<Play> plays)
    {
        this.invoice = invoice;
        this.plays = plays;
    }
    
    public string Statement()
    {
        return RenderPlainText(new StatementData(invoice, plays));
    }

    private string RenderPlainText(StatementData data)
    {
        string result = $"청구 내역 (고객명:{data.customer})\n";

        foreach (var perf in data.performances)
        {
            result += $" {perf.play.name}: {Usd(perf.amount)} ({perf.audience}석)\n";
        }
        
        result += $"총액: {Usd(data.totalAmount)}\n";
        result += $"적립 포인트: {data.totalVolumeCredits}점\n";

        return result;
    }

    private string Usd(int aNumber)
    {
        return string.Format("${0:#,##0.00}", aNumber / 100);
    }
}
```

```csharp
// HtmlStatement 클래스
public class HtmlStatement : IStatement
{
    private readonly Invoice invoice;
    private readonly List<Play> plays;
    public HtmlStatement(Invoice invoice, List<Play> plays)
    {
        this.invoice = invoice;
        this.plays = plays;
    }
    public string Statement()
    {
        return RenderHtml(new StatementData(invoice, plays));
    }

    private string RenderHtml(StatementData data)
    {
        string result = $"<h1>청구 내역 (고객명:{data.customer})</h1>\n";

        result += "<table>\n";
        result += "<tr><th>연극</th><th>좌석 수</th><th>금액</th></tr>";
        foreach (var perf in data.performances)
        {
            result += $"<tr><td>{perf.play.name}</td><td>{perf.audience}</td>";
            result += $"<td>{Usd(perf.amount)}</td></tr>\n";
        }
        result += "</table>\n";

        result += $"<p>총액: <em>{Usd(data.totalAmount)}</em></p>\n";
        result += $"<p>적립 포인트: <em>{data.totalVolumeCredits}</em>점</p>\n";

        return result;
    }

    private string Usd(int aNumber)
    {
        return string.Format("${0:#,##0.00}", aNumber / 100);
    }
}
```

```csharp
// StatementPrinter 클래스
public class StatementPrinter
{
    private IStatement statement;
    public StatementPrinter(IStatement statement)
    {
        this.statement = statement;
    }

    public void Print()
    {
        Console.WriteLine(statement.Statement());
    }
}
```

```csharp
public class Program
{
    public static void Main()
    {
        List<Play> plays = new List<Play>();
        
        plays.Add(new Play("Hamlet", "tragedy"));
        plays.Add(new Play("As You Like It", "comedy"));
        plays.Add(new Play("Othello", "tragedy"));

        List<Performance> performances = new List<Performance>();

        performances.Add(new Performance("Hamlet", 55));
        performances.Add(new Performance("As You Like It", 35));
        performances.Add(new Performance("Othello", 40));

        Invoice invoices = new Invoice("BigCo", performances);

        // Account account = new Account(plays, invoices);
        // Console.WriteLine(account.Statment());

        StatementPrinter statementPrinter = new StatementPrinter(new TextStatement(invoices, plays));
        statementPrinter.Print();

        statementPrinter = new StatementPrinter(new HtmlStatement(invoices, plays));
        statementPrinter.Print();
    }
}
```

문제가 되는 부분은 EnrichPerformance클래스의 확장으로 인한 Performance클래스의 중복값 발생이다.

나중에 사용자가 모르고 사용한다면 더블 체크나 사이드 이펙트가 발생할 가능성이 높다.

그래도 코드 자체의 줄수가 줄어들고 추상화 레벨에 맞게 분리되어 있게 리팩터링을 진행했다.

다 작성하고 나니 보이는 추가 수정사항은 public 말고 c#의 특성에 맞게 프로퍼티로 작성했으면 더 좋았을 것 같다.

readonly가 몇개 부실하거나 불변성을 보장하지 못하는 부분 몇개..

### 1.7 중간 점검: 두 파일로 분리됨

책에서는 data와 statement로 두개로 분리되었지만

내 코드에선 data 두가지, statment는 인터페이스로 두 가지로 분리되었다.

처음 코드에 비해 양이 매우 많이 늘었지만 전체 로직 자체는 더 뚜렷하게 분리되어 있다.

각 출력 형식 이전에 data를 해당 로직에서 생성 후 출력 형식은 각각 인터페이스에 맞게 제작하여 printer로 넘겨준다.

> 캠핑자들에게는 "도착했을 때보다 깔끔하게 정돈하고 떠난다."라는 규칙이 있다.  
> 프로그래밍도 마찬가지다.  
> 항시 코드베이스를 작업 시작 전보다 건강하게 만들어놓고 떠나야 한다.

### 1.8 다형성을 활용해 계산 코드 재구성하기

현재 amoutFor()함수를 보면 연극 장르에 따라 계산 방식이 달라진 다는 것을 알 수 있다.

이런 조건부 형식의 코드는 수정횟수가 늘어남에 따라 버그도 덩달아 같이 늘어나게 된다.

명확한 구조를 보완하는 방법은 다양하지만 객체지향의 다형성을 활용하는 것이 바람직하다.

여기서 사용되는 리팩터링 기법이 **조건부 로직을 다형성으로 바꾸기**다.

간단하게 생성 디자인 패턴 중 팩토리 메서드 패턴을 생각하면 간단하다.

인터페이스 레벨에서 DI까지 말고 switch 정도로 구현해본다.

```csharp
// PerformanceCalculator 클래스
public interface IPerformaceCalculator
{
    int AmountFor();
    int VolumeCreditsFor();
    Play GetPlay();
}
```

```csharp
// PerformanceCalculator 클래스
public class ComedyCalculator : IPerformaceCalculator
{
    private Performance aPerformance;
    private Play play;

    public ComedyCalculator(Performance aPerformance, Play play)
    {
        this.aPerformance = aPerformance;
        this.play = play;
    }

    public int AmountFor()
    {
        int result = 30000;
        if (aPerformance.audience > 20)
        {
            result += 10000 + 500 * (aPerformance.audience - 20);
        }

        result += 300 * aPerformance.audience;
        return result;
    }

    public int VolumeCreditsFor()
    {
        return (int) Math.Floor((decimal) aPerformance.audience / 5);
    }

    public Play GetPlay()
    {
        return play;
    }
}
```

```csharp
// PerformanceCalculator 클래스
public class TragedyCalculator : IPerformaceCalculator
{
    private Performance aPerformance;
    private Play play;

    public TragedyCalculator(Performance aPerformance, Play play)
    {
        this.aPerformance = aPerformance;
        this.play = play;
    }

    public int AmountFor()
    {
        int result = 40000;
        if (aPerformance.audience > 30)
        {
            result += 1000 * (aPerformance.audience - 30);
        }

        return result;
    }

    public int VolumeCreditsFor()
    {
        return Math.Max(aPerformance.audience - 30, 0);
    }

    public Play GetPlay()
    {
        return play;
    }
}
```

```csharp
// PerformanceCalculator 클래스
public class EnrichPerformance
{
    private List<Play> plays;
    public Play play;
    public int amount;
    public int volumeCredits;
    public int audience;

    public EnrichPerformance(Performance aPerformace, List<Play> plays)
    {
        this.plays = plays;

        IPerformaceCalculator calculator = CreatePerformanceCalculator(aPerformace, PlayFor(aPerformace));

        this.play = calculator.GetPlay();
        this.amount = calculator.AmountFor();
        this.volumeCredits = calculator.VolumeCreditsFor();

        audience = aPerformace.audience;
    }

    private Play PlayFor(Performance aPerformance)
    {
        return plays.FirstOrDefault(p => p.name == aPerformance.playID) ?? throw new Exception ($"연극이름:{aPerformance.playID}를 찾을 수 없습니다.");
    }

    private IPerformaceCalculator CreatePerformanceCalculator(Performance aPerformance, Play aPlay)
    {
        switch (aPlay.type)
        {
            case "tragedy":
                return new TragedyCalculator(aPerformance, aPlay);
            case "comedy":
                return new ComedyCalculator(aPerformance, aPlay);
            default:
                throw new Exception($"알 수 없는 장르:{aPlay.type}");
        }
    }
}
```

EnrichPerformance부분에 Calculator 팩토리 메서드를 넣어뒀는데 사실 SRP를 위반하기에 따로 Factory 클래스를 만들어서 분리하는 것이 좋다.

그게 핵심이 아니니.. 자세한 내용은 블로그를 참고

[링크](https://fkdl0048.github.io/patterns/Patterns_FactoryMethod/)

### 1.9 상태 점검: 다형성을 활용하여 데이터 생성하기

앞서 함수를 추출했을 때와 같이 구조를 보강하면서 코드가 늘어났다.

이번 수정으로 나아진 점은 연극 장르별 계산 코드들이 함께 묶이면서 가독성이 올라갔다는 것

수정, 추가가 편리하다.

새로운 장르를 추가하기 위해선 해당 인터페이스를 상속받아서 추가하기만 하면 된다.

### 1.10 마치며

간단한 예로 리팩터링을 진행하였다.

- 함수 추출하기
- 변수 인라인하기
- 함수 옮기기
- 조건부 로직을 다형성으로 바꾸기

등 다양한 리팩터링 기법을 알아봤다.

이번 장에선 리팩터링을 크게 3 단계로 진행했다.

먼저 원본 함수를 중첩 함수 여러 개로 나눴다.

다음으로 단계 쪼개기를 적용하여 계산 코드와 출력코드를 구분했다.

마지막으로 계산로직을 다형성으로 표현했다.

책과 다른 점은 출력로직또한 인터페이스를 활용하여 다형성을 적용했다는 점이다.

이 외에도 코드에 적용해야할 리팩터링이 많이 남아있지만 이번 장에선 과정정도로 이해한다.

> 좋은 코드를 가늠하는 확실한 방법은 '얼마나 수정하기 쉬운가'디.

프로그래머 사이에서 좋은 코드에 대한 의견은 항상 분분하다.

저자가 선호하는 `적절한 이름의 작은 함수들`로 만드는 방식에 대하는 사람도 분명 있을 것이다.

미적인 관점으로 접근하게 되면 좋고 나쁨이 명확하지 않아서 개인 취향 말고는 어떠한 지침도 세울 수 없다.

하지만 취향을 넘어선 관점이 분명하게 존재하며, 코드를 `수정하기 쉬운 정도`야 말로 좋은 코드를 가늠하는 가장 확실한 방법이다.

**코드는 명확해야 한다.**

건강한 코드베이스는 생산성을 극대화하고, 고객에 필요한 기능을 더 빠르고 저렴한 비용으로 제공하도록 해준다.

이번 예시에서 배울 수 있는 가장 중요한 부분은 리팩터링하는 **리듬**이다.  

각 단계를 마칠 때마다 테스트하고 동작을 확인한다.

이는 곧 단계를 작게 나누고, 더 빠르게 처리하고, 코드가 절대 망가지지 않게 해준다.

이러한 작은 단계들이 모여 상당히 큰 변화를 이룰 수 있다는 것을 알게 될 것이다.

### 느낀점

1장부터 예제로 리팩터링의 전반을 설명해줘서 좋은 책임을 직감했다.

앞서 읽은 클린코드가 코드를 작성하면서 지켜야 할 패턴이라면 리팩터링은 이미 작성된 코드를 개선하는 방법이다.(이미 동작하는)

그 과정이 크게 다르지 않을 것이라 생각했는데 읽어보니 깨닫게 되는 부분이 많았다.

우리는 처음부터 자동차를 만들 수 없기 때문에 리팩터링은 필수적이라는 사실..

> 가장 느리게 가는길이 가장 빠른 길이다.

읽으면서 1챕터는 여러번 다시 읽어야할 부분이라고 생각되며 1챕터를 제대로 읽어야지 뒷 부분을 공감하며, 이해할 수 있을 것 같다.

다른 책에서도 공통적으로 느끼는 점이지만 이런 패턴, 리듬을 빨리 파악하는게 중요한 것 같다.

*전체적으로 다시 읽어보니 너무 `다.`로 끝나는 다다체가 너무 많은 듯..*

#### 논의사항

스스로 리팩터링을 하지 않는(회피하는) 이유는 뭘까요?

저는 개인적으로 귀찮아서(귀찮다고 생각한 이유는 지금 생각해보면 해당 프로젝트에 애정이 없었던 것 같습니다.)가 가장 큽니다.
