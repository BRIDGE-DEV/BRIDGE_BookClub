
## 01 프로시저 추상화와 데이터 추상화

**프로시저 추상화 (procedure abstraction)**: 시스템을 분해하는 방법 중 하나, 기능분해(functional decomposition) 혹은 알고리즘 분해(algorithmic decomposition)라고 부른다.
**데이터 추상화(data abstraction)**: 시스템을 분해하는 방법 중 하나, 두 가지 방법이 있다. 데이터를 중심으로 *타입 추상화(type abstraction)*, 데이터를 중심으로 *프로시저 추상화(procedure abstraction)* 전자는 *추상 데이터 타입(Abstract Data Type)* 후자는 *객체지향(Object Oriented)* 이다.

'역할과 책임을 수행하는 객체'가 객체지향 패러다임이 이용하는 추상화다.
'협력하는 공동체'를 구성하도록 객체들로 나누는 과정이 객체지향 패러다임에서의 분해이다.

## 02 프로시저 추상화와 기능 분해

#### 메인 함수로서의 시스템

기능은 오래동안 시스템 분해의 기준으로 사용됐다. *알고리즘 분해* , 혹은 *기능 분해*라고 부른다. 기능 분해 관점에서는 추상화의 단위는 프로시저이다.

프로시저는 재사용 가능성이 높은 작업들을 보아둬 로직을 재사용하고 중복을 방지하는 추상화 방법이다. 잠재적으로는 정보은닉(information hiding)의 가능성을 제시만 효과적인 정보은닉 체계를 구축하기엔 한계가 있다.

기능분해의 관점에서 시스템은 더 작은 작업으로 분해될 수 있는 커다란 메인 함수이다.

*하향식 접근법(Top - Down Approach)* 을 따른다. 시스템을 구성하는 최상위 기능을 정의하고 더 작은 단계의 기능으로 분해해 나가는데 분해의 마지막은 프로그래밍 언어로 구현 가능할 수준이 된다. 각 단계는 그 상위 단계보다 구체적이어야 한다.

#### 급여관리 시스템

이번 예시는 직원의 급여관리 시스템이다.

> 급여 = 기본금 -(기본금 * 소득세율)

급여관리 시스템을 구현하기위한 추상적 최상위 문장은 

> 직원의 급여를 계산한다.

가 될 것이다. 이 문장이 메인 프로시저로 구현된다.
더 세분화된 절차로 필요한 정보는 다음과 같다.

> 직원의 급여를 계산한다.
> 	사용자로부터 소득세율을 입력받는다.
> 	직원의 급여를 계산한다.
> 	양식에  맞게 결과를 출력한다.

문장들을 더욱 구체적이고 단순한 문장들의 조합으로 분해되어야 한다. 즉 구현이 가능할 수준의 저수준 문장이 될 때까지 기능을 분해해야 한다.

>직원의 급여를 계산한다.
> 	사용자로부터 소득세율을 입력받는다.
> 		"세율을 입력하세요. : " 라는 문장을 출력한다.
> 		키보드를 통해 세율을 입력받는다.
> 	직원의 급여를 계산한다.
> 		전역 변수에 저장된 직원의 기본급 정보를 얻는다.
> 		급여를 계산한다.
> 	양식에  맞게 결과를 출력한다.
> 		"이름: {직원명}, 급여: {계산된 금액}  형식에 따라 출력 문자열을 생성된다."

기본적으로 기능 분해의 결과는 책의 목차를 정리하고 그 안의 내용을 채워넣는 것과 유사하다.

기능 분해 방법에서는 기능을 중심으로 데이터가 결정된다. 기능이 우선되고 데이터는 기능의 뒤를 따른다.

#### 급여 관리 시스템 구현

급여 관리 시스템이라는 동일한 시스템을 다양한 방식으로 구현하고 비교하기 쉬운 루비언어로 구현을 시작해보자

```ruby
def main(name)
	taxRate = getTaxRate()
	pay = calculatePayFor(name, taxRate)
	puts(describeResult(name pay))
end
```
메인 문장인 직원의 급여를 계산한다에서는 각 단계의 프로시저를 호출하는 명령문으로 변환한다.

