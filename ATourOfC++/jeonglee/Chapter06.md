## 6장: 필수 연산

타입의 생성자, 소멸자, 복사와 이동 연산은 논리적으로 별개 아니다. 서로 연관된 집합으로 정의하지 않으면 논리적 문제나 성능 문제를 겪게 된다. 클래스 x가 자유 저장소 반납이나 자원 해제 같은 중대한 작업을 수행하는 소멸자를 포함하면 그 클래스를에 함수 구성 전체를 넣어야 할 것이다.

```c++
class X {
public:
    X() { /* 생성자 */ }
    ~X() { /* 소멸자 */ }
    X(const X&) { /* 복사 생성자 */ }
    X(X&&) { /* 이동 생성자 */ }
    X& operator=(const X&) { /* 복사 대입 연산자 */ return *this; }
    X& operator=(X&&) { /* 이동 대입 연산자 */ return *this; }
};
```

- [관련 정리 내용 CodeReview](https://github.com/fkdl0048/CodeReview/blob/main/Language/C%2B%2B/ConstructorDestructor/README.md)

