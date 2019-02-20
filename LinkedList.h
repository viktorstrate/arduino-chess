//
// Created by Viktor Hundahl Strate on 19/02/2019.
//


#pragma once

#include "logger.h"

template <typename T>
class LinkedList
{
public:
    T value;
    LinkedList<T>* next;

    LinkedList();

    explicit LinkedList(T item);

    ~LinkedList() = default;

    void freeList();

    void push(const T& item);

    void printList();

    bool contains(const T& item);

    bool end();

private:
    bool initialized;
};

template<typename T>
LinkedList<T>::LinkedList() : next(nullptr), initialized(false) {}

template<typename T>
LinkedList<T>::LinkedList(T item) : value(item), next(nullptr), initialized(true)
{}

template<typename T>
void LinkedList<T>::freeList()
{
    LinkedList<T>* n = next;

    while(n != nullptr)
    {
        LinkedList<T>* temp = n;
        delete n;
        n = temp->next;
    }
}

template<typename T>
void LinkedList<T>::push(const T& item)
{
    if (!initialized)
    {
        this->value = item;
        initialized = true;
        return;
    }

    auto* link = new LinkedList(item);

    LinkedList<T>* tail = this;

    while(tail->next != nullptr) {
        tail = tail->next;
    }

    tail->next = link;
}

template<typename T>
bool LinkedList<T>::contains(const T& item)
{
    LinkedList<T>* head = this;

    while (head != nullptr) {
        if (head->value == item) return true;
        head = head->next;
    }

    return false;
}

template<typename T>
void LinkedList<T>::printList()
{
    if (!initialized) {
        println(";");
        return;
    }

    print(value);

    if (next == nullptr) {
        println("");
        return;
    }

    print(", ");

    next->printList();
}

template<typename T>
bool LinkedList<T>::end()
{
    return !initialized;
}
