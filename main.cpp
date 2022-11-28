#include<mysql.h>
#include<bits/stdc++.h>
#include<fstream>
#include<string>
#include "header/Engineer.h"

MYSQL mysql;
MYSQL_RES *res;//这个结构代表返回行的一个查询结果集
MYSQL_ROW column;//一个行数据的类型安全(type-safe)的表示
using namespace std;

bool connectMysql();
void freeConnect();
bool updateData(const string& sql);
bool outMysql();
bool queryDatabase(const string& sql);

bool addEngineer(const Engineer& engineer);
void updateEngineerInfos(const string& engineer_number);
void updateEngineerInfo(const string& engineer_number);
void deleteEngineer(const string& engineer_number);
void sortByEngineer();
void selectEngineer();
void selectAllEngineer();
bool createFile();

int main() {
    bool page1 = true;
    connectMysql();
    while (page1) {
        cout << "***********************" << endl;
        cout << "*欢迎来到软件工程师管理系统*" << endl;
        cout << "*****请选择以下功能：*****" << endl;
        cout << "***********************" << endl;
        cout << "***1、显示全部工程师信息***" << endl;
        cout << "***2、条件查询工程师信息***" << endl;
        cout << "***3、添加单个工程师信息***" << endl;
        cout << "***4、条件修改工程师信息***" << endl;
        cout << "***5、删除单个工程师信息***" << endl;
        cout << "***6、按条件排序薪水信息***" << endl;
        cout << "***7、导出目前工程师信息***" << endl;
        cout << "***8、退出工程师管理系统***" << endl;
        cout << "***********************" << endl;
        cout << "你的选择是：" << endl;
        int selection1 = 0;
        cin >> selection1;
        if (selection1 == 1) {
            selectAllEngineer();
            cout << "查询完毕，输入任一数字返回主菜单……" << endl;
            getchar();
            getchar();
        } else if (selection1 == 2) {
            bool page2 = true;
            while (page2) {
                selectEngineer();
                cout << "是否继续查询？（是/否==1/其他数字）" << endl;
                int selection2 = 0;
                cin >> selection2;
                if (selection2 == 1) {
                    continue;
                } else {
                    page2 = false;
                }
            }
        } else if (selection1 == 3) {
            bool page2 = true;
            while (page2) {
                Engineer engineer;
                int engineer_number = 0;
                cout << "请输入工号：" << endl;
                bool page3 = true;
                while (page3) {
                    cin >> engineer_number;
                    if (engineer_number <= 0 || engineer_number > 1000) {
                        page3 = true;
                        cout << "范围在0-1000，输入有误，请重新输入……" << endl;
                    } else {
                        page3 = false;
                    }
                }
                engineer.setEngineerNumber(engineer_number);
                string engineer_name;
                string engineer_gender;
                string engineer_degree;
                int engineer_age;
                int engineer_salary;
                string engineer_address;
                string engineer_phone;
                cout << "请输入姓名：" << endl;
                cin >> engineer_name;
                cout << "请输入性别：" << endl;
                cin >> engineer_gender;
                cout << "请输入学位：" << endl;
                cin >> engineer_degree;
                cout << "请输入年龄：" << endl;
                cin >> engineer_age;
                cout << "请输入薪水：" << endl;
                cin >> engineer_salary;
                cout << "请输入地址：" << endl;
                cin >> engineer_address;
                cout << "请输入电话：" << endl;
                cin >> engineer_phone;
                engineer.setEngineerName(engineer_name);
                engineer.setEngineerGender(engineer_gender);
                engineer.setEngineerDegree(engineer_degree);
                engineer.setEngineerAge(engineer_age);
                engineer.setEngineerSalary(engineer_salary);
                engineer.setEngineerAddress(engineer_address);
                engineer.setEngineerPhone(engineer_phone);
                addEngineer(engineer);
                cout << "是否继续添加？（是/否==1/其他数字）" << endl;
                int selection2 = 0;
                cin >> selection2;
                if (selection2 == 1) {
                    continue;
                } else {
                    page2 = false;
                }
            }
        } else if (selection1 == 4) {
            bool page2 = true;
            while (page2) {
                cout << "请选择一下修改方式：（输入其他数字则表示退出选择）" << endl;
                cout << "1.全部信息修改" << endl;
                cout << "2.部分信息修改" << endl;
                cout << "你的选择是：" << endl;
                int selection2 = 0;
                cin >> selection2;
                if (selection2 == 1) {
                    cout << "请输入需要修改的工程师工号：" << endl;
                    string engineer_number;
                    cin >> engineer_number;
                    updateEngineerInfos(engineer_number);
                } else if (selection2 == 2) {
                    cout << "请输入需要修改的工程师工号：" << endl;
                    string engineer_number;
                    cin >> engineer_number;
                    updateEngineerInfo(engineer_number);
                } else {
                    cout << "正在退出……" << endl;
                    page2 = false;
                }
                cout << "是否继续修改？（是/否==1/其他数字）" << endl;
                cin >> selection2;
                if (selection2 == 1) {
                    continue;
                } else {
                    page2 = false;
                }
            }
        } else if (selection1 == 5) {
            bool page2 = true;
            while (page2) {
                cout << "请输入你要删除的工程师工号：" << endl;
                string engineer_number;
                cin >> engineer_number;
                deleteEngineer(engineer_number);
                cout << "是否继续删除？（是/否==1/其他数字）" << endl;
                int selection2 = 0;
                cin >> selection2;
                if (selection2 == 1) {
                    continue;
                } else {
                    page2 = false;
                }
            }
        } else if (selection1 == 6) {
            bool page2 = true;
            while (page2) {
                sortByEngineer();
                cout << "是否继续排序？（是/否==1/其他数字）" << endl;
                int selection2 = 0;
                cin >> selection2;
                if (selection2 == 1) {
                    continue;
                } else {
                    page2 = false;
                }
            }
        } else if (selection1 == 7) {
            createFile();
            cout << "保存成功，路径在D:\\work.txt！输入任一数字退出……" << endl;
            getchar();
            getchar();
        } else if (selection1 == 8) {
            int selection2 = 0;
            cout << "是否退出系统(是/否 == 1/其他数字)：" << endl;
            cin >> selection2;
            if (selection2 == 1) {
                page1 = false;
            } else {
                page1 = true;
                cout << "取消退出成功！正在返回主菜单……" << endl;
            }
        } else {
            page1 = true;
            cout << "输入有误！输入任一数字返回主菜单……" << endl;
            getchar();
            getchar();
        }
    }
    freeConnect();
    return 0;
}

