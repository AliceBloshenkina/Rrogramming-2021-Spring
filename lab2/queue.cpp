#include <iostream>
#include <exception>
#include <cstring>
#include <fstream>
#include <cassert>
#include <complex>

using namespace std;

template<class T>
class Sequence {
public:
    virtual size_t getSize() const = 0;

    virtual T &operator[](int count) = 0;

    virtual void resize(int new_size) = 0;

    virtual void append(const T &data) = 0;

    virtual void prepend(const T &data) = 0;

    virtual T getFirst() = 0;

    virtual T getLast() = 0;

    virtual void deleteFirst() = 0;

    virtual void GetSubsequence(int startIndex, int endIndex) = 0;

};

template<class T>
class DynamicArray : public Sequence<T> {

private:
    size_t size_;
    T *array_;

public:
    DynamicArray() {
        size_ = 0;
        array_ = nullptr;
    }

    explicit DynamicArray(int size) {
        if (size >= 0) {

            array_ = new T[size];
            for (int i = 0; i < size; i++)
                array_[i] = 0;

            size_ = size;

        } else
            throw out_of_range("DynamicArray(int size) -> count < 0");
    };

    DynamicArray(const T *items, int count) {

        if (count < 0)
            throw out_of_range("DynamicArray(T* items, int count) -> count < 0");

        array_ = new T[count];
        for (int i = 0; i < count; i++)
            array_[i] = items[i];

        size_ = count;
    };

    DynamicArray(const DynamicArray<T> &arr) {
        DynamicArray<T>(arr.size_);
        for (int i = 0; i < size_; ++i)
            this->array_[i] = arr.array_[i];
    };

    size_t getSize() const override {
        return size_;
    };

    T &operator[](int count) override {
        if (count >= size_)
            throw out_of_range("DynamicArray -> operator[] -> count >= size_");
        return array_[count];
    }

    void resize(int new_size) override {
        if (new_size < 0)
            throw std::length_error("DynamicArray -> operator[] -> new_size < 0");

        if (new_size == 0) {
            delete[] array_;
            array_ = nullptr;
            return;
        }

        T *new_data = new T[new_size];

        if (new_size > size_)
            memcpy(new_data, array_, size_ * sizeof(T));
        else
            memcpy(new_data, array_, new_size * sizeof(T));

        size_ = new_size;
        delete[] array_;

        array_ = new_data;
    };

    void append(const T &data) override {
        resize(size_ + 1);
        array_[size_ - 1] = data;
    };

    void prepend(const T &data) override {
        resize(size_ + 1);
        for (int i = size_ - 1; i >= 0; i--) {
            array_[i + 1] = array_[i];
        }
        array_[0] = data;
    };

    T getFirst() override {
        if (size_ == 0)
            throw std::logic_error("DynamicArray -> getFirst -> size_ = 0 ");
        return array_[0];
    }

    T getLast() override {
        if (size_ == 0)
            throw std::logic_error("DynamicArray -> getLast -> size_ = 0 ");
        return array_[size_ - 1];
    }

    void deleteFirst() override {
        if (size_ == 0)
            throw std::logic_error("DynamicArray -> deleteFirst -> size_ = 0 ");
            array_[0] = T(0);
        for(int i = 1; i < size_; i++){
            array_[i-1] = array_[i];
        }
        resize(size_ - 1);
    };

    void GetSubsequence(int startIndex, int endIndex) override {
        for (int i = startIndex; i <= endIndex; i++) {
            cout << array_[i] << " ";
        }
    };

    DynamicArray<T> operator+(const DynamicArray<T> &arr) {
        if (arr.getSize() != this->getSize())
            throw logic_error("Wrong size of new array");

        DynamicArray<T> result(arr.getSize());
        for (int i = 0; i < arr.getSize(); i++)
            result.array_[i] = arr.array_[i] + this->array_[i];

        return result;
    };

    DynamicArray<T> &operator*(const T &value) {

        DynamicArray<T> result(this->getSize());
        for (int i = 0; i < this->getSize(); i++)
            result.array_[i] = this->array_[i] * value;

        return result;
    };

