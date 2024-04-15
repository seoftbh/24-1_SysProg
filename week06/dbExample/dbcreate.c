#include <stdio.h>   // ǥ�� ����� �Լ�
#include <stdlib.h>  // ǥ�� ���̺귯�� �Լ� - �޸� �Ҵ�, ���α׷� ����(exit)
#include <unistd.h>  // UNIX ǥ�� API
#include <fcntl.h>   // ���� ���� ���� �Լ� - open, close ��
#include "student.h"

/* �л� ������ �Է¹޾� �����ͺ��̽� ���Ͽ� ���� */
int main(int argc, char *argv[])  // argc: ���� ��, argv: ���� �� �迭
{
    int fd;  // ���� ��ũ���� ������ ����
    struct student record;  // student ����ü �ν��Ͻ�

    /* ���ڰ� �˻� */
    if (argc < 2)  // ����� ���ڰ� ������ ���
    {
        fprintf(stderr, "���� : %s ���ϸ�\n", argv[0]);  // ǥ�� ���� ��Ʈ���� ����� �����
        exit(1);  // ���α׷� ���� �� ���� �ڵ� 1 ��ȯ
    }
    /* ���� ���� */
    if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) == -1)  // ���� ����, ���� ����, ���� ���� ���� ����, fd ������ �˻�
    {
        perror(argv[1]);  // ���� ���� ������ ��� �����޽��� ���
        exit(2);  // ���α׷� ���� �� ���� �ڵ� 2 ��ȯ
    }

    printf("%-9s %-8s %-4s\n", "�й�", "�̸�", "����");  // �� ������ ȭ�鿡 ��� (������ ũ��, ���� ����)

    /* ������ �Է� �� ���� ���� */
    while (scanf("%d %s %d", &record.id, record.name, &record.score) == 3)  // �Է� �ޱ� - ���� �ԷµǸ�, �ݺ��ؼ� �Է� ����
    {
        lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);  // ���� ������ ��ġ �̵�
        write(fd, (char *)&record, sizeof(record));  // ���Ͽ� student ����ü ���
    }

    close(fd);  // ���� ��ũ���� �ݱ�
    exit(0);    // ���α׷� ���� ����
}