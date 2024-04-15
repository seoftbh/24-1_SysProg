#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* �й��� �Է¹޾� �ش� �л��� ���ڵ带 ���Ͽ��� �о� ��� */
int main(int argc, char *argv[])  // argc: ���� ��, argv: ���� ��
{
    int fd, id;
    char c;
    struct student record;

    /* ���ڰ� �˻� */
    if (argc < 2)  // ���� ���� ������ ���
    {
        fprintf(stderr, "���� : %s ���ϸ�\n", argv[0]);  // ǥ�� ���� ��Ʈ���� ���� ���
        exit(1);  // ���� �ڵ� 1�� �Բ� ���α׷� ����
    }
    /* ���� ���� */
    if ((fd = open(argv[1], O_RDONLY)) == -1)  // �ش�Ǵ� ������ �б� ���� ����
    {
        perror(argv[1]);  // ���� ���� ���� -> ���� �޽��� ���
        exit(2);  // ���� �ڵ� 2�� �Բ� ���α׷� ����
    }
    /* �й� �Է����� �л� ���� �˻� */
    do  // Y�� �Է��ϴ� ���� ��� �ݺ�
    {
        printf("\n�˻��� �л��� �й� �Է�:");
        if (scanf("%d", &id) == 1)  // �������� �й� �Է� �ޱ�
        {
            lseek(fd, (id - START_ID) * sizeof(record), SEEK_SET);  // ���� �� �ش� �й����� ������ �̵�

            if ((read(fd, (char *)&record, sizeof(record)) > 0) && (record.id != 0))  // �ش� �й��� �л� ������ ��ȿ���� Ȯ��
                printf("�̸�:%s\t �й�:%d\t ����:%d\n", record.name, record.id, record.score);  // �л� ���� ���
            else
                printf("���ڵ� %d ����\n", id);  // ���ڵ尡 �������� �ʴ� ���
        }
        else
            printf("�Է� ����");  // �Է��� �߸��� ���
        printf("����ϰڽ��ϱ�?(Y/N)");
        scanf(" %c", &c);  // ����� �Է� �ޱ�
    } while (c == 'Y' || c == 'y');  // ������� ���� �޾� �ݺ� ���� ����

    close(fd);  // ���� ��ũ���� �ݱ�
    exit(0);    // ���α׷� ���� ����
}
