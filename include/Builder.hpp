// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#pragma once

#include <list>
#include <string>

#include <boost/program_options.hpp>
#include <boost/program_options/parsers.hpp>
#include <iostream>

namespace po = boost::program_options;

struct Parameters {
    static int timeout;
    static bool isInstallAdded;
    static bool isPackAdded;
    static std::string buildConfig;
    static int prepareCommandLine(int argc, char **argv);
};

class Builder {
public:
    static const std::string kDirectoryBuild;
    static const std::string kDirectoryInstall;
    static std::list<std::string> getConfig();
    static std::list<std::string> getBuild();
    static std::list<std::string> getInstall();
    static std::list<std::string> getPack();
};
