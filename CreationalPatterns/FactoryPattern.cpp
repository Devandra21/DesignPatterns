//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Factory Method Pattern
// Defines an interface for creating objects but allows subclasses to decide which class to instantiate.
// It delegates the responsibility of object creation to subclasses, providing flexibility in object creation.
// In this example, the Factory Method Pattern is employed to encapsulate the creation logic of different Product types.
// The Factory class provides a static method createProduct() which takes a string parameter indicating the type of product to create.
// Based on the input type, the Factory class decides which ConcreteProduct to instantiate and returns it as a unique_ptr to the base Product interface.
// This abstraction shields the client code from the details of object creation, promoting loose coupling between the client and the products.
// Clients can request products through the Factory without needing to know the specific implementation details of each product type.
// This flexibility allows for easy addition or modification of product types in the future, as new ConcreteProduct classes can be added without altering existing client code.


#include <iostream>
#include <memory>
#include <string>

// Product interface
class Product {
public:
    virtual void printInfo() = 0;
    virtual ~Product() {} // Virtual destructor for polymorphic behavior
};

// Concrete Products
class ConcreteProduct1 : public Product {
public:
    void printInfo() override {
        std::cout << "This is ConcreteProduct1" << std::endl;
    }
};

class ConcreteProduct2 : public Product {
public:
    void printInfo() override {
        std::cout << "This is ConcreteProduct2" << std::endl;
    }
};

// Factory class
class Factory {
public:
    static std::unique_ptr<Product> createProduct(const std::string& type) {
        if (type == "Product1") {
            return std::make_unique<ConcreteProduct1>();
        } else if (type == "Product2") {
            return std::make_unique<ConcreteProduct2>();
        } else {
            return nullptr; // Handle unknown types gracefully
        }
    }
};

int main() {
    // Create products using the Factory
    std::unique_ptr<Product> product1 = Factory::createProduct("Product1");
    std::unique_ptr<Product> product2 = Factory::createProduct("Product2");

    // Use the products
    if (product1) {
        product1->printInfo();
    }

    if (product2) {
        product2->printInfo();
    }

    return 0;
}