```ruby
def getTaxRate()
	print("세율을 입력하세요: ")
	return gets().chomp().to_f()
end
```
소득세율을 입력받는 함수이다.

```ruby
$employees = ["직원A","직원B","직원C"]
$basePays = [400,300,250]
```
급여를 계산하는 calculatePayFor함수는 파라미터로 전달된 직원의 이름을 이용해 basePays의 급여에 접근해 기본급 정보를 얻는다.

```ruby
def calculatePayFor(name, taxRate)
	index = $employees.index(name)
	basePay=$basePays[index]
	return basePay -(basePay*taxRate)
end
```
급여를 계산해 포매팅하는 함수이다.

```ruby
def describeResult(name, pay)
	return "이름: #{name}, 급여: #{pay}"
end
```

이름이 '정재욱'인 직원의 급여를 계산하려면 main("정재욱")을 호출하면 된다.

하향식 기능 분해방식으로 설계한 시스템은 트리로 표현할 수 있다.
하향식 기능 분해는 논리적이고 체계적인 시스템 개발 절차지만 이상적이고 체계적이기에 불완전한 인간과 만나는 지점에 혼란이 발생한다.

#### 하향식 기능 분해의 문제점

- 시스템은 하나의 메인 함수로 구성돼 있지 않다.
- 기능 추가나 요구사항 변경으로 인해 메인 함수를 빈번하게 수정해야 한다.
- 비즈니스 로직이 사용자 인터페이스와 강하게 결합된다.
- 하향식 분해는 너무 이른 시기에 함수들의 실행 순서를 고정시키기 때문에 유연성과 재사용성이 저하된다.
- 데이터 형식이 변경될 경우 파급효과를 예측할 수 없다.


### 하나의 메인 함수라는 비현실적인 아이디어

프로그램의 기능들은 시간이 지나고 요구사항을 도출해나가는 과정에서 지속적으로 새로운 기능들이 추가된다. 추가된 기능들은 높은 확률로 하나의 메인 함수에 속하지 않을 가능성이 크다. 결국 처음에 중요하게 생각했던 메인 함수는 *다른 동등하게 중요한 여러 함수들 중 하나로 전락한다.* 대부분의 시스템에서 하나의 메인 기능이란 개념은 존재하지 않는다. 현대적인 시스템에서는 동등한 수준의 다양한 기능들로 구성된다.

"실제 시스템에 정상(top)은 존재하지 않는다."

### 메인 함수의 빈번한 재설계

하향식 기능 분해의 경우 새로운 기능을 추가할 때마다 매번 메인함수를 수정해야 한다. 기존 로직과는 아무런 상관없는 새로운 함수의 적절한 위치를 확보해야 하기 때문에 메인 함수의 구조를 변경할 수 밖에 없다. 기존 코드의 변경은 버그를 발생시키고 변경에 취약해진다.

직원들 기본급여의 총합을 계산하는 기능을 추가해야 될 때 총합 계산 함수인 sumOfBasePays()함수의 위치가 애매해진다.

```ruby
def main(name)
	taxRate = getTaxRate()
	pay = calculatePayFor(name, taxRate)
	puts(describeResult(name pay))
end
```

메인함수의 어떤 곳에도 자리가 없으며 총합을 구하는 함수는 개념적으로 메인 함수와 동등한 수준의 작업을 수행한다. 따라서 현재의 메인 함수 안에서 sumOfBasePays를 호출할 수 없다. 

해결하는 방법은 급여를 계산하는 메인함수의 기능들을 calculatePay라는 새로운 로직을 만들어 이사시켜야 한다.

```ruby
def main(operation, args={})
	case(operation)
	when :pay then calculatePay(args[:name])
	when :basePays then sumOfBasePays()
```

### 비즈니스 로직과 사용자 인터페이스의 결합

하향식 접근법은 로직을 설계할 때 초기 단계에 입력 방법과 출력 양식을 함께 고민하도록 강요한다. 급여를 계산하는 기능의 경우 "사용자로부터 소득세율을 입력받아 급여를 계산한 후 계산된 결과를 화면에 출력한다."에서 코드 안에 비즈니스 로직과 사용자 인터페이스 로직이 밀접하게 결합된다.

