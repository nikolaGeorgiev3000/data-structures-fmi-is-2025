#pragma once

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <iostream>

template <typename T>
class SinglyLinkedList
{
public:
    // Big five
    SinglyLinkedList() = default;
    SinglyLinkedList(const SinglyLinkedList& other);
    SinglyLinkedList(SinglyLinkedList&& other) noexcept;
    SinglyLinkedList& operator=(const SinglyLinkedList& other);
    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept;
    ~SinglyLinkedList();

    // Basic operations
    void pushFront(const T& value);
    void pushBack(const T& value);

    void popFront();

    // Access
    T&       front();
    const T& front() const;
    T&       back();
    const T& back() const;

    // Info
    std::size_t getSize() const;
    bool        isEmpty() const;

    // Iterators
    class SllIterator;
    class ConstSllIterator;

    SllIterator     begin();
    SllIterator     end();
    ConstSllIterator cbegin() const;
    ConstSllIterator cend() const;

    // Insert / erase after iterator
    SllIterator insertAfter(const T& value, const ConstSllIterator& it);
    SllIterator removeAfter(const ConstSllIterator& it);

    // Debug print
    void print() const;

    // Concatenate two lists by stealing their nodes
    template <typename U>
    friend SinglyLinkedList<U> concat(SinglyLinkedList<U>& lhs, SinglyLinkedList<U>& rhs);

private:
    struct Node
    {
        T     data;
        Node* next;

        explicit Node(const T& value)
            : data(value)
            , next(nullptr)
        {}
    };

    Node*      head = nullptr;
    Node*      tail = nullptr;
    std::size_t size = 0;

    void copyFrom(const SinglyLinkedList& other);
    void moveFrom(SinglyLinkedList&& other);
    void free();

public:
    // Forward iterator
    class SllIterator
    {
        Node* currentElementPtr = nullptr;
        friend class SinglyLinkedList;

    public:
        using iterator_category = std::forward_iterator_tag;

        explicit SllIterator(Node* ptr = nullptr)
            : currentElementPtr(ptr)
        {}

        T& operator*()
        {
            return currentElementPtr->data;
        }

        T* operator->()
        {
            return &currentElementPtr->data;
        }

        SllIterator& operator++()
        {
            if (currentElementPtr)
                currentElementPtr = currentElementPtr->next;
            return *this;
        }

        SllIterator operator++(int)
        {
            SllIterator copy(*this);
            ++(*this);
            return copy;
        }

        SllIterator& operator+=(std::size_t s)
        {
            while (s--)
                ++(*this);
            return *this;
        }

        SllIterator operator+(int i) const
        {
            SllIterator res(*this);
            return res += i;
        }

        bool operator==(const SllIterator& rhs) const
        {
            return currentElementPtr == rhs.currentElementPtr;
        }

        bool operator!=(const SllIterator& rhs) const
        {
            return !(*this == rhs);
        }
    };

    // Const forward iterator
    class ConstSllIterator
    {
        const Node* currentElementPtr = nullptr;
        friend class SinglyLinkedList;

    public:
        using iterator_category = std::forward_iterator_tag;

        ConstSllIterator() = default;

        explicit ConstSllIterator(const Node* ptr)
            : currentElementPtr(ptr)
        {}

        ConstSllIterator(const SllIterator& it)
            : currentElementPtr(it.currentElementPtr)
        {}

        const T& operator*() const
        {
            return currentElementPtr->data;
        }

        const T* operator->() const
        {
            return &currentElementPtr->data;
        }

        ConstSllIterator& operator++()
        {
            if (currentElementPtr)
                currentElementPtr = currentElementPtr->next;
            return *this;
        }

        ConstSllIterator operator++(int)
        {
            ConstSllIterator copy(*this);
            ++(*this);
            return copy;
        }

        ConstSllIterator& operator+=(std::size_t s)
        {
            while (s--)
                ++(*this);
            return *this;
        }

        ConstSllIterator operator+(int i) const
        {
            ConstSllIterator res(*this);
            return res += i;
        }

        bool operator==(const ConstSllIterator& rhs) const
        {
            return currentElementPtr == rhs.currentElementPtr;
        }

        bool operator!=(const ConstSllIterator& rhs) const
        {
            return !(*this == rhs);
        }
    };
};

// ===== Basic operations =====

template <typename T>
void SinglyLinkedList<T>::pushFront(const T& value)
{
    Node* newNode = new Node(value);

    if (isEmpty())
        head = tail = newNode;
    else
    {
        newNode->next = head;
        head = newNode;
    }
    ++size;
}

