// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#include "Process.hpp"
void Process::create(std::unique_ptr<ThreadData> &data) {
    if (Parameters::timeout <= 0) {
        return;
    }
    static const int kTimeDelta = 1;
    while (Parameters::timeout > 0 && (!data || !data->isTerminated)) {
        std::this_thread::sleep_for(std::chrono::seconds{kTimeDelta});
        Parameters::timeout -= kTimeDelta;
    }

    data->isTerminated = true;
    std::cerr << "TIME IS OVER";
        data->currentProcess.terminate();
}


void Process::startProcess(const std::list<std::string> &commandArg,
                           std::unique_ptr<ThreadData> &data) {
    namespace pr = boost::process;

    if (data && data->isTerminated) {
        return;
    }
    std::string out;
    for (const auto &com : commandArg) {
        out += com + " ";
    }
    // Start

    pr::ipstream stream;

    pr::child child{"/usr/local/bin/cmake", pr::args(commandArg),
                    pr::std_out > stream};

    // Update data
    if (!data) {
        data = std::make_unique<ThreadData>
                (ThreadData{false, std::move(child)});
    } else {
        data->currentProcess = std::move(child);
    }
    // Get output
    for (std::string line;
         data->currentProcess.running() && std::getline(stream, line);) {
        std::cout << line << std::endl;
    }

    // Wait until exit
    data->currentProcess.wait();

    auto exitCode = data->currentProcess.exit_code();

    if (exitCode != 0) {
        data->isTerminated = true;
    }
}
