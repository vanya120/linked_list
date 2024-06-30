#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <cassert>

#include <listnode.h>

template <class T>
class List
{
private:
    ListNode<T>* first;
    ListNode<T>* last;

public:

    class ListConstIterator
    {
    protected:
        const ListNode<T>* current;

    public:
        explicit ListConstIterator(const ListNode<T>* ptr) :
            current(ptr) {}

    public:
        const T& operator*() const noexcept;
        ListConstIterator& operator++() noexcept;
        ListConstIterator operator++(int) noexcept;
        bool operator==(ListConstIterator other) const noexcept;
        bool operator!=(ListConstIterator other) const noexcept;

    public:
        const ListNode<T>* get() const noexcept
        {
            return current;
        }
    };

    class ListIterator : public ListConstIterator
    {
    public:
        explicit ListIterator(ListNode<T>* ptr) :
            ListConstIterator(ptr) {}

    public:
        T& operator*() const noexcept;
        ListIterator& operator++() noexcept;
        ListIterator operator++(int) noexcept;

    };

public:

    List() : first(nullptr), last(nullptr) {}

    List(std::initializer_list<T> values)
    {
        for (auto& i : values)
            push_back(i);
    }

    ~List()
    {
        while (first)
        {
            auto temp = first;
            first = first->next;
            delete temp;
        }
        last = nullptr;
    }

    bool is_empty() const { return first == nullptr; }

    void push_front(T value)
    {
        ListNode<T>* node = new ListNode<T>(std::move(value));

        if (is_empty()) {
            first = node;
            last = node;
            return;
        }

        node->next = first;
        first = node;
    }

    void push_back(T value)
    {
        ListNode<T>* node = new ListNode<T>(std::move(value));

        if (is_empty()) {
            first = node;
            last = node;
            return;
        }

        last->next = node;
        last = node;
    }

    void insert(ListConstIterator place, T item)
    {
        auto ptr = const_cast<ListNode<T>*>(place.get());
        if (!ptr)
        {
            push_front(std::move(item));
            return;
        }

        ListNode<T>* node = new ListNode<T>(std::move(item));
        node->next = ptr->next;
        ptr->next = node;
    }

    void dump(std::ostream& out) const
    {
        if (is_empty()) { return; }

        for (auto p = first; p != nullptr; p = p->next)
            out << *p << ' ';
        out << '\n';
    }

    ListConstIterator begin() const noexcept
    {
        return ListConstIterator{ first };
    }

    ListConstIterator end() const noexcept
    {
        return ListConstIterator{ nullptr };
    }

    ListIterator begin() noexcept
    {
        return ListIterator{ first };
    }

    ListIterator end() noexcept
    {
        return ListIterator{ nullptr };
    }

    ListConstIterator find(const T& val) const {
        for (auto it = begin(), it_end = end(); it != it_end; ++it)
        {
            if (*it == val)
                return it;
        }
        return ListConstIterator{ nullptr };
    }

    ListIterator find(const T& val) {
        auto it = static_cast<const List &>(*this).find(val);
        return ListIterator{const_cast<ListNode<T>*>(it.get())};
    }

    void remove_first() {
        if (is_empty()) return;
        auto p = first;
        first = p->next;
        delete p;
    }

    void remove_last() {
        if (is_empty()) return;
        if (first == last) {
            remove_first();
            return;
        }
        auto p = first;
        while (p->next != last) {
            p = p->next;
        }
        p->next = nullptr;
        delete last;
        last = p;
    }

    //Удаление по значению
    void remove(T value) {
        if (is_empty()) return;
        if (first->value == value) {
            remove_first();
            return;
        }
        else if (last->value == value) {
            remove_last();
            return;
        }

        auto slow = first;
        auto fast = first->next;

        while (fast && fast->value != value) {
            slow = slow->next;
            fast = fast->next;
        }
        if (!fast) {
            std::cerr << "This element does not exist\n";
            return;
        }
        slow->next = fast->next;
        delete fast;
    }

    //Удаление по итератору
    void erase(ListConstIterator It)
    {
        auto ptr = const_cast<ListNode<T>*>(It.get());
        if (ptr)
        {
            auto Delete = ptr->next;
            if (ptr->next)
            {
                ptr->next = ptr->next->next;
            }
            delete Delete;
        }
        else
        {
            assert(first != nullptr);
            auto temp = first;
            first = first->next;
            delete temp;
        }
    }

    void reversed() {
        ListNode<T>* prev = nullptr;
        while (first) {
            auto link = first;
            first = first->next;
            link->next = prev;
            prev = link;
        }
        first = prev;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& list)
{
    list.dump(out);
    return out;
}

template <typename T>
const T& List<T>::ListConstIterator::operator*() const noexcept
{
    assert(current != nullptr);
    return current->value;
}

template <typename T>
bool List<T>::ListConstIterator::operator==(ListConstIterator other) const noexcept
{
    return current == other.current;
}

template <typename T>
bool List<T>::ListConstIterator::operator!=(ListConstIterator other) const noexcept
{
    return !(*this == other);
}


template <typename T>
typename List<T>::ListConstIterator& List<T>::ListConstIterator::operator++() noexcept
{
    assert(current != nullptr);
    current = current->next;
    return *this;
}

template <typename T>
typename List<T>::ListConstIterator List<T>::ListConstIterator::operator++(int) noexcept
{
    assert(current != nullptr);
    auto copy = *this;
    current = current->next;
    return copy;
}

template <typename T>
T& List<T>::ListIterator::operator*() const noexcept
{
    auto&& res = ListConstIterator::operator *();
    return const_cast<T&>(res);
}

template <typename T>
typename List<T>::ListIterator& List<T>::ListIterator::operator++() noexcept
{
    ListConstIterator::operator ++();
    return *this;
}

template <typename T>
typename List<T>::ListIterator List<T>::ListIterator::operator++(int) noexcept
{
    auto res = ListConstIterator::operator ++(0);
    return ListIterator{ const_cast<ListNode<T>*>(res.get()) };
}



#endif // LIST_H
