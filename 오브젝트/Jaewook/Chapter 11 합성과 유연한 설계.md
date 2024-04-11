
합성은 상속과 달리 객체의  구현이 아닌 퍼블릭 인터페이스에 의존한다. 때문에 객체 내부 구현이 변경되어도 영향을 줄일 수 있으며 결합도 또한 낮다.또한 퍼블릭 인터페이스에 의존하기 때문에 런타임 시간에 의존할 수 있다. 

## 01 상속을 합성으로 변경하기

10장의 상속에는 3가지 문제점이 있었다.

1. **불필요한 인터페이스 상속 문제**
		자식 클래스에게는 부적합한 부모 클래스의 오퍼레이션이 상속되기 때문에 자식 클래스 인스턴스의 상태가 불안정해지는 문제 -java.util.Properties와 java.util.Stack의 문제
2. **메서드 오버라이딩의 오작용 문제**
		자식 클래스가 부모 클래스의 메서드를 오버라이딩할 때 자식 클래스가 부모 클래스의 메서드 호출 방법에 영향을 받는 문제 - java.util.HashSet을 상속받는 InstrumentedHashSet의 문제
3. **부모 클래스와 자식 클래스의 동시 수정 문제**
		부모 클래스와 자식 클래스 사이의 개념적인 결합으로 인해 부모 클래스를 변경할 때 자식 클래스도 함께 변경해야 하는 문제 Playlist를 상속받는 PersonalPlaylist의 예를 살펴봤다.

#### 불필요한 인터페이스 상속 문제: java.util.Properties와 java.util.Stack

Hashtable클래스와 Properties 클래스 사이의 상속관계를 합성관계로 바꿔보자.

```java
public class Properties{
	private Hashtable<String, String> properties=new Hashtable<>();

	public String setProperty(String key, String value){
		return properties.put(key,value);
	}
	public String getProperty(String key){
		return properties.get(key);
	}
}

```

Proprties는 Hashtable의 불필요한 오퍼레이션들이 사용되지 않아 퍼블릭 인터페이스를 오염시키지 않는다. 또한 상속과 달리 Properties는 Hashtable의 내부구현을 알지 못한다. 다만 get과 set을 통해서만 Hashtable과 협력할 수 있을 뿐이다.

Stack도 마찬가지로 합성으로 고쳐보자
```java
public class Stack<E>{
	private Vector<E> elements = new Vector<>();
	public E push(E item){
		elements.addElement(item);
		return item;

	}
	public E pop() {
		if(elemnts.ieEmpty()){
			throw new EmptyStackException();	
		}
		return elements.remove(elements.size()-1);
	}
}
```
Stack은 Vector가 임의의 위치에 추가하거나 삭제하는 오퍼레이터를 포함하지 않는다. 다만 Vector의 기능을 이용해 마지막 위치에만 추가하고 삭제하는 기능을 구현했을 뿐이다.

#### 메서드 오버라이딩 오작용 문제 : InstrumentedHashSet

Properties와 Stack은 불필요한 퍼블릭 인터페이스를 넣지 않게 하기 위해 합성을 사용해 기능을 제한했다. 하지만 InstrumentedHashSet은 HashSet의 모든 퍼블릭 인터페이스를 그대로 제공해야 한다.

HashSet의 구현 결합도를 낮추면서  퍼블릭 인터페이스를 그대로 상속받을 수 있는 방법은 자바의 인터페이스를 사용하면 된다.


```java

//예시
private int addCount=0;
private Set<E> set;
@Override
public boolean addAll(Collection<? extends E> c){
	addCount+=c.size();
	return set.addAll(c);
}

@Override public boolean remove(Object o){return set.remove(o)};
@Override public void clear() {set.clear();}
@Override public boolean equals(Object o){return set.equals(o);}
@Override public int hashCode() {return set.hashCode();}
...

```

Set의 오퍼레이션을 오버라이딩한 메서드 내부에서 똑같이 실행하는 모습이 보인다. 이를 **포워딩(forwarding)** 이라 부르며 동일한 메서드를 호출하기 위해 추가된 메서드는 **포워딩 메서드(forwarding method)** 라고 부른다. 포워딩은 기존 메서드의 구현에 대한 결합없이 일부 작동 방식만 바꾸고 싶을 때  유용한 방식이다.

