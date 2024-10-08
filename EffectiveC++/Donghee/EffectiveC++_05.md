# 챕터2: 생성자, 소멸자 및 대입 연산자

## 항목5: C++가 은근슬쩍 만들어 호출해 버리는 함수들에 촉각을 세우자

C++의 어떤 멤버 함수는 클래스 안에 직접 선언하지 않으면, 컴파일러가 저절로 선언해 주도록 되어 있다. 생성자, 복사 생성자, 복사 대입 연산자, 소멸자가 그들이다. 다음의 빈 클래스를 보자.

```cpp
class Empty{};
```

이는 사실,

```cpp
class Empty{
public:
	Empty() {...} // 기본 생성자
	Empty(const Empty& rhs) {...} // 복사 생성자
	~Empty() {...} // 소멸자
	Empty& operator=(const Empty& rhs) {...} // 복사 대입 연산자
};
```

이렇게 쓴 것과 근본적으로 다르지 않다는 것이다. 물론 복사 대입 연산자(=) 같은 경우엔 제약 조건이 붙어 있다. 최종 결과가 적법(legal)하고, 이치에 맞아야만(reasonable)해야만 컴파일러가 이들을 자동 생성한다. 예를 들어 데이터 멤버가 상수나 참조자가 있다면,  이를 다른 값으로 대입하는 것은 불가능하니 이 상황에서 복사 대입 연산자를 사용하면, 컴파일 거부를 일으킨다.

> 컴파일러는 경우에 따라 기본 생성자, 복사 생성자, 복사 대입 연산자, 소멸자를 암시적으로 만들어 놓는다.
> 복사 대입 연산자는 그 결과가 적법하고 이치에 맞아야만 자동 생성된다.