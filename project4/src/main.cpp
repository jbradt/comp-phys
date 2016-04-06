#include <iostream>
#include <armadillo>
#include "Integration.h"
#include "Cluster.h"
// #include "parser.h"
// #include "yaml-cpp/yaml.h"
#include <string>
#include <vector>


int main(const int argc, const char** argv)
{
    Cluster cl (20, 10, 1, 10);
    cl.print();
    return 0;
}
