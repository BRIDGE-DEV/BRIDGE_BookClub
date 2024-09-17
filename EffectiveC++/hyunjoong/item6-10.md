# item 6

구구절절 설명이 많았지만, 사실 c++11에서 = delete가 추가되면서 간단해진 항목입니다. 그러니깐 컴파일러가 자동으로 생성자, 복사 생성자, 복사 연산자를 자동으로 만들어주는데, 이를 방지하려고 private로 선언만 하는 트릭을 여태 썼던 것입니다.

하지만 이제는 HomeForSale(const HomeForSale &) = delete; 한줄이면 무슨 상속 이런 트릭은 신경쓰지 않아도 됩니다. 다만 예전 코드를 읽을 때를 대비해서 이런게 있구나 정도만 간단히 하고 넘어갑시다.

modern effective c++에서도 = delete를 쓰라고 나오는 부분입니다.

요약:
HomeForSale(const HomeForSale &) = delete;
이렇게 쓰자.

# item 7

상속받을 일이 있는 베이스 클래스의 경우에는 잊지 말고 virtual ~foo();를 해 줍시다.

하나 재밌는 점은 c++20부터는 operator delete로 지우면 또 괜찮게 바뀌었다고 하네요: https://en.cppreference.com/w/cpp/language/virtual

이렇게 바뀌어도 혹시 몰라 virtual destructor로 저는 쓸 것 같습니다..

또 하나 짚고 넘어갈 점은, 반대로 상속받을 일이 없으면 virtual을 굳이 쓸 필요가 없다는건데요, vtable과 vptr에 대해서는 또 깊게 파고들면 할 말이 많지만.. 오늘은 넘어갑시다.

> tmi.. 책에서 나온 내용 그대로 virtual call은 객체 자체의 크기도 키울 뿐만 아니라 일반 호출에 비해 포인터를 대략 두 번 정도 더 따라가기 때문에 타이트한 루프에서는 성능이 좋지 않다고 할 수 있겠네요. 그리하여 컴파일러가 비가상화(devirtualization)해서 일반 함수처럼 호출하게 해 둔다던지, 요즘 cpu는 branch prediction이 좋으니 그냥 넘어가도 된다던지 하긴 하지만... 하지만 최대한 사용을 하지 않고 타이트한 루프에서는 안 쓰는게 좋지 않겠습니까. 저의 개인적인 생각입니다.

요약:
상속받을 일이 있는 친구면 가상 소멸자를 쓰자.
아니면 쓰지 말자.

# item 8

소멸자에서 exception이 발생할 때는...

가장 좋은 것은 close()의 예시처럼 애초에 유저가 예외 처리를 하는 것이 좋겠네요.
그리고 소멸자 안에 캐치를 하고 std::abort를 호출하거나 예외를 삼켜버리면 된다로 정리할 수 있겠군요.
좋은 글이었습니다.

>애초에 throw/try/catch의 에러 핸들링보다는.. optional<T>같은게 더 좋은 차세대 에러핸들링 방법이 아닐까 싶습니다.

# item 9

https://www.notion.so/blog-rpopic/416f778ba3ee42b6a6eb04aecb32adeb

전에 블로그에 글까지 쓴 적이 있을 정도네요. 저도 이를 꼭 기억하기 위해서 블로그에 글도 썼습니다. 이에 대해 좀 더 자세히 설명해 뒀으니 궁금하신 분들은 한 번 읽어 보세요. **생성자/소멸자에서 가상 함수를 호출하지 맙시다.**

https://en.cppreference.com/w/cpp/language/virtual

이 글의 During construction and destruction 부분도 한 번 읽어보시길 권합니다.


# item 10

이게 this에 대한 레퍼런스를 반환하면 여러 군데에 편합니다. 특히 std::cout::operator<<도 그 대표적인 예이죠. `std::cout << "Hello " << "World!" << std::endl;`같은 코드가 가능하게 해 줍니다.

c#이랑 또 다른 점이 여기 나오는데요, this가 포인터라는 점입니다. 그리하여 레퍼런스(&)를 반환할 때에는 *this로 포인터를 따라가(dereference)준 다음에 반환해야 합니다. *연산자를 안쓰면 포인터에 대한 레퍼런스가 반환되겠죠.


