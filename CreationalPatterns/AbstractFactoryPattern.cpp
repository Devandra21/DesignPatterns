//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Abstract Factory Pattern
// Provides an interface for creating families of related or dependent objects without specifying their concrete classes.
// It facilitates the creation of object groups that work together and belong to a specific family.
// 
// In this example, Abstract Product Interfaces (ProductTypeA and ProductTypeB) define the common methods that concrete product classes must implement.
// Concrete Products (ConcreteProductA1, ConcreteProductA2, ConcreteProductB1, and ConcreteProductB2) are the actual implementations of the abstract product interfaces.
// Abstract Factory Interface (AbstractFactory) declares methods for creating product objects. Concrete factories (ConcreteFactory1 and ConcreteFactory2) implement these methods to create specific families of products.


#include <iostream>
#include <memory>

// Abstract Product Interfaces
class ProductTypeA {
public:
    virtual void performAction() const = 0;
};

class ProductTypeB {
public:
    virtual void performAction() const = 0;
    virtual void collaborate(const ProductTypeA& collaborator) const = 0;
};

// Concrete Products
class ConcreteProductA1 : public ProductTypeA {
public:
    void performAction() const override {
        std::cout << "Performing action of Product A1." << std::endl;
    }
};

class ConcreteProductA2 : public ProductTypeA {
public:
    void performAction() const override {
        std::cout << "Performing action of Product A2." << std::endl;
    }
};

class ConcreteProductB1 : public ProductTypeB {
public:
    void performAction() const override {
        std::cout << "Performing action of Product B1." << std::endl;
    }

    void collaborate(const ProductTypeA& collaborator) const override {
        std::cout << "Product B1 collaborating with (";
        collaborator.performAction();
        std::cout << ")" << std::endl;
    }
};

class ConcreteProductB2 : public ProductTypeB {
public:
    void performAction() const override {
        std::cout << "Performing action of Product B2." << std::endl;
    }

    void collaborate(const ProductTypeA& collaborator) const override {
        std::cout << "Product B2 collaborating with (";
        collaborator.performAction();
        std::cout << ")" << std::endl;
    }
};

// Abstract Factory Interface
class AbstractFactory {
public:
    virtual std::unique_ptr<ProductTypeA> createProductA() const = 0;
    virtual std::unique_ptr<ProductTypeB> createProductB() const = 0;
};

// Concrete Factories
class ConcreteFactory1 : public AbstractFactory {
public:
    std::unique_ptr<ProductTypeA> createProductA() const override {
        return std::make_unique<ConcreteProductA1>();
    }

    std::unique_ptr<ProductTypeB> createProductB() const override {
        return std::make_unique<ConcreteProductB1>();
    }
};

class ConcreteFactory2 : public AbstractFactory {
public:
    std::unique_ptr<ProductTypeA> createProductA() const override {
        return std::make_unique<ConcreteProductA2>();
    }

    std::unique_ptr<ProductTypeB> createProductB() const override {
        return std::make_unique<ConcreteProductB2>();
    }
};

int main() {
    // Use Concrete Factory 1
    std::unique_ptr<ConcreteFactory1> factory1 = std::make_unique<ConcreteFactory1>();
    std::unique_ptr<ProductTypeA> productA1 = factory1->createProductA();
    std::unique_ptr<ProductTypeB> productB1 = factory1->createProductB();
    productB1->collaborate(*productA1);

    // Use Concrete Factory 2
    std::unique_ptr<ConcreteFactory2> factory2 = std::make_unique<ConcreteFactory2>();
    std::unique_ptr<ProductTypeA> productA2 = factory2->createProductA();
    std::unique_ptr<ProductTypeB> productB2 = factory2->createProductB();
    productB2->collaborate(*productA2);

    return 0;
}
