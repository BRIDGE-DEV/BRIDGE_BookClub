# Clean Code
> 코드 품질을 측정하는 유일한 척도 = 분당 내지르는 WTF! 횟수

너무 마음에 드는 구절이라 가져와 봤다. WTF!

요즘 리팩토링에 재미도 느끼고 있고, 좋은 경험이 될 것 같다.

발전하는 사람이 되자.

### 들어가면서

자전거 타는 법을 알려주더라도, 직접 타보지 않으면 그 방법을 터득할 수 없다. 

깨끗한 코드를 작성하는 방법 역시 비슷하다.

원칙과 패턴도 알아야 하지만, 연습하고 실패도 맛봐야 한다.

코드를 끊임없이 읽고 이해하려고 노력해야 한다.

그렇게 한 발자국씩 나아가는 것이다.

## 1장 깨끗한 코드

### 코드가 존재하리라

코드는 요구사항을 명세하는 수단이며, 언젠간 코드가 사라지리라 기대하는 것은 비현실적이다.

정밀한 표현이 필요한 부분에서는 코드가 계속해서 필요하다.

### 나쁜 코드

나쁜 코드는 생산성을 떨어뜨리고, 유지 보수에 어려움을 초래한다.

나쁜 코드를 작성하게 된 원인 중 하나는 일단 돌아가는 코드를 만들고, 나중에 정리하겠다는 생각 때문이다.

그땐 하나 같이 생각한다. **'나중에 정리해야겠다.'**


>나중은 결코 오지 않는다.
>
>*르블랑의 법칙(Leblanc's Law)*

### 나쁜 코드로 치르는 대가

나쁜 코드가 쌓일수록 프로젝트의 진행 속도가 느려진다.

이를 해결하기 위해 온 사람들이 생산성 압박에 시달려 또 다시 나쁜 코드를 양산한다.

#### 원대한 재설계의 꿈

재설계의 시작은 꿈으로 가득 차있지만, 결국 현실에 부딪힌다.

#### 태도

프로그래머는 좋은 코드를 작성하기 위한 사명감을 가져야 한다.

전문가다운 태도로 나쁜 코드의 위험을 이해하고, 관리자에게 설명할 줄 알아야 한다.

#### 원초적 난제

코드를 깨끗하게 유지하는 것이 빨리 가는 유일한 방법이다.

#### 깨끗한 코드라는 예술?

좋은 코드를 작성하는 일은 '코드 감각'이다. 이는 마치 예술과 비슷하다.

#### 깨끗한 코드란?

바야네 스트롭스트룹, 그래디 부치, 큰 데이브 토마스, 마이클 페더스, 론 제프리스, 워드 커닝햄 등 여러 전문가들의 의견이 다양하게 제시되어 있다.

공통적으로 좋은 코드는 가독성이 높고, 명확한 추상화를 가지며, 효율적이고, 한 가지 일을 제대로 수행하는 코드로 정의된다.

~~다들 헤어스타일이 믿음이 간다,,~~

### 우리들 생각

깨끗한 변수 이름, 깨끗한 함수, 깨끗한 클래스를 만드는 방법을 소개한다.

절대적인 진리라고 생각하지만, 모두가 동의하지는 않으리라.

받아들이되 맹신하지는 말 것.
  

### 우리는 저자다

프로그래머가 작성한 코드는 누군가 읽게 된다.

대다수의 시간은 다른 모듈을 찾고, 읽는 데에 소요된다.

따라서 코드를 작성할 때 읽기 쉽게 만들어야 한다.

### 보이스카우트 규칙

> 캠프장에 처음 왔을 때보다 더 깨끗하게 해놓고 떠나라.
>
> *보이스카우트 규칙*

조금 긴 함수를 분할하거나, 약간의 중복을 제거해도 괜찮다.

조금씩 개선해나가자.

### 프리퀄과 원칙

이 책에서는 SRP, OCP DIP 등의 원칙을 산발적으로 거론한다.

### 결론

예술에 대한 책을 읽는다고 예술가가 된다는 보장은 없다.

**연습하자, 연습!**

## 느낀점

첫 장이라 그런지 추상적인 이야기가 주를 이룬 느낌이었다.

딱 준비 운동했다 정도의 느낌?

반복해서 언급했지만, 연습이 중요하다.

계속해서 부서지고 깨져봐야겠다,,

## 논의사항

요즘 ChatGPT-4를 보면 모호한 요구사항에도 적절한 답변을 출력하는 모습을 보입니다.

이런 발전 속에 정말 코드가 절대 사라지지 않을까요?

여러분의 의견이 궁금합니다.