#include "Header.h";

using namespace std;

/*
Job Sequencing Problem with Deadlines
Given a list of tasks with deadlines and total profit earned on completing a task, find the maximum profit earned by executing the tasks within the specified deadlines. Assume that each task takes one unit of time to complete, and a task can’t execute beyond its deadline. Also, only a single task will be executed at a time.

For example, consider the following set of tasks with a deadline and the profit associated with it. If we choose tasks 1, 3, 4, 5, 6, 7, 8, and 9, we can achieve a maximum profit of 109. Note that task 2 and task 10 are left out.

Tasks	Deadlines	Profit
1	9	15
2	2	2
3	5	18
4	7	1
5	4	25
6	2	20
7	5	8
8	7	10
9	4	12
10	3	5
Practice This Problem

We can easily solve this problem by following a Greedy approach. The idea is simple – consider each task decreasing order of their profits and schedule it in the latest possible free slot that meets its deadline. If no such slot is there, don’t schedule the task.

The following table shows the tasks arranged based on their associated profits. Here, task 5 has a maximum priority associated with it as it has a maximum gain of 30. Similarly, task 4 has the least priority. The greedy approach will consider the tasks in decreasing order of their priority.

Tasks	Deadlines	Profit (Maximum first)
5	4	25
6	2	20
3	5	18
1	9	15
9	4	12
8	7	10
7	5	8
10	3	5
2	2	2
4	7	1

To demonstrate the greedy approach, let’s consider the deadlines in the form of a circular structure, as shown below. A given task can fill each slot. Now, let’s start allocated the tasks based on the deadlines. We will start with task 5, having a deadline of 4, and fill it empty slot 3–4.

Job Scheduling – Step 2

Next, consider task 6 having deadline 2 and fill it empty slot 1–2.

Job Scheduling – Step 3

Next, consider task 3 having deadline 5 and fill it empty slot 4–5.

Job Scheduling – Step 4

Next, consider task 1 having deadline 9 and fill it empty slot 8–9.

Job Scheduling – Step 5

Next, consider task 9 having deadline 4. As slot 3–4 is already filled with task 5, we will consider the next free slot 2–3 and assign task 9.

Job Scheduling – Step 6

Next, consider task 8 having deadline 7 and fill it empty slot 6–7.

Job Scheduling – Step 7

Next, consider task 7 having a deadline of 5. As slot 4–5 is already filled with task 3, we will consider the next free slot 0–1 and assign task 7.

Job Scheduling – Step 8

Next, consider task 10 having a deadline of 3. Since all slots before deadline 3 are filled, ignore the task. Similarly, ignore the next task 2 having deadline 2.

The last task is task 4, having deadline 7, gets the next empty slot 6–5.

Job Scheduling – Step 9

Following is the implementation of the above approach in C++
The time complexity of the above solution is O(n2), where n is the total number of jobs.

*/


// stores the maximum deadleine that can be associated with a job
#define T 15

// Data structure to store job details each job has an identifier
// a deadline, and profit associated with it
struct Job
{
	int taskId, deadline, profit;
};

// Function to schedule jobs to maximize profit
void scheduleJobs(vector<Job> jobs) // no ref no c onst
{
	// stores the maximum profit that can be earned by scheduling jobs
	int profit = 0;

	// array to store used and unused slots info
	vector<int> slot(T, -1);

	// arrange the jobs in decreasing order of their profits
	sort(jobs.begin(), jobs.end(), [](Job& a, Job& b)
		{
			return a.profit > b.profit; // using c++ 11 lambda comparison
		});

	// consider each job in decreasing order of their profits
	for (const Job& job : jobs)
	{
		// search for the next free slot and map the task to that slot
		for (int j = job.deadline - 1; j >= 0; j--)
		{
			if (j < T && slot[j] == -1)
			{
				slot[j] = job.taskId;
				profit += job.profit;
				break;
			}
		}
	}

	// print the scheduled jobs
	cout << "the scheduled jobs are ";
	for (int i = 0; i < T; i++)
	{
		if (slot[i] != -1)
		{
			cout << slot[i] << " ";
		}
	}

	// print the total profit that can be earned 
	cout << "\n the total profit earned is " << profit;
}


int main()
{
	// vector of given jobs. Each job has an identifier, a deadline, and
   // profit associated with it
	vector<Job> jobs =
	{
		{1, 9, 15}, {2, 2, 2}, {3, 5, 18}, {4, 7, 1}, {5, 4, 25},
		{6, 2, 20}, {7, 5, 8}, {8, 7, 10}, {9, 4, 12}, {10, 3, 5}
	};

	// schedule jobs and calculate the maximum profit
	scheduleJobs(jobs);

	return 0;
}

/*

*/