#### 부모와 자식 클래스의 동시 수정 문제: PersonalPlaylist

Playlist의 경우에는 합성을 사용하더라도 PersonalPlaylist를 함께 수정해야 하는 문제는 해결되지 않는다.

```java

private Playlist playlist=new Playlist();

public void remove(Song song){
	playlist.getTracks().remove(song);
	playlist.getSingers().remove(song.getSinger());
}

```

그럼에도 합성이 상속보다 좋은 점은 Playlist의 내부 구현이 변경되더라도 그 파급효과를 PersonalPlaylist의 내부로 캡슐화할 수 있기 때문이다.

## 02 상속으로 인한 조합의 폭발적인 증가

상속으로 인해 결합도가 높아지면 기능을 조합해 더 큰 기능을 수행하는 객체를 만들 때 다음과 같은 문제가 발생한다.

- 하나의 기능을 추가하거나 수정하기 위해 불필요하게 많은 수의 클래스를 추가하거나 수정해야 한다.
- 단일 상속만 지원하는 언어에서는 상속으로 인해 오히려 중복 코드의 양이 늘어날 수있다.
#### 기본 정책과 부가 정책 조합하기

10장의 핸드폰 과금 시스템의 기본 정책에 (기본 요금제, 심야 할인 요금제) 부가 정책을 추가해보자.

기본정책은 통화량을 기반으로 요금이 책정되지만 부가정책은 통화량과 무관하게 기본 정책에 선택적으로 추가할 수 있는 요금 방식을 의미한다. 10장에 추가된 세금 같은 경우 부가 정책의 한 종류로 '세금 정책'에 속할 것이다. 일정 금액 할인하는 '기본 요금 할인 정책'도 존재한다.

- 기본 정책
	- 일반 요금제
	- 심야 할인 요금제
- 부가 정책
	- 세금 정책
	- 기본 요금 할인 정책

부가 정책은 다음의 특성을 가진다.

***기본 정책의 계산 결과에 적용된다*

세금 정책은 기본 정책인 RegularPhone이나 NightlyDiscountPhone의 계산이 끝난 결과에 세금을 부과한다.

**선택적으로 적용할 수 있다**

기본 정책의 계산 결과에 세금 정책을 적용할 수 있고 적용하지 않을 수도 있다.

**조합 가능하다**

기본 정책에 세금 정책만 적용하는 것도 가능하고, 기본 요금 할인 정책만 적용하는 것도 가능하다. 또한 세금 정책과 기본 요금 할인 정책을 함께 적용하는 것도 가능해야 한다.

**부가 정책은 임의의 순서로 적용 가능하다**

기본 정책에 세금 정책과 기본 요금 할인 정책을 함께 적용할 경우 세금 정책을 적용한 후에 기본 요금 할인 정책을 적용할 수 있고, 기본 요금 할인 정책을 적용한 후에 세금 정책을 적용할 수도 있다.

#### 상속을 이용해서 기본 정책 구현하기

```java
public abstract class Phone {

    private List<Call> calls = new ArrayList<>();

  

    public Money calculateFee() {

        Money result = Money.ZERO;

  

        for(Call call : calls) {

            result = result.plus(calculateCallFee(call));

        }

  

        return afterCalculated(result);

    }

  

    protected Money afterCalculated(Money fee) {

        return fee;

    }

  

    protected abstract Money calculateCallFee(Call call);

}

public class RegularPhone extends Phone {

    private Money amount;

    private Duration seconds;

  

    public RegularPhone(Money amount, Duration seconds) {

        this.amount = amount;

        this.seconds = seconds;

    }

  

    @Override

    protected Money calculateCallFee(Call call) {

        return amount.times(call.getDuration().getSeconds() / seconds.getSeconds());

    }

}

public class NightlyDiscountPhone extends Phone {

    private static final int LATE_NIGHT_HOUR = 22;

  

    private Money nightlyAmount;

    private Money regularAmount;

    private Duration seconds;

  

    public NightlyDiscountPhone(Money nightlyAmount, Money regularAmount, Duration seconds) {

        this.nightlyAmount = nightlyAmount;

        this.regularAmount = regularAmount;

        this.seconds = seconds;

    }
    @Override

    protected Money calculateCallFee(Call call) {

        if (call.getFrom().getHour() >= LATE_NIGHT_HOUR) {

            return nightlyAmount.times(call.getDuration().getSeconds() / seconds.getSeconds());

        } else {

            return regularAmount.times(call.getDuration().getSeconds() / seconds.getSeconds());

        }

    }

}

```

