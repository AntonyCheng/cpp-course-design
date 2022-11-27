//
// Created by admin on 2022/11/27.
//

#ifndef PROCOURSEDESIGN_ENGINEER_H
#define PROCOURSEDESIGN_ENGINEER_H

#include<iostream>
#include<string>

using namespace std;

class Engineer {
private:
    int engineer_number;
    string engineer_name;
    string engineer_gender;
    string engineer_degree;
    int engineer_age;
    int engineer_salary;
    string engineer_address;
    string engineer_phone;
public:
    Engineer();

    Engineer(int engineerNumber, const string &engineerName, const string &engineerGender, const string &engineerDegree,
             int engineerAge, int engineerSalary, const string &engineerAddress, const string &engineerPhone);

    int getEngineerNumber() const;

    void setEngineerNumber(int engineerNumber);

    const string &getEngineerName() const;

    void setEngineerName(const string &engineerName);

    const string &getEngineerGender() const;

    void setEngineerGender(const string &engineerGender);

    const string &getEngineerDegree() const;

    void setEngineerDegree(const string &engineerDegree);

    int getEngineerAge() const;

    void setEngineerAge(int engineerAge);

    int getEngineerSalary() const;

    void setEngineerSalary(int engineerSalary);

    const string &getEngineerAddress() const;

    void setEngineerAddress(const string &engineerAddress);

    const string &getEngineerPhone() const;

    void setEngineerPhone(const string &engineerPhone);


};

#endif //PROCOURSEDESIGN_ENGINEER_H
