/*
 * multiple_children.c
 * 여러 자식 프로세스를 생성하고 관리하는 예제
 * 
 * 컴파일: gcc -o multiple_children multiple_children.c
 * 실행: ./multiple_children
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_CHILDREN 5

int main() {
    pid_t pids[NUM_CHILDREN];
    int i;
    
    printf("=== Multiple Children Example ===\n");
    printf("부모 프로세스 (PID: %d)에서 %d개의 자식 생성\n\n", 
           getpid(), NUM_CHILDREN);
    
    // 여러 자식 프로세스 생성
    for (i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();
        
        if (pids[i] < 0) {
            perror("fork 실패");
            exit(1);
            
        } else if (pids[i] == 0) {
            // 자식 프로세스
            printf("[자식 %d] PID: %d, 부모 PID: %d\n", 
                   i + 1, getpid(), getppid());
            
            // 각 자식마다 다른 시간 동안 작업
            int work_time = (i + 1) * 2;
            printf("[자식 %d] %d초 동안 작업 수행 중...\n", 
                   i + 1, work_time);
            
            sleep(work_time);
            
            printf("[자식 %d] 작업 완료! 종료 코드: %d\n", 
                   i + 1, i + 10);
            exit(i + 10);  // 각 자식마다 다른 종료 코드
        }
        
        // 부모 프로세스는 계속 반복
        printf("[부모] 자식 프로세스 %d 생성 완료 (PID: %d)\n", 
               i + 1, pids[i]);
    }
    
    printf("\n[부모] 모든 자식 프로세스 생성 완료\n");
    printf("[부모] 자식 프로세스들의 종료를 기다립니다...\n\n");
    
    // 모든 자식 프로세스 종료 대기
    for (i = 0; i < NUM_CHILDREN; i++) {
        int status;
        pid_t child_pid = wait(&status);
        
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("[부모] 자식 프로세스 %d 종료됨, 종료 코드: %d\n", 
                   child_pid, exit_code);
        }
    }
    
    printf("\n[부모] 모든 자식 프로세스가 종료되었습니다\n");
    printf("[부모] 부모 프로세스 종료\n");
    
    return 0;
}

