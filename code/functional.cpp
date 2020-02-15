#include <iostream>
#include <string>
#include <algorithm>

auto taxFunc(double taxPercentage) {
   return [taxPercentage](double amt) {
     return amt * (1 - taxPercentage / 100);
   };
}

double calculateGrossPaycheck(int hours, double payPerHour) {
  return hours * payPerHour;
}

double calculatePaycheck(int employeeHours, double employeeRate, double taxPercentage) {
  return taxFunc(taxPercentage)(calculateGrossPaycheck(employeeHours, employeeRate));
}

struct Employee {
  int hours;
  double rate;
};

int main() {
  struct Employee employee1;
  struct Employee employee2;

  employee1.rate = 8;
  employee1.hours = 40;
  employee2.rate = 11.50;
  employee2.hours = 40;

  const Employee employees[2] = { employee1, employee2 };
  const int n = sizeof(employees) / sizeof(employees[0]);
  const double taxPercentage = 20;
  double paychecks[2];

  transform(employees, employees+n, paychecks, [taxPercentage](Employee employee) {
    return calculatePaycheck(employee.hours, employee.rate, taxPercentage);
  });

  cout << endl << to_string(paychecks[0]) + " " + to_string(paychecks[1]);
}