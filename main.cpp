#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <iomanip>

// Simple hash function for password using std::hash (less secure than cryptographic hashes)
std::string hashPassword(const std::string& password) {
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(password);

    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash; // Output as hex
    return ss.str();
}

class User {
public:
    User(std::string username, std::string password)
        : username(username), password(hashPassword(password)) {}

    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }

private:
    std::string username;
    std::string password;
};

class Appointment {
public:
    Appointment(std::string date, std::string time, std::string description)
        : date(date), time(time), description(description) {}

    std::string getDate() const { return date; }
    std::string getTime() const { return time; }
    std::string getDescription() const { return description; }

    void display() const {
        std::cout << "Date: " << date << ", Time: " << time << ", Description: " << description << std::endl;
    }

private:
    std::string date;
    std::string time;
    std::string description;
};

class Employee {
public:
    Employee(std::string name, double hourlyWage)
        : name(name), hourlyWage(hourlyWage) {}

    std::string getName() const { return name; }
    double getHourlyWage() const { return hourlyWage; }

private:
    std::string name;
    double hourlyWage;
};

class WorkLog {
public:
    WorkLog(Employee employee, int hoursWorked)
        : employee(employee), hoursWorked(hoursWorked) {}

    Employee getEmployee() const { return employee; }
    int getHoursWorked() const { return hoursWorked; }
    double getWage() const { return hoursWorked * employee.getHourlyWage(); }

    void display() const {
        std::cout << "Employee: " << employee.getName() << ", Hours Worked: " << hoursWorked << ", Wage: $" << getWage() << std::endl;
    }

private:
    Employee employee;
    int hoursWorked;
};

class Project {
public:
    Project(std::string name, std::string description)
        : name(name), description(description) {}

    std::string getName() const { return name; }
    std::string getDescription() const { return description; }

    void addWorkLog(const WorkLog& workLog) {
        workLogs.push_back(workLog);
    }

    void displayWorkLogs() const {
        for (const auto& workLog : workLogs) {
            workLog.display();
        }
    }

    double getTotalWages() const {
        double total = 0.0;
        for (const auto& workLog : workLogs) {
            total += workLog.getWage();
        }
        return total;
    }

    int getTotalHours() const {
        int total = 0;
        for (const auto& workLog : workLogs) {
            total += workLog.getHoursWorked();
        }
        return total;
    }

private:
    std::string name;
    std::string description;
    std::vector<WorkLog> workLogs;
};

class Customer {
public:
    Customer(std::string name, std::string email, std::string phone)
        : name(name), email(email), phone(phone) {}

    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    std::string getPhone() const { return phone; }
    const std::vector<Project>& getProjects() const {
        return projects;
    }

    void addAppointment(const Appointment& appointment) {
        appointments.push_back(appointment);
    }

    void cancelAppointment(const std::string& date, const std::string& time) {
        for (auto it = appointments.begin(); it != appointments.end(); ++it) {
            if (it->getDate() == date && it->getTime() == time) {
                appointments.erase(it);
                break;
            }
        }
    }

    void displayAppointments() const {
        for (const auto& appointment : appointments) {
            appointment.display();
        }
    }

    void display() const {
        std::cout << "Name: " << name << ", Email: " << email << ", Phone: " << phone << std::endl;
        std::cout << "Appointments:" << std::endl;
        displayAppointments();
    }

    void addSale(double amount) {
        sales.push_back(amount);
    }

    void displaySales() const {
        double totalSales = 0.0;
        for (double sale : sales) {
            totalSales += sale;
        }
        std::cout << "Total Sales: $" << totalSales << std::endl;
    }

    std::vector<Appointment> getAppointments() const {
        return appointments;
    }

    void addProject(const Project& project) {
        projects.push_back(project);
    }

    void displayProjects() const {
        for (const auto& project : projects) {
            std::cout << "Project: " << project.getName() << ", Description: " << project.getDescription() << std::endl;
            project.displayWorkLogs();
            std::cout << "Total Hours: " << project.getTotalHours() << ", Total Wages: $" << project.getTotalWages() << std::endl;
        }
    }

private:
    std::string name;
    std::string email;
    std::string phone;
    std::vector<Appointment> appointments;
    std::vector<double> sales;
    std::vector<Project> projects;
};

class CRM {
public:
    void addCustomer(const User& user, const Customer& customer) {
        customers[user.getUsername()] = customer;
    }

