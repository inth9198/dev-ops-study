# 2장: 프로세스 생성 실습 가이드

이 디렉토리에는 프로세스 생성과 관련된 개념을 실습할 수 있는 예제 코드들이 포함되어 있습니다.

## 📁 예제 파일 목록

### 1. `fork_example.c`
**학습 목표**: `fork()`와 `wait()`의 기본 사용법

**내용**:
- 기본적인 `fork()` 호출
- 부모와 자식 프로세스 구분
- `wait()`로 자식 프로세스 종료 대기
- 종료 상태 확인

**컴파일 및 실행**:
```bash
gcc -o fork_example fork_example.c
./fork_example
```

**예상 출력**:
```
=== Fork Example ===
부모 프로세스 시작 (PID: 12345)

[부모] 자식 프로세스 생성 완료 (자식 PID: 12346)
[부모] 자식 프로세스 종료 대기 중...
[자식] PID: 12346, 부모 PID: 12345
[자식] 3초 동안 작업 수행 중...
[자식] 작업 완료, 종료 코드 42로 종료

[부모] 자식 프로세스 12346가 종료됨
[부모] 자식이 정상 종료됨, 종료 코드: 42
[부모] 부모 프로세스 종료
```

---

### 2. `fork_exec_example.c`
**학습 목표**: `fork()`와 `exec()` 계열 함수 조합

**내용**:
- `fork()` 후 `exec()` 호출
- 새로운 프로그램 실행 (`ls -la`)
- 부모가 자식의 종료를 기다림

**컴파일 및 실행**:
```bash
gcc -o fork_exec_example fork_exec_example.c
./fork_exec_example
```

**예상 출력**:
```
=== Fork + Exec Example ===
부모 프로세스 (PID: 12345)에서 'ls -la' 실행

[자식] 'ls -la' 명령어 실행 중...
==========================================
total 128
drwxr-xr-x  5 user user  4096 Jan  5 10:00 .
drwxr-xr-x 12 user user  4096 Jan  5 09:00 ..
-rw-r--r--  1 user user  2048 Jan  5 10:00 fork_example.c
...
==========================================
[부모] 자식 프로세스 종료됨
[부모] ls 명령어 종료 코드: 0
```

---

### 3. `multiple_children.c`
**학습 목표**: 여러 자식 프로세스 관리

**내용**:
- 반복문으로 여러 자식 프로세스 생성
- 각 자식이 다른 작업 수행
- 모든 자식의 종료를 순차적으로 대기

**컴파일 및 실행**:
```bash
gcc -o multiple_children multiple_children.c
./multiple_children
```

**예상 출력**:
```
=== Multiple Children Example ===
부모 프로세스 (PID: 12345)에서 5개의 자식 생성

[부모] 자식 프로세스 1 생성 완료 (PID: 12346)
[자식 1] PID: 12346, 부모 PID: 12345
[자식 1] 2초 동안 작업 수행 중...
[부모] 자식 프로세스 2 생성 완료 (PID: 12347)
...
[부모] 모든 자식 프로세스 생성 완료
[부모] 자식 프로세스들의 종료를 기다립니다...

[자식 1] 작업 완료! 종료 코드: 10
[부모] 자식 프로세스 12346 종료됨, 종료 코드: 10
...
```

---

### 4. `aslr_test.c`
**학습 목표**: ASLR (Address Space Layout Randomization) 이해

**내용**:
- 다양한 메모리 영역의 주소 출력
- ASLR 상태 확인 (Linux)
- PIE 컴파일 여부에 따른 차이 확인

**컴파일 (PIE 활성화)**:
```bash
gcc -fPIE -pie -o aslr_test aslr_test.c
```

**컴파일 (PIE 비활성화)**:
```bash
gcc -no-pie -o aslr_test_nopie aslr_test.c
```

**실행**:
```bash
./aslr_test

# 여러 번 실행하여 주소 변화 확인
for i in {1..3}; do 
  echo "=== 실행 $i ===" 
  ./aslr_test | grep "함수 main"
done
```

**예상 출력**:
```
====================================
   ASLR 테스트 프로그램
====================================

=== ASLR 상태 확인 ===
현재 ASLR 상태: 2 (완전 활성화 - 모든 메모리 영역)

프로세스 ID: 12345

=== 메모리 주소 분석 ===

1. 코드 영역 (Text Segment):
   함수 main():           0x555555555169
   함수 print_addresses(): 0x555555555089
   라이브러리 printf():    0x7ffff7e0f540
   라이브러리 malloc():    0x7ffff7e5c3a0

2. 데이터 세그먼트 (Data Segment):
   전역 변수 (초기화):     0x555555558010 (값: 100)

3. BSS 세그먼트:
   전역 변수 (미초기화):   0x555555558014 (값: 0)

4. 스택 (Stack):
   지역 변수:             0x7fffffffe2bc (값: 42)

5. 힙 (Heap):
   동적 할당 변수:         0x5555555592a0 (값: 84)
```

