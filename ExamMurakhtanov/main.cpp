#include <iostream>
#include <map>
#include <cassert>
#include <optional>

class MetricRegister {
private:
    std::map<int, std::pair<int, int>> metrics;
    int nextMetricNumber;

    MetricRegister() : nextMetricNumber(1) {}

public:
    static MetricRegister& getInstance() {
        static MetricRegister instance;
        return instance;
    }

    bool add_metric(int resp_t, int wait_t) {
        metrics[nextMetricNumber] = std::make_pair(resp_t, wait_t);
        nextMetricNumber++;
        return true;
    }

    void show_metrics() {
        for (const auto& metric : metrics) {
            std::cout << "Metric Number: " << metric.first
                      << ", Response Time: " << metric.second.first
                      << ", Wait Time: " << metric.second.second << std::endl;
        }
    }

    std::optional<int> count_metric(int timestamp) {
        for (const auto& metric : metrics) {
            if (metric.first == timestamp) {
                int response_time = metric.second.first;
                int wait_time = metric.second.second;
                return response_time + wait_time;
            }
        }
        return std::nullopt;
    }
};

void test_count_metric() {
    MetricRegister& metricRegister = MetricRegister::getInstance();

    metricRegister.add_metric(100, 200);
    metricRegister.add_metric(150, 250);
    metricRegister.add_metric(120, 180);
    metricRegister.add_metric(300, 400);
    metricRegister.add_metric(200, 300);
    metricRegister.add_metric(180, 220);
    metricRegister.add_metric(250, 350);
    metricRegister.add_metric(150, 150);
    metricRegister.add_metric(170, 270);
    metricRegister.add_metric(280, 380);

    assert(metricRegister.count_metric(1).value() == 300);
    assert(metricRegister.count_metric(2).value() == 400);
    assert(metricRegister.count_metric(3).value() == 300);
    assert(metricRegister.count_metric(4).value() == 700);
    assert(metricRegister.count_metric(5).value() == 500);
    assert(metricRegister.count_metric(6).value() == 400);
    assert(metricRegister.count_metric(7).value() == 600);
    assert(metricRegister.count_metric(8).value() == 300);
    assert(metricRegister.count_metric(9).value() == 440);
    assert(metricRegister.count_metric(10).value() == 660);

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    MetricRegister& metricRegister = MetricRegister::getInstance();

    metricRegister.add_metric(100, 200);
    metricRegister.add_metric(150, 250);
    metricRegister.add_metric(120, 180);
    metricRegister.add_metric(300, 400);
    metricRegister.add_metric(200, 300);
    metricRegister.add_metric(180, 220);
    metricRegister.add_metric(250, 350);
    metricRegister.add_metric(150, 150);
    metricRegister.add_metric(170, 270);
    metricRegister.add_metric(280, 380);

    std::cout << "All Metrics:" << std::endl;
    metricRegister.show_metrics();

    int metricNumber = 4;
    std::optional<int> count = metricRegister.count_metric(metricNumber);
    if (count.has_value()) {
        std::cout << "Count Metric for metric number " << metricNumber << ": " << count.value() << std::endl;
    } else {
        std::cout << "No metric found for metric number " << metricNumber << std::endl;
    }

    test_count_metric();

    return 0;
}