/**
 * 获取数据库连接
 * @return
 */
bool connectMysql() {
    mysql_init(&mysql);//初始化mysql
    if (!(mysql_real_connect(&mysql,
                             "localhost",//主机
                             "root",//用户名
                             "cry020114",//密码
                             "cpp_database",//数据库名
                             3306,//端口号
                             nullptr, 0//最后两个参数的常用写法
    ))) {
        cout << "连接数据库出错:" + (string) mysql_error(&mysql) << endl;
        return false;
    } else {
        cout << "已经连接数据库！" << endl;
        return true;
    }
}

/**
 * 释放连接
 */
void freeConnect() {
    mysql_free_result(res);
    mysql_close(&mysql);
}

/**
 * 作更新操作
 * @param sql
 * @return
 */
bool updateData(const string& sql) {
    mysql_query(&mysql, "set names gbk");//设置编码格式 否则mysql里中文乱码
    // 执行SQL语句
    // 0 执行成功
    // 1 执行失败
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query第二个参数只接受const char* 需要将string类型转化
        cout << "更新数据库失败 ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    } else {
        cout << "数据库更新成功！" << endl;
        return true;
    }
}

/**
 * 打印查询到的数据
 */
bool outMysql() {
    if (mysql_affected_rows(&mysql) != 0) {
        //打印数据行数
        cout << "查询工程师数量为： " << mysql_affected_rows(&mysql) << endl;

        char *field[32];//字段名

        int num = mysql_num_fields(res);//获取列数
        for (int i = 0; i < num; ++i) {//获取字段名
            field[i] = mysql_fetch_field(res)->name;
        }

        for (int i = 0; i < num; ++i) {
            cout << (string) field[i] << "\t";
        }
        cout << endl;

        column = mysql_fetch_row(res);
        while (column) {//获取一行数据
            for (int i = 0; i < num; ++i) {
                cout << column[i] << "\t";
            }
            cout << endl;
            column = mysql_fetch_row(res);
        }
        return true;
    } else {
        cout << "查询结果数量为：" << mysql_affected_rows(&mysql) << "，请确认后查询！" << endl;
        return false;
    }
}

