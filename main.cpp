#include<mysql.h>
#include<bits/stdc++.h>
#include<fstream>
#include<string>

MYSQL mysql;
MYSQL_RES *res;//����ṹ�������е�һ����ѯ�����
MYSQL_ROW column;//һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ
using namespace std;

/**
 * ��ȡ���ݿ�����
 * @return
 */
bool connectMysql() {
    mysql_init(&mysql);//��ʼ��mysql
    if (!(mysql_real_connect(&mysql,
                             "localhost",//����
                             "root",//�û���
                             "123456",//����
                             "cpp_database",//���ݿ��� �������Ѿ����ڵ� �ҵ�mysql��Сд������
                             3306,//�˿ں� Ĭ�ϵ�0����3306
                             NULL, 0//������������ĳ���д�� ��������������
    ))) {
        cout << "�������ݿ����:" + (string) mysql_error(&mysql) << endl;
        return false;
    } else {
        cout << "�Ѿ��������ݿ⣡" << endl;
        return true;
    }
}

/**
 * �ͷ�����
 */
void freeConnect() {
    mysql_free_result(res);
    mysql_close(&mysql);
}

/**
 * �����²���
 * @param sql
 * @return
 */
bool updateData(string sql) {
    mysql_query(&mysql, "set names gbk");//���ñ����ʽ ����mysql����������
    // ִ��SQL���
    // 0 ִ�гɹ�
    // 1 ִ��ʧ��
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query�ڶ�������ֻ����const cahr* ��Ҫ��string����ת��
        cout << "�������ݿ�ʧ�� ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    } else {
        cout << "���ݿ���³ɹ���" << endl;
        return true;
    }
}

/**
 * ��ӡ��ѯ��������
 */
void outMysql() {
    if (mysql_affected_rows(&mysql) != 0) {
        //��ӡ��������
        cout << "��ѯ����ʦ����Ϊ�� " << mysql_affected_rows(&mysql) << endl;

        char *field[32];//�ֶ���

        int num = mysql_num_fields(res);//��ȡ����
        for (int i = 0; i < num; ++i) {//��ȡ�ֶ���
            field[i] = mysql_fetch_field(res)->name;
        }

        for (int i = 0; i < num; ++i) {
            cout << (string) field[i] << "\t";
        }
        cout << endl;

        while (column = mysql_fetch_row(res)) {//��ȡһ������
            for (int i = 0; i < num; ++i) {
                cout << column[i] << "\t";
            }
            cout << endl;
        }
    } else {
        cout << "��ѯ�������Ϊ��" << mysql_affected_rows(&mysql) << "����ȷ�Ϻ��ѯ��" << endl;
    }
}

/**
 * ��ѯ���ݿ�
 * @param sql 
 * @return 
 */
bool queryDatabase(string sql) {
    mysql_query(&mysql, "set names gbk");//���ñ����ʽ ����cmd����������
    // ִ��SQL���
    // 0 ִ�гɹ�
    // 1 ִ��ʧ��
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query�ڶ�������ֻ����const cahr* ��Ҫ��string����ת��
        cout << "��ѯʧ�� ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    } else {
        cout << "���ڲ�ѯ����" << endl;
    }

    //��ý���� MYSQL_RES *res;
    if (!(res = mysql_store_result(&mysql))) {
        cout << "Couldn't get result from " + (string) mysql_error(&mysql) << endl;
        return false;
    }
    outMysql();//��ӡ���
    return true;
}

/**
 * ���һ������ʦ��Ϣ
 * @param engineer_number
 * @param engineer_name
 * @param engineer_gender
 * @param engineer_degree
 * @param engineer_age
 * @param engineer_salary
 * @param engineer_address
 * @param engineer_phone
 */
