File Handling

1. Write a C++ program to create a file and print “File created successfully” and throw
an error if file is not created.
2. Write a C++ program to read a text file and count the number of characters in it.
3. Write a C++ program to open an output file 'a.txt' and append data to it.
4. Write a program to copy the contents of one text file to another while changing the
case of every alphabet.
5. Write a C++ program to merge the two files.
6. Write a C++ program that counts the total number of characters, words and lines in
the file.
7. There are 50 records in a file. Each record contains 6-character item-code, 20
characters for item-name and an integer price. Write a program to read these
records, arrange them in the descending order of price and write them in the same
file, overwriting the earlier records.
8. A file 'Employee.txt' contains empno and empname. Write a C++ program to add and
read contents of this file and search for an employee whose name is 'XYZ'.
9. A company has following details of their employees in the file 'emp.dat'
a. Emp Id
b. Emp Name
c. Emp Address
d. Emp Dept (Admin/Sales/Production/IT)
e. Emp Phone
f. Emp Age
Write a C++ program to read the above file. Create a new file such as Adm.dat,
Sal.dat, Pro.dat, IT.dat respectively to store the employee details according to their
department.
10. Write a C++ program to create a file which has information Name, Account number,
Balance and perform following operations:
a. Add record
b. Display content of file
c. Display name of person having balance > 10,000

Solution:-

1. #include <iostream>
#include <fstream>

int main() {
    std::ofstream file("example.txt");
    if (file) {
        std::cout << "File created successfully" << std::endl;
    } else {
        std::cerr << "Error: File could not be created" << std::endl;
    }
    file.close();
    return 0;
}


2. #include <iostream>
#include <fstream>

int main() {
    std::ifstream file("example.txt");
    if (!file) {
        std::cerr << "Error: File could not be opened" << std::endl;
        return 1;
    }

    char ch;
    int count = 0;
    while (file.get(ch)) {
        count++;
    }

    std::cout << "Number of characters: " << count << std::endl;
    file.close();
    return 0;
}

3. #include <iostream>
#include <fstream>

int main() {
    std::ofstream file("a.txt", std::ios::app);
    if (!file) {
        std::cerr << "Error: File could not be opened" << std::endl;
        return 1;
    }

    file << "Appending this data to the file.\n";
    std::cout << "Data appended successfully" << std::endl;
    file.close();
    return 0;
}

4. #include <iostream>
#include <fstream>
#include <cctype>

int main() {
    std::ifstream sourceFile("source.txt");
    std::ofstream destinationFile("destination.txt");

    if (!sourceFile || !destinationFile) {
        std::cerr << "Error: File could not be opened" << std::endl;
        return 1;
    }

    char ch;
    while (sourceFile.get(ch)) {
        if (std::isalpha(ch)) {
            ch = std::islower(ch) ? std::toupper(ch) : std::tolower(ch);
        }
        destinationFile.put(ch);
    }

    sourceFile.close();
    destinationFile.close();
    std::cout << "File copied and case changed successfully" << std::endl;
    return 0;
}

5. #include <iostream>
#include <fstream>

int main() {
    std::ifstream file1("file1.txt");
    std::ifstream file2("file2.txt");
    std::ofstream outputFile("merged.txt");

    if (!file1 || !file2 || !outputFile) {
        std::cerr << "Error: File could not be opened" << std::endl;
        return 1;
    }

    outputFile << file1.rdbuf() << file2.rdbuf();

    file1.close();
    file2.close();
    outputFile.close();
    std::cout << "Files merged successfully" << std::endl;
    return 0;
}

6. #include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream file("example.txt");
    if (!file) {
        std::cerr << "Error: File could not be opened" << std::endl;
        return 1;
    }

    int charCount = 0, wordCount = 0, lineCount = 0;
    std::string line, word;

    while (std::getline(file, line)) {
        lineCount++;
        charCount += line.length() + 1;  // +1 for newline character
        std::istringstream iss(line);
        while (iss >> word) {
            wordCount++;
        }
    }

    std::cout << "Characters: " << charCount << "\nWords: " << wordCount << "\nLines: " << lineCount << std::endl;
    file.close();
    return 0;
}

7. #include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Record {
    char itemCode[7];
    char itemName[21];
    int price;
};

bool comparePrice(const Record &a, const Record &b) {
    return a.price > b.price;
}

