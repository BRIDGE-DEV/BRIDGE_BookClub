
#### 단어 정리

**테스트 스위트 test suite** 
- 특정 테스트 주기에서 실행해야 하는 테스트 케이스(또는 테스트 스크립트)의 집합이나 테스트 절차
- 테스트 실행 목적에 따라 그룹화된 테스트 케이스의 집합
- 실행 환경에 따라 구분해 놓은 테스트 케이스의 집합
- 각 테스트 케이스가 시나리오를 포함하고 있는 경우에 테스트 스위트를 이용한다
- 테스트 스위트 내 하나의 테스트 케이스가 성공적으로 끝나야 다음 테스트 케이스로 넘어간다
- 테스트 스위트가 유용하게 쓰이는 테스트 유형 = 빌드 검증 테스트, 스모크 테스트, E2E 테스트, 기능성 검증 테스트, 리그레션 테스트
- 자동화 리그레션 테스트 케이스 집합 또는 end-to-end 시나리오로 구성된 테스트 케이스 집합을 연속적으로 실행 가능

예) 테스트 스위트 (각 테스트 케이스는 테스트 스크립트를 포함)

- 테스트 케이스 1: 로그인

- 테스트 케이스 2: 새로운 제품 추가

- 테스트 케이스 3: 체크아웃

- 테스트 케이스 4: 로그아웃

**코드 커버리지 code coverage**

코드 커버리지는 소프트웨어 테스트에서 사용되는 지표 중 하나로, 코드의 실행 여부를 기반으로 코드의 품질과 완성도를 측정하는 방법입니다. 즉, 테스트 케이스를 실행할 때 코드 내의 각 요소가 실행되는 빈도를 측정하여, 테스트 케이스가 커버하는 코드 비율을 나타내는 지표입니다. 보통 코드 커버리지는 테스트 케이스의 실행 여부를 기준으로 계산됩니다. 이를 통해, 테스트 케이스가 커버하지 않은 코드 블록을 식별하여 개발자가 이를 보완할 수 있도록 도와줍니다.

보통 코드 커버리지는 여러 가지 요소를 측정합니다. 가장 일반적인 것은 다음과 같습니다.

1. Statement Coverage: 실행된 문장 수 / 전체 문장 수
2. Branch Coverage: 실행된 조건문 블록 수 / 전체 조건문 블록 수
3. Function Coverage: 실행된 함수 수 / 전체 함수 수
4. Decision Coverage: 수행된 분기 수 / 전체 분기 수
5. Condition Coverage: 수행된 조건 수 / 전체 조건 수

**스캐폴딩 scaffolding**

*스캐폴딩(Scaffolding)* 은 프로그래밍에서 새로운 프로젝트나 모듈을 시작할 때, 초기 구조와 설정을 자동으로 생성해주는 과정이나 도구를 가리킵니다. 이는 개발자가 처음부터 모든 것을 수동으로 설정하고 작성하는 번거로움을 덜어주고, 더 빠르게 개발을 시작할 수 있도록 도와줍니다.


#### 테스트를 꼭 해야 할까?

테스트의 목적은 코드의 동작을 확인하는 것 뿐만 아니라 나중에 의도치 않게 코드의 동작이 바뀌는 것을 방지하고 깔끔한 코드 작성을 도와주기 위함도 있다.

- 개발자가 API를 사용하도록 강제한다.
- 컴포넌트를 어떻게 사용하는지에 대한 문서 역할을 한다.
- 실험을 위한 공간의 역할을 한다.
- 소프트웨어가 원하는 대로 동작하는지 검증한다.
- 새로운 변경사항이 추가돼도 기존 동작을 유지할 수 있는 방패막이가 된다.
- 테스트 코드를 작성하면서 프로그램의 인터페이스와 실제 구현에 대해 고민해 볼 수 있다.
- 미숙한 인터페이스 설계를 테스트를 수행하면서 일찍 발견해 볼 수 있다.
- 스파게티 코드나 의존성이 엉망인 코드르 개선할 기회를 얻을 수 있다.

**테스트 주도 개발 test - driven development (TDD)** : 코드를 작성하기 전에 테스트를 먼저 작성하는 방법. 테스트를 작성하면서 실패를 겪고 코드를 완성하면서 성공하게 되는 방식. 실제 코드를 작성하기 전에 코드의 동작. 인터페이스 설계, 다른 코드와의 통합 등을 먼저 고민하게 된다.

테스트는 코드를 어떻게 활용할 것인지를 보여주는 문서 역할을 한다. 
새로운 코드베이스를 만나게 되면 코드를 이해하기 위해 가장 먼저 읽게 되는 코드이기도 하며 테스트 스위트는 개발자의 훌륭한 놀이터이다.


#### 테스트 유형과 기법

