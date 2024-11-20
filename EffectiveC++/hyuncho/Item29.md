# Item29. 예외 안전성이 확보되는 그날 위해 싸우고 또 싸우자!
```cpp
class PrettyMenu {
public:
	...
	void changeBackground(std::istream& imgSrc);
	...
private:
	Mutex mutex;   //이 객체 하나를 위한 뮤텍스

	Image *bgImage;
	int imageChanges;
};

void PrettyMenu::changeBackground(std::istream& imgSrc)
{
	lock(&mutex);   //뮤텍스를 획득
	delete bgImage;
	++imageChanges;
	bgImage = new Image(imgSrc);

	unlock(&mutex);  //뮤텍스 해제
}
```
예외 안전성의 측면에서 위의 changeBackground 함수보다 나쁠 수는 없다.
이유는 첫 번째로 new Image에서 예외가 발생하면 unlock함수가 실행되지 않아 자원이 샌다.
두 번째로 new Image가 예외를 던지면 새 그림이 깔린게 아닌데 imageChanges의 카운트가 증가하고 이전 bgImage도 삭제되어 버린다.

일반적으로 예외 안전성을 위해서 두가지 요구사항이 필요하다.
1. 자원이 새도록 만들지 않는다.
2. 자료구조가 더렵혀지는 것을 허용하지 않는다.
```cpp
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
	Lock m1(&mutex);   //뮤텍스를 대신 획득하고 이것이 필요 없어질 시점에 바로 해제해 주는 객체

	delete bgImage;
	++imageChanges;
	bgImage = new Image(imgSrc);
}
```
위와 같은 코드로 자원을 새는 것을 막을 수 있긴하지만 아직 자료구조가 더럽혀지긴 한다.

예외 안전성을 갖춘 함수는 아래의 세가지 보장 중 하나를 제공한다.

**기본적인 보장**
함수 동작 중에 예외가 발생하면, 실행 중인 프로그램에 관련된 모든 것들을 유효한 상태로 유지하겠다는 보장이다. 어떤 객체나 자료구조도 더럽혀지지 않으며, 모든 객체의 상태는 내부적으로 일관성을 유지한다. 하지만 프로그램의 상태가 정확히 어떠한지는 예측이 안될 수 있다.

**강력한 보장**
함수 동작 중에 예외가 발생하면 프로그램의 상태를 절대로 변경하지 않겠다는 보장이다. 이런 함수를 호출하는 것은 원자적인(atomic) 동작이라고 할 수 있다. 호출이 성공하면(예외가 발생하지 않으면) 마무리까지 완벽하게 성공하고 호출이 실패하면 함수 호출이 없었던 것처럼 프로그램의 상태가 되돌아간다.

**예외불가 보장**
예외를 절대로 던지지 않겠다는 보장이다. 약속한 동작은 언제나 끝까지 완수하는 함수라는 뜻이다. 기본제공 타입(int, 포인터 등)에 대한 모든 연산은 예외를 던지지 않게 되어 있다(즉, 예외 불가 보장이 제공된다.) 예외에 안전한 코드를 만들기 위한 가장 기본적이며 핵심적인 요소가 아닐까.

예외 안전성을 갖춘 함수는 위의 세 가지 보장 중 하나를 반드시 제공해야 한다. 아무 보장도 제공하지 않으면 예외에 안전한 함수가 아니다. 따라서 '선택'해야 하는 것은 '어떤 보장을 제공할 것인가'이다.

```cpp
class PrettyMenu {
	...
	std::tr1::shared_ptr<Image> bgImage;
	...
};

void PrettyMenu::changeBackground(std::istream& imgSrc)
{
	Lock m1(&mutex);
	bgImage.reset(new Image(imgScr));  //bgImage의 내부 포인터를 'new Image' 표현식의 실행결과로 바꿔치기한다.

	++imageChanges;
}
```
변경점
1. PrettyMenu의 bgImage 데이터 멤버의 타입을 기본 제공 포인터 타입인 Image* 에서 자원관리 전담용 포인터로 바꾼다.
2. changeBackground 함수 내의 문장을 재배치해서 배경그림이 진짜로 바뀌기 전에는 imageChanges를 증가시키지 않도록 만든다.
이제는 이전의 배경그림(Image 객체)을 프로그래머가 직접 삭제할 필요가 없게 되었다. 

이렇게 강력한 예외 안전성 보장을 거의 만족할 수 있게 된 경우이다. (거의라고 한 이유는 imgSrc의 생성자에서 예외를 일으킬 때 그 시점에 입력 스트림의 읽기 표시자가 이동한 채로 남아있을 수 있고 이는 다른 것에 영향을 줄 수도 있기 때문.)

```cpp
struct PMImpl {
	std::tr1::shared_ptr<Image> bgImage;
	int imageChanges;
};

class PrettyMenu {
	...
private:
	Mutex mutex;
	std::tr1::shared_ptr<PMImpl> pImpl;
};

void PrettyMenu::changeBackground(std::istream& imgScr)
{
	using std::swap;
	
	Lock m1(&mutex);

	std::tr1::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));

	pNew->bgImage.reset(new Image(imgSrc));   //사본 수정
	++pNew->imageChanges;

	swap(pImp1, pNew);   //진짜로 배경그림을 바꾸는 부분
}
```
위의 코드는 copy-and-swap 방법으로 어떤 객체를 수정하고 싶으면 그 객체의 사본을 하나 만들어 놓고 그 사본을 수정하는 것이다. 이렇게 하면 수정 동작 중에 실행되는 예외가 던져지더라도 원본 객체는 바뀌지 않은 채로 남는다.


+ 예외 안전성을 갖춘 함수는 실행 중 예외가 발생되더라도 자원을 누출시키지 않으며 자료구조를 더럽힌 채로 내버려 두지 않는다. 이런 함수들이 제공할 수 있는 예외 안전성 보장은 기본적인 보장, 강력한 보장, 예외 금지 보장이 있다.
+ 강력한 예외 안전성 보장은 '복사-후-맞바꾸기' 방법을 써서 구현할 수 있지만, 모든 함수에 대해 강력한 보장이 실용적인 것은 아니다.
+ 어떤 함수가 제공하는 예외 안전성 보장의 강도는, 그 함수가 내부적으로 호출하는 함수들이 제공하는 가장 약한 보장을 넘지 않는다.