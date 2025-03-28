#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����ڵ�ṹ��
typedef struct Node {
    void* data;          // ָ�����ݵ�ָ��
    struct Node* next;   // ָ����һ���ڵ��ָ��
} Node;

// ������нṹ��
typedef struct {
    Node* head;         // ����ͷָ��
    Node* tail;         // ����βָ��
    size_t size;        // ���д�С
    size_t data_size;   // �洢���������ʹ�С
} Queue;


 // ��ʼ������

void queue_init(Queue* q, size_t data_size) {
    q->head = q->tail = NULL;
    q->size = 0;
    q->data_size = data_size;
}

 // �������Ƿ�Ϊ��

int queue_is_empty(const Queue* q) {
    return q->head == NULL;
}


 // ��ȡ���д�С

size_t queue_size(const Queue* q) {
    return q->size;
}


 // Ԫ�����

int queue_enqueue(Queue* q, const void* data) {
    // �����½ڵ�
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return 0;

    // ���������ڴ沢��������
    new_node->data = malloc(q->data_size);
    if (!new_node->data) {
        free(new_node);
        return 0;
    }
    memcpy(new_node->data, data, q->data_size);

    new_node->next = NULL;

    // ���ڵ���ӵ�����β��
    if (queue_is_empty(q)) {
        q->head = q->tail = new_node;
    }
    else {
        q->tail->next = new_node;
        q->tail = new_node;
    }

    q->size++;
    return 1;
}


 // Ԫ�س���

int queue_dequeue(Queue* q, void* data) {
    if (queue_is_empty(q)) return 0;

    Node* temp = q->head;

    // ����ṩ��dataָ�룬��������
    if (data != NULL) {
        memcpy(data, temp->data, q->data_size);
    }

    // �ƶ�ͷָ��
    q->head = q->head->next;

    // ������б�գ�����βָ��
    if (q->head == NULL) {
        q->tail = NULL;
    }

    // �ͷŽڵ��ڴ�
    free(temp->data);
    free(temp);

    q->size--;
    return 1;
}


 // �鿴����Ԫ�ص����Ƴ�

int queue_peek(const Queue* q, void* data) {
    if (queue_is_empty(q)) return 0;

    memcpy(data, q->head->data, q->data_size);
    return 1;
}


 // ��ն���

void queue_clear(Queue* q) {
    while (!queue_is_empty(q)) {
        queue_dequeue(q, NULL);
    }
}


 // @brief ��ӡ���Ͷ���(���ڲ���)

void queue_print_int(const Queue* q) {
    Node* current = q->head;
    printf("��������(��С=%zu): ", q->size);
    while (current != NULL) {
        printf("%d ", *(int*)current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    // �������Ͷ���
    Queue int_queue;
    queue_init(&int_queue, sizeof(int));

    printf("�������Ͷ���:\n");

    // ��Ӳ���
    int values[] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < 5; i++) {
        queue_enqueue(&int_queue, &values[i]);
    }
    queue_print_int(&int_queue);

    // ���Ӳ���
    int dequeued;
    while (queue_dequeue(&int_queue, &dequeued)) {
        printf("����Ԫ��: %d\n", dequeued);
    }

    // ���Կն���
    if (!queue_dequeue(&int_queue, &dequeued)) {
        printf("�����ѿգ��޷�����\n");
    }

    // ������������(��double)
    Queue double_queue;
    queue_init(&double_queue, sizeof(double));

    printf("\n����˫���ȸ������:\n");
    double d_values[] = { 1.1, 2.2, 3.3 };
    for (int i = 0; i < 3; i++) {
        queue_enqueue(&double_queue, &d_values[i]);
    }

    double d_val;
    while (queue_dequeue(&double_queue, &d_val)) {
        printf("����Ԫ��: %.2f\n", d_val);
    }

    // �������
    queue_clear(&int_queue);
    queue_clear(&double_queue);

    return 0;
}