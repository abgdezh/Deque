//https://github.com/abgdezh/Deque

#include <cstring>
#include <iostream>

template<class T>
class Deque {
public:
    Deque() : data(0), capacity(0), posBegin(0), posEnd(0) {}

    Deque(const Deque<T> &rhs) : data(new T[rhs.size()]), capacity(rhs.size()), posBegin(0), posEnd(rhs.size() - 1) {
        for (size_t i = 0; i < capacity; ++i)
            data[i] = rhs[i];
    }

    ~Deque() {
        if (data)
            delete[] data;
    }

    Deque<T> &operator=(const Deque<T> &rhs) {
        if (&rhs == this)
            return *this;
        capacity = rhs.size();
        posBegin = 0;
        posEnd = capacity - 1;
        if (data)
            delete[] data;
        data = new T[capacity];
        for (size_t i = 0; i < capacity; ++i)
            data[i] = rhs[i];
        return *this;
    }

    void push_back(const T &value) {
        ensureCapacityAtPush();
        posEnd = (posEnd + 1) % capacity;
        data[posEnd] = value;
    }

    void pop_back() {
        ensureCapacityAtPop();
        if (capacity)
            posEnd = (posEnd - 1 + capacity) % capacity;
    }

    void push_front(const T &value) {
        ensureCapacityAtPush();
        posBegin = (posBegin - 1 + capacity) % capacity;
        data[posBegin] = value;
    }

    void pop_front() {
        ensureCapacityAtPop();
        if (capacity)
            posBegin = (posBegin + 1) % capacity;
    }

    T &operator[](size_t pos) {
        return data[(posBegin + pos) % capacity];
    }

    const T &operator[](size_t pos) const {
        return data[(posBegin + pos) % capacity];
    }

    T &front() {
        return data[posBegin];
    }

    const T &front() const {
        return data[posBegin];
    }

    T &back() {
        return data[posEnd];
    }

    const T &back() const {
        return data[posEnd];
    }

    bool empty() const {
        return size() == 0;
    }

    size_t size() const {
        if (!data)
            return 0;
        return posEnd >= posBegin ? posEnd - posBegin + 1 : capacity - (posBegin - posEnd - 1);
    }

private:
    template<typename valueType, typename dequeType, int direction>
    class genericDequeIterator : public std::iterator<std::random_access_iterator_tag, valueType> {
    public:
        genericDequeIterator(long long pos, dequeType *deque) : pos(pos), deque(deque) {}

        valueType &operator*() {
            return (*deque)[pos];
        }

        valueType *operator->() {
            return &(operator*());
        }

        valueType &operator[](int n) {
            return direction > 0 ? (*deque)[pos + n] : (*deque)[pos - n];
        }

        genericDequeIterator<valueType, dequeType, direction> &operator++() {
            pos += direction;
            return *this;
        }

        genericDequeIterator<valueType, dequeType, direction> &operator--() {
            pos -= direction;
            return *this;
        }

        genericDequeIterator<valueType, dequeType, direction> operator++(int) {
            genericDequeIterator<valueType, dequeType, direction> result = *this;
            ++(*this);
            return result;
        }

        genericDequeIterator<valueType, dequeType, direction> operator--(int) {
            genericDequeIterator<valueType, dequeType, direction> result = *this;
            --(*this);
            return result;
        }

        genericDequeIterator<valueType, dequeType, direction> &operator+=(long long difference) {
            pos += direction > 0 ? difference : -difference;
            return *this;
        }

        genericDequeIterator<valueType, dequeType, direction> &operator-=(long long difference) {
            pos -= direction > 0 ? difference : -difference;
            return *this;
        }

        genericDequeIterator<valueType, dequeType, direction> operator+(long long difference) const {
            genericDequeIterator<valueType, dequeType, direction> result = *this;
            return result += difference;
        }

        genericDequeIterator<valueType, dequeType, direction> operator-(long long difference) const {
            genericDequeIterator<valueType, dequeType, direction> result = *this;
            return result -= difference;
        }

