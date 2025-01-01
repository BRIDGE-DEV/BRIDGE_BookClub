# 챕터6: 상속, 그리고 객체 지향 설계

## 항목 34: 인터페이스 상속과 구현 상속의 차이를 제대로 파악하고 구별하자

상속이라는 개념은 언뜻 보기에는 그다지 복잡하지 않은 것 같지만, 사실 두 가지로 나뉜다. 하나는 함수 인터페이스의 상속, 하나는 함수 구현의 상속이다.

함수의 인터페이스만을 상속하기 위해서는, 순수 가상 함수를 활용하면 된다. 순수 가상 함수의 특징은 두 가지가 있다. 첫째, 어떤 가상 함수를 물려받은 구체 클래스가 해당 순수 가상 함수를 다시 선언해야 한다. 둘째, 순수 가상 함수는 전형적으로 추상 클래스 안에서 정의를 갖지 않는다.

사실은 순수 가상 함수에도 정의를 제공할 수 있다. 단, 구현이 붙은 순수 가상 함수를 호출하려면 반드시 클래스 이름을 한정자로 붙여 주어야만 한다.

```cpp
Shape *ps1 = new Rectangle;
ps1->Shape::draw(); // 구현이 붙은 순수 가상 함수 호출
```

다음은 단순 가상 함수, 즉 비순수 가상 함수이다. 단순 가상 함수는 파생 클래스로 하여금 함수 인터페이스를 상속하게 한다는 점은 똑같지만, 파생 클래스 쪽에서 오버라이드할 수 있는 함수 구현부도 제공한다는 점이 다르다.

하지만, 단순 가상 함수에서 함수 인터페이스와 기본 구현을 한꺼번에 지정하도록 내버려두는 것은 위험할 수도 있다. 기본 동작을 원한다고 명시적으로 밝히지 않았는데도 그 동작을 물려받는 데 아무런 걸림돌이 없기 때문이다. 이는 기본 구현은 따로 비가상 함수로 만들어놓고, 상속하려는 인터페이스는 순수 가상 함수로 만들면 해결이 가능하다.

마지막은 비가상 함수이다. 멤버 함수가 비가상 함수로 되어 있다는 것은, 이 함수는 파생 클래스에서 다른 행동이 일어날 것으로 가정하지 않았다는 뜻이다. 비가상 함수는 클래스 상속에 상관없는 불변동작과 같다.

멤버 함수를 선언할 때, 클래스 설계를 많이 하지 않은 사람들의 흔한 실수 두 가지를 알아보자.

첫 번째 실수는 모든 멤버 함수를 비가상 함수로 선언하는 것이다. 이렇게 하면 파생 클래스를 만들더라도 기본 클래스의 동작을 특별하게 만들 만한 여지가 없어지게 된다. 특히 비가상 소멸자가 문제가 될 수도 있다. 가상 함수의 비용은 크게 생각하지 말자.

또 한 가지 실수는 모든 멤버 함수를 가상 함수로 선언하는 것이다. 파생 클래스에서 재정의가 안 되어야 하는 함수도 분명 있을 것이다. 이런 함수가 있다면 반드시 비가상 함수로 만들어 둠으로써 입장을 확실히 밝히자.

> 인터페이스 상속은 구현 상속과 다르다. public 상속에서, 파생 클래스는 항상 기본 클래스의 인터페이스를 물려받는다.
순수 가상 함수는 인터페이스 상속만을 허용한다.
단순 가상 함수는 기본 구현의 상속도 가능하도록 지정한다.
비가상 함수는 인터페이스 상속과 더불어 필수 구현의 상속도 가하도록 지정한다.