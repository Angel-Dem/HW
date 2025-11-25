#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <random>
#include <iomanip>

enum class ContainerType { //container type
    Vector,
    Deque,
    List
};

enum class Operation { //operation type
    PushBack,
    PushFront,
    RandomInsert,
    RandomErase,
    IterateSum,
    RandomAccess
};
enum class TimeUnit { // time units
    Milliseconds,
    Seconds
};

union TimeValue { //measured time values
    double ms;
    double sec;
};

struct TimeResult {
    ContainerType ct;
    Operation op;
    TimeUnit unit;
    TimeValue val;
};

template<class Seq>
double measure_push_back(int N, int repeats) {
    std::vector<int> payload(N);
    std::mt19937 gen(12345); // генератор случайных чисел
    std::uniform_int_distribution<int> dist(0, 1000000);
    for (int &x : payload) x = dist(gen);

    double total = 0.0;
    Seq c;

    for (int i = 0; i < repeats; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        c.clear();
        for (int x : payload) c.push_back(x);
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    return total / repeats; // average time in milliseconds
}

template<class Seq>
double measure_push_front(int N, int repeats) {
    std::vector<int> payload(N);
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(0, 1000000);

    for (int &x : payload) x = dist(gen);

    double total = 0.0;
    Seq c;

    for (int i = 0; i < repeats; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        c.clear();
        for (int x : payload) c.insert(c.begin(), x);
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    return total / repeats;
}

template<class Seq>
double measure_random_insert(int N, int repeats) {
    std::vector<int> payload(N);
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(0, 1000000);

    for (int &x : payload) x = dist(gen);
    int count = 0;

    double total = 0.0;
    Seq c;
    std::mt19937 pos_gen(54321);
    for (int i = 0; i < repeats; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        c.clear();
        for (int x : payload) {
            int current_size = c.size();
            // if (N == 262144) {
            //     count ++;
            //     std::cout<<count<<"\n";
            // }
            std::uniform_int_distribution<int> pos_dist(0, current_size);
            int rand_index = pos_dist(pos_gen);
            auto it = std::next(c.begin(), rand_index);
            c.insert(it, x);
        }
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    return total / repeats;
}

template<class Seq>
double measure_random_erase(int N, int repeats = 10) {
    std::vector<int> payload(N);
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(0, 1000000);

    for (int &x : payload) x = dist(gen);

    double total = 0.0;
    Seq c;
    std::mt19937 pos_gen(54321);
    for (int i = 0; i < repeats; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        c.clear();
        for (int x : payload) {
            int current_size = c.size();

            std::uniform_int_distribution<int> pos_dist(0, current_size);
            int rand_index = pos_dist(pos_gen);
            auto it = std::next(c.begin(), rand_index);
            c.erase(it, x);
        }
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    return total / repeats;
}

template<class Seq>
double measure_iterate_sum(int N, int repeats) {
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist_payload(0, 1000000);
    Seq c;
    for (int i = 0; i < N; ++i) {
        c.insert(c.end(), dist_payload(gen));
    }

    double total_time_ms = 0.0;

    for (int i = 0; i < repeats; ++i) {
        long long sum = 0;

        auto start = std::chrono::high_resolution_clock::now();
        for (int x : c) {
            sum += x;
        }

        auto end = std::chrono::high_resolution_clock::now();
        total_time_ms += std::chrono::duration<double, std::milli>(end - start).count();
        (void)sum;
    }

    return total_time_ms / repeats;
}

template<class Seq>
double measure_random_access(int N, int repeats) {
    //if (repeats == 1) std::cout<<"LOOONG\n";
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist_payload(0, 1000000);
    Seq c;
    for (int i = 0; i < N; ++i) {
        c.insert(c.end(), dist_payload(gen));
    }
    std::mt19937 pos_gen(54321);
    std::uniform_int_distribution<int> dist_index(0, N - 1);

    double total_time_ms = 0.0;

    volatile int dummy_sum = 0;
    for (int i = 0; i < repeats; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int k = 0; k < N; ++k) {
            //std::cout<<k<<'\n';
            int rand_index = dist_index(pos_gen);
            auto it = std::next(c.begin(), rand_index);
            dummy_sum += *it;
        }

        auto end = std::chrono::high_resolution_clock::now();

        total_time_ms += std::chrono::duration<double, std::milli>(end - start).count();
    }

    return total_time_ms / repeats;
}


struct TestFunction {
    std::string name;
    double (*func)(int, int);
};

int main() {
    const int repeats = 10;
    const std::vector<int> N_sizes = {1048576};

    std::cout << "--- STL Container Benchmark (Time in ms, averaged over " << repeats << " repeats) ---\n\n";

    const std::vector<std::string> test_names = {
        "PushBack",
        "PushFront",
        "RandomInsert",
        "IterateSum",
        "RandomAccess"
    };

    for (int N : N_sizes) {
        if (N>1000000) N = 350000;
        std::cout << "N = " << N << " elements\n";
        // Заголовок таблицы
        std::cout << std::left << std::setw(15) << "Test"
                  << std::setw(15) << "vector"
                  << std::setw(15) << "deque"
                  << std::setw(15) << "list" << "\n";
        std::cout << "\n";

        double time_vec = measure_push_back<std::vector<int>>(N, repeats);
        double time_deq = measure_push_back<std::deque<int>>(N, repeats);
        double time_list = measure_push_back<std::list<int>>(N, repeats);

        std::cout << std::left << std::setw(15) << test_names[0]
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_vec
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_deq
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_list << "\n";

        double time_vec_1 = measure_push_front<std::vector<int>>(N, repeats);
        double time_deq_1 = measure_push_front<std::deque<int>>(N, repeats);
        double time_list_1 = measure_push_front<std::list<int>>(N, repeats);

        std::cout << std::left << std::setw(15) << test_names[1]
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_vec_1
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_deq_1
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_list_1 << "\n";


        double time_vec_2 = measure_random_insert<std::vector<int>>(N, repeats);
        double time_deq_2 = measure_random_insert<std::deque<int>>(N, repeats);
        double time_list_2 = measure_random_insert<std::list<int>>(N, repeats);

        std::cout << std::left << std::setw(15) << test_names[2]
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_vec_2
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_deq_2
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_list_2  << "\n";

        double time_vec_3 = measure_iterate_sum<std::vector<int>>(N, repeats);
        double time_deq_3 = measure_iterate_sum<std::deque<int>>(N, repeats);
        double time_list_3 = measure_iterate_sum<std::list<int>>(N, repeats);

        std::cout << std::left << std::setw(15) << test_names[3]
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_vec_3
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_deq_3
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_list_3 << "\n";


        double time_vec_4 = measure_random_access<std::vector<int>>(N, repeats);
        double time_deq_4 = measure_random_access<std::deque<int>>(N, repeats);
        double time_list_4 = measure_random_access<std::list<int>>(N, repeats);

        std::cout << std::left << std::setw(15) << test_names[4]
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_vec_4
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_deq_4
                  << std::setw(15) << std::fixed << std::setprecision(3) << time_list_4 << "\n";

        std::cout << "\n";
    }

    return 0;
}
