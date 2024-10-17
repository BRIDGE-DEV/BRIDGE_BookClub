# Item17. new로 생성한 객체를 스마트 포인터에 저장하는 코드는 별도의 한 문장으로 만들자
```cpp
int priority();
void processWidget(std::tr1::shared_ptr<Widget> pw, int priority);

//tr1::shared_ptr의 생성자는 explicit으로 선언되어 있기 때문에 암시적 변환이 이루어지지 않음.
//아래와 같은 매개변수를 넣으면 컴파일 오류가 난다.
processWidget(new Widget, priority());

//아래와 같은 경우는 컴파일 가능. 하지만 자원 누출 가능성이 존재함.
//priority호출, "new Widget"을 실행, tr1::shared_ptr 생성자 호출 이 세가지의 순서가 컴파일러의 제작사 마다 다르다.
//만약 1. "new Widget"실행  2. priority 호출  3. tr1::shared_ptr 생성자 호출 순으로 이루어져 있다고 했을 때 2번에서 예외가 난다면 new Widget의 메모리가 누출되게 된다.
processWidget(std::tr1::shared_ptr<Widget>(new Widget), priority());

//이런 문제를 피하기 위해서는 Widget을 생성해서 스마트 포인터에 저장하는 코드를 별도의 문장 하나로 만들고, 그 스마트 포인터를 processWidget에 넘긴다.
std::tr1::shared_ptr<Widget> pw(new Widget);
processWidget (pw, priority());    //이제 자원누출 걱정은 없다.

```


+ new로 생성한 객체를 스마트 포인터로 넣는 코드는 별도의 한 문장으로 만들자. 이것이 안 되어 있으면, 예외가 발생될 때 디버깅하기 힘든 자원 누출이 초래될 수 있다.