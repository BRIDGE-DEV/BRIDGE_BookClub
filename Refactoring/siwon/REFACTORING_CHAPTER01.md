# REFACTORING_CHAPTER01

# 점진적인 개선

## 내용 정리

---

> 프로그램이 새로운 기능을 추가하기에 편한 구조가 아니라면, 
먼저 기능을 추가하기 쉬운 형태로 리팩터링하고 나서 원하는 기능을 추가한다.
> 

예제에서 사용된 기법 위주로 정리해봤다. 뒷 장에서 더 자세하게 다룰테지만 눈에 한 번 더 익혀두고 싶었다.

- 리팩터링하기 전에 제대로 된 테스트부터 마련한다. 테스트는 반드시 자가진단 하도록 만든다.
    - 테스트를 작성하는데 시간이 걸리겠지만, 신경 써서 만들어두면 디버깅 시간이 줄어서 전체 작업 시간은 오히려 단축된다.

- 수정하고 나면 곧바로 컴파일-테스트-커밋을 잊지 않도록 한다.
    - 조금씩 변경하고 매번 테스트하는 것은 리팩터링 절차의 핵심이다.
    - 한 번에 너무 많이 수정하려다 실수를 저지르면 디버깅하기 어려워서 결과적으로 작업 시간이 늘어난다.

- 코드의 명확성을 높이기 위한 이름 바꾸기에는 조금도 망설이지 마라.
    - 좋은 코드라면 하는 일이 명확히 드러나야 한다.
    - ‘찾아 바꾸기’ 기능을 제공하는 도구를 사용하면 어렵지 않다.

- **함수 추출하기**
    - 긴 함수를 리팩터링 할 때는 먼저 전체 동작을 각각의 부분으로 나눌 수 있는 지점을 찾는다.
    - 별도 함수로 빼냈을 때 유효 범위를 벗어나는 변수. 즉, 새 함수에서는 바로 사용할 수 없는 변수가 있는지 확인한다.
    - 새 함수에서도 필요하지만 값을 변경할 필요가 없는 변수는 매개변수로 전달한다.
    - 함수 안에서 값이 바뀌는 변수는 반환하도록 한다.
    - 흔히 IDE에서 자동으로 수행해주는 기능이 있다.

- **변수 인라인 하기**
    - 변수는 함수 안에서 표현식을 가리키는 이름으로 쓰이며, 대체로 긍정적인 효과를 준다. 
    하지만, 그 이름이 원래 표현식과 다를 바 없을 때도 있다.
    - 변수를 가장 처음 사용하는 코드를 찾아서 대입문 우변의 코드로 바꾼다.

- **임시 변수를 질의 함수로 바꾸기**
    - 임시 변수들이 있으면 로컬 범위에 존재하는 이름이 늘어나서 추출 작업이 복잡해진다.
    - 임시 변수의 들어갈 값을 대신 반환하는 질의 함수로 변경하도록 한다.

- **함수 선언 바꾸기**
    - 매개변수를 제거하려거든 먼저 함수 본문에서 제거 대상 매개변수를 참조하는 곳은 없는지 확인
    - 메서드 선언을 원하는 형태로 바꿈
    - 기존 메서드 선언을 참조하는 부분을 모두 찾아서 바뀐 형태로 수정

- **반복문 쪼개기**
    - 반복문을 별도로 분리한다.
    - 반복문이 중복되어 생기는 부수효과를 파악해서 제거한다.

- **문장 슬라이드하기**
    - 코드 조각(문장들)을 이동할 목표 위치를 찾는다. 코드 조각의 원래 위치와 목표 위치 사이의 코드들을 훑어보면서, 조각을 모으고 나면 동작이 달라지는 코드가 있는지 살핀다.
    - 코드 조각을 원래 위치에서 잘라내어 목표 위치에 붙여 넣는다.
    - 다음과 같은 간섭이 있다면 이 리팩토링을 포기한다.
        - 코드 조각에서 참조하는 요소를 선언하는 문장 앞으로는 이동할 수 없다.
        - 코드 조각을 참조하는 요소의 뒤로는 이동할 수 없다.
        - 코드 조각에서 참조하는 요소를 수정하는 문장을 건너뛰어 이동할 수 없다.
        - 코드 조각이 수정하는 요소를 참조하는 요소를 건너뛰어 이동할 수 없다.

- **단계 쪼개기**
    - 논리적인 단위로 기존 로직을 분석한다.
    - 로직을 분석하여 독립 함수로 추출하고 테스트한다.
    - 중간 데이터 구조를 작성하여 독립 함수의 파라미터로 추가한다.

