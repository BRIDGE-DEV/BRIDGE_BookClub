# 5장 형식 맞추기

## 느낀점
형식 맞추기는 가장 쉬워보이면서도 가장 어려운 습관이다. 자칫 잘못하면 나쁜 코드가 될 가능성이 있는 나쁜 습관으로의 유혹으로 잘 빠져들 수 있기 때문이다. 처음부터 나의 코드 습관 규칙을 엄격하게 세워놓고, 이를 계속 따라야 좋은 형식의 코드를 짤 수 있는 습관이 생긴다는 것을 이해했다. 사실 코드를 급하게 짜다보면 이런 형식 맞추기를 지키지 못한 채 코드만 짜기 급급할 수 있다. 결국 이러한 습관은 2주뒤에 이 코드를 다시 보았을 때, 누구세요? 하는 경험을 할 수 있다고 생각한다. 규칙은 미래의 내가 해당 코드를 이해할 수 있는 초석이라고 생각한다.

## 논의사항
책에서는 팀 규칙을 정할 때 구현 스타일을 10분정도 논의하여 정했다고 하는데, 실제로도 이렇게 빠르게 정해지나요..? 코드 스타일이 서로 다르다면  더 오래 걸릴 것 같기도 한데.. 혹시 팀 규칙을 처음 정할 때 어떻게 정하시는 지 궁금합니다!

## 내용 요약
오랜 시간이 지나 원래 코드의 흔적을 더 이상 찾아보기 어려울 정도로 코드가 바뀌어도 맨 처음 잡아놓은 구현 스타일과 가독성 수준은 유지보수 용이성과 확장성에 계속 영향을 미친다.

**적절한 행 길이를 유지하라.**

**신문 기사처럼 작성하라.**

소스코드를 이름은 간단하면서도 설명이 가능하게 짓는다. 이름만 보고도 올바른 모듈을 살펴보고 있는지 아닌지를 판단할 정도로 신경 써서 짓는다. 소스 첫 부분은 고차원 개념과 알고리즘을 설명한다. 아래로 내려갈수록 의도를 세세히 묘사한다. 마지막에는 가장 저차원 함수와 세부 내역이 나온다.

**개념은 빈 행으로 분리하라.**

빈 행을 추가함으로써 코드 가독성을 높일 수 있다. 줄 바꿈은 개념을 분리한다.

**세로 밀집도**

서로 밀접한 코드행은 세로로 가까이 놓여야 한다. 그래야 코드가 한눈에 들어온다. 

**수직 거리**

서로 밀접한 개념은 세로로 가까이 둬야 한다. 같은 파일에 속할 정도로 밀접한 두 개념은 세로 거리로 연관성을 표현한다. 연관성은 한 개념을 이해하는 데 다른 개념이 중요한 정도다. 연관성이 깊은 두 개념이 멀리 덜어져 있으면 코드를 읽는 사람이 소스 파일과 클래스를 여기저기 뒤지게 된다. 

1. 변수선언 : 변수는 사용하는 위치에 최대한 가까이 선언한다. 루프를 제어하는 변수는 루프문 내부에 선언한다. 

2. 인스턴스변수 : 인스턴스 변수는 클래스 맨 처음에 선언한다. 변수간에 세로로 거리를 두지 않는다. 

3. 종속 함수 : 한 함수가 다른 함수를 호출한다면, 두 함수는 세로로 가까이 배치한다. 또한 가능하다면 호출하는 함수를 호출되는 함수보다 먼저 배치한다. 이러면 모듈 전체의 가독성도 높아진다.

4. 개념적 유사성 : 친화도가 높을수록 코드를 가까이 배치한다. 
    - 한 함수가 다른 함수를 호출해 생기는 직접적인 종속성
    - 변수와 그 변수를 사용하는 함수
    - 비슷한 동작을 수행하는 함수

**세로 순서**

호출되는 함수를 호출하는 함수보다 나중에 배치한다.

**가로 형식 맞추기**

120자 정도로 행 길이를 제한하자.

**가로 공백과 밀집도**

가로로는 공백을 사용해 밀접한 개념과 느슨한 개념을 표현한다.  할당 연산자를 강조하기 위해 앞뒤에 공백을 준다. 함수 이름과 이어지는 괄호 사이에는 공백을 넣지 않는다.

**가로 정렬**

코드가 엉뚱한 부분을 강조해 진짜 의도가 가려질 수 있다. 

**들여쓰기**

범위로 이루어진 계층을 표현하기 위해 코드를 들여쓴다. 들여쓰는 정도는 계층에서 코드가 자리잡은 수준에 비례한다. 왼쪽으로 코드를 맞춰 코드가 속하는 범위를 시각적으로 표현한다. 들여쓰기한 파일은 구조가 한눈에 들어온다. 

**들여쓰기 무시하기**

간단한 if문, 짧은 while 문, 짧은 함수는 들여쓰기를 하지 않고 싶을 때가 있지만 무조건 들여쓰기를 해야한다.

**팀규칙**

프로그래머라면 각자 선호하는 규칙이 있으나, 팀에 속한다면 자신이 선호해야 할 규칙은 팀 규칙이 된다. 팀은 한 가지 규칙에 합의해야 하며, 모든 팀원은 그 규칙을 따라야 한다. 좋은 소프트웨어 시스템은 읽기 쉬운 문서로 이루어진다는 사실을 기억한다. 스타일은 일관적이고 매끄러워야 한다. 한 소스 파일에서 봤던 형식이 다른 소스파일에도 쓰이리라는 신뢰감을 줘야 한다.