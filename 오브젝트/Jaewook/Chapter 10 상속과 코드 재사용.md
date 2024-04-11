
## 01 상속과 중복 코드
#### DRY 원칙
코드가 변경되는 것은 피할 수 없는 일이다. 코드가 중복되는 것은 변경에 필요한 노력을 배로 증가시킨다. 어떤 코드가 중복인지를 찾아야 하고 일관되게 수정해야 하며 개별적으로 테스트를 해야 한다. 

중복 여부를 판단하기 위한 기준은 '변경'이다. 변경이 발생할 때 두 코드를 함께 수정해야 한다면 코드 중복이며 함께 수정할 필요가 없다면 중복이 아니다. 코드의 모양이 중복 코드를 결정하는 기준이 아니라는 뜻이다.(코드의 모양이 같은 것은 중복의 징후이다.)

**DRY 원칙**: Don't Repeat Yourself 의 약자로 동일한 지식을 반복하지 말라는 의미가 있다.
		 모든 지식은 시스템 내에서 단일하고, 애매하지 않고, 정말로 믿을 만한 표현 양식을 가져야 한다.
#### 중복과 변경

전화요금을 계산하는 애플리케이션을 개발할 때  Phone 인스턴스는 요금 계산에 필요한 세 인스턴스 amount(단위 요금), seconds(단위 시간), calls(통화 목록) 을 저장해 calculateFee 메서드를 통해 요금을 계산한다.

```java
public class Phone {

    private Money amount;

    private Duration seconds;

    private List<Call> calls = new ArrayList<>();

  

    public Phone(Money amount, Duration seconds) {

        this.amount = amount;

        this.seconds = seconds;

    }

  

    public void call(Call call) {

        calls.add(call);

    }

  

    public List<Call> getCalls() {

        return calls;

    }

  

    public Money getAmount() {

        return amount;

    }

  

    public Duration getSeconds() {

        return seconds;

    }

  

    public Money calculateFee() {

        Money result = Money.ZERO;

  

        for(Call call : calls) {

            result = result.plus(amount.times(call.getDuration().getSeconds() / seconds.getSeconds()));

        }

  

        return result;

    }

}
```

만약 여기에 심야 할인 요금을 계산하는 요구사항이 추가된다면 가장 쉽고 빠른 방법은 Phone의 코드를 복사해 NightlyDiscountPhone 클래스를 만들고 수정하는 것이다.

```java
public class NightlyDiscountPhone {

    private static final int LATE_NIGHT_HOUR = 22;

  

    private Money nightlyAmount;

    private Money regularAmount;

    private Duration seconds;

    private List<Call> calls = new ArrayList<>();

  

    public NightlyDiscountPhone(Money nightlyAmount, Money regularAmount, Duration seconds) {

        this.nightlyAmount = nightlyAmount;

        this.regularAmount = regularAmount;

        this.seconds = seconds;

    }

  

    public Money calculateFee() {

        Money result = Money.ZERO;

  

        for(Call call : calls) {

            if (call.getFrom().getHour() >= LATE_NIGHT_HOUR) {

                result = result.plus(nightlyAmount.times(call.getDuration().getSeconds() / seconds.getSeconds()));

            } else {

                result = result.plus(regularAmount.times(call.getDuration().getSeconds() / seconds.getSeconds()));

            }

        }

  

        return result;

    }

}

```

LATE_NIGHT_HOUR를 통해 밤 시간을 구분지어 야간 할인 요금을 계산하는 부분을 제외하면 Phone과 유사하다. 

구현시간은 상당히 절약했지만 중복코드를 갖고 있다는 것은 잠재적 리스크를 지고 가는 것과 같다.

#### 중복 코드 수정하기

만약 중복된 코드가 적용된 상황에 통화요금에 부과할 세금을 계산하는 요구사항을 추가해보자

phone 클래스에서는 taxRate라는 세율 인스턴스를 생성하고 calculateFee메서드를 세율을 적용시키는 방식을 추가해 수정할 것이다. 마찬가지로 NightlyDiscountPhone도 동일한 방식으로 수정될 것이다.

