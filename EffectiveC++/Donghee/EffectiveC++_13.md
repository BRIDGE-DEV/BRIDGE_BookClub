# 챕터3: 자원 관리

프로그래밍 분야에서 자원(resource)이란, 사용을 일단 마치고 난 후엔 시스템에 돌려주어야 하는 모든 것을 말한다. 메모리는 관리해야 하는 많은 자원 중 하나일 뿐이다. 중요한 것은 “어쨌든 가져와서 다 썼으면 해제해야 한다.”는 사실이다.

이번 장에서는 C++의 생성자, 소멸자, 객체 복사 함수를 사용해 자원 관리를 보여준다. 이 방법을 닿는 대로 써먹으면 어지간한 자원 관리 문제는 박멸할 수 있다.

## 항목13: 자원 관리에는 객체가 그만!

Investment라는 최상위 클래스가 있고, 이것을 기본으로 하여 투자 클래스가 파생되어 있다고 해보자. 또한, Investment에서 파생된 클래스의 객체를 사용자가 얻어내는 용도로 팩토리 함수만 쓰도록 만들어져 있다.

```cpp
class Investment { ... };
Investment* createInvestment(); // Investment 파생 객체를 동적 할당하고 포인터를 반환
```

createInvestment 함수를 통해 얻어낸 객체를 사용할 일이 없을 때, 그 객체를 삭제해야 하는 쪽은 이 함수의 호출자이다. 아래의 함수 f를 보자.

```cpp
void f()
{
	Investment *pInv = createInvestment();
	...
	delete pInv; // 호출자에서 객체 해제 담당
}
```

멀쩡해 보이지만, 우려할 부분이 꽤 있다. ‘…’ 부분 어딘가에 return 문이 들어있을 가능성이 있다. 또한 createInvestment 호출문과 delete가 어느 루프문에 들어가있고, continue 문으로 갑작스럽게 빠져나왔을 수도 있다. 또한 ‘…’ 안의 문장에서 예외를 던질 수도 있다.

이렇게 delete 문을 건너뛸 수 있는 경우는 여러 가지지만, 결과는 하나로 동일하다. 객체를 담고 있는 메모리가 누출되고, 동시에 그 객체가 갖고 있던 자원까지 모두 샌다. f가 항상 delete 문으로 가 줄 거라고 믿지 말자.

결국 자원이 항상 해제되도록 만들 방법은, 자원을 객체에 넣고 그 자원 해제를 소멸자가 맡도록 하며, 소멸자는 실행 제어가 f를 떠날 때 호출되도록 만드는 것이다. 즉 자원을 객체에 넣음으로써, C++가 자동으로 호출해 주는 소멸자에 의해 해당 자원을 저절로 해제할 수 있다.

표준 라이브러리엔 auto_ptr이라고 이런 용도에 쓰라고 마련된 클래스가 있다. auto_ptr은 포인터와 비슷하게 동작하는 **스마트 포인터**로서, 가리키고 있는 대상에 대해 소멸자가 자동으로 delete를 불러주도록 설계되어 있다.

```cpp
void f()
{
	std::auto_ptr<Investment> pInv(createInvestment());
	...
}
```

간단한 예제지만, 두 가지 중요한 특징을 볼 수 있다.

1. 자원을 획득한 후에 자원 관리 객체에게 넘긴다.
    
    위의 예제에서 createInvestment 함수가 만들어 준 자원은 그 자원을 관리할 auto_ptr 객체를 초기화 하는 데 쓰인다. 이런 아이디어는 **자원 획득 즉 초기화(RAII, Resource Acquisition Is Initialization)**라는 이름으로도 통용된다.
    
2. 자원 관리 객체는 자신의 소멸자를 사용해 자원이 확실히 해제되도록 한다.
    
    소멸자는 어떤 객체가 소멸될 때 자동적으로 호출된다. 따라서 실행 제어가 어떤 경위로 블록을 떠나는가에 상관없이 자원 해제가 이루어지는 것이다.
    

auto_ptr은 자신이 소멸될 때 자신이 가리키고 있는 대상에 대해 자동으로 delete를 먹이기 때문에, 어떤 객체를 가리키는 auto_ptr의 개수가 둘 이상이면 절대로 안 된다. 둘 이상이면 자원이 두 번 이상 삭제되는 미정의 동작을 유발하기 때문이다.

따라서 auto_ptr은 이런 상황을 막기 위해, 복사 생성자/복사 대입 연산자를 통해 복사하면 원본 객체는 null로 만드는 특성이 있다.

```cpp
	std::auto_ptr<Investment> pInv1(createInvestment());
	std::auto_ptr<Investment> pInv2(pInv1); 
	// pInv2는 원래 pInv1에 있던 객체를 가리키며, pInv1는 null을 담는다.
	pInv1 = pInv2;
	// pInv1는 다시 원래 객체를 가리키며, pInv2는 null을 담는다.
```

이런 특성 때문에, 모든 관리 객체를 auto_ptr로 쓰는 건 최선이 아니다. 예를 들어, STL 컨테이너의 경우엔 원소들이 정상적인 복사 동작을 가져야 하기 때문에, auto_ptr은 이들의 원소로 허용되지 않는다.

auto_ptr을 쓸 수 없는 상황이라면 대안으로 **참조 카운팅 방식 스마트 포인터(RCSP)**가 괜찮다. RCSP는 어떤 자원을 가리키는 외부 객체의 개수를 유지하다가, 그 개수가 0이 되면 자원을 자동으로 삭제하는 스마트 포인터다.

따라서 RCSP의 동작은 가비지 컬렉션(GC)과 흡사하게 보이기도 한다. 단, 참조 상태가 서로 꼬리를 물고 무는 **순환 참조** 경우에 없앨 수 없다는 점은 가비지 컬렉션과 다르다. GC는 객체 간의 참조 구조를 분석해 해제하지만, RCSP는 서로를 참조할 경우 카운트가 0이 되지 않기 때문이다.

TR1에서 제공하는 tr1::shared_ptr이 대표적인 RCSP이다.

```cpp
void f()
{
	...
	std::tr1::shared_ptr<Investment> pInv1(createInvestment());
	
	std::tr1::shared_ptr<Investment> pInv2(pInv1);
	pInv1 = pInv2;
	...
}
```

이제는 복사 동작이 예상대로 이루어진다. 때문에, tr1::shared_ptr은 auto_ptr이 쓰이지 못하는 STL 컨테이너 등의 환경에 알맞게 쓸 수 있다.

auto_ptr 및 tr1::shared_ptr은 소멸자 내부에서 delete 연산자를 사용한다. **delete[] 연산자가 아니다.** 즉, 동적으로 할당한 배열에 대해 이들을 사용하면 난감하다는 이야기다. 컴파일 에러도 나지 않는다.

C++ 표준 라이브러리에는 동적 할당된 배열을 위해 준비된 auto_ptr 혹은 tr1::shared_ptr 같은 클래스가 제공되지 않는다. 동적으로 할당된 배열을 vector 및 string으로 거의 대체가 가능하기 때문이다. 혹시나 필요하다면, boost::scoped_array와 boost::shared_array를 알아보자.

강조하고 싶은 건 자원 해제를 직접 일일이 하다 보면 언젠가 잘못을 저지르고 만다는 것이다. 이미 널리 쓰이고 있는 auto_ptr이나 tr1::shared_ptr 같은 자원 관리 클래스를 활용하는 것도 이 잘못을 막을 수 있는 방법이다. 다만 이런 클래스로도 제대로 관리할 수 없는 자원도 있다는 사실을 잊지 말자.

### unique_ptr

auto_ptr은 비일반적 복사 동작, 동적 배열에 대한 해제 불가 등의 이유로 C++11부터는 사용 중지 권고, C++17부터는 제거되었다고 한다. 대신 unique_ptr이 등장했다. unique_ptr은 복사는 불가하고 이동 함수(이동 생성자, 이동 대입 연산자)를 통한 이동만 가능해, 명시적으로 사용자에게 작동 방식을 잘 보여준다. 또한 unique_ptr은 배열에 대한 스마트 포인터로도 사용할 수 있다.

```cpp
#include <iostream>
#include <memory>

int main() {
	std::unique_ptr<int> ip(new int(4));
	std::cout << *ip.get() << std::endl; // 4
	
	std::unique_ptr<int> ip2 = std::move(ip); // 소유권 이전
	std::cout << *ip2.get() << std::endl; // 4
	
	//std::unique_ptr<int> ip3 = ip; // 컴파일 에러, 복사 함수 사용 불가.
	//std::cout << *ip.get() << std::endl; // 런타임 에러, ip는 댕글링 포인터를 담고 있다.
	return 0;
}
```

> 생성자 안에서 자원을 획득하고, 소멸자에서 그것을 해제하는 RAII 객체를 사용하자.
널리 쓰이는 RAII 클래스는 tr1::shared_ptr, auto_ptr(현재는 unique_ptr) 이다. 둘중 tr1::shared_ptr이 복사 동작이 직관적이라 대개 더 좋다.