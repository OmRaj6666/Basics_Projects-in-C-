#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Task
{
    string description;
    bool completed;
};

vector<Task> tasks;

void displayMenu()
{
    cout << "\nTo-Do List Manager\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Delete Task\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void addTask()
{
    Task newTask;
    cout << "Enter task description: ";
    cin.ignore(); // Clear input buffer
    getline(cin, newTask.description);
    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Task added successfully!\n";
}

void viewTasks()
{
    if (tasks.empty())
    {
        cout << "No tasks in the list.\n";
        return;
    }

    cout << "\nTask List:\n";
    for (size_t i = 0; i < tasks.size(); i++)
    {
        cout << i + 1 << ". ";
        cout << (tasks[i].completed ? "[X] " : "[ ] ");
        cout << tasks[i].description << "\n";
    }
}

void markCompleted()
{
    viewTasks();
    if (tasks.empty())
        return;

    int taskNumber;
    cout << "Enter task number to mark as completed: ";
    cin >> taskNumber;

    if (taskNumber > 0 && taskNumber <= static_cast<int>(tasks.size()))
    {
        tasks[taskNumber - 1].completed = true;
        cout << "Task marked as completed!\n";
    }
    else
    {
        cout << "Invalid task number!\n";
    }
}

void deleteTask()
{
    viewTasks();
    if (tasks.empty())
        return;

    int taskNumber;
    cout << "Enter task number to delete: ";
    cin >> taskNumber;

    if (taskNumber > 0 && taskNumber <= static_cast<int>(tasks.size()))
    {
        tasks.erase(tasks.begin() + taskNumber - 1);
        cout << "Task deleted successfully!\n";
    }
    else
    {
        cout << "Invalid task number!\n";
    }
}

int main()
{
    int choice;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addTask();
            break;
        case 2:
            viewTasks();
            break;
        case 3:
            markCompleted();
            break;
        case 4:
            deleteTask();
            break;
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}