일련의 수정을 거치고 나면 중복코드에서 수정을 하는 것이 쉬운 일이 아니라는 것을 알게 된다. 중복 코드는 항상 함께 수정되야 하므로 하나라도 빠뜨리면 버그가 발생한다.
추가로 중복된 코드는 서로 다른 방식으로 수정될 가능성이 있다.

#### 상속을 이용해서 중복 코드 제거하기

상속은 이미 존재하는 클래스와 유사한 클래스가 필요하다면 코드를 복사하지  말고 상속을 이용해 코드를 재사용하는 것이다.

```java
public class NightlyDiscountPhone extends Phone {

    private static final int LATE_NIGHT_HOUR = 22;
    private Money nightlyAmount;

    public NightlyDiscountPhone(Money nightlyAmount, Money regularAmount, Duration seconds) {

        this.nightlyAmount = nightlyAmount;
    }

  
	@Override
    public Money calculateFee() {
	//부모 클래스의 calculateFee() 호출
        Money result = super.calculateFee();

		Money nightlyFee=Money.ZERO;
        for(Call call : getCalls()) {

            if (call.getFrom().getHour() >= LATE_NIGHT_HOUR) {
				nightlyFee=nightlyFee.plus(
				getAmount().minus(nightlyAmount).times(
				call.getDuration().getSeconds()/getSeconds().getSeconds()));
              
            }
        }
        return result.minus(nightlyFee);
    }

}

```

super 참조에서 부모의 calculateFee를 호출해서 일반 요금제에 따라 통화 요금제를 계산한 후 이 값에서 통화 시작 시간이 10시 이후인 통화의 요금을 빼주는 부분이다.

이 부분에서 개발자가 세운 상속의 의도를 이해해야 한다.  
전체 통화에서 기본 요금제를 적용하고 10시 이후의 통화요금을 전체 요금에서 차감하는 방식이다.

방식을 이해하는 것이 중점이 아니라 개발자의 가정을 이해하기 전에는 코드를 이해하기 어렵다는 점이다.

상속은 재사용을 위해 여러 가정을 세웠고 그 가정은 코드를 이해하기 어렵게 만들뿐 아니라 직관에도 어긋날 수 있다.

상속을 이용해 코드를 재사용하기 위해서는 부모 클래스의 개발자가 세웠던 가정과 추론을 이해 해야하며, 자식 클래스의 작성자가 부모 클래스의 구현 방법에 대해 정확히 이해해야 하며 이는 결합도가 높아지는 결과를 초래한다.

#### 강하게 결합된 Phone과 NightlyDiscountPhone

부모 클래스와 자식 클래스 사이의 결합이 문제인 이유 역시 변경에 취약하다.
Phone의 calculateFee 메서드를 오버라이딩한다. super 참조를 통해 부모 클래스의 메서드를 호출한다. 즉 NightlyDiscountPhone의 calculateFee메서드는 Phone의 calculateFee에 기반한다.

이 상황에서 세금을 부과하는 요구사항이 추가된다면 Phone은 앞에서 구현했던 것처럼 taxRate를 인스턴스 변수로 포합하고 calculateFee 메서드에서 값을 반환할 때 taxRate를 이용해 세금을 부과해야 한다.

NightlyDiscountPhone 또한 생성자에서 전달받은 taxRate를 부모 클래스인 Phone의 생성자로 전달해서 Phone과 동일하게 반환해야 한다.

NightlyDiscountPhone을 Phone의 자식 클래스로 만든 이유는 중복된 코드를 피하기 위해서였지만 세금을 부과하는 로직을 추가하기 위해 Phone과 같이 NightlyDiscountPhone에도 추가해야 했다.  즉 중복을 피하기 위해서 상속을 사용했지만 로직을 추가하기 위해 중복 코드를 만들어야 했다.

## 02 취약한 기반 클래스 문제

**취약한 기반 클래스 문제(Fragile Base Class Problem, Brittle Base Class Problem)** : 부모 클래스의 변경에 의해 자식 클래스가 영향을 받는 현상

