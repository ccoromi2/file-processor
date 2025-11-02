// file_processor_clnt.c
// --------------------------------------------
// 프로세스 협력 파일 처리기 - 클라이언트 프로그램
// 지정된 텍스트 파일을 한 줄씩 읽어 서버로 전송하고
// 서버로부터 처리 결과를 받아 출력한다.
// --------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#define FIFO_C2S "fifo_c2s" // Client → Server
#define FIFO_S2C "fifo_s2c" // Server → Client
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <input_file> <mode>\n", argv[0]);
        exit(1);
    }

    char *input_file = argv[1];
    char *mode = argv[2];
    FILE *fp = fopen(input_file, "r");

    if (!fp) {
        perror("파일 열기 실패");
        exit(1);
    }

    int fd_write, fd_read;
    char buf[BUF_SIZE];
    int line_num = 0;
    clock_t start_time, end_time;

    mkfifo(FIFO_C2S, 0666);
    mkfifo(FIFO_S2C, 0666);

    fd_write = open(FIFO_C2S, O_WRONLY);
    fd_read = open(FIFO_S2C, O_RDONLY);

    // 서버에 모드 전송 (첫 메시지)
    write(fd_write, mode, strlen(mode) + 1);

    start_time = clock();

    // 파일을 한 줄씩 읽기
    while (fgets(buf, sizeof(buf), fp)) {
        line_num++;
        printf("%d번째 줄 전송...\n", line_num);

        // 서버로 전송
        write(fd_write, buf, strlen(buf) + 1);

        // 서버로부터 결과 수신
        char result[BUF_SIZE];
        memset(result, 0, sizeof(result));
        read(fd_read, result, sizeof(result));

        printf("%d번째 줄 결과 수신: %s\n", line_num, result);
    }

    // 모든 줄 처리 후 END 전송
    write(fd_write, "END", 4);

    end_time = clock();
    double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\n=== 처리 통계 ===\n");
    printf("처리 모드: %s\n", mode);
    printf("처리한 줄 수: %d줄\n", line_num);
    printf("소요 시간: %.2f초\n", elapsed);

    fclose(fp);
    close(fd_write);
    close(fd_read);

    return 0;
}
