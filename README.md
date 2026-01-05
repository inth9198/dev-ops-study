# 리눅스 시스템 프로그래밍 스터디

> 운영체제의 핵심 개념과 리눅스 시스템 프로그래밍을 체계적으로 학습하는 프로젝트입니다.

## 📖 프로젝트 소개

이 프로젝트는 리눅스 운영체제의 핵심 개념을 이론과 실습을 통해 학습할 수 있도록 구성되어 있습니다. 각 장마다 개념 설명 문서와 실습 코드를 제공하여 실무에 필요한 시스템 프로그래밍 능력을 기를 수 있습니다.

## 📚 목차

### ✅ 1장: 리눅스 개요
**학습 내용**:
- 커널(Kernel)이란?
- 시스템 콜(System Call)과 래퍼 함수
- CPU 모드: 커널 모드와 사용자 모드
- 시스템 콜 추적 도구 (strace, dtruss)
- 시스템 성능 모니터링 (sar, vm_stat, iostat, top)
- 정적 라이브러리와 공유 라이브러리
- 패키지 관리 도구

**파일**:
- `리눅스 개요.md` - 이론 문서 (537줄)
- `dtruss_guide.txt` - macOS 시스템 콜 추적 가이드 (200줄+)
- `hello.go` - 시스템 콜 추적 실습용 예제

**상태**: ✅ 완료 및 검증됨

---

### ✅ 2장: 프로세스 생성
**학습 내용**:
- 프로세스를 생성하는 목적
- fork() 함수와 Copy-on-Write
- wait()와 waitpid() 함수
- execve()와 exec 계열 함수
- ASLR (Address Space Layout Randomization)
- 프로세스의 부모-자식 관계
- 프로세스 상태와 좀비/고아 프로세스
- 시그널(Signal)과 시그널 핸들러
- 셸 작업 관리 (포그라운드/백그라운드)
- 세션과 프로세스 그룹
- 데몬(Daemon) 프로세스

**파일**:
- `프로세스 생성.md` - 이론 문서 (1400줄+)
- `fork_example.c` - fork()와 wait() 기본 실습
- `fork_exec_example.c` - fork()와 exec() 조합
- `multiple_children.c` - 여러 자식 프로세스 관리
- `aslr_test.c` - ASLR 동작 확인
- `README.md` - 실습 가이드

**상태**: ✅ 완료 및 대폭 확장됨 (60% 이상 내용 추가)

---

### 🔜 3장: 프로세스 간 통신 (IPC) - 예정
**예정 학습 내용**:
- 파이프 (Pipe)
  - 익명 파이프
  - 이름있는 파이프 (FIFO)
- 시그널 (Signal) 심화
  - 시그널 핸들러
  - 시그널 마스킹
- 공유 메모리 (Shared Memory)
  - System V 공유 메모리
  - POSIX 공유 메모리
- 메시지 큐 (Message Queue)
- 소켓 (Socket)
  - Unix Domain Socket
  - 네트워크 소켓

---

### 🔜 4장: 메모리 관리 - 예정
**예정 학습 내용**:
- 가상 메모리
- 페이징과 세그멘테이션
- 메모리 할당 (malloc, brk, mmap)
- 메모리 매핑

---

### 🔜 5장: 파일 시스템 - 예정
**예정 학습 내용**:
- 파일 시스템 구조
- inode와 디렉토리
- 파일 I/O
- I/O 멀티플렉싱

---

## 🎯 학습 목표

1. **개념 이해**: 운영체제와 리눅스 커널의 핵심 개념 이해
2. **실무 능력**: 시스템 프로그래밍 API 사용 능력 습득
3. **문제 해결**: 프로세스, 메모리, I/O 관련 문제 해결 능력
4. **디버깅**: 시스템 레벨 디버깅 도구 활용 능력
5. **보안 이해**: ASLR, DEP 등 시스템 보안 메커니즘 이해

## 🛠️ 개발 환경

### 필요 도구
- **컴파일러**: GCC 또는 Clang
- **디버거**: GDB
- **추적 도구**: 
  - Linux: `strace`, `ltrace`
  - macOS: `dtruss` (DTrace)