문제는 비즈니스 로직과 사용자 인터페이스 로직의 변경되는 빈도가 다르다는 것이다. 사용자는 시스템 내에서 가장 자주 변경되는 부분이다.  하향식 접근법은 인터페이스 로직과 비즈니스 로직이 섞여 있기 때문에 사용자 인터페이스 로직을 변경시키면 비즈니스 로직에도 영향을 미친다. 즉 변경에 불안정한 아키텍쳐가 된다.

### 성급하게 결정된 실행 순서

하향식으로 기능을 분해하는 과정은 큰 함수를 작은 함수로 분리하고 분해된 함수들의 실행순서를 결정하는 작업으로 요약된다. 이것이 설계가 '무엇'을 하는가 보다 '어떻게'하는가에 집중하게 만든다.

어떻게에 집중하게 되면 함수들의 실행순서가 정의된다.(시간 제약 temporal constraint)
실행순서나 조건, 반복과 같은 제어구조를 결정하지 않고는 분해를 진행할 수 없기에 자연스레 중앙집중 제어 스타일(centralized control style)의 형태를 띄게 된다. 결과적으로 중요한 제어 흐름의 결정은 상위 함수에서 이뤄지고 하위 함수는 상위 함수의 흐름에 따라 호출된다.

문제는 함수의 *제어구조의 변경이 빈번하게 일어난다.* 기능이 추가되거나 변경될 때 초기 함수 흐름이 올바르지 않다는 것이 판명된다. 

이를 해결하기 위한 방법은 시간 제약에 대한 미련을 버리고 논리적 제약을 설계의 기준으로 삼는 것이다. 객체지향은 호출 순서가 아니라 논리적인관계를 중심으로 설계를 이끌어 간다. 

하향식 접근법은 *재사용하기 어렵다.* 하위 함수들은 상위 함수가 강요하는 문맥에서만 의미를 가지기 때문이다. 함수가 재사용 가능하려면 상위 함수보다 일반적이어야 한다. 하향식으로 분해된 함수는 문맥에 종속적이 되며 재사용과는 반대되는 개념이다.

모든 문제의 원인은 *결합도*다. 상위 함수가 강요하는 문맥에 강하게 결합된다. 시간적으로도 강하게 결합되어 변경에 취약하게 만들고 이해하기 어렵게 만든다.
함수들 또한 데이터와 강하게 결합된다는 것이 가장 큰 문제이다.

### 데이터 변경으로 인한 파급효과

하향식 기능 분해의 문제점은 데이터 사용자의 추적이 어렵다는 점이다. 데이터 변경으로 인해 어떤 함수가 영향을 받을지 예상하기 어렵다. 

#### 언제 하향식 분해가 유용한가?

설계가 어느정도 안정된 뒤에 문서화나 논리적 설명에 유용하다. 설계를 문서화하고 설명하는데 유용할 뿐이지 설계를 하는 데 유용한 것은 아니다. 작은 프로그램과 개별 알고리즘을 위해서는 유용한 패러다임이지만 실제로 동작하는 커다란 프로그램을 설계하는 데 적합한 방법은 아니다. 

## 03 모듈

#### 정보 은닉과 모듈
시스템 변경을 관리하는 기본적인 방법 중 하나는 변경되는 부분을 구현 단위로 묶고 퍼블릭 인터페이스를 통해서만 접근하도록 만드는 것이다. *기능 기반이 아닌 변경 방향에 맞춰 시스템을 분해하는 것이다.*

**정보 은닉( information hiding) :** 시스템을 모듈 단위로 분해하기 위한 기본 원리, 자주 변경되는 부분을 상대적으로 덜 변경되는 안정적인 인터페이스 뒤로 감추는 것

> 모듈은 서브 프로그램이라기보다는 책임의 할당이다. 모듈화는 개별적인 모듈에 대한 작업이 시작되기 전에 정해져야 하는 설계 결정들을 포함한다. ~분할된 모듈에 대해 감춰야 하는 설계 결정에 따라 특징 지어진다. 해당 모듈 내부의 작업을 가능한 적게 노출하는 인터페이스 또는 정의를 선택한다. ~어려운 설계 결정이나 변화할 것 같은 설계 결정들의 목록을 사용해 설계를 시작할 것을 권장한다. 이런 결정이 외부 모듈에 대해 숨겨지도록 각 모듈을 설계해야 한다.

