# CleanCode_Chapter7

# CHAPTER 7 : 오류 처리

## 내용 정리

---

### 오류 코드보다 예외를 사용하라

오류 코드를 사용하면 호출자 코드가 복잡해진다. 함수를 호출한 즉시 오류를 확인해야 하기 때문이다. 그래서 오류가 발생하면 예외를 던지는 편이 낫다.

```java
public class Device Controller {
    /* ... */
    public void sendShutDown() {
        DeviceHandle handle = getHandle(DEV1);
        if (handle != DeviceHandle.INVALID) {
            retrieveDeviceRecord(handle);
            if (recode.getStatus() != DEVICE_SUSPENDED) {
                pauceDevice(handle);
                clearDeviceWorkQueue(handle);
                closeDevce(handle);
            }
            else {
                logger.lod("Device suspended.");
            }
        }
        else {
            logger.log("Invalid handle for: " + DEV1.toString());
        }
    }
}
```

위의 예시를 아래처럼 변경

```java
public class DeviceController {
    /* ... */
    public void sendShutDonw() {
        try {
            tryToShutDown();
        } catch (DeviceShutDownError e) {
            logger.log(e);
        }
    }

    private void tryToShutDown() thros DeviceShutDownError {
        DeviceHandle handle = getHandle(DEV1);
        DeviceRecord record = retrieveDeviceRecord(handle);

        pauseDevice(handle);
        clearDeviceWorkQueue(handle);
        closeDevice(handle);
    }

    private DeviceHandle getHandle(DeviceID id) {
        /* ... */
        throw new DeviceShutDownError("Invalid handle for: " + id.toString());
    }
}
```

### Try-Catch-Finally 문부터 작성하라

try 블록은 트랜잭션과 비슷하다. 블록에서 무슨 일이 생기든지 catch 블록은 프로그램 상태를 일관성 있게 유지해야 한다. 그러므로 예외가 발생할 코드를 짤 때는 try-catch-finally 문으로 시작하는 편이 좋다.

```java
public List<RecordedGrip> retrieveSection(String sectionName) {
    try {
        FileInputStream stream = new FileInputStream(sectionName);
        stream.close();
    } catch (FileNotFoundException e) {
        throw new StorageException("retrieval error", e);
    }
    return new ArrayList<RecordedGrip>();
}
```

try-catch 구조로 범위를 정의했으므로 TDD를 사용해 필요한 나머지 논리를 추가해야 한다. 먼저 강제로 예외를 일으키는 테스트 케이스를 작성한 후 테스트를 통과하게 코드를 작성하는 방법을 권장한다. 그러면 자연스럽게 try 블록의 트랜잭션 범위부터 구현하게 되므로 범위 내에서 트랜잭션 본질을 유지하기 쉬워진다.

### 예외에 의미를 제공하라

오류가 발생한 원인과 위치를 찾기 쉽도록 예외를 던질 때는 전후 상황을 충분히 덧붙여야 한다. 오류 메시지에 정보를 담아 예외와 함께 던지는 것이 좋다. 실패한 연산 이름과 실패 유형도 같이 언급한다.

### 호출자롤 고려해 예외 클래스를 정의하라

아래 코드는 오류를 형편없이 분류한 사례로, 외부 라이브러리가 던질 예외를 모두 잡아낸다.

```java
ACMEPort port = new ACMEPort(12);

try {
    port.open();
} catch (DeviceResponseException e) {
    reportPortError(e);
    logger.log("Device response exception", e);
} catch (ATM1212UnlockedException e) {
    reportPortError(e);
    logger.log("Unlock exception", e);
} catch (GMXError e) {
    reportPortError(e);
    logger.log("Device response exception");
} finally {
    /* ... */
}
```

예외에 대응하는 방식이 예외 유형과 무관하게 거의 동일하다. 따라서 중복을 제거하면서 예외 클래스를 정의하면 코드를 간결하게 고칠 수 있다.

```java
LocalPort port = new LocalPort(12);
try {
    port.open();
} catch (PortDeviceFailure e) {
    reportError(e);
    logger.log(e.getMessage(), e);
} finally {
    /* ... */
}
```

```java
public class LocalPort {
    private ACMEPort innerPort;

    public LocalProt(int portNumber) {
        innerPort = new ACMEPort(portNumber);
    }

    public void open() {
        try {
            innerPort.open();
        } catch (DeviceResponseException e) {
            throw new PortDeviceFailure(e);
        } catch (ATM1212UnlockedException e) {
            throw new PortDeviceFailure(e);
        } catch (GMXError e) {
            throw new PortDeviceFailure(e);
        }
    }
}
```

`LocalPort` 클래스처럼 외부 API를 감싸는 클래스는 매우 유용하다. 외부 API를 감싸면 외부 라이브러리와 프로그램 사이에서 의존성이 크게 줄어든다. 나중에 다른 라이브러리로 갈아타더라도 비용이 적다.

### null을 반환하지 마라

null을 반환하는 코드는 호출자에게 문제를 떠넘기는 것이다. 중간에 하나라도 null 확인을 빼먹는다면 애플리케이션이 통제 불능에 빠질지도 모른다. 메서드에서 null을 반환하고 싶다면, 그 대신 예외를 던지거나 특수 사례 객체를 반환하는 것이 좋다.

```java
List<Employee> employees = getEmployees();
for (Employee e : employees) {
    totalPay += e.getPay();
}
```

```java
public List<Employee> getEmployees() {
    if (/* 직원이 없다면 */) {
        return Collections.emptyList();
    }
}
```

위처럼 null을 반환하는 대신 빈 컬렉션을 반환다면 null 체크할 필요없이 코드가 훨씬 깔끔해다.

### null을 전달하지 마라

정상적인 인수로 null을 기대하는 API가 아니라면 메서드로 null을 전달하는 코드는 최대한 피해야 한다.

```
public class MetricsCalculator {
    public double xProjection(Point p1, Point p2) {
        assert p1 != null : "p1 should not be null";
        assert p2 != null : "p2 should not be null";
        return (p2.x - p1.x) * 1.5;
    }
}
```

assert 문을 사용해서 일부는 방지할 수는 있지만, 문제를 완전히 해결하지는 못한다. 대다수 프로그래밍 언어는 호출자가 실수로 넘기는 null을 적절히 처리하는 방법이 없다. 애초에 null을 넘기지 못하도록 금지하는 정책을 따르는 것이 보다 합리적이다.

## 느낀 점

---

프로그래밍 초보인 저는 놀랍게도 아직까지 try/catch 문으로 제대로 된 오류 처리를 만들어 본 적이없습니다 ㅎㅎ... 

존재는 알았지만 써야하는 이유를 몰랐었습니다. 쓸 일이 없기도 했구요. 아직 제가 오류 처리가 제대로 되어야만 돌아가는 큰 볼륨의 프로젝트를 맡은 적이 없어서 그런건지도 모르겠네요. 배워야할게 파도 파도 끝이없습니다.

## 논의 내용

---

오류 처리를 잘못해서, 혹은 오류 처리를 하지 않아 고생해 본 경험이 있나요?