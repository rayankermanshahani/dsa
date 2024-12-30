#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

// namespace for testing framework
namespace test {
// timer for benchmarking
class Timer {
private:
  using Clock = std::chrono::high_resolution_clock;
  using TimePoint = Clock::time_point;
  using Duration = std::chrono::duration<double>;

  TimePoint start_;
  std::string operation_name_;

public:
  // constructor
  explicit Timer(std::string operation = "Operation")
      : start_(Clock::now()), operation_name_(std::move(operation)) {}

  // destructor
  ~Timer() {
    auto end = Clock::now();
    Duration duration = end - start_;
    std::cout << operation_name_ << " took " << duration.count() * 1000 << "ms"
              << std::endl;
  }
};

// rng utilities
class RandomGenerator {
private:
  std::mt19937 gen_;

public:
  // constructor
  RandomGenerator() : gen_(std::random_device{}()) {}

  // generate random integer vector
  std::vector<int> generate_ints(size_t len, int min = 0, int max = 1000) {
    std::vector<int> ints(len);
    std::uniform_int_distribution<> dist(min, max);
    std::generate(ints.begin(), ints.end(), [&]() { return dist(gen_); });
    return ints;
  }

  // generate random string
  std::string generate_string(size_t len) {
    std::string str(len, 0);
    std::uniform_int_distribution<> dist('a', 'z');
    std::generate(str.begin(), str.end(),
                  [&]() { return static_cast<char>(dist(gen_)); });
    return str;
  }

  // generate random string vector
  std::vector<std::string> generate_strings(size_t count, size_t min_len = 1,
                                            size_t max_len = 10) {
    std::vector<std::string> strs(count);
    std::uniform_int_distribution<> len_dist(min_len, max_len);
    std::generate(strs.begin(), strs.end(),
                  [&]() { return generate_string(len_dist(gen_)); });
    return strs;
  }
};

// benchmark suite
class Benchmark {
private:
  std::string name_;
  std::vector<std::pair<std::string, std::function<void()>>> tests_;

public:
  explicit Benchmark(std::string name) : name_(std::move(name)) {}

  // add test case
  template <typename Func>
  void add_test(const std::string& test_name, Func&& test) {
    tests_.emplace_back(test_name, std::forward<Func>(test));
  }

  // run all benchmarks
  void run() {
    std::cout << "\nRunning benchmark suite: " << name_ << "\n"
              << std::string(50, '=') << std::endl;

    for (const auto& [test_name, test] : tests_) {
      std::cout << "\nExecuting tests: " << test_name << std::endl;
      Timer timer(test_name);
      test();
    }
  }
};

// unit testing utilities
class TestSuite {
private:
  std::string name_;
  std::vector<std::pair<std::string, std::function<void()>>> tests_;
  size_t passed_ = 0;
  size_t failed_ = 0;

public:
  explicit TestSuite(std::string name) : name_(std::move(name)) {}

  // add test case
  template <typename Func>
  void add_test(const std::string& test_name, Func&& test) {
    tests_.emplace_back(test_name, std::forward<Func>(test));
  }

  // run all tests
  void run() {
    std::cout << "\nRunning test suite: " << name_ << "\n"
              << std::string(50, '=') << std::endl;

    for (const auto& [test_name, test] : tests_) {
      try {
        std::cout << "Running test: " << test_name << "...";
        test();
        std::cout << "PASSED " << std::endl;
        ++passed_;
      } catch (const std::exception& e) {
        std::cout << "FAILED\nError: " << e.what() << std::endl;
        ++failed_;
      }
    }

    // print summary
    std::cout << "\nTest Summary:\n"
              << "Passed: " << passed_ << "\n"
              << "Failed: " << failed_ << "\n"
              << "Total: " << tests_.size() << std::endl;
  }
};
// assertion utilities
template <typename T>
void assert_equal(const T& expected, const T& actual,
                  const std::string& message = "") {
  if (!(expected == actual)) {
    std::ostringstream oss;
    oss << "Assertion failed: expected " << expected << ", got " << actual;
    if (!message.empty()) {
      oss << " - " << message;
    }
    throw std::runtime_error(oss.str());
  }
}

template <typename T>
void assert_not_equal(const T& unexpected, const T& actual,
                      const std::string& message = "") {
  if (unexpected == actual) {
    std::ostringstream oss;
    oss << "Assertion failed: unexpected " << unexpected;
    if (!message.empty()) {
      oss << " - " << message;
    }
    throw std::runtime_error(oss.str());
  }
}

inline void assert_true(bool condition, const std::string& message = "") {
  if (!condition) {
    std::ostringstream oss;
    oss << "Assertion failed: expected true";
    if (!message.empty()) {
      oss << " - " << message;
    }
    throw std::runtime_error(oss.str());
  }
}

inline void assert_false(bool condition, const std::string& message = "") {
  if (condition) {
    std::ostringstream oss;
    oss << "Assertion failed: expected false";
    if (!message.empty()) {
      oss << " - " << message;
    }
    throw std::runtime_error(oss.str());
  }
}

} // namespace test
