# CGI 아키텍처 다이어그램

<img width="361" alt="스크린샷 2023-04-01 20 28 17" src="https://user-images.githubusercontent.com/76278794/229286069-17e194f8-b556-4d35-bc87-120abb7282e1.png">

<br>

# CGI란?

- Common Gateway Interface는 web server와 custom script 간 정보 교환 방식을 정의하는 표준이다.
- CGI spec는 NCSA가 유지보수하며 NCSA가 CGI를 정의한다.
- CGI(Common Gateway Interface)는 외부 게이트웨이 프로그램이 HTTP 서버와 같은 정보 서버와 인터페이스하기 위한 표준입니다.

# Web server 설정

- CGI 프로그래밍을 계속하기 전에 웹 서버가 CGI를 지원하고 CGI 프로그램을 처리하도록 구성되어 있는지 확인하십시오.
- HTTP 서버에서 실행할 모든 CGI 프로그램은 사전 구성된 디렉토리에 보관됩니다.
- 이 디렉터리는 CGI 디렉터리라고 하며 관례에 따라 /var/www/cgi-bin으로 이름이 지정됩니다.
- CGI 파일은 C++ 실행 파일이지만 .cgi로 확장된다.
- 기본적으로 Apache Web 서버는 /var/www/cgi-bin에서 CGI 프로그램을 실행하도록 구성되어 있습니다.
- CGI 스크립트를 실행할 다른 디렉터리를 지정하려면 httpd.conf 파일에서 다음 섹션을 수정할 수 있습니다

```cpp
<Directory "/var/www/cgi-bin">
   AllowOverride None
   Options ExecCGI
   Order allow,deny
   Allow from all
</Directory>

<Directory "/var/www/cgi-bin">
   Options All
</Directory>
```

# CGI by CPP

- c++로 작성된 이런 프로그램도 CGI가 될 수 있습니다.

```cpp
#include <iostream>
using namespace std;

int main () {
   cout << "Content-type:text/html\r\n\r\n";
   cout << "<html>\n";
   cout << "<head>\n";
   cout << "<title>Hello World - First CGI Program</title>\n";
   cout << "</head>\n";
   cout << "<body>\n";
   cout << "<h2>Hello World! This is my first CGI program</h2>\n";
   cout << "</body>\n";
   cout << "</html>\n";

   return 0;
}
```

<br><br>

# Nginx

- Nginx는 기본적으로 다중프로세스/스레드 모델이다.

<br>

## 프로세스

- Nginx는 1개의 마스터 프로세스와 여러개의 워커 프로세스로 구성된다.
- 마스터 프로세스는 주소 환경 설정 파일의 로드와 같은 초기화작업을 수행한다.
- 실제 클라이언트 요청 처리 작업은 워커프로세스에서 수행된다.
- 기본값으로 CPU코어의 개수이고, 수동으로 설정할 수 있다.

<br>

## 스레드

- nginx는 기본적으로 각 워커 프로세스가 1개의 스레드를 사용해 요청을 처리한다.
- 하지만, 이 각 워커프로세스하나로만 요청을 처리하는 것은 시간이 오래걸린다.
- 특히, `read/write와 같이 시간이 오래걸리는 작업`은 Thread Pool에 있는 워커스레드에서 처리한다.
  - Memory에 Cache되어있지 않은 경우에 시간이 오래걸린다.
  - Async model을 선택할수도있지만 FreeBSD에서만 가능허거나 리눅스에서는 모든 파일 액세스가 메모리 캐시를 바이패스하는 문제가 있다.

<br>

따라서, Nginx에서 생성되는 총 스레드의 개수는 워커 프로세스 개수 \* 워커 스레드 개수 이다.

이렇게 생성된 스레드 모두 클라이언트 요청을 처리하게된다.
