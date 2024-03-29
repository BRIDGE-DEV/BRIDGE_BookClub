ㅍ 1장 리팩터링 : 첫 번째 예시
=============

프로그램이 새로운 기능을 추가하기에 편한 구조가 아니라면, 먼저 기능을 추가하기 쉬운 형태로 리팩터링하고 나서 원하는 기능을 추가한다.

- **함수 추출하기**
별도 함수로 빼냈을때 유효범위를 벗어나는 변수, 즉 새 함수에서 곧바로 사용할 수 없는 변수가 있는지 확인한다.
값이 바뀌지 않는 변수는 매개변수로 전달, 함수 안에서 값이 바뀌는 변수는 함수 안에서 초기화해서 사용 후 결과 값을 반환 한다. (예제의 경우 값이 바뀌는 변수가 하나라서)
추출된 함수는 변경할 만한 이름이 없는지 확인한다. 반환값이 된 변수를 result로 바꿔주는 등

- **매개변수 제거**
임시 변수들 때문에 로컬 범위에 존재하는 이름이 늘어나서 추출 작업이 복잡해질 수 있어 최대한 제거한다. 임시 변수를 질의 함수로 바꾼다음 변수 인라인을 적용한다. (이렇게 하려면 좋은 이름 설정이 매우 중요해 보인다..)
지역 변수를 제거하면 유효범위를 신경 써야할 대상이 줄어들어 추출 작업이 훨씬 쉬워진다.

- **문장 슬라이드하기**
값 갱신과 관련한 문장을 먼저 한대 모아두면 임시 변수를 질의 함수로 바꾸기와 함수로 추출이 쉬워진다.

- **반복문 쪼개기**
반복문을 쪼개는 과정에서 반복문 중복을 꺼리는 이들이 많지만, 성능에 미치는 영향은 미미할 때가 많다. 설사 성능이 크게 떨어졌더라도 리팩터링된 코드가 성능 개선 작업을 수월하게 해줄 수 있다. 특별한 경우가 아니면 리팩터링을 마무리하고 성능을 개선하자.

### 계산 단계와 포맷팅 단계 분리하기
텍스트 버전과 HTML버전 함수가 똑같은 계산 함수들을 사용하게 만들기 위해 저자는 단계 쪼개기를 사용했다. 표현과 표현에 필요한 값으로 단계를 나누는 것이다. 다시 말해 첫 번째 단계에서는 두 번째 단계로 전달할 중간 데이터 구조를 생성하는 것이다.

이 과정에서 파일이 2개가 되고 코드량도 늘었지만 간결함이 지혜의 정수일지 몰라도,프로그래밍에서만큼은 명료함이 진화할 수 있는 소프트웨어의 정수다.



### 마치며

이번 장에서 리팩터링을 크게 세 단계로 진행했다.
1. 긴 원본 함수를 작은 함수 여러 개로 나누기.
2. 계산 코드와 출력 코드로 단계 쪼개기.
3. 계산 로직을 다형성으로 표현.

> 좋은 코드를 가늠하는 확실한 방법은 '얼마나 수정하기 쉬운가'다.

코드를 수정해야 할 상황이 되면 고쳐야 할 곳을 쉽게 찾을 수 있고 오류 없이 빠르게 수정할 수 있어야 한다. 건강한 코드는 생산성을 극대화하고, 필요한 기능을 더 빠르고 저렴하게 제공하도록 해준다. 팀의 현재와 이상의 차이에 항상 신경 쓰면서, 이상에 가까워지도록 리팩터링해야 한다.

이번 예시를 통해 배울 수 있는 가장 중요한 것은 리팩터링하는 리듬이다. 작은 단계들이 모여서 상당히 큰 변화를 이룰 수 있다는 사실을 깨닫는 것이다.

느낀점
=============
클린코드에서 지저분한 코드와 깨끗한 코드를 비교해 줬다면 이 책에서는 그 개선해 나가는 중간 과정을 절차적으로 보여줘서 좋았다. 또한 1장에서 코드가 변해가는 모습을 보여주니 단순히 글로 읽는 것보다 리팩터링이 어떤 작업인지 직접적으로 느낄 수 있었고 뒤에서 소개될 구체적인 내용도 궁금해진다. 뒤 내용을 읽고 다시 한번 읽어보면 좋을 것 같다.

논의 사항
=============
본인이 생각하는 좋은 코드의 기준이 있는지 궁금합니다!
