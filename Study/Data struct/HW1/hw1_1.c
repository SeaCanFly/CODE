/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #1_1
*/
array[n];
void insert_array(int loc, int value)
{
	int temp = 0;
	for (int i = loc - 1; i < items + 1; i++)
	{ 
		temp = array[i];
		array[i] = value;
		value = temp;
	}
}
O(n), O(1), O(n);