- **모니터링**: `top`, `htop`, `ps`, `vmstat`

### 권장 환경
- **Linux**: Ubuntu 20.04 LTS 이상
- **macOS**: 10.15 (Catalina) 이상
- **WSL2**: Windows 사용자를 위한 Linux 환경

## 🚀 빠른 시작

### 1. 예제 코드 컴파일
```bash
cd dev-ops-study/2장

# 기본 컴파일
gcc -o fork_example fork_example.c
gcc -o fork_exec_example fork_exec_example.c
gcc -o multiple_children multiple_children.c

# ASLR 테스트 (PIE 활성화)
gcc -fPIE -pie -o aslr_test aslr_test.c

# 모든 보안 기법 활성화
gcc -fPIE -pie \
    -fstack-protector-strong \
    -D_FORTIFY_SOURCE=2 \
    -Wl,-z,relro,-z,now \
    -o secure_program program.c
```

### 2. 예제 실행
```bash
# fork() 예제
./fork_example

# fork() + exec() 예제
./fork_exec_example

# 여러 자식 프로세스
./multiple_children

# ASLR 테스트
./aslr_test
for i in {1..3}; do ./aslr_test | grep "함수 main"; done
```

### 3. 시스템 콜 추적
```bash
# Linux
strace -o output.log ./fork_example
strace -f ./multiple_children  # 자식 프로세스도 추적

# macOS
sudo dtruss ./fork_example
sudo dtruss -f ./multiple_children
```

## 📊 학습 진행 상황

| 장 | 주제 | 이론 문서 | 실습 코드 | 상태 |
|----|------|----------|----------|------|
| 1장 | 리눅스 개요 | ✅ | ✅ | 완료 |
| 2장 | 프로세스 생성 | ✅ | ✅ | 완료 |
| 3장 | IPC | 🔜 | 🔜 | 예정 |
| 4장 | 메모리 관리 | 🔜 | 🔜 | 예정 |
| 5장 | 파일 시스템 | 🔜 | 🔜 | 예정 |

## 📝 최근 업데이트 (2026-01-05)

### 팩트체크 및 대규모 개선 완료

#### 1장 개선 사항
- ✅ 시스템 콜 목록 확장 및 카테고리화
- ✅ CPU 모드 설명 강화 (5가지 이유로 확장)
- ✅ SIP(System Integrity Protection) 상세 설명
- ✅ strace vs dtruss 비교 테이블 개선

#### 2장 대폭 확장 (60%+ 증가)
- ✅ **wait()/waitpid() 섹션 신규 추가** (완전히 누락되어 있었음)
  - 종료 상태 매크로 설명
  - 좀비 프로세스 방지 3가지 방법
- ✅ **Copy-on-Write 상세 설명 추가**
  - 페이지 테이블과의 관계
  - 성능 이점
- ✅ **exec 계열 함수 비교 테이블**
  - 7가지 함수 체계적 정리
  - 명명 규칙 (l, v, p, e) 설명
- ✅ **ASLR 섹션 3배 확장**
  - PIE 컴파일 설명
  - 실험 코드 제공
  - ASLR의 한계 설명
  - 추가 보안 기법 (DEP, Stack Canary, RELRO)
- ✅ **프로세스 관리 주의사항 확장**
  - Fork Bomb 방어책
  - IPC 메커니즘 5가지 소개

#### dtruss 가이드 완전히 재작성 (10배 확장)
- ✅ 21줄 → 200줄+ 확장
- ✅ 체계적인 매뉴얼 형식으로 재구성
- ✅ 주요 옵션 테이블 추가
- ✅ 다양한 사용 예시
- ✅ SIP 관리 방법 설명
- ✅ 일반적인 오류와 해결 방법
- ✅ Linux strace와의 비교

#### 실습 코드 신규 추가
- ✅ `fork_example.c` - fork()와 wait() 기본
- ✅ `fork_exec_example.c` - fork()와 exec() 조합
- ✅ `multiple_children.c` - 여러 자식 프로세스 관리
- ✅ `aslr_test.c` - ASLR 동작 확인 (완전한 실험 코드)
- ✅ `2장/README.md` - 상세한 실습 가이드

