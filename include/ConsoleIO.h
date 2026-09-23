#pragma once

#include <cmath>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

namespace sgs {

inline void stripBom(std::string& line) {
    if (line.size() >= 3 &&
        static_cast<unsigned char>(line[0]) == 0xEF &&
        static_cast<unsigned char>(line[1]) == 0xBB &&
        static_cast<unsigned char>(line[2]) == 0xBF) {
        line.erase(0, 3);
    }
}

inline void stripEol(std::string& line) {
    while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) {
        line.pop_back();
    }
}

inline bool readLine(std::istream& in, std::string& line) {
    if (!std::getline(in, line)) {
        return false;
    }
    stripBom(line);
    stripEol(line);
    return true;
}

inline bool askInt(std::istream& in, std::ostream& out, const std::string& prompt,
                   int lo, int hi, int& value) {
    for (;;) {
        out << prompt;
        out.flush();
        std::string line;
        if (!readLine(in, line)) {
            return false;
        }
        std::istringstream iss(line);
        int v = 0;
        std::string rest;
        if ((iss >> v) && !(iss >> rest) && v >= lo && v <= hi) {
            value = v;
            return true;
        }
        out << "  输入无效，请输入 " << lo << " ~ " << hi << " 之间的整数。\n";
    }
}

inline bool askDouble(std::istream& in, std::ostream& out, const std::string& prompt,
                      double& value) {
    for (;;) {
        out << prompt;
        out.flush();
        std::string line;
        if (!readLine(in, line)) {
            return false;
        }
        std::istringstream iss(line);
        double v = 0.0;
        std::string rest;
        if ((iss >> v) && !(iss >> rest) && std::isfinite(v)) {
            value = v;
            return true;
        }
        out << "  输入无效，请输入一个数字（例如 12 或 12.5）。\n";
    }
}

}
