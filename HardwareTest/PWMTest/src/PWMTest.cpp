#include <iostream>
#include <functional>

class MyFunctionObject {
public:
    MyFunctionObject() : functionPointer_(nullptr) {}

    template <typename T>
    MyFunctionObject(T* instance, void (T::*function)(int)) {
        functionPointer_ = [instance, function](int value) {
            (instance->*function)(value);
        };
    }

    void execute(int value) {
        if (functionPointer_) {
            functionPointer_(value);
        }
    }

private:
    std::function<void(int)> functionPointer_;
};

class OtherClass {
public:
    OtherClass(MyFunctionObject callback) : callback_(callback) {}

    void CallCallback(int value) {
        callback_.execute(value);
    }

private:
    MyFunctionObject callback_;
};

int main() {
    class MyClass {
    public:
        void SomeFunction(int value) {
            std::cout << "SomeFunction called with value: " << value << std::endl;
        }
    };

    MyClass obj;
    MyFunctionObject functor(&obj, &MyClass::SomeFunction);
    OtherClass other(functor);
    other.CallCallback(42);

    return 0;
}