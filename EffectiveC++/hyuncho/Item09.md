두가지 이유
+ 호출 결과가 원하는대로 돌아가지 않을 것이다.
+ 분노한(?) 얼굴을 하고 있을 것
```cpp
class Transaction {
public:
	Transation();
	virtual void logTransaction() const = 0;
	...
};

Transaction::Transaction()
{
	...
	logTransaction();
}

class BuyTransaction: public Transaction {
public:
	virtual void logTransaction() const;
	...
};

class SellTransaction: public Transaction {
public:
	virtual void logTransaction() const;
	...
}
```

BuyTransaction 생성자가 호출되는 것은 어쨌든 맞다. 하지만 우선 Transaction 생성자가 호출되어야 한다. 파생 클래스 객체가 생성될 때 그 객체의 기본 클래스 부분이 파생클래스 부분 보다 먼저 호출되는 것이 정석이다. Transaction 생성자에서 가상함수 logTransaction을 호출하는데 여기서 호출되는 함수가 BuyTransaction이 아닌 Transaction이 호출이 된다. 왜냐하면 기본 생성자의 클래스가 호출될 동안에는 가상 함수는 파생 클래스 쪽으로 내려가지 않는다. 그 대신 객체 자신이 기본 클래스 타입인 것처럼 동작한다. 만약 파생클래스 쪽으로 내려가는 동작이 이루어졌다면 아직 초기화 되지도 않은 데이터를 건드리는 불상사가 일어날 것이다.

+ **생성자 혹은 소멸자 안에서 가상 함수를 호출하지 마세요. 가상 함수라고 해도 지금 실행 중인 생성자나 소멸자에 해당되는 클래스의 파생 클래스 쪽으로는 내려가지 않는다.**