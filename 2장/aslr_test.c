/*
 * aslr_test.c
 * ASLR (Address Space Layout Randomization) 확인 프로그램
 * 
 * 컴파일 (PIE 활성화):
 *   gcc -fPIE -pie -o aslr_test aslr_test.c
 * 
 * 컴파일 (PIE 비활성화):
 *   gcc -no-pie -o aslr_test_nopie aslr_test.c
 * 
 * 실행:
 *   ./aslr_test
 * 
 * 여러 번 실행하여 주소 변화 확인:
 *   for i in {1..5}; do echo "=== 실행 $i ==="; ./aslr_test; echo; done
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 전역 변수 (데이터 세그먼트)
int global_initialized = 100;

// 초기화되지 않은 전역 변수 (BSS 세그먼트)
int global_uninitialized;

// 함수 (텍스트/코드 세그먼트)
void print_addresses() {
    // 지역 변수 (스택)
    int stack_var = 42;
    
    // 동적 할당 (힙)
    int *heap_var = (int *)malloc(sizeof(int));
    if (heap_var == NULL) {
        perror("malloc 실패");
        exit(1);
    }
    *heap_var = 84;
    
    printf("프로세스 ID: %d\n\n", getpid());
    
    printf("=== 메모리 주소 분석 ===\n\n");
    
    printf("1. 코드 영역 (Text Segment):\n");
    printf("   함수 main():           %p\n", (void *)main);
    printf("   함수 print_addresses(): %p\n", (void *)print_addresses);
    printf("   라이브러리 printf():    %p\n", (void *)printf);
    printf("   라이브러리 malloc():    %p\n\n", (void *)malloc);
    
    printf("2. 데이터 세그먼트 (Data Segment):\n");
    printf("   전역 변수 (초기화):     %p (값: %d)\n\n", 
           (void *)&global_initialized, global_initialized);
    
    printf("3. BSS 세그먼트:\n");
    printf("   전역 변수 (미초기화):   %p (값: %d)\n\n", 
           (void *)&global_uninitialized, global_uninitialized);
    
    printf("4. 스택 (Stack):\n");
    printf("   지역 변수:             %p (값: %d)\n\n", 
           (void *)&stack_var, stack_var);
    
    printf("5. 힙 (Heap):\n");
    printf("   동적 할당 변수:         %p (값: %d)\n\n", 
           (void *)heap_var, *heap_var);
    
    printf("=== 메모리 레이아웃 (낮은 주소 → 높은 주소) ===\n");
    printf("코드 영역 → 데이터 → BSS → 힙 → ... → 스택\n\n");
    
    free(heap_var);
}

void check_aslr_status() {
    printf("=== ASLR 상태 확인 ===\n\n");
    
#ifdef __linux__
    printf("Linux 시스템에서 ASLR 상태 확인:\n");
    printf("  cat /proc/sys/kernel/randomize_va_space\n");
    printf("  0 = 비활성화, 1 = 부분 활성화, 2 = 완전 활성화\n\n");
    
    FILE *fp = fopen("/proc/sys/kernel/randomize_va_space", "r");
    if (fp) {
        int aslr_status;
        if (fscanf(fp, "%d", &aslr_status) == 1) {
            printf("현재 ASLR 상태: %d ", aslr_status);
            switch (aslr_status) {
                case 0:
                    printf("(비활성화)\n");
                    break;
                case 1:
                    printf("(부분 활성화 - 스택, 힙, 라이브러리)\n");
                    break;
                case 2:
                    printf("(완전 활성화 - 모든 메모리 영역)\n");
                    break;
                default:
                    printf("(알 수 없음)\n");
            }
        }
        fclose(fp);
    } else {
        printf("ASLR 상태 파일을 읽을 수 없습니다.\n");
    }
#elif __APPLE__
    printf("macOS 시스템: ASLR은 기본적으로 활성화되어 있습니다.\n");
#else
    printf("알 수 없는 시스템\n");
#endif
    
    printf("\n");
}

void explain_aslr() {
    printf("=== ASLR이란? ===\n\n");
    printf("ASLR (Address Space Layout Randomization)은\n");
    printf("프로세스가 실행될 때마다 메모리 레이아웃을 랜덤하게 배치하여\n");
    printf("메모리 주소에 의존하는 공격(버퍼 오버플로우, ROP 등)을 방어하는 보안 기법입니다.\n\n");
    
    printf("이 프로그램을 여러 번 실행하면:\n");
    printf("  - ASLR이 활성화되어 있으면: 주소가 매번 달라짐\n");
    printf("  - ASLR이 비활성화되어 있으면: 주소가 항상 같음\n\n");
    
    printf("PIE (Position Independent Executable) 컴파일:\n");
    printf("  - PIE 활성화: 코드 영역도 랜덤화됨\n");
    printf("  - PIE 비활성화: 코드 영역은 고정 주소\n\n");
}

int main(int argc, char *argv[]) {
    printf("====================================\n");
    printf("   ASLR 테스트 프로그램\n");
    printf("====================================\n\n");
    
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'h') {
        explain_aslr();
        return 0;
    }
    
    check_aslr_status();
    print_addresses();
    
    printf("=== 사용 팁 ===\n");
    printf("1. 이 프로그램을 여러 번 실행하여 주소 변화를 관찰하세요:\n");
    printf("   $ for i in {1..3}; do ./aslr_test | grep '함수 main'; done\n\n");
    
    printf("2. PIE 여부 확인:\n");
    printf("   $ file ./aslr_test\n");
    printf("   $ readelf -h ./aslr_test | grep Type\n\n");
    
    printf("3. 프로세스 메모리 맵 확인 (Linux):\n");
    printf("   $ cat /proc/%d/maps\n\n", getpid());
    
    printf("4. ASLR 임시 비활성화 (테스트용, 권장하지 않음):\n");
    printf("   $ sudo sysctl -w kernel.randomize_va_space=0\n");
    printf("   $ sudo sysctl -w kernel.randomize_va_space=2  # 재활성화\n\n");
    
    return 0;
}

