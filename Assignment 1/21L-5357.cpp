//Muhammad Faseeh----21L-5357
//l215357@lhr.nu.edu.pk
#include <iostream>
#include<fstream>
#include<windows.h>
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//making struct required in question
struct activity
{
	char* title;
	char* userid;
	int duration;
	float priority;
};
//temporay struct used in many tasks
struct temporary {
	int month;
	int day;
	int hour;
	float priority;
	int k = 0;
};
//making variables,functions for ease
int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
int noOfActivity[12][31][24] = { 0 };
void stringCopy(char copy[], char tocopy[]);
int activityInMonth(activity***** calender, int month);
//vital functions
void memoryAllocate(activity*****& calender)
{
	calender = new activity****[12];//months
	for (int month = 0; month < 12; month++)
	{
		calender[month] = new activity ***[days[month]];//days
		for (int day = 0; day < days[month]; day++)
		{
			calender[month][day] = new activity **[24];//hours
			for (int hour = 0; hour < 24; hour++)
			{
				calender[month][day][hour] = new activity*[1];
				calender[month][day][hour][0] = nullptr;
				
			}

		}
	}
}
void dataInput(activity*****& calender)
{
	fstream input;
	activity file;
	int num = 0;
	int day, month, start_time, end_time;
	char userid[50], actid[50], title[100]; float priority;
	input.open("calendar1.dat");
	while (!input.eof())
	{
		//********************************
		input >> day;
		input.ignore();
		input >> month;
		input.ignore();
		input >> start_time;
		input.ignore();
		input >> end_time;
		input.ignore();
		input.getline(userid, 50, ',');
		input.getline(actid, 50, ',');
		input.getline(title, 100, ',');
		input >> priority;
		int len = strlen(userid);
		file.userid = new char[len + 1];//+1 for null 
		stringCopy(file.userid, userid);//strcpy not working so have to make another function
		len = strlen(title);
		file.title = new char[len + 1];//+1 for null 
		stringCopy(file.title, title);
		file.duration = end_time - start_time;
		file.priority = priority;
		noOfActivity[month-1][day-1][start_time]++;
		num = noOfActivity[month-1][day-1][start_time];
		//********************************

		//adding the activity in calender
		if (num == 1)
		{
			calender[month - 1][day - 1][start_time][0] = new activity[1];
			calender[month-1][day-1][start_time][0][0] = file;
		}
		else if (num != 1)
		{
			//deepcopy
			activity* temp; temp = new activity[num];
			for (int i = 0; i < num-1; i++)
			{
				temp[i] = calender[month - 1][day - 1][start_time][0][i];
			}
			delete[]calender[month - 1][day - 1][start_time][0];
			calender[month - 1][day - 1][start_time][0] = new activity [num];
			for (int i = 0; i < num-1; i++)
			{
				calender[month - 1][day - 1][start_time][0][i]=temp[i];
			}
			calender[month - 1][day - 1][start_time][0][num-1] = file;
		}
		
	}
	input.close();		
}

//functions for use
void stringCopy(char copy[], char tocopy[])
{
	int len = strlen(tocopy);
	for (int i = 0; i < len; i++)
	{
		copy[i] = tocopy[i];
	}
	copy[len] = '\0';

}
//funtions of question
void listAllActivities(activity***** calender, char user[], int startdate, int enddate, int startmonth, int endmonth);
void listOf5Imp(activity***** calender, char user[], int startdate, int enddate, int startmonth, int endmonth);
void longestFreePeroid(activity***** calender, char user[]);
void listOfClashingActivities(activity***** calender, char userid1[],char userid2[], int startdate, int enddate, int startmonth, int endmonth);
void listOfFreeSlots(activity***** calender, char users[][10],int size, int startdate, int enddate, int startmonth, int endmonth);
void printActivityStats(activity***** calender, int month);
void printCalenderStats(activity***** calender);
void removeAUser(activity*****& calender, char user[]);
void saveTheCalender(activity***** calender);
void printAMonth(activity***** calender, int month);
void exitDeallocation(activity*****& calender);


