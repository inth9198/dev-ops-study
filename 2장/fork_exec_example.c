/*
 * fork_exec_example.c
 * fork()와 exec() 조합 예제 - 새로운 프로그램 실행
 * 
 * 컴파일: gcc -o fork_exec_example fork_exec_example.c
 * 실행: ./fork_exec_example
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    int status;
    
    printf("=== Fork + Exec Example ===\n");
    printf("부모 프로세스 (PID: %d)에서 'ls -la' 실행\n\n", getpid());
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork 실패");
        exit(1);
        
    } else if (pid == 0) {
        // 자식 프로세스: ls -la 실행
        printf("[자식] 'ls -la' 명령어 실행 중...\n");
        printf("==========================================\n");
        
        // execvp()를 사용하여 ls 실행
        char *args[] = {"ls", "-la", NULL};
        execvp("ls", args);
        
        // execvp()가 성공하면 이 코드는 실행되지 않음
        perror("execvp 실패");
        exit(1);
        
    } else {
        // 부모 프로세스: 자식 종료 대기
        wait(&status);
        
        printf("==========================================\n");
        printf("[부모] 자식 프로세스 종료됨\n");
        
        if (WIFEXITED(status)) {
            printf("[부모] ls 명령어 종료 코드: %d\n", WEXITSTATUS(status));
        }
    }
    
    return 0;
}

