3.
넥스트라는 회사가 있었다는 건 알고 있었지만, 실제  제품들은 처음 봐서 흥미로웠다. (넥스트스테이션은 c64만큼이나 소장욕을 불러일으킨다!)

4.
회사 분위기가 참 재미있고 창의적이며 틀에 박히지 않고 신선한 것 같다. 그들의 전설적인 실력은 말 할것도 없다. 정말 성공을 할 수밖에 없는 조건이 아닌가 생각도 든다. 문을 부수고 그 사이에서 찍은 사진을 보면 참 재미있다. 도끼로 문을 부순 썰을 보면 역시 카멕과 로메로는 참 비범한 사람들이다...는 생각이 들었다.

최근에 디아블로 2 같은 시점의 게임을 구상하면서 어떻게 해야 캐릭터들이 뛰고 공격하는 장면 등등을 다 게임 애셋으로 만들 수 있을까 했는데, 점토를 만들거나 실물을 사진을 찍어서 게임에 넣은 것이었다니 꽤나 창의적인 생각이라고 생각이 들었다. (디아블로2는 3d 모델링을 만들고 캡쳐했다고 한다. 우리 게임은 일일히 다 그리고 있는데, 이게 어느 세월에 완성될지 모르겠다.)

배경도 마찬가지로 원래 있는 사진을 잘 가공해서 아트 리소스를 참 효율적, 효과적으로 만들어 냈다는 생각이 들었다.

지도의 경우에 어떻게 하면 맵을 직렬화해서 저장할 수 있을지에 대한 좋은 인사이트를 얻은 것 같다. 마치 그래픽스 할 때처럼 버텍스들을 지정하고, 그 사이를 줄로 이었다. 또한 이렇게 섹터를 만들어 높낮이도 주었다. 분명 참고할 만한 방식이라고 생각한다.

뒤에 DoomEd에도 월드맵을 위한 일러스트레이터라고 써 놓은거 보면 참 위트도 좋다. 경고창의 메세지도 매우 둠 스럽고 위트있다. 켜면 나오는 임프 소리와 함께 저 임프 초상화가 경고 메세지로 말하는 듯 하다. 놀듯이 즐겁게 일하지 않았을까 싶다.

톰의 컴퓨터 위에 붙여진 "quality"라는 단어. 모니터에 이 단어를 써 붙여 뒀다니, 왠지 듬직하고 멋진 프로그래머라는 생각이 들었다. 항상 버그 없는 소프트웨어를 지속 가능하게 만들겠다는 생각은 했지만 품질을 중요시 하겠다는 말과는 좀 다르게 멋지게 느껴졌다. 품질이라 하면 외부에서 다른 사람들이 게임을 플레이 했을 때도 문제 없이 부드럽게 잘 돌아감은 물론이오 만들어 낸 코드도 잘 정리된 품질 높을 코드가 있을 것 같다는 생각이 들었다. 반면 버그 없는 소프트웨어는 고장은 잘 나지 않아도 왠지 때깔은 보장 못한다는 느낌의 차이가 있는 것 같다. (여기서의 때깔은 코드의 사소한 포매팅, 사소한 ui의 정렬 등을 미묘한 차이들에서 일어나는 것을 생각했다.) 나도 역시 품질이라는 단어를 한번 생각해 보고 마음에 새기는 계기가 되었다.

| 회사에 들어가서 일을 하거나 프로젝트를 하다 보면 시간에 쫒겨 품질이 낮은 코드를 생산하게 된 경험이 있을 것 같습니다. 이렇게 하면서 쌓여가는 기술적 부채와 그로 인한 스트레스도 꽤 많이 받아봤을 것 같은데요. 다른 분들의 경험과 이러한 일이 일어나지 않도록 하려면 어떻게 하면 좋을지에 대한 이야기들이 궁금합니다. 혹은 기술 부채때문에 열받은 이야기도 좋습니다.

DoomED -> DWD -> WAD 순으로 지도가 작성된다.
이 안에 있는 자료구조는 개론적으로 그냥 훝고만 지나가서 솔직히 제대로 어떤 원리로 돌아가는지 모르겠다. bsp node tree인지 뭔지가 어떻게 생성되는지는 모르겠지만.. 한번 파헤쳐보고 싶긴 하다.

(wad 파일을 보니 든 생각인데, 전에 다른 유튜브 비디오에서 본 내용이 생각났다. 우리라면 string을 이용해서 asset을 찾을 때 대부분 hashmap을 떠올리겠지만, -doom이었나 quake였는지 기억은 안나지만- 그냥 linear search를 했다는 점이었다. 그게 더 성능상 빨랐기 때문이라고 하는데, 지난 시간에도 얘기했지만 메모리 time/space locality가 이렇게 중요하고 유리하다고 생각한 자료구조가 무조건 빠르지 않다는 것을 느꼈다.)

지금 맥에 있는 TextEdit.app이 저떄는 저렇게 생겼었다니..싶다. 메뉴도 왼쪽에 있고 스크롤바도 왼쪽에 있는게 지금 보니 참 신기하다. 지금은 코드를 위한 기능은 특별히 없는 것 같다...

사실 지금은 저 Interface Builder처럼 만드는게 당연하게 여겨지지만, 저 당시에는 꽤나 신박한 것이었다니...

OOP에 대한 찬양과 Object-C에 대한 좋은 이야기가 있었다. 개인적으로는 Object-C를 욕하는 말밖에 들어보지 못해서 한번 어떻게 생긴 언어인지 궁금해서 더 알아보기로 했다.

