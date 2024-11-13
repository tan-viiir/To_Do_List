#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Task {
public:
    string description;
    string dueDate;
    string priority;
    bool completed;

    Task(string desc, string date, string prio) {
        description = desc;
        dueDate = date;
        priority = prio;
        completed = false;
    }
};

class ToDoList {
    vector<Task> tasks;

public:
    void addTask(string desc, string dueDate, string priority) {
        tasks.push_back(Task(desc, dueDate, priority));
        cout << "Added task.\n";
    }

    void viewTasks() {
        for (int i = 0; i < tasks.size(); i++) {
            cout << (i + 1) << ". " << tasks[i].description
                 << " [Due: " << tasks[i].dueDate
                 << ", Priority: " << tasks[i].priority
                 << ", " << (tasks[i].completed ? "Done" : "Not Done") << "]\n";
        }
    }

    void markComplete(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].completed = true;
            cout << "Task marked as complete.\n";
        } else {
            cout << "Invalid task number.\n";
        }
    }

    void deleteTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
            cout << "Task deleted.\n";
        } else {
            cout << "Invalid task number.\n";
        }
    }

    void saveToFile(string filename) {
        ofstream file(filename);
        for (auto &task : tasks) {
            file << task.description << ";" << task.dueDate << ";" 
                 << task.priority << ";" << task.completed << "\n";
        }
        file.close();
        cout << "Tasks saved.\n";
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) return;
        tasks.clear();
        string line;
        while (getline(file, line)) {
            int pos1 = line.find(';');
            int pos2 = line.find(';', pos1 + 1);
            int pos3 = line.find(';', pos2 + 1);
            string desc = line.substr(0, pos1);
            string date = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string prio = line.substr(pos2 + 1, pos3 - pos2 - 1);
            bool completed = (line.back() == '1');
            Task task(desc, date, prio);
            task.completed = completed;
            tasks.push_back(task);
        }
        file.close();
        cout << "Tasks loaded.\n";
    }

    void sortTasks(string criteria) {
        if (criteria == "date") {
            sort(tasks.begin(), tasks.end(), [](Task &a, Task &b) {
                return a.dueDate < b.dueDate;
            });
        } else if (criteria == "priority") {
            sort(tasks.begin(), tasks.end(), [](Task &a, Task &b) {
                return a.priority < b.priority;
            });
        } else {
            cout << "Invalid sorting option.\n";
        }
    }
};

int main() {
    ToDoList todo;
    todo.loadFromFile("tasks.txt");
    int choice;
    while (true) {
        cout << "\n1. Add Task\n2. View Tasks\n3. Mark Complete\n4. Delete Task\n5. Sort Tasks\n6. Save & Exit\nChoice: ";
        cin >> choice;
        if (choice == 6) break;
        if (choice == 1) {
            string desc, dueDate, priority;
            cout << "Description: ";
            cin.ignore();
            getline(cin, desc);
            cout << "Due date (YYYY-MM-DD): ";
            getline(cin, dueDate);
            cout << "Priority (High, Medium, Low): ";
            getline(cin, priority);
            todo.addTask(desc, dueDate, priority);
        } else if (choice == 2) {
            todo.viewTasks();
        } else if (choice == 3) {
            int index;
            cout << "Task number to mark complete: ";
            cin >> index;
            todo.markComplete(index - 1);
        } else if (choice == 4) {
            int index;
            cout << "Task number to delete: ";
            cin >> index;
            todo.deleteTask(index - 1);
        } else if (choice == 5) {
            string criteria;
            cout << "Sort by (date/priority): ";
            cin >> criteria;
            todo.sortTasks(criteria);
        } else {
            cout << "Invalid choice.\n";
        }
    }

    todo.saveToFile("tasks.txt");
    cout << "Tasks saved. Goodbye!\n";
    return 0;
}
