#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;


enum class TaskStatus {
    NEW,
    IN_PROGRESS,
    TESTING,
    DONE
};

using TasksInfo = map<TaskStatus, int>;


TasksInfo GetRidOfEmptyStatuses(const TasksInfo& tasks) {
    TasksInfo result_tasks = tasks;
    for (auto& task : tasks) {
        if (task.second == 0) {
            result_tasks.erase(task.first);
        }
    }

    return result_tasks;
}


TaskStatus GetNextTaskStatus(const TaskStatus& current_task_status_name) {
    return static_cast<TaskStatus>(static_cast<int>(current_task_status_name) + 1);
}


class TeamTasks {
public:
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return persons.at(person);
    }

    void AddNewTask(const string& person) {
        ++persons[person][TaskStatus::NEW];
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo current_tasks = persons[person];
        TasksInfo result_tasks = current_tasks;
        TasksInfo updated_tasks;
        TasksInfo untouched_tasks;

        int task_count_remaining = task_count;
        for (const auto& current_task_status : current_tasks) {
            TaskStatus current_task_status_name = current_task_status.first;
            int current_task_status_count = current_task_status.second;
            if (current_task_status_name == TaskStatus::DONE) {
                break;
            }

            int delta = min(task_count_remaining, current_task_status_count);
            TaskStatus next_task_status_name = GetNextTaskStatus(current_task_status_name);

            result_tasks[current_task_status_name] -= delta;
            result_tasks[next_task_status_name] += delta;

            updated_tasks[next_task_status_name] = delta;
            if (current_task_status_count - delta > 0) {
                untouched_tasks[current_task_status_name] = current_task_status_count - delta;
        }

            task_count_remaining -= delta;
        }

        persons[person] = result_tasks;
        updated_tasks = GetRidOfEmptyStatuses(updated_tasks);
        untouched_tasks = GetRidOfEmptyStatuses(untouched_tasks);

        return make_tuple(updated_tasks, untouched_tasks);
    }

private:
    map<string, TasksInfo> persons;
};


void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ivan's tasks: "; PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan")); cout << endl;

    TasksInfo updated_tasks, untouched_tasks;

    // for (int i = 0; i < 3; ++i) {
    //     cout << "\n====================" << endl;
    //     tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 1);
    //     cout << "Ivan's tasks: ";
    //     PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    //     cout << "Updated Ivan's tasks: ";
    //     PrintTasksInfo(updated_tasks);
    //     cout << "Untouched Ivan's tasks: ";
    //     PrintTasksInfo(untouched_tasks);
    // }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 5);
    cout << "Updated Ivan's tasks: "; PrintTasksInfo(updated_tasks); cout << "Untouched Ivan's tasks: "; PrintTasksInfo(untouched_tasks); cout << "Ivan's tasks: "; PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan")); cout << endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 5);
    cout << "Updated Ivan's tasks: "; PrintTasksInfo(updated_tasks); cout << "Untouched Ivan's tasks: "; PrintTasksInfo(untouched_tasks); cout << "Ivan's tasks: "; PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan")); cout << endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 1);
    cout << "Updated Ivan's tasks: "; PrintTasksInfo(updated_tasks); cout << "Untouched Ivan's tasks: "; PrintTasksInfo(untouched_tasks); cout << "Ivan's tasks: "; PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan")); cout << endl;

    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ivan's tasks: "; PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan")); cout << endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: "; PrintTasksInfo(updated_tasks); cout << "Untouched Ivan's tasks: "; PrintTasksInfo(untouched_tasks); cout << "Ivan's tasks: "; PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan")); cout << endl;

    return 0;
}
