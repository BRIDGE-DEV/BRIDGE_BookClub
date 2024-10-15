# Item14. 자원 관리 클래스의 복사 동작에 대해 진지하게 고찰하자
힙에 생기지 않는 자원은 auto_ptr 혹은 tr1::shared_ptr 등의 스마트 포인터로 처리해 주기엔 맞지 않다는 것이 일반적인 견해다. 항상 그런 것은 아니지만, 자원 관리 클래스를 스스로 만들어야 할 필요를 느끼는 경우가 바로 이런 경우이다.

```cpp
class Lock {
public:
	explicit Lock(Mutex *pm)
	: mutexPtr(pm)
	{ lock(mutexPtr); }    //자원 획득
	
	~Lock() { unlock(mutexPtr); }    //자원 해제
private:
	Mutex *mutexPtr;
};
```
만약 아래와 같이 Lock 객체가 복사가 된다면?
```cpp
Lock m11(&m);
Lock m12(m11);    //m11을 m12로 복사한다 이게 어떻게 되어야할까?
```
RAII 객체가 복사될 때 어떤 동작이 이루어져야 할까? 아래 4가지 중 하나를 선택
1. 복사를 금지한다.
   복사 연산을 private멤버로 만들어 복사를 방지한다.
2. 관리하고 있는 자원에 대해 참조 카운팅을 수행한다.
   tr1::shared_ptr을 데이터 멤버로 넣으면서 '삭제자(delete)'를 지정하여 참조카운트가 0이 되었을 때 호출되는 함수를 지정한다. 삭제자를 넣는 이유는 tr1::shared_ptr 은 참조자가 0이 될 때 자신이 가리키고 있던 대상을 삭제해 버리도록 기본동작이 되어있기 때문
   ```cpp
   class Lock {
   public:
       explicit Lock(Mutex *pm)
       : mutexPtr(pm, unlock)    //삭제자로 unlock함수를 사용
       {
           lock(mutexPtr.get());
       }
    private:
        std::tr1::shared_ptr<Mutex> mutexPtr;
 };
   ```
3. 관리하고 있는 자원을 진짜로 복사한다.
   깊은 복사를 수행
4. 관리하고 있는 자원의 소유권을 옮긴다.

+ RAII 객체의 복사는 그 객체가 자원의 복사 문제를 안고 가기 때문에, 그 자원을 어떻게 복사하느냐에 따라 RAII 객체의 복사 동작이 결정된다.
+ RAII 클래스에 구현하는 일반적인 복사 동작은 복사를 금지하거나 참조 카운팅을 해주는 선으로 마무리하는 것이다. 하지만 이 외의 방법들도 가능하다.