    DynamicArray<T> &operator=(const DynamicArray<T> &arr) {

        if (this == &arr) return *this;

        delete[] this->array_;
        this->array_ = new T[arr.size_];

        for (int i = 0; i < arr.getSize(); i++)
            this->array_[i] = arr.array_[i];

        this->size_ = arr.size_;

        return *this;
    };

    ~DynamicArray() {
        delete[] array_;
        array_ = nullptr;
        size_ = 0;
    };
};

template<class T>
class LinkedList : public Sequence<T> {
private:
    struct Item {
        T data;
        Item *next;
    };
    struct List {
        Item *head;
        Item *tail;
    };
    List *list_;
    size_t size_;

public:
    LinkedList() {
        list_ = new List;
        list_->head = nullptr;
        list_->tail = nullptr;
        size_ = 0;
    }

    LinkedList(int count) : LinkedList() {
        for (int i = 0; i < count; ++i)
            append(0);
    };

    LinkedList(const T *items, int count) : LinkedList() {
        for (int i = 0; i < count; ++i)
            append(items[i]);
    };

    LinkedList(const LinkedList<T> &list) : LinkedList() {
        Item *ptr = list.list_->head;
        for (int i = 0; i < list.size_; i++) {
            append(ptr->data);
            ptr = ptr->next;
        }
    };

    size_t getSize() const override {
        return size_;
    };

    void append(const T &data) override {

        Item *ptr = new Item;

        ptr->data = data;
        ptr->next = nullptr;

        if (list_->head == nullptr) {
            list_->head = ptr;
            list_->tail = ptr;
        } else {
            list_->tail->next = ptr;
            list_->tail = ptr;
        }
        size_++;
    };

    void resize(int newSize) override {
        Item *ptr = list_->head;
        if (newSize == size_) {
            return;
        } else if (newSize < size_) {
            for (int i = 0; i < newSize; ++i) {
                ptr = ptr->next;
            }
            Item *ptr_prev;
            while (ptr) {
                ptr_prev = ptr;
                ptr = ptr->next;
                //delete ptr_prev->data;
                ptr_prev->next = nullptr;
                delete ptr_prev;
            }
        } else if (newSize > size_) {
            for (int i = size_; i < newSize; i++) {
                append(T(0));
            }
        }
    };

    void prepend(const T &data) override {
        Item *ptr = new Item;
        if (!ptr) {
            return;
        }
        ptr->data = data;
        if (!list_->head) {
            ptr->next = nullptr;
            list_->tail = ptr;
        } else
            ptr->next = list_->head;
        list_->head = ptr;
        size_++;

    };

    T getFirst() override {
        if (list_->head == nullptr)
            throw std::logic_error("LinkedList -> getFirst -> list_->head == nullptr ");
        return list_->head->data;
    }

    T getLast() override {
        if (list_->tail == nullptr)
            throw std::logic_error("LinkedList -> getLast -> list_->tail == nullptr ");
        return list_->tail->data;
    }

    void deleteFirst() override {
        if (list_->head == nullptr)
            throw std::logic_error("LinkedList -> deleteFirst -> list_->head == nullptr ");

        Item *ptr = list_->head->next;
        Item *ptr_prev = list_->head;

        ptr_prev->next = nullptr;
        delete ptr_prev;
        list_->head = ptr;

        size_ -= 1;
    };

    T &operator[](int count) override {
        if (count >= size_)
            throw out_of_range("LinkedList -> operator[] -> count >= size_");

        Item *ptr = list_->head;

        for (int i = 0; i < count; ++i) {
            ptr = ptr->next;
        }

        return ptr->data;
    }

    void GetSubsequence(int startIndex, int endIndex) override {
        Item *ptr = list_->head;
        for (int i = 0; i < startIndex; ++i) {
            ptr = ptr->next;
        }
        for (int i = startIndex; i <= endIndex; ++i) {
            //cout << ptr->data << " ";
            ptr = ptr->next;
        }
    };

    LinkedList<T> operator+(const LinkedList<T> &list) {
        if (list.getSize() != this->getSize())
            throw logic_error("Wrong size of new array");

        LinkedList<T> result(list.getSize());
        Item *ptr1 = list.list_->head, *ptr2 = this->list_->head, *ptr3 = result.list_->head;
        for (int i = 0; i < list.getSize(); i++) {
            ptr3->data = ptr1->data + ptr2->data;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
            ptr3 = ptr3->next;
        }

        return result;
    };

