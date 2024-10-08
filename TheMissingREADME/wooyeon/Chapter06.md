# 필독! 개발자 온보딩 가이드

## 6장. 테스트! 개발자의 든든한 지원군

> 업무 부하를 낮추면서 시스템 동작도 검증하는 테스트 방안

<br>

### 테스트를 꼭 해야 할까

테스트의 목적은 코드의 동작을 확인하는 것 뿐만이 아니라 나중에 의도치 않게 코드의 동작이 바뀌는 것을 방지하고 깔끔한 코드를 작성하게 도와준다. 개발자가 자신의 API를 사용하도록 강제하며 컴포넌트를 어떻게 사용하는지에 대한 문서 역할을 할 뿐 아니라 실험을 위한 공간으로서의 역할도 한다.

무엇보다 테스트는 소프트웨어가 원하는 대로 동작하는지를 검증한다. 예측할 수 없는 동작은 사용자와 개발자, 운영자 모두에게 문제를 야기한다. 기본적으로 테스트는 코드가 명시된 대로 동작하는지를 보여준다. 준비가 완료되고 나면 테스트는 새로운 변경사항이 추가돼도 기존 동작을 유지할 수 있는 방패막이가 되어준다. 오래된 테스트가 실패하게 되면, 개발자가 동작을 의도적으로 변경한 것 때문인지 아니면 버그가 발생한 것 때문인지를 판단해야 한다.

또한 개발자는 테스트를 작성하면서 프로그램의 인터페이스와 실제 구현에 대해 고민해볼 수 있다. 개발자는 주로 자신이 작성한 코드를 테스트 코드를 안에서 처음 사용해본다. 새로운 코드에는 잘 다듬어지지 않은 부분이 있을 수 있다. 테스트를 수행하면 미숙한 인터페이스 설계를 일찍 발견해서 수정할 수 있다.

_(게임 프로그래머에게도 해당되는 말일까?)_

또한 스파게티 코드나 의존성이 너무 많은 코드처럼 엉망으로 구현된 코드는 테스트가 어려워지므로 이를 개선할 기회를 얻을 수 있다. 개발자는 테스트를 작성하면서 관심사의 분리를 개선해 코드를 잘 정리하고 코드 간의 강력한 결합을 줄일 수 있다.

_(이는 테스트 코드를 처음 작성해봤을 때도 느꼈던 점이다.)_

테스트를 하면서 코드를 깔끔하게 만드는 효과가 굉장히 좋았기에 `테스트 주도 개발(TDD)`는 차츰 보편화됐다. TDD는 코드를 작성하기 전에 테스트를 먼저 작성하는 방법이다. 테스트를 작성하는 시점에 그 테스트는 실패할 것이며 그 후로 코드를 완성하면서 성공하게 되는 방식이다. 개발자는 TDD 원칙을 따르면서 실제 코드를 작성하기에 앞서 코드의 동작, 인터페이스 설계, 다른 코드와의 통합 등을 먼저 고민하게 된다.

_(TDD는 이번 여름에는 꼭 도전해보고 싶다!)_

테스트는 코드를 어떻게 활용할 것인지를 보여주는 일종의 문서 역할도 한다. 경험이 많은 프로그래머가 새로운 코드베이스를 만날 경우 코드를 이해하기 위해 가장 먼저 읽는 것이 테스트 코드다. 

<br>

### 테스트의 유형과 기법

테스트의 유형과 기법은 매우 다양하다. 그 중 가장 보편적인 유형의 테스트인 단위 테스트 Unit Test, 통합 테스트 Integration Test, 시스템 테스트 System Test, 성능 테스트 Performance Test, 인수 테스트 Acceptance Test 정도를 살펴보겠다.

`단위 테스트`는 코드의 '단위', 즉 메소드나 동작 하나를 검증한다. 단위 테스트는 빠르고 작으며 집중적이어야 한다. 하나의 코드 단위에만 집중하는 소규모 테스트는 실패했을 때 어디가 문제인지 쉽게 이해할 수 있다.

