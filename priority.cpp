#include <iostream>
#include <algorithm>
using namespace std;

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int remaining_time;
    int start_time;
};

void calculateCompletionTime(Process arr[], int n)
{
    int current_time = 0;
    int completed = 0;

    while (completed < n)
    {
        int idx = -1;
        int highest_priority = INT16_MAX;

        for (int i = 0; i < n; i++)
        {
            if (arr[i].arrival_time <= current_time && arr[i].remaining_time > 0)
            {
                if (arr[i].priority < highest_priority || (arr[i].priority == highest_priority && arr[i].arrival_time < arr[idx].arrival_time))
                {
                    highest_priority = arr[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            if (arr[idx].remaining_time == arr[idx].burst_time)
            {
                arr[idx].start_time = current_time;
            }
            current_time++;
            arr[idx].remaining_time--;

            if (arr[idx].remaining_time == 0)
            {
                arr[idx].completion_time = current_time;
                arr[idx].turn_around_time = arr[idx].completion_time - arr[idx].arrival_time;
                arr[idx].waiting_time = arr[idx].turn_around_time - arr[idx].burst_time;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }
}

void display(Process arr[], int n)
{
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    cout << "PID\tArrival\tBurst\tPriority\tStart\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i].pid << "\t" << arr[i].arrival_time << "\t" << arr[i].burst_time << "\t" << arr[i].priority << "\t\t"
             << arr[i].start_time << "\t" << arr[i].completion_time << "\t\t" << arr[i].turn_around_time << "\t\t" << arr[i].waiting_time << "\n";
        total_waiting_time += arr[i].waiting_time;
        total_turnaround_time += arr[i].turn_around_time;
    }
    cout << "Average Waiting Time: " << total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << total_turnaround_time / n << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process arr[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Process ID, Arrival Time, Burst Time, and Priority for process " << i + 1 << ": ";
        cin >> arr[i].pid >> arr[i].arrival_time >> arr[i].burst_time >> arr[i].priority;
        arr[i].remaining_time = arr[i].burst_time;
    }

    calculateCompletionTime(arr, n);
    display(arr, n);

    return 0;
}