기존에 상속으로 구현했던 Phone과 RegularPhone, NightlyDiscountPhone이다.

#### 기본 정책에 세금 정책 조합하기

일반 요금제에 세금 정책을 조합해야 한다면 RegularPhone을 상속받은 TaxableRegularPhone 클래스를 추가하면 된다. 다만 calculateFee를 super를 통해 호출하는 것 보다 상위 클래스인 Phone에 추상 메서드를 추가해 동작의 명세를 기술한다면 부모클래스와 자식 클래스 사이의 결합도를 낮출 수 있다.
```java

protected abstract Money calculateFee(Call call);
protected abstract Money afterCalculated(Money fee);

```
afterCalculated는 전체 요금을 계산한 후 수행할 로직이다.

RegularPhone은 요금을 수정할 필요가 없기에 그대로 반환한다.

```java
//RegularPhone에서...
@Override
protected Money afterCalculated(Money fee){
	return fee;
}
```

NightyDiscountPhone 클래스 역시 수정한다.

```java
//NightyDiscountPhone에서...
@Override
protected Money calculateCallFee(Call call){
if(call.getFrom().getHour()>=LATE_NIGHT_HOUR){
	return nightlyAmout.times(call.getDuration().getSeconds()/seconds.getSeconds());
	else{
	return regularAmout.tiems(call.getDuration().getSeconds()/seconds.getSeconds());
	}
}
@Override
protected Money afterCallCalculated(Money fee){
	return fee;
	}
}
```

하지만 상속계층에 전반적으로 값을 그대로 반환하는 afterCallCulculated가 반복된 코드로 나타난다. 유연성을 유지하면서 중복 코드를 제거할 방법은 Phone에서 afterCalculated메서드에 대해 기본 구현을 제공하는 것이다.

```java
//Phone에서...
protected Money afterCalculated(Money fee){
return fee;
}
protected abstract Money calculateCallFee(Call call);
```

> [!note] 추상 메서드와 훅 메서드
> 
> 추상 메서드의 단점은 상속 계층에 속하는 모든 자식 클래스가 추상 메서드를 오버라이딩해야 한다는 것이다. 상속 계층 전반에 걸쳐 중복 코드가 존재하게 될텐데 이를 해결하기 위해선 메서드에 기본 구현을 제공하는 것이다. 이런 편의를 위해 기본 구현을 제공하는 메서드를 **훅 메서드(hook method)** 라고 부른다. `afterCalculated` 메서드가 훅 메서드이다.

TaxableRegularPhone을 수정해보자 afterCalculated메서드를 오버라이딩한 후 fee에 세금을 더해 반환하도록 구현하자

```java
public class TaxableRegularPhone extends RegularPhone{

...

@Override
	protected Money afterCalculated(Money fee){
		return fee.plus(fee.times(taxRate);
	}
}

```

NightlyDiscountPhone에도 TaxableNightlyDiscountPhone을 추가해 세금을 계산할 수 있도록 한다. 구현은 TaxableRegularPhone과 같이 afterCalculated를 오버라이드한다.


TaxableRegularPhone과 TaxableNightlyDiscountPhone은 부모클래스의 이름을 제외하면 코드가 거의 동일하다. ->  자바를 비롯한 대부분의 객체지향 언어는 단일 상속만 지원하기 때문에 상속으로 인해 발생하는 중복 코드를 피하기 쉽지 않다.

#### 기본 정책에 기본 요금 할인 정책 조합하기

기본요금 할인 정책 또한 마찬가지로 afterCalculated를 상속한 RateDiscountableRegularPhone(혹은 TaxableNightlyDiscountPhone)을 추가하면 된다.
마찬가지로 중복된 코드가 생성된다.

