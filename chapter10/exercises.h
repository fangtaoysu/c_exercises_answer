#ifndef __EXERCISES_H__
#define __EXERCISES_H__


struct Student {
    int id;
    char* name;
};

struct Node {
    Student student;
    Node* next;
};

void delete_a_item(Node* &a, Node* b); // 10.8


#endif