---

## 🎯 실습 순서 추천

### 1단계: 기초 이해
1. `fork_example.c` 실행
2. 코드를 읽고 출력 결과 분석
3. 부모와 자식의 실행 흐름 이해

### 2단계: exec 이해
1. `fork_exec_example.c` 실행
2. `ls -la`가 어떻게 실행되는지 관찰
3. `execvp()` 이전/이후의 프로세스 상태 이해

### 3단계: 복수 프로세스 관리
1. `multiple_children.c` 실행
2. 5개의 자식이 동시에 실행되는 것 관찰
3. `wait()`가 순차적으로 호출되는 것 확인

### 4단계: 보안 메커니즘
1. `aslr_test.c` (PIE 버전) 여러 번 실행
2. 주소가 매번 달라지는 것 확인
3. PIE 없는 버전과 비교

---

## 🔧 추가 실습 아이디어

### 실습 1: 좀비 프로세스 생성 및 관찰
```c
// zombie_test.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    if (fork() == 0) {
        printf("자식 프로세스 종료\n");
        exit(0);
    }
    
    printf("부모 프로세스가 wait()를 호출하지 않고 30초 대기\n");
    printf("다른 터미널에서 'ps aux | grep Z'로 좀비 확인\n");
    sleep(30);
    
    return 0;
}
```

### 실습 2: 파이프로 부모-자식 통신
```c
// pipe_example.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buffer[100];
    
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    if (fork() == 0) {
        // 자식: 파이프에서 읽기
        close(pipefd[1]);  // 쓰기 끝 닫기
        read(pipefd[0], buffer, sizeof(buffer));
        printf("자식이 받은 메시지: %s\n", buffer);
        close(pipefd[0]);
    } else {
        // 부모: 파이프에 쓰기
        close(pipefd[0]);  // 읽기 끝 닫기
        const char *msg = "Hello from parent!";
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);
        wait(NULL);
    }
    
    return 0;
}
```

### 실습 3: 시그널 처리
```c
// signal_example.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigchld_handler(int sig) {
    printf("SIGCHLD 수신: 자식 프로세스가 종료됨\n");
}

int main() {
    signal(SIGCHLD, sigchld_handler);
    
    if (fork() == 0) {
        printf("자식 프로세스 2초 후 종료\n");
        sleep(2);
        exit(0);
    }
    
    printf("부모 프로세스 대기 중...\n");
    sleep(5);
    printf("부모 프로세스 종료\n");
    
    return 0;
}
```

---

## 🐛 디버깅 팁

### GDB로 fork 디버깅
```bash
gcc -g -o fork_example fork_example.c
gdb ./fork_example

(gdb) set follow-fork-mode child  # 자식 프로세스 추적
(gdb) set follow-fork-mode parent # 부모 프로세스 추적
(gdb) set detach-on-fork off      # 부모/자식 모두 추적
(gdb) break fork
(gdb) run
```

### strace/dtruss로 시스템 콜 추적
```bash
# Linux
strace -f ./fork_example

# macOS
sudo dtruss -f ./fork_example
```

### 프로세스 트리 확인
```bash
# 실행 중인 프로그램의 프로세스 트리
pstree -p $(pgrep fork_example)

# 또는
ps -ejH | grep fork_example
```

---

## 📚 참고 자료

### Man 페이지
```bash
man 2 fork      # fork() 시스템 콜
man 2 execve    # execve() 시스템 콜
man 2 wait      # wait() 시스템 콜
man 2 waitpid   # waitpid() 시스템 콜
man 3 exec      # exec 계열 함수
```

### 관련 문서
- `프로세스 생성.md`: 이론적 배경
- `팩트체크_및_개선사항.md`: 상세한 설명과 추가 자료

---

## ✅ 학습 체크리스트

- [ ] `fork()`의 반환값을 이해했다
- [ ] 부모와 자식 프로세스의 실행 흐름을 이해했다
- [ ] `wait()`의 필요성을 이해했다
- [ ] 좀비 프로세스가 무엇인지 안다
- [ ] `exec()` 계열 함수의 차이를 이해했다
- [ ] `fork()` + `exec()` 패턴을 이해했다
- [ ] Copy-on-Write의 개념을 이해했다
- [ ] ASLR이 무엇인지 이해했다
- [ ] PIE 컴파일이 무엇인지 안다
- [ ] 프로세스 간 통신(IPC)의 필요성을 이해했다

모든 항목을 이해했다면 3장으로 넘어갈 준비가 되었습니다! 🚀