- **단위 테스트 unit test**
	- 코드의 단위, 즉 메소드나 동작 하나를 검증한다. 단위 테스트는 빠르고 작고 집중적이어야 한다. 
- ****통합 테스트 intergration test**
	- 여러 컴포넌트가 어우러져 동작하는지 검증한다. 서로 의존하며 동작하는 코드를 테스트하기 위한 코드를 작성 중이라면 통합 테스트를 작성하고 있는 것이다.
- **시스템 테스트 system test**
	- 시스템 전체를 검증한다. end to end(e2e) 워크플로는 프로덕션 환경의 전반적인 단계에서 실제 사용자의 동작을 시뮬레이션한다.
- **성능 테스트 performance test**
	- 주어진 설정에서 시스템의 성능을 측정하는 것이다.
	- 부하테스트 load test 와 스트레스 테스트 stress test로 구분된다.
		- 부하 테스트 : 시스템에 다양한 수준의 부하를 걸고 성능을 측정한다.
		- 스트레스 테스트 : 장애가 발생하는 수준까지 부하를 올려 어느 정도까지 부하를 견디는지, 수준을 넘어가면 어떤 일이 발생하는지를 확인한다.
	- 용량 계획과 SLO(서비스 수준 목표) 설정에 도움이 된다.
- **인수 테스트 acceptance test**
	- 사용자나 사용자의 대리인이 제공된 소프트웨어가 인수 조건을 만족하는지 검증하는 테스트

#### 테스트 도구

테스트 도구의 분류

- 테스트 작성 도구
	- 모킹 mocking
- 테스트 실행 프레임워크
	- 셋업부터 마무리까지 수명주기를 모델링해서 실행하게 해주는 도구
- 코드 품질 도구
	- 코드 커버리지와 복잡도 등을 분석하거나 정적 분석을 통한 버그 발견 및 코딩 스타일 에러 검사. 주로 빌드나 컴파일 단계에서 실행됨.

#### 모킹 라이브러리

- 모킹 라이브러리는 객체지향 코드의 단위 테스트에 주로 사용된다.
- **모의 객체 mock** : 실제 시스템이 제공하는 인터페이스를 유사하게 모방하는 stub 객체로 외부 의존성을 대체한다. 모의 객체는 하드코딩된 응답을 리턴해 테스트한다.
- 외부 의존성을 줄이면 단위 테스트를 더 빠르고 집중적으로 수행할 수 있다.
- 모의 객체를 활용하면 테스트를 하기 위한 메소드, 파라미터, 변수를 실제 애플리케이션 코드에 추가할 필요 없다.
- **주의점** : 모의 객체에 과도하게 의존하는 것 역시 결합도가 강하다는 것을 의미한다. 단위 테스트에 기본적인 모의 객체만 사용하는 것부터 시작하자

#### 테스트 프레임워크

**테스트 프레임워크** : 테스트 코드를 작성하고 실행하는 도구, 단위테스트, 통합 테스트, 성능 테스트, UI테스트까지 조율한다.

- 테스트 셋업과 해제
- 테스트 실행 및 조율
- 테스트 결과 보고서 생성
- 추가 검증 메소드 등의 도구 제공
- 코드 커버리지 도구와의 통합

#### 코드 품질 도구

**린터 linter** : 코드 품질 규칙을 강제하는 도구. 정적 분석과 스타일 검사를 실행한다.

**정적 코드 분석기 static code analyzer** : 뮨법 오류를 검사하는 컴파일러가 없는 동적 언어에 사용한다. 값이 초기화되지 않은 변수를 찾거나 파일 핸들을 열린 채로 두거나 하는 실수를 찾는다. 

**코드 스타일 검사기 code style checker** : 한 줄당 최대 문자 수나 캐멀 표기법과 스네이크 표기법의 혼용 여부, 들여쓰기 등을 검사해 모든 소스 코드를 동일한 스타일로 통일 시킬 수 있으니 IDE에 설정하길 바란다.

**코드 복잡도 도구 code complexity tool** :  순환 복잡도 cyclomatic complexity를 계산하거나 분기횟수를 확인해 너무 복잡한 로직을 작성하지 않도록 해준다. 코드의 복잡도가 높을 수록 테스트가 어려워지고 결함이 발생하기 쉬워진다.

코드 베이스의 크기가 커질 수록 순환 복잡도가 커지기 때문에 점수가 높다고 마냥 나쁜 것은 아니지만 복잡도가 갑작스럽게 높아진다면 추가된 메소드의 복잡도가 높은 것이므로 주의 깊게 볼 필요가 있다.

**코드 커버리지 도구 code coverage tool**: 테스트가 몇 줄의 코드를 실행했는지를 측정한다.

