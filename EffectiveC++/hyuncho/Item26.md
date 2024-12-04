# Item26. 변수 정의는 늦출 수 있는 데까지 늦추는 근성을 발휘하자
생성자와 소멸자를 끌고 다니는 변수의 경우 변수를 정의하면 반드시 생성자가 호출되는 비용과 유효범위를 벗어날 때 소멸자가 호출되는 비용 두가지 비용이 발생한다.
```cpp
//너무 빨리 'encrypted'변수를 정의한 경우
std::string encryptPassword(const std::string& password)
{
	using namespace std;
	string encrypted;

	if (password.length() < MinimumPasswordLength) {
		throw logic_error("Password is too short");
	}
	...

	return encrypted;
}
```
encrypted 객체가 사실 이 함수에서 완전히 안 쓰인다고 할 수 없지만 예외가 발생하면 사용되지 않는다.
```cpp
std::string encryptPassword(const std::string& password)
{
	...    //길이 조건 검사

	std::string encrypted(password);   //변수를 정의함과 동시에 초기화, 이때 복사생성자가 사용됨.

	encrypt(encrypted);
	return encrypted;
}
```
위와 같은 코드를 보면 늦출 수 있는 데 까지 늦추고 초기화 인자를 손에 넣기 전까지 정의를 늦추었다. 이런 방법으로 쓰이지도 않을 객체의 생성과 소멸을 발생시키지 않으며, 불필요한 기본 생성자 호출도 일어나지 않는다. 또한 변수의 의미가 명확한 상황에서 초기화가 이루어지기 때문에, 변수의 쓰임새를 문서화하는 데도 큰 도움이 된다.
```cpp
// A 방법: 루프 바깥쪽에 정의
Widget w;
for (int i = 0; i < n; i++){
	w = i;
	...
}

// B 방법: 루프 안쪽에 정의
for (int i = 0; i < n; i++){
	Widget w(i);
	...
}
```
A, B를 비교했을 때 어느 것이 더 효율적일까?
A방법 : 생성자 1번 + 소멸자 1번 + 대입 n번
B방법 : 생성자 n번 + 소멸자 n번

A방법이 효율적인 경우
+ 생성자-소멸자 상보다 대입에 들어가는 비용이 적은 경우
+ 전체 코드에서 수행 성능에 민감한 부분을 건드리는 경우

B방법이 효율적인 경우
+ 프로그램의 이해도와 유지보수성을 높이려고 할 때

결론은 A방법이 효율적인 경우를 제외하고는 B방법을 택하자.


+ 변수 정의는 늦출 수 있을 때까지 늦추자. 프로그램이 더 깔끔해지며 효율도 좋아진다.