#### 중복 코드의 덫에 걸리다

부가 정책은 자유롭게 조합할 수 있어야 하며 적용되는 순서 역시 임의로 결정할 수 있어야 한다. 세금 정책을 적용한 후 기본 요금 할인 정책을 적용하거나 그 반대의 순서로 적용하는 것도 가능해야 한다.

TaxableAndRateDiscountableRegularPhone과 RateDiscountableAndTaxableRegularPhone을 만들어야 하며 NightlyDiscountPhone도 똑같이 만들어야 한다.

이러한 상속 계층에는 새로운 정책을 추가하기가 어렵다. 현재의 설계에 새로운 정책을 추가하기 위해서는 불필요하게 많은 수의 클래스를 상속 계층 안에 추가해야 한다.

![[Pasted image 20240411023510.png]]

**클래스 폭발(class explosion)** :상속의 남용으로 하나의 기능을 추가하기 위해 필요 이상으로 많은 수의 클래스를 추가해야 하는 상황

클래스 폭발은 자식클래스가 부모 클래스의 구현에 필요 이상으로 강하게 결합되는 상속의 한계 떄문에 일어난다.
컴파일타임에 결정된 부모 클래스와 자식 클래스의 관계는 변경 시킬 수 없기 때문에 다양한 조합이 필요한 상황에서 해결방법은 조합의 수만큼 클래스를 추가하는 것 뿐이다.

## 03 합성 관계로 변경하기

상속관계는 컴파일타임에 결정되고 고정되기 때문에 코드 실행 중 변경할 수 없다.
따라서 조합 경우 별로 클래스를 추가해야 하는 클래스 폭발 문제에 직면한다.

합성은 컴파일타임 관계를 런타임 관계로 변경해 이 문제를 해결한다.  합성은 구현이 아닌 퍼블릭 인터페이스에 대해서만 의존할 수 있기 때문에 런타임에  객체의 관계를 변경할 수 있다. 

합성은 구현 시점에 정책들의 관계를 고정시킬 필요가 없으며 실행 시점에 정책들의 관계를 유연하게 변경할 수 있게 된다. 컴파일 의존성에 속박되지 않고 다양한 방식의 런타임 의존성을 구성할 수 있는 것이 합성의 장점이다.

*컴파일 의존성과 런타임 의존성의 거리가 멀어질 수록 설계의 복잡도는 상승한다.*
대부분의 경우 단순한 설계가 정답이지만 변경에 따른 고통이 복잡성으로 인한 혼란을 넘어선다면 유연성을 위해 단순한 설계를 포기하는 것이 현명하다.
#### 기본 정책 합성하기

우선은 핸드폰에서 요금계산 방법이라는 개념을 분리시킨다.

```java
public interface RatePolicy{
	Money calculateFee(Phone phone)
}
```

RatePolicy는 기본정책과 부가정책을 포괄하는 인터페이스다.

```java
public abstract class BasicRatePolicy implements RatePolicy {

    @Override

    public Money calculateFee(Phone phone) {

        Money result = Money.ZERO;

  

        for(Call call : phone.getCalls()) {

            result.plus(calculateCallFee(call));

        }

  

        return result;

    }

  

    protected abstract Money calculateCallFee(Call call);

}
```

```java
public class RegularPolicy extends BasicRatePolicy {

    private Money amount;

    private Duration seconds;

  

    public RegularPolicy(Money amount, Duration seconds) {

        this.amount = amount;

        this.seconds = seconds;

    }

  

    @Override

    protected Money calculateCallFee(Call call) {

        return amount.times(call.getDuration().getSeconds() / seconds.getSeconds());

    }

}
```

```java
public class NightlyDiscountPolicy extends BasicRatePolicy {

    private static final int LATE_NIGHT_HOUR = 22;

  

    private Money nightlyAmount;

    private Money regularAmount;

    private Duration seconds;

  

    public NightlyDiscountPolicy(Money nightlyAmount, Money regularAmount, Duration seconds) {

        this.nightlyAmount = nightlyAmount;

        this.regularAmount = regularAmount;

        this.seconds = seconds;

    }

  

    @Override

    protected Money calculateCallFee(Call call) {

        if (call.getFrom().getHour() >= LATE_NIGHT_HOUR) {

            return nightlyAmount.times(call.getDuration().getSeconds() / seconds.getSeconds());

        }

  

        return regularAmount.times(call.getDuration().getSeconds() / seconds.getSeconds());

    }

}
```

