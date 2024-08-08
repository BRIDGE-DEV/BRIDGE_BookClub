# 5장 피할 수 없는 코드 의존성의 관리

## 정리

> 복잡한 프로그램을 짜봐야 비로소 깨닫는 의존성의 진실

의존성에는 호환성 없는 변경, 순환 의존성, 버전 충돌, 통제 불가능 등 다양한 위험성이 내포돼 있다. 이번 5장에서는 의존성 관리에 대한 기본 내용을 설명하고 모든 엔지니어에게 악몽과도 같은 의존성 지옥에 대해 알아보고자 한다.

### 의존성 관리를 이해하기 위한 필수 개념

**의존성**이란 여러분의 코드가 의존하는 코드를 말한다.

의존성이 필요한 시점, 즉 컴파일 시점, 테스트, 런타임 등을 **의존성 범위**라고 부른다.

버저닝(versioning) 스키마를 잘 따르는 버전은 다음과 같은 특징을 가진다.

- 고유성: 버전은 재사용되지 않아야 한다.
- 비교성: 버전은 사람과 도구가 버전의 우선권을 이해하는 데 도움이 된다.
- 정보성: 버전은 사전 릴리스한 코드와 정식 릴리스한 코드를 구분하고 산출물에 빌드 번호를 매기며 안정성과 호환성을 설명해준다.

**시맨틱 버저닝**

가장 보편적으로 사용하는 버저닝 스키마 중 시맨틱 버저닝(SemVer)이 있다. 이 명세는 주 버전, 보조 버전, 그리고 패치 버전 등 세 가지 숫자로 버전을 정의한다.

시맨틱 버전은 고유성과 비교성, 정보성을 모두 갖추고 있다. 주 버전이 0인 버전은 ‘사전 릴리스’로서 개발 주기를 빠르게 가져가기 위해 사용하며 호환성은 전혀 보장되지 않는다. 주 버전이 1이 되면 프로젝트는 다음 요건들을 보장해야 한다.

- 패치 보전은 하위 호환성을 갖는 버그 수정이 일어날 때마다 증가한다.
- 보조 버전은 하위 호환성을 갖는 기능을 추가할 때마다 증가한다.
- 주 버전은 하위 호환성을 갖지 못하는 변경을 추가할 때 증가한다.

**이행적 의존성**

패키지 관리나 빌드 파일은 프로젝트의 직접 의존성을 보여주지만 직접 의존성은 빌드나 패키징 시스템이 실제로 사용하는 의존성의 일부에 불과하다.

의존성은 다른 라이브러리에 주로 의존하며, 이를 일컬어 **이행적 의존성**이라고 부른다. 이행적 의존성을 이해하는 것은 의존성 관리에서 중요한 부분이다.

의존성 하나를 추가하는 일은 작은 변경인 듯 하지만, 만일 그 라이브러리가 100개의 의존성을 가지고 있다면 여러분의 코드는 이제 101개의 라이브러리에 의존하게 되는 셈이다.

### 현업이면 누구나 한 번은 겪는 의존성 지옥

의존성 지옥을 일으키는 가장 보편적 주범은 순환 의존성, 다이아몬드 의존성, 버전 충돌이다.

서로 다른 라이브러리가 동일한 라이브러리의 다른 버전을 의존한다면 **다이아몬드 의존성** 형태를 띄게 된다.

더 심각한 경우는 라이브러리가 자기 자신을 이행적 의존성으로 갖게 되는 **순환 의존성**이다.

### 의존성 지옥에서 탈출하자

의존성은 피할 수 없지만 뭐가 됐든 새로운 의존성이 추가될 때마다 비용이 따른다. 의존성의 가치가 그 비용보다 큰지 여러분 스스로 꼭 자문해보기 바란다.

- 이 기능은 정말 필요한가?
- 의존성은 얼마나 잘 관리되고 있는가?
- 뭔가 잘못됐을 때 의존성을 수정하는 것은 얼마나 쉬운가?
- 의존성은 얼마나 성숙해 있는가?
- 나와 우리 팀은 의존성에 대해 얼마나 이해하는가?
- 코드를 직접 작성한다면 구현 난이도는 어느 정도인가?
- 어떤 유형의 라이선스인가?
- 의존성 내에서 내가 사용하는 코드와 사용하지 않는 코드의 비율은?