    LinkedList<T> operator*(const T &value) {

        LinkedList<T> result(this->getSize());
        Item *ptr1 = list_->head, *ptr2 = result.list_->head;
        for (int i = 0; i < this->getSize(); i++) {
            ptr2->data = ptr1->data * value;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        return result;
    };

    LinkedList<T> &operator=(const LinkedList<T> &list) {

        if (this == &list) return *this;

        Item *ptr = list_->head->next;
        Item *ptr_prev = list_->head;

        while (ptr != nullptr) {
            delete ptr_prev;
            ptr_prev = ptr;
            ptr = ptr->next;
        }
        list_->head = nullptr;
        list_->tail = nullptr;
        this->size_ = 0;

        Item *ptr_list = list.list_->head;
        for (int i = 0; i < list.getSize(); i++) {
            this->append((ptr_list->data));
            ptr_list = ptr_list->next;
        }

        this->size_ = list.size_;

        return *this;
    };

};

template<class T, template <class> class Sequence1>
class queue {
private:
    Sequence<T> *seq_;
public:
    queue(){
        seq_ = new Sequence1<T>();
    }

    void push(const T &value) {
        seq_->append(value);
    }

    size_t getSize() {
        return seq_->getSize();
    };

    T front() {
        return seq_->getFirst();
    }

    bool empty() {
        return (seq_->getSize() == 0);
    }

    T back() {
        return seq_->getLast();
    }

    void pop() {
        seq_->deleteFirst();
    }