```java
public class Phone {

    private RatePolicy ratePolicy;

    private List<Call> calls = new ArrayList<>();

  

    public Phone(RatePolicy ratePolicy) {

        this.ratePolicy = ratePolicy;

    }

  

    public List<Call> getCalls() {

        return Collections.unmodifiableList(calls);

    }

  

    public Money calculateFee() {

        return ratePolicy.calculateFee(this);

    }

}
```

기본 정책을 이용해 요금을 계산하는 Phone의 생성자에 RatePolicy가 추가됨을 주목해야 한다.
Phone은 다양한 요금 정책과 협력할 수 있어야 하므로 요금 정책의 타입이 RatePolicy로 정의돼 있다 Phone은 이 컴파일타임 의존성을 런타임 의존성으로 대체하기 위해 생성자를 통해 주입받는다.

일반 요금제나 심화 요금제를 계산하고 싶으면 다음과 같이 Phone과 합성하면 된다.
```java
Phone phone = new Phone(new RaegularPolicy(Money.wons(10),Duration.ofSeconds(10)));

Phone phone = new Phone(new NightlyDiscountPolicy(Money.wons(5),Money.wons(10),Duration.ofSeconds(10)));

```

합성을 사용하게 되면 Phone은 RatePolicy가 어떤 타입인지에 따라 요금을 계산하는 방식이 달라진다.

#### 부가 정책 적용하기

부가 정책은 다음 두 가지 제약에 따라 구현해야 한다.

- 부가 정책은 기본 정책이나 다른 부가 정책의 인스턴스를 참조할 수 있어야 한다. 다시 말해 부가 정책의 인스턴스는 어떤 종류의 정책과도 합성될 수 있어야 한다.
- Phone의 입장에서 자신이 기본 정책의 인스턴스에게 메시지를 전송하는지 부가 정책의 인스턴스에 메시지를 전송하는 지 몰라야 한다. 다시 말해 기본 정책과 부가 정책은 협력 안에서 동일한 역할을 수행해야 한다. 

부가 정책을 AdditionalRatePolicy  추상 클래스로 구현하자.

```java
public abstract class AdditionalRatePolicy implements RatePolicy {

    private RatePolicy next;
    
    public AdditionalRatePolicy(RatePolicy next) {
        this.next = next;
    }
    @Override
    public Money calculateFee(Phone phone) {
        Money fee = next.calculateFee(phone);
        return afterCalculated(fee) ;
    }
    abstract protected Money afterCalculated(Money fee);
}
```

AdditionalRatePolicy는 다른 타입과 조합될 수 있도록 RatePolicy 타입의 next를 인스턴스 변수로 내부에 포함시킨다. 생성자를 통해 RatePolicy를 주입받고 그 변수를 next에 전달한다.

세금 정책
```java
public class TaxablePolicy extends AdditionalRatePolicy {

    private double taxRatio;

  

    public TaxablePolicy(double taxRatio, RatePolicy next) {

        super(next);

        this.taxRatio = taxRatio;

    }

  

    @Override

    protected Money afterCalculated(Money fee) {

        return fee.plus(fee.times(taxRatio));

    }

}
```

기본 요금 할인 정책
```java
public class RateDiscountablePolicy extends AdditionalRatePolicy {

    private Money discountAmount;

  

    public RateDiscountablePolicy(Money discountAmount, RatePolicy next) {

        super(next);

        this.discountAmount = discountAmount;

    }

  

    @Override

    protected Money afterCalculated(Money fee) {

        return fee.minus(discountAmount);

    }

}
```

#### 기본 정책과 부가 정책 합성하기

이제는 다양한 방식으로 정책들을 조합할 수 있는 설계가 됐다.