_(내가 해본 테스트는 거의 이거일 것이다.)_


`통합 테스트`는 여러 컴포넌트가 함께 어우러져 동작하는지를 검증한다. 여러 객체의 인스턴스를 생성해서 서로 의존하며 동작하는 코드를 테스트하기 위한 코드를 작성 중이라면 통합 테스트를 작성하고 있다고 봐도 무방하다. 통합 테스트를 활용하면 독립적인 단위를 개별적으로 테스트하는 것만으로는 식별하기 어려운 문제를 찾아낼 수 있다.

`시스템 테스트`는 시스템 전체를 검증한다. 종단 간 end-to-end 워크플로는 프로덕션 환경의 전반적인 단계에서 실제 사용자의 동작을 시뮬레이션한다.

`성능 테스트`는 주어진 설정하에서 시스템의 성능을 측정하는 것으로, 예를 들어 부하 테스트나 스트레스 테스트가 있다. `부하 테스트 load test`는 시스템에 다양한 수준의 부하를 걸고 성능을 측정한다. (10명 동시접속, 만명 동시접속 등) `스트레스 테스트 stress test`는 장애가 발생하는 수준까지 시스템 부하를 올린다. 시스템이 어느 정도의 부하를 견딜 수 있는지 그리고 그 수준을 넘어서는 부하가 걸리면 어떤 일이 벌어지는지를 확인한다.

`인수 테스트`는 사용자나 사용자의 대리인이 제공된 소프트웨어가 인수 조건을 만족하는지 검증하는 테스트로서, 주로 공식 인수 테스트 및 조건이 계약에 포함된 엔터프라이즈 소프트웨어를 대상으로 한다.

```
테스트에 대해 너무 완벽하려고 노력하지 않아도 된다.
성공적인 프로젝트는 실용성을 위주로 현실적인 테스트에 대한 결정을 내리므로 그렇게 하면 된다.
어떤 식으로도 테스트를 개선할 기회를 찾았다면 반드시 개선하자!
```

<br>

### 테스트 도구

테스트 도구는 테스트 작성 도구, 테스트 실행 프레임워크, 코드 품질 도구 등 몇 가지로 분류할 수 있다. 모킹 mocking 라이브러리 같은 `테스트 작성 도구`를 이용하면 깔끔하고 효율적인 테스트를 작성할 수 있다. `테스트 프레임워크`는 셋업부터 마무리까지 테스트의 수명주기를 모델링해서 테스트를 실행하게 해주는 도구다. `코드 품질` 도구는 코드 커버리지와 복잡도 등을 분석하거나 정적 분석을 통한 버그 발견 및 코딩 스타일 에러 검사 등에 사용한다. 분석 도구는 주로 빌드나 컴파일 단계에서 실행하게 된다.

새로운 도구를 추가할 때마다 부담감은 커진다. 조직 내의 모든 구성원이 그 새로운 도구는 물론, 도구가 지닌 특이점을 이해해야 하기 때문이다. 게다가 해당 도구가 수많은 다른 라이브러리에 의존하면서 시스템 복잡도를 증가시키는 경우도 있다. 오히려 테스트를 더디게 하는 도구도 간혹 있다. 따라서 복잡도에 대한 트레이드오프를 정당화할 수 이씅며 팀이 동의하기 전까지는 아직 잘 알려지지 않은 도구를 도입하는 일은 피하는 편이 좋다.

<br>

#### 모킹 라이브러리

모킹 라이브러리는 특히 객체지향 코드의 단위 테스트에 주로 사용된다. 코드는 주로 외부 시스템이나 라이브러리 또는 객체에 의존하는 경우가 많기 대문이다. `모의 객체 mock`는 실제 시스테밍 제공하는 인터페이스를 유사하게 모방하는 스텁 객체로 외부 의존성을 대체한다. 모의 객체는 입력에 대해 하드코딩된 응답을 리턴함으로써 테스트에 필요한 기능을 구현한다.

