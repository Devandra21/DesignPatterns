//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Builder Pattern
// Separates the construction of a complex object from its representation, enabling the same construction process to create different representations.
// This pattern is useful when dealing with objects with many optional or complex components.

// In this example, the Builder Design Pattern is employed to construct complex Product objects, 
// while decoupling the construction process from their representation. This allows the same construction 
// process to create different representations of the Product. 
// The Product class represents the object to be constructed, which contains various parts.
// The Builder abstract class defines the interface for creating different parts of the Product.
// ConcreteBuilder1 and ConcreteBuilder2 are concrete implementations of the Builder interface, each responsible 
// for constructing a specific representation of the Product. They implement the buildPartA() and buildPartB() methods 
// to construct different parts of the Product.
// The Director class orchestrates the construction process by invoking the appropriate methods on the Builder 
// object it is associated with. It provides a construct() method to guide the order of construction.


#include <iostream>
#include <string>
#include <memory>

// Product
class Product {
public:
    void addPart(const std::string& part) {
        parts_ += part + " ";
    }

    void showProduct() const {
        std::cout << "Product parts: " << parts_ << std::endl;
    }

private:
    std::string parts_;
};

// Abstract Builder
class Builder {
public:
    virtual ~Builder() {} // Virtual destructor for proper cleanup

    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual void buildPartC() = 0;
    virtual Product* getProduct() = 0;
};

// Concrete Builder 1
class ConcreteBuilder1 : public Builder {
public:
    void buildPartA() override {
        product_->addPart("PartA1");
    }

    void buildPartB() override {
        product_->addPart("PartB1");
    }

    void buildPartC() override {
        product_->addPart("PartC1");
    }

    Product* getProduct() override {
        return product_.get();
    }

private:
    std::unique_ptr<Product> product_ = std::make_unique<Product>();
};

// Concrete Builder 2
class ConcreteBuilder2 : public Builder {
public:
    void buildPartA() override {
        product_->addPart("PartA2");
    }

    void buildPartB() override {
        product_->addPart("PartB2");
    }

    void buildPartC() override {
        product_->addPart("PartC2");
    }

    Product* getProduct() override {
        return product_.get();
    }

private:
    std::unique_ptr<Product> product_ = std::make_unique<Product>();
};

// Director
class Director {
public:
    // Setter and Getter for Builder
    void setBuilder(std::unique_ptr<Builder> builder) {
        builder_ = std::move(builder);
    }

    void construct() {
        builder_->buildPartA();
        builder_->buildPartB();
        builder_->buildPartC();
    }
    
    Product* getProduct() const {
        return builder_->getProduct();
    }

private:
    std::unique_ptr<Builder> builder_;
};

int main() {
    Director director;
    
    // Construct using ConcreteBuilder1
    std::unique_ptr<ConcreteBuilder1> builder1 = std::make_unique<ConcreteBuilder1>();
    director.setBuilder(std::move(builder1));
    director.construct();
    Product* product1 = director.getProduct();
    product1->showProduct();

    // Construct using ConcreteBuilder2
    std::unique_ptr<ConcreteBuilder2> builder2 = std::make_unique<ConcreteBuilder2>();
    director.setBuilder(std::move(builder2));
    director.construct();
    Product* product2 = director.getProduct();
    product2->showProduct();

    return 0;
}
