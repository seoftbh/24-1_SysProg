#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* 학번을 입력받아 해당 학생의 레코드를 파일에서 읽어 출력 */
int main(int argc, char *argv[])  // argc: 인자 수, argv: 인자 값
{
    int fd, id;
    char c;
    struct student record;

    /* 인자값 검사 */
    if (argc < 2)  // 인자 값이 부족한 경우
    {
        fprintf(stderr, "사용법 : %s 파일명\n", argv[0]);  // 표준 에러 스트림에 사용법 출력
        exit(1);  // 오류 코드 1과 함께 프로그램 종료
    }
    /* 파일 열기 */
    if ((fd = open(argv[1], O_RDONLY)) == -1)  // 해당되는 파일을 읽기 모드로 열기
    {
        perror(argv[1]);  // 파일 열기 실패 -> 오류 메시지 출력
        exit(2);  // 오류 코드 2와 함께 프로그램 종료
    }
    /* 학번 입력으로 학생 정보 검색 */
    do  // Y를 입력하는 동안 계속 반복
    {
        printf("\n검색할 학생의 학번 입력:");
        if (scanf("%d", &id) == 1)  // 정수형의 학번 입력 받기
        {
            lseek(fd, (id - START_ID) * sizeof(record), SEEK_SET);  // 파일 내 해당 학번으로 포인터 이동

            if ((read(fd, (char *)&record, sizeof(record)) > 0) && (record.id != 0))  // 해당 학번의 학생 정보가 유효한지 확인
                printf("이름:%s\t 학번:%d\t 점수:%d\n", record.name, record.id, record.score);  // 학생 정보 출력
            else
                printf("레코드 %d 없음\n", id);  // 리코드가 존재하지 않는 경우
        }
        else
            printf("입력 오류");  // 입력이 잘못된 경우
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);  // 사용자 입력 받기
    } while (c == 'Y' || c == 'y');  // 사용자의 응답 받아 반복 여부 결정

    close(fd);  // 파일 디스크립터 닫기
    exit(0);    // 프로그램 정상 종료
}
