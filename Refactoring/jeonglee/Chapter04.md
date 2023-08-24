## 4. 테스트 구축하기

리팩터링은 가치있는 도구이지만, 제대로 활용하려면 실수를 잡아주는 견고한 **테스트 스위트**가 필요하다.

*리팩터링을 꼭하지 않더라도 테스트 코드 작성은 필요하다. 전체적인 개발효율을 높여준다.*

### 4.1 자가 테스트 코드의 가치

실상 프로그래머는 코드를 짜는 시간은 얼마 되지 않는다.

읽거나 고민하는 시간이 훨씬 더 많다.

사실 버그를 해결하는 것은 금방 해결되지만 가장 끔찍한 것은 **버그를 찾는 과정**이다.

이런 과정에서 사이드 이펙트가 발생하여 다른 버그를 양산할 수 있다..

테스트 코드를 직접 작성하고 이를 하나씩 확인하는 과정에서 지금의 Junits나 NUnit 같은 테스트 프레임워크가 탄생하게 되었다.

> 모든 테스트를 완전히 자동화하고 그 결과까기 스스로 검사하게 만들자

테스트를 작성하기 가장 좋은 시간은 **프로그래밍을 시작하기 전**이다.

예를 들어 기능을 추가하기 전에 테스트부터 작성한다면, 원하는 기능을 추가하기 위해 무엇이 필요한지 고민하게 된다.

**구현보다 인터페이스에 집중**하게 된다는 장점이 있다.

또한 테스트 코드가 작성되어 있다면 작업이 완료되는 시점을 정확하게 판단할 수 있다.(테스트가 다 통과한 시점)

이게 조금 더 극단적으로 가면 **테스트 주도 개발(TDD)**이다.

*이후 TDD관련 책을 읽어도 좋을 것 같다는 생각*

### 4.2 테스트할 샘플 코드

이 코드도 1장에서 내가 `C#`으로 변경해서 작업한 것과 같이 내 입맛에 맞춰서 실습해 볼 예정이다.

비즈니스 로직 코드는 클래스 두 개로 구성되며, 하나는 생산자를 표현하는 Producer이고, 다른 하나는 지역 전체를 표현하는 Province이다.

*마찬가지로 json import과정을 생략하고 main에서 객체로 넣는 방식을 채택*

- 테스트할 샘플 코드는 `C# windowforms으로 제작`
- 자바스크립트에서 C#으로 변환이기에 어색한 부분이 있음

