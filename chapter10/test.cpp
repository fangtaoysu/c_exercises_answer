#include "exercises.h"
#include <gtest/gtest.h>
#include <cstring>  // for strcpy



// 辅助函数：创建链表节点
Node* create_node(int id, const char* name) {
    Node* node = new Node;
    node->student.id = id;
    node->student.name = new char[strlen(name) + 1];
    strcpy(node->student.name, name);
    node->next = nullptr;
    return node;
}

// 辅助函数：释放链表内存
void free_list(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete[] temp->student.name;
        delete temp;
    }
}

TEST(DeleteAItemTest, BasicCase) {
    // 创建链表 a: 1->2->3->4
    Node* a = create_node(1, "Alice");
    a->next = create_node(2, "Bob");
    a->next->next = create_node(3, "Charlie");
    a->next->next->next = create_node(4, "David");
    a->next->next->next->next = nullptr;
    // 创建链表 b: 2->4
    Node* b = create_node(2, "Bob");
    b->next = create_node(4, "David");
    b->next->next = nullptr;
    delete_a_item(a, b);

    // 验证结果
    ASSERT_NE(a, nullptr);
    EXPECT_EQ(a->student.id, 1);
    ASSERT_NE(a->next, nullptr);
    EXPECT_EQ(a->next->student.id, 3);
    EXPECT_EQ(a->next->next, nullptr);

    free_list(a);
    free_list(b);
}

TEST(DeleteAItemTest, NoCommonItems) {
    // 创建链表 a: 1->2->3
    Node* a = create_node(1, "Alice");
    a->next = create_node(2, "Bob");
    a->next->next = create_node(3, "Charlie");
    a->next->next->next = nullptr;

    // 创建链表 b: 4->5
    Node* b = create_node(4, "Diana");
    b->next = create_node(5, "Eve");
    b->next->next = nullptr;

    delete_a_item(a, b);

    // 验证结果（链表a应保持不变）
    ASSERT_NE(a, nullptr);
    EXPECT_EQ(a->student.id, 1);
    ASSERT_NE(a->next, nullptr);
    EXPECT_EQ(a->next->student.id, 2);
    ASSERT_NE(a->next->next, nullptr);
    EXPECT_EQ(a->next->next->student.id, 3);
    EXPECT_EQ(a->next->next->next, nullptr);

    free_list(a);
    free_list(b);
}

TEST(DeleteAItemTest, DeleteFirstNode) {
    // 创建链表 a: 1->2->3
    Node* a = create_node(1, "Alice");
    a->next = create_node(2, "Bob");
    a->next->next = create_node(3, "Charlie");
    a->next->next->next = nullptr;

    // 创建链表 b: 1
    Node* b = create_node(1, "Alice");
    b->next = nullptr;

    delete_a_item(a, b);

    // 验证结果
    ASSERT_NE(a, nullptr);
    EXPECT_EQ(a->student.id, 2);
    ASSERT_NE(a->next, nullptr);
    EXPECT_EQ(a->next->student.id, 3);
    EXPECT_EQ(a->next->next, nullptr);

    free_list(a);
    free_list(b);
}

TEST(DeleteAItemTest, DeleteAllNodes) {
    // 创建链表 a: 1->2->3
    Node* a = create_node(1, "Alice");
    a->next = create_node(2, "Bob");
    a->next->next = create_node(3, "Charlie");
    a->next->next->next = nullptr;

    // 创建链表 b: 1->2->3
    Node* b = create_node(1, "Alice");
    b->next = create_node(2, "Bob");
    b->next->next = create_node(3, "Charlie");
    b->next->next->next = nullptr;

    delete_a_item(a, b);

    // 验证结果（链表a应为空）
    EXPECT_EQ(a, nullptr);

    free_list(b);  // a已经被删除
}

TEST(DeleteAItemTest, EmptyListB) {
    // 创建链表 a: 1->2->3
    Node* a = create_node(1, "Alice");
    a->next = create_node(2, "Bob");
    a->next->next = create_node(3, "Charlie");
    a->next->next->next = nullptr;

    // 创建空链表 b
    Node* b = nullptr;

    delete_a_item(a, b);

    // 验证结果（链表a应保持不变）
    ASSERT_NE(a, nullptr);
    EXPECT_EQ(a->student.id, 1);
    ASSERT_NE(a->next, nullptr);
    EXPECT_EQ(a->next->student.id, 2);
    ASSERT_NE(a->next->next, nullptr);
    EXPECT_EQ(a->next->next->student.id, 3);
    EXPECT_EQ(a->next->next->next, nullptr);

    free_list(a);
}

TEST(DeleteAItemTest, EmptyListA) {
    // 创建空链表 a
    Node* a = nullptr;

    // 创建链表 b: 1->2->3
    Node* b = create_node(1, "Alice");
    b->next = create_node(2, "Bob");
    b->next->next = create_node(3, "Charlie");
    b->next->next->next = nullptr;
    
    delete_a_item(a, b);

    // 验证结果（a应仍为空）
    EXPECT_EQ(a, nullptr);

    free_list(b);
}