- **함수 옮기기**
    - 함수를 옮겨야 하는 경우
        - 해당 함수가 다른 문맥에 있는 데이터를 **더 많이 참조**하는 경우
        - 해당 함수를 다른 클라이언트(클래스)에서도 **필요로** 하는 경우
    - 함수를 옮겨갈 새로운 문맥(클래스)이 필요한 경우에는 "**여러 함수를 클래스로 묶기**" 또는 **클래스 추출하기**를 사용한다.
    - 함수를 옮길 적당한 위치를 찾기가 어렵다면, 그대로 두어도 괜찮다.

- **반복문을 파이프라인으로 바꾸기**
    - 반복문에서 사용하는 컬렉션을 가리키는 변수를 하나 만든다.
    - 각각의 단위 행위를 파이프라인 연산으로 대체한다. 반복문의 첫줄부터 시작하며 각 단위의 행위를 수정한 뒤 테스트를 진행한다.
    - 수정이 완료되면 반복문을 제거한다.

- **조건부 로직을 다형성으로 바꾸기**
    - 다형성 동작을 표현하는 클래스들이 아직 없다면 만들어준다.이왕이면 적합한 인스턴스를 알아서 만들어 반환하는 팩토리함수도 함께 만든다.
    - 호출하는 코드에서 팩토리 함수를 사용하게 한다.
    - 조건부 로직 함수를 부모클래스로 옮긴다. (조건부 로직이 온전한 함수로 분리되어 있지 않다면, 먼저 함수로 추출한다.)
    - 부모클래스의 조건부 로직 메소드를 오버라이드하여 내부를 수정한다.
    - 같은 방식으로 각 조건절을 해당 서브클래스에서 메소드로 구현한다.
    - 부모클래스 메소드에는 기본 동작 부분만 남기거나, 가상함수로 정의한다.

- **함수 인라인 하기**
    - 일반적인 함수의 호출 과정을 거치지 않고, 함수의 모든 코드를 호출된 자리에 바로 삽입하는 방식
    - 이 방식은 함수를 호출하는 데 걸리는 시간은 절약되나, 함수 호출 과정으로 생기는 여러 이점을 포기하게 된다.
    - 따라서 코드가 매우 적은 함수만을 인라인 함수로 선언하는 것이 좋다.

- **생성자를 팩터리 함수로 바꾸기**
    - 팩터리팩토리 함수를 만든다. 팩토리 함수의 본문에서는 원래의 생성자를 호출한다.
    - 생성자를 호출하던 코드를 팩터리 함수 호출로 바꾼다.
    - 하나씩 수정할 때마다 테스트한다.
    - 생성자의 가시 범위가 최소가 되도록 제한한다.

- **타입 코드를 서브클래스로 바꾸기**
    - 조건에 따라 다르게 동작하도록 해주는 다형성을 제공 (타입 코드에 따라 동작이 달라져야하는 함수가 여러 개일 때 특히 유용)
    - 특정 타입에서만 의미가 있는 값을 사용하는 필드나 메서드가 있을 때 (필요한 서브클래스만 필요한 필드를 가지도록 하여 더 명확)
    - **대상 클래스에 직접 적용할지, 아니면 타입 코드 자체에 적용할 지**를 고민해야한다.
        - 대상 클래스에 직접 적용한다면 - 하위타입인 엔지니어를 만들 것
        - 타입 코드 자체에 적용한다면 - 유형 '속성' 을 부여하고, 이 속성을 클래스로 정의해 엔지니어 속성과 관리자 속성 같은 서브클래스를 만들 것

- **지역 변수 제거하기**
    - 유효범위를 신경 써야할 대상이 줄어들어 추출 작업이 훨씬 쉬워진다. 추출 작업 전에는 항상 지역 변수부터 제거한다.

### 리팩터링 이전 코드

```jsx
function statement(invoice, plays) {
	let totalAmount = 0;
	let volumeCredits = 0;
	let result = '청구 내역 (고객명: ${invoice.customer})\n'
	const format = newIntl.NumberFormat("en-US", 
											{ style: "currency", currency: "USD",
												minimumFractionDigits: 2}).format;
	for (let perf of invoice.performances) {
		const play =plays[perf.playID];
		let thisAmount = 0;

		switch(play.type) {
		case "tragedy":
			thisAmount = 40000;
			if (perf.audience > 30) {
				thisAmount += 1000 * (perf.audience - 30);
			}
			break;
		case "comedy":
			thisAmount = 30000;
			if (perf.audience > 20) {
				thisAmount += 10000 + 500 * (perf.audience - 20);
			}
			break;
		defalut:
			throw new Error("알 수 없는 장르: $(play.type)");
		}
		// 포인트를 적립한다.
		volumeCredits += Math.max(perf.audience - 30, 0);
		// 희극 관객 5명마다 추가 포인트를 제공한다.
		if ("comdey" == play.type) volumeCredits += Math.floor(perf.audience / 5);

		// 청구 내역을 출력한다.
		result += ' ${play.name}: ${format(thisAmount/100)} (${perf.audience}석)\n';
		totalAmount += thisAmount;
	}
	result += '총액: ${format(totalAmount/100)}\n';
	result += '적립 포인트: ${volumeCredits}점\n';
	return result;
}
```

