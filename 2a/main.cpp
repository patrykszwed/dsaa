#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

class Queue {
public:
	int *arr;
	int size;
	int end;
};

bool isEmpty(Queue& q);
bool isFull(Queue& q);

void init(Queue& q, int size) {
	q.end = 0;
	q.arr = new int[size];
	q.size = size;
}

bool enqueue(Queue& q, int value) {
	if (isFull(q))
		return false;
	q.arr[q.end++] = value;
	if (q.end >= q.size)
		q.end = 0;
	return true;
}

bool dequeue(Queue& q, int &value) {
	if (isEmpty(q))
		return false;
	value = q.arr[0];
	for(int i = 0; i < q.end; ++i)
        q.arr[i] = q.arr[i+1];
    q.end--;
	return true;
}
bool isEmpty(Queue& q) {
	return 0 == q.end;	//if they're equal that means that queue is empty
}
bool isFull(Queue& q) {
	return (q.end == q.size);
}
void show(Queue& q) {
	if (isEmpty(q))
	{
		cout << endl;
		return;
	}
	for(int k = 0; k < q.end; ++k)
        cout << q.arr[k] << ",";
    cout << endl;
}


void showBool(bool val) {
	if (val)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

bool isCommand(const string command, const char *mnemonic) {
	return command == mnemonic;
}

int main() {
	string line;
	string command;
	Queue *queue = NULL;
	int currentQ = 0;
	int value;
	cout << "START" << endl;
	while (true) {
		getline(cin, line);
		std::stringstream stream(line);
		stream >> command;
		if (line == "" || command[0] == '#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0] = toupper(command[0]);
		command[1] = toupper(command[1]);

		if (isCommand(command, "HA")) {
			cout << "END OF EXECUTION" << endl;
			break;
		}

		// zero-argument command
		if (isCommand(command, "EM"))
		{
			showBool(isEmpty(queue[currentQ]));
			continue;
		}
		if (isCommand(command, "FU"))
		{
			showBool(isFull(queue[currentQ]));
			continue;
		}
		if (isCommand(command, "SH"))
		{
			show(queue[currentQ]);
			continue;
		}
		if (isCommand(command, "DE"))
		{
			int ret;
			bool retBool = dequeue(queue[currentQ], ret);
			if (!retBool)
				cout << "false" << endl;
			else
				cout << ret << endl;
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if (isCommand(command, "GO"))
		{
			queue = new Queue[value];
			continue;
		}
		if (isCommand(command, "CH"))
		{
			currentQ = value;
			continue;
		}

		if (isCommand(command, "IN"))
		{
			init(queue[currentQ], value);
			continue;
		}

		if (isCommand(command, "EN"))
		{
			bool retBool = enqueue(queue[currentQ], value);
			showBool(retBool);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
}
