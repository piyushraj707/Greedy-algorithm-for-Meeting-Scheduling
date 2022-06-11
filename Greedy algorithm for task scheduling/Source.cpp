#include <iostream>
#include <iomanip>
using namespace std;

class Meeting {
private:
	double strt; //min value > 00 which represents 00:00:00
	double end;  //max value < 24 which represents 23:59:50
public:
	Meeting() :strt(0.0), end(0.0) {}
	Meeting(double strt, double end) : strt(strt), end(end) {}
	double getStrt() {
		return strt;
	}
	double getEnd() {
		return end;
	}
	void setValue() {
		cout << "Provide the starting time of the meeting: "; cin >> strt;
		cout << "Provide the ending time of the meeting: "; cin >> end;
		cout << endl;
	}
	void getValue() {
		cout << "strt: " << strt << endl;
		cout << "end: " << end << endl;
	}
};


int main() {
	cout << "Please provide starting and ending time of all the meetings. Note that start time cannot be greater than ending time." << endl << endl;

	Meeting* MeetsPtr[50];
	int n = 0; //n=total number of meetings
	char choice;

	do {
		MeetsPtr[n] = new Meeting;
		cout << "Meeting " << n + 1 << endl;
		MeetsPtr[n++]->setValue();
		cout << "More meetings? (y/n): "; cin >> choice;
		cout << endl << endl;
	} while (choice == 'y' && n < 50);
	
	//bubble sorting (in ascending order) the Meetings according to the end time.
	for (int i = 1; i <= n - 1; i++) {
		for (int j = 1; j <= n - i; j++) {
			if (MeetsPtr[j - 1]->getEnd() > MeetsPtr[j]->getEnd()) {
				Meeting temp;
				temp = *MeetsPtr[j];
				*MeetsPtr[j] = *MeetsPtr[j - 1];
				*MeetsPtr[j - 1] = temp;
			}
		}
	}


	//Applying Greedy's algorithm to the meetings
	int Meet_no[50];  //storing the meeting number for all compatible meetings
	Meet_no[0] = 0;   //The first meeting is to be held for sure
	int final_total = 1;  //counting the total number of meetings to be held
	for (int i = 1; i < n; i++) {  //i: index of meeting being checked
		int j = Meet_no[final_total - 1];  //index of last confirmed meeting
		if (MeetsPtr[i]->getStrt() >= MeetsPtr[j]->getEnd()) {    //if strt time of a meeting to be checked is after the end time of the last confirmed meeting only then this meeting can be confirmed.
			Meet_no[final_total] = i;
			final_total++;
		}
	}

	cout << "Here is the list of meetings approved by the Greedy Algorithm." << endl << endl;
	cout << "Meeting number   Starting time    Ending time" << endl;
	for (int i = 0; i < final_total; i++) {
		cout << setw(14) << Meet_no[i]
			<< setw(16) << MeetsPtr[Meet_no[i]]->getStrt()
			<< setw(15) << MeetsPtr[Meet_no[i]]->getEnd() << endl;
	}

	return 0;
}