    void removeCustomer(const std::string& username) {
        customers.erase(username);
    }

    void addAppointment(const std::string& name, const Appointment& appointment) {
        customers[name].addAppointment(appointment);
    }

    void cancelAppointment(const std::string& name, const std::string& date, const std::string& time) {
        customers[name].cancelAppointment(date, time);
    }

    void displayCustomer(const std::string& name) const {
        customers.at(name).display();
    }

    void addSale(const std::string& name, double amount) {
        customers[name].addSale(amount);
    }

    void displaySales(const std::string& name) const {
        customers.at(name).displaySales();
    }

    void printAppointments() const {
        for (const auto& pair : customers) {
            std::cout << "Appointments for " << pair.first << ":" << std::endl;
            pair.second.displayAppointments();
        }
    }

    void searchCustomerByName(const std::string& name) const {
        auto it = customers.find(name);
        if (it != customers.end()) {
            it->second.display();
        } else {
            std::cout << "Customer not found." << std::endl;
        }
    }

private:
    std::map<std::string, Customer> customers;
};

void displayMenu() {
    std::cout << "CRM Menu:" << std::endl;
    std::cout << "1. Add Customer" << std::endl;
    std::cout << "2. Remove Customer" << std::endl;
    std::cout << "3. Add Appointment" << std::endl;
    std::cout << "4. Cancel Appointment" << std::endl;
    std::cout << "5. Display Customer Info" << std::endl;
    std::cout << "6. Add Sale" << std::endl;
    std::cout << "7. Display Sales Info" << std::endl;
    std::cout << "8. Print All Appointments" << std::endl;
    std::cout << "9. Search Customer by Name" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    CRM crm;

    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear the input buffer

        switch (choice) {
            case 1: {
                // Add customer
                std::string username, password, name, email, phone;
                std::cout << "Enter username: ";
                std::getline(std::cin, username);
                std::cout << "Enter password: ";
                std::getline(std::cin, password);
                std::cout << "Enter customer name: ";
                std::getline(std::cin, name);
                std::cout << "Enter customer email: ";
                std::getline(std::cin, email);
                std::cout << "Enter customer phone: ";
                std::getline(std::cin, phone);
                crm.addCustomer(User(username, password), Customer(name, email, phone));
                break;
            }
            case 2: {
                // Remove customer
                std::string username;
                std::cout << "Enter username to remove: ";
                std::getline(std::cin, username);
                crm.removeCustomer(username);
                break;
            }
            case 3: {
                // Add appointment
                std::string name, date, time, description;
                std::cout << "Enter customer name: ";
                std::getline(std::cin, name);
                std::cout << "Enter date (YYYY-MM-DD): ";
                std::getline(std::cin, date);
                std::cout << "Enter time: ";
                std::getline(std::cin, time);
                std::cout << "Enter description: ";
                std::getline(std::cin, description);
                crm.addAppointment(name, Appointment(date, time, description));
                break;
            }
            case 4: {
                // Cancel appointment
                std::string name, date, time;
                std::cout << "Enter customer name: ";
                std::getline(std::cin, name);
                std::cout << "Enter date of appointment to cancel (YYYY-MM-DD): ";
                std::getline(std::cin, date);
                std::cout << "Enter time of appointment to cancel: ";
                std::getline(std::cin, time);
                crm.cancelAppointment(name, date, time);
                break;
            }
            case 5: {
                // Display customer info
                std::string name;
                std::cout << "Enter customer name: ";
                std::getline(std::cin, name);
                crm.displayCustomer(name);
                break;
            }
            case 6: {
                // Add sale
                std::string name;
                double amount;
                std::cout << "Enter customer name: ";
                std::getline(std::cin, name);
                std::cout << "Enter sale amount: ";
                std::cin >> amount;
                crm.addSale(name, amount);
                break;
            }
            case 7: {
                // Display sales info
                std::string name;
                std::cout << "Enter customer name: ";
                std::getline(std::cin, name);
                crm.displaySales(name);
                break;
            }
            case 8: {
                // Print all appointments
                crm.printAppointments();
                break;
            }
            case 9: {
                // Search customer by name
                std::string name;
                std::cout << "Enter customer name: ";
                std::getline(std::cin, name);
                crm.searchCustomerByName(name);
                break;
            }
            case 0: {
                std::cout << "Exiting..." << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    } while (choice != 0);

    return 0;
}


