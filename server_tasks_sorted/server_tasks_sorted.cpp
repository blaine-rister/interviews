/* Create a server which can accept tasks with three fields:
 * - ID
 * - start time
 * - duration 
 *
 * The server takes in all tasks. Then, it executes them such that:
 *  - No task runs before t >= start_time
 *  - If multiple tasks can run, ties are resolved by (duration, start time) lexicographic order
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Task {
public:
	Task() : id(-1), start_time(-1), duration(-1) {};
	Task(int id, int start_time, int duration) : id(id), start_time(start_time), duration(duration) {};
	int id;
	int start_time;
	int duration;
};

bool compare_runtime(Task &t1, Task &t2) {
	return t1.start_time > t2.start_time;
}

struct {
	bool operator() (Task &t1, Task &t2) {
		return t1.duration < t2.duration || ((t1.duration == t2.duration) && t1.start_time < t2.start_time);
	}
} compare_priority;

class Server {
	int time;
	vector<Task> tasks;

public:
	Server() {
		time = 0;
	}

	void addTask(Task &task) {
		tasks.push_back(task);
	}

	void runTasks() {
		// Run all tasks and print their IDs

		// Sort tasks by start time 
	 	sort(tasks.begin(), tasks.end(), compare_runtime);

	 	// Run tasks
		priority_queue <Task, vector<Task>, decltype(compare_priority)> q(compare_priority);
		while (!tasks.empty() || !q.empty()) {
			// Fill with tasks that could start at this time
			int task_idx;
			for (task_idx = tasks.size() - 1; task_idx >= 0; task_idx--) {
				auto &task = tasks.at(task_idx);
				if (task.start_time <= time) {
					q.push(task);
				} else {
					// Since tasks are sorted by start time, stop here.
					break;
				}
			}	
			tasks.resize(task_idx + 1);

			// Check for deadlock
			if (q.empty()) {
				cerr << "Queue deadlock! No task to run!" << endl;
				exit(1);
			}

			// Run the highest-priority task
			auto &task = q.top();
			cout << "Task " << task.id << endl;
			time += task.duration;
			q.pop();
			
		}	
			
	}
};

int main() {

   // Order should be: t2, t1, t3
   Task t1(1, 0, 1);
   Task t2(2, 0, 2);
   Task t3(3, 1, 2);

   Server server;
   server.addTask(t1);
   server.addTask(t2);
   server.addTask(t3);

   server.runTasks();

   return 0;
}