모듈은 두 가지 비밀을 감춰야 한다.

- **복잡성**: 모듈이 너무 복잡한 경우 이해하고 사용하기 어렵다. 외부에 모듈을 추상화할 수 있는 간단한 인터페이스를 제공해서 모듈의 복잡도를 낮춘다.
- **변경 가능성**: 변경 가능한 설계 결정이 외부에 노출될 경우 실제로 변경이 발생했을 때 파급효과가 커진다. 변경 발생 시 하나의 모듈만 수정하면 되도록 변경 가능한 설계 결정을 모듈 내부로 감추고 외부에는 쉽게 변경되지 않을 인터페이스를 제공한다.

*데이터 캡슐화와 정보은닉은 동일한 개념이 아니다*  변경과 관련된 비밀을 감춘다는 공통점이 있지만 데이터 캡슐화는 캡슐화의 비밀의 한 종류인 데이터를 감추는 캡슐화의 한 종류이다. 비밀이 반드시 데이터일 필요는 없다. 복잡한 로직이나 변경 가능성이 큰 자료구조일 수도 있다.

```ruby
#encoding: UTF-8

module Employees

  $employees = ["직원A", "직원B", "직원C", "아르바이트D", "아르바이트E", "아르바이트F"]

  $basePays = [400, 300, 250, 1, 1, 1.5]

  $hourlys = [false, false, false, true, true, true]

  $timeCards = [0, 0, 0, 120, 120, 120]

  

  def Employees.calculatePay(name, taxRate)

    if (Employees.hourly?(name)) then

      pay = Employees.calculateHourlyPayFor(name, taxRate)

    else

      pay = Employees.calculatePayFor(name, taxRate)

    end

  end

  

  def Employees.hourly?(name)

    return $hourlys[$employees.index(name)]

  end

  

  def Employees.calculateHourlyPayFor(name, taxRate)

    index = $employees.index(name)

    basePay = $basePays[index] * $timeCards[index]

    return basePay - (basePay * taxRate)

  end

  

  def Employees.calculatePayFor(name, taxRate)

    return basePay - (basePay * taxRate)

  end

  def Employees.sumOfBasePays()

    result = 0

    for name in $employees

      if (not Employees.hourly?(name)) then

        result += $basePays[$employees.index(name)]

      end

    end

    return result

  end

end

  

def main(operation, args={})

  case(operation)

  when :pay then calculatePay(args[:name])

  when :basePays then sumOfBasePays()

  end

end

  

def calculatePay(name)

  taxRate = getTaxRate()

  pay = Employees.calculatePay(name, taxRate)

  puts(describeResult(name, pay))

end

  

def getTaxRate()

  print("세율을 입력하세요: ")

  return gets().chomp().to_f()

end

  

def describeResult(name, pay)

  return "이름 : #{name}, 급여 : #{pay}"

end

  

def sumOfBasePays()

  puts(Employees.sumOfBasePays())

end

  

main(:basePays)

main(:pay, name:"아르바이트F")
```

전체 직원에 관한 처리를 Employees 모듈로 캡슐화한 결과이다.

#### 모듈의 장점과 한계

Employees 예제를 통해 알 수 있는 모듈의 장점이다.

**모듈 내부의 변수가 변경되더라도 모듈 내부에만 영향을 미친다**

모듈을 사용하면  모듈 내부에 정의된 변수를 직접 참조하는 코드의 위치를 모듈 내부로 제한할 수 있다. 이제 어떤 데이터가 변경됐을 때 영향을 받는 함수를 찾기 위해 해당 데이터를 정의한 모듈만 검색하면 된다. -> 즉 데이터는 그 객체(모듈)이 직접 처리해야 된다.

**비즈니스 로직과 사용자 인터페이스에 대한 관심사를 분리한다**

사용자 입력과 화면 출력을 Employees 모듈이 아닌 외부에 뒀다는 점을 주목하라. 수정된 코드에서 Employees 모듈은 비즈니스 로직과 관련된 관심사만 담당하며 사용자 인터페이스와 관련된 관심사는 모두 Employees 모듈을 사용하는 main 함수 쪽에 위치한다.
추가로 다른 형식의 사용자 인터페이스가 추가되도  Employees 모듈에 포함된 비즈니스 로직은 변경되지 않는다.

