## 10장 견고한 소프트웨어를 위한 기술 설계 절차

> 대규모 변경에 적합한 소프트웨어 설계와 문서화 기법

대부분 초급 엔지니어는 생각을 짧게 하고 바로 코딩이 가능한 업무가 주어지기에 어렵지 않게 업무를 진행할 수 있지만, 결국 큰 업무를 맡게 될 것이고 그런 상황에선 견고한 기술 설계를 고민해야 한다.

### 고깔형의 기술 설계 절차

**소프트웨어의 설계란 조사와 브레인스토밍을 거쳐 문서화하고 승인을 받는 선형적인 과정이 아니다. 오히려 단독 업무와 팀 협업 사이를 전환하면서 모든 단계마다 설계를 명확히 하고 재정의하는 나선형 업무에 가깝다.**

설계 문서는 과정을 반복할 때마다 더 명확해지고 상세해진다. 실험, 개념 증명, 벤치마크 등 설계 외 업무를 수행하면서 해결책에 대한 문서 작성자의 확신도 커진다. 설계에 참여하는 인원 수와 다양성도 시간이 지날수록 증가한다.

처음에는 고깔의 바닥에서 시작한다. 문제의 범위와 요구사항, 가능한 해결책 등이 불명확한 상태다. **그래서 절차를 처음 시작할 때는 확실한 해결책 마련이 불가능하다.**

결국 이 과정의 목표는 확실성과 명확성을 높이기 위해 문제에 대해 알아가는 것이다. *계속해서 문서를 수정하고 토론하고 확장해 나가는 과정에서 점점 넓어지고 이 과정의 반복이다. 중요한 점은 시작을 해야하며, 수정에 대해 열려 있어야 한다는 점이다.*

### 올바른 기술 설계를 하려면

소프트웨어 설계는 탐구에서 출발한다. 설계를 시작하기 전에 문제 영역과 요구사항을 반드시 이해해야 한다. 탐구 과정에는 고민과 조사, 실험, 논의 등이 필요하다.

#### 문제를 정의하자

가장 먼저 할 일은 해결하고자 하는 문제를 정의하고 이해하는 것이다. 올바른 해결 방법을 찾기 위해 문제의 경계부터 이해해야 한다. 어쩌면 문제가 없거나 해결할 필요조차 없다는 점을 알아낼지도 모른다.

*이 과정에서 문제에 대한 이해는 이해하려고 하는 자가 문제 자체를 명확하게 인지하는 단계에서부터 출발한다. 정의하는 과정에선 너무 큰 덩어리보다 작은 단위로 쪼개서 이해하는 것이 많이 도움되는 듯 하다.*

> "이 문제를 해결하지 않으면 어떻게 될까?"

위와 같은 질문을 해보고 실제로 이 문제가 해결할 가치가 있는지 생각해보자. *문제 자체를 이성적으로 바라보고 이해하는 것이 중요하다.*

#### 해결 방법을 조사하자

문제를 정의했다고 해서 곧바로 '최종' 설계를 마련하라고 서두르지는 말자. 관련 내용에 대한 조사, 다른 해결책, 트레이드 오프 등을 고려해야 한다. **스스로 생각해낸 설계는 최초의 방안이 아니라 최선의 방안이어야 한다.**

#### 다양한 실험을 해보자

일단 아이디어가 떠올랐으면 대략적으로 코드를 작성하고 테스트를 실행해서 실햄해보자. API 명세를 작성하고 부분적으로 구현해본다. 해당 문제에 대한 자신감이 붙기 시작한다면 설계상의 트레이드 오프가 보이기 시작하고 좀 더 명확한 정의가 떠오르기도 한다.

#### 충분한 시간을 투자하자

좋은 설계에는 창의력이 많이 필요하다. 앉은 자리에서 한 번에 설계를 끝낼 수 있다고 기대해서는 안 된다. 자신에게 충분한 시간을 주고, 휴식도 취하며, 시각으로 바꿀 수 있는 환경도 만들어보고, 인내심을 갖자.

*개인적으로 가장 좋아하는 시간이다. 설계에 창의력을 발휘하고 좀 더 좋은 구조를 고민해볼 수 있는 기회가 많았으면 좋겠다. 개인적으로 샤워할 때 가장 많이 떠오른다.*

### 의사소통을 위한 설계 문서 작성 방안

