
코드 리뷰에 대한 불안감이나 과도한 자신감에 대해서는 [[Chapter 2 역량을 높이는 의식적 노력]]의 가면 증후군과 더닝 크루거를 참고하자

#### 코드 리뷰는 왜 필요한가

- 미처 알지 못했던 유용한 라이브러리나 코딩 기법을 리뷰어에게 배울 수있다.
- 프로덕션 수준의 코드를 작성하는 법을 배울 수 있다. [[Chapter 4 운영 환경을 고려한 코드 작성]]
- 팀의 코드 스타일을 배울 수 있다.
- 두 명 이상의 프로그래머가 프로덕션 코드를 숙지한다는 것을 의미한다.
	- 코드베이스에 대한 이해를 공유하는 것은 팀이 코드를 응집성 있게 개선하는데 도움을 준다.
	- 정보를 공유하게 된다는 것은 문제가 발생했을 때 책임을 나눠서 질 수 있다는 뜻이다.
- 리뷰의 댓글 기록은 코드가 왜 이와 같은 방식으로 작성됐는지 설명하는 문서 역할을 한다.
- 보안 규정을 준수하는 목적이 되기도 한다.

## 코드 리뷰를 제대로 받는 방법

코드가 변경되는 과정

1. 필요한 코드를 변경하고 제출
2. 제출된 코드에 리뷰 요청 review request 생성
3. 리뷰어로부터 피드백과 논의, 추가적인 변경
4. 변경된 코드가 승인을 받고 코드베이스에 머지

#### 코드 리뷰를 받을 때 준비해야 할 사항

- 개별 코드 변경은 작게 유지
- 기능과 리팩터링 작업은 다른 리뷰로 분리
- 커밋 메시지는 내용이 잘 설명되도록 작성
- 주석과 테스트를 포함시키면 더 좋다.
- 리뷰를 요청한 코드에 연연하지 말자
	- 리뷰를 거치는 동안 얼마든지 변경될 수 있다.
- 제목과 설명을 작성하고 리뷰어를 추가한 뒤 해결하고자 하는 이슈의 링크를 추가하자
- 리뷰 요청의 제목과 설명
	- 변경사항의 테스트 방법
	- 다른 자료에 대한 링크
	- 구현 상세에 대한 도움 요청이나 질문
	- 추가적인 배경 설명

예시)

```
리뷰어 : agupta, csmith, jshu, ui-ux
제목 : [UI-1343] 메뉴 헤더의 누락된 링크 수정
설명 :

# 요약
주 메뉴 헤더의 About Us 메뉴 옵션에 링크가 설정되어 있지 않아 메뉴 버튼을 클릭해도 아무런 동작이 발생하지 않습니다.
이 문제를 해결하기 위해 href 특성에 링크 주소를 지정했고 검증을 위한 셀레늄(Selenium)테스트도 추가했습니다.

# 체크 리스트
이 PR에는 :

- [X] 새로운 테스트의 추가 여부
- [ ] 공개 API의 변경 여부
- [ ] 설계 문서의 포함 여부

```

제목에는 해결할 이슈 [UI-1343]이 존재하며 이렇게 표준 규칙에 의해 이슈를 참조하면 자동으로 이슈 트래커와 코드 리뷰를 연결할 수 있다.
설명란에는 리뷰어에게 제공하기 위한 템플릿이 있다.

#### 리뷰 초안이 있으면 위험을 낮출 수 있다

**변경 초안 draft change** : 테스트 작성, 코드 정리 문서 추가 등에 시간을 할애하지 않고 변경사항을 검토하고 제안하는 방법

리뷰초안을 제출하면 하고 있는 일의 방향이 맞는지 확인할 수 있다.
깃허브에서는 *Draft PR* 이라는 기능을 제공한다. 제출한 코드가 올바른 방향으로 진행되는 것이 확인되면 구현과 테스트, 문서화를 마무리하고 *초안 Draft* 상태를 제거하면 된다.

#### 테스트 실행을 위한 리뷰 제출은 금물이다