외부 의존성을 줄이면 단위 테스트를 더 빠르고 집중적으로 수행할 수 있다. 메소드에 대한 모의 객체를 제공하면 개발자가 한 가지 특징만 검증하는 단위 테스트에만 집중할 ㅜㅅ 있다.

모의 객체를 활용하면 테스트를 하기 위한 메소드나 파라미터, 변수를 애플리케이션 코드에 추가할 필요가 없다. 테스트를 위해 코드를 변경하면 유지보수가 어렵고 코드의 가독성도 떨어지며 이해하기 어려운 버그가 생겨난다.

모의 객체는 이렇듯 유용하지만 남용해서는 안 된다. 모의 객체에 복잡한 로직을 넣으면 테스트는 불안정해지고 이해하기도 어려워진다. 단위 테스트에 기본적인 모의 객체만 사용하는 것부터 시작하고 여러 테스트에서 모의 객체를 생성하는 로직을 반복하지 않는다면 공용 모의 클래스를 만들지 말자.

모의 객체에 과도하게 의존하는 것 역시 코드가 강하게 결합돼 있음을 의미하는 코드 악취일 뿐이다. 모의 객체가 필요한 시점이 되면 모의 시스템에 대한 의존성을 제거하도록 리팩터링이 가능한지부터 고민해보자.

_(모킹 라이브러리는 사용해본 적 없는데, 한 번 공부해볼만 한 것 같다.)_

<br>

#### 테스트 프레임워크

테스트 프레임워크는 테스트 코드를 작성하고 실행하는 도구다. 프레임워크의 역할은 다음과 같다.

- 테스트 셋업과 해제
- 테스트 실행 및 조율
- 테스트 결과 보고서 생성
- 추가 검증 메소드 등의 도구 제공
- 코드 커버리지 도구와의 통합

<br>

#### 코드 품질 도구

고품질의 코드를 작성하는 데 도움이 되는 도구를 활용하자. 코드 품질 규칙을 강제하는 도구를 `린터`라고 부른다. 린터는 정적 분석과 스타일 검사를 실행한다. 코드 품질 모니터링 도구는 복잡도나 테스트 커버리지 같은 지표도 보고해준다.

`정적 코드 분석기`는 파일 핸들을 열린 채로 둔다거나 값이 대입되지 않은 변수를 사용하는 등의 일반적인 실수를 찾아준다. 파이썬처럼 문법 오류를 검사하는 컴파일러가 없는 동적 언어를 사용할 때 특히 중요하다. 분석기는 잘 알려진 코드 악취를 찾아내고 의심스러운 코드를 강조하는 기느옫 제공하지만 거짓양성 보고의 가능성이 있으므로 이에 대해서는 신중하게 생각해야 한다.

`코드 스타일 검사기`를 사용하면 모든 소스 코드를 동일한 방식으로 작성할 수 있다. 예컨대 한 줄당 최대 문자 수나 카멜 표기법과 스테이크 표기법의 혼용 여부, 적절한 들여쓰기 같은 것을 검사한다. 여러 프로그래머가 하나의 코드베이스를 공유할 때는 일관된 스타일을 유지하는 게 도움이 된다. 모든 스타일 규칙이 자동으로 적용되도록 IDE를 설정해두길 강력히 권한다.
_(방법을 찾아보면 좋겠다)_

`코드 복잡도 도구`는 `순환 복잡도`를 계산하거나 간단하게 코드의 분기 횟수를 확인함으로써 너무 복잡한 로직을 작성하지 않게 해준다. 코드의 복잡도가 높을수록 테스트는 어려워지고 결함이 발생할 확률이 높아진다.

`코드 커버리지 도구`는 테스트가 몇 줄의 코드를 실행했는지를 측정한다. 만일 여러분이 코드를 변경한 후 코드 커버리지가 낮아졌다면 테스트를 더 많이 작성해야 한다는 뜻이다. 적절한 수준의 커버리지(보통 65~85% 사이)를 유지시키자. 커버리지가 너무 높거나 너무 낮으면 오판할 가능성이 높다.