> 이제 결합도의 개념을 상속에 적용한다면 구현을 상속한 경우(extends를 사용한 경우) 파생 클래스는 기반 클래스에 강하게 결합된다.

상속은 자식 클래스를 점진적으로 추가해서 기능을 확장하는 데 유리하지만 기반인 부모 클래스를 점진적으로 개선하는 것은 어렵게 만든다.

자식 클래스는 부모클래스의 구현 세부사항에 의존하도록 만든다. 이것이 상속을 피해야 하는 첫 번째 이유이다.

상속을 사용하면 부모 클래스의 퍼블릭 인터페이스가 아닌 구현을 변경하면 자식 클래스에도 영향이 미치며 상속 계층의 상위 클래스에 가해지는 작은 변경도 상속 계층의 모든 자손들에 영향을 미친다.

객체지향의 기반은 캡슐화를 통한 변경의 통제다. 상속은 캡슐화의 장점을 희석시키고 결합도를 높인다.

#### 불필요한 인터페이스 상속 문제

자바의 초기 버전에서 상속이 잘못된 사례는 java.uitl.Properties와 java.util.Stack이다.

Stack은 Vector를 재사용하기 위해 상속을 받은 클래스로 구현했다. Vector는 임의의 위치에서 get, add, remove오퍼레이션을 제공하지만 Stack은 LIFO이기 때문에 맨 마지막 요소를 추가하고 제거하는 push, pop 오퍼레이션을 제공한다.

Stack은 Vector를 상속받기 때문에 Stack도 임의의 위치에서 요소를 추가하거나 삭제할 수 있다. -> 즉 Stack의 규칙을 쉽게 위반할 수 있다.

java.util.Properties 클래스는 키와 값을 String만 가질 수 잇다.
Properties는 Map의 조상인 Hashtable을 상속받는데 자바에 제네릭(generic)이 도입되기 전에 만들어졌기 때문에 String을 체크할 방법이 없었다. 

#### 메서드 오버라이딩의 오작용 문제

InstrumentedHashSet은 HashSet의 내부에 저장된 요소의 수를 셀 수 있는 기능이 추가된 클래스로 HashSet의 자식 클래스로 구현돼 있다. 
```java
public boolean addAll(Collection<? extends E>c){
	addCount+=c.size();
	return super.addAll();
}
```
InstrumentedHashSet의  addAll메서드는 addCount를 증가시킨 후 super 참조를 이용해 부모 클래스의 메서드를 호출해서 요소를 추가한다.

addAll 메서드가 호출되면 addCount가 추가되고 super.addAll메서드가 호출되서 부모클래스로 이동해 부모 클래스인 HashSet의 add메서드를 호출해서 중복으로 addCount가 증가하는 불상사가 생긴다. 

문제를 해결하기 위해서는 InstrumentedHashSet의 addAll메서드를 제거해 HashSet의 addAll메서드가 호출된다.

하지만 이 방법에서는 HashSet의 addAll메서드가 add 메시지를 전송하지 않도록 수정된다면 addAll 메서드를 이용해 추가되는 요소들에 대한 카운트는 누락될 것이다.

#### 부모 클래스와 자식 클래스의 동시 수정 문제

음악을 추가하는 Playlist클래스다. 
```java
public class Song{
	private String singer;
	private String title;

	public Song(String singer, String title){
		this.singer=singer;
		this.title=title;
	}
	public String getString() {
		return singer;
	}
	public String getTitle() {
		return title;
	}
}

```

Playlist는 트랙에 노래를 추가할 수 있는 append 메서드를 구현한다.

```java
public class Playlist{
	private List<Song> tracks = new ArrayList<>();

	public void append(Song song){
		getTracks().add(song);
	}

	public List<Song> getTracks(){
		return tracks;
	}

}
```

여기에 노래를 삭제할 수 있는 기능을 추가한 PersonalPlaylist가 필요하다고 해보자

