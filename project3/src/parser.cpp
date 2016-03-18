#include "parser.h"

namespace YAML {
    Node convert<arma::vec>::encode(const arma::vec& rhs)
    {
        Node node;
        for (const auto item : rhs) {
            node.push_back(item);
        }
        return node;
    }

    bool convert<arma::vec>::decode(const Node& node, arma::vec& rhs)
    {
        if(!node.IsSequence()) return false;

        rhs.set_size(node.size());
        for (arma::uword i = 0; i < node.size(); i++) {
            rhs(i) = node[i].as<double>();
        }
        return true;
    }
}