엔지니어는 코드 품질 지표에 집착하는 경향이 있다. 코드 품질이 나빠지도록 놔둘 필요는 없지만 그렇다고 하던 일을 모두 멈추고 프로젝트를 정리하려는 시도는 하지 말자.

<br>

### 개발자 스스로 직접 테스트를 작성하자

여러분에게는 팀이 작성한 코드가 의도대로 동작하게 만들 의무가 있다. 누군가가 여러분의 코드를 대신 정리해줄 거라 기대하지 말고 직접 테스트를 작성하자.

여러분이 작성한 코드의 안정성을 검증하는 데 QA팀이 도움을 줄 수는 있지만 그렇다고 QA팀이 여러분을 대신해 모든 테스트를 수행하게 해서는 안 된다. 정식 QA팀을 갖춘 회사에서 근무하고 있다면 QA팀의 역하로가 협업 방법을 알아내기 바란다.

<br>

#### 테스트는 깔끔하게 작성하자

테스트도 신경 써서 작성해야 한다. 테스트 때문에 의존성이 더해질 수도 있고 테스트도 유지보수가 필요하며 시간이 지나면 리팩터링도 해야 한다. 편법을 써서 작성한 테스트는 유지보수 비용이 높아서 향후 개발 속도를 저해하는 요인이 될 수 있다. 또한 안정성도 떨어져서 신뢰할 수 있는 결과를 기대하기 어렵다.

테스트에도 좋은 프로그래밍 기법을 적용해야 한다. 테스트가 어떻게 동작하는지, 어떻게 실행하는지 그리고 왜 그 테스트가 필요한지 문서화하자. 값을 하드코딩하지도 말고 코드를 중복 사용하는 일도 피하자. 테스트의 응집력을 유지하며 결합도를 낮추자.
_(중요한 부분)_

상세 구현보다는 근본적인 기능을 테스트하는 데 중점을 둬야 한다.

테스트에 필요한 의존성은 실제 코드의 의존성과 분리해서 관리하자. 대부분의 빌드 및 패키징 시스템은 테스트 전용 의존성을 선언할 수 있다.
_(유니티에서도 Test Assemblies라는 기능으로 된다고 한다. 오..)_

<br>

#### 과도한 테스트는 삼가자

테스트를 작성하는 데 너무 많은 노력을 기울이지는 말자. 테스트는 실패했을 때 충분한 의미를 갖도록 작성하자. 커버리지 지표를 올리기 위한 목적으로 테스트 코드를 작성하지는 말자. 코드에 내포된 위험에 가장 큰 영향을 미치는 테스트를 작성하는 데 주력하자.

가장 가치 있는 테스트에 역량을 집중하자. 테스트를 작성하고 유지하는 데에는 시간이 필요하다. 그러므로 가장 가치 있는 테스트에 집중하는 편이 비용 대비 효과가 크다.

<br>

### 테스트 결정성: 항상 동일한 테스트 결과를 만들려면

`결정적 코드`란 입력이 같으면 그 출력도 항상 같은 코드를 말한다. 반면 `비결정적 코드`는 입력이 같아도 출력은 다를 수 있다. 비결정적 테스트는 피로도가 높은 만큼 많은 프로젝트에서 문제가 된다. 그래서 비결정적 테스트가 왜 안 좋은지, 어떻게 수정하는지 그리고 비결정적 테스트를 작성하지 않으려면 어떻게 해야 하는지를 이해하는 것이 중요하다.

비결정적 코드는 테스트의 가치를 떨어뜨린다. 테스트가 간헐적으로 실패한다는 것은 매번 동일한 현상이 발생하지는 않는다는 뜻이므로 재현과 디버깅이 어렵다. 코드가 문제인지 테스트가 문제인지 알 수 없기 때문이다. 이런 테스트는 의미 있는 정보를 제공하지 않기 때문에 개발자는 테스트의 실패를 무시하고 결국 잘못된 코드를 체크인하게 된다.

간헐적으로 실패하는 테스트는 비활성화시키거나 즉시 수정해야 한다. 이런 테스트를 발견하면 문제 상황을 재현해야 한다.