/**
 * 查询数据库
 * @param sql 
 * @return 
 */
bool queryDatabase(const string& sql) {
    mysql_query(&mysql, "set names gbk");//设置编码格式 否则cmd下中文乱码
    // 执行SQL语句
    // 0 执行成功
    // 1 执行失败
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query第二个参数只接受const char* 需要将string类型转化
        cout << "查询失败 ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    } else {
        cout << "正在查询……" << endl;
    }

    //获得结果集 MYSQL_RES *res;
    if (!(res = mysql_store_result(&mysql))) {
        cout << "Couldn't get result from " + (string) mysql_error(&mysql) << endl;
        return false;
    }
    bool b = outMysql();//打印结果
    return b;
}

/**
 * 添加一个工程师信息
 * @param engineer_number
 * @param engineer_name
 * @param engineer_gender
 * @param engineer_degree
 * @param engineer_age
 * @param engineer_salary
 * @param engineer_address
 * @param engineer_phone
 */
bool addEngineer(const Engineer& engineer) {
    mysql_query(&mysql, "set names gbk");//设置编码格式 否则cmd下中文乱码
    // 执行SQL语句
    // 0 执行成功
    // 1 执行失败
    string sql = "select * from t_engineer where engineer_number = " + to_string(engineer.getEngineerNumber());
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query第二个参数只接受const char* 需要将string类型转化
        cout << "查询失败 ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    } else {
        cout << "正在查询……" << endl;
    }

    //获得结果集 MYSQL_RES *res;
    if (!(res = mysql_store_result(&mysql))) {
        cout << "Couldn't get result from " + (string) mysql_error(&mysql) << endl;
        return false;
    }
    if (mysql_affected_rows(&mysql) != 0) {
        cout << "工号重复，请重新输入！" << endl;
        return false;
    } else {
        updateData("insert into t_engineer values(null,'"
                   + to_string(engineer.getEngineerNumber()) + "','"
                   + engineer.getEngineerName() + "','"
                   + engineer.getEngineerGender() + "','"
                   + engineer.getEngineerDegree() + "','"
                   + to_string(engineer.getEngineerAge()) + "','"
                   + to_string(engineer.getEngineerSalary()) + "','"
                   + engineer.getEngineerAddress() + "','"
                   + engineer.getEngineerPhone() + "')");
        cout << to_string(engineer.getEngineerNumber()) << "号员工添加成功！" << endl;
        return true;
    }
}

/**
 * 根据工号更新一个工程师所有信息
 * @param engineer_number
 */
void updateEngineerInfos(const string& engineer_number) {
    cout << "该工程师信息如下：" << endl;
    bool b = queryDatabase(
            "select engineer_number 工号,engineer_name 姓名,engineer_gender 性别,engineer_degree 学位,engineer_age 年龄,engineer_salary 薪水,engineer_address 地址,engineer_phone 电话 from t_engineer where engineer_number = " +
            engineer_number);
    if (!b) {
        return;
    }
    string engineer_name;
    string engineer_gender;
    string engineer_degree;
    string engineer_age;
    string engineer_salary;
    string engineer_address;
    string engineer_phone;
    cout << "请输入修改后的姓名：" << endl;
    cin >> engineer_name;
    cout << "请输入修改后的性别：" << endl;
    cin >> engineer_gender;
    cout << "请输入修改后的学位：" << endl;
    cin >> engineer_degree;
    cout << "请输入修改后的年龄：" << endl;
    cin >> engineer_age;
    cout << "请输入修改后的薪水：" << endl;
    cin >> engineer_salary;
    cout << "请输入修改后的地址：" << endl;
    cin >> engineer_address;
    cout << "请输入修改后的电话：" << endl;
    cin >> engineer_phone;
    updateData(
            "update t_engineer set engineer_name = '"
            + engineer_name + "',engineer_gender = '"
            + engineer_gender + "',engineer_degree = '"
            + engineer_degree + "',engineer_age = "
            + engineer_age + ",engineer_salary = "
            + engineer_salary + ",engineer_address = '"
            + engineer_age + "',engineer_phone = '"
            + engineer_phone + "' where engineer_number = "
            + engineer_number);
    cout << engineer_number << "号员工修改成功！" << endl;
}

