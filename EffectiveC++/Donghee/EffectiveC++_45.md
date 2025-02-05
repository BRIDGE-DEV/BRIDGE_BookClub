# 챕터7: 템플릿과 일반화 프로그래밍

## 항목 45: “호환되는 모든 타입”을 받아들이는 데는 멤버 함수 템플릿이 직방!

포인터에는 스마트 포인터로 대신할 수 없는 특징이 있다. 바로 암시적 변환을 지원한다는 것이다. 파생 클래스 포인터는 암시적으로 기본 클래스 포인터로 변환되고, 비상수 객체에 대한 포인터는 상수 객체에 대한 포인터로의 암시적 변환이 가능하고, 등등이다. 이런 타입 변환을 사용자 정의 스마트 포인터를 써서 흉내 내려면 무척 까다롭다. 아래 예제를 보자.

```cpp
class Top { ... };
class Middle: public Top { ... };
class Bottom: public Middle { ... };

template<typename T>
class SmartPtr {
public:
	explicit SmartPtr(T *realPtr);
	...
};

SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle);
SmartPtr<Top> pt2 = SmartPtr<Bottom>(new Bottom);
SmartPtr<const Top> pct2 = pt1;
```

이렇게 같은 템플릿으로 만들어진 다른 인스턴스들 사이에는 어떤 관계도 없기 때문에, 컴파일러의 눈에는 `SmartPtr<Middle>`과 `SmartPtr<Top>`은 완전히 별개의 클래스로 보인다.

이를 해결하기 위한 방법은, 생성자를 만들어내는 템플릿을 쓰는 것이다. 이것을 **멤버 함수 템플릿**으로도 부르는데, 이는 어떤 클래스의 멤버 함수를 찍어내는 템플릿을 일컫는다.

```cpp
template<typename T>
class SmartPtr {
public:
	template<typename U>
	SmartPtr(const SmartPtr<U>& other);
	...
};
```

이 코드에 따르면, 모든 T 타입 및 모든 U 타입에 대해서 `SmartPtr<T>` 객체가 `SmartPtr<U>`로부터 생성될 수 있다. 이런 꼴의 생성자를 가리켜 **일반화 복사 생성자**라고 한다.

지금 `SmartPtr`에 선언된 일반화 복사 생성자는 실제로 우리가 원하는 것보다 더 많은 것을 해 준다. `SmartPtr<Top>`으로부터 `SmartPtr<Bottom>`을 만들 수도 있다. 이것은 원하는 바가 아니다.

`tr1::shared_ptr`에서 쓰는 방법을 따라서 `get` 멤버 함수를 통해 기본제공 포인터의 사본을 반환한다면, 이것을 이용해 타입 변환 제약을 줄 수 있다.

```cpp
template<typename T>
class SmartPtr {
public:
	template<typename U>
	SmartPtr(const SmartPtr<U>& other) : heldPtr(other.get()) {...}
	T* get() const { return heldPtr; }
	...
private:
	T *heldPtr;
};
```

이렇게 해 두면 `U*`에서 `T*`로 진행되는 암시적 변환이 가능할 때만 컴파일 에러가 나지 않는다.

멤버 함수 템플릿은 생성자 뿐만 아니라 대입 연산자에서도 많이 쓰인다. 예시로, `shared_ptr` 클래스 템플릿은 호환되는 모든 기본제공 포인터, `tr1::shared_ptr`, `auto_ptr`, `tr1::weak_ptr` 객체들로부터 생성자 호출이 가능하고, `tr1::weak_ptr`을 제외한 나머지를 대입 연산에 쓸 수 있다. 아래와 같다.

```cpp
template<class T> class shared_ptr {
public:
	template<class Y>
	explicit shared_ptr(Y * p);
	template<class Y>
	shared_ptr(shared_ptr<Y> const& r);
	template<class Y>
	explicit shared_ptr(weak_ptr<Y> const& r);
	template<class Y>
	explicit shared_ptr(auto_ptr<Y>& r);
	template<class Y>
	shared_ptr& operator=(shared_ptr<Y> const& r);
	template<class Y>
	shared_ptr& operator=(auto_ptr<Y>& r);
	...
};
```

일반화 복사 생성자를 제외하고는 모든 생성자가 `explicit`로 선언되어 있다. 이는 `shared_ptr`로 만든 어떤 타입으로부터 또 다른 타입으로 진행되는 암시적 변환은 허용하지만, 나머지 변환은 암시적 변환을 모두 막겠다는 것이다.

멤버 함수 템플릿은 훌륭하지만, C++ 언어의 기본 규칙까지 바꾸지는 않는다. 어떤 `tr1::shared_ptr` 객체가 자신과 동일한 타입의 다른 `tr1::shared_ptr` 객체로부터 생성되는 상황에서, 컴파일러는 `tr1::shared_ptr`의 복사 생성자를 만들까? 아니면 일반화 복사 생성자 템플릿을 인스턴스화할까?

일본화 복사 생성자는 일반화 복사 생성자일 뿐, 보통의 복사 생성자가 아니다. 따라서 어떤 클래스의 복사 생성을 전부 관리하고 싶다면, 일반화 복사 생성자는 물론이고 보틍의 복사 생성자까지 직접 선언해주어야 한다.

> 호환되는 모든 타입을 받아들이는 멤버 함수를 만들려면 멤버 함수 템플릿을 사용하자.
일반화된 복사 생성 연산과 일반화된 대입 연산을 위해 멤버 템플릿을 선언했다 하더라도, 보통의 복사 생성자와 복사 대입 연산자는 직접 선언해야 한다.