        long long operator-(const genericDequeIterator<valueType, dequeType, direction> &rhs) const {
            return direction > 0 ? pos - rhs.pos : rhs.pos - pos;
        }

        bool operator==(const genericDequeIterator<valueType, dequeType, direction> &rhs) const {
            return pos == rhs.pos && deque == rhs.deque;
        }

        bool operator!=(const genericDequeIterator<valueType, dequeType, direction> &rhs) const {
            return !(rhs == *this);
        }

        bool operator<(const genericDequeIterator<valueType, dequeType, direction> &rhs) const {
            return direction > 0 ? pos < rhs.pos : pos > rhs.pos;
        }

        bool operator>(const genericDequeIterator &rhs) const {
            return rhs < *this;
        }

        bool operator<=(const genericDequeIterator &rhs) const {
            return !(rhs < *this);
        }

        bool operator>=(const genericDequeIterator &rhs) const {
            return !(*this < rhs);
        }

    private:
        long long pos;
        dequeType *deque;
    };

public:

    typedef genericDequeIterator<T, Deque, 1> iterator;

    typedef genericDequeIterator<const T, const Deque, 1> const_iterator;

    typedef genericDequeIterator<T, Deque, -1> reverse_iterator;

    typedef genericDequeIterator<const T, const Deque, -1> const_reverse_iterator;

    iterator begin() {
        return iterator(0, this);
    }

    const_iterator begin() const {
        return const_iterator(0, this);
    }

    const_iterator cbegin() const {
        return const_iterator(0, this);
    }

    iterator end() {
        return iterator(size(), this);
    }

    const_iterator end() const {
        return const_iterator(size(), this);
    }

    const_iterator cend() const {
        return const_iterator(size(), this);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(size() - 1, this);
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(size() - 1, this);
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(size() - 1, this);
    }

    reverse_iterator rend() {
        return reverse_iterator(-1, this);
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(-1, this);
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(-1, this);
    }

    /*void print() const {
        std::cout << data << ' ' << capacity << ' ' << posBegin << ' ' << posEnd << '\n';
        std::cout << '[';
        for (size_t i = 0; i < size(); ++i) {
            std::cout << operator[](i) << (i + 1 != size() ? ", " : "");
        }
        std::cout << "]\n";
    }*/

private:
    T *data;
    size_t capacity;
    size_t posBegin;
    size_t posEnd;

    const size_t MIN_RESIZE = 10;

    const double RESIZE_FACTOR = 1.5;

    void resize(size_t newCapacity) {
        T *newData = new T[newCapacity];
        if (!size()) {
            data = newData;
            capacity = newCapacity;
            posBegin = 0;
            posEnd = capacity - 1;
            return;
        }
        if (posBegin <= posEnd) {
            memcpy(static_cast<void *>(newData), static_cast<void *>(data + posBegin),
                   (posEnd - posBegin + 1) * sizeof(T));
        } else {
            size_t frontElements = (capacity - posBegin);
            size_t backElements = (posEnd + 1);
            memcpy(static_cast<void *>(newData), static_cast<void *>(data + posBegin), frontElements * sizeof(T));
            memcpy(static_cast<void *>(newData + frontElements), static_cast<void *>(data), backElements * sizeof(T));
        }
        delete[] data;
        data = newData;
        posEnd = size() - 1;
        posBegin = 0;
        capacity = newCapacity;
    }

    void ensureCapacityAtPush() {
        if (!capacity) {
            resize(MIN_RESIZE);
            return;
        }
        if ((posEnd + 1) % capacity != posBegin)
            return;
        resize(static_cast<size_t>(capacity * RESIZE_FACTOR));
    }

    void ensureCapacityAtPop() {
        if (size() == 1) {
            delete[] data;
            data = 0;
            capacity = 0;
            return;
        }
        if (capacity > MIN_RESIZE * RESIZE_FACTOR &&
            size() * RESIZE_FACTOR * RESIZE_FACTOR < capacity)
            resize(static_cast<size_t>(capacity / RESIZE_FACTOR));
    }
};