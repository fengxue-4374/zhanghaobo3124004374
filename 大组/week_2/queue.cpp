#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义节点结构体
typedef struct Node {
    void* data;          // 指向数据的指针
    struct Node* next;   // 指向下一个节点的指针
} Node;

// 定义队列结构体
typedef struct {
    Node* head;         // 队列头指针
    Node* tail;         // 队列尾指针
    size_t size;        // 队列大小
    size_t data_size;   // 存储的数据类型大小
} Queue;


 // 初始化队列

void queue_init(Queue* q, size_t data_size) {
    q->head = q->tail = NULL;
    q->size = 0;
    q->data_size = data_size;
}

 // 检查队列是否为空

int queue_is_empty(const Queue* q) {
    return q->head == NULL;
}


 // 获取队列大小

size_t queue_size(const Queue* q) {
    return q->size;
}


 // 元素入队

int queue_enqueue(Queue* q, const void* data) {
    // 创建新节点
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return 0;

    // 分配数据内存并复制数据
    new_node->data = malloc(q->data_size);
    if (!new_node->data) {
        free(new_node);
        return 0;
    }
    memcpy(new_node->data, data, q->data_size);

    new_node->next = NULL;

    // 将节点添加到队列尾部
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


 // 元素出队

int queue_dequeue(Queue* q, void* data) {
    if (queue_is_empty(q)) return 0;

    Node* temp = q->head;

    // 如果提供了data指针，则复制数据
    if (data != NULL) {
        memcpy(data, temp->data, q->data_size);
    }

    // 移动头指针
    q->head = q->head->next;

    // 如果队列变空，更新尾指针
    if (q->head == NULL) {
        q->tail = NULL;
    }

    // 释放节点内存
    free(temp->data);
    free(temp);

    q->size--;
    return 1;
}


 // 查看队首元素但不移除

int queue_peek(const Queue* q, void* data) {
    if (queue_is_empty(q)) return 0;

    memcpy(data, q->head->data, q->data_size);
    return 1;
}


 // 清空队列

void queue_clear(Queue* q) {
    while (!queue_is_empty(q)) {
        queue_dequeue(q, NULL);
    }
}


 // @brief 打印整型队列(用于测试)

void queue_print_int(const Queue* q) {
    Node* current = q->head;
    printf("队列内容(大小=%zu): ", q->size);
    while (current != NULL) {
        printf("%d ", *(int*)current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    // 测试整型队列
    Queue int_queue;
    queue_init(&int_queue, sizeof(int));

    printf("测试整型队列:\n");

    // 入队测试
    int values[] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < 5; i++) {
        queue_enqueue(&int_queue, &values[i]);
    }
    queue_print_int(&int_queue);

    // 出队测试
    int dequeued;
    while (queue_dequeue(&int_queue, &dequeued)) {
        printf("出队元素: %d\n", dequeued);
    }

    // 测试空队列
    if (!queue_dequeue(&int_queue, &dequeued)) {
        printf("队列已空，无法出队\n");
    }

    // 测试其他类型(如double)
    Queue double_queue;
    queue_init(&double_queue, sizeof(double));

    printf("\n测试双精度浮点队列:\n");
    double d_values[] = { 1.1, 2.2, 3.3 };
    for (int i = 0; i < 3; i++) {
        queue_enqueue(&double_queue, &d_values[i]);
    }

    double d_val;
    while (queue_dequeue(&double_queue, &d_val)) {
        printf("出队元素: %.2f\n", d_val);
    }

    // 清理队列
    queue_clear(&int_queue);
    queue_clear(&double_queue);

    return 0;
}