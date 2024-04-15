#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* �й��� �Է¹޾� �ش� �л� ���ڵ带 ���� */
int main(int argc, char *argv[]) // ���� �ޱ�
{
    int fd, id;
    char c;
    struct student record;

    /* ���ڰ� �˻� */
    if (argc < 2)
    {
        fprintf(stderr, "���� : %s ���ϸ�\n", argv[0]);
        exit(1);
    }
    /* ���� ���� */
    if ((fd = open(argv[1], O_RDWR)) == -1)  // �б� �� ���� ���� ���� ����
    {
        perror(argv[1]);  // ���� ���� ������ ��� ���� �޽��� ���
        exit(2);  // ���� �ڵ� 2�� �Բ� ���α׷� ����
    }
    /* �й� �Է� �� ���ڵ� �����ϱ� */
    do  // Y�� �Է��ϴ� ���� ��� �ݺ�
    {
        printf("������ �л��� �й� �Է�: ");  
        if (scanf("%d", &id) == 1)  // ������ �л��� �й� �Է� �ޱ�
        {
            lseek(fd, (long)(id - START_ID) * sizeof(record), SEEK_SET);  // ���Ͽ��� �ش� �й��� ��ġ�� ������ �̵�
            if ((read(fd, (char *)&record, sizeof(record)) > 0) && (record.id != 0))  // �л� �������� �ش� �й��� ��ȿ���� Ȯ��
            {
                printf("�й�:%8d\t �̸�:%4s\t ����:%4d\n", record.id, record.name, record.score);  // ���� �� �л� ���� ���
                printf("���ο� ����: ");  // ���ο� ���� �Է� �ޱ�
                scanf("%d", &record.score);
                lseek(fd, (long)-sizeof(record), SEEK_CUR);  // ���� ���� ������ ��ġ���� ���ڵ� ũ�⸸ŭ ���������� �̵�
                write(fd, (char *)&record, sizeof(record));  // ������ ���ڵ带 ���Ͽ� ���
            }
            else  // �й��� �ش��ϴ� ���ڵ尡 ���� ���
                printf("���ڵ� %d ����\n", id);
        }
        else  // �Է� ����
            printf("�Է¿���\n");
        printf("����ϰڽ��ϱ�?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y' || c == 'y');  // ������� ���� �޾� �ݺ� ���� ����

    close(fd);  // ���� ��ũ���� �ݱ�
    exit(0);    // ���α׷� ���� ����
}
