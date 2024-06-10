//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Prototype Pattern
// Creates new objects by copying an existing object, known as the prototype. It allows efficient creation of new instances by copying an existing instance, rather than creating from scratch, especially when the initialization of objects is complex or resource-intensive.

// In this example, The Prototype class defines the interface for cloning itself and showing information about the cloned object. Concrete classes derived from Prototype implement these methods.
// ConcretePrototype class is a concrete implementation of Prototype. It holds a unique field 'prototype_field_' and implements the clone method by creating a new instance of itself and copying its field value.


#include <iostream>
#include <memory>

class Prototype {
public:
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void showInfo() const = 0;
    virtual ~Prototype() = default;
};

// Concrete Prototype
class ConcretePrototype : public Prototype {
private:
    int m_prototype_field_;

public:
    ConcretePrototype(int prototype_field) : m_prototype_field_(prototype_field) {}

    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype>(*this);
    }

    void showInfo() const override {
        std::cout << "Prototype with field: " << m_prototype_field_ << std::endl;
    }
};

int main() {
    // Create a prototype object
    ConcretePrototype prototype(100);

    // Clone the prototype
    std::unique_ptr<Prototype> clone = prototype.clone();

    // Display information of original and cloned objects
    std::cout << "Original prototype: ";
    prototype.showInfo();
    std::cout << " Address of original prototype: " <<&prototype<<std::endl;

    std::cout << "Cloned prototype: ";
    clone->showInfo();
    std::cout << " Address of cloned prototype: " << clone.get() << std::endl;

    return 0;
}