설계 문서는 아이디어를 명확하게 소통할 수 있는 확장 가능한 방법이다. 문서를 작성하는 과정에서 생각을 정리할 수 있고 약점도 드러날 수 있다. 아이디어를 문서화하는 작업이 항상 수월하지만은 않다. 유용한 설계 문서를 작성하려면 가장 중대한 변경사항에 집중하고 목표와 대상을 유념하면서 글쓰기를 연습하고 문서를 계속 업데이트해야 한다.

*개인적으로 문서에 해당 구조에 대한 약점도 같이 기재하는 것이 좋지 않을까? 라는 생각이 든다. 모든 구조에는 약점이 있을텐데 관련된 내용도 같이 적어놔야 실질적 도움이 될 것 같다.*

#### 중요한 변경사항은 문서화해두자

모든 변경사항에 대해 설계 문서를 작성할 필요는 없으며 공식적으로 설계 리뷰 절차가 필요한 경우도 드물다. 각 조직에 맞는 컨벤션을 따라가는 것이 좋다.

#### 설계 문서를 작성하는 이유를 이해하자

표면적으로 설계 문서는 소프트웨어 컴포넌트의 동작 방식을 설명하는 것 정도로만 보인다. 하지만 설계 문서의 기능은 단순한 문서 이상이다. 설계 문서는 생각할 수 있게 하며, 피드백을 받을 수 있게 하며, 팀원과 소통할 수 있게 한다. *도구의 역할, 테스트코드도 하나의 문서다.*

또한, 문서화는 모르는 것을 드러내기 좋은 방법이기도 하고, 사고방식의 형상화이다. 이를 통해 다른 협업자에게 피드백을 좀 더 쉽게 요청할 수 있으며 다른 사람도 이 문서를 보고 같은 멘탈 모델을 공유할 수 있다.

#### 글쓰는 법을 배우자

글쓰기 스킬 역시 다른 스킬과 마찬가지로 개선할 수 있는 영역이고 개발자에게 필요한 영역이다. 자신의 생각을 명확하게 글로 전달하고 기록하는 것은 소프트웨어 개발과정에서 당연하게 필요하다. **스스로 작성한 글을 본인이 아닌 독자의 관점으로 읽어보자.** 남이 쓴 글을 읽어보면 어떤 부분을 놓치고 있는지 명확하게 알 수 있다.

#### 설계 문서는 최신 상태로 유지하자

실제 구현이 시작되면서 설계 문서는 단순한 제안서에서 소프트웨어 구현 방법을 **서술**하는 문서로 바뀐다. 이는 살아있는 문서로서 팀원들이 모두 같은 멘탈 모델을 공유할 수 있게 한다. 다만 제안서를 문서로 전환하는 과정에서 보편적으로 범하는 실수는 크게 두 가지를 들 수 있다.

첫 번째로 제안 문서를 더 이상 업데이트하지 않고 내버려두는 것이다. 구현 방식은 여러 가지일 수 있으므로 업데이트하지 않은 문서는 나중에 사용자에게 잘못된 정보를 제공하게 된다. 두 번째 실수는 문서가 업데이트되면서 제안 단계에서 기록된 이력을 잃어버리는 것이다. 그러면 나중에 합류하는 개발자는 그 설계 결정에 이르게된 논의 과정을 전혀 알 수 없으며 과거의 실수를 반복할 사능성이 커질 수 있다.

업무를 진행하는 중에는 문서를 계속 업데이트하자. 설계 제안과 설계 문서를 둘로 나눈 경우라면, 구현된 제안 내용에 따라 각 문서를 계속해서 업데이트 해야 할 것이다. 위 내용을 쉽게 다룰려면 설계 문서도 결국 버전 관리가 되어야 함을 의미한다.

### 설계 문서 탬플릿의 기본 구조

**설계 문서는 현재의 코드 설계, 변경 이유, 고려해 볼 수 있는 여러 해결책과 그중에서 채택하고자 하는 해결책 등을 서술해야 한다.** 특히 채택하고자 하는 해결책에는 아키텍처 다이어그램, 주요 알고리즘, 공개 API, 스키마, 대안과의 트레이드오프, 가설, 의존성 등 상세 내용이 무도 담겨야 한다.

> 참고할만한 구조