비결정성은 슬립이나 타임아웃 난수 생성 등을 제대로 처리하지 못해서 발생하기도 한다. 시간과 임의성을 결정적으로 만들고 테스트 실행 후에는 비결정성을 제거하자.

<br>

#### 난수생성기에 적절한 시드값을 사용하자

반드시 원하는 난수가 나올 수 있는 시드값을 사용해야 한다.

<br>

#### 단위 테스트에서 원격 시스템을 호출해서는 안 된다

원격 시스템 호출은 네트워크 연결이 필요한데, 네트워크는 대체로 안정적이지 않다. 네트워크 호출에 타임아웃이 발생해서 단위 테스트에 비결정성이 추가되기도 한다.

모의 객체를 사용하거나 원격 시스템은 통합 테스트에서만 사용하도록 코드를 리팩터링해서 원격 시스템 호출을 제거할 수 있다.

<br>

#### 클럭을 주입하자

특정한 간격의 시간에 의존하는 코드는 제대로 처리하지 않으면 비결정성을 유발한다. 특정 작업에 걸리는 시간은 네트워크 레이턴시나 CPU 속도 같은 외부 요인에 영향을 받는 반면, 시스템 클럭은 외부 요인과는 무관하게 시간이 계속 흐른다.

now나 sleep 같은 정적 시스템 클럭 메소드를 사용한다면 코드가 시간에 의존적이라는 뜻이다.

시스템 클럭을 주입할 수 있게 만들어야 한다. (모의 객체 사용)

<br>

#### 슬립과 타임아웃의 사용을 삼가자

별도의 스레드나 프로세스, 머신에서 테스트가 돌아가는 경우, 개발자는 테스트가 결과를 검증하기 전에 작업을 완료할 수 있도록 sleep() 메소드를 호출하거나 타임아웃을 이용하는 경우가 많다. 이 방법의 문제점은 다른 스레드의 실행이 어느 시점이 지나면 완료될 것이라고 가정한다는 점인데, 이런 가정에 의존해서는 안 된다.

여러 이유로 테스트가 간혹 실패할 수도 있고, 테스트에서 sleep() 메소드를 호출하거나 타임아웃을 너무 길게 설정하면 테스트의 실행 시간도 느려지며 그만큼 개발과 디버깅 절차도 느려지게 된다.

만일 테스트에서 sleep() 메소드를 호출하거나 타임아웃을 설정해야 한다면 테스트를 재구성해서 모든 것이 결정적으로 실행될 수 있는지를 검토해보자. 그렇지 못해도 괜찮지만 최선을 다해 노력해보자. 동시적 또는 비동기적 코드의 테스트가 항상 결정적인 것은 아니다.

<br>

#### 네트워크 소켓과 파일 핸들을 닫자
#### 0번 포트에 바인딩하자
#### 파일과 데이터베이스에 대해 고유한 경로를 생성하자
#### 이전 테스트의 상태를 격리하고 해제하자

상태를 정리하지 않는 테스트도 비결정성을 유발한다.

테스트가 성공하든 실패하든 상태는 반드시 리셋해야 한다.

<br>

#### 테스트의 실행 순서에 의존하지 말자

테스트 사이에 로직을 공유하려면 셋업과 해제 메소드를 사용하면 된다. 각 테스트에 필요한 데이터는 셋업 메소드를 이용해 마련하고 해제 메소드에서 해당 데이터를 제거하면 된다. 각 테스트를 실행할 때마다 상태를 리셋해주면 상태의 변화로 인태 테스트가 서로 간섭받는 일이 없다.

### 개발자의 필수 체크리스트
### 레벨업을 위한 읽을거리

<br>

### 생각

그럴 것 같긴 했지만 난 진짜 테스트 코드 찍먹만 해봤구나..
현업자들한테 테스트 코드 사용 중인지, 어떻게 쓰는지 물어봐야겠음

모킹 라이브러리와 테스트 프레임워크 둘 다 안쓰니
직접 객체들을 임시로 생성하고 직접 셋업과 해제 코드를 작성해줘야 함