//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Observer Pattern
// This pattern defines a one-to-many dependency between objects, where changes in one object automatically notify and update its dependents.

// In this example, Observer Pattern is demonstrated using a ConcreteSubject (the subject) and ConcreteObservers (the observers).
// - The Subject interface declares methods for attaching, detaching, and notifying observers.
// - The ConcreteSubject class implements the Subject interface, maintaining a list of observers and notifying them of any changes to its state.
// - The Observer interface declares the update method that all concrete observers must implement.
// - The ConcreteObserver class implements the Observer interface, providing specific behavior in the update method to handle notifications from the subject.


#include <iostream>
#include <list>
#include <string>
#include <memory>
#include <unordered_set>
#include <mutex>

// Observer abstract class
class Observer {
public:
    virtual void update(const std::string &message) = 0;
    virtual ~Observer() = default;
};

// Subject abstract class
class Subject {
public:
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = default;
};

// Concrete Subject class
class ConcreteSubject : public Subject {
private:
    std::unordered_set<std::shared_ptr<Observer>> observers;
    std::string message;
    std::mutex mtx;

public:
// Added a lock in below functions for thread safety, as multiple threads can try to use subject and notify
// This example is very simple and we have not used multiple threads , but added locks so that we thing beyond this example
    void attach(std::shared_ptr<Observer> observer) override {
        std::lock_guard<std::mutex> lock(mtx);
        observers.insert(observer);
    }

    void detach(std::shared_ptr<Observer> observer) override {
        std::lock_guard<std::mutex> lock(mtx);
        observers.erase(observer);
    }

    void notify() override {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& observer : observers) {
            observer->update(message);
        }
    }

    void setMessage(const std::string &message) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            this->message = message;
        }
        notify();
    }
};

// Concrete Observer class
class ConcreteObserver : public Observer {
private:
    std::string name;

public:
    ConcreteObserver(const std::string &name) : name(name) {}

    void update(const std::string &message) override {
        std::cout << name << " received message: " << message << std::endl;
    }
};

int main() {
    ConcreteSubject subject;
    std::shared_ptr<ConcreteObserver> observer1 = std::make_shared<ConcreteObserver>("Observer 1");
    std::shared_ptr<ConcreteObserver> observer2 = std::make_shared<ConcreteObserver>("Observer 2");

    subject.attach(observer1);
    subject.attach(observer2);

    subject.setMessage("Hello observers!");

    subject.detach(observer2);

    subject.setMessage("Hello again!");

    return 0;
}