**지속적 통합 continuous integration (CI) 시스템** : 자동화된 빌드 및 테스트가 수행된 후, 개발자가 코드 변경 사항을 중앙 리포지토리에 정기적으로 병합하는 [DevOps](https://aws.amazon.com/ko/devops/) 소프트웨어 개발 방식입니다. 지속적 통합은 소프트웨어 릴리스 프로세스 중 빌드 또는 통합 단계를 주로 가리키며, 자동화 구성 요소(예: CI 또는 빌드 서비스)와 문화적 구성 요소(예: 빈번하게 통합하도록 학습) 모두를 포함합니다. 지속적 통합의 핵심 목표는 버그를 신속하게 찾아 해결하고, 소프트웨어 품질을 개선하고, 새로운 소프트웨어 업데이트를 검증 및 릴리스하는 데 걸리는 시간을 단축하는 것입니다. 

테스트를 실행할 목적으로 코드 리뷰를 제출하는 것은 낭비다.
정작 테스트 큐가 가득차서 머지전에 테스트를 해봐야 하는 리뷰를 방해하기도 한다.
*테스트는 로컬에서 실행할 방법을 찾아보자.* 테스트가 실패했을 때는 CI환경보다 로컬에서 디버깅하는 편이 수월하다.

#### 코드 변경사항이 많을 때는 좀 더 면밀하게

**코드 워크스루 code walk through** : 변경한 코드가 많을 때 다른 사람에게 설명하는 시간
즉 개발자가 화면을 공유하고 팀원들을 대상으로 어떤 코드를 왜 변경했는지 회의를 여는 것이다.

- 관련된 설계 문서와 코드는 팀원들에게 미리 배포해 회의 참석 전에 살펴본 후 와달라고 당부해야 한다. (1시간 전에 보내기 X)
- 회의 전에 변경사항에 대한 전후 사정부터 설명하자
- 화면을 공유하고 IDE에서 변경한 코드를 보여주면서 설명을 붙이자
	- 좋은 방법은 시작 지점(페이지의 로드, API 호출 등)부터 시작해서 실행이 완료되는 곳까지의 흐름을 따라가는 것이다.
- 코드 리뷰는 회의 중에 진행하면 안된다. 리뷰는 회의가 끝난 후 댓글로 남겨야 한다.
	- 나중에 팀 전체가 이해할 수 있기 때문

#### 자신의 코드에 너무 집착하지 말자

- 의견을 감정적으로 받아들이지 말자
	- 리뷰는 코드에 대한 의견이지 자신에 대한 의견이 아니다.
- 코드는 나 자신의 코드가 아니라 팀 전체의 코드다.
- 코드에 의견 댓글이 수없이 달리는 상황은 지극히 정상이다.
	- 경험이 적은 초보 개발자라면 더더욱
- 다른 사람의 피드백은 되도록 받아들이고 코드가 바뀔 수 있다는 점을 명심하자

#### 공감력은 갖되 무례함은 참지 말자

- 리뷰어에게 의심할 수 있는 자유는 허락하되, 글이 요점을 벗어나거나 무례한 경우에는 알려주자
- 요점을 벗어나면 얼굴을 맞대고 얘기하는 게 좋은 해결법이 될 수 있다.
- 리뷰에 반박하기 전에 자신의 반응을 살펴봐야 한다.
	- 단순히 자신의 코드이기 때문에 본능적으로 보호하려 하는가?
- 동의할 수 없는 리뷰를 어떻게 해야할 지 모르겠다면 팀장에게 물어보자

#### 주도적으로 행동하자

- 수많은 코드리뷰 요청이 쇄도하게 되면서 놓치게 되는 일이 있다. 밀리게 된다면 팀에게 확인해보자
- 신속하게 응대할 수록 빠른 답변을 받을 수 있을 것이다.
- 승인을 받은 즉시 머지하자
## 코드 리뷰 제대로 해주는 방법

요청의 긴급도와 복잡도를 결정하기.
변경이 필요한 이유를 이해하고 질문 준비하기.
피드백 제공과 결론으로 이끌기.

#### 리뷰 요청을 선별하자

리뷰 요청은 선별하는 것부터 시작하자

- 리뷰의 중요도를 구분하자
	- 곧바로 리뷰해야 하는 변경도 있다.
- 변경의 규모와 복잡도 또한 고려할 부분이다.
- 모든 변경사항을 리뷰할 필요는 없다.
	- 배울 수 있고 잘 아는 코드를 수정하는 리뷰 요청에 집중하자

#### 리뷰를 위한 시간을 마련하자

리뷰 시점을 선택하지 않으면 리뷰를 하느라 생산성이 떨어질 수 있다.

일정상에 코드 리뷰를 위한 시간을 마련하자

#### 코드 변경사항을 이해하자

- 다짜고짜 의견남기기 전에 리뷰에 필요한 질문을 충분히 하자.
- 리뷰는 시간을 들여 제대로 변경 목적을 이해할 때 그 가치가 생긴다.

#### 포괄적인 피드백을 제시하자

- 변경의 올바름
- 구현
- 유지보수성
- 적합성
- 보안성
- 스타일 가이드를 위반하는지
- 읽기 어려운 코드가 있는지

변경사항을 접한다면 본인은 어떻게 구현할지 생각해보고 대안을 찾아보자

- 공개 API가 변경 됐다면 호환성이나 롤아웃 일정에 미칠 영향
- 프로그래머가 이 코드를 오용하거나 오해할 소지가 있는지
- 도움이 될 만한 라이브러리와 서비스가 있는지
- 코드의 유지보수성을 위해 필요한 패턴이 있는지
- OWASP 톱 10의 취약점 고려

*의견은 반드시 정중하게 표현*

#### 좋은 점을 인정하자

*좋은 점에 대해서도 의견을 남기자*

- 코드를 읽으면서 새로운 것을 배웠다면 원저자에게 언급하자
- 긍정적으로 격려하는 의견을 남기자
- 좋은 점을 찾을 수 없다면 노력이라도 인정해주자

#### 이슈, 제안, 사소한 흠결은 잘 구분하자

- 스타일에 대한 피드백을 남기는 것을 주저하지 말자
	- 스타일과 관련한 리뷰는 댓글에 사소한 일임을 표시하자
	- 스타일에 관해 같은 문제가 계속 발생한다고 해서 반복적으로 언급하지 말자
		- 린팅 도구가 있는지 살펴보자 이런 문제는 도구가 해결해야할 문제이다.
- 더 나은 방법이 있다면 제안하되, '선택적', '원저자에게 맡김' 등의 접두어를 붙이자
- 수정이 필요한 사항과 제안사항을 명확히 구분하자

#### 대충대충 리뷰는 금물

- 리뷰를 빨리 승인해야 한다는 유혹에 넘어가지 말자
	- 대충한 리뷰는 팀원들이 변경이 필요한 이유나 변경사항에 대해 잘 안다고 생각할 것이다.
- 리뷰의 적절한 우선순위를 정할 수 없다면 리뷰하지 말자
- 코드 리뷰의 규모가 크면 작게 나눠달라고 부탁하자

#### 웹기반 리뷰 도구에만 의존하지는 말자

리뷰를 보통 깃허브의 PR 인터페이스로 처리할텐데

- 실제로 다운로드해서 로컬에 실행해볼 수 있다.
- IDE를  통해 변경사항을 살필 수 있다.
- 직접 테스트를 해보고 동작을 확인해 볼 수 있다.
- 실행중인 코드에 디버거를 붙여볼 수도 있다.

#### 테스트 리뷰도 잊지 말자

- 테스트 코드를 먼저 읽고 리뷰를 해보는 것도 유용할 때가 있다.
- 테스트 코드는 이런 점을 체크해보자
	- 실행순서에 의존하는가
	- 테스트가 제대로 격리되었는가
	- 원격 시스템 호출하는가
	- 잘못된 패턴을 따르지는 않는가

#### 어떻게든 결론을 맺어야 한다.

*개선사항은 너무 오래 끌지 말자*

- 지나치게 완벽을 추구하지 말자
- 변경의 범위를 확장하지 말자
- 어떠한 의견이 중요한지 명확히 묘사하자

코드를 읽다보면 새로운 기능을 추가하려는 아이디어가 떠오를 때가 있다.
이런 변경은 기존 리뷰에 추가해달라고 요청하지 말자 - 티켓을 생성해라

댓글이 너무 많이 달리면 리뷰 요약을 제공하는 것도 방법이다. 변경을 요청한다면 어떤 부분을 개선해야 하는지 명확히 하자.

---

**이것만은 지키자**
- 코드 리뷰를 요청하기 전에 테스트와 린터의 성공 여부를 확인하자
- 코드 리뷰를 위한 시간을 마련하고 다른 업무와 마찬가지로 우선순위를 파악하자
- 리뷰 의견이 무례하거나 비판적이거나 적절하지 않으면 이의를 제기하자
- 리뷰어에게 변경사항에 대한 적절한 맥락을 제시하자
- 리뷰를 진행할 때는 사소한 스타일 이슈보다는 더 중요한 부분을 살피자
- 코드 리뷰 UI는 물론 다른 모든 도구를 활용해 변경을 검토하자
- 테스트도 리뷰하자

**이것만은 피하자**
- CI 시스템을 실행하기 위해 코드 리뷰를 요청해서는 안된다.
- 코드 리뷰를 대충 하지 말자
- 본인의 코드에 너무 연연하거나 피드백을 감정적으로 대하지 말자
- 변경에 대한 필요를 이해하기 전에 코드부터 리뷰해서는 안 된다.
- 너무 사소한 부분만 지적하지는 말자.
- 너무 완벽하려고 애쓰지는 말자

#### 감상

코드 리뷰를 해야겠다고 생각을 하고 있었는데 좋은 지침이 될 것 같다.

#### 논의 사항

여러 분들이 코드리뷰 했던 기록들을 같이 구경하면 도움이 될 듯 합니다.
부끄럽게도 저는 아직 코드 리뷰를 해본 적이 없습니다...




