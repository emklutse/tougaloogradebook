// Grade Book.cpp : Defines the entry point for the console application.
// Program written by Emmanuel Klutse on 14/02/2018

#include "pch.h"
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

/* Global Constant Variables: Number of students, Number of test scores */
const int NUM_SCORES = 4,
NUM_STUDENTS = 5;

/* Function Prototypes: Get data, Calculate average, Get letter grades,
Display result */
void getData(string[], string[], double[][NUM_SCORES]);
void dropLowest(const double[][NUM_SCORES], double[]);
void calcAverage(const double[][NUM_SCORES], double[], double[]);
void getLetterGrade(const double[], char[]);
void displayResult(const string[], const string[], const double[][NUM_SCORES],
	const double[], const char[], const double[]);

int main()
{
	/* Array variables: Names, Subjects, Letter grades, Scores,
	Average */
	string names[NUM_STUDENTS] = { " " };
	string subjects[NUM_SCORES] = { "Math", "Bio", "Chem", "His" };

	char letterGrades[5] = { 'A', 'B', 'C', 'D', 'F' };

	double scores[NUM_STUDENTS][NUM_SCORES] = { { 0.0 } };
	double lowest[5] = { 0.0 };
	double average[NUM_STUDENTS] = { 0.0 };

	/* Call: getData, calcAverage, getLetterGrade, displayResult */
	getData(names, subjects, scores);
	dropLowest(scores, lowest);
	calcAverage(scores, average, lowest);
	getLetterGrade(average, letterGrades);
	displayResult(names, subjects, scores, average, letterGrades, lowest);

	system("pause");
	return 0;
}

/* **********************************************************
Definition: getData

This function accepts the following arrays as arguments:

* names[]
* subjects[]
* scores[]

This function asks the user for five student names, and
their four test scores.
********************************************************** */

void getData(string names[], string subjects[], double scores[][NUM_SCORES])
{
	/* Variables: Name index, Score index (loop counters) */
	int namesIdx = 0,
		scoresIdx = 0,
		inputCtrl = 0;

	/* Display: Header */
	cout << "\t\TOUGALOO COLLEGE - STUDENT SCORE REPORT\n\n";

	/* These loops get the five student names from the user which
	are stored in names[], and then ask for the five sets of
	four scores, which are then stored in scores[][] */
	for (namesIdx = 0; namesIdx < NUM_STUDENTS; namesIdx++)
	{
		cout << "Enter name of the student: ";
		cin >> names[namesIdx];

		for (scoresIdx = 0; scoresIdx < NUM_SCORES; scoresIdx++)
		{
			cout << subjects[scoresIdx] << " score: ";
			cin >> scores[namesIdx][scoresIdx];

			/* Input validation */
			for (inputCtrl = 0; scores[namesIdx][scoresIdx] < 0.0 ||
				scores[namesIdx][scoresIdx] > 100.0; inputCtrl++)
			{
				cout << "\nInput failure: A number below 0.0 or above 100.0\n"
					<< "was entered. Please repeat your input.\n";
				cout << subjects[scoresIdx] << " score: ";
				cin >> scores[namesIdx][scoresIdx];
			}
		}
		cout << endl;
	}
}

/* **********************************************************
Definition: dropLowest

This function accepts the following array as argument:

* scores[][]
* lowest[]

It determines and stores the lowest scores in lowest[].
********************************************************** */

void dropLowest(const double scores[][NUM_SCORES], double lowest[])
{
	/* Variables: Lower (accumulator), Index of names, Index of scores
	(loop counters) */
	int namesIdx = 0,
		scoresIdx = 0;

	double lower = scores[NUM_STUDENTS][0];


	for (namesIdx = 0; namesIdx < NUM_STUDENTS; namesIdx++)
	{
		/* Reset: Lower */
		lower = scores[namesIdx][0];

		/* The lowest values found are stored in lowest[] */
		for (scoresIdx = 0; scoresIdx < NUM_SCORES; scoresIdx++)
		{
			if (scores[namesIdx][scoresIdx] < lower)
				lower = scores[namesIdx][scoresIdx];
			lowest[namesIdx] = lower;
		}
	}
}

/* **********************************************************
Definition: getAverage

This function accepts the following array as its argument:

* scores[][]
* average[]
* lowest[]

It calculates the average sum for each student and set of
test scores stored in the scores[][] array, and stores the
result in average[].
********************************************************** */

