# CleanCode_Chapter4

# ****CHAPTER 4 : 주석****

## 내용 정리

---

잘 달린 주석은 그 어떤 정보보다 유용하다. 주석을 잘 달아라. 어디서 많이 봤었던 말이다. 잘 다는 것 = 하나 하나 자세히 다는 것인가? 아니면 요약을 해서 간결하게 다는 것인가. 코드의 어느 부분까지 달아야 적당한 것인지 벌써부터 궁금해진다. ~~뒷 내용에서 설명해주겠지.~~

저자는 주석을 필요악이라고 칭한다. 이해가 간다. 아직까지 주석만 읽고 코드를 완전히 이해한 적은 없다. 주석을 참고하고 코드로 살펴보러 넘어간다. 총, 두 번의 과정이 생긴다. 저자 말대로 코드만 보고 이해할 수 있을 정도로 작성을 하면 베스트일 것 같다.

또, 저자는 주석과 코드를 동시에 관리하는 것에 대한 어려움을 주장한다.
주석을 엄격하게 관리하지 못해서 나오는 치명적인 오류들이 있기 때문이다. 서로 소통을 하기 위해서 만들어진 주석이 업데이트 되는 코드를 따라가지 못해, 함정이 되어버릴 수도 있는 것이다. 바쁘면 주석만 보고 코드를 가져다 쓰는 경험도 많이 있었어서, 공감이 갔다.

주석은 나쁜 코드를 보완하지 못한다.

주석은 나쁜 코드, 모듈을 설명하는 용도로 작성하면 안되는 것 같다. 나같은 경우에도 짠 코드를 보았을 때, 한눈에 이해하기 어렵겠다 할 때만 주석을 달곤하는데 깊이 반성하게 된다.

코드로 의도를 표현하라!

주석으로 달리는 설명을 함수로 만들어 표현해라! 의도가 분명한 함수 네이밍을 지으면 주석이 필요없다.

### 좋은 주석

---

*법적인 주석*

첫머리에 주석으로 들어가는 회사에서 필요로 하는 저작권, 소유권 정보

반드시 첫머리에 계약조건이나 법적인 정보일 필요는 없다. 표준 라이선스나 외부 문서를 참조해도 된다.

```java
// Copyright (C) 2003, 2004, 2005 by Object Mentor, Inc, All rights reserved.
// GNU General Public License 버전 2 이상을 따르는 조건으로 배포한다.
```

*정보를 제공하는 주석*

때로는 기본적인 정보를 주석으로 제공하면 편리하다. 다만 가능하다면 함수 이름에 정보를 담는 편이 더 좋다.

```java
// kk:mm:ss EEE, MMM dd, yyyy 형식이다.
Pattern timeMatcher = Pattern.compile(
"\\d*:\\d*:\\d* \\w*, \\w* \\d*, \\d*");
```

*의도를 설명하는 주석*

구현을 이해하게 도와주는 선을 넘어 결정에 깔린 의도까지 설명한다.

```java
// 스레드를 대량 생성하는 방법으로 어떻게든 경쟁 조건을 만들려 시도한다.
for(int i = 0; i < 2500; i++) {
	WidgetBuilderThread widgetBuilderThread =
		new WidgetBuilderThread(widgetBuilder, text, parten, failFlag);
	Thread thread = new Thread(widgetBuilderThread);
	thread.start();
	}
```

*의미를 명료하게 밝히는 주석*

인수나 반환값 자체를 명확하게 만들면 더 좋겠지만, 인수나 반환값이 표준 라이브러리나 변경하지 못하는 코드에 속해야 하는 경우에 유용하다.

```java
assertTrue(a.compareTo(a) == 0); // a == a
assertTrue(a.compareTo(b) != 0); // a != a
assertTrue(ab.compareTo(ab) == 0); // ab == ab
```

하지만 주석이 올바른지 검증하기는 쉽지않다. 이것이 의미를 명료하게 밝히는 주석이 양날의 검인 이유이다. 그러므로 이 방법을 사용할 때는 더 나은 방법이 없는지 고민 후, 정확히 달도록 각별히 주의한다.

*결과를 경고하는 주석*

다른 프로그래머에게 경고할 목적으로 사용한다.

다음은 특정 테스트 케이스를 꺼야하는 이유를 설명한 주석이다.

```java
public static SimpleDateFormat makeStandardHttpDateFormat()
{
	// SimpleDateFormat은 스레드에 안전하짐 못하다.
	// 따라서 각 인스턴스를 독립적으로 생성해야 한다.
	SimpleDateFormat df = new SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss z");
	df.setTimeZone(TimeZone.getTimeZone("GMT"));
	return df;
}
```

프로그램 효율을 높이기 위해 정적 초기화 함수를 사용하려던 프로그래머가 주석 때문에 실수를 면한다.

*TODO 주석*

‘앞으로 할 일’을 //TODO 주석으로 남겨두면 편하다. 필요하다 여기지만 당장 구현하기 어려운 업무를 기술한다.

더 이상 필요 없는 기능을 삭제하라는 알림, 누군가에게 문제를 봐달라는 요청, 더 좋은 이름을 떠올려달라는 부탁, 앞으로 발생할 이벤트에 맞춰 코드를 고치라는 주의 등에 유용하다.

다음은 함수를 구현하지 않은 이유와 미래 모습을 주석으로 설명한 예제이다.

```java
// TODO-MdM 현재 필요하지 않다.
// 체크아웃 모델을 도입하면 함수가 필요 없다.
protected VersionInfo makeVersion() throws Exception
{
	return null;
}
```

