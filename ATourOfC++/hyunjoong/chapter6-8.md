소멸자가 delete를 호출해야 하거나 락을 풀어야하거나 등 리소스 관리를 하는 경우

1. 생성자
2. 기본 생성자
3. 복사 생성자
4. 이동 생성자
5. 복사 대입자
6. 이동 대입자
7. 소멸자

.. rule of five.

대신 std::vector, std::string같이 알아서 자원 관리를 해주는 친구들을 멤버로 쓰면
안 써도 됨! rule of zero.

= delete로 자동으로 생성자를 컴파일러가 만드는걸 막아주는 기능도 알아둬야 한다.

7.3.3.2

솔직히 말해서 좀 괴기하긴 하다. rust에서 나오는 match expression을 따라하려고 한 것은 같은데..

만약 rust의 match expression을 가져온다면?

```rust
vector<int> v = match m {
    zero => vector<int>(n),
    seq => vector<int>{p, q},
    cpy => arg,
}
```
람다보다 훨씬 깔끔하지 않은가?

c#에도 switch expression이 있다.

```c#
vector<int>v = m switch {
    zero => vector<int>(n),
    seq => vector<int>{p, q},
    cpy => arg,
}

```
v :: vector.int.
    m is
    zero -> n .with_size,
    seq -> p, q .from_iter,
    cpy -> arg,
~ v~. delete=>
```

7.3.3.3 finally

일단 이걸 공식 지원하려면 아직도 멀었다는게 좀 아쉽긴 하다
https://en.cppreference.com/w/cpp/experimental/scope_exit.html

솔직히 뭐 std::vector, std::string, std::unique_ptr이 있는데 굳이 저게 필요하냐 해서 아직 안만드는것도 같긴한데..

zig, go의 defer문이 참 수동 메모리 관리에서 빛을 발하지 않나 싶다.
솔직히 조금만 코드가 길어져도 내가 메모리 해제를 했는지 한눈에 보이지도 않고 메모리 해제하는 부분이 괜히 지저분해 보인다.

```cpp
void *p = malloc(n * sizeof (int));
defer free(p);
```

이렇게 쓸 수 있다면 얼마나 좋냐는 것이다.. 람다로 하는게 솔직히 defer보다 깔끔할 수 있는지 의문이다.

std.heap.
p :: n * #sizeof int .alloc=>
~ p~ .free=>

# 8.
컨셉이라는 새로운 개념이 c++20에 등장하였는데..
rust나 c#의 where T : 와 비슷한 느낌으로 나온거긴 한데, 훨씬 더 유연하다는 생각이 들긴 한다. 동시에 또 비교적 복잡하다는 생각도 든다.

c#의 경우에는 너무 단순하게 클래스 상속 정도만 체크하는 느낌이지만, rust는 인터페이스가 Iterator, Copy, Eq 등 세분화 및 정의가 잘 돼있다. 그래서 그냥 where T: Iterator, U: Copy로 하면 T는 반복자가, U는 복사가 되는 얘들로 제한이 된다. 그리고 인터페이스로써 무엇을 할 수 있는지 정의가 되어 있으므로, 우리가 기존에 쓰던 코드와 크게 다르지 않은 문법으로 들어올 수 있는 타입에 제약을 걸 수 있는 것이다.

그런데 c++의 컨셉은 문법이 새로 만들어졌다.

```c++
template<typename T, typename T2 = T>
concept Equality_comparable =
    requires (T a, T b) {
        { a == b } -> Boolean;
        { a != b } -> Boolean;
    };
```

책에도 나오지만 저 Boolean은 타입 bool이 아니라 컨셉이다. 아마 bool의 정의 자체가 굉장히 느슨해서 bool a = 3;도 그냥 컴파일이 돼버리는 문제때문에 새로 아예 만들지 않았을까도 싶다.

rust로 다시 만들어본다면..
```rust
trait Eq<Rhs = Self>    // 일단 where문은 생략함..
{
    fn eq(&self, other: &Rhs) -> bool;
    fn ne(&self, other: &Rhs) -> bool;
}
```

```cpp
template<typename S>
concept Sequence = requires (S a) {
    typename range_value_t<S>;
    typename iterator_t<S>;

    { a.begin() } -> same_as<iterator_t<S>>;
    { a.end() } -> same_as<iterator_t<S>>;

    requires input_iterator<iterator_t<S>>;
    requires same_as<range_value_t<S>, iter_value_t<S>>;
};
```

```rust
trait Sequence<T> {
    type RangeValue<T>;
    type Iterator<T>;

    fn begin() -> Iterator<T>
    fn end() -> Iterator<T>
}
```