```java
Phone phone = new Phone(
	new TaxablePolicy(0.05,
			new RegularPolicy(...))
);

Phone phone = new Phone(
	new TaxablPolicy(0.05,
		new RateDiscountablePolicy(Money.wons(1000),
			new RegularPolicy(...)))
);
Phone phone = new Phone(
	new RateDiscountablPolicy(Money.wons(1000),
		new TaxablePolicy(0.05,
			new RegularPolicy(...)))
);
Phone phone = new Phone(
	new RateDiscountablPolicy(Money.wons(1000),
		new TaxablePolicy(0.05,
			new NightlyDiscountPolicy(...)));
```

#### 새로운 정책 추가하기

상속에서는 새로운 부가 정책을 추가하기 위해 상속계층에 불필요할 정도로 많은 클래스를 추가해야 했지만 합성은 클래스 '하나'만을 추가해 원하는 방식으로 조합하면 된다.

요구사항이 변경될 시에도 오직 하나의 클래스만을 수정해도 된다. 세금 정책을 변경한다고 하면 TaxablePolicy 클래스 하나만을 변경하면 된다. 즉 단일 책임 원칙을 준수하고 있다는 의미이다.

## 04 믹스인


**믹스인(mixin)** : 객체를 생성할 때 코드 일부를 클래스 안에 섞어 넣어 재사용하는 기법

상속과 유사하지만 상속보다 유연한 관계를 구성할 수 있다. 특정 코드의 재사용에 특화된 방법이면서 상속처럼 높은 결합도 문제를 초래하지 않는다.

믹스인은 Flavors라는 언어에서 처음 도입됐고 이후 Flavors의 특징을 흡수한 CLOS(Common Lisp Object System)에 의해 대중화 됐다.

책에서는 스칼라 언어에서 제공하는 트레이트(trait)를 이용해 믹스인을 구현한다.
#### 트레이트로 부가 정책 구현하기

트레이트로 섞어 넣게될 대상은 기본 정책에 해당하는 RegularPolicy와 NightlyDiscountPolicy다.

다음은 부가 정책 중 세금 정책에 해당하는 TaxablePolicy 트레이트다.
```scala
trait TaxablePolicy extends BasicRatePolicy {
  val taxRate: Double
  override def calculateFee(phone: Phone): Money = {
    val fee = super.calculateFee(phone)
    return fee + fee * taxRate
  }
}

```

TaxablePolicy 는 BasicRatePolicy를 확장한다. 이것은 상속의 개념이 아니라 TaxablePolicy가 BasicRatePolicy나 그의 자손에 해당하는 경우에만 믹스인될 수 있다는 뜻이다.

부가 정책은 항상 기본 정책의 처리가 완료된 후에 실행돼야 한다. 따라서 BasicRatePolicy의 calculateFee를 오버라이딩한 후 super를 통해 BasicRatePolicy의 calculateFee를 실행한 후 자신의 처리를 한다.

BasicRatePolicy를 상속받고 super를 통해 호출한다는 점에서 기존의 상속과 차이가 없어보이지만 트레이트에서는 TaxablePolicy가 실제로 BasicRatePolicy의 자식이 되는 것은 아니다. 위 코드의 extends는 단지 TaxablePolicy가 사용될 문맥을 제한한다. TaxablePolicy는 BasicRatePolicy를 상속받은 경우에만 믹스인될 수 있기 때문에 RegularPolicy나 NightlyDiscountPolicy에 믹스인될 수 있으며 나아가 미래에 추가될 BasicRatePolicy의 자손에도 믹스인될 수 있다.

이는 믹스인이 동적임을 의미한다. TaxablePolicy는 어떤 코드에 믹스인될 지 알 수 없으며 단지 BasicRatePolicy를 상속받은 코드에 믹스인된다는 사실만 알 수 있다. 이는 상속과 달리 부가 정책과 기본 정책을 구현한 코드 사이에 어떠한 관계도 존재하지 않음을 의미한다.

super로 참조되는 코드 역시 고정되지 않고 호출시 calculateFee를 보관하는 메서드는 트레이트가 믹스인되는 시점에 결정된다.

TaxablePolicy의 super호출의 경우 실행되는 코드는 RegularPolicy에 믹스인 된다면 RegularPolicy의 calculateFee가 호출된다. 마찬가지로 NightlyDiscountPolicy에 믹스인 된다면 NightlyDiscountPolicy의 caculateFee가 호출된다.