![image](https://github.com/fkdl0048/ToDo/assets/84510455/5b6658c9-edff-4e49-b6fa-9bb5e8168cd9)

[리팩터링 4Chapter 레포](https://github.com/fkdl0048/CodeReview/tree/main/Refactoring/Chapter04)

```csharp
public class Producer
{
    private Province province;
    private string name;
    private int cost;
    private int production;

    public Producer(Province province, string name, int cost, int production)
    {
        this.province = province;
        this.name = name;
        this.cost = cost;
        this.production = production;
    }

    public string GetName()
    {
        return name;
    }

    public int GetCost()
    {
        return cost;
    }

    public void SetCost(int arg)
    {
        cost = arg;
    }

    public int GetProduction()
    {
        return production;
    }

    public void SetProduction(int arg)
    {
        production = arg;
        // 수정
    }
}
```

```csharp
public class Province
{
    private string name;
    private List<Producer> producers = new List<Producer>();
    private int totalProduction;
    private int demand;
    private int price;

    public Province(string name, int demand, int price)
    {
        this.name = name;
        this.demand = demand;
        this.price = price;
        this.totalProduction = 0;
    }

    public void AddProducer(Producer arg)
    {
        producers.Add(arg);
        totalProduction += arg.GetProduction();
    }

    public string GetName()
    {
        return name;
    }

    public int GetTotalProduction()
    {
        return totalProduction;
    }

    public void SetTotalProduction(int arg)
    {
        totalProduction = arg;
    }

    public int GetDemand()
    {
        return demand;
    }

    public void SetDemand(int arg)
    {
        demand = arg;
    }

    public int GetPrice()
    {
        return price;
    }

    public void SetPrice(int arg)
    {
        price = arg;
    }

    public List<Producer> GetProducers()
    {
        return producers;
    }

    public int Shortfall()
    {
        return demand - totalProduction;
    }

    public int Profit()
    {
        return DemandValue() - DemandCost();
    }

    public int DemandValue()
    {
        return satisfiedDemand() * price;
    }

    public int DemandCost()
    {
        int remainingDemand = demand;
        int result = 0;
        producers.Sort((a, b) => a.GetCost() - b.GetCost());
        foreach (Producer p in producers)
        {
            int contribution = Math.Min(remainingDemand, p.GetProduction());
            remainingDemand -= contribution;
            result += contribution * p.GetCost();
        }
        return result;
    }

    public int satisfiedDemand()
    {
        return Math.Min(demand, totalProduction);
    }
}
```

```csharp
namespace Chapter04;

public partial class Form1 : Form
{
    private Province province;

    public Form1()
    {
        InitializeData();
        InitializeComponent();
    }

    private void InitializeData()
    {
        province = new Province("Asia", 30, 20);
        province.AddProducer(new Producer(province, "Byzantium", 10, 9));
        province.AddProducer(new Producer(province, "Attalia", 12, 10));
        province.AddProducer(new Producer(province, "Sinope", 10, 6));
    }
}
```

```csharp
namespace Chapter04;

partial class Form1
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;
    private System.Windows.Forms.Label titleLabel = null;
    private System.Windows.Forms.Label header_1 = null;
    private System.Windows.Forms.Label header_2 = null;
    private System.Windows.Forms.Label header_3 = null;

    private Font titleFont = null;
    private Font bodyFont = null;

    /// <summary>
    ///  Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }
        base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    ///  Required method for Designer support - do not modify
    ///  the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        titleFont = new Font("Arial", 16, FontStyle.Bold);
        bodyFont = new Font("Arial", 10, FontStyle.Regular);

        this.components = new System.ComponentModel.Container();
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(600, 350);
        this.Text = "리팩터링 Chapter04";

        this.titleLabel = new System.Windows.Forms.Label();
        this.titleLabel.Location = new System.Drawing.Point(10, 10);
        this.titleLabel.Size = new System.Drawing.Size(500, 30);
        this.titleLabel.Text = "지역:" + province.GetName();
        this.titleLabel.Font = titleFont;
        this.Controls.Add(this.titleLabel);

        this.header_1 = new System.Windows.Forms.Label();
        this.header_1.Location = new System.Drawing.Point(30, 60);
        this.header_1.Size = new System.Drawing.Size(200, 20);
        this.header_1.Text = $"수요: {province.GetDemand()}     가격: {province.GetPrice()}";
        this.header_1.Font = bodyFont;
        this.Controls.Add(this.header_1);

        this.header_2 = new System.Windows.Forms.Label();
        this.header_2.Location = new System.Drawing.Point(10, 120);
        this.header_2.Size = new System.Drawing.Size(100, 20);
        this.header_2.Text = $"생산자 수: {province.GetProducers().Count}";
        this.header_2.Font = bodyFont;
        this.Controls.Add(this.header_2);

        // FlowLayoutPanel 생성
        FlowLayoutPanel flowLayoutPanel = new FlowLayoutPanel();
        flowLayoutPanel.FlowDirection = FlowDirection.TopDown;
        flowLayoutPanel.Location = new System.Drawing.Point(30, 150);
        flowLayoutPanel.Size = new System.Drawing.Size(1000, 150);

        // FlowLayoutPanel에 Button 컨트롤 추가
        for (int i = 0; i < province.GetProducers().Count ; i++)
        {
            Label label = new Label();
            label.Text = $"{province.GetProducers()[i].GetName()}:  비용: {province.GetProducers()[i].GetCost()}  생산량: {province.GetProducers()[i].GetProduction()} 수익: {province.GetProducers()[i].GetCost() * province.GetProducers()[i].GetProduction()}";
            label.Font = bodyFont;
            label.Size = new System.Drawing.Size(300, 40);
            flowLayoutPanel.Controls.Add(label);
        }

        this.Controls.Add(flowLayoutPanel); // 폼에 FlowLayoutPanel 추가

        this.header_3 = new System.Windows.Forms.Label();
        this.header_3.Location = new System.Drawing.Point(10, 300);
        this.header_3.Size = new System.Drawing.Size(200, 20);
        this.header_3.Text = $"부족분: {province.Shortfall()} 총수익: {province.Profit()}";
        this.header_3.Font = bodyFont;
        this.Controls.Add(this.header_3);

        this.ResumeLayout(false);
    }

    #endregion
}
```

```csharp
namespace Chapter04;

static class Program
{
    /// <summary>
    ///  The main entry point for the application.
    /// </summary>
    [STAThread]
    static void Main()
    {
        // To customize application configuration such as set high DPI settings or default font,
        // see https://aka.ms/applicationconfiguration.
        ApplicationConfiguration.Initialize();
        Application.Run(new Form1());
    }    
}
```

### 4.3 첫 번째 테스트

위에서 작성한 코드를 테스트하기 위해선 먼저 테스트 프레임워크를 마련해야 한다.

C#의 경우 NUnit을 사용하면 된다.

```
dotnet add package NUnit
```

*테스트 코드 작성 예시*

```csharp
namespace Province_Test;

public class Tests
{
    private Province asia;

    [SetUp]
    public void SetUp()
    {
        asia = Chapter04.Program.SampleProvinceData();
    }

    [Test]
    public void Shortfall()
    {
        Assert.AreEqual(5, asia.Shortfall());
    }
}
```

책에서 말한 픽스처(고정장치)는 SetUp, Init과정으로 위 처럼 테스트를 위해 사용할 객체를 초기화하는 과정이라 생각된다.

*테스트 코드 실행 결과*

![image](https://github.com/fkdl0048/ToDo/assets/84510455/9df14768-a372-4e50-b22b-0e1c4765fd38)

1단계 픽스처(여기선 SetUp, 클래스쪽에 애트리뷰트로 다는 경우)

2단계 해당 픽스처의 속성들을 검증한다.

> 실패해야 할 상황에서는 반드시 실패하게 만들자

문제없이 통과했다는 것은 좋은 일이지만 테스트 코드의 정확성을 위해 오류를 주입해보는 것도 좋은 방법이다.

![image](https://github.com/fkdl0048/ToDo/assets/84510455/ee79f819-f201-4ffc-bf30-6364a71d39bf)

> 자주 테스트하라. 작성 중인 코드는 최소한 몇 분 간격으로 테스트하고, 적어도 하루에 한 번은 전체 테스트를 돌려보자

지금은 한개의 테스트이지만 실전은 수백, 수천개의 테스트 코드가 존재할 수 있다.

이런 경우에 내가 지금 사용하는 것과 같이 CLI의 과정은 좋지 못한 것 같다.

Extension에서 GUI테스트 코드 확장을 설치하여 NUnit의 기능을 좀 더 활용해보는 것도 좋을 것 같다.

![image](https://github.com/fkdl0048/ToDo/assets/84510455/a3af57ff-9a67-4c68-ad5f-ab8d91f76520)

*ClI에서 GUI로 변경*

위 GUI와 같이 테스트를 자주 실행하고 간편하게 확인한다면 무언가 실패했을 때 금방 확인할 수 있다.

간결한 피드백은 자가 테스트에서 매우 중요하다.

### 4.4 테스트 추가하기

이번에는 클래스가 하는 일을 모두 살펴보고 각각의 기능에서 오류가 생길 수 있는 조건을 하나씩 테스트하는 식으로 진행한다.

*일부 프로그래머가 좋아하는 public메서드를 빠짐없이 테스트하는 방식과는 다르다.*

> 테스트는 위험 요인을 중심으로 작성해야 하며, 테스트의 목적은 어디까지나 현재 혹은 향후에 발생하는 버그를 찾는 데 있다.

> 완벽하게 만드느라 테스트를 수행하지 못하느니, 불완전한 테스트라도 작성해 실행하는 편이 낫다.

저자는 테스트 코드의 기대값을 설정할 때 오류 주입을 통해 확인한다.

```csharp
namespace Province_Test;

[TestFixture]
public class Tests
{
    private Province asia;

    [SetUp]
    public void SetUp()
    {
        asia = Chapter04.Program.SampleProvinceData();
    }

    [Test]
    public void Shortfall()
    {
        Assert.AreEqual(5, asia.Shortfall());
    }

    [Test]
    public void Profit()
    {
        Assert.AreEqual(230, asia.Profit());
    }
}
```

지금까지 작성된 두 테스트에는 문제점이 하나 있다.

같은 객체를 공유하기 때문에 테스트의 순서에 따라 결과가 달라지거나 불변을 보장하지 못하기에 문제가 될 수 있다는 점이다.

하지만 `C# Nunit`의 경우 [SetUp] 애트리뷰트를 통해 테스트를 실행하기 전 매번 초기화를 진행한다.

*1회만 하고 싶다면 [OneTimeSetUp]을 붙이면 된다.*

불변이 정말로 보장된다면 공유 픽스처를 사용할 수 있지만 애초에 테스트에서 픽스처 값을 변경하지 못하도록 하는 것이 중요하다.

> 따라서 가장 쉬운 방법이 위와 같이 테스트 전에 한번 씩 픽스처를 만드는 것이다.

### 4.5 픽스처 수정하기

지금까지 작성한 테스트 코드를 통해 픽스처를 불러와 그 속성을 확인하는 방법을 알 수 있었다.

그런데 실전에서는 사용자가 값을 변경하면서 픽스처의 내용도 수정되는 경우가 흔하다.

이런 수정은 대부분 세터에서 이뤄지는데, 세터는 보통 아주 단순하여 버그가 생길 일도 없으니 잘 테스트하지 않는다.

하지만 복잡한 동작이 포함되어 있다면 테스트해볼 필요가 있다.

SetUp에서 `설정`한 표준 픽스처를 취해서, 테스트를 `수행`하고, 이 픽스처가 기대한 대로 처리했는지 `검증`한다.

이를 준비(arrange), 실행(act), 단언(assert)이라고 부른다.

### 4.6 경계 조건 검사하기

**지금까지 작성한 테스트는 모든 일이 순조롭고 사용자의 의도대로 사용하는, 일명 `꽃길`상황에 집중하였다.**

그런데 이 범위를 벗어나는 경계 지점에서 문제가 생기면 어떤 일이 벌어지는지 확인하는 테스트도 함께 작성하면 좋다.

생산자가 없거나 수요가 없거나 수요가 마이너스인 경우와 같이 경계 조건을 테스트하는 것이다.

여기서 드는 의문으로 수요가 음수일 때 수익이 음수가 나온다는 것이 이 프로그램을 사용하는 고객관점에서 말이 되는 소리일까?

이처럼 경계를 확인하는 테스트를 작성해보면 특이 상황, 예외적인 상황에 대해 더 잘 이해할 수 있다.

> 문제가 생길 가능성이 있는 부분을 생각해보고 그 부분을 집중적으로 테스트하자

`실패`와 `에러`의 차이를 명확하게 하는 것도 중요하다.

실패란 검증 단계에서 실제 값이 예상 범위를 벗어났다는 뜻이고, 에러는 성격이 조금 다르다.

검증보다 앞선 과정에서 발생한 예외 상황을 말한다.

그렇다면 테스트를 어느 수준까지 해야 할까?

아무리 꼼꼼한 테스트를 하더라도 버그 없는 완벽한 프로그램을 만들 수는 없다.

반면 테스트가 프로그래밍 속도를 높여준다는 사실에는 변함이 없다.

정말 많은 테스트 기법들이 있지만 너무 몰입할 필요는 없다..!

또한 테스트에 너무 집중하여 작성하다 보면 오히려 의욕이 떨어질 수 있기 때문에 위험한 부분에 집중하는 것이 좋다.

### 4.7 끝나지 않은 여정

이 책의 주제는 테스트가 아닌 리팩터링이다. (테스트 내용만 따로 책으로 읽는 걸 추천,)

테스트에 관한 내용은 방대하고 계속 변하가기에 처음부터 완벽한 테스트 코드를 작성하려고 하지 말자.

테스트 과정 또한, 배워가는 과정 모두 리팩터링의 일부라고 생각하자.

### 느낀점

논의사항으로 대체

#### 논의사항

저번 논의사항에서도 말했지만 테스트 코드를 제대로 활용하기 위해선 객체지향적인 스킬이 먼저 선행되어야 한다고 생각합니다.

물론 테스트 코드를 작성하다 보면 객체지향적으로 코딩하게 되는 좋은 선순환이 있지만 그전에 제대로 된 이해가 되어야 할 것 같습니다.

`좋은 코드, 나쁜 코드`에서 읽은 내용인데 테스트 코드를 짤 때 빠지는 함정이 스스로 짠 로직에서 통과할 수 있는 케이스만 만드는 것에 대한 내용이 나오는데 그 당시에는 이해가 되지 않았지만 작성하다 보니 무슨말인지 알겠더라구요

마찬가지로 스스로 테스트 코드를 작성하실 때 조심해야하는 부분, 포인트가 있을까요?

*비슷한 내용으로 '실패해야 할 상황에서는 반드시 실패하게 만들자'가 있었습니다.*
