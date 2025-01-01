# Item44. 매개변수에 독립적인 코드는 템플릿으로부터 분리시키자
템플릿은 코딩 시간 절약, 코드 중복 회피 두 가지 장점이 존재한다.

그러나 아무 생각 없이 템플릿을 사용하면 코드 비대화 발생 우려가 있다. 똑같은 내용의 코드와 데이터가 여러 벌로 중복되어 이진 파일로 구워진다. 소스코드만 보면 단정해보이지만 목적 코드의 모양새는 뚱뚱 흐느적 그 자체이다.

해결 방법으로는 공통성 및 가변성 분석을 하는 것이다. 이는 공통점을 찾고 새로운 함수에 옮기고 다른 부분은 원래의 함수에 남겨놓는 방식이다.

템플릿이 아닌 코드에서는 코드 중복이 명시적이다. 두 함수 혹은 두 클래스 사이에 똑같은 부분이 있으면 눈으로 찾으면 된다. 반면 템플릿 코드는 코드 중복이 암시적이다. 어떤 템플릿이 여러 번 인스턴스화 될 때 발생할 수 있는 코드 중복을 감각으로 알아채야 한다.

```cpp
template<typename T, std::size_t n>
class SquareMatrix {
public:
	...
	void invert();   //주어진 행렬을 그 저장공간에서 역행렬로 바꾼다.
};

SquareMatrix<double, 5> sm1;
...
sm1.invert();   //SquareMatrix<double, 5>::invert 를 호출한다.

SquareMatrix<double, 10) sm2;
sm2.invert();   //SquareMatrix<double, 10>::invert 를 호출한다.
```
이때 invert의 사본이 인스턴스화 되는데 만들어지는 사본의 개수가 두 개이다. 5X5에 대해, 10X10에 대해 각각 동작 할 함수이다. 하지만 행과 열의 크기를 나타내는 상수 빼면 똑같은 함수이다. 이런 현상이 바로 템플릿을 포함한 프로그램이 코드 비대화를 일으키는 일반적인 형태 중 하나이다.

이제 값을 매개변수로 받는 별도의 함수를 만들고 그 함수에 5와 10을 매개변수로 넘겨서 호출하게 만들겠다.
```cpp
template<typename T>
class SquareMatrixBase {
protected:
	...
	void invert(std::size_t matrixsize);
	...
};

template<typename T, std::size_t n>
class SquareMatrix : private SquareMatrixBase<T> {
private:
	using SquareMatrixBase<T>::invert;  //기본 클래스의 invert가 가려지는 것을 막기 위한 문장
public:
	...
	void invert() { this->invert(n); }  //invert의 기본 클래스 버전에 대해 인라인 호출을 수행한다.
}
```
같은 타입의 객체를 원소로 갖는 모든 정방행렬은 오직 한 가지의 SquareMatrixBase 클래스를 공유하게 되는 것이다. 다시 말해, 같은 원소 타입의 정방행렬이 사용하는 기본 클래스 버전의 invert 함수도 오직 한 개의 사본이다.

SquareMatrixBase::invert 함수는 파생 클래스에서 코드 복제를 피할 목적으로만 마련한 장치이기 때문에, public 멤버가 아니라 protected 멤버로 되어 있다. 기본 클래스의 invert 함수를 호출하도록 구현된 파생 클래스의 invert 함수가 바로 인라인 함수 이기 때문에 이 함수의 호출에 드는 추가 비용은 없다.

템플릿화된 기본클래스의 멤버 함수 이름이 파생클래스에서 가려지는 문제를 피하기 위한 것으로 "this->" 를 사용했지만 using 선언이 위에 있어 꼭 필요하지는 않다.

상속 관계가 private 이기 때문에 기본 클래스를 사용하는 데는 순전히 파생클래스의 구현을 돕기 위한 일 뿐이라는 것을 드러내는 부분이다.

이제 진짜 행렬을 저장한 데이터를 기본클래스가 역행렬을 만들 때 사용할 수 있도록 방법이 필요하다. 해결방법으로 행렬 값을 담는 메모리에 대한 포인터를 SquareMatrixBase가 저장하게 하는 것이다.