/**
 * 根据工号更新一个工程师某项信息
 * @param engineer_number
 */
void updateEngineerInfo(const string& engineer_number) {
    cout << "该工程师信息如下：" << endl;
    bool b = queryDatabase(
            "select engineer_number 工号,engineer_name 姓名,engineer_gender 性别,engineer_degree 学位,engineer_age 年龄,engineer_salary 薪水,engineer_address 地址,engineer_phone 电话 from t_engineer where engineer_number = " +
            engineer_number);
    if (!b) {
        return;
    }
    int selection = 0;
    cout << "请选择你要修改的信息：(输入其他数字表示退出选择)" << endl;
    cout << "1.姓名" << endl;
    cout << "2.性别" << endl;
    cout << "3.学位" << endl;
    cout << "4.年龄" << endl;
    cout << "5.薪水" << endl;
    cout << "6.地址" << endl;
    cout << "7.电话" << endl;
    cin >> selection;
    if (selection == 1) {
        string engineer_name;
        cout << "请输入修改后的姓名：" << endl;
        cin >> engineer_name;
        updateData("update t_engineer set engineer_name = '" + engineer_name +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "号员工修改成功！" << endl;
    } else if (selection == 2) {
        string engineer_gender;
        cout << "请输入修改后的性别：" << endl;
        cin >> engineer_gender;
        updateData("update t_engineer set engineer_gender = '" + engineer_gender +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "号员工修改成功！" << endl;
    } else if (selection == 3) {
        string engineer_degree;
        cout << "请输入修改后的学位：" << endl;
        cin >> engineer_degree;
        updateData("update t_engineer set engineer_degree = '" + engineer_degree +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "号员工修改成功！" << endl;
    } else if (selection == 4) {
        string engineer_age;
        cout << "请输入修改后的年龄：" << endl;
        cin >> engineer_age;
        updateData("update t_engineer set engineer_age = '" + engineer_age +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "号员工修改成功！" << endl;
    } else if (selection == 5) {
        string engineer_salary;
        cout << "请输入修改后的薪水：" << endl;
        cin >> engineer_salary;
        updateData("update t_engineer set engineer_salary = '" + engineer_salary +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "号员工修改成功！" << endl;
    } else if (selection == 6) {
        string engineer_address;
        cout << "请输入修改后的地址：" << endl;
        cin >> engineer_address;
        updateData("update t_engineer set engineer_address = '" + engineer_address +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "号员工修改成功！" << endl;
    } else if (selection == 7) {
        string engineer_phone;
        cout << "请输入修改后的电话：" << endl;
        cin >> engineer_phone;
        updateData("update t_engineer set engineer_phone = '" + engineer_phone +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "号员工修改成功！" << endl;
    } else {
        cout << "正在退出……" << endl;
        return;
    }
    cout << "修改完毕，输入任一数字以退出……" << endl;
    getchar();
    getchar();
}


/**
 * 根据工号删除一个工程师信息
 * @param engineer_number
 */
void deleteEngineer(const string& engineer_number) {
    cout << "该工程师删除前信息如下：" << endl;
    bool b = queryDatabase(
            "select engineer_number 工号,engineer_name 姓名,engineer_gender 性别,engineer_degree 学位,engineer_age 年龄,engineer_salary 薪水,engineer_address 地址,engineer_phone 电话 from t_engineer where engineer_number = " +
            engineer_number);
    if (!b) {
        return;
    }
    updateData("delete from t_engineer where engineer_number = '" + engineer_number + "'");
}

/**
 * 升序排序
 */
void sortByEngineer() {
    cout << "请选择一下排序方式：（输入其他数字则表示退出选择）" << endl;
    cout << "1.升序排序" << endl;
    cout << "2.降序排序" << endl;
    int selection = 0;
    cin >> selection;
    if (selection == 1) {
        queryDatabase(
                "select engineer_number 工号,engineer_name 姓名,engineer_gender 性别,engineer_degree 学位,engineer_age 年龄,engineer_salary 薪水,engineer_address 地址,engineer_phone 电话 from t_engineer order by engineer_salary");
    } else if (selection == 2) {
        queryDatabase(
                "select engineer_number 工号,engineer_name 姓名,engineer_gender 性别,engineer_degree 学位,engineer_age 年龄,engineer_salary 薪水,engineer_address 地址,engineer_phone 电话 from t_engineer order by engineer_salary desc");
    } else {
        cout << "正在退出……" << endl;
        return;
    }
}

/**
 * 根据条件查询工程师信息
 */
void selectEngineer() {
    cout << "请选择一下查找方式：（输入其他数字则表示退出选择）" << endl;
    cout << "1.工号查找" << endl;
    cout << "2.姓名查找" << endl;
    cout << "3.学历查找" << endl;
    int selection = 0;
    cin >> selection;
    if (selection == 1) {
        cout << "请输入工号：" << endl;
        string engineer_number;
        cin >> engineer_number;
        queryDatabase(
                "select engineer_number 工号,engineer_name 姓名,engineer_gender 性别,engineer_degree 学位,engineer_age 年龄,engineer_salary 薪水,engineer_address 地址,engineer_phone 电话 from t_engineer where engineer_number = " +
                engineer_number);
    } else if (selection == 2) {
        cout << "请输入姓名：" << endl;
        string engineer_name;
        cin >> engineer_name;
        queryDatabase(
                "select engineer_number 工号,engineer_name 姓名,engineer_gender 性别,engineer_degree 学位,engineer_age 年龄,engineer_salary 薪水,engineer_address 地址,engineer_phone 电话 from t_engineer where engineer_name = '" +
                engineer_name + "'");
    } else if (selection == 3) {
        cout << "请输入学历：" << endl;
        string engineer_degree;
        cin >> engineer_degree;
        queryDatabase(
                "select engineer_number 工号,engineer_name 姓名,engineer_gender 性别,engineer_degree 学位,engineer_age 年龄,engineer_salary 薪水,engineer_address 地址,engineer_phone 电话 from t_engineer where engineer_degree = '" +
                engineer_degree + "'");
    } else {
        cout << "正在退出……" << endl;
        return;
    }
    cout << "查询完毕，输入任一数字以退出……" << endl;
    getchar();
    getchar();
}


/**
 * 查询数据库中所有工程师的信息
 */
void selectAllEngineer() {
    queryDatabase(
            "select engineer_number 工号,engineer_name 姓名,engineer_gender 性别,engineer_degree 学位,engineer_age 年龄,engineer_salary 薪水,engineer_address 地址,engineer_phone 电话 from t_engineer");
}

/**
 * 生成txt文件
 */
bool createFile() {
    mysql_query(&mysql, "set names gbk");//设置编码格式 否则cmd下中文乱码
    // 执行SQL语句
    // 0 执行成功
    // 1 执行失败
    string sql = "select engineer_number 工号,engineer_name 姓名,engineer_gender 性别,engineer_degree 学位,engineer_age 年龄,engineer_salary 薪水,engineer_address 地址,engineer_phone 电话 from t_engineer";
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query第二个参数只接受const cahr* 需要将string类型转化
        cout << "查询失败 ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    }

    //获得结果集 MYSQL_RES *res;
    if (!(res = mysql_store_result(&mysql))) {
        cout << "Couldn't get result from " + (string) mysql_error(&mysql) << endl;
        return false;
    }

    std::ofstream OsWrite("d:\\work.txt", std::ofstream::out);
    char *field[32];//字段名
    int num = mysql_num_fields(res);//获取列数
    for (int i = 0; i < num; ++i) {//获取字段名
        field[i] = mysql_fetch_field(res)->name;
    }
    for (int i = 0; i < num; ++i) {
        OsWrite << (((string) field[i]) + "\t ");
    }
    OsWrite << endl;
    column = mysql_fetch_row(res);
    while (column) {//获取一行数据
        for (int i = 0; i < num; ++i) {
            OsWrite << column[i] << "\t  ";
        }
        OsWrite << endl;
        column = mysql_fetch_row(res);
    }
    OsWrite.close();
    return true;
}