int main() {
    std::fstream file("records.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error: File could not be opened" << std::endl;
        return 1;
    }

    std::vector<Record> records(50);
    file.read(reinterpret_cast<char*>(records.data()), records.size() * sizeof(Record));

    std::sort(records.begin(), records.end(), comparePrice);

    file.seekp(0);
    file.write(reinterpret_cast<const char*>(records.data()), records.size() * sizeof(Record));
    file.close();

    std::cout << "Records sorted and written to file successfully" << std::endl;
    return 0;
}

8. #include <iostream>
#include <fstream>
#include <string>

struct Employee {
    int empno;
    char empname[50];
};

int main() {
    std::fstream file("Employee.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!file) {
        std::cerr << "Error: File could not be opened" << std::endl;
        return 1;
    }

    // Adding a new employee
    Employee emp;
    emp.empno = 123;
    strcpy(emp.empname, "XYZ");
    file.write(reinterpret_cast<char*>(&emp), sizeof(Employee));

    // Searching for an employee
    file.seekg(0);
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
        if (std::string(emp.empname) == "XYZ") {
            std::cout << "Employee found: " << emp.empno << ", " << emp.empname << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Employee 'XYZ' not found" << std::endl;
    }

    file.close();
    return 0;
}

9. #include <iostream>
#include <fstream>
#include <string>

struct Employee {
    int empId;
    char empName[50];
    char empAddress[100];
    char empDept[20];
    char empPhone[15];
    int empAge;
};

void writeEmployeeToFile(const Employee& emp, const std::string& fileName) {
    std::ofstream file(fileName, std::ios::app);
    file.write(reinterpret_cast<const char*>(&emp), sizeof(Employee));
    file.close();
}

int main() {
    std::ifstream inputFile("emp.dat", std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error: File could not be opened" << std::endl;
        return 1;
    }

    Employee emp;
    while (inputFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
        if (strcmp(emp.empDept, "Admin") == 0) {
            writeEmployeeToFile(emp, "Adm.dat");
        } else if (strcmp(emp.empDept, "Sales") == 0) {
            writeEmployeeToFile(emp, "Sal.dat");
        } else if (strcmp(emp.empDept, "Production") == 0) {
            writeEmployeeToFile(emp, "Pro.dat");
        } else if (strcmp(emp.empDept, "IT") == 0) {
            writeEmployeeToFile(emp, "IT.dat");
        }
    }

    inputFile.close();
    std::cout << "Employees sorted into respective department files successfully" << std::endl;
    return 0;
}

10. #include <iostream>
#include <fstream>
#include <string>

struct Account {
    char name[50];
    int accountNumber;
    double balance;
};

void addRecord(const std::string& fileName) {
    std::ofstream file(fileName, std::ios::app);
    if (!file) {
        std::cerr << "Error: File could not be opened for writing" << std::endl;
        return;
    }

    Account acc;
    std::cout << "Enter Name: ";
    std::cin.ignore();
    std::cin.getline(acc.name, 50);
    std::cout << "Enter Account Number: ";
    std::cin >> acc.accountNumber;
    std::cout << "Enter Balance: ";
    std::cin >> acc.balance;
    file.write(reinterpret_cast<char*>(&acc), sizeof(Account));
    file.close();
    std::cout << "Record added successfully" << std::endl;
}

void displayContent(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error: File could not be opened for reading" << std::endl;
        return;
    }

    Account acc;
    while (file.read(reinterpret_cast<char*>(&acc), sizeof(Account))) {
        std::cout << "Name: " << acc.name << ", Account Number: " << acc.accountNumber << ", Balance: " << acc.balance << std::endl;
    }
    file.close();
}

void displayHighBalance(const std::string& fileName, double threshold) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error: File could not be opened for reading" << std::endl;
        return;
    }

    Account acc;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&acc), sizeof(Account))) {
        if (acc.balance > threshold) {
            std::cout << "Name: " << acc.name << ", Balance: " << acc.balance << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No account with balance greater than " << threshold << " found." << std::endl;
    }
    file.close();
}

int main() {
    std::string fileName = "accounts.dat";
    int choice;
    double threshold = 10000;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add record\n";
        std::cout << "2. Display content of file\n";
        std::cout << "3. Display name of person having balance > 10,000\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addRecord(fileName);
                break;
            case 2:
                displayContent(fileName);
                break;
            case 3:
                displayHighBalance(fileName, threshold);
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
