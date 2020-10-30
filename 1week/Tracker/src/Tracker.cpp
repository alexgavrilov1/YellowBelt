#include <iostream>
#include <tuple>
#include <map>
#include <string>

using namespace std;

// Перечислимый тип для статуса задачи

enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса

 using TasksInfo = map<TaskStatus, int>;

TasksInfo operator+(const TasksInfo& left, const TasksInfo& right){
	TasksInfo result;
	for(const auto& item: left){
		result[item.first] = item.second;
	}
	for(const auto& item: right){
		result[item.first] += item.second;
	}
	return result;
}

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const{
	  return tracker.at(person);
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person){
	  tracker[person][TaskStatus::NEW]++;
  }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count){
	  TasksInfo update, untouch;
	  if(tracker.count(person) == 0){
		  return make_tuple(TasksInfo{},TasksInfo{});
	  }
	  for(const auto& item: tracker[person]){
		  if(item.first == TaskStatus::DONE){
			  untouch[TaskStatus::DONE] = item.second;
		  }
		  else{
			  if(item.second > task_count){
				  untouch[item.first] = item.second - task_count;
				  if(task_count != 0){
					  update[static_cast<TaskStatus>(static_cast<int>(item.first) + 1)] = task_count;
				  }
				  task_count = 0;
			  }
			  else{
				  update[static_cast<TaskStatus>(static_cast<int>(item.first) + 1)] = item.second;
				  task_count -= item.second;
			  }
		  }

	  }
	  tracker[person] = update + untouch;
	  untouch.erase(TaskStatus::DONE);
	  return make_tuple(update, untouch);
  }
private:
  map<string , TasksInfo> tracker;
};

void PrintTasksInfo(const TasksInfo& tasks_info) {
    if (tasks_info.count(TaskStatus::NEW)) {
        std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
    }
    if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
        std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
    }
    if (tasks_info.count(TaskStatus::TESTING)) {
        std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
    }
    if (tasks_info.count(TaskStatus::DONE)) {
        std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
    }
}

void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
    std::cout << "Updated: [";
    PrintTasksInfo(updated_tasks);
    std::cout << "] ";

    std::cout << "Untouched: [";
    PrintTasksInfo(untouched_tasks);
    std::cout << "] ";

    std::cout << std::endl;
}


int main() {
	TeamTasks tasks;
	    TasksInfo updated_tasks;
	    TasksInfo untouched_tasks;


	    std::cout << "\nLisa" << std::endl;

	    for (auto i = 0; i < 5; ++i) {
	        tasks.AddNewTask("Lisa");
	    }

	    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

	    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

	    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
	    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

	    for (auto i = 0; i < 5; ++i) {
	        tasks.AddNewTask("Lisa");
	    }

	    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
	    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]

	    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
	    std::cout << std::endl;

	    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
	    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

	    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
	    std::cout << std::endl;

	    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]

	    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": 2}
	    std::cout << std::endl;

	    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
	    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]

	    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
	    std::cout << std::endl;

	    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
	    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

	    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
	    std::cout << std::endl;

	    tasks.AddNewTask("Lisa");

	    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
	    std::cout << std::endl;

	    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
	    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

	    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
	    std::cout << std::endl;

	    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
	    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

	    return 0;
}