- 적절한 수준의 커버리지(65%~85% 사이)를 유지시키자.
- 테스트 품질을 커버리지만으로 측정하는 것은 좋은 방법이 아니다.
- 스캐폴딩 scaffolding 같이 자동으로 생성된 코드나 직렬화 클래스를 검사에 포함시키면 커버리지 지표가 엉뚱하리만치 낮아진다.
- 단위 테스트로 100%의 커버리지를 구현한다고 해도 안정성이 보장되는 것은 안디ㅏ.

#### 개발자 스스로 직접 테스트를 작성하자

QA팀이 하는 일

- 블랙박스 black box나 화이트 박스white-box 테스트 작성
- 성능 테스트 작성
- 통합 테스트, 사용자 인수 테스트, 시스템 테스트 수행
- 테스트 도구 제공 및 유지보수
- 테스트 환경과 인프라스트럭처 유지보수
- 정식 테스트 인증과 릴리스 절차 정의

QA가 모든 테스트를 수행하게 두어서는 안된다. 테스트 코드는 직접 작성하고 QA팀의 역할과 협업 방법을 알아내야 한다.

#### 테스트는 깔끔하게 작성하자

테스트도 유지보수가 필요하고 리팩터링이 필요하다. 테스트에도 좋은 프로그래밍 기법이 적용돼야 한다. 응집도를 높이고 결합도를 낮추며 하드코딩은 하지말고 코드가 중복되어서도 안된다. 즉 실제 코드를 작성할 때처럼 깔끔하게 작성해야 한다.

상세 구현보다 근본적인 기능 테스트에 중점을 두자
테스트가 특정 구현에 강하게 결합되지 않게 하자.

#### 과도한 테스트는 삼가자

테스트를 너무 많이 작성하면 적재적소에 활용하는 감각을 잃기 쉽다.

- 테스트는 실패했을 때 의미를 갖도록 작성하자
- 커버리지 지표를 올리기 위한 목적으로 작성하지 말자
	- 가벼운 데이터베이스 래퍼, 서드파티 라이브러리, 기본적인 변수대입 등을 테스트해 높은 커버리지를 달성해도 의미가 없다.
- 코드 커버리지는 규칙이 아닌 가이드 정도로 생각하자
- 가장 가치 있는 테스트에 역량을 집중하자.
	- 집중할 부분은 위험 매트릭스 risk matrix를 이용해 찾으면 된다.
		- 위험 매트릭스는 위험의 발생 가능성과 위험이 발생했을 때의 영향도를 기준으로 정의한다.

#### 테스트 결정성 : 항상 동일한 테스트 결과를 만들려면

**결정적 코드 deterministic code** : 입력이 같으면 항상 같은 출력이 나오는 코드
**비결정적 코드 nondeterministic code** : 입력이 같아도 출력이 다를 수 있는 코드

네트워크 소켓을 통해 원격 웹서비스를 호출하는 단위 테스트는 비결정적이다.

비결정적 코드는 테스트 가치를 떨어뜨린다. 테스트가 간헐적으로 실패하면 개발자는 코드가 문제인지 테스트가 문제인지 알 수 없기 때문에 테스트가 의미 있는 정보를 제공하지 못한다. 

이러한 테스트가 발견되면 여러 번의 루프를 실행해 실패하는 상황을 재연하고 비결정성을 제거하거나 버그를 수정해야 한다.

비결정성은 슬립 sleep이나 타임아웃 난수 생성 등을 제대로 처리하지 못해 발생한다.
side effect나 원격에 의존하는 테스트도 비결정성을 유발한다.

#### 난수생성기에 적절한 시드값을 사용하자

난수 생성기 random number generator는 원하는 난수가 나올 수 있는 시드값 seed value을 사용하자

난수 생성기는 보통 시스템 클럭을 사용하므로 매 실행마다 다른 값을 리턴한다. 이럴 때 상수를 시드값으로 지정해 결정적으로 만들면 된다.

#### 단위 테스트에서 원격 시스템을 호출해서는 안된다.

원격 시스템 호출은 네트워크 연결이 필요한데, 네트워크는 안정적이지 않아 비결정적이다. 원격 호출을 제거해 단위 테스트의 속도와 이식성을 유지하자. 원격 호출 시스템에 의존하는 단위 테스트는 이식성이 떨어진다.

모의 객체를 활용하거나 원격 시스템은 통합 테스트에서만 사용하자

#### 클럭을 주입하자

특정 간격의 시간에 의존하는 코드는 비결정성을 유발한다.  시스템 클럭이 CPU 속도나 네트워크 레이턴시와 무관하게 흐르기 때문이다.

정적 시스템 클럭 메소드(now, sleep 등)를 활용하기보다 테스트 시점에 시간을 제어할 수 있도록 클럭을 주입하는 편이 좋다.

