#pragma once
#include "Observer.hpp"
#include <vector>
#include <algorithm>

class Subject {
public:
    virtual ~Subject() = default;

    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() const {
        for (Observer* observer : observers) {
            observer->update();
        }
    }

private:
    std::vector<Observer*> observers;
};