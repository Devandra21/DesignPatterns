//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Adapter Pattern
// This pattern allows objects with incompatible interfaces to work together by wrapping an existing class with a new interface.

// In this example, The Target interface defines the expected interface that the client code interacts with.
// The Adaptee class has its own interface, which is incompatible with the Target interface.
// To bridge this incompatibility, the Adapter class is introduced.
// The Adapter class implements the Target interface and internally holds an instance of the Adaptee.
// It translates the requests from the Target interface into calls to the Adaptee's interface.


#include <iostream>
#include <string>
#include <memory>

// The Target interface that the client expects to work with
class Target {
public:
    virtual std::string Request() const = 0;
    virtual ~Target() = default;
};

// The Adaptee class with an incompatible interface
class Adaptee {
public:
    std::string SpecificRequest() const {
        return "Adaptee's specific request";
    }
};

// The Adapter class makes the Adaptee's interface compatible with the Target's interface
class Adapter : public Target {
private:
    std::unique_ptr<Adaptee> adaptee;

public:
    Adapter(std::unique_ptr<Adaptee> a) : adaptee(std::move(a)) {}

    std::string Request() const override {
        return "Adapter: (TRANSLATED) " + adaptee->SpecificRequest();
    }
};

// Client code
void ClientCode(const std::shared_ptr<Target>& target) {
    std::cout << target->Request() << std::endl;
}

int main() {
    std::unique_ptr<Adaptee> adaptee = std::make_unique<Adaptee>();
    std::shared_ptr<Target> adapter = std::make_shared<Adapter>(std::move(adaptee));
    
    std::cout << "Client: I can work just fine with the Target objects:\n";
    ClientCode(adapter);

    return 0;
}