```cpp
template<typename T>
class SquareMatrixBase{
protected:
	SquareMatrixBase(std::size_t n, T *pMem):size(n), pData(pMem) {}

	void setDataPtr(T *ptr) { pData = ptr; }
	...
private:
	std::size_t size;
	T *pData;
};
```
이렇게 설계해두면 행렬 값을 담을 메모리 할당 방법의 결정 권한이 파생클래스 쪽으로 넘어가게 된다.
```cpp
template<typename T, std::size_t n>
class SquareMatrix : private SquareMatrixBase<T> {
public:
	SquareMatrix()
	:SquareMatrixBase<T>(n, data) {}  //행렬 크기(n) 및 데이터 포인터를 기본클래스로 올려보낸다.
	...
private:
	T data[n*n];
};
```
이렇게 파생 클래스를 만들면 동적 메모리 할당이 필요 없는 객체가 되지만, 객체 자체의 크기가 커질 수 있다. 이 방법이 마음에 들지 않는다면 각 행렬의 데이터를 힙에 둘 수도 있다.
```cpp
template<typename T, std::size_t n>
class SquareMatrix : private SquareMatrixBase<T> {
public:                                   //기본 클래스의 포인터를 널로 설정하고,
	SquareMatrix()                        //행렬 값의 메모리를 할당하고,
	: SquareMatrixBase<T>(n, 0),          //파생 클래스의 포인터에 그 메모리를
		pData(new T[n*n])                 //올려 놓은 후, 이 포인터의 사본을
	{ this->setDataPtr(pData.get()); }    //기본 클래스로 올려보낸다.
}
```

어느 메모리에 데이터를 저장하느냐에 따라 설계가 다소 달라지긴 하지만 코드 비대화 측면에서 아주 중요한 성과를 손에 쥘 수 있다는 점은 같다. 중요한 성과란 SquareMatrix에 속해 있는 멤버 함수 중 상당 수가 기본 클래스 버전을 호출하는 단순 인라인 함수가 될 수 있으며 똑같은 타입의 데이터를 원소로 갖는 모든 정방행렬들이 행렬 크기에 상관없이 이 기본 클래스 버전의 사본 하나를 공유한다는 것이다. 이와 동시에 행렬 크기가 다른 SquareMatrix 객체는 저마다 고유의 타입을 갖고 있다는 점도 아주 중요하다.

행렬 크기가 미리 녹아든 상태로 별도의 버전이 만들어지는 invert.
행렬 크기가 함수 매개 변수로 넘겨지거나 객체에 저장된 형태로 다른 파생 클래스들이 공유하는 버전의 invert.

전자가 더 좋은 코드를 생성할 가능성이 높다. 예를 들어 크기별 고정 버전(전자)의 경우, 행렬 크기가 컴파일 시점에 투입되는 상수이기 때문에 상수 전파(constant propagation) 등의 최적화가 먹혀 들어가기에 좋다. 생성되는 기계 명령어에 대해 이 크기 값이 즉치 피연산자(immediate operand)로 바로 박히는 것도 이런 종류의 최적화 중 하나이다.

반면 여러 행렬 크기에 대해 한 가지 버전의 invert 를 두도록 만들면 실행 코드가 작아지는 이점이 있다. 이렇게 되면 프로그램 작업 세트 크기가 줄어들면서 명령어 캐시 내의 참조 지역성도 향상된다. 이렇게 되면 프로그램 실행속도가 빨라지게 된다.

결국 정확한 판단을 위해서는 쓰는 플랫폼 및 대표적인 데이터 집합에 대해 직접 두 방법을 적용해보고 그 결과를 관찰 할 수 밖에 없다.

효울에 대해 생각해볼 것이 하나 더 있는데, 바로 객체의 크기이다. invert 비슷한 크기 독립형 버전의 함수를 기본 클래스 쪽으로 아무 생각 없이 옮겨 놓다 보면, 슬그머니 각 객체의 전체 크기가 늘어나게 된다. 예를 들면 SquareMatrix 객체는 메모리에 생길 때마다 SquareMatrixBase 의 클래스에 들어있는 데이터를 가리키는 포인터를 하나씩 떠 안고 있다. 결국 이것 때문에 SquareMatrix 객체 하나의 크기는 최소한 포인터 하나 크기만큼 낭비된 것이다.


+ 템플릿을 사용하면 비슷비슷한 클래스와 함수가 여러 벌 만들어진다. 따라서 템플릿 매개변수에 종속되지 않은 템플릿 코드는 비대화의 원인이 된다.
+ 비타입 템플릿 매개변수로 생기는 코드 비대화의 경우, 템플릿 매개변수를 함수 매개변수 혹은 클래스 데이터 멤버로 대체함으로써 비대화를 종종 없앨 수 있다.
+ 타입 매개변수로 생기는 코드 비대화의 경우, 동일한 이진 표현구조를 가지고 인스턴스화되는 타입들이 한 가지 함수 구현을 공유하게 만듦으로써 비대화를 감소시킬 수 있다.