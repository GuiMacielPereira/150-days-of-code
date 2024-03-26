
// Simulation of printer in lab
//
// Printer options: 5 pages / 60 secs (high quality) or 10 pages / 60 secs (low quality)
// 20 print tasks per hour, each with 1-20 pages (uniform distribution)
// What is the waiting time on average for each task?
//
// Below is my solution with minimal help from the textbook

// Hint: Do a class for printer, queue of tasks and task
#include <queue>
#include <random>
#include <vector>
#include <iostream>

class Task {
  public:
    Task (int t, int max_pages): time_at_creation(t) { n_pages = rand() % max_pages + 1; };
    int get_wait_time (int current_time) {return current_time - time_at_creation;}
    int n_pages;  
  private:
    int time_at_creation;
};

class Printer {
  public:
    Printer (int ppm): pages_per_minute(ppm) {};
    bool begin_task (const Task* t) {
      if (!is_available) { 
        return false; 
      }
      time_to_finish_task = t->n_pages / pages_per_minute * 60;
      is_available = false;
      return true;
    }
    void tick() {
      if (time_to_finish_task==0) {
        is_available = true;
      } else {
        time_to_finish_task--;
      }
    }
  private:
    int pages_per_minute;
    bool is_available {true};
    int time_to_finish_task {0};
};

bool start_task_rand(int n_students) {
  int avg_tasks_per_student_per_hour = 2;
  return rand() % (3600 / n_students / avg_tasks_per_student_per_hour) + 1 == 1;
}

void print_task_added (const Task& t, const std::queue<Task>& q) {
  std::cout << "Task with " << t.n_pages 
            << " pages added to queue. Size of queue: " 
            << q.size() << std::endl;
}

void print_task_started (const std::queue<Task>& q) {
  std::cout << "Waiting finished. Size of queue: " << q.size() << std::endl;
}

void print_results (int avg_time, const std::queue<Task>& q) {
  std::cout << "Average waiting time per task: " << avg_time 
            << ", Tasks remaining: " << q.size() << std::endl;
}


void run_sim(int timesteps, int pages_per_minute, int n_students, int max_pages, bool verbose = false) {

  std::queue<Task> tqueue;
  Printer printer(pages_per_minute);
  std::vector<int> waiting_times {};
 
  for (int time=0; time < timesteps; time++) {
    if (start_task_rand(n_students)) {
      Task t(time, max_pages);
      tqueue.push(t);
      if (verbose) print_task_added(t, tqueue);
    }
    if (!tqueue.empty() && printer.begin_task(&tqueue.front())) {
      waiting_times.push_back(tqueue.front().get_wait_time(time));
      tqueue.pop();
      if (verbose) print_task_started(tqueue);
    } else { 
      printer.tick(); 
    }
  }
  int avg_time {0}; 
  for (int t : waiting_times) avg_time += t / waiting_times.size();
  print_results(avg_time, tqueue);
}

int main() {
  for (int i=0; i<10; i++) run_sim(3600, 5, 20, 10);
}
