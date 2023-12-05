#include <math.h>
#include <stdexcept>

#include "Func.hpp"

FunctionComposition::FunctionComposition(AbstractFunction &lfunc, AbstractFunction &rfunc, std::string type):
    lfunc(lfunc.Copy()), rfunc(rfunc.Copy()), type(type) {}

std::string FunctionComposition::ToString() const {
    if (type == "+") {
        return (*lfunc).ToString() + " + " + (*rfunc).ToString();
    } else if (type == "-") {
        return (*lfunc).ToString() + " - " + (*rfunc).ToString();
    } else if (type == "*") {
        return "(" + (*lfunc).ToString() + ") * (" + (*rfunc).ToString() + ")";
    } else if (type == "/") {
        return "(" + (*lfunc).ToString() + ") / (" + (*rfunc).ToString() + ")";
    } else {
        throw std::logic_error("operator error");
    }
}

double FunctionComposition::GetDeriative(double x) {
    if (type == "+") {
        return lfunc->GetDeriative(x) + rfunc->GetDeriative(x);
    } else if (type == "-") {
        return lfunc->GetDeriative(x) - rfunc->GetDeriative(x);
    } else if (type == "*") {
        return (lfunc->GetDeriative(x) * (*rfunc)(x) + rfunc->GetDeriative(x) * (*lfunc)(x));
    } else if (type == "/") {
        return (lfunc->GetDeriative(x) * (*rfunc)(x) - rfunc->GetDeriative(x) * (*lfunc)(x)) / ((*rfunc)(x) * (*rfunc)(x));
    } else {
        throw std::logic_error("operator error");
    }
}

double FunctionComposition::operator()(double x) {
    if (type == "+") {
        return (*lfunc)(x) + (*rfunc)(x);
    } else if (type == "-") {
        return (*lfunc)(x) - (*rfunc)(x);
    } else if (type == "*") {
        return (*lfunc)(x) * (*rfunc)(x);
    } else if (type == "/") {
        return (*lfunc)(x) / (*rfunc)(x);
    } else {
        throw std::logic_error("operator error");
    }
}

std::shared_ptr<AbstractFunction> FunctionComposition::Copy() {
    return std::make_shared<FunctionComposition>(*lfunc, *rfunc, type);
}

Identical::Identical(): param(0) {}

Identical::Identical(double param): param(param) {}

Identical::Identical(std::vector<double> params): param(params[0]) {}

std::string Identical::ToString() const {
    if (param == 0)
        return "0";
    else if (param == 1)
        return "x";
    else
        return "(" + std::to_string(param) + "*x)";
}

double Identical::GetDeriative(double x) {
    return param;
}

double Identical::operator()(double x) {
    return param * x;
}

std::shared_ptr<AbstractFunction> Identical::Copy() {
    return std::make_shared<Identical>(*this);
}

Constant::Constant(): param(0) {}

Constant::Constant(double param): param(param) {}

Constant::Constant(std::vector<double> params): param(params[0]) {}

std::string Constant::ToString() const {
    return "(" + std::to_string(param) + ")";
}

double Constant::GetDeriative(double x) {
    return 0;
}

double Constant::operator()(double x) {
    return param;
}

std::shared_ptr<AbstractFunction> Constant::Copy() {
    return std::make_shared<Constant>(*this);
}

Power::Power(): param(0) {}

Power::Power(double param): param(param) {}

Power::Power(std::vector<double> params): param(params[0]) {}

std::string Power::ToString() const {
    if (param == 0)
        return "1";
    else if (param < 0)
        return "1/x^(" + std::to_string(param) + ")";
    else
        return "x^(" + std::to_string(param) + ")";
}

double Power::GetDeriative(double x) {
    if (param == 0)
        return 0;
    else
        return param * pow(x, param - 1);
}

double Power::operator()(double x) {
    return pow(x, param);
}

std::shared_ptr<AbstractFunction> Power::Copy() {
    return std::make_shared<Power>(*this);
}

Exponential::Exponential(): param(0) {}

Exponential::Exponential(double param): param(param) {}

Exponential::Exponential(std::vector<double> params): param(params[0]) {}

std::string Exponential::ToString() const {
    if (param == 0)
        return "1";
    else
        return "exp(" + std::to_string(param) + "*x)";
}

double Exponential::GetDeriative(double x) {
    return param * exp(param * x);
}

double Exponential::operator()(double x) {
    return exp(param * x);
}

std::shared_ptr<AbstractFunction> Exponential::Copy() {
    return std::make_shared<Exponential>(*this);
}

Polynomial::Polynomial() {
    ParamsDict[0] = 0;
}

Polynomial::Polynomial(double x) {
    ParamsDict[0] = x;
}

Polynomial::Polynomial(std::vector<double> params) {
    for (int i = 0; i < params.size(); i++) {
        if (params[i] != 0) 
            ParamsDict[i] = params[i];
        else if (i == 0)
            ParamsDict[i] = 0;
    }
}

std::string Polynomial::ToString() const {
    std::string res = "";
    for (auto & [key, val]: ParamsDict) {
        if (key == 0 && val != 0)
            res += std::to_string(val) + " + ";
        else if (val != 0)
            res += "(" + std::to_string(val) + ")*x^(" + std::to_string(key) + ") + ";
    }
    if (res == "")
        return "0";
    return res.substr(0, res.length() - 3);
}

double Polynomial::GetDeriative(double x) {
    double res = 0;
    for (auto &[key, val]: ParamsDict) {
        if (key > 0)
            res += key * val * pow(x, key - 1);
    }
    return res;
}

double Polynomial::operator()(double x) {
    double res = 0;
    for (auto & [key, val]: ParamsDict) {
        res += val * pow(x, key);
    }
    return res;
}

std::shared_ptr<AbstractFunction> Polynomial::Copy() {
    return std::make_shared<Polynomial>(*this);
}