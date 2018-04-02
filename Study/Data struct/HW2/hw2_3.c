/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_3
*/
typedef struct person
{
	char ca_name[5];
	int i_age;
	float f_income;
	struct {
		int month;
		int day;
		int year;
	}birthday;
}person;