int main()
{
	activity***** calender;
	char user[20], user1[20];
	memoryAllocate(calender);
	dataInput(calender);
	int choice = -1, startdate, enddate, startmonth, endmonth;
	while (1)
	{
		cout << "\t\t\tCALENDER APPLICATION" << endl;
		cout << "1-> List all activities of a given user during a time period." << endl;
		cout << "2-> List the 5 most important activities of a given user during a time period." << endl;
		cout << "3-> For a given user, print the longest free period." << endl;
		cout << "4-> List all the clashing activities of a pair of users." << endl;
		cout << "5-> For a list of users, and a time period, list all hourly slots that are free for all these user." << endl;
		cout << "6-> Print activity stats for a given month." << endl;
		cout << "7-> Print Calendar Stats (for the whole year)." << endl;
		cout << "8-> Remove a user from the calendar." << endl;
		cout << "9-> Save the calendar." << endl;
		cout << "10-> Print a month of the calendar." << endl;
		cout << "11-> EXIT." << endl;
		cout << "Enter your choice(1-11): ";
		cin >> choice;
		if (choice == 1)
		{
			cout << "Enter the userid: ";
			cin >> user;
			cout << "Enter the start date(1-31): ";
			cin >> startdate;
			cout << "Enter the start month(1-12): ";
			cin >> startmonth;
			cout << "Enter the end date(1-31): ";
			cin >> enddate;
			cout << "Enter the end month(1-12): ";
			cin >> endmonth;
			listAllActivities(calender, user, startdate, enddate, startmonth, endmonth);
			system("pause");
		}
		else if (choice == 2)
		{
			cout << "Enter the userid: ";
			cin >> user;
			cout << "Enter the start date(1-31): ";
			cin >> startdate;
			cout << "Enter the start month(1-12): ";
			cin >> startmonth;
			cout << "Enter the end date(1-31): ";
			cin >> enddate;
			cout << "Enter the end month(1-12): ";
			cin >> endmonth;
			listOf5Imp(calender, user, startdate, enddate, startmonth, endmonth);
			system("pause");
		}
		else if (choice == 3)
		{
			cout << "Enter the userid: ";
			cin >> user;
			longestFreePeroid(calender, user);
			system("pause");
		}
		else if (choice == 4)
		{
			cout << "Enter the userid of 1st user: ";
			cin >> user;
			cout << "Enter the userid of 2nd user: ";
			cin >> user1;
			cout << "Enter the start date(1-31): ";
			cin >> startdate;
			cout << "Enter the start month(1-12): ";
			cin >> startmonth;
			cout << "Enter the end date(1-31): ";
			cin >> enddate;
			cout << "Enter the end month(1-12): ";
			cin >> endmonth;
			listOfClashingActivities(calender, user, user1, startdate, enddate, startmonth, endmonth);
			system("pause");
		}
		else if (choice == 5)
		{
			char temp[50][10]; int i = 0;
			while (1)
			{
				cout << "Enter the userid of " << i + 1 << " user or enter 0 to stop: ";
				cin >> temp[i];
				if (temp[i][0] == '0')
				{
					break;
				}
				i++;
			}
			cout << "Enter the start date(1-31): ";
			cin >> startdate;
			cout << "Enter the start month(1-12): ";
			cin >> startmonth;
			cout << "Enter the end date(1-31): ";
			cin >> enddate;
			cout << "Enter the end month(1-12): ";
			cin >> endmonth;
			listOfFreeSlots(calender, temp, i, startdate, enddate, startmonth, endmonth);
			system("pause");
		}
		else if (choice == 6)
		{
			int month;
			cout << "Enter the month(1-12) ";
			cin >> month;
			month--;
			printActivityStats(calender, month);
			system("pause");
		}
		else if (choice == 7)
		{
			printCalenderStats(calender);
			system("pause");
		}
		else if (choice == 8)
		{
			cout << "Enter the userid : ";
			cin >> user;
			removeAUser(calender, user);
			cout << "User Removed " << endl;
			system("pause");
		}
		else if (choice == 9)
		{
			saveTheCalender(calender);
			cout << "File Saved " << endl;
			system("pause");
		}
		else if (choice == 10)
		{
			int month;
			cout << "Enter the month(1-12): ";
			cin >> month;
			printAMonth(calender, month);
			SetConsoleTextAttribute(hConsole, 15); cout << endl;
			system("pause");
		}
		else if (choice == 11)
		{
		exitDeallocation(calender);
			break;
		}
		system("cls");
	}
	cout << "Exiting!!!"<<endl;
	system("pause");
	return 0;
}

