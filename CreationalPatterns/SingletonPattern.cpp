//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Singleton Design Pattern
// Ensures that a class has only one instance and provides a global point of access to that instance.
// This is useful for scenarios where we need precisely one instance of a class, such as managing configurations or database connections.
// In this example, the Singleton design pattern is implemented to ensure that the class Singleton has only one instance throughout the program execution. 
// This is achieved by providing a static member function, getInstance(), which returns a reference to the single instance of the Singleton class. If the instance doesn't exist, it is created; otherwise, the existing instance is returned.
// Additionally, the copy constructor and assignment operator are deleted to prevent cloning of the Singleton instance, ensuring its uniqueness.


#include <iostream>
#include <memory>

class Singleton {
public:
    // Static member function to access the instance
    static Singleton& getInstance() {
        // Create the instance if it doesn't exist
        if (!instance) {
            instance.reset(new Singleton());
            std::cout << "Created new Instance of object." << std::endl;
        }
        else {
            std::cout << "Returning already existing Instance of object." << std::endl;
        }
        return *instance;
    }
    
    // Delete copy constructor and assignment operator to prevent cloning
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Public member function to demonstrate Singleton behavior
    void showMessage() {
        std::cout << "Hello, I am a Singleton!" << std::endl;
    }
    //destructor is not implemented for Singleton as it may defeat the purpose of singleton

private:
    // Private constructor to prevent instantiation
    Singleton() {}

    // Private static pointer to the single instance
    static std::unique_ptr<Singleton> instance;
};

// Initialize the static instance pointer to nullptr
std::unique_ptr<Singleton> Singleton::instance = nullptr;

int main() {
    // Access the Singleton instance
    Singleton& singleton = Singleton::getInstance();

    // Call a member function to demonstrate Singleton behavior
    singleton.showMessage();
    
    // Call demonstrating Singleton Behaviour
    Singleton& singleton2 = Singleton::getInstance();
    singleton2.showMessage();
    
    return 0;
}
