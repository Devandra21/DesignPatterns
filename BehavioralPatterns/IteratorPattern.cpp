//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Iterator Pattern
// The Iterator pattern provides a way to access the elements of a collection sequentially without exposing its underlying representation.

// In this example, The Iterator interface (Iterator<T>) defines methods like hasNext() and next() which are implemented by concrete iterators (ConcreteIterator<T>) to iterate over the collection.
// ConcreteIterator<T> maintains a reference to the collection and keeps track of the current position while iterating.
// Aggregate interface (Aggregate<T>) declares a method createIterator() which is implemented by concrete aggregates
// (ConcreteAggregate<T>) to create an iterator for the collection.
// ConcreteAggregate<T> represents the collection of elements and provides methods to add elements to it. It also implements
// createIterator() by creating and returning a ConcreteIterator<T> instance for the collection.



#include <iostream>
#include <vector>
#include <memory>

// Iterator interface
template <class T>
class Iterator {
public:
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
    virtual ~Iterator() = default;
};

// Concrete Iterator
template <class T>
class ConcreteIterator : public Iterator<T> {
private:
    typename std::vector<T>::const_iterator current;
    typename std::vector<T>::const_iterator end;
    const std::vector<T>& collection;

public:
    ConcreteIterator(const std::vector<T>& coll) : collection(coll) {
        current = collection.begin();
        end = collection.end();
    }

    bool hasNext() const override {
        return current != end;
    }

    T next() override {
        return *(current++);
    }
};

// Aggregate interface
template <class T>
class Aggregate {
public:
    virtual std::unique_ptr<Iterator<T>> createIterator() const = 0;
    virtual ~Aggregate() = default;
};

// Concrete Aggregate
template <class T>
class ConcreteAggregate : public Aggregate<T> {
private:
    std::vector<T> collection;

public:
    void add(const T& item) {
        collection.push_back(item);
    }

    std::unique_ptr<Iterator<T>> createIterator() const override {
        return std::make_unique<ConcreteIterator<T>>(collection);
    }
};

int main() {
    ConcreteAggregate<int> aggregate;
    aggregate.add(1);
    aggregate.add(2);
    aggregate.add(3);

    std::unique_ptr<Iterator<int>> iterator = aggregate.createIterator();
    while (iterator->hasNext()) {
        std::cout << iterator->next() << " ";
    }
    std::cout << std::endl;

    return 0;
}
