
#include <iostream>
#include <iomanip>
#include <array>
#include <fstream>

class Employee {

	std::string m_firstName{};
	char m_MI{};
	std::string m_lastName{}; // Better to pass m_lastName and m_firstName to a void function by refrences and set their value with std::getLine
	int m_idNumber{};
	int m_empNum{};
	int m_hoursWorked{};
	double m_ratePerHour{};
	double m_gross{};
	double m_tax{};
	double m_net{};
        static int s_value; // don't worry about this being private, you can define from outside fine

	// Setter functions are private since they should only be called by our constructor
	std::string setFirstName() {
		std::string firstName{};
		std::cout << "\nEnter first name : ";
		std::cin >> firstName;
		return firstName;
	}
	char  setMInitial() {
		char mi{};
		std::cout << "\nEnter middle initial : ";
		std::cin >> mi;
		return mi;
	}
	std::string setLastName() {
		std::string lastName{};
		std::cout << "\nEnter last name : ";
		std::cin >> lastName;
		return lastName;
	}
	int setIdNumber() {
		int idNumber{};
		std::cout << "\nEnter ID number : ";
		std::cin >> idNumber;
		while (idNumber < 0) {
			std::cout << "Input error! Input must be greater than " << 0;
			std::cin >> idNumber;
		}
		return idNumber;
	}
	double setHoursWorked() {
		double hoursWorked{};
		std::cout << "\nEnter hours worked : ";
		std::cin >> hoursWorked;                                    // Input validation for hours worked - You could make this a seperate function but it wont be reused so its useless
		while (hoursWorked < 0) {
			std::cout << "Input error! Input must be greater than " << 0;
			std::cin >> hoursWorked;
		}
		return hoursWorked;
	}
	double setRatePerHour() {
		double ratePerHour{};
		std::cout << "\nEnter rate per hour  : ";
		std::cin >> ratePerHour;

		while (ratePerHour < 15.00 || ratePerHour > 35.00) {      // Input validation for rph - You could make this a seperate function but it wont be reused so its useless
			std::cout << ("\nInput error! Re-enter a number between 15.00 and 35.00\n\n");
			std::cin >> ratePerHour;
		}
		return ratePerHour;
	}
	double setGrossPay(const int hoursWorked, const double ratePerHour) {
		double gross{};

		if (hoursWorked <= 40) {     // If employee worked 40 or less hours, it will calculate a standard salary
			gross = hoursWorked * ratePerHour;
		}
		else {                       // If employee has worked more than 40 hours, calculate a standard salary for the first 40 hours and then calculate overtime salary for the remaining hours 
			std::cout << "\nRegular pay " << hoursWorked * ratePerHour;
			gross = (40 * ratePerHour) + ((hoursWorked - 40) * (ratePerHour * 1.5)); // its 40 * ratePerHour, not hoursWorked * ratePerHour   
			std::cout << "\nFixed pay : " << gross;
			std::cout << "\nHours worked are right now : " << hoursWorked;
			std::cout << "\nRPH are right now : " << ratePerHour;
		}

		return gross;
	}
	double calcTax(double m_gross) {
		double tax = m_gross * (0.21);   // 0.21 or whatever tax % rate is
		return tax;
	}
	double setNet() {
		return m_gross - m_tax;
	}
	
	int genEmpNum() {
	
		++s_value;
		return s_value;
		
	}

public:

	Employee() { // We can use initilization list in this case, but I think its better not to as we are setting value with by returning data with function. Use static constexpr on member vars that cannot change the same for all instances,  and IL for assigning member vars values, works on class members who are const and with function calls

		std::cout << "\nEmployee # " << s_Value << "\n";
		m_firstName = setFirstName();
		m_MI = setMInitial();
		m_lastName = setLastName();
		m_idNumber = setIdNumber();
		m_hoursWorked = setHoursWorked();
		m_ratePerHour = setRatePerHour();
		m_gross = setGrossPay(m_hoursWorked, m_ratePerHour);
		m_tax = calcTax(m_gross);
		m_net = setNet();
		m_empNum = genEmpNum();

	}

	const std::string& getFirstName() const {
		return m_firstName;
	}
	char getMI() const {
		return m_MI;
	}
	const std::string& getLastName() const {
		return m_lastName;
	}
	int getIDNumber() const {
		return m_idNumber;
	}
	int getHoursWorked() const {
		return m_hoursWorked;
	}
	int getRatePerhour() const {
		return m_ratePerHour;
	}
	int getGross() const {
		return m_gross;
	}
	double calcTax() const {
		return m_gross;
	}
	double getNet() const {
		return m_net;
	}

}; 

void outputMenu(const std::array<Employee, 5>& employees);
void consoleOutput(const std::array<Employee, 5>& employees);
void fileOutput(const std::array<Employee, 5>& employees);
// Better to place Employee class and file related functions in their own .h & .cpp file, but I cant for this project

int Employee::s_value{ 0 };

int main(){

	std::array<Employee, 5> employees; // Auto populates with constructor, alternative would be default constructors and populating by sending to function with for loop

	outputMenu(employees);
	
}

	void outputMenu(const std::array<Employee, 5>& employees) {

		int choice{ 0 };

		while (choice != 4) {

			std::cout << "\n1. Output to console\n2. Output to File\n3. Both\n4. Exit\n";
			std::cin >> choice;

			switch (choice) {
			case 1:
				fileOutput(employees);
				break;
			case 2:
				consoleOutput(employees);
				break;
			case 3:
				fileOutput(employees);
				consoleOutput(employees);
				break;
			default:
				std::cout << "\nExiting\n";
				choice = 4;
			}

		}
	}

	void consoleOutput(const std::array<Employee, 5>& employees) {

		int total{ 0 };

		for (auto i{ 0 }; i < employees.size(); ++i) {

			std::cout << "\nEmployee  #" << std::setw(5) << i + 1;
			std::cout << "\nFirst Name :" << std::setw(5) << employees[i].getFirstName();
			std::cout << "\nMiddle Initial :" << std::setw(5) << employees[i].getMI();
			std::cout << "\nLast Name :" << std::setw(5) << employees[i].getLastName();
			std::cout << "\nID Number :" << std::setw(5) << employees[i].getIDNumber();
			std::cout << "\nHours Worked :" << std::setw(5) << employees[i].getHoursWorked();
			std::cout << "\nRate Per Hour :" << std::setw(5) << employees[i].getRatePerhour();
			std::cout << "\nGross Pay :" << std::setw(5) << std::fixed << std::setprecision(2) << employees[i].getGross();
			std::cout << "\nNet Pay :" << std::setw(5) << std::fixed << std::setprecision(2) << employees[i].getNet();

			total += employees[i].getGross();
		}

		std::cout << "\nTotal : " << std::setw(5) << std::fixed << std::setprecision(2) << total;
	}

	void fileOutput(const std::array<Employee, 5>& employees) {

		std::ofstream outputFile; // Dont zero initilize, it already uses default constructors for class objects and looks cleaner without the braces
		outputFile.open("Output.txt");

		int total{ 0 };

		for (auto i{ 0 }; i <= employees.size(); ++i) {

			outputFile << "\nEmployee # " << i + 1 << "\n";
			outputFile << "\nFirst Name : " << employees[i].getFirstName() << "\n";
			outputFile << "\nMiddle Initial : " << employees[i].getMI() << "\n";
			outputFile << "\nLast Name : " << employees[i].getLastName() << "\n";
			outputFile << "\nID Number : " << employees[i].getIDNumber() << "\n";
			outputFile << "\nHours Worked : " << employees[i].getHoursWorked() << "\n";
			outputFile << "\nRate Per Hour : " << employees[i].getRatePerhour() << "\n";
			outputFile << "\nGross income : " << employees[i].getGross() << "\n";
			outputFile << "\nNet income : " << employees[i].getNet() << "\n";
			total += employees[i].getGross();

		}

		outputFile << "\nTotal Revenue : " << total;

		outputFile.close();

	}
