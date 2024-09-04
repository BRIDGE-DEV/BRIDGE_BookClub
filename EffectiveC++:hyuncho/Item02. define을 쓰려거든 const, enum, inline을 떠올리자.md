### # define은 언어로 취급되지 않는다
간단한 constants를 위해서는 # define 대신에 const objects 또는 enum을 사용해라
매크로 같은 함수들을 위해서는 # define 대신에 인라인 함수를 사용해라

```cpp
#define ASPECT_RATIO 1.653;       // 이렇게 사용시에 문제 발생
const double AspectRatio = 1.653; //이와 같이 사용.
```
문제 : ASPECT_RATIO는 컴파일러에 의해 보이지 않는다. 전처리과정중에 삭제되기 때문. ASPECT_RATIO는 symbol table에 들어가지 않아 에러를 고칠 때 혼란이 올 수 있다. 왜나하면 error 메세지가 1.653으로 언급되기 때문

### # define을 const 로 바꾸었을때 특별한 주의점 2가지
1. 상수 포인터 선언
    
    ```cpp
    const char * const authorName = "Scott Meyers";  //pointer에 const, 포인터가 가리키는 대상도 const
    const std::string authorName("Scott Mayers");   //char* 보다는 string 사용
    ```
    
2. 클래스 specific 상수
    ```cpp
    class GamePlayer{
    private:
    	static const int NumTurns = 5; // 이는 선언이지 정의가 아님. 
    	int scores[NumTurns];
    };
    ```
    클래스 내의 const뒤에 static을 붙이는 이유는 객체가 여러개 생성되어도 const를 사용해 어차피 같은 값이기 때문에 하나만 존재해도 되기 때문
    ```cpp
    const int GamePlayer::NumTurns;
    //NumTurns의 정의이다. 이는 헤더파일이 아닌 구현파일에 있어야함.
    //이때 왜 값을 주지 않았나하면 상수가 선언된 것에 초기 값이 제공되었기 때문임. 그래서 정의시점에는 값을 넣을 수 없다.
    ```
### # define을 이용한 매크로보다는 inline을 사용하자
```cpp
#define CALL_WITH(a, b) f((a) > (b) ? (a) : (b))

int a = 5, b = 0;
CALL_WITH_MAX(++a, b);        //a가 두 번 증가
CALL_WITH_MAX(++a, b + 10);   //a가 한 번 증가

template<typename T>
inline void callWithMax(const T& a, const T& b)
{
	f(a > b ? a : b);
}
```
인라인을 통해 기존 매크로의 효율을 그대로 유지하면서 정규 함수의 모든 동작방식 및 타입 안정성까지 완벽히 취할 수 있다.
### 궁금증
**선언과 정의의 차이**
선언은 컴파일러에게 어떤 대상의 이름을 알려주는 행위. 정의는 컴파일러에게 어떤 대상의 실제 내용을 알려주는 행위
이 두가지를 구분하는 기준은 memory address binding의 유무이다. 어떤 이름에 대해 상응하는 메모리가 정해진다면 그것은 정의이고 그렇지 않다면 선언이다.
[선언과 정의의 차이.-펌글](https://ciwhiz.tistory.com/257)