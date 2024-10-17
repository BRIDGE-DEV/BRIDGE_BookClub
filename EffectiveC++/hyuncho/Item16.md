# Item16. new 및 delete를 사용할 때는 형태를 만드시 맞추자
```cpp
std::string *stringArray = new std::string[100];
...
delete stringArray; //객체 한개를 삭제
//위와 같은 경우 stringArray가 가리키는 100개의 string 객체들 가운데 99개는 정상적인 소멸 과정을 거치지 못할 가능성이 크다.

delete [] stringArray; //객체의 배열을 삭제
```
delete 연산자가 적용되는 객체는 대체 몇 개일까? -> 답은 '소멸자가 호출되는 횟수'가 된다.
대괄호 쌍 []을 delete 뒤에 붙여주는 것은 포인터가 배열을 가리키고 있다는 의미이다.
```cpp
typedef std::string AddressLines [4];
std::string *pal = new AddressLines;

delete pal;    //무슨일이 생길지 모른다.
delete [] pal; //깔끔하게 메모리를 해제한다.
//즉, typdef로 정의된 어떤 타입의 객체(배열)를 메모리에 생성하려고 new를 썼을 때 delete[]를 사용해야함. 되도록이면 배열 타입을 typedef로 만들지 말고 vertor를 활용하자.
```


+ new 표현식에 []를 썼으면, 대응되는 delete 표현식에도 []를 써야 한다. 마찬가지로 new 표현식에 []를 안썼으면, 대응되는 delete 표현식에도 []를 쓰지 말아야 한다.