    ~queue() {
        delete seq_;
    };
};

void test(){

    queue<int, LinkedList> myQueque_int;
    myQueque_int.push(11);
    myQueque_int.push(22);
    myQueque_int.push(33);
    assert(myQueque_int.front() == 11);
    assert(myQueque_int.back() == 33);
    assert(myQueque_int.getSize() == 3);
    assert(myQueque_int.empty() == false);
    myQueque_int.pop();
    assert(myQueque_int.front() == 22);
    assert(myQueque_int.back() == 33);
    assert(myQueque_int.getSize() == 2);
    for(int i = 0; i < 2; i++)
        myQueque_int.pop();
    assert(myQueque_int.empty() == true);

    queue<float, LinkedList> myQueque_float;
    myQueque_float.push(1.0);
    myQueque_float.push(2.0);
    myQueque_float.push(3.0);
    assert(myQueque_float.front() == 1.0);
    assert(myQueque_float.back() == 3.0);
    assert(myQueque_float.getSize() == 3);
    assert(myQueque_float.empty() == false);
    myQueque_float.pop();
    assert(myQueque_float.front() == 2.0);
    assert(myQueque_float.back() == 3.0);
    assert(myQueque_float.getSize() == 2);
    for(int i = 0; i < 2; i++)
        myQueque_float.pop();
    assert(myQueque_float.empty() == true);

    queue<complex<int>, LinkedList> myQueque_complex;
    complex<int> a(3, 2);
    complex<int> b(2, 5);
    complex<int> c(3, 1);
    myQueque_complex.push(a);
    myQueque_complex.push(b);
    myQueque_complex.push(c);
    assert(myQueque_complex.front() == a);
    assert(myQueque_complex.back() == c);
    assert(myQueque_complex.getSize() == 3);
    assert(myQueque_complex.empty() == false);
    myQueque_complex.pop();
    assert(myQueque_complex.front() == b);
    assert(myQueque_complex.back() == c);
    assert(myQueque_complex.getSize() == 2);
    for(int i = 0; i < 2; i++)
        myQueque_complex.pop();
    assert(myQueque_complex.empty() == true);

    queue<string, LinkedList> myQueque_str;
    myQueque_str.push("first");
    myQueque_str.push("second");
    myQueque_str.push("third");
    assert(myQueque_str.front() == "first");
    assert(myQueque_str.back() == "third");
    assert(myQueque_str.getSize() == 3);
    assert(myQueque_str.empty() == false);
    myQueque_str.pop();
    assert(myQueque_str.front() == "second");
    assert(myQueque_str.back() == "third");
    assert(myQueque_str.getSize() == 2);
    for(int i = 0; i < 2; i++)
        myQueque_str.pop();
    assert(myQueque_str.empty() == true);

    queue<int, DynamicArray> myQueque_int_2;
    myQueque_int.push(11);
    myQueque_int.push(22);
    myQueque_int.push(33);
    assert(myQueque_int.front() == 11);
    assert(myQueque_int.back() == 33);
    assert(myQueque_int.getSize() == 3);
    assert(myQueque_int.empty() == false);
    myQueque_int.pop();
    assert(myQueque_int.front() == 22);
    assert(myQueque_int.back() == 33);
    assert(myQueque_int.getSize() == 2);
    for(int i = 0; i < 2; i++)
        myQueque_int.pop();
    assert(myQueque_int.empty() == true);

    queue<float, DynamicArray> myQueque_float_2;
    myQueque_float.push(1.0);
    myQueque_float.push(2.0);
    myQueque_float.push(3.0);
    assert(myQueque_float.front() == 1.0);
    assert(myQueque_float.back() == 3.0);
    assert(myQueque_float.getSize() == 3);
    assert(myQueque_float.empty() == false);
    myQueque_float.pop();
    assert(myQueque_float.front() == 2.0);
    assert(myQueque_float.back() == 3.0);
    assert(myQueque_float.getSize() == 2);
    for(int i = 0; i < 2; i++)
        myQueque_float.pop();
    assert(myQueque_float.empty() == true);

    queue<complex<int>, DynamicArray> myQueque_complex_2;
    complex<int> a_2(3, 2);
    complex<int> b_2(2, 5);
    complex<int> c_2(3, 1);
    myQueque_complex.push(a_2);
    myQueque_complex.push(b_2);
    myQueque_complex.push(c_2);
    assert(myQueque_complex.front() == a_2);
    assert(myQueque_complex.back() == c_2);
    assert(myQueque_complex.getSize() == 3);
    assert(myQueque_complex.empty() == false);
    myQueque_complex.pop();
    assert(myQueque_complex.front() == b);
    assert(myQueque_complex.back() == c);
    assert(myQueque_complex.getSize() == 2);
    for(int i = 0; i < 2; i++)
        myQueque_complex.pop();
    assert(myQueque_complex.empty() == true);

    queue<string, DynamicArray> myQueque_str_2;
    myQueque_str.push("first");
    myQueque_str.push("second");
    myQueque_str.push("third");
    assert(myQueque_str.front() == "first");
    assert(myQueque_str.back() == "third");
    assert(myQueque_str.getSize() == 3);
    assert(myQueque_str.empty() == false);
    myQueque_str.pop();
    assert(myQueque_str.front() == "second");
    assert(myQueque_str.back() == "third");
    assert(myQueque_str.getSize() == 2);
    for(int i = 0; i < 2; i++)
        myQueque_str.pop();
    assert(myQueque_str.empty() == true);

    cout << "The tests were successful" << endl;

};

class Sheep{
private:
    int age_;
    int weight_;
    string Name_;
public:
    int getAge(){
        return age_;
    };

    int getWeight(){
        return weight_;
    };

    string getName(){
        return Name_;
    };

    void setSheep(int age, int weight, string Name){
        age_ = age;
        weight_ = weight;
        Name_ = Name;
    }
};


int main() {

    test();

    Sheep *Dolly = new Sheep();
    Dolly->setSheep(118, 53, "Dolly WhiteSheep");



    Sheep *Kate = new Sheep();
    Kate->setSheep(24, 72, "Katy GreenGrass");
    Sheep *Antonio = new Sheep();
    Antonio->setSheep(48, 87, "Antonio NeBanderas");

    queue<Sheep*, LinkedList> *myQueque = new queue<Sheep*, LinkedList>;
    myQueque->push(Dolly);
    myQueque->push(Kate);
    myQueque->push(Antonio);



    cout << myQueque->getSize() << endl;

    cout << myQueque->front()->getName() << endl;
    cout << myQueque->back()->getName() << endl << endl;

    myQueque->pop();
    
    cout << myQueque->front()->getName() << endl;
    cout << myQueque->back()->getName() << endl;
    cout << myQueque->getSize() << endl;



    return 0;
}
