// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#ifndef INCLUDE_PROCESS_HPP_
#define INCLUDE_PROCESS_HPP_

#include <boost/process.hpp>
#include <chrono>
#include <list>
#include <memory>
#include <sstream>
#include <string>

#include "Builder.hpp"
#include <iostream>
#include <random>

struct ThreadData {
    ThreadData() = delete;

    bool isTerminated = false;
    boost::process::child currentProcess;
};

class Process {
public:
    static void create(std::unique_ptr<ThreadData> &data);
    static void startProcess(const std::list<std::string> &commandArg,
                             std::unique_ptr<ThreadData> &data);
};

#endif  // INCLUDE_PROCESS_HPP_