- 개요
- 현재의 상태와 컨텍스트
- 변경해야 하는 이유
- 요구사항
- 고려할 수 있는 해결책
- 채택하려는 해결책
- 설계와 아키텍처
  - 시스템 다이어그램
  - UI/UX 변경
  - 코드 변경
  - API 변경
  - 영속 계층 변경
- 테스트 계획
- 롤아웃 계획
- 미결 사항
- 부록

### 설계 과정에서도 협업은 중요하다

팀과 건설적으로 협업하면 더 나은 설계를 구현할 수 있다. 하지만 항상 쉽지만은 않은 것이 협업이다. 개발자는 완고하다. 개발자의 피드백을 해석하고 압축해서 의미있는 설계에 녹여내는 것은 결코 쉬운 일이 아니다. **팀의 설계 절차를 따르고, 일찍 자주 소통해서 혼선을 줄이며, 설계 논의를 통해 브레인 스토밍을 진행하는 등의 방법으로 협업하면서 설계를 완성하자.**

#### 팀의 설계 리뷰 절차를 이해하자

아키텍트는 설계 리뷰를 통해 앞으로 발생할 거대한 변경사항을 알게 되고, 기술 리드는 피드백을 제공할 기회를 얻게 된다. 확고한 리뷰 정책을 운영하는 조직도 있는 반면 비공식적으로 리뷰를 진행하는 조직도 있다.

*마찬가지로 팀 내의 리뷰나 피드백 절차를 따라가야 한다.*

#### 갑작스런 상황은 만들지 말자

사람들에게 설계를 제안할 때는 정중하게 그리고 점진적으로 시도하자. 정식 설계 문서를 다른 팀이나 기술 리드에게 처음 선보일 때는 실패할 수 있음을 염두에 두자. 사람들마다 각자 시각이나 관심 분야가 다른데다 사전에 미리 언급된 적 없는 설계 문서를 갑자기 들이밀면 서부 반응을 보일 수도 있다.

그보다는 처음 조사를 시작할 시점에 다른 팀과 기술 리드로부터 일찍이 피드백을 받아보자. 그러면 설계도 더 향상될 뿐 아니라, 다른 사람도 지금 하고 있는 일을 인지해 설계에 참여할 수 있다. (협업)

#### 설계를 논의하며 브레인스토밍을 하자

설계에 대한 논의는 문제 영역에 대한 이해, 지식 공유, 트레이드오프에 대한 고민, 더 견고한 설계 등에 도움이 된다. 이와 같은 브레인스토밍 세션은 비공식적이며 화이트 보드를 이용해 자유로운 형태로 대화하는 시간이다.

설계에 대한 논의는 문제에 대해서는 어느 정도 이해하고 있지만 설계 방식은 아직 결정되지 않은 시점에 주로 이뤄진다. 이 기간에서는 대화가 수월하게 진행될 수 있도록 사람을 2~5명정도로 제한하고 최소 2시간 정도로 생각해야 한다. 목적은 자유로운 토론으로 시작해 충분한 정보를 제공함을 목적으로 한다.

이 과정에서 회의 내용을 기록하는 것이 오히려 더 방해가 될 수 있다. 이 때는 돌아가면서 회의록을 작성해야 하며 중간중간 상태를 저장하고, 이미지/키워드 중심으로 요약된 회의록을 남긴다.

#### 설계에 참여하자

스스로 설계뿐만 아니라 팀의 설계 업무에도 참여해야 한다. 마치 코드 리뷰처럼 설계에 참여하는 상황이 편치는 않을 수 있다. 본인보다 설계 경험이 많은 개발자가 설계를 주도한다면 스스로 기여할 것이 하나도 없다고 생각할 수 있지만, 설계 문서를 읽고 브레인스토밍 회의에 참여하는 것이 불필요하게 여겨질 수도 있다.

그래도 참여해야 한다. 팀의 설계를 개선하는데 도움이 될 뿐만 아니라 다른 배움을 얻을 수 있는 기회도 된다. 참여한 이후 궁금한 것은 물어보자.

### 결론

먼 이야기긴 하지만, 다른 장보다는 확실히 재밌게 읽은 것 같습니다. 설계에 관심이 많고 궁극적으로 하고 싶은 일이라 현업에서는 어떤 방식으로 진행하는지 궁금했는데, 결론은 팀의 방식에 맞춰서 참여하라 인 것 같습니다.

#### 논의사항

- 진행하는 프로젝트에서 설계는 어떤 방식으로 진행하시나요?