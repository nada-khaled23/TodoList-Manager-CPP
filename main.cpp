
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// هيكل لتخزين بيانات المهمة
struct Task {
    string description;
    bool isCompleted;
};

// دالة عرض القائمة الرئيسية
void showMenu() {
    cout << "\n=== To-Do List Manager ===" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Mark Task as Complete" << endl;
    cout << "4. Delete Task" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

// دالة إضافة مهمة جديدة
void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, newTask.description);
    newTask.isCompleted = false;
    
    tasks.push_back(newTask);
    cout << "Task added successfully!" << endl;
}

// دالة عرض المهام
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "Your to-do list is empty." << endl;
        return;
    }
    
    cout << "\n--- Your Tasks ---" << endl;
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". [" << (tasks[i].isCompleted ? "X" : " ") << "] " 
             << tasks[i].description << endl;
    }
}

// دالة تحديد المهمة كمكتملة
void completeTask(vector<Task>& tasks) {
    viewTasks(tasks);
    if (tasks.empty()) return;
    
    int taskNum;
    cout << "Enter the number of the task to mark complete: ";
    cin >> taskNum;
    
    if (taskNum > 0 && taskNum <= (int)tasks.size()) {
        tasks[taskNum - 1].isCompleted = true;
        cout << "Task marked as complete!" << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

// دالة حذف مهمة
void deleteTask(vector<Task>& tasks) {
    viewTasks(tasks);
    if (tasks.empty()) return;
    
    int taskNum;
    cout << "Enter the number of the task to delete: ";
    cin >> taskNum;
    
    if (taskNum > 0 && taskNum <= (int)tasks.size()) {
        tasks.erase(tasks.begin() + (taskNum - 1));
        cout << "Task deleted successfully." << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

// دالة حفظ المهام في ملف
void saveTasksToFile(const vector<Task>& tasks) {
    ofstream outFile("tasks.txt");
    for (const auto& task : tasks) {
        outFile << task.isCompleted << "," << task.description << endl;
    }
    outFile.close();
}

// دالة تحميل المهام من الملف
void loadTasksFromFile(vector<Task>& tasks) {
    ifstream inFile("tasks.txt");
    if (!inFile.is_open()) return;
    
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        bool status = line[0] == '1';
        string desc = line.substr(2);
        tasks.push_back({desc, status});
    }
    inFile.close();
}

int main() {
    vector<Task> tasks;
    loadTasksFromFile(tasks);
    
    int choice;
    do {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                completeTask(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                saveTasksToFile(tasks);
                cout << "Tasks saved. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);
    
    return 0;
}