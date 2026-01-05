/*
 * fork_example.c
 * fork()와 wait()의 기본 사용법 예제
 * 
 * 컴파일: gcc -o fork_example fork_example.c
 * 실행: ./fork_example
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    int status;
    
    printf("=== Fork Example ===\n");
    printf("부모 프로세스 시작 (PID: %d)\n\n", getpid());
    
    // fork() 호출
    pid = fork();
    
    if (pid < 0) {
        // fork() 실패
        perror("fork 실패");
        exit(1);
        
    } else if (pid == 0) {
        // 자식 프로세스
        printf("[자식] PID: %d, 부모 PID: %d\n", getpid(), getppid());
        printf("[자식] 3초 동안 작업 수행 중...\n");
        
        // 작업 시뮬레이션
        sleep(3);
        
        printf("[자식] 작업 완료, 종료 코드 42로 종료\n");
        exit(42);  // 종료 코드 42
        
    } else {
        // 부모 프로세스
        printf("[부모] 자식 프로세스 생성 완료 (자식 PID: %d)\n", pid);
        printf("[부모] 자식 프로세스 종료 대기 중...\n\n");
        
        // 자식 프로세스 종료 대기
        pid_t child_pid = wait(&status);
        
        printf("\n[부모] 자식 프로세스 %d가 종료됨\n", child_pid);
        
        // 종료 상태 확인
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("[부모] 자식이 정상 종료됨, 종료 코드: %d\n", exit_code);
        } else if (WIFSIGNALED(status)) {
            int signal_num = WTERMSIG(status);
            printf("[부모] 자식이 시그널로 종료됨, 시그널 번호: %d\n", signal_num);
        }
        
        printf("[부모] 부모 프로세스 종료\n");
    }
    
    return 0;
}