고도로 최적화된에 대한 각주가 arm64, 즉 aarch64에 대한 블로그 글이다. 해당 es가 2011년에 나온건데 왜 넥스트에 사용된 어셈블리가 최적화됐다는 각주로 채택됐는지 모르겠다. 그러거나 말거나 좋은 블로그 글이었다.

objc_msgSend가 도대체 뭐길래?

---

https://www.mikeash.com/pyblog/friday-qa-2012-11-16-lets-build-objc_msgsend.html
일단 성능상으로 느리다는 것 같다. 그래서 빠르게 하기 위해서 캐싱도 한다.
보니 클래스에 특정 메서드를 호출하게 하는 것 같다. [foo bar]이라고 하면 foo라는 오브젝트의 bar를 호출한다. 그런데 foo.bar()이랑은 뭐가 다른걸까?

---

https://eun-dev.tistory.com/81 obj가 간단히 어떤 언어인지 보여주는 좋은 글인 것 같다.

---

아래 두 줄이 같은 코드라고 한다. 대충 왜 쓰는지 알겠다. syntactic sugar다.
```id obj = objc_msgSend(objc_msgSend([NSObject class], @selector(alloc)), @selector(init));

id obj = [[NSObject alloc] init];
```

https://stackoverflow.com/questions/17263354/why-shouldnt-you-use-objc-msgsend-in-objective-c

---

https://stackoverflow.com/questions/1835619/is-objc-msgsend-the-significant-piece-that-makes-objective-c-object-oriented

여기선 또 c++과는 다르게 무조건 dynamic dispatch에 의해 함수가 호출된다는 것 같은데... 좀 엥 싶다.

---

애플 공식 문서다.

https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ObjectiveC/Chapters/ocObjectsClasses.html#//apple_ref/doc/uid/TP30001163-CH11-SW1

아하... Object-C는 최대한 많은 결정을 컴파일 타임, 링크 타임에서 런타임으로 옮기는 언어라고 한다. 애초에 컨셉이 이렇다고 하니 이해가 된다. 또한 dynamically-typed 라고 한다. 어찌 보면 python과도 좀 비슷한 구석이 있다고 볼 수 있겠다.

또한 책에서 나온 null pointer 역참조(dereferencing)에 대한 내용도 나온다. 그냥 아무것도 안한다고 한다. 리턴 값은 0이 된다고 한다. 하지만 동시에 이게 과연 우아한 처리일까? 그냥 0을 리턴하는 함수랑은 어떻게 구별할 것인가? 실패하지 않기 때문에 오히려 프로그램이 예상치 못하게 흘러가거나 여기가 문제라고 파악하기 힘들 수 있지도 않을까? 하는 생각도 든다.

이러한 dynamic dispatch의 특성 덕분에 상속에 의한 다형성이 자연스럽게 나오게 된다고 한다.

| This feature, referred to as polymorphism, plays a significant role in the design of object-oriented programs. Together with dynamic binding, it permits you to write code that might apply to any number of different kinds of objects, without you having to choose at the time you write the code what kinds of objects they might be. They might even be objects that will be developed later, by other programmers working on other projects. If you write code that sends a display message to an id variable, any object that has a display method is a potential receiver.

내가 보기에는 그냥 내가 [foo bar]라고 쓰면 bar가 도대체 무슨 일을 할지, 어떤 값을 리턴할지 virtual 함수보다도 더 알 수 없다라고 보이는데... 이런 면에서는 좀 프로그래밍하기 머리아플 수도 있지 않을까 생각이 든다. 위 문장에서 나온 것처럼 아직 쓰지 않는 객체의 메서드를 호출하고, 다른 사람이 쓰고 있는 메서드를 호출한다는 장점이 나온다. 과연 이게 장점일까?

그냥 컴파일이 되니까 까먹고 프로그램을 돌렸는데 문제가 생길 수도 있다. 컴파일 에러가 뜨면 아직 구현 안했다고 알려줄 텐데. 다른 사람이 쓰고 있는 메서드의 시그니처가 어떻게 생겼을지 어떻게 예측을 할 수 있을까? 커밋 전에 시그니처는 계속 바뀌고 있을 수 있을 수도 있지 않을까? 만약 이걸 알려준다고 하면 어차피 시그니처가 뭔지 기다려야 하고 또 소통 비용도 있지 않을까?


여기 나온 이상적인 시나리오는 [foo copy]라고 하면, foo가 image일 때는 이미지가 복사되며 텍스트일때는 텍스트가 복사되는 이런 식이라고 한다.

일단 objc는 c++과는 완전 다른 길을 걸어갔구나 싶긴 하다. 솔직히 문법이 c언어랑도 많이 다르고 작동 방식도 꽤 다르다. 하여튼 c같은 언어만 보다가 보니까 참 신기하다. 또 다른 언어도 이렇게 맛보고 싶다.

다 읽고 나니 이런 언어도 있구나 하면서 머리가 확장되는 느낌이다. 또 너무 부정적인 시선에서 바라봤나 싶기도 하다.

또한 rust랑은 완전히 대척점에 있는 언어라는 생각도 든다. rust는 런타임, 링크 타임에 일어날 일을 최대한 컴파일 타임으로 당겨왔는데, objc는 완전 반대라는 점이 흥미롭다.

---

배포 전략은 정말 기가 막힌 것 같다. 지금에야 사용할 수 없는 방법이지만, 진짜 이 회사 사람들 머리가 좋고 사고가 자유로운 것 같다.