```java
public class PersonalPlaylist extends Playlist{
public void remove(Song song){
	getTracks().remove(song);
	}
}
```

여기에 추가로 요구사항이 변경되어 노래 목록뿐 아니라 가수별 노래의 제목도 관리해야 한다고 가정하면 가수를 키로 제목을 추가하는 Playlist의 append 메서드를 수정해야 한다.

```java
public class Playlist {

    private List<Song> tracks = new ArrayList<>();

    private Map<String, String> singers = new HashMap<>();

    public void append(Song song) {

        tracks.add(song);

        singers.put(song.getSinger(), song.getTitle());
    }
    
    public List<Song> getTracks() {
        return tracks;
    }
    
    public Map<String, String> getSingers() {
        return singers;
    }
}
```

수정된 내용이 동작하려면 PersonalPlaylist의 remove 메서드도 함께 수정해야 한다.

```java
public void remove(Song song){
	getTracks().remove(song);
	getSingers().remove(song.getSinger());
}

```

자식 클래스가 부모 클래스의 메서드를 오버라이딩하거나 불필요한 인터페이스를 상속받지 않음에도 수정에 여파가 미칠 수 있다는 사실이다.

상속을 사용해 결합도가 높기 때문이다.

다음은 이에 대한 조슈아 블로치의 조언이다.

> 서브클래스는 올바른 기능을 위해 슈퍼클래스의 세부적인 구현에 의존한다. 슈퍼클래스의 구현은 릴리스를 거치면서 변경될 수 있고, 그에 따라 서브클래스의 코드를 변경하지 않더라도 깨질 수 있다. 결과적으로, 슈퍼클래스의 작성자가 확장될 목적으로 특별히 그 클래스를 설계하지 않았다면 서브클래스는 슈퍼클래스와 보조를 맞춰서 진화해야 한다.

## 03 Phone 다시 살펴보기

#### 추상화에 의존하자

NightlyDiscountPhone의 문제는 Phone에 강하게 결합돼 있기 때문에 Phone의 변경에 취약하다는 것이다.

코드 중복을 제거하기 위한 상속을 도입할 때 따르는 두 가지 원칙이 있다.

- 두 메서드가 유사하게 보인다면 차이점을 메서드로 추출하라. 메서드 추출을 통해 두 메서드를 동일한 형태로 보이도록 만들 수 있다.
- 부모 클래스의 코드를 하위로 내리지 말고 자식 클래스의 코드를 상위로 올려라. 부모 클래스의 구체적인 메서드를 자식 클래스로 내리는 것보다 자식 클래스의 추상적인 메서드를 부모 클래스로 올리는 것이 재사용성과 응집도 측면에서 더 뛰어난 결과를 얻을 수 있다.

#### 차이를 메서드로 추출하라

calculateFee의 for문 안에 구현된 요금 계산 로직이 서로 다르기 때문에 그 부분을 메서드로 추출했다.
```java
private Money calculateCallFee(Call call){
	return amount.times(call.getDuration().getSeconds()/seconds.getSeconds());
}
```

```java

private Money calculateCallFee(Call call){
	if(call.getFrom().getHour()>=LATE_NIGHT_HOUR){
		return nightlyAmout.times(call.getDuration().getSeconds()/seconds.getSeconds());
	}else{
		return regularAmount.times(call.getDuration().getSeconds()/seconds.getSeconds());
	}
}

```

다른 부분들을 분리시킨 calculateFee메서드는 부모 클래스로 올리면 된다.

#### 중복 코드를 부모 클래스로 올려라

```java

public abstract class AbstractPhone(){}

public class Phone extends AbstractPhone{...}

public NightlyDiscountPhone extends AbstractPhone{...}

```

추상적인 상위 클래스인 AbsractPhone을 만들고 나머지 Phone을 상속시키자. 후에 공통된 코드를 AbstractPhone으로 옮기면 된다.

*공통된 코드를 옮길 때는 변수보다 메서드를 먼저 옮기는 것이 좋다. 메서드를 먼저 옮겨 놓으면 그에 필요한 변수가 컴파일 에러로 알려주기 때문이다.*