#### 문서화
- ✅ `팩트체크_및_개선사항.md` - 상세한 검토 결과
- ✅ 이 README.md - 프로젝트 전체 구조

자세한 내용은 [`팩트체크_및_개선사항.md`](팩트체크_및_개선사항.md)를 참조하세요.

## 🎓 추천 학습 순서

### 초급 (1-2주)
1. 1장 리눅스 개요 읽기
2. hello.go 실행 및 시스템 콜 추적
3. dtruss/strace 사용법 익히기

### 중급 (2-3주)
1. 2장 프로세스 생성 개념 학습
2. fork_example.c 실습
3. fork_exec_example.c 실습
4. multiple_children.c 실습

### 고급 (2-3주)
1. ASLR 개념 학습 및 aslr_test.c 실험
2. 보안 기법 (DEP, Stack Canary, RELRO) 학습
3. 데몬 프로세스 작성
4. 간단한 셸 구현 프로젝트

## 💡 실습 프로젝트 아이디어

### 프로젝트 1: 간단한 셸 (Mini Shell)
```
난이도: ⭐⭐⭐
예상 시간: 1주
학습 효과: fork, exec, wait, pipe, signal 통합

기능:
- 명령어 파싱 및 실행
- 백그라운드 작업 (&)
- 파이프 (|)
- 리다이렉션 (>, <, >>)
- 시그널 처리 (Ctrl+C, Ctrl+Z)
```

### 프로젝트 2: 프로세스 모니터 (Process Monitor)
```
난이도: ⭐⭐⭐⭐
예상 시간: 1-2주
학습 효과: /proc 파일시스템, 시그널, UI

기능:
- 실시간 프로세스 목록
- CPU/메모리 사용량 표시
- 프로세스 트리 시각화
- 프로세스 종료/일시정지
- 정렬 및 필터링
```

### 프로젝트 3: 멀티프로세스 웹 서버
```
난이도: ⭐⭐⭐⭐⭐
예상 시간: 2-3주
학습 효과: 소켓, fork, I/O, HTTP

기능:
- HTTP/1.1 기본 지원
- 클라이언트마다 fork()
- 정적 파일 서빙
- 로그 기록
- 시그널 처리 (graceful shutdown)
```

## 📚 참고 자료

### 책
1. **"The Linux Programming Interface"** - Michael Kerrisk
   - 리눅스 시스템 프로그래밍의 바이블
   - 1500페이지, 모든 시스템 콜 상세 설명

2. **"Advanced Programming in the UNIX Environment"** - W. Richard Stevens
   - UNIX 시스템 프로그래밍 고전
   - 실용적인 예제 다수

3. **"Operating Systems: Three Easy Pieces"** - Remzi H. Arpaci-Dusseau
   - 운영체제 이론
   - 무료: https://pages.cs.wisc.edu/~remzi/OSTEP/

### 온라인 리소스
- **man 페이지**: `man 2 fork`, `man 2 execve`, `man 7 signal`
- **Linux 커널 문서**: https://www.kernel.org/doc/
- **POSIX 표준**: https://pubs.opengroup.org/

### 실습 환경
- **Linux VM**: VirtualBox + Ubuntu
- **Docker**: 격리된 실습 환경
- **WSL2**: Windows에서 Linux 환경

## 🤝 기여 방법

이 프로젝트는 개인 학습용이지만, 개선 사항이나 오류를 발견하시면:
1. 오류 내용을 문서화
2. 수정 제안
3. 추가 예제 코드 작성

## 📄 라이선스

이 프로젝트는 학습 목적으로 자유롭게 사용할 수 있습니다.

## ✨ 앞으로의 계획

- [ ] 3장: 프로세스 간 통신 (IPC) 작성
- [ ] 4장: 메모리 관리 작성
- [ ] 5장: 파일 시스템 작성
- [ ] 각 장마다 더 많은 실습 예제 추가
- [ ] 프로젝트 기반 학습 자료 추가

---

**Happy Learning! 🚀**

마지막 업데이트: 2026년 1월 5일

