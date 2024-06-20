//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Template Method Pattern
// This pattern defines the structure of an algorithm in a superclass but lets subclasses override specific steps of the algorithm without changing its structure.

// In this example, Template Method Pattern is used to define a skeleton of an algorithm in the 'AbstractClass'.
// The 'templateMethod' function defines the sequence of steps by calling 'primitiveOperation1' and 'primitiveOperation2'.
// The actual implementation of these primitive operations is provided by the concrete subclasses 'ConcreteClassA' and 'ConcreteClassB'.
// This allows 'AbstractClass' to control the algorithm structure while letting subclasses provide specific implementations for certain steps.

#include <iostream>
#include <memory>

// Abstract Class
class AbstractClass {
public:
    virtual ~AbstractClass() = default;

    // Template method defines the algorithm structure
    void templateMethod() {
        primitiveOperation1();
        primitiveOperation2();
    }

    // Primitive operations to be implemented by subclasses
    virtual void primitiveOperation1() = 0;
    virtual void primitiveOperation2() = 0;

    // Delete copy constructor and assignment operator
    AbstractClass(const AbstractClass&) = delete;
    AbstractClass& operator=(const AbstractClass&) = delete;

protected:
    AbstractClass() = default;
};

// Concrete Class A
class ConcreteClassA final : public AbstractClass {
public:
    void primitiveOperation1() override {
        std::cout << "ConcreteClassA: Primitive Operation 1" << std::endl;
    }

    void primitiveOperation2() override {
        std::cout << "ConcreteClassA: Primitive Operation 2" << std::endl;
    }
};

// Concrete Class B
class ConcreteClassB final : public AbstractClass {
public:
    void primitiveOperation1() override {
        std::cout << "ConcreteClassB: Primitive Operation 1" << std::endl;
    }

    void primitiveOperation2() override {
        std::cout << "ConcreteClassB: Primitive Operation 2" << std::endl;
    }
};

int main() {
    std::unique_ptr<AbstractClass> classA = std::make_unique<ConcreteClassA>();
    std::unique_ptr<AbstractClass> classB = std::make_unique<ConcreteClassB>();

    std::cout << "Using ConcreteClassA:" << std::endl;
    classA->templateMethod();

    std::cout << "\nUsing ConcreteClassB:" << std::endl;
    classB->templateMethod();

    return 0;
}
