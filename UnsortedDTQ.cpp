#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Finding the waiting time
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum){
    
    // Create copies of burst time to calculate reminder burst time
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++){
        rem_bt[i] = bt[i];
    }

    // All processes' arrival time
    int t = 0;

    // Traverse through all processes until finish
    while (1){
        bool done = true;
        
        for (int i = 0 ; i < n; i++){
            
            // If burst time is greater than 0, continue process
            if (rem_bt[i] > 0){
                done = false;
                
                // If burst time is more than time quantum 
                if (rem_bt[i] > quantum){
                    t += quantum; // Increase time elapsed based on time quantum
                    rem_bt[i] -= quantum; // Remaining burst time
                }
                
                // Else if it does not -- increase time elapsed based on burst time
                else{
                    t = t + rem_bt[i]; // Increase time elapsed based on burst time
                    wt[i] = t - bt[i]; // Waiting time = current time - burst time
                    rem_bt[i] = 0;
                    
                }
            }
        }
        
        // When all processes are done
        if (done == true){
            break;
        }
    }
}

// Calculate turn around time from burst time and waiting time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]){
    for (int i = 0; i < n ; i++){
        tat[i] = bt[i] + wt[i];
    }
}

// Calculate and show average waiting time and turn around time
void findavgTime(int processes[], int n, int bt[], int quantum){
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt, quantum);

    findTurnAroundTime(processes, n, bt, wt, tat);

    cout << "PN\t " << " \tBT " << " WT " << " \tTAT\n";

    for (int i=0; i<n; i++){
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i+1 << "\t\t" << bt[i] <<"\t " << wt[i] <<"\t\t " << tat[i] <<endl;
    }

    cout << "Average waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}

// Find middle point of the array
int QMed(int arr[], int size){
    if (size % 2 != 0){
        return arr[size/2];
    }
    return (arr[(size-1)/2] + arr[size/2])/2;
}


int main() {
	// Define amount of processes
	int n;
	cout << "Insert amount of processes: ";
	cin >> n;

    // Define all processes' ID
	int processes[n];
	for (int i = 0; i < n; i++){
    	cout << "Insert process' ID: ";
    	cin >> processes[i];
	}

    // Define all processes' burst time
    int burst_time[n];
	for (int i = 0; i < n; i++){
    	cout << "Insert process' burst times: ";
    	cin >> burst_time[i];
	}

    // Define time quantum
    int quantum = QMed(burst_time, n);
	cout << "The time quantum for the process is: " << quantum << "\n";

    findavgTime(processes, n, burst_time, quantum);
    return 0;
}