*중요성을 강조하는 주석*

자칫 대수롭지 않다고 여겨질 뭔가의 중요성을 강조하기 위해서도 주석을 사용한다.

```java
String listItemContent = match.group(3).trim();
// 여기서 trim은 정말 중요하다. trim 함수는 문자열에서 시작 공백을 제거한다.
// 문자열에 시작 공백이 있으면 다른 문자열로 인식되기 때문이다.
```

### 나쁜 주석

---

허술한 코드를 지탱, 엉성한 코드를 변명, 미숙한 결정을 합리화 하는 주석들을 말한다.

*주절거리는 주석*

특별한 이유 없이 의무감으로 혹은 프로세스에서 하라고 하니까 마지못해 주석을 단다면 시간 낭비다. 주석을 달기로 결정했다면 충분한 시간을 들여 최고의 주석을 달도록 노력해라.
충분한 정보를 제공하지 못해 읽었는데도 오히려 궁금증을 유발하는 주석들을 말한다.

*같은 이야기를 반복하는 주석*

헤더에 달린 주석이 같은 코드 내용을 그대로 중복한다면 코드보다 주석을 읽는 시간이 더 오래 걸린다. 이와 같은 경우는 주석이 코드보다 더 많은 정보를 제공하지 못한다. 독자가 함수를 대충 이해하고 넘어가게 만든다.

*오해할 여지가 있는 주석*

주석에 담긴 살짝 잘못된 정보로 인해 어느 프로그래머가 경솔하게 함수를 호출할지도 모른다.

*의무적으로 다는 주석*

모든 함수, 변수에 주석을 달아야한다는 규칙은 어리석기 그지없다. 이런 주석은 코드를 복잡하게 만들며, 혼동과 무질서를 초래한다.

*이력을 기록하는 주석*

예전에는 모든 모듈 첫머리에 변경 이력을 기록하고 관리하는 관례가 있었다. 하지만 이제는 소스 코드 관리 시스템이 있으니 완전히 제거하는 편이 좋다.

*있으나 마나 한 주석*

너무 당연한 사실을 언급하며 새로운 정보를 제공하지 못하는 주석이다.

*오타난 주석을 복붙해서 만든 코드*

저자가 주의를 기울이지 않았다면 오류가 발생할 수 있다.

*함수나 변수로 표현할 수 있다면 주석을 달지 마라*

```java
// 전역 목록 <smodule>에 속하는 모듈이 우리가 속한 하위 시스템에 의존하는가?
if (smodule.getDependSubSystems().contains(subSysMod.getSubSystem()))

// 위의 예시 코드 주석 없는 버전으로 수정
ArrayList moduleDependees = smodule.getDependSubsystems();
String ourSubSystem = subSysMod.getSubSystem();
if (moduleDependees.contains(ourSubSystem))
```

*위치를 표현하는 주석*

일반적으로 이와 같은 주식은 가독성만 낮춘다. 아주 드물게 사용하는 편이 좋다.

```jsx
// Actions //////////////////////////
```

*닫는 괄호에 다는 주석*

중첩이 심하고 장황한 함수라면 의미가 있을지도 모르지만 우리가 선호하는 작고 캡슐화된 함수에는 도움이 안된다. 대신 함수를 줄이려고 시도하자.

*공로를 돌리거나 저자를 표시하는 주석*

이제는 필요없다. 소스 코드 관리 시스템을 믿자.

*주석으로 처리한 코드!*

1960년대 즈음에는 주석으로 처리한 코드가 유용했었다. 이제는 소스 코드 관리 시스템이 우리를 대신해 코드를 기억해준다.

*HTML 주석*

HTML 주석은 읽기 쉬워야 하는 주석의 본질을 해친다. 편집기/IDE에서 조차 읽기가 어렵다.

*전역 정보*

주석 바로 아래 함수가 아니라 시스템 어딘가에 있는 다른 함수를 설명하는 주석.

*너무 많은 정보*

TMI…

*모호한 관계*

주석과 주석이 설명하는 코드는 관계가 명백해야한다. 주석을 다는 목적은 코드만으로 설명이 부족해서인데, 주석 자체가 다시 설명을 요구하는 것이면 안된다. 충분한 정보가 담겨있어야 함.

*함수 헤더*

짧고 한 가지만 수행하며 이름 잘 붙인 함수는 헤더 주석이 필요없다.

*비공개 코드에서 Javadocs*

## 느낀 점

---

저자는 허술한 코드를 지탱, 엉성한 코드를 변명, 미숙한 결정을 합리화 하는 주석이 나쁜 주석이라 했습니다. ~~그런 코드를 짜고 있으면서 주석조차 달지 않는 사람이 바로 나.~~

**너무 많은 정보**가 들어갈까봐, 하나를 설명하면 열을 설명해야될까봐 주석을 다는 걸 꺼려했었습니다. 근데 또 짧고 간단하게 쓰자니 **모호한 관계**가 될 것 같고… 뭐든 적당히 하는 것이 어려운 것 같습니다. 

저자가 보여줬던 예제들을 보면은 이해가 가고 필요성을 느끼면서도, 막상 제 것을 보고 주석을 달자니 못하겠는 것은 왜일까요. 남이 봐서 한눈에 이해할 수 있을 정도가 되어야 한다는 부담감 때문일까요... 이번 장의 내용 또한 큰 도움이 됐습니다.

## 논의 내용

---

저자가 말하는 **주절거리는 주석**을 써놓고 나중에 기억이 안나 곤란했던 경험이 있나요?