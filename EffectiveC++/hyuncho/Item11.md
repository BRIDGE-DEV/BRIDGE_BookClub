# Item11. operator=에서는 자기대입에 대한 처리가 빠지지 않도록 하자
### 자기대입이란?
어떤 객체가 자기 자신에 대해 대입 연산자를 적용하는 것
```cpp
class Widget { ... };

Widget w;
...

w = w;    //자기에 대한 대입
```
### 중복 참조란?
여러 곳에서 하나의 객체를 참조하는 상태
+ 같은 타입으로 만들어진 객체 여러 개를 참조자 혹은 포인터로 물어 놓고 동작하는 코드를 작성할 때는 같은 객체가 사용될 가능성을 고려해야한다.
```cpp
class Bitmap { ... };
class Widget {
	...
	
private:
	Bitmap *pb;    //힙에 할당된 객체를 가리키는 포인터
};

Widget& Widget::operator=(const Widget& rhs)    //안전하지 않게 구현된 operator=
{
	delete pb;
	pb = new Bitmap(*rhs.pb);    //만약 rhs와 *this가 같은 객체일 경우 문제가 발생 -> pb삭제하는 것이 결국 *rhs.pb를 삭제하는 것과 같다.

	return *this;
}

//위의 operator= 를 개선한 방법 -> 일치성검사를 통해 자기대입을 점검
Widget& Widget::operator=(const Widget& rhs)
{
	if (this == &rhs) return *this;    //객체가 같은지, 즉 자기 대입인지 검사

	delete pb;
	pb = new Bitmap(*rhs.pb);

	return *this;
}

//위의 operator= 의 문제점 -> new Bitmap 부분에서 예외가 발생하면 pb가 삭제된 Bitmap을 가리키게 되는 문제 발생 -> 개선 방법은 예외에 안전하게 구현하고(Bitmap 생성자에서 예외처리) 원래의 pb를 어딘가 기억해두기 -> 일치성검사가 없어도 자기대입을 완벽히 처리함
Widget& Widget::operator=(cosnt Widget& rhs)
{
	Bitmap *pOrig = pb;
	pb = new Bitmap(*rhs.pb);
	delete pOrig;

	return *this;
}

//예외 안전성과 자기대입 안전성을 동시에 가진 operator=을 구현하는 다른 방법으로 '복사 후 맞바꾸기' 기법
Widget& Widget::operator=(const Widget& rhs)
{
	Widget temp(rhs);
	swap(temp);
	
	return *this;
}

//위의 operator=를 인자를 값으로 취하여 사본을 취하는 방법
Widget& Widget::operator=(Widget rhs)
{
	swap(rhs);

	return *this;
}
```
+ operator=을 구현할 때, 어떤 객체가 그 자신에 대입되는 경우를 제대로 처리하도록 만들자. 
  1. 원본 객체와 복사대상 객체의 주소를 비교
  2. 문장의 순서를 적절히 조정
  3. 복사 후 맞바꾸기 기법
+ 두 개 이상의 객체에 대해 동작하는 함수가 있다면, 이 함수에 넘겨지는 객체들이 사실 같은 객체인 경우에 정확하게 동작하는지 확인해 보자.
### 궁금증
왜 처리 흐름에 분기를 만들게 되면 실행 시간 속력이 덜컥덜컥 줄어드나요?
-> 파이프라이닝과 관련이 있는데 분기가 생기게 되면 cpu가 다음 명령어를 예측할 수가 없기 때문?