#### 슬립과 타임아웃의 사용을 삼가자

별도의 스레드나 프로세스, 머신에서 테스트가 돌아가는 경우, 개발자는 테스트가 결과를 검증하기전에 작업을 완료하도록 sleep() 메소드를 호출하거나 타임아웃을 이용하는 경우가 있다. 

이는 다른 스레드가 어느 시점에 완료될 것이라고 가정한다는 것인데, 이 가정에 의존해서는 안된다.
언어의 가상 머신이나 인터프리터 가비지 콜렉터, 운영체제 등등이 실행하는 프로세스에 리소스를 충분히 할당하지 못하면 테스트는 실패가 된다.

또한 sleep이나 타임아웃을 사용한 시간만큼 테스트 속도가 늦어지기 때문에 디버깅도 오래걸리게 된다.

sleep이나 타임아웃을 사용한 테스트가 있다면 전면적으로 검토하고 결정적으로 만들자

#### 네트워크 소켓과 핸들을 닫자

테스트의 실행시간이 짧고 테스트가 종료되면 운영체제가 모든 리소스를 해제할 거라 생각하는 까닭에 리소스 누수를 일으키는 테스트가 많다.

하지만 테스트 실행 프레임워크는 리소스 누수를 정리하는 경우가 많이 없다.
리소스 누수는 비결정성을 일으킨다. 리소스 누수가 많아지면 새로운 리소스를 할당하지 못하며 새 소켓이나 네트워크를 열 수 없어 테스트가 실패한다.

#### 0번 포트에 바인딩하자

모든 테스트에서 동일한 포트에 바인딩하는 것이 보편적인 기법이다. 다만 병렬적으로 실행하면 실패하게 된다.

네트워크 소켓에 0번 포트를 바인딩하면 운영체제는 사용 가능한 포트를 자동적으로 열어준다.  그러면 테스트 코드는 바인딩된 포트를 찾아 이후의 작업에 사용하게 된다.

#### 파일과 데이터베이스에 대해 고유한 경로를 생성하자

파일명, 디렉터리 경로, 데이터베이스나 테이블 이름은 동적으로 생성하자
그러면 모든 테스트가 각자 다른 위치에서 읽고 쓰는 작업을 수행하므로 테스트를 병렬로 실행할 수 있다.

#### 테스트의 실행 순서에 의존하지 말자

테스트가 순서에 의존하게 되면 다양한 문제가 발생한다.

- 첫 번째 테스트가 실패하면 두 번째 테스트도 실패한다,.
- 두 번째 테스트는 첫 번째 테스트가 완료되기 전까지 실행할 수 없으므로 테스트의 병렬 실행이 어렵다.
- 첫 번째 테스트를 수정하면 의도치 않게 두 번째 테스트도 실패할 수 있다.
- 테스트 실행기의 변경으로 테스트가 다른 순서로 실핼될 수 있다.

테스트 사이의 로직을 공유하려면 셋업과 해제 메소드를 사용하자 각 테스트에 필요한 데이터를 셋업으로 마련해준다면 테스트 사이의 순서 의존성을 없앨 수 있다.

---

**이것만은 지키자**
- 버그가 재현되는지 테스트를 이용해 확인 해보자.
- 단위 테스트는 모의 객체 도구를 이용해 작성하자.
- 코드 품질 도구를 이용해 커버리지, 스타일, 복잡도를 검증하자
- 테스트가 사용하는 난수생성기에는 시드값을 적용하자
- 테스트에서 사용한 네트워크 소켓과 파일은 반드시 닫자
- 테스트에 고유한 파일 경로와 데이터베이스 ID를 생성하자
- 테스트 실행 사이에 남겨진 상태는 정리하자
**이것만은 피하자**
- 새로운 테스트 도구를 추가하는 데 드는 비용을 무시하지 말자
- 다른 사람이 여러분을 대신해 테스트를 작성해주길 기대하지 말자
- 코드 커버리지를 높일 목적으로 테스트를 작성해서는 안된다.
- 코드 커버리지만으로 품질을 측정하지 말자
- 테스트에서 불필요한 sleep() 메소드와 타임아웃을 사용해서는 안된다.
- 단위 테스트에서 원격 시스템을 호출하지 말자
- 테스트 실행 순서에 의존하지 말자

#### 감상

안그래도 테스트 코드에 대해 궁금했는데 이 기회에 조금 공부했습니다. 나중에 테스트 코드를 더 공부해보고 다시 복습해볼만한 챕터인 것 같습니다.

#### 논의사항

게임에서 테스트 코드를 작성한다면 보통 어떤 걸 중점으로 두나요?
테스트 코드를 작성한 경험과 무엇을 테스트했는지 궁금합니다.



