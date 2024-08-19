#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <QString>
#include <QStringList>
#include <QHash>
#include <QPair>
#include <vector>
#include <algorithm>

template <typename T>
struct Node
{
    T data_;
    Node* nextNode_;

    Node(T data) : data_(data), nextNode_(nullptr)
    {
    }

    QString first() const
    {
        return data_.first;
    }

    int second() const
    {
        return data_.second;
    }
};

template <typename T>
class LinkedList
{
private:
    Node<T>* head_;

public:
    LinkedList();
    ~LinkedList();

    void append(T data);
    LinkedList<QPair<QString, int>> countWords();
    void sort();
    QString listToStr() const;
};


template <typename T>
LinkedList<T>::LinkedList() : head_(nullptr) {}

template <typename T>
LinkedList<T>::~LinkedList()
{
    while (head_)
    {
        Node<T>* temporary = head_;
        head_ = head_->nextNode_;
        delete temporary;
    }
}

template <typename T>
void LinkedList<T>::append(T data)
{
    Node<T>* newNode = new Node<T>(data);
    if(!head_)
    {
        head_ = newNode;
        return;
    }
    Node<T>* currentNode = head_;
    while(currentNode->nextNode_)
    {
        currentNode = currentNode->nextNode_;
    }
    currentNode->nextNode_ = newNode;
}

template <typename T>
LinkedList<QPair<QString, int>> LinkedList<T>::countWords()
{
    QHash<QString, int> countMap;
    Node<T>* current = head_;
    while (current)
    {
        countMap[current->data_]++; // считаю колличество слов использую QHash
        current = current->nextNode_;
    }
    LinkedList<QPair<QString, int>> resultList;
    for (auto it = countMap.begin(); it != countMap.end(); ++it)
    {
        resultList.append(QPair<QString, int>(it.key(), it.value())); // закидываю в свой
    }
    resultList.sort(); // сортирую по колличеству и в алфавитном
    return resultList;
}

template <typename T>
void LinkedList<T>::sort()
{
    if (!head_ || !head_->nextNode_) return;
    std::vector<T> elements; // использую в вектор из-за sort()
    Node<T>* current = head_;
    while (current)
    {
        elements.push_back(current->data_); // пока нода есть закидываю в vector
        current = current->nextNode_;
    }

    std::sort(elements.begin(), elements.end(), [](const T& a, const T& b) {
        if (a.second == b.second) // если колличестов слов одинаковое
        {
            return a.first < b.first; // сравниваю строки ( a - самое маленькое значение z - самое большое )
        }
        return a.second > b.second;
    });

    head_ = nullptr;
    for (const auto& element : elements)
    {
        append(element); // добавляю в свой лист
    }
}

template <typename T>
QString LinkedList<T>::listToStr() const
{
    QString result;
    Node<T>* current = head_;
    while (current)
    {
        result += QString("word: %1\t count: %2 \n").arg(current->first()).arg(current->second());
        current = current->nextNode_;
    }
    return result;
}

#endif
