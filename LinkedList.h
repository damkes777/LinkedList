#pragma once

#include <iostream>

using namespace std;

template <typename DATA>
class LinkedList
{
public:
    class Node
    {
    public:
        DATA data;
        Node* prev = nullptr;
        Node* next = nullptr;
    };

    void addAtStart(DATA data)
    {
        Node* n = new Node();
        n->data = data;

        if (head == nullptr)
        {
            head = n;
            tail = n;

            ++nodeCount;
            return;
        }

        head->prev = n;
        n->next = head;
        head = n;

        ++nodeCount;
    }

    void addAtEnd(DATA data)
    {
        Node* n = new Node();
        n->data = data;

        if (head == nullptr)
        {
            head = n;
            tail = n;


            ++nodeCount;
            return;
        }

        tail->next = n;
        n->prev = tail;
        tail = n;

        ++nodeCount;
    }

    void removeFirst()
    {

        if (head == nullptr)
            return;

        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            return;
        }

        if (tail == head)
        {
            delete tail;

            tail = nullptr;
            head = nullptr;

            return;
        }

        Node* tmp = head;
        head = head->next;

        delete tmp;
        --nodeCount;
    }

    void removeLast() {
        if (nodeCount < 0)
        {
            return;
        }

        if (tail == nullptr)
            return;

        if (tail == head)
        {
            delete tail;

            tail = nullptr;
            head = nullptr;

            return;
        }

        if (tail->prev == nullptr)
        {
            delete tail;
            tail = nullptr;
            return;
        }

        Node* tmp = tail;

        tail = tail->prev;
        tail->next = nullptr;

        delete tmp;

        --nodeCount;
    }


    DATA* getDataWidthIndex(int idx)
    {
        if (idx >= nodeCount)
            return nullptr;

        if (head == nullptr)
            return nullptr;

        int it = 0;

        Node* tmp = head;

        while (it != idx)
        {
            if (tmp->next == nullptr)
                return nullptr;

            tmp = tmp->next;
            it++;
        }

        return &tmp->data;
    }

    DATA* getDataWithCompare(DATA data)
    {
        if (data_cmp == nullptr)
            return nullptr;

        if (head == nullptr)
            return nullptr;

        Node* tmp = head;

        while (tmp->next != nullptr)
        {
            if (data_cmp (tmp->data, data) == 0)
                return &tmp->data;

            tmp = tmp->next;
        }

        return nullptr;
    }

    void removeDataWithCompare(DATA data)
    {
        if (head == nullptr)
            return;

        if (data_cmp == nullptr)
            return;

        if (data_cmp(head->data, data) >= 0)
        {
            removeFirst();
            return;
        }

        if (data_cmp(tail->data, data) <= 0)
        {
            removeLast();
            return;
        }

        Node* tmp = head;

        while (tmp->next != nullptr)
        {
            if (data_cmp(tmp->data, data) == 0)
            {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;

                delete tmp;
                return;
            }

            tmp = tmp->next;
        }
    }

    void addDataWithCompare(DATA data)
    {
        if (head == nullptr) {
            addAtStart(data);
            return;
        }

        if (data_cmp == nullptr)
            return;

        if (data_cmp(head->data, data) >= 0)
        {
            addAtStart(data);
            return;
        }

        if (data_cmp(tail->data, data) <= 0)
        {
            addAtEnd(data);
            return;
        }

        Node* tmp = head;

        while (tmp->next != nullptr)
        {
            if (data_cmp(tmp->data, data) < 0 && data_cmp (tmp->next->data, data) > 0)
            {
                Node* n = new Node();
                n->data = data;

                n->prev = tmp->prev;
                n->next = tmp->next;

                tmp->next->prev = n;
                tmp->next = n;

                ++nodeCount;

                return;
            }

            tmp = tmp->next;
        }
    }

    void replaceDataWidthIndex(int idx, DATA data)
    {
        if (idx >= nodeCount)
            return;

        if (head == nullptr)
            return;

        int it = 0;

        Node* tmp = head;

        while (it != idx)
        {
            if (tmp->next == nullptr)
                return;

            tmp = tmp->next;
            it++;
        }

        tmp->data = data;
    }

    void clear()
    {
        if (head == nullptr)
            return;

        if (head == tail)
        {
            delete head;
            delete tail;

            head = nullptr;
            tail = nullptr;
            nodeCount = 0;
            return;
        }

        Node* tmp = head;

        while (tmp != nullptr)
        {
            Node* toDelete = tmp;
            tmp = tmp->next;
            delete toDelete;
        }

        head = nullptr;
        tail = nullptr;
        nodeCount = 0;
    }


    void toString()
    {
        cout << "Liczba elementow: " << nodeCount << endl;

        Node* tmp = head;

        while (tmp != nullptr)
        {
            cout << single_node_to_string (tmp->data) << endl;
            tmp = tmp->next;
        }
    }
    int (*data_cmp)(DATA, DATA);
    string (*single_node_to_string)(DATA);

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int nodeCount = 0;
};