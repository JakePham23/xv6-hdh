#include "kernel/types.h"
#include "user/user.h"
#include "kernel/sysinfo.h" 


void testcall() {
    struct sysinfo info;
    if (sysinfo(&info) < 0) {
        printf("testcall: Failed to get system info\n");
        exit(1);
    }
    printf("testcall: Number of processes: %lu\n\n", info.nproc);  // Sửa thành %lu
}

void testmem() {
    struct sysinfo info;
    if (sysinfo(&info) < 0) {
        printf("testmem: Failed to get system info\n\n");
        exit(1);
    }
    printf("testmem: Number of free memory pages before allocation: %lu\n", info.freemem);  // Sửa thành %lu
    
    char *p = malloc(4096); 
    if (p == 0) {
        printf("testmem: Memory allocation failed\n\n");
        exit(1);
    }

    if (sysinfo(&info) < 0) {
        printf("testmem: Failed to get system info after allocation\n\n");
        free(p); 
        exit(1);
    }
    printf("testmem: Number of free memory pages after allocation: %lu\n", info.freemem);  // Sửa thành %lu
    
    strcpy(p, "Memory test passed!");
    printf("testmem: %s\n\n", p);
    free(p); 
}

void testproc() {
    struct sysinfo info;
    if (sysinfo(&info) < 0) {
        printf("testproc: Failed to get system info\n\n");
        exit(1);
    }
    printf("testproc: Number of processes before fork: %lu\n", info.nproc);  // Sửa thành %lu
    
    int pid = fork(); 
    if (pid < 0) {
        printf("testproc: Fork failed\n");
    } else if (pid == 0) {
        printf("testproc: This is the child process with PID: %d\n", getpid());
        exit(0);
    } else {
        wait(0); 
        if (sysinfo(&info) < 0) {
            printf("testproc: Failed to get system info after fork\n\n");
            exit(1);
        }
        printf("testproc: Number of processes after fork: %lu\n\n", info.nproc);  // Sửa thành %lu
    }
}


int main(int argc, char *argv[]) {
    printf("Starting sysinfotest...\n\n");
    
    testcall(); // Gọi hàm kiểm tra system call
    testmem();  // Gọi hàm kiểm tra bộ nhớ
    testproc(); // Gọi hàm kiểm tra tiến trình

    printf("sysinfotest: OK\n"); // Thông báo tất cả các bài kiểm tra thành công
    exit(0);
}