**전역 변수와 전역 함수를 제거함으로써 네임스페이스 오염(namespace pollution)을 방지한다**

모듈의 한 가지 용도는 네임스페이스를 제공하는 것이다. 변수와 함수를 모듈 내부에 포함시키기 때문에 다른 모듈에서도 동일한 이름을 사용할 수 있게 된다. 따라서 모듈은 전역 네임스페이스의 오염을 방지하는 동시에 이름 충돌(name collision)의 위험을 완화한다.

## 04 데이터 추상화와 추상 데이터 타입

#### 추상 데이터 타입

다음은 추상 데이터 타입을 구현하려할 때 필요한 특성들이다.

- 타입 정의를 선언할 수 있어야 한다.
- 타입의 인스턴스를 다루기 위해 사용할 수 있는 오퍼레이션의 집합을 정의할 수 있어야 한다.
- 제공된 오퍼레이션을 통해서만 조작할 수 있도록 데이터를 외부로부터 보호할 수 있어야 한다.
- 타입에 대해 여러 개의 인스턴스를 생성할 수 있어야 한다.


루비의 Struct를 이용해 개별 직원을 위한 추상 데이터 타입을 구현하자. 우선 이름(name), 기본급여(basePay), 아르바이트 직원 여부(hourly), 작업시간(timeCard)를 비밀로 가지는 추상 데이터 타입인 Employee를 선언한다.
```ruby
Employee= Struct.new(:name,:basePay,:hourly,:timeCard)do
End
```


추상 데이터 타입에 적용할 오퍼레이션이다. 직원의 유형에 따라 급여를 계산하거나

```ruby
#encoding: UTF-8

Employee = Struct.new(:name, :basePay, :hourly, :timeCard) do

  def calculatePay(taxRate)

    if (hourly) then

      return calculateHourlyPay(taxRate)

    end

    return calculateSalariedPay(taxRate)

  end

  

  def monthlyBasePay()

    if (hourly) then return 0 end

    return basePay

  end

private  

  def calculateHourlyPay(taxRate)

    return (basePay * timeCard) - (basePay * timeCard) * taxRate

  end

  def calculateSalariedPay(taxRate)

    return basePay - (basePay * taxRate)

  end

end

  

$employees = [

  Employee.new("직원A", 400, false, 0),

  Employee.new("직원B", 300, false, 0),

  Employee.new("직원C", 250, false, 0),

  Employee.new("아르바이트D", 1, true, 120),

  Employee.new("아르바이트E", 1, true, 120),

  Employee.new("아르바이트F", 1, true, 120),

]

  

def main(operation, args={})

  case(operation)

  when :pay then calculatePay(args[:name])

  when :basePays then sumOfBasePays()

  end

end

  

def calculatePay(name)

  taxRate = getTaxRate()

  for each in $employees

    if (each.name == name) then employee = each; break end

  end

  pay = employee.calculatePay(taxRate)

  puts(describeResult(name, pay))

end

  

def getTaxRate()

  print("세율을 입력하세요: ")

  return gets().chomp().to_f()

end

  

def describeResult(name, pay)

  return "이름 : #{name}, 급여 : #{pay}"

end

  

def sumOfBasePays()

  result = 0

  for each in $employees

    result += each.monthlyBasePay()

  end

  puts(result)

end

  

main(:basePays)

main(:pay, name:"아르바이트F")
```
 

## 05 클래스

#### 클래스는 추상 데이터 타입인가?

추상 데이터 타입은 오퍼레이션을 기준으로 타입들을 추상화한다.
클래스는 타입을 기준으로 절차들을 추상화한다.