결과적으로 AbstractPhone은 추상화에 의존하게 된다.

> 

#### 추상화가 핵심이다

공통 코드를 상위로 옮기고 난 후에는 `NightlyDiscountPhone`와 `Phone`은 각자 하나의 변경 이유를 가지기 때문에 *단일 책임 원칙*을 준수하게 된다. 또한 `NightlyDiscountPhone`과 `Phone`은 상위 클래스인 `AbstractPhone`에 의존하고 `AbstractPhone`은 자식 클래스에 의존하지 않기 때문에 *의존성 역전 원칙*을 준수한다.
*개방-폐쇄 원칙*도 역시 준수하는데, `AbstractPhone`을 상속받는 클래스를 추가한 후 `calulateCallFee`만 오버라이딩하면 된다. 설계의 확장에 열려있고 수정에는 닫혀 있다.

#### 의도를 드러내는 이름 선택하기

다른 클래스 이름은 괜찮으나 기본요금을 계산하는 Phone은 기능이 명시적이지 않다. AbstractPhone은 휴대폰 전체를 포괄한다는 느낌이 들지 않는다. 때문에 AbstractPhone은 Phone으로 Phone은 RegularPhone으로 변경하는 것이 적절하다.

#### 세금 추가하기

수정된 코드는 변경하기 쉬울까?

다시 세금을 추가해보자.

세금은 공통사항이기 때문에 모든 요금제에 적용돼야 한다. 추상 클래스인 Phone을 수정해야 한다.

```java
public Phone(double taxRate){
	this.taxRate=taxRate;
}

```

Phone의 생성자에 세금을 추가했지만  자식 클래스의 생성자에도 taxRate를 초기화하기 위한 생성자를 추가해야 한다. 

클래스 사이의 상속은 행동뿐만 아니라 변수에도 강하게 결합된다. 인스턴스 변수가 추가된다면 행동이 추가되는 것과는 다르게 모든 클래스가 변수를 초기화 해야하기 때문에 자연스럽게 부모 클래스에 추가된 인스턴스 변수는 자식 클래스의 초기화 로직에 영향을 미친다.

하지만 초기화 로직을 변경하는 것이 두 클래스에 동일한 세금 계산 로직을 중복시키는 것보다 현명하다.

상속에서 결합을 피할 방법은 없다. 메서드 구현에 의한 결합은 추상화를  해결이 가능하나 인스턴스 변수에 대한 잠재적 결합은 피할 수 없다. 단지 인스턴스 변수 추가에 의한 영향(부작용)이 퍼져나가는 것을 막아야 하는 것 뿐이다.
## 04 차이에 의한 프로그래밍

**차이에 의한 프로그래밍 (programming by difference)** : 상속과 같이 기존 코드와 다른 부분만을 추가해 애플리케이션의 기능을 확장하는 방법

상속은 이미 존재하는 클래스의 코드를 기반으로 다른 부분을 구현할 때 쉽고 빠르게 추가할 수있다. 중복 코드를 하나의 클래스로 모은 뒤 중복 코드가 상속관계의 클래스에 연결되며 확장할 수 있다. 다만 상속의 무분별한 남용과 오용은 설계의 이해와 확장을 어렵게 만들기 때문에 정말 필요한 경우에 사용하는 것이 옳다.

## 소감

클래스 폭발의 예제를 보고 정말 상속을 사용하는 극단적으로 잘못된 예제를 보는 것 같았네요. 애초에 상속을 잘 사용하지 않을 뿐더러 사용을 고려할 때도 하나의 계층정도만 생각했었는데, 복잡한 상속의 계층구조와 그로인해 발생할 수 있는 문제점들을 코드로 직접 볼 수 있어 좋은 챕터였습니다.

## 논의 사항

저는 몬스터를 구현하면서 virtual을 사용해 간단한 계층의 상속을 사용했던 기억이 납니다. 상속을 사용하는 상황 자체가 드물 것 같은데 여러분들은 어떤 상황에 상속을 사용했나요?
