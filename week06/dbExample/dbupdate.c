#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* 학번을 입력받아 해당 학생 레코드를 수정 */
int main(int argc, char *argv[]) // 인자 받기
{
    int fd, id;
    char c;
    struct student record;

    /* 인자값 검사 */
    if (argc < 2)
    {
        fprintf(stderr, "사용법 : %s 파일명\n", argv[0]);
        exit(1);
    }
    /* 파일 열기 */
    if ((fd = open(argv[1], O_RDWR)) == -1)  // 읽기 및 쓰기 모드로 파일 열기
    {
        perror(argv[1]);  // 파일 열기 실패한 경우 오류 메시지 출력
        exit(2);  // 오류 코드 2와 함께 프로그램 종료
    }
    /* 학번 입력 및 레코드 수정하기 */
    do  // Y를 입력하는 동안 계속 반복
    {
        printf("수정할 학생의 학번 입력: ");  
        if (scanf("%d", &id) == 1)  // 수정할 학생의 학번 입력 받기
        {
            lseek(fd, (long)(id - START_ID) * sizeof(record), SEEK_SET);  // 파일에서 해당 학번의 위치로 포인터 이동
            if ((read(fd, (char *)&record, sizeof(record)) > 0) && (record.id != 0))  // 학생 정보에서 해당 학번이 유효한지 확인
            {
                printf("학번:%8d\t 이름:%4s\t 점수:%4d\n", record.id, record.name, record.score);  // 수정 전 학생 정보 출력
                printf("새로운 점수: ");  // 새로운 점수 입력 받기
                scanf("%d", &record.score);
                lseek(fd, (long)-sizeof(record), SEEK_CUR);  // 현재 파일 포인터 위치에서 레코드 크기만큼 역방향으로 이동
                write(fd, (char *)&record, sizeof(record));  // 수정된 레코드를 파일에 기록
            }
            else  // 학번에 해당하는 레코드가 없는 경우
                printf("레코드 %d 없음\n", id);
        }
        else  // 입력 오류
            printf("입력오류\n");
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y' || c == 'y');  // 사용자의 응답 받아 반복 여부 결정

    close(fd);  // 파일 디스크립터 닫기
    exit(0);    // 프로그램 정상 종료
}