### 리팩터링 이후 코드

```jsx
// createStatementData.js
export defalut function createStatement(invoice, plays) {
	const result = {};
	result.customer = invoice.customer;
	result.performances = invoice.performances.map(enrichPerformance);
	result.totalAmount = totalAmount(result);
	result.totalVolumeCredits = totalVoluemCredits(result);
	return result;

	function enrichPerformance(aPerformance) {
		const calculator = createPerformanceCalculator(aPerformance, playFor(aPerformance));
		const result = Object.assign({}, aPerformance);
		result.play = calculator.play;
		result.amount = calculator.amount;
		result.volumeCredits = calculator.volumeCredits;
		return result;
	}

	function playFor(aPerformance) {
		return plays[aPerformance.playID]
	}

	function totalAmount(data) {
		return data.performances.reduce((total, p) => total + p.amount, 0);
	}
	
	function totalVolumeCredits(data) {
		return data.performances.reduce((total, p) => total + p.volumeCredits, 0);
	}
}

function createPerformanceCalculator(aPerformance, aPlay) {
	switch(aPlay.type) {
	case "tragedy": return new TragedyCalculator(aPerformance, aPlay);
	case "comedy": return new ComedyCalculator(aPerformance, aPlay);
	defalut:
		throw new Error('알 수 없는 장르: ${aPlay.type}');
	}
}

class PerformanceCalculator {
	constructor(aPerformance, aPlay) {
	this.performance = aPerformance;
	this.play = aPlay;
	}

get amount() {
	throw new Error('서브클래스에서 처리하도록 설계되었습니다.');
	}

get volumeCredits() {
	return Math.max(this.performance.audience -30, 0);
	}
}

class TragedyCalculator extends PerformanceCalculator {
get amount() {
		let result = 40000;
		if(this.performance.audience < 30) {
		result += 1000 * (this.performance.audience -30);
		}
		return result;
	}
}

class ComedyCalculator extends PerformanceCalculator {
	get amount() {
		let result = 30000;
		if(this.performance.audience > 20) {
			result += 10000 + 5000 * (this.performance.audience - 20);
		}
		result += 300 * this.performance.audience;
		return result;
}

get volumeCredits() {
		return super.volumeCredits + Math.floor(this.performance.audience /5 );
	}
}
```

좋은 코드를 가늠하는 확실한 방법은 얼마나 수정하기 쉬운가다.

프로그래밍 팀의 현재와 이상의 차이에 항상 신경 쓰면서, 이상에 가까워지도록 리팩터링해야한다.

건강한 코드베이스는 생산성을 극대화하고 고객에게 필요한 기능을 더 빠르고 저렴한 비용으로 제공하도록 해준다!

## 느낀 점

---

초장부터 연극 예약 시스템 예시를 통해, 책의 전반적인 내용을 요약하듯이 다룬다. 오직 한가지의 예시를 가지고 자세하고 쉽게 설명해주기 때문에 좋았다.

개발 초보인 내가 처음 접했던 개발 관련 서적이 클린코드였어서 읽을 때 어려움을 많이 느꼈었는데, 
그래도 그 경험 덕분인지 이번 책은 좀 더 수월하게 이해가 되는 느낌이었다.

굉장히 인상 깊었던 것은 리펙터링의 주기가 굉장히 짧고 여러 번 반복된다는 사실이었다. 함수명을 바꾸고, 매개 변수를 다른 형식으로 바꾸고, 그것을 적용하는 것까지 모두 다른 커밋으로 나타낸다는 점이 신선했다. 

## 논의 내용

---

이 저자 또한 클린 코드의 저자처럼 테스트의 중요성을 곱씹어서 말하기 때문에, 뒤에 나올 테스트에 대한 챕터를 빨리 읽어보고 싶다는 생각이 드네요.
여러분이 생각하시는 혹은 상상하시는 좋은 테스트 코드의 구조가 있을까요?