즉 super참조의 대상은 컴파일 시점이 아닌 실행 시점에 결정된다는 것을 의미한다. 이는 곧 상속과 달리 this참조와 super참조가 동적으로 결정된다는 것을 의미한다.


두 번째 부가 정책인 비율 할인 정책 또한 동일하게 구현된다.
```scala
trait RateDiscountablePolicy extends BasicRatePolicy {
  val discountAmount: Money
  
  override def calculateFee(phone: Phone): Money = {
    val fee = super.calculateFee(phone)
    fee - discountAmount
  }  
}
```

#### 부가정책 트레이트 믹스인하기

스칼라의 트레이트는 다른 트레이트에 믹스인할 수 있도록 extends와 with 키워드를 제공한다. 믹스인 대상 클래스에 부모 클래스가 존재한다면 extends로 상속받고 트레이트는 with로 믹스인해야 한다. 이를 **트레이트 조합(trait composition)** 이라고 부른다.

표준 요금제에 세금 정책을 조합한다면 믹스인 트레이트는 TaxablePolicy이고 조합될 클래스는 RegularPolicy다. 따라서 extends를 통해 RegularPolicy를 상속받고 with를 통해 TaxablePolicy 트레이트를 믹스인한다.
```scala
class TaxableRegularPolicy(amount: Money, seconds: Duration, val taxRate: Double) 
  extends RegularPolicy(amount, seconds) 
  with TaxablePolicy
```

이 객체에서 calculateFee 메시지를 전송하면 TaxableRegularPolicy 다음에 TaxablePolicy,그 다음으로 RegularPolicy 순서로 호출된다.


심야 할인 요금제인 NightlyDiscountPolicy 클래스에 NightlyDiscountPolicy트레이트를 믹스인 하는 경우에도 동일하다.
```scala
class TaxableNightlyDiscountPolicy(nightlyAmount: Money, regularAmount: Money, seconds: Duration, val taxRate: Double) 
  extends NightlyDiscountPolicy(nightlyAmount, regularAmount, seconds) 
  with TaxablePolicy

```

부가정책인 세금할인 정책과 비율할인 정책은 임의의 순서대로 조합해 적용시킬 수 있어야 한다. 

표준 요금제에 세금 정책을 적용시킨 후 비율 할인 정책을 적용한 경우라면 트레이트를 활용해 조합해 다음과 같은 순서가 된다.

```scala
class RateDiscountableAndTaxableRegularPolicy(
    amount: Money, 
    seconds: Duration, 
    val discountAmount: Money,
    val taxRate: Double)
  extends RegularPolicy(amount, seconds)
  with TaxablePolicy 
  with RateDiscountablePolicy
```

#### 쌓을 수 있는 변경

믹스인은 상속 계층 안에서 확장된 클래스보다 더 하위에 위치한다. 믹스인은 대상 클래스의 자식 클래스처럼 사용될 용도로 만들어지는 것이다. 따라서 믹스인을 **추상 서브클래스(abstract subclass)** 라고 부르기도 한다. 또한 특정 클래스에 대한 변경이나 확장을 따로 구현한 뒤 필요할 때 차례대로 추가하는 특징 때문에 **쌓을 수 있는 변경**이라고 부르기도 한다.


## 소감

믹스인이라니... 난생 처음 듣는 개념이 등장해서 상당히 신기해하며 공부했습니다. 이해하고 난뒤에는 결국에 "자식클래스를 추상화시키는 거잖아?"라고 생각했는데 마지막에 추상 서브클래스라고 부르는 것을 보고 잘못 이해한 건 아니구나 싶었네요. 합성은 책의 초반부 예제부터 꾸준히 나왔고 실제로 짠 코드에도 많이 활용돼서 빠르게 정리할 줄 알았는데 이해와 정리 속도는 다른 것 같습니다...

## 논의 사항

합성의 사용예제를 보고 마치 링크드 리스트를 보는 것 같았습니다. 저는 여태까지 단순하게 합성을 사용했던 것 같은데 여러분들은 상속을 어느정도 수준까지 활용해 봤나요?