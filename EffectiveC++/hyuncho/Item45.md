# Item45. 호환되는 모든 타입을 받아들이는 데는 멤버 함수 템플릿이 직방
스마트 포인터는 그냥 포인터처럼 동작하면서도 포인터가 주지 못하는 기능을 갖고 있기도 하다. list::iterator 와 같은 STL 컨테이너 반복자도 스마트 포인터나 마찬가지 인데 포인터에다가 "++" 연산을 적용이 가능하다.

포인터에도 스마트 포인터로 대신할 수 없는 특징이 있다. 그 중 하나가 암시적 변환을 지원한다는 것이다. 파생 클래스 포인터는 암시적으로 기본 클래스 포인터로 변환되고 비상수 객체에 대한 포인터는 상수 객체에 대한 포인터로의 암시적 변환이 가능하다.

아래 코드들을 보면 세 수준으로 구성된 클래스 계통이 주어지고 몇 가지 타입변환이 가능하다.
```cpp
class top { ... };
class Middle : public Top { ... };
class Bottom : public Middle { ... };
Top *pt1 = new Middle;  //Middle* => Top*의 변환
Top *pt2 = new Bottom;  //Bottom* => Top*의 변환
const Top *pct2 = pt1;  //Top* => const Top*의 변환
```
위와 같은 타입 변환을 사용자 정의 스마트 포인터를 써서 흉내내려면 무척 까다롭다.
```cpp
template<typename T>
class SmartPtr {
public:
	explicit SmartPtr(T *realPtr);  //스마트 포인터는 대개 기본제공 포인터로 초기화된다.
	...
};

SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle);  //SmartPtr<Middle> => SmartPtr<Top>의 변환
SmartPtr<Top> pt2 = SmartPtr<Bottom>(new Bottom);  //SmartPtr<Bottom> => SmartPtr<Top>의 변환
SmartPtr<const Top> pct2 = pt1;  //SmartPtr<Top> => SmartPtr<const Top>의 변환
```
같은 템플릿으로부터 만들어진 다른 인스턴스들 사이에는 어떤 관계도 없기 때문에, 컴파일러의 눈에 비치는 SmartPtr\<Middle> 과 SmartPtr\<Top>은 완전히 별개의 클래스다. 이는 SmartPtr 사이의 변환이 이루어지도록 만들고 싶다면 변환이 되도록 프로그램을 따로 만들어야 한다는 의미이다.

SmartPtr에 생성자 함수를 둘 필요없이 바로 생성자를 만드는 템플릿을 쓰면 된다. 이는 멤버 함수 템플릿의 한 예이다. 멤버 함수 템플릿은 간단히 말해서 어떤 클래스의 멤버 함수를 찍어내는 템플릿을 일컫는다.

```cpp
template<typename T>
class SmartPtr{
public:
	template<typename U>
	SmartPtr(const SmartPtr<U>& other);  //"일반화된 복사생성자"를 만들기 위한 멤버 템플릿
	...
};
```
위 코드는 모든 T 타입 및 모든 U 타입에 대해서 SmartPtr\<T> 객체가 SmartPtr\<U>로 부터 생성될 수 있다는 이야기이다. 그 이유는 SmartPtr\<U>의 참조자를 매개변수로 받아들이는 생성자가 SmartPtr\<T> 안에 있기 때문이다. 이런 생성자 (SmartPtr\<U>로부터 SmartPtr\<T>를 만들어내는 생성자)를 가리켜 일반화 복사 생성자라고 부른다.

위의 일반화 복사 생성자가 explicit으로 선언되지 않았는데 그 이유는 기본 제공 포인터는 포인터 타입 사이의 타입변환이 암시적으로 이루어지며 캐스팅이 필요하지 않기 때문이다.

그러나 SmartPtr에 선언된 일반화 복사 생성자는 실제로 우리가 원하는 것보다 더 많은 것을 해준다. 우리는 SmartPtr\<Bottom>으로부터 SmartPtr\<Top>을 만들 수 있기를 원했지 그 반대는 원하지 않았다.

이를 해결할 방법으로 auto_ptr 및 tr1::shared_ptr 에서 쓰는 방법을 그대로 따라서 SmartPtr도 get 멤버 함수를 통해 해당 스마트 포인터 객체에 자체적으로 담긴 기본제공 포인터의 사본을 반환한다고 가정하면 이것을 이용해서 생성자 템플릿에 우리가 원하는 타입 변환 제약을 줄 수 있다.