bool addEngineer(string engineer_number,
                 string engineer_name,
                 string engineer_gender,
                 string engineer_degree,
                 string engineer_age,
                 string engineer_salary,
                 string engineer_address,
                 string engineer_phone) {
    mysql_query(&mysql, "set names gbk");//���ñ����ʽ ����cmd����������
    // ִ��SQL���
    // 0 ִ�гɹ�
    // 1 ִ��ʧ��
    string sql = "select * from t_engineer where engineer_number = " + engineer_number;
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query�ڶ�������ֻ����const cahr* ��Ҫ��string����ת��
        cout << "��ѯʧ�� ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    } else {
        cout << "���ڲ�ѯ����" << endl;
    }

    //��ý���� MYSQL_RES *res;
    if (!(res = mysql_store_result(&mysql))) {
        cout << "Couldn't get result from " + (string) mysql_error(&mysql) << endl;
        return false;
    }
    if (mysql_affected_rows(&mysql) != 0) {
        cout << "�����ظ������������룡" << endl;
        return false;
    } else {
        updateData("insert into t_engineer values(null,'"
                   + engineer_number + "','"
                   + engineer_name + "','"
                   + engineer_gender + "','"
                   + engineer_degree + "','"
                   + engineer_age + "','"
                   + engineer_salary + "','"
                   + engineer_address + "','"
                   + engineer_phone + "')");
        cout << engineer_number << "��Ա����ӳɹ���" << endl;
        return true;
    }
}

/**
 * ���ݹ��Ÿ���һ������ʦ������Ϣ
 * @param engineer_number
 */
void updateEngineerInfos(string engineer_number) {
    cout << "�ù���ʦ��Ϣ���£�" << endl;
    queryDatabase(
            "select engineer_number ����,engineer_name ����,engineer_gender �Ա�,engineer_degree ѧλ,engineer_age ����,engineer_salary нˮ,engineer_address ��ַ,engineer_phone �绰 from t_engineer where engineer_number = " +
            engineer_number);
    string engineer_name = "";
    string engineer_gender = "";
    string engineer_degree = "";
    string engineer_age = "";
    string engineer_salary = "";
    string engineer_address = "";
    string engineer_phone = "";
    cout << "�������޸ĺ��������" << endl;
    cin >> engineer_name;
    cout << "�������޸ĺ���Ա�" << endl;
    cin >> engineer_gender;
    cout << "�������޸ĺ��ѧλ��" << endl;
    cin >> engineer_degree;
    cout << "�������޸ĺ�����䣺" << endl;
    cin >> engineer_age;
    cout << "�������޸ĺ��нˮ��" << endl;
    cin >> engineer_salary;
    cout << "�������޸ĺ�ĵ�ַ��" << endl;
    cin >> engineer_address;
    cout << "�������޸ĺ�ĵ绰��" << endl;
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
    cout << engineer_number << "��Ա���޸ĳɹ���" << endl;
}

/**
 * ���ݹ��Ÿ���һ������ʦĳ����Ϣ
 * @param engineer_number
 */