**의존성을 격리하자**

빌드와 패키지 시스템을 위해 의존성 관리를 그만둘 필요는 없다. 코드를 프로젝트로 복사해넣는 것은 더 높은 격리 수준을 위해 의존성 관리 자동화를 포기하는 것이다.

코드 복사를 권장하지 않는 DRY 철학을 따르는 개발자가 대체로 많다. 하지만 더 큰 의존성 문제나 불안정한 의존성 문제를 피하는데 도움이 된다면 코드를 복사하는 것에 큰 죄의식을 갖진 말자. 물론 이는 버전 기록도 유지할 수 없으며, 업데이트가 필요할 때마다 매번 코드를 다시 복사해야 하는 단점이 존재한다.

**의존성 가리기**도 의존성을 격리하는 방법 중 하나다. 이는 충돌을 피하기 위해 의존성을 다른 네임스페이스로 자동 이전하는 기법을 말한다. 의존성 가리기는 고급 기법으로, 반드시 필요한 경우에만 활용해야 한다.

의존성 가리기의 목적은 의존성의 존재를 숨기는 것으로, 충돌 가능성이 높은 의존성을 광범위하게 사용하는 라이브러리를 만들고 있을 때만 적용하도록 권장한다.

**의존성은 신중하게 추가하자**

사용하는 모든 라이브러리는 명시적으로 의존성으로 선언하자. 이행적 의존성 라이브러리가 제공하는 메소드와 클래스는 혹여 괜찮아 보일지라도 사용하지 말아야 한다.

IDE에만 의존해 의존성을 관리해서는 안 된다. 의존성은 명시적으로 빌드 파일에 추가하자.

**버전을 고정하자**

모든 의존성의 버전 번호를 명시하자. 버전을 고정해두지 않으면 빌드나 패키지 관리 시스템이 버전을 결정하게 된다.

**의존성의 범위를 좁히자**

의존성은 최대한 범위를 좁혀서 사용해야 한다. 모든 의존성을 컴파일 타임 범위에 추가하는 것은 좋은 방법이 아니다. 범위를 좁히면 충돌과 컴파일 바이너리의 크기를 줄일 수 있다.

**순환 의존성에 주의하자**

절대로 순환 의존성이 발생해서는 안 된다. 순환 의존성은 시스템의 오동작과 배포 순서 문제를 유발한다. 빌드 도구를 이용해 여러분 스스로를 보호하자.

### 필수 체크리스트

| O 이것만은 지키자 | X 이것만은 피하자 |
| --- | --- |
| 시맨틱 버저닝을 사용하자 | 깃 해시를 버전 번호로 사용하지 말자 |
| 의존성 버전은 특정 범위로 고정하자 | 비용 대비 효과가 낮다면 의존성을 추가하지 말자 |
| 의존성 보고서를 이용해 이행적 의존성을 파악하자 | 이행적 의존성을 직접 사용해서는 안 된다 |
| 새 의존성 추가는 가급적 피하자 | 순환 의존성을 추가하지 말자 |
| 의존성은 적당한 범위 내에 선언하자 |  |

---

## 느낀 점

최근에 읽었던 책이 오브젝트라 그런지, 5장을 처음 읽을 때는 객체 사이의 의존성을 말하는 줄 알았다.. 물론 이것도 라이브러리 사이의 의존성이니 큰 개념 자체는 바뀌는 것이 없는 것 같다. 라이브러리를 한번에 많이 사용해본 경험은 없는지라, 이것이 얼마나 큰 영향을 끼치는 지는 생각해보지 못했었다. 지금보다 나중에 규모가 거대한 프로젝트에 참여할 때 도움이 될 것 같은 챕터였다.

---

## 논의사항

- 라이브러리를 많이 사용하시나요?

저는 아직 라이브러리를 많이 사용해보진 않아서.. 정확히는 잘 몰라서 안 쓴다는 느낌에 가까운 것 같습니다. 더 알아야 하는게 많네요.. 추천해주고 싶은 라이브러리가 있으시다면 서로 추천해주는 것도 좋을 것 같아요!