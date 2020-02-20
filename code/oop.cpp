#include <iostream>
#include <string>

using namespace std;

// paycheck
class Paycheck {
    int hours;
    double rate, taxPercentage;

    public:
        Paycheck(int h, double r, double tp) {
            hours = h;
            rate = r;
            taxPercentage = tp;
        }

        double calculate() {
            return (hours * rate) * (1 - taxPercentage / 100);
        }
};

// employee
class Employee {
    Paycheck paycheck;

    public:
        Employee(Paycheck p) : paycheck(p) {}

        double calculateSalary() {
            return paycheck.calculate();
        }

        Paycheck getPaycheck() {
            return paycheck;
        }
};


int main() {
    Paycheck johnPaycheck(40, 8, 20);
    Paycheck jimPaycheck(40, 11.50, 20);

    Employee john(johnPaycheck);
    Employee jim(jimPaycheck);

    printf("%.2f %.2f", john.calculateSalary(), jim.getPaycheck().calculate() );
}