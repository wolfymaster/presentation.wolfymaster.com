#include <iostream>
#include <string>

using namespace std;

int main() {
    double payPerHour1 = 8;
    double numHours1 = 40;
    double payPerHour2 = 11.50;
    double numHours2 = 40;
    double taxPercentage = 20;

    double paycheck1 = (payPerHour1 * numHours1) * (1 - taxPercentage / 100);
    double paycheck2 = (payPerHour2 * numHours2) * (1 - taxPercentage / 100);

    cout << to_string(paycheck1) + " " + to_string(paycheck2);
}