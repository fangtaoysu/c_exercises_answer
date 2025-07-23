#include "exercises.h"
#include <gtest/gtest.h>


bool is_same_name(Node* a, Node* b) {
    char* name1 = a->student.name, *name2 = b->student.name;
    while (*name1 && *name2) {
        if (*name1++ != *name2++) {
            return false;
        }
    }
    return !(*name1) && !(*name2);
}

// 10.8 
void delete_a_item(Node* &a, Node* b) {
    Node* ptr_b = b;
    while (ptr_b) {
        Node* current = a;
        Node* prev = nullptr; // 刚开始没有头结点，因此前一个节点是空
        while (current) {
            if (is_same_name(current, ptr_b)) {
                if (prev == nullptr) { // 处理前一个节点是空的情况
                    Node* tmp = a;
                    a = a -> next;
                    delete[] tmp -> student.name;
                    delete tmp;
                    current = a;
                } else { // 处理前一个节点存在的情况
                    prev -> next = current -> next;
                    delete[] current -> student.name;
                    delete current;
                    current = prev->next;
                }
            } else {
                prev = current;
                current = current->next;
            }
        }
        ptr_b = ptr_b->next;
    }
}





int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}