void calcAverage(const double scores[][NUM_SCORES], double average[],
	double lowest[])
{
	/* Variables: Total (accumulator), Scores index,
	Names index (loop counters) */
	double total = 0.0;

	int scoresIdx = 0,
		namesIdx = 0;

	/* These loops calculate the total sum and the average for each
	set of scores. The results are stored in average[] */
	for (int namesIdx = 0; namesIdx < NUM_STUDENTS; namesIdx++)
	{
		/* Reset: total */
		total = 0.0;

		/* Modification: The lowest score dropped is subtracted from
		total and divided by scoresIdx instead of NUM_SCORES */
		for (int scoresIdx = 0; scoresIdx < NUM_SCORES; scoresIdx++)
		{
			total += scores[namesIdx][scoresIdx];
			average[namesIdx] = (total - lowest[namesIdx]) / scoresIdx;
		}
	}
}

/* **********************************************************
Definition: getLetterGrade

This function accepts the following arrays as arguments:

* letterGrades[]
* average[]

It determines and assigns the letter grades based on the
average scores of each student, and stores the result in
grades[].
********************************************************** */

void getLetterGrade(const double average[], char grades[])
{
	/* Variable: Name index (loop counter) */
	int namesIdx = 0;

	/* These ternary operators determine and assign the letter grades */
	for (namesIdx = 0; namesIdx < NUM_STUDENTS; namesIdx++)
	{
		average[namesIdx] >= 90.0 && average[namesIdx] <= 100.0 ? grades[namesIdx] = 'A' :
			average[namesIdx];
		average[namesIdx] >= 80.0 && average[namesIdx] <= 89.9 ? grades[namesIdx] = 'B' :
			average[namesIdx];
		average[namesIdx] >= 70.0 && average[namesIdx] <= 79.9 ? grades[namesIdx] = 'C' :
			average[namesIdx];
		average[namesIdx] >= 60.0 && average[namesIdx] <= 69.9 ? grades[namesIdx] = 'D' :
			average[namesIdx];
		average[namesIdx] >= 0.0 && average[namesIdx] <= 59.9 ? grades[namesIdx] = 'F' :
			average[namesIdx];
	}
}

/* **********************************************************
Definition: displayResults

This function accepts the following arrays as arguments:

* studentNames[]
* subjects[]
* letterGrades[]
* scores[][]
* lowest[]
* average[]

It displays the test results and final letter grades for
each student.
********************************************************** */

void displayResult(const string dNames[], const string dSubjects[],
	const double dScores[][NUM_SCORES], const double dAverage[],
	const char dLetterGrade[], const double lowest[])
{
	/* Variable: Index of names, Index of scores (loop counter) */
	int namesIdx = 0,
		scoresIdx = 0;

	/* Display: Header*/
	cout << "\t\TOUGALOO COLLEGE - STUDENT SCORE REPORT\n\n"
		<< "\t(The lowest score will be dropped!)\n\n"
		<< "Student Name: " << "\t\t" << "Subject: " << "\t\t"
		<< "Score:\n";

	/* Display: The scores, averages and letter grades of each student */
	for (namesIdx = 0; namesIdx < NUM_STUDENTS; namesIdx++)
	{
		cout << fixed << showpoint << setprecision(1);

		cout << "\n-----------------------------------------------------\n"
			<< setw(10) << left << dNames[namesIdx] << endl;

		for (scoresIdx = 0; scoresIdx < NUM_SCORES; scoresIdx++)
		{
			cout << setw(28) << right << dSubjects[scoresIdx]
				<< setw(25) << right << dScores[namesIdx][scoresIdx] << "\n";
		}

		for (int i = 0; i < 1; i++)
		{
			cout << setw(54) << right << "------\n";
		}

		/* Modification: Display the lowest score that has been dropped */
		cout << "Dropped: "
			<< setw(44) << right << lowest[namesIdx] << endl;

		cout << "Average: " << setw(44) << right << dAverage[namesIdx]
			<< setw(10) << left;

		cout << "\n-----------------------------------------------------\n";
		cout << "Final Letter Grade: "
			<< setw(8) << right << dLetterGrade[namesIdx] << "\n";
	}
}