#### 추상 데이터 타입에서 클래스로 변경하기


 ```ruby
 #encoding: UTF-8

class Employee

  attr_reader :name, :basePay

  def initialize(name, basePay)

    @name = name

    @basePay = basePay

  end

  def calculatePay(taxRate)

    raise NotImplementedError

  end

  def monthlyBasePay()

    raise NotImplementedError

  end

end

  --------------------------------------------------------------

class SalariedEmployee < Employee

  def initialize(name, basePay)

    super(name, basePay)

  end

  def calculatePay(taxRate)

    return basePay - (basePay * taxRate)

  end

  def monthlyBasePay()

    return basePay

  end

end

  ---------------------------------------------------------------

class HourlyEmployee < Employee

  attr_reader :timeCard

  def initialize(name, basePay, timeCard)

    super(name, basePay)

    @timeCard = timeCard

  end

  def calculatePay(taxRate)

    return (basePay * timeCard) - (basePay * timeCard) * taxRate

  end

  def monthlyBasePay()

    return 0

  end  

end

  

$employees = [

  SalariedEmployee.new("직원A", 400),

  SalariedEmployee.new("직원B", 300),

  SalariedEmployee.new("직원C", 250),

  HourlyEmployee.new("아르바이트D", 1, 120),

  HourlyEmployee.new("아르바이트E", 1, 120),

  HourlyEmployee.new("아르바이트F", 1, 120),

]

  

def main(operation, args={})

  case(operation)

  when :pay then calculatePay(args[:name])

  when :basePays then sumOfBasePays()

  end

end

  

def calculatePay(name)

  taxRate = getTaxRate()

  for each in $employees

    if (each.name == name) then employee = each; break end

  end

  pay = employee.calculatePay(taxRate)

  puts(describeResult(name, pay))

end

  

def getTaxRate()

  print("세율을 입력하세요: ")

  return gets().chomp().to_f()

end

  

def describeResult(name, pay)

  return "이름 : #{name}, 급여 : #{pay}"

end

  

def sumOfBasePays()

  result = 0

  for each in $employees

    result += each.monthlyBasePay()

  end

  puts(result)

end

  

main(:basePays)

main(:pay, name:"아르바이트F")
```
Employee라는 추상화된 인터페이스와 그걸 구현하는 SalariedEmployee와 HourlyEmployee를 통해 클라이언트 입장에서 메시지와 메서드를 분리시킨 코드이다.

#### 변경을 기준으로 선택하라

클래스가 추상 데이터 타입의 개념을 따르는 지 확인하는 방법은 클래스에 인스턴스의 타입을 구분하는 변수가 있는지를 확인하면 된다. hourly는 아르바이트인지 정직원인지를 구분하는 변수이다.

객체지향에서는 타입 변수를 이용한 조건문을 다형성으로 대체한다. 객체가 스스로 메시지를 처리할 메서드를 선택하게 해야 한다.

새로운 직원 유형을 구현하는 클래스를 Employee 상속 계층에 추가하고 필요한 메서드를 오버라이딩하면 된다.

**개방-폐쇄 원칙(Open-Closed Principle, OCP)**  : 기존 코드에 아무런 영향을 미치지 않고 새로운 객체 유형과 행위를 추가할 수 있는 특성 

추상 데이터 타입 vs 객체지향 설계

'타입  추가' 변경의 압력이 강한 경우 : 객체지향 설계
	새로운 타입을 추가 해야할 경우 추상 데이터 타입 설계라면 타입을 체크하는 클라이언트 코드를 일일이 찾아보고 수정해야 한다.
'오퍼레이션 추가' 변경의 압력이 강한 경우 : 추상 데이터 타입 설계
	오퍼레이션을 추가 해야 하는 경우 객체지향 설계라면 상속받은 클래스를 한 번에 수정해야 한다.


## 느낀 점

지금 짠 코드는 실행순서가 굉장히 중요한, 즉 시간적 제약이 강하게 걸려 있는 상태입니다. 어떻게 고쳐야하나 막막했는데 덕분에 방향성은 알게 됐네요. 여전히 전체적으로 뜯어 고쳐야 한다는 건 두렵지만 시도해볼만한 용기의 지식을 얻어갑니다...

## 논의사항

여러분들은 추상 데이터 타입 설계를 해본 적 있나요?

사실 책을 읽어도 아직까지 추상데이터 타입 설계가 완벽히 이해가 가진 않습니다.(ruby언어를 처음봐서 그런걸까요...) 여러분들의 추상데이터 타입과 관련된 경험을 들어보고 싶습니다.
