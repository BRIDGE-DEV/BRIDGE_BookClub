C++의 연산은 사슬처럼 엮일 수 있는 재미있는 성질을 가지고 있다.
```cpp
int x, y, z;
x = y = z = 15;
```
이는
```cpp
x = (y = (z = 15)); 
```
와 같이 분석된다.

이렇게 대입 연산이 사슬 처럼 엮이려면 좌변 인자에 대한 참조자를 반환하도록 관례를 지키는 것이 좋다.
```cpp
class Widget {
public:
	...
	Widget& operator=(const Widget& rhs)
	{
		...
		return *this;
	}
};
```

+ **대입 연산자는 \*this의 참조자를 따르도록 만들자**