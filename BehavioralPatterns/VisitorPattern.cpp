//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Visitor Pattern
// This pattern lets you add further operations to objects without modifying them. It involves defining new operations on an object structure by creating a separate visitor class.

// In this example, Visitor Pattern is used to separate algorithms from the objects on which they operate. 
// We have a `Visitor` interface with visit methods for each concrete element type.
// The `Element` interface declares an `accept` method that takes a `Visitor`.
// `ElementA` and `ElementB` are concrete implementations of the `Element` interface.
// `ConcreteVisitor` implements the `Visitor` interface, providing specific operations for each type of element.


#include <iostream>
#include <vector>
#include <memory>

class ElementA;
class ElementB;

// Visitor interface
class Visitor {
public:
    virtual void visit(const ElementA& element) const = 0;
    virtual void visit(const ElementB& element) const = 0;
    virtual ~Visitor() = default; // Virtual destructor for proper cleanup
};

// Element interface
class Element {
public:
    virtual void accept(Visitor& visitor) const = 0;
    virtual ~Element() = default; // Virtual destructor for proper cleanup
};

// Concrete elements
class ElementA : public Element {
public:
    void accept(Visitor& visitor) const override {
        visitor.visit(*this);
    }
    void operationA() const {
        std::cout << "ElementA operation\n";
    }
};

class ElementB : public Element {
public:
    void accept(Visitor& visitor) const override {
        visitor.visit(*this);
    }
    void operationB() const {
        std::cout << "ElementB operation\n";
    }
};

// Concrete visitor
class ConcreteVisitor : public Visitor {
public:
    void visit(const ElementA& element) const override {
        std::cout << "Visiting ElementA\n";
        element.operationA();
    }

    void visit(const ElementB& element) const override {
        std::cout << "Visiting ElementB\n";
        element.operationB();
    }
};

int main() {
    std::vector<std::unique_ptr<Element>> elements;
    elements.push_back(std::make_unique<ElementA>());
    elements.push_back(std::make_unique<ElementB>());

    ConcreteVisitor visitor;

    for (const auto& elem : elements) {
        elem->accept(visitor);
    }

    return 0;
}
