#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <iomanip>

template<typename T>
T calcDeriv1(const T x, const T h)
{
    return (atan(x+h) - atan(x)) / h;
}

template<typename T>
T calcDeriv2(const T x, const T h)
{
    return (atan(x+h) - atan(x-h)) / (2*h);
}

template<typename T>
void writeToFile(const std::string& path, const std::vector<T>& stepSizes,
                 const std::vector<T>& derivs1, const std::vector<T>& derivs2)
{
    size_t N = stepSizes.size();
    assert(derivs1.size() == N);
    assert(derivs2.size() == N);

    std::ofstream outFile (path);

    if (outFile.good()) {
        for (size_t i = 0; i < N; i++) {
            outFile << std::setprecision(8);
            outFile << stepSizes.at(i) << "," << derivs1.at(i) << "," << derivs2.at(i) << std::endl;
        }
    }
    else {
        std::cerr << "File was bad." << std::endl;
        return;
    }
}

template<typename T>
void calculateAndStore(const std::string& path)
{
    std::vector<T> stepSizes;
    for (int scale = 0; scale > -20; scale--) {
        for (T value = 0; value < 10; value++) {
            stepSizes.push_back(value * pow(10, scale));
        }
    }

    const T x = sqrt(2);

    std::vector<T> derivs1;
    std::vector<T> derivs2;

    for (auto h : stepSizes) {
        derivs1.push_back(calcDeriv1(x, h));
        derivs2.push_back(calcDeriv2(x, h));
    }

    writeToFile(path, stepSizes, derivs1, derivs2);
}

int main()
{
    calculateAndStore<float>("float_results.csv");
    calculateAndStore<double>("double_results.csv");
    return 0;
}
