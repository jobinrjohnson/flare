//
// Created by jobinrjohnson on 22/08/21.
//

#include <fstream>
#include <iostream>
#include <flare.h>

#include <jsoncpp/json/json.h>

struct TestSpecification {

    int exitCode{};
    std::string scriptPath;

};

typedef struct TestSpecification TestSpecification;


TestSpecification *getTestSpecification(std::string path) {

    auto *ts = new TestSpecification;

    Json::Value testSpec;
    std::ifstream test_file(path + "/config.json", std::ifstream::binary);
    test_file >> testSpec;

    ts->exitCode = atoi(testSpec["exit_code"].asCString());
    ts->scriptPath = path + "/" + testSpec["script"].asString();

    return ts;

}


int main() {

    auto testSpec = getTestSpecification("../../test/hello-world");

    printf("%s", testSpec->scriptPath.c_str());

    std::ifstream file(testSpec->scriptPath, std::ifstream::in);

    if (!file.is_open()) {
        std::cerr << "Some error occurred while opening the file.";
        return -1;
    }

    // Execute
    flare::Flare f;
    f.executeStream(file, "hello-world/script.js");

    assert(f.getExitCode() == testSpec->exitCode);

    delete (testSpec);


    return 0;

}