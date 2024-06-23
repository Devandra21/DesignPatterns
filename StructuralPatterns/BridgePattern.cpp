//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Bridge Pattern
// This pattern decouples abstraction from implementation, allowing both to evolve independently. It involves creating a bridge interface that contains a reference to an implementation interface.

// In this example, Bridge Pattern is used to separate the abstraction (RemoteControl) from its implementations (BasicRemote and AdvancedRemote). 
// The Device interface acts as the Implementor, with concrete implementations like TV and Radio.
// This allows the RemoteControl abstraction to operate independently of the device it controls, promoting flexibility and scalability. 


#include <iostream>
#include <memory>

// Implementor Interface
class Device {
public:
    virtual ~Device() = default;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void setVolume(int volume) = 0;
};

// ConcreteImplementor 1
class TV : public Device {
public:
    void turnOn() override {
        std::cout << "Turning on the TV.\n";
    }
    void turnOff() override {
        std::cout << "Turning off the TV.\n";
    }
    void setVolume(int volume) override {
        std::cout << "Setting TV volume to " << volume << ".\n";
    }
};

// ConcreteImplementor 2
class Radio : public Device {
public:
    void turnOn() override {
        std::cout << "Turning on the Radio.\n";
    }
    void turnOff() override {
        std::cout << "Turning off the Radio.\n";
    }
    void setVolume(int volume) override {
        std::cout << "Setting Radio volume to " << volume << ".\n";
    }
};

// Abstraction
class RemoteControl {
protected:
    std::shared_ptr<Device> device;
public:
    RemoteControl(std::shared_ptr<Device> device) : device(device) {}
    virtual ~RemoteControl() {}
    virtual void turnOn() {
        device->turnOn();
    }
    virtual void turnOff() {
        device->turnOff();
    }
};

// RefinedAbstraction 1
class BasicRemote : public RemoteControl {
public:
    BasicRemote(std::shared_ptr<Device> device) : RemoteControl(device) {}
    void turnOn() override {
        std::cout << "Basic Remote: ";
        device->turnOn();
    }
    void turnOff() override {
        std::cout << "Basic Remote: ";
        device->turnOff();
    }
};

// RefinedAbstraction 2
class AdvancedRemote : public RemoteControl {
public:
    AdvancedRemote(std::shared_ptr<Device> device) : RemoteControl(device) {}
    void turnOn() override {
        std::cout << "Advanced Remote: ";
        device->turnOn();
    }
    void turnOff() override {
        std::cout << "Advanced Remote: ";
        device->turnOff();
    }
    void setVolume(int volume) {
        std::cout << "Advanced Remote: ";
        device->setVolume(volume);
    }
};

int main() {
    std::shared_ptr<Device> tv = std::make_shared<TV>();
    std::shared_ptr<Device> radio = std::make_shared<Radio>();

    std::shared_ptr<RemoteControl> basicRemote = std::make_shared<BasicRemote>(tv);
    std::shared_ptr<AdvancedRemote> advancedRemote = std::make_shared<AdvancedRemote>(radio);

    basicRemote->turnOn();
    basicRemote->turnOff();

    advancedRemote->turnOn();
    advancedRemote->turnOff();
    advancedRemote->setVolume(10);

    return 0;
}