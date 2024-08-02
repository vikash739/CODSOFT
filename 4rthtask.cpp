#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string description;
    bool completed;

    Task(string desc) : description(desc), completed(false) {}
};

void displayMenu() {
    cout << "\nTo-Do List Manager" << endl;
    cout << "------------------" << endl;
    cout << "1. View To-Do List" << endl;
    cout << "2. Add Task" << endl;
    cout << "3. Mark Task as Completed" << endl;
    cout << "4. Remove Task" << endl;
    cout << "5. Exit" << endl;
    cout << "------------------" << endl;
}

void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\nNo tasks in the to-do list." << endl;
    } else {
        cout << "\nTo-Do List:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". [" << (tasks[i].completed ? "X" : " ") << "] " << tasks[i].description << endl;
        }
    }
}

void addTask(vector<Task>& tasks) {
    string task;
    cout << "\nEnter the task: ";
    cin.ignore();  
    getline(cin, task);
    tasks.emplace_back(task);
    cout << "Task '" << task << "' added to the list." << endl;
}

void markTaskAsCompleted(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\nNo tasks to mark as completed." << endl;
    } else {
        int taskNum;
        cout << "\nEnter the task number to mark as completed: ";
        cin >> taskNum;
        if (taskNum > 0 && taskNum <= static_cast<int>(tasks.size())) {
            tasks[taskNum - 1].completed = true;
            cout << "Task '" << tasks[taskNum - 1].description << "' marked as completed." << endl;
        } else {
            cout << "Invalid task number." << endl;
        }
    }
}

void removeTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\nNo tasks to remove." << endl;
    } else {
        int taskNum;
        cout << "\nEnter the task number to remove: ";
        cin >> taskNum;
        if (taskNum > 0 && taskNum <= static_cast<int>(tasks.size())) {
            string removedTask = tasks[taskNum - 1].description;
            tasks.erase(tasks.begin() + taskNum - 1);
            cout << "Task '" << removedTask << "' removed from the list." << endl;
        } else {
            cout << "Invalid task number." << endl;
        }
    }
}

int main() {
    vector<Task> tasks;
    while (true) {
        displayMenu();
        int choice;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewTasks(tasks);
                break;
            case 2:
                addTask(tasks);
                break;
            case 3:
                markTaskAsCompleted(tasks);
                break;
            case 4:
                removeTask(tasks);
                break;
            case 5:
                cout << "Exiting the To-Do List Manager. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }
    }
}

