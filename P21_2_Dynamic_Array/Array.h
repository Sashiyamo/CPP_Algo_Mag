#include <iostream>

template<typename T>
class Array final {
    const int DEFAULT_CAP = 16;
    const double CAP_SCALE = 2;

    int capacity;
    T *array;
    int arrSize;

public:
    Array() {
        capacity = DEFAULT_CAP;
        arrSize = 0;
        array = (T *) (malloc(capacity * sizeof(T)));
    }

    Array(int initCapacity) {
        capacity = initCapacity;
        arrSize = 0;
        array = (T *) (malloc(capacity * sizeof(T)));
    }

    Array(const Array<T> &copy) {
        capacity = copy.capacity;
        arrSize = copy.arrSize;
        array = (T *) (malloc(capacity * sizeof(T)));
        for (int i = 0; i < arrSize; i++)
            new (array + i) T(copy.array[i]);
    }

    Array(Array<T> &&copy) {
        capacity = copy.capacity;
        arrSize = copy.arrSize;
        array = copy.array;

        copy.array = nullptr;
        copy.arrSize = 0;
        copy.capacity = 0;
    }

    ~Array() {
        for (int i = 0; i < arrSize; i++)
            array[i].~T();
        free(array);
    }

    int insert(const T &value) {
        insert(arrSize, value);
    }

    int insert(int index, const T &value) {
        if (arrSize >= capacity) {
            capacity = capacity ? capacity * CAP_SCALE : DEFAULT_CAP;
            T *newArray = (T *) (malloc(capacity * sizeof(T)));

            for (int i = 0; i < arrSize; i++) {
                new (newArray + i) T(std::move(array[i]));
            }
            new (newArray + index) T(value);

            for (int i = index + 1; i < arrSize + 1; i++) {
                new (newArray + i) T(std::move(array[i - 1]));
            }

            for (int i = 0; i < arrSize; i++) {
                array[i].~T();
            }

            free(array);
            array = newArray;
        }

        if (index < arrSize) {
            for (int i = arrSize; i > index; i--){
                new(array + i) T(std::move(array[i - 1]));
                array[i - 1].~T();
            }

            new(array + index) T(value);
        }

        arrSize++;

        return index;
    }

    void remove(int index) {
        if (index >= arrSize || index < 0)
            return;

        for (int i = index; i < arrSize - 1; i++) {
            array[i].~T();
            new (array + i) T(std::move(array[i + 1]));
        }
        array[arrSize - 1].~T();
        arrSize -= 1;
    }

    int capacity_() {
        return capacity;
    }

    const T &operator[](int index) const {
        return array[index];
    }

    T &operator[](int index) {
        return array[index];
    }

    int size() const {
        return arrSize;
    }

    Array<T> &operator=(const Array<T> &comp) {
        if (this != &comp) {
            Array<T> temp(comp);
            swap(temp);
        }

        return *this;
    }

    Array<T> &operator=(const Array<T> &&comp) {
        if (this != &comp) {
            swap(comp);
        }

        return *this;
    }

    void swap(Array<T>& copy) {
        std::swap(capacity, copy.capacity);
        std::swap(arrSize, copy.arrSize);
        std::swap(array, copy.array);
    }



    class Iterator
    {
    public:
        Iterator(Array<T>* start, bool isReversed = false) {
            array = start;
            position = isReversed ? array->size() - 1 : 0;
            reverse = isReversed;
        }

        const T& get() const {
            return (*array)[position];
        }

        void set(const T& value) {
            (*array)[position] = value;
        }

        void next() {
            reverse ? position-- : position++;
        }

        bool hasNext() const {
            bool next = true;
            if (reverse && position == 0 || !reverse && position == array->size()) next = false;
            return next;
        }

    protected:
        bool reverse;
        int position;
        Array<T>* array;
    };

    class ConstIterator : public Iterator
    {
    public:
        ConstIterator(Array<T>* start, bool isReversed = false) {
            Iterator(start, isReversed);
        }

    private:
        using Iterator::set;
    };

    Iterator iterator() {
        return Iterator(this);
    }

    Iterator reverseIterator() {
        return Iterator(this, true);
    }

    ConstIterator iterator() const {
        return ConstIterator(this);
    }

    ConstIterator reverseIterator() const {
        return ConstIterator(this, true);
    }
};