//i. List all activities of a given user during a time
void listAllActivities(activity***** calender, char user[], int startdate, int enddate, int startmonth, int endmonth)
{
	int check = 0;
	cout << "List of Activities of User::" << user << endl;
	for (int month = startmonth - 1; month < endmonth; month++)
	{
		for (int day = startdate - 1; day < days[month]; day++)
		{
			if (month == endmonth - 1 && day == enddate)
			{
				check = 1;
				break;
			}
			for (int hour = 0; hour < 24; hour++)
			{
				/*cout<<noOfActivity[month][day][hour];*/
				for (int k = 0; k < noOfActivity[month][day][hour]; k++)
				{
					if (!strcmp(calender[month][day][hour][0][k].userid, user))
					{
						cout << day + 1 << "/" << month + 1 << "  " << calender[month][day][hour][0][k].title << endl;
					}

				}
			}
		}
		if (check == 1)
		{
			break;
		}
	}
}
//**********************************
//ii. List the 5 most important activities of a given user during a time period :
void listOf5Imp(activity***** calender, char user[], int startdate, int enddate, int startmonth, int endmonth)
{
activity tt[30]; int t = 0;
temporary corordinates[30]; int c = 0;
	int check = 0;
	cout << "List of 5 Important Activities of User::" << user << endl;
	for (int month = startmonth - 1; month < endmonth; month++)
	{
		for (int day = startdate - 1; day < days[month]; day++)
		{
			if (month == endmonth - 1 && day == enddate)
			{
				check = 1;
				break;
			}
			for (int hour = 0; hour < 24; hour++)
			{
				for (int k = 0; k < noOfActivity[month][day][hour]; k++)
				{
					if (!strcmp(calender[month][day][hour][0][k].userid, user))
					{
						tt[t] = calender[month][day][hour][0][k];
						t++;
						corordinates[c].day = day;
						corordinates[c].month = month;
						corordinates[c].hour = hour;
						corordinates[c].k = k;
						c++;
					}

				}
			}

		}
		if (check == 1)
		{
			break;
		}
	}
	for (int i = 0; i < t; i++)
	{
		int min = i;

		for (int j = 0; j < t; j++)
		{
			if (tt[min].priority> tt[j].priority)
			{
				min = j;
			}
			if (min != i)
			{
				activity temp1;
				temp1 = tt[i];
				tt[i] = tt[min];
				tt[min] = temp1;
				temporary temp2;//for day and month
				temp2.day = corordinates[i].day; corordinates[i].day = corordinates[min].day; corordinates[min].day = temp2.day;
				temp2.hour = corordinates[i].hour; corordinates[i].hour = corordinates[min].hour; corordinates[min].hour = temp2.hour;
				temp2.k = corordinates[i].k; corordinates[i].k = corordinates[min].k; corordinates[min].k = temp2.k;
				temp2.month= corordinates[i].month;corordinates[i].month = corordinates[min].month;corordinates[min].month = temp2.month;
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		cout <<corordinates[i].day+1<<"/"<<corordinates[i].month+1<<"  " << tt[i].title << endl;
	}
}
//**********************************
//iii.For a given user, print the longest free period; that is, the longest consecutive num	ber of days in which the user has no activity.
void longestFreePeroid(activity***** calender, char user[])
{
	temporary corordinates[30]; int c = 0;
	int check = 0;
	for (int month = 0; month < 12; month++)
	{
		for (int day = 0; day < days[month]; day++)
		{
			for (int hour = 0; hour < 24; hour++)
			{
				for (int k = 0; k < noOfActivity[month][day][hour]; k++)
				{
					if (!strcmp(calender[month][day][hour][0][k].userid, user))
					{
						corordinates[c].day = day;
						corordinates[c].month = month;
						corordinates[c].hour = hour;
						corordinates[c].k = k;
						c++;
					}

				}
			}

		}
	}
	//now in coordinates there are all activities day month we will subtract it to find largest num of days
	int dayamount=0; int max=0;
	int endmonthdays, startmonthdays;
	int startingdate, endingdate, startingmonth, endingmonth;
	for (int i = c-1; i > 0; i--)
	{
		//last acitvit to end year check
		if (i == c-1)
		{
			if (11 - corordinates[i].month == 0)//means in dec
			{
			 dayamount = 30 - corordinates[i].day;
			 max = dayamount;
			 startingdate = corordinates[i].day; startingmonth = corordinates[i].month;
			 endingdate = 30; endingmonth = 11;		
			}
			else if (11 - corordinates[i].month != 0)
			{
				for (int k = 11; k > corordinates[i].month; k--)
				{
					dayamount = dayamount + days[k];
				}
				int remdays = days[corordinates[i].month] - (corordinates[i].day+1);//bcz 1 day is less in corodinates
				dayamount = dayamount + remdays;
				max = dayamount;
				startingdate = corordinates[i].day; startingmonth = corordinates[i].month;
				endingdate = 30; endingmonth = 11;
			}
		}
		else if (corordinates[i].month - corordinates[i - 1].month == 0)//last and 2ndlast in same month
		{

			dayamount = corordinates[i].day - corordinates[i - 1].day;
			if (max < dayamount)
			{
				max = dayamount;
				startingdate = corordinates[i - 1].day; startingmonth = corordinates[i - 1].month;
				endingdate = corordinates[i].day; endingmonth = corordinates[i].month;
			}
		}
		else if (corordinates[i].month - corordinates[i - 1].month == 1)
		{
			//end month days
			endmonthdays = corordinates[i].day;
			startmonthdays = (days[i - 1] - 1) - corordinates[i - 1].day;
			dayamount = startmonthdays + endmonthdays;
			if (max < dayamount)
			{
				max = dayamount;
				startingdate = corordinates[i - 1].day; startingmonth = corordinates[i - 1].month;
				endingdate = corordinates[i].day; endingmonth = corordinates[i].month;
			}
		}
		else if (corordinates[i].month - corordinates[i - 1].month > 1)
		{
			for (int k = corordinates[i].month; k > corordinates[i-1].month; k--)
			{
				if (k == corordinates[i].month)
				{
					dayamount = corordinates[i].day;
				}
				else
				{
					dayamount = dayamount + days[k];
				}
			}
			int remdays = (days[corordinates[i-1].month]-1) - (corordinates[i-1].day);//bcz 1 day is less in corodinates
			dayamount = dayamount + remdays;
			if (max < dayamount)
			{
				max = dayamount;
				startingdate = corordinates[i-1].day; startingmonth = corordinates[i-1].month;
				endingdate = corordinates[i].day; endingmonth = corordinates[i].month;
			}
		}
	}
	cout << "The longest consecutive number of days in which the user has no activity are::" << max<<endl;
	cout << "Starting from date " << startingdate + 1 << " of month " << startingmonth + 1 << " till date " << endingdate + 1 << " of month " << endingmonth + 1<<endl;
}
//**********************************
//iv.List all the clashing activities of a pair of users, during a time period. (Clashing activities are those that share one hour of time or more).
void listOfClashingActivities(activity***** calender, char user1[],char user2[], int startdate, int enddate, int startmonth, int endmonth)
{
	int check = 0;//used in loop to exit at end date
	cout << "Activites Clashing Details are below: " << endl;
	for (int month = startmonth - 1; month < endmonth; month++)
	{
		for (int day = startdate - 1; day < days[month]; day++)
		{
			if (month == endmonth - 1 && day == enddate)
			{
				check = 1;
				break;
			}
			for (int hour = 0; hour < 24; hour++)
			{
				for (int k = 0; k < noOfActivity[month][day][hour]; k++)
				{
					if (strcmp(calender[month][day][hour][0][k].userid, user1)==0)
					{
						for (int hour1 = 0; hour1 < 24; hour1++)
						{
							for (int l = 0; l < noOfActivity[month][day][hour1]; l++)
							{
								if (strcmp(calender[month][day][hour1][0][l].userid, user2) == 0)
								{
									int endtime = calender[month][day][hour][0][k].duration + hour;
									int endtime1 = calender[month][day][hour1][0][l].duration + hour1;
									if (hour > hour1 && hour < endtime1)
									{
										cout << user1 << " has the activity " << calender[month][day][hour][0][k].title << " starting from " << hour << " till " << (calender[month][day][hour][0][k].duration) + (hour) << " on " << day + 1 << "/" << month + 1 << endl;
										cout << user2 << " has the activity " << calender[month][day][hour1][0][l].title << " starting from " << hour1 << " till " << (calender[month][day][hour1][0][l].duration) + (hour1) << " on " << day + 1 << "/" << month + 1 << endl;
									}
									else if (endtime > hour1 && endtime < endtime1)
									{
										cout << user1 << " has the activity " << calender[month][day][hour][0][k].title << " starting from " << hour << " till " << (calender[month][day][hour][0][k].duration) + (hour) << " on " << day + 1 << "/" << month + 1 << endl;
										cout << user2 << " has the activity " << calender[month][day][hour1][0][l].title << " starting from " << hour1 << " till " << (calender[month][day][hour1][0][l].duration) + (hour1) << " on " << day + 1 << "/" << month + 1 << endl;
									}
								}
							}
						}
					}

				}
			}

		}
		if (check == 1)
		{
			break;
		}
	}
}
//**********************************
//v. For a list of users, and a time period, list all hourly slots that are free for all these user in this time period.
void listOfFreeSlots(activity***** calender, char users[][10], int size, int startdate, int enddate, int startmonth, int endmonth)
{
	int check = 0;//realted to loop
	int count = 0;//related to function
	cout << "List of Free Slots of Users::"<<endl;
	for (int month = startmonth - 1; month < endmonth; month++)
	{
		for (int day = startdate - 1; day < days[month]; day++)
		{
			if (month == endmonth - 1 && day == enddate)
			{
				check = 1;
				break;
			}
			for (int hour = 0; hour < 24; hour++)
			{
				count = 0;
				for (int k = 0; k < noOfActivity[month][day][hour]; k++)
				{
					for (int u = 0; u < size; u++)
					{
						if (!strcmp(calender[month][day][hour][0][k].userid,users[u]))
						{
							count=1;
							hour = hour+calender[month][day][hour][0][k].duration;
							hour--;//hour is going to get incremented 
							break;
						}
					}
					if(count==1)
					{
						break;
					}
				}
				if (count == 0)
				{
					cout << "Free Slot is " << hour << " on " << day + 1 << "/" << month + 1<<endl;
				}
			}

		}
		if (check == 1)
		{
			break;
		}
	}
}
//**********************************
//vi. Print activity stats for a given month
void printActivityStats(activity***** calender, int month)
{
	int totalActivities = 0;float avgNumMonth = 0; int busiestday, busiestActivitynum = 0; float sumPriority = 0, avgPriority, highesAvgPriority, priorityActivityNum, highestAvgPriorityDay;;
	int activityInDay = 0;
	for (int day = 0; day < days[month]; day++)
	{
		activityInDay = 0;
		for (int i = 0; i < 24; i++)
		{
			activityInDay = activityInDay + noOfActivity[month][day][i];
			totalActivities = totalActivities + noOfActivity[month][day][i];
			if (day == 0)
			{
				busiestActivitynum = activityInDay;
				busiestday = day;
			}
			if (busiestActivitynum < activityInDay)
			{
				busiestActivitynum = activityInDay;
				busiestday = day;
			}
		}
		sumPriority = 0;
		for (int hour = 0; hour < 24; hour++)
		{
			for (int k = 0; k < noOfActivity[month][day][hour]; k++)
			{
				sumPriority = sumPriority + calender[month][day][hour][0][k].priority;
			}
		}
		avgPriority = sumPriority / activityInDay;
		if (day == 0)
		{
			highesAvgPriority = avgPriority;
			priorityActivityNum = activityInDay;
			highestAvgPriorityDay = day;
		}
		if (highesAvgPriority < avgPriority)
		{
			highesAvgPriority = avgPriority;
			priorityActivityNum = activityInDay;
			highestAvgPriorityDay = day;
		}
	}
	avgNumMonth = (float)totalActivities / (float)days[month];
	cout << "total number of activities in the month: " << totalActivities << endl;
	cout << "average number of activities per day: " << avgNumMonth << endl;
	cout << "the busiest day of the month: " << busiestday + 1 << endl;
	cout << "number of activities in the busiest day: " << busiestActivitynum << endl;
	cout << "the day with the highest average priority of the activities(i.e.the most important day): " << highestAvgPriorityDay + 1 << endl;
	cout << "the number of activities in the most important day: " << priorityActivityNum << endl;
}
//**********************************
//vii. Print Calendar Stats (for the whole year)
void printCalenderStats(activity***** calender)
{
	int numOfActInYear = -1,busiestMonth,numOfActInBusiestMonth; float avgNumOfActPerMonth;//cout variables
	int numOfActInHour, numOfActInDay, numOfActInMonth=0;
	for (int month = 0; month < 12; month++)
	{
		numOfActInMonth = activityInMonth(calender, month);
		numOfActInYear = numOfActInYear + numOfActInMonth;
		if (month == 0)
		{
			busiestMonth = month;
			numOfActInBusiestMonth = numOfActInMonth;
		}
		if (numOfActInBusiestMonth < numOfActInMonth)
		{
			busiestMonth = month;
			numOfActInBusiestMonth = numOfActInMonth;
		}
		numOfActInMonth = 0;
	}
	avgNumOfActPerMonth = (float)numOfActInYear / 12;
	cout << "total number of activities in the year: " << numOfActInYear << endl;
	cout << "average number of activities per month: " << avgNumOfActPerMonth << endl;
	cout << "the busiest month of the year: " << busiestMonth+1 << endl;;
	cout << "number of activities in the busiest month: " << numOfActInBusiestMonth << endl;
}
//**********************************
int activityInMonth(activity***** calender, int month)//used in printCalenderStats function
{
	int totalActivities = 0;
	for (int day = 0; day < days[month]; day++)
	{
		for (int i = 0; i < 24; i++)
		{
			totalActivities = totalActivities + noOfActivity[month][day][i];	
		}
		
	}
	return totalActivities;
}
//**********************************
//viii. Remove a user from the calendar (remove all activities of this user)
void removeAUser(activity*****& calender, char user[])
{
	for (int month = 0; month < 12; month++)
	{
		for (int day = 0; day < days[month]; day++)
		{
			for (int hour = 0; hour < 24; hour++)
			{
				for (int k = 0; k < noOfActivity[month][day][hour]; k++)
				{
					if (!strcmp(calender[month][day][hour][0][k].userid, user))
					{
						int num = noOfActivity[month][day][hour];
						activity* temp; temp = new activity[num];
						for (int i = 0; i <num; i++)
						{
							temp[i] = calender[month][day][hour][0][i];
						}
						for (int kk = 0; kk < num; kk++)
						{
							delete[]calender[month][day][hour][0][kk].title;
							delete[]calender[month][day][hour][0][kk].userid;
						}
						delete[]calender[month][day][hour];
						calender[month][day][hour] = nullptr;
						noOfActivity[month][day][hour]=noOfActivity[month][day][hour]-1;
						calender[month][day][hour] = new activity * [1];
						calender[month][day][hour][0] = new activity[noOfActivity[month][day][hour]];
						int ko = 0;
						for (int i = 0; i < noOfActivity[month][day][hour]; i++)
						{
							if (temp[ko].userid == user)
							{
								ko++;
								calender[month][day][hour][0][i] = temp[ko];
								ko++;
							}
							else
							{
								calender[month][day][hour][0][i] = temp[ko]; ko++;
							}
						}
						delete[] temp;
					}

				}
			}

		}
	}
}
//**********************************
// ix.Save the calendar
void saveTheCalender(activity***** calender)
{
	ofstream output;
	int num = 0,act = 0;
	output.open("calendar1.dat");
	for (int month = 0; month < 12; month++)
	{
		for (int day = 0; day < days[month]; day++)
		{
			for (int hour = 0; hour < 24; hour++)
			{
				for (int k = 0; k < noOfActivity[month][day][hour]; k++)
				{
						int endtime = calender[month][day][hour][0][k].duration + hour;
						output << day + 1 << "/" << month + 1 << "," << hour << "," << endtime << "," << calender[month][day][hour][0][k].userid << ",act" << act << "," << calender[month][day][hour][0][k].title << "," << calender[month][day][hour][0][k].priority << endl;
						act++;
				}
			}

		}
	}
}
//**********************************
//x. Print a month of the calendar
void printAMonth(activity***** calender, int month)
{
	string names[12] = { "Januray","Feburary","March","April","May","June","July","August","September","October","November","December" };
	cout << endl << endl << endl << endl;
	cout << "                " << names[month - 1] << "                " << endl;
	cout << endl;
	cout << "Mon" <<"\t" << "Tue" << "\t" << "Wed" << "\t" << "Thurs" << "\t" << "Fri" << "\t" << "Sat" << "\t" << "Sun" << endl;

	int day1[12] = { 6,2,2,5,7,3,5,1,4,6,2,4 };
	//1st week
	int count = 0,check=0;
	
	for (int i = day1[month-1]; i <= 7; i++)
	{
		check = 0;
		if (i == day1[month - 1])
		{
			for (int j = 1; j < day1[month - 1]; j++)
			{
				cout << '\t';
			}
		}
		for (int hour = 0; hour < 24; hour++)
		{
			for (int k = 0; k < noOfActivity[month - 1][count][hour]; k++)
			{
				if (calender[month - 1][count][hour][0]!=0)
				{
					SetConsoleTextAttribute(hConsole, 15);
					check = 1;
					break;
				}

			}if (check == 1) { break; }
		}
		cout << count + 1 <<"\t"; count++;
		SetConsoleTextAttribute(hConsole, 14);
	}
	cout << endl;
	//2nd week
	for (int i = 0; i < 7; i++)
	{
		check = 0;
		for (int hour = 0; hour < 24; hour++)
		{
			for (int k = 0; k < noOfActivity[month - 1][count][hour]; k++)
			{
				if (calender[month - 1][count][hour][0] != 0)
				{
					check = 1;
					SetConsoleTextAttribute(hConsole, 15);
					break;
				}
			}if (check == 1) { break; }
		}
		cout << count + 1 << "\t"; count++;
		SetConsoleTextAttribute(hConsole, 14);
	}
	cout << endl;
	//3rd week
	for (int i = 0; i < 7; i++)
	{
		for (int hour = 0; hour < 24; hour++)
		{
			check = 0;
			for (int k = 0; k < noOfActivity[month - 1][count][hour]; k++)
			{
				if (calender[month - 1][count][hour][0] != 0)
				{
					check = 1;
					SetConsoleTextAttribute(hConsole, 15);
					break;
				}
			}if (check == 1) { break; }
		}
		cout << count + 1 << "\t"; count++;
		SetConsoleTextAttribute(hConsole, 14);
	}
	cout << endl;
	//4th week
	for (int i = 0; i < 7; i++)
	{
		for (int hour = 0; hour < 24; hour++)
		{
			check = 0;
			for (int k = 0; k < noOfActivity[month - 1][count][hour]; k++)
			{
				if (calender[month - 1][count][hour][0] != 0)
				{
					check = 1;
					SetConsoleTextAttribute(hConsole, 15);
					break;
				}
			}if (check == 1) { break; }
		}
		cout << count + 1 << "\t"; count++;
		SetConsoleTextAttribute(hConsole, 14);
	}
	//5th week
	int limit = days[month - 1] - count;
	cout << endl;
	//2nd week
	
	for (int i = 0; i < limit; i++)
	{
		for (int hour = 0; hour < 24; hour++)
		{
			check = 0;
			for (int k = 0; k < noOfActivity[month - 1][count][hour]; k++)
			{
				if (calender[month - 1][count][hour][0] != 0)
				{
					check = 1;
					SetConsoleTextAttribute(hConsole, 15);
					break;
				}
			}if (check == 1) { break; }
		}
		if (limit > 7)
		{
			if (i == 7)
			cout << endl;

		}
		cout << count + 1 << "\t"; count++;
		SetConsoleTextAttribute(hConsole, 14);
	}
}
//**********************************
//At the end of the program all the dynamically allocated memory must be deallocated.
void exitDeallocation(activity*****& calender)
{
	for (int month = 0; month < 12; month++)
	{
		for (int day = 0; day < days[month]; day++)
		{
			for (int hour = 0; hour < 24; hour++)
			{
				for (int k = 0; k < noOfActivity[month][day][hour]; k++)
				{
					delete[]calender[month][day][hour][0][k].userid;
					delete[]calender[month][day][hour][0][k].title;
				}delete[]calender[month][day][hour][0];
			}delete[]calender[month][day];
		}delete[]calender[month];
	}delete[]calender;
}
//**********************************