```cpp
template<typename T>
class SmartPtr {
public:
	template<typename U>
	SmartPtr(const SmartPtr<U>& other)  //이 SmartPtr에 담긴 포인터를
	: heldPtr(other.get()) { ... }      //다른 SmartPtr에 담긴 포인터로 초기화한다.

	T* get() const { return heldPtr; }
	...
private:
	T *heldPtr;  //SmartPtr에 담긴 기본 제공 포인터
}
```
멤버 초기화 리스트를 이용해 SmartPtr\<T>의 데이터 멤버인 T* 타입의 포인터를 SmartPtr\<U>에 들어 있는 U* 타입의 포인터로 초기화했다. 이렇게 해두면 U\*에서 T\*로 진행되는 암시적 변환이 가능할 때만 컴파일 에러가 나지 않는다.

멤버 함수 템플릿의 활용은 대입 연산에서도 이루어진다. 예를 들면 TR1의 shared_ptr 클래스 템플릿은 호환되는 모든 기본 제공 포인터, tr1::shared_ptr, auto_ptr, tr1::weak_ptr 객체들로부터 생성자 호출이 가능한데다가, 이들 중 tr1::weak_ptr을 제외한 나머지를 대입 연산에 쓸 수 있도록 만들어져 있다.
```cpp
template<class T> class shared_ptr{
public:
	template<class Y>
		explicit shared_ptr(Y *p);                    //호환되는 모든
	template<class Y>                                 //기본 제공 포인터,
		shared_ptr(shared_ptr<Y> const& r);           //shared_ptr,
	template<class Y>                                 //weak_ptr,
		explicit shared_ptr(weak_ptr<Y> const& r);    //auto_ptr 객체로부터
	template<class Y>                                 //생성자 호출이 가능
		explicit shared_ptr(auto_ptr<Y>& r);
	template<class Y>
		shared_ptr& operator= (shared_ptr<Y> const& r); //호출되는 모든
	template<class Y>                                   //shared_ptr 혹은
		shared_ptr& operator= (auto_ptr<Y>& r);         //auto_ptr로 부터
	...	                                                //대입이 가능하다.
};
```
일반화 복사 생성자를 제외하고 모든 생성자가 explicit로 선언되어 있는게 보인다. 이 뜻은 shared_ptr로 만든 어떤 타입으로부터 또다른 (shared_ptr로 만든) 타입으로 진행되는 암시적 변환은 허용되지만 기본 제공 포인터 혹은 다른 스마트 포인터 타입으로부터 변환되는 것은 막겠다는 뜻이다.

tr1::shared_ptr 생성자와 대입 연산자에 넘겨지는 auto_ptr이 const로 선언되지 않았는데 이와 대조적으로 tr1::shared_ptr 및 tr1::weak_ptr 은 const로 넘겨지도록 되어 있다. 이유는 auto_ptr은 복사 연산으로 인해 객체가 수정될 때 오직 복사된 쪽 하나만 유효하게 남는 사실을 반영하기 위함이다.

'복사 생성자가 필요한 데 프로그래머가 직접 선언하지 않으면 컴파일러가 자동으로 하나 만든다'라는 규칙이 있는데 멤버 템플릿은 이 규칙을 바꾸지 않는다. 즉 일반화 복사 생성자를 선언하는 것은 컴파일러 나름의 복사 생성자를 만드는 것을 막는 요소가 아니다. 따라서 어떤 클래스의 복사 생성을 전부 손아귀에 넣고 싶다면 일반화 복사 생성자는 물론이고 "보통의" 복사 생성자까지 선언해야 한다.

```cpp
template<class T> class shared_ptr {
public:
	share_ptr(shared_ptr const& r);  //복사 생성자

	template<class Y>                       //일반화 복사 생성자
		shared_ptr(shared_ptr<Y> const& r);
	shared_ptr& operator= (shared_ptr const& r);  //복사 대입 연산자
	template<class Y>
		shared_ptr& operator= (shared_ptr<Y> const& r); //일반화 복사 대입 연산자
	...
};
```


+ 호환되는 모든 타입을 받아들이는 멤버 함수를 만들려면 멤버 함수 템플릿을 사용하자.
+ 일반화된 복사 생성 연산과 일반화된 대입 연산을 위해 멤버 템플릿을 선언했다 하더라도, 보통의 복사 생성자와 복사 대입 연산자는 여전히 직접 선언해야 한다.