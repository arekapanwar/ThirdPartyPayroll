#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include "person.cpp"
using namespace std;

void readData(string filename, vector<Person> &vect){
  string fname;
  string lname;
  int ID;
  string cname;
  double hours;
  double pay_rate;
  Person temp;
  
  ifstream inFile;
  inFile.open(filename);
  while (!inFile.eof()){
    inFile >> fname >> lname >> ID >> cname >> hours >> pay_rate;
    temp.setFirstName(fname);
    temp.setLastName(lname);
    temp.setEmployeeId(ID);
    temp.setCompanyName(cname);
    temp.setHoursWorked(hours);
    temp.setPayRate(pay_rate);
    vect.push_back(temp);
  }
}


void getCompanies(vector<string> &comp, vector<Person> &emp){
  string name;
 
  for(int i = 0; i < emp.size(); i++){
    name = emp.at(i).getCompanyName();
    comp.push_back(name);
  }


  for(int i = 0; i < comp.size(); i++) {
    for (int j = i+1; j <comp.size(); j++) {
      
      if (comp.at(i) < comp.at(j)){
	string temp = comp.at(i);
	comp.at(i) = comp.at(j);
	comp.at(j) = temp;
      }
    }

  }

 
}

void printHighestPaid(vector<Person> &emp){
  float temp_total_pay = emp[0].totalPay();
  int num;
 
  for (int i = 1; i < emp.size(); i++) {
    if (emp[i].totalPay() > temp_total_pay){
      temp_total_pay = emp[i].totalPay();
      
    }

  }

  for (int i = 0; i < emp.size(); i++) {
    if (emp[i].totalPay() == temp_total_pay){
      num = i;
    }
  }

  cout<< "Highest Paid: " << (emp[num].getFirstName() + " " + emp[num].getLastName())<<endl;
  cout<< "Employee ID: " <<  emp[num].getEmployeeId()<<endl;
  cout<< "Employer: " <<  emp[num].getCompanyName() << endl;
  cout<< "Total Pay: " <<  temp_total_pay << endl;

  
}

void separateAndSave(vector<Person> &emp, vector<string> &comp){
  float total = 0;
  float totalEmpPay = 0;
  for (int i = 0; i < comp.size(); i++) {
    if(comp[i] != comp[i+1]){
      ofstream outFile;
      outFile.open(comp[i]);
      outFile << comp[i] << endl;
      for (int j = 0; j < emp.size(); j++) {
	if (comp[i] == emp[j].getCompanyName()){
	 
	  totalEmpPay = emp[j].totalPay();
	  total += totalEmpPay;
	 
	  outFile << left;
	  outFile.width(10);
	  outFile << emp[j].getFirstName()
		  << " " << emp[j].getLastName()
		  << " " << emp[j].getEmployeeId()
		  << " " << totalEmpPay << fixed  << setprecision(2)
		  << "\n";
	}

      }
      	outFile << total;
	total = 0;
	outFile.close();
    }
  }
}

int main() {


  vector<Person> employees;
  vector<string> companyNames;

  readData("input.txt", employees);
  getCompanies(companyNames, employees);
  printHighestPaid(employees);
  
  cout << "\n";

  /* for (int i = 0; i < employees.size(); i++){
  cout << employees[i].getFirstName() << endl;
  float temp = employees[i].totalPay();
  cout<< temp << endl;
  }
  */


  separateAndSave(employees, companyNames);





  return 0;








}