void updateEngineerInfo(string engineer_number) {
    cout << "�ù���ʦ��Ϣ���£�" << endl;
    queryDatabase(
            "select engineer_number ����,engineer_name ����,engineer_gender �Ա�,engineer_degree ѧλ,engineer_age ����,engineer_salary нˮ,engineer_address ��ַ,engineer_phone �绰 from t_engineer where engineer_number = " +
            engineer_number);
    int selection = 0;
    cout << "��ѡ����Ҫ�޸ĵ���Ϣ��(����������ʾ�˳�ѡ��)" << endl;
    cout << "1.����" << endl;
    cout << "2.�Ա�" << endl;
    cout << "3.ѧλ" << endl;
    cout << "4.����" << endl;
    cout << "5.нˮ" << endl;
    cout << "6.��ַ" << endl;
    cout << "7.�绰" << endl;
    cin >> selection;
    if (selection == 1) {
        string engineer_name = "";
        cout << "�������޸ĺ��������" << endl;
        cin >> engineer_name;
        updateData("update t_engineer set engineer_name = '" + engineer_name +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "��Ա���޸ĳɹ���" << endl;
    } else if (selection == 2) {
        string engineer_gender = "";
        cout << "�������޸ĺ���Ա�" << endl;
        cin >> engineer_gender;
        updateData("update t_engineer set engineer_gender = '" + engineer_gender +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "��Ա���޸ĳɹ���" << endl;
    } else if (selection == 3) {
        string engineer_degree = "";
        cout << "�������޸ĺ��ѧλ��" << endl;
        cin >> engineer_degree;
        updateData("update t_engineer set engineer_degree = '" + engineer_degree +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "��Ա���޸ĳɹ���" << endl;
    } else if (selection == 4) {
        string engineer_age = "";
        cout << "�������޸ĺ�����䣺" << endl;
        cin >> engineer_age;
        updateData("update t_engineer set engineer_age = '" + engineer_age +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "��Ա���޸ĳɹ���" << endl;
    } else if (selection == 5) {
        string engineer_salary = "";
        cout << "�������޸ĺ��нˮ��" << endl;
        cin >> engineer_salary;
        updateData("update t_engineer set engineer_salary = '" + engineer_salary +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "��Ա���޸ĳɹ���" << endl;
    } else if (selection == 6) {
        string engineer_address = "";
        cout << "�������޸ĺ�ĵ�ַ��" << endl;
        cin >> engineer_address;
        updateData("update t_engineer set engineer_address = '" + engineer_address +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "��Ա���޸ĳɹ���" << endl;
    } else if (selection == 7) {
        string engineer_phone = "";
        cout << "�������޸ĺ�ĵ绰��" << endl;
        cin >> engineer_phone;
        updateData("update t_engineer set engineer_phone = '" + engineer_phone +
                   "' where engineer_number = '" + engineer_number + "'");
        cout << engineer_number << "��Ա���޸ĳɹ���" << endl;
    } else {
        cout << "�����˳�����" << endl;
        return;
    }
    cout << "�޸���ϣ������������˳�����" << endl;
    getchar();
    getchar();
    return;
}


/**
 * ���ݹ���ɾ��һ������ʦ��Ϣ
 * @param engineer_number
 */
void deleteEngineer(string engineer_number) {
    cout << "�ù���ʦɾ��ǰ��Ϣ���£�" << endl;
    queryDatabase(
            "select engineer_number ����,engineer_name ����,engineer_gender �Ա�,engineer_degree ѧλ,engineer_age ����,engineer_salary нˮ,engineer_address ��ַ,engineer_phone �绰 from t_engineer where engineer_number = " +
            engineer_number);
    updateData("delete from t_engineer where engineer_number = '" + engineer_number + "'");
}

/**
 * ��������
 */
void sortByEngineer() {
    cout << "��ѡ��һ������ʽ���������������ʾ�˳�ѡ��" << endl;
    cout << "1.��������" << endl;
    cout << "2.��������" << endl;
    int selection = 0;
    cin >> selection;
    if (selection == 1) {
        queryDatabase(
                "select engineer_number ����,engineer_name ����,engineer_gender �Ա�,engineer_degree ѧλ,engineer_age ����,engineer_salary нˮ,engineer_address ��ַ,engineer_phone �绰 from t_engineer order by engineer_salary");
    } else if (selection == 2) {
        queryDatabase(
                "select engineer_number ����,engineer_name ����,engineer_gender �Ա�,engineer_degree ѧλ,engineer_age ����,engineer_salary нˮ,engineer_address ��ַ,engineer_phone �绰 from t_engineer order by engineer_salary desc");
    } else {
        cout << "�����˳�����" << endl;
        return;
    }
}

/**
 * ����������ѯ����ʦ��Ϣ
 */
void selectEngineer() {
    cout << "��ѡ��һ�²��ҷ�ʽ���������������ʾ�˳�ѡ��" << endl;
    cout << "1.���Ų���" << endl;
    cout << "2.��������" << endl;
    cout << "3.ѧ������" << endl;
    int selection = 0;
    cin >> selection;
    if (selection == 1) {
        cout << "�����빤�ţ�" << endl;
        string engineer_number = "";
        cin >> engineer_number;
        queryDatabase(
                "select engineer_number ����,engineer_name ����,engineer_gender �Ա�,engineer_degree ѧλ,engineer_age ����,engineer_salary нˮ,engineer_address ��ַ,engineer_phone �绰 from t_engineer where engineer_number = " +
                engineer_number);
    } else if (selection == 2) {
        cout << "������������" << endl;
        string engineer_name = "";
        cin >> engineer_name;
        queryDatabase(
                "select engineer_number ����,engineer_name ����,engineer_gender �Ա�,engineer_degree ѧλ,engineer_age ����,engineer_salary нˮ,engineer_address ��ַ,engineer_phone �绰 from t_engineer where engineer_name = '" +
                engineer_name + "'");
    } else if (selection == 3) {
        cout << "������ѧ����" << endl;
        string engineer_degree = "";
        cin >> engineer_degree;
        queryDatabase(
                "select engineer_number ����,engineer_name ����,engineer_gender �Ա�,engineer_degree ѧλ,engineer_age ����,engineer_salary нˮ,engineer_address ��ַ,engineer_phone �绰 from t_engineer where engineer_degree = '" +
                engineer_degree + "'");
    } else {
        cout << "�����˳�����" << endl;
        return;
    }
    cout << "��ѯ��ϣ������������˳�����" << endl;
    getchar();
    getchar();
    return;
}


/**
 * ��ѯ���ݿ������й���ʦ����Ϣ
 */
void selectAllEngineer() {
    queryDatabase(
            "select engineer_number ����,engineer_name ����,engineer_gender �Ա�,engineer_degree ѧλ,engineer_age ����,engineer_salary нˮ,engineer_address ��ַ,engineer_phone �绰 from t_engineer");
}

/**
 * ����txt�ļ�
 */
bool createFile() {
    mysql_query(&mysql, "set names gbk");//���ñ����ʽ ����cmd����������
    // ִ��SQL���
    // 0 ִ�гɹ�
    // 1 ִ��ʧ��
    string sql = "select engineer_number ����,engineer_name ����,engineer_gender �Ա�,engineer_degree ѧλ,engineer_age ����,engineer_salary нˮ,engineer_address ��ַ,engineer_phone �绰 from t_engineer";
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query�ڶ�������ֻ����const cahr* ��Ҫ��string����ת��
        cout << "��ѯʧ�� ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    }

    //��ý���� MYSQL_RES *res;
    if (!(res = mysql_store_result(&mysql))) {
        cout << "Couldn't get result from " + (string) mysql_error(&mysql) << endl;
        return false;
    }

    std::ofstream OsWrite("d:\\work.txt", std::ofstream::out);
    char *field[32];//�ֶ���
    int num = mysql_num_fields(res);//��ȡ����
    for (int i = 0; i < num; ++i) {//��ȡ�ֶ���
        field[i] = mysql_fetch_field(res)->name;
    }
    for (int i = 0; i < num; ++i) {
        OsWrite << (((string) field[i]) + "\t ");
    }
    OsWrite << endl;
    while (column = mysql_fetch_row(res)) {//��ȡһ������
        for (int i = 0; i < num; ++i) {
            OsWrite << column[i] << "\t  ";
        }
        OsWrite << endl;
    }
    OsWrite.close();
    return true;
}

void menu() {
    cout << "***********************" << endl;
    cout << "*��ӭ�����������ʦ����ϵͳ*" << endl;
    cout << "*****��ѡ�����¹��ܣ�*****" << endl;
    cout << "***********************" << endl;
    cout << "***1����ʾȫ������ʦ��Ϣ***" << endl;
    cout << "***2��������ѯ����ʦ��Ϣ***" << endl;
    cout << "***3����ӵ�������ʦ��Ϣ***" << endl;
    cout << "***4�������޸Ĺ���ʦ��Ϣ***" << endl;
    cout << "***5��ɾ����������ʦ��Ϣ***" << endl;
    cout << "***6������������нˮ��Ϣ***" << endl;
    cout << "***7������Ŀǰ����ʦ��Ϣ***" << endl;
    cout << "***8���˳�����ʦ����ϵͳ***" << endl;
    cout << "***********************" << endl;
    cout << "���ѡ���ǣ�" << endl;
}

int main() {
    bool page1 = true;
    connectMysql();
    while (page1) {
        menu();
        int selection1 = 0;
        cin >> selection1;
        if (selection1 == 1) {
            selectAllEngineer();
            cout << "��ѯ��ϣ����������ַ��������˵�����" << endl;
            getchar();
            getchar();
        } else if (selection1 == 2) {
            bool page2 = true;
            while (page2) {
                selectEngineer();
                cout << "�Ƿ������ѯ������/��==1/������" << endl;
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
                int number = 0;
                cout << "�����빤�ţ�" << endl;
                bool page3 = true;
                while (page3) {
                    cin >> number;
                    if (number <= 0 || number > 1000) {
                        page3 = true;
                        cout << "��Χ��0-1000�������������������롭��" << endl;
                    } else {
                        page3 = false;
                    }
                }
                string engineer_number = to_string(number);
                string engineer_name = "";
                string engineer_gender = "";
                string engineer_degree = "";
                string engineer_age = "";
                string engineer_salary = "";
                string engineer_address = "";
                string engineer_phone = "";
                cout << "������������" << endl;
                cin >> engineer_name;
                cout << "�������Ա�" << endl;
                cin >> engineer_gender;
                cout << "������ѧλ��" << endl;
                cin >> engineer_degree;
                cout << "���������䣺" << endl;
                cin >> engineer_age;
                cout << "������нˮ��" << endl;
                cin >> engineer_salary;
                cout << "�������ַ��" << endl;
                cin >> engineer_address;
                cout << "������绰��" << endl;
                cin >> engineer_phone;
                addEngineer(engineer_number,
                            engineer_name,
                            engineer_gender,
                            engineer_degree,
                            engineer_age,
                            engineer_salary,
                            engineer_address,
                            engineer_phone);
                cout << "�Ƿ������ӣ�����/��==1/������" << endl;
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
                cout << "��ѡ��һ���޸ķ�ʽ���������������ʾ�˳�ѡ��" << endl;
                cout << "1.ȫ����Ϣ�޸�" << endl;
                cout << "2.������Ϣ�޸�" << endl;
                cout << "���ѡ���ǣ�" << endl;
                int selection2 = 0;
                cin >> selection2;
                if (selection2 == 1) {
                    cout << "��������Ҫ�޸ĵĹ���ʦ���ţ�" << endl;
                    string engineer_number = "";
                    cin >> engineer_number;
                    updateEngineerInfos(engineer_number);
                } else if (selection2 == 2) {
                    cout << "��������Ҫ�޸ĵĹ���ʦ���ţ�" << endl;
                    string engineer_number = "";
                    cin >> engineer_number;
                    updateEngineerInfo(engineer_number);
                } else {
                    cout << "�����˳�����" << endl;
                    page2 = false;
                }
                cout << "�Ƿ�����޸ģ�����/��==1/������" << endl;
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
                cout << "��������Ҫɾ���Ĺ���ʦ���ţ�" << endl;
                string engineer_number = "";
                cin >> engineer_number;
                deleteEngineer(engineer_number);
                cout << "�Ƿ����ɾ��������/��==1/������" << endl;
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
                cout << "�Ƿ�������򣿣���/��==1/������" << endl;
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
            cout << "����ɹ���·����D:\\work.txt�����������ַ��˳�����" << endl;
            getchar();
            getchar();
        } else if (selection1 == 8) {
            int selection2 = 0;
            cout << "�Ƿ��˳�ϵͳ(��/�� == 1/����)��" << endl;
            cin >> selection2;
            if (selection2 == 1) {
                page1 = false;
            } else {
                page1 = true;
                cout << "ȡ���˳��ɹ������ڷ������˵�����" << endl;
            }
        } else {
            page1 = true;
            cout << "�����������ڷ������˵�����" << endl;
        }
    }
    freeConnect();
    return 0;
}