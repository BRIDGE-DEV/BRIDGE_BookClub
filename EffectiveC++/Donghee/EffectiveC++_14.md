# 챕터3: 자원 관리

## 항목14: 자원 관리 클래스의 복사 동작에 대해 진지하게 고찰하자

힙에 생기지 않는 자원은 auto_ptr 혹은 tr1::shared_ptr 등의 스마트 포인터로 처리해 주기엔 맞지 않다는 것이 일반적이다. 여기서 말하는 ‘힙에 생기지 않는 자원’은 소켓 같은 커널 리소스, 혹은 그래픽 리소스 등을 의미한다. 커널 영역이나 GPU 메모리 등에 생성되는 자원들은 힙에 관리되는 자원들과는 다르게 처리해야 한다.

예를 하나 들어 보자. Mutex 타입의 객체를 조작하는 C API를 사용하는 중이라고 가정해본다.

```cpp
void lock(Mutex *pm);
void unlock(Mutex *pm);
```

이 뮤텍스의 잠금을 관리하는 클래스를 따로 만들고 싶다. 이럴 때에는 RAII 법칙을 따라 구성한다.

```cpp
class Lock {
public:
	explicit Lock(Mutex *pm) : mutexPtr(pm) { lock(mutexPtr); }
	~Lock() { unlock(mutexPtr); }
	
private:
	Mutex *mutexPtr;
};
```

사용자는 RAII 방식에 맞추어 Lock을 사용하면 된다.

```cpp
Mutex m;
...
{
	Lock m1(&m); // 뮤텍스에 lock을 검
	...
} // 자동으로 Lock 해
```

하지만 여기서 Lock 객체가 복사된다면 어떻게 해야 할까? 이 질문을 더 일반화하면, ‘RAII 객체가 복사될 때 어떤 동작이 이루어져야 할까?’가 된다. 이 질문엔 다음 선택지가 있다.

- 복사를 금지한다.
    - 실제로 RAII 객체가 복사되도록 놔두는 것은 말이 안되는 경우가 많다. 항목 6에 나왔던 것처럼 복사 연산을 private 멤버로 만들자.
- 관리하고 있는 자원에 대해 참조 카운팅을 수행한다.
    - 자원을 사용하고 있는 마지막 객체가 소멸될 때 까지 그 자원을 해제하지 않는 게 바람직할 경우도 있다. tr1::shared_ptr의 경우도 이렇다.
    - 위의 Lock을 참조 카운팅 방식으로 하면, 복사가 잘 이루어질 것이라 예상할 수 있다. 따라서 mutexPtr의 타입을 Mutex*에서 tr1::shared_ptr<Mutex>로 바꾸자는 것이다. 하지만 tr1::shared_ptr은 참조 카운트가 0이 될 때 가리키는 대상을 바로 삭제해버린다. 우리가 하고 싶은 것은 unlock인데 말이다.
    이럴 때를 위해 tr1::shared_ptr은 참조 카운트가 0이 될 때의 행동인 ‘삭제자(deleter)’를 지정할 수 있게 해놨다. 이를 반영한 코드는 아래와 같다.
        
        ```cpp
        class Lock {
        public:
        	explicit Lock(Mutex *pm) : mutexPtr(pm, unlock) { lock(mutexPtr.get()); }
        	
        private:
        	std::tr1::shared_ptr<Mutex> mutexPtr;
        };
        ```
        
- 관리하고 있는 자원을 진짜로 복사한다.
    - 때에 따라서는 자원을 원하는 대로 복사할 수도 있다. 이럴 때는 자원 관리 객체를 복사하면 그 객체가 둘러싸고 있는 자원까지 복사되어야 한다. 즉, ‘깊은 복사’를 수행해야 한다.
- 관리하고 있는 자원의 소유권을 옮긴다.
    - RAII 객체가 복사될 때 그 자원의 소유권을 사본 쪽으로 아예 옮겨야 할 경우도 생긴다. auto_ptr의 복사 동작이 그러하다.

객체 복사 함수는 컴파일러에 의해 생성될 여지가 있기 떄문에, 만약 동작이 마음에 들지 않는다면 직접 만드는 수밖에 없다.

> RAII 객체의 복사는 관리하는 자원의 복사 문제를 안고 가기 때문에, 그 자원을 어떻게 복사하느냐에 따라 복사 동작이 결정 된다.
RAII 클래스에 구현하는 일반적 복사 동작은 복사를 금지하거나 참조 카운팅을 해 주는 선으로 마무리하는 것이다.