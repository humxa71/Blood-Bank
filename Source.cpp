#include <iostream>
#include <fstream>
using namespace std;
bool login();
bool compareText(char* a, char* b);
void saveToFile(char* name, int age, char* bg);
void addDonor(char names[][30], int ages[], char bloodGroupsList[][4], int& total, int
	stock[], char bloodGroups[][4]);
void updateDonor(char names[][30], int ages[], char bloodGroupsList[][4], int total, int
	stock[], char bloodGroups[][4]);
void deleteDonor(char names[][30], int ages[], char bloodGroupsList[][4], int& total, int
	stock[], char bloodGroups[][4]);
void showAllDonors(char names[][30], int ages[], char bloodGroupsList[][4], int total);
void showStock(int stock[], char bloodGroups[][4]);
bool isValidBG(char* bg, char bloodGroups[][4]);
void saveAllDonorsToFile(char names[][30], int ages[], char bloodGroupsList[][4], int
	total);
int main() {
	if (!login()) {
		cout << "Login failed. Exiting.\n";
		return 0;
	}
	char names[100][30];
	int ages[100];
	char bloodGroupsList[100][4];
	int totalDonors = 0;
	int stock[8] = { 0 };
	char bloodGroups[8][4] = { "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-" };
	int choice;
	do {
		cout << "\n--- BLOOD BANK MENU ---\n";
		cout << "1. Add Donor\n";
		cout << "2. Update Donor\n";
		cout << "3. Delete Donor\n";
		cout << "4. Show All Donors\n";
		cout << "5. Show Blood Stock\n";
		cout << "6. Exit\n";
		cout << "Enter choice : ";
		cin >> choice;
		if (choice == 1) {
			addDonor(names, ages, bloodGroupsList, totalDonors, stock, bloodGroups);
		}
		else if (choice == 2) {
			updateDonor(names, ages, bloodGroupsList, totalDonors, stock, bloodGroups);
		}
		else if (choice == 3) {
			deleteDonor(names, ages, bloodGroupsList, totalDonors, stock, bloodGroups);
		}
		else if (choice == 4) {
			showAllDonors(names, ages, bloodGroupsList, totalDonors);
		}
		else if (choice == 5) {
			showStock(stock, bloodGroups);
		}
	} while (choice != 6);
	return 0;
}
bool login() {
	char user[10], pass[10];
	char correctUser[] = "admin";
	char correctPass[] = "1234";
	cout << "--- LOGIN ---\nUsername: ";
	cin >> user;
	cout << "Password: ";
	cin >> pass;
	if (!compareText(user, correctUser)) {
		return false;
	}
	if (!compareText(pass, correctPass)) {
		return false;
	}
	return true;
}
bool compareText(char* a, char* b) {
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i]) {
			return false;
		}
		i++;
	}
	if (a[i] == '\0' && b[i] == '\0') {
		return true;
	}
	return false;
}
void saveToFile(char* name, int age, char* bg) {
	ofstream out("donors.txt", ios::app);
	if (out.is_open()) {
		out << name << "," << age << "," << bg << "\n";
		out.close();
	}
	else {
		cout << "Error opening file.\n";
	}
}
void saveAllDonorsToFile(char names[][30], int ages[], char bloodGroupsList[][4], int
	total) {
	ofstream out("donors.txt");
	if (out.is_open()) {
		for (int i = 0; i < total; i++) {
			out << names[i] << "," << ages[i] << "," << bloodGroupsList[i] << "\n";
		}
		out.close();
	}
	else {
		cout << "Error opening file.\n";
	}
}
void addDonor(char names[][30], int ages[], char bloodGroupsList[][4], int& total, int
	stock[], char bloodGroups[][4]) {
	if (total >= 100) {
		cout << "Maximum donors reached.\n";
		return;
	}
	char name[30], bg[4];
	int age;
	cin.ignore();
	cout << "Enter Name: ";
	cin.getline(name, 30);
	cout << "Enter Age: ";
	cin >> age;
	cout << "Enter Blood Group: ";
	cin >> bg;
	if (!isValidBG(bg, bloodGroups)) {
		cout << "Invalid Blood Group.\n";
		return;
	}
	int i = 0;
	while (name[i] != '\0') {
		names[total][i] = name[i];
		i++;
	}
	names[total][i] = '\0';
	ages[total] = age;
	i = 0;
	while (bg[i] != '\0') {
		bloodGroupsList[total][i] = bg[i];
		i++;
	}
	bloodGroupsList[total][i] = '\0';
	for (int j = 0; j < 8; j++) {
		if (compareText(bg, bloodGroups[j])) {
			stock[j]++;
			break;
		}
	}
	saveToFile(name, age, bg);
	total++;
	cout << "Donor added successfully.\n";
}
void updateDonor(char names[][30], int ages[], char bloodGroupsList[][4], int total, int
	stock[], char bloodGroups[][4]) {
	if (total == 0) {
		cout << "No donors to update.\n";
		return;
	}
	char searchName[30];
	cout << "Enter the name of the donor to update: ";
	cin.getline(searchName, 30);
	int index = -1;
	for (int i = 0; i < total; i++) {
		if (compareText(names[i], searchName)) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "Donor not found.\n";
		return;
	}
	cout << "Current details:\n";
	cout << "Name: " << names[index] << "\n";
	cout << "Age: " << ages[index] << "\n";
	cout << "Blood Group: " << bloodGroupsList[index] << "\n";
	char newName[30], newBG[4];
	int newAge;
	cout << "Enter new name: ";
	cin.getline(newName, 30);
	if (newName[0] == '\0') {
		int i = 0;
		while (names[index][i] != '\0') {
			newName[i] = names[index][i];
			newName[i + 1] = '\0';
			i++;
		}
	}
	cout << "Enter new age: ";
	cin >> newAge;
	cin.ignore();
	cout << "Enter new blood group: ";
	cin.getline(newBG, 4);
	for (int j = 0; j < 8; j++) {
		if (compareText(bloodGroupsList[index], bloodGroups[j])) {
			if (stock[j] > 0) {
				stock[j]--;
			}
			break;
		}
	}
	if (newName[0] != '\0') {
		int i = 0;
		while (newName[i] != '\0') {
			names[index][i] = newName[i];
			i++;
		}
		names[index][i] = '\0';
	}
	if (newAge != 0) {
		ages[index] = newAge;
	}
	if (newBG[0] != '\0') {
		if (isValidBG(newBG, bloodGroups)) {
			int i = 0;
			while (newBG[i] != '\0') {
				bloodGroupsList[index][i] = newBG[i];
				i++;
			}
			bloodGroupsList[index][i] = '\0';
			for (int j = 0; j < 8; j++) {
				if (compareText(newBG, bloodGroups[j])) {
					stock[j]++;
					break;
				}
			}
		}
		else {
			cout << "Invalid blood group entered.\n";
			for (int j = 0; j < 8; j++) {
				if (compareText(bloodGroupsList[index], bloodGroups[j])) {
					stock[j]++;
					break;
				}
			}
		}
	}
	else {
		for (int j = 0; j < 8; j++) {
			if (compareText(bloodGroupsList[index], bloodGroups[j])) {
				stock[j]++;
				break;
			}
		}
	}
	saveAllDonorsToFile(names, ages, bloodGroupsList, total);
	cout << "Donor updated successfully.\n";
}
void deleteDonor(char names[][30], int ages[], char bloodGroupsList[][4], int& total, int
	stock[], char bloodGroups[][4]) {
	if (total == 0) {
		cout << "No donors to delete.\n";
		return;
	}
	char searchName[30];
	cin.ignore();
	cout << "Enter the name of the donor to delete: ";
	cin.getline(searchName, 30);
	int index = -1;
	for (int i = 0; i < total; i++) {
		if (compareText(names[i], searchName)) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "Donor not found.\n";
		return;
	}
	for (int j = 0; j < 8; j++) {
		if (compareText(bloodGroupsList[index], bloodGroups[j])) {
			if (stock[j] > 0) {
				stock[j]--;
			}
			break;
		}
	}
	for (int i = index; i < total - 1; i++) {
		int j = 0;
		while (names[i + 1][j] != '\0') {
			names[i][j] = names[i + 1][j];
			j++;
		}
		names[i][j] = '\0';
		ages[i] = ages[i + 1];
		j = 0;
		while (bloodGroupsList[i + 1][j] != '\0') {
			bloodGroupsList[i][j] = bloodGroupsList[i + 1][j];
			j++;
		}
		bloodGroupsList[i][j] = '\0';
	}
	total--;
	saveAllDonorsToFile(names, ages, bloodGroupsList, total);
	cout << "Donor deleted successfully.\n";
}
void showAllDonors(char names[][30], int ages[], char bloodGroupsList[][4], int total) {
	if (total == 0) {
		cout << "No donors available.\n";
		return;
	}
	for (int i = 0; i < total; i++) {
		cout << "\nDonor " << i + 1 << ":\n";
		cout << "Name: " << names[i] << "\n";
		cout << "Age: " << ages[i] << "\n";
		cout << "Blood Group: " << bloodGroupsList[i] << "\n";
	}
}
void showStock(int stock[], char bloodGroups[][4]) {
	cout << "\n--- Blood Stock ---\n";
	for (int i = 0; i < 8; i++) {
		cout << bloodGroups[i] << ": " << stock[i] << "\n";
	}
}
bool isValidBG(char* bg, char bloodGroups[][4]) {
	for (int i = 0; i < 8; i++) {
		if (compareText(bg, bloodGroups[i])) {
			return true;
		}
	}
	return false;
}