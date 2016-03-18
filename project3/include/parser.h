#ifndef PARSER_H
#define PARSER_H

#include "yaml-cpp/yaml.h"
#include <armadillo>

namespace YAML {
    template<>
    struct convert<arma::vec> {
        static Node encode(const arma::vec& rhs);
        static bool decode(const Node& node, arma::vec& rhs);
    };
}

#endif /* end of include guard: PARSER_H */