template <typename T>
void SinglyLinkedList<T>::pushBack(const T& value)
{
    Node* newNode = new Node(value);

    if (isEmpty())
        head = tail = newNode;
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    ++size;
}

template <typename T>
void SinglyLinkedList<T>::popFront()
{
    if (!head)
        throw std::logic_error("Empty list");

    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }
    --size;
}

// ===== Access =====

template <typename T>
const T& SinglyLinkedList<T>::front() const
{
    if (!head)
        throw std::logic_error("Empty list");
    return head->data;
}

template <typename T>
const T& SinglyLinkedList<T>::back() const
{
    if (!tail)
        throw std::logic_error("Empty list");
    return tail->data;
}

template <typename T>
T& SinglyLinkedList<T>::front()
{
    if (!head)
        throw std::logic_error("Empty list");
    return head->data;
}

template <typename T>
T& SinglyLinkedList<T>::back()
{
    if (!tail)
        throw std::logic_error("Empty list");
    return tail->data;
}

// ===== Info =====

template <typename T>
std::size_t SinglyLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
bool SinglyLinkedList<T>::isEmpty() const
{
    return size == 0;
}

// ===== Concatenate (steals nodes) =====

template <typename T>
SinglyLinkedList<T> concat(SinglyLinkedList<T>& lhs, SinglyLinkedList<T>& rhs)
{
    SinglyLinkedList<T> result;

    if (!lhs.head)
    {
        result.head = rhs.head;
        result.tail = rhs.tail;
    }
    else if (!rhs.head)
    {
        result.head = lhs.head;
        result.tail = lhs.tail;
    }
    else
    {
        lhs.tail->next = rhs.head;
        result.head = lhs.head;
        result.tail = rhs.tail;
    }

    result.size = lhs.size + rhs.size;

    lhs.head = lhs.tail = nullptr;
    rhs.head = rhs.tail = nullptr;
    lhs.size = rhs.size = 0;

    return result;
}

// ===== Iterators interface =====

template <typename T>
typename SinglyLinkedList<T>::SllIterator SinglyLinkedList<T>::begin()
{
    return SllIterator(head);
}

template <typename T>
typename SinglyLinkedList<T>::SllIterator SinglyLinkedList<T>::end()
{
    return SllIterator(nullptr);
}

template <typename T>
typename SinglyLinkedList<T>::ConstSllIterator SinglyLinkedList<T>::cbegin() const
{
    return ConstSllIterator(head);
}

template <typename T>
typename SinglyLinkedList<T>::ConstSllIterator SinglyLinkedList<T>::cend() const
{
    return ConstSllIterator(nullptr);
}

// ===== Insert / remove after =====

template <typename T>
typename SinglyLinkedList<T>::SllIterator
SinglyLinkedList<T>::insertAfter(const T& value, const ConstSllIterator& it)
{
    if (it == cend())
        return end();

    Node* itNode = const_cast<Node*>(it.currentElementPtr);
    Node* newNode = new Node(value);

    newNode->next = itNode->next;
    itNode->next = newNode;

    if (itNode == tail)
        tail = newNode;

    ++size;
    return SllIterator(newNode);
}

template <typename T>
typename SinglyLinkedList<T>::SllIterator
SinglyLinkedList<T>::removeAfter(const ConstSllIterator& it)
{
    if (it == cend() || getSize() <= 1)
        return end();

    Node* base = const_cast<Node*>(it.currentElementPtr);
    Node* toDelete = base->next;

    if (!toDelete)
        return end();

    Node* newNext = toDelete->next;
    base->next = newNext;

    if (toDelete == tail)
        tail = base;

    delete toDelete;
    --size;

    return SllIterator(newNext);
}

// ===== Big five =====

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
{
    copyFrom(other);
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other) noexcept
{
    moveFrom(std::move(other));
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    free();
}

// ===== Helpers =====

template <typename T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList<T>& other)
{
    Node* iter = other.head;
    while (iter)
    {
        pushBack(iter->data);
        iter = iter->next;
    }
}

template <typename T>
void SinglyLinkedList<T>::moveFrom(SinglyLinkedList<T>&& other)
{
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = other.tail = nullptr;
    other.size = 0;
}

template <typename T>
void SinglyLinkedList<T>::free()
{
    Node* iter = head;
    while (iter)
    {
        Node* toDelete = iter;
        iter = iter->next;
        delete toDelete;
    }
    head = tail = nullptr;
    size = 0;
}

template <typename T>
void SinglyLinkedList<T>::print() const
{
    Node* iter = head;
    while (iter)
    {
        std::cout << iter->data;
        if (iter->next)
            std::cout << " -> ";
        iter = iter->next;
    }
    std::cout << '\n';
}