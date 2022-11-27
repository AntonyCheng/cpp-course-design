//
// Created by admin on 2022/11/27.
//

#include "../header/Engineer.h"

Engineer::Engineer() {}

Engineer::Engineer(int engineerNumber, const string &engineerName, const string &engineerGender,
                   const string &engineerDegree, int engineerAge, int engineerSalary, const string &engineerAddress,
                   const string &engineerPhone) : engineer_number(engineerNumber), engineer_name(engineerName),
                                                  engineer_gender(engineerGender), engineer_degree(engineerDegree),
                                                  engineer_age(engineerAge), engineer_salary(engineerSalary),
                                                  engineer_address(engineerAddress), engineer_phone(engineerPhone) {}

int Engineer::getEngineerNumber() const {
    return engineer_number;
}

void Engineer::setEngineerNumber(int engineerNumber) {
    engineer_number = engineerNumber;
}

const string &Engineer::getEngineerName() const {
    return engineer_name;
}

void Engineer::setEngineerName(const string &engineerName) {
    engineer_name = engineerName;
}

const string &Engineer::getEngineerGender() const {
    return engineer_gender;
}

void Engineer::setEngineerGender(const string &engineerGender) {
    engineer_gender = engineerGender;
}

const string &Engineer::getEngineerDegree() const {
    return engineer_degree;
}

void Engineer::setEngineerDegree(const string &engineerDegree) {
    engineer_degree = engineerDegree;
}

int Engineer::getEngineerAge() const {
    return engineer_age;
}

void Engineer::setEngineerAge(int engineerAge) {
    engineer_age = engineerAge;
}

int Engineer::getEngineerSalary() const {
    return engineer_salary;
}

void Engineer::setEngineerSalary(int engineerSalary) {
    engineer_salary = engineerSalary;
}

const string &Engineer::getEngineerAddress() const {
    return engineer_address;
}

void Engineer::setEngineerAddress(const string &engineerAddress) {
    engineer_address = engineerAddress;
}

const string &Engineer::getEngineerPhone() const {
    return engineer_phone;
}

void Engineer::setEngineerPhone(const string &engineerPhone) {
    engineer_phone = engineerPhone;
}
