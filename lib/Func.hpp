#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <memory>
#include <vector>
#include <map>

#include <stdio.h>

class AbstractFunction {
  public:
    virtual std::string ToString() const = 0;
    virtual double GetDeriative(double x) = 0;
    virtual double operator()(double x) = 0;
    virtual std::shared_ptr<AbstractFunction> Copy() = 0;
};

class FunctionComposition: public AbstractFunction {
  public:  
    FunctionComposition(AbstractFunction &lfunc, AbstractFunction &rfunc, std::string type);
    std::string ToString() const;
    double GetDeriative(double x);
    double operator()(double x);
    std::shared_ptr<AbstractFunction> Copy();
  private:
    std::shared_ptr<AbstractFunction> lfunc, rfunc;
    std::string type;
};

class Identical: public AbstractFunction {
  public:
    Identical();
    explicit Identical(double param);
    explicit Identical(std::vector<double> param);
    std::string ToString() const;
    double GetDeriative(double x);
    double operator()(double x);
    std::shared_ptr<AbstractFunction> Copy();
  protected:
    double param;
};

class Constant: public AbstractFunction {
  public:
    Constant();
    explicit Constant(double param);
    explicit Constant(std::vector<double> param);
    std::string ToString() const;
    double GetDeriative(double x);
    double operator()(double x);
    std::shared_ptr<AbstractFunction> Copy();
  protected:
    double param;
};

class Power: public AbstractFunction {
  public:
    Power();
    explicit Power(double param);
    explicit Power(std::vector<double> param);
    std::string ToString() const;
    double GetDeriative(double x);
    double operator()(double x);
    std::shared_ptr<AbstractFunction> Copy();
  protected:
    double param;
};

class Exponential: public AbstractFunction {
  public:
    Exponential();
    explicit Exponential(double param);
    explicit Exponential(std::vector<double> param);
    std::string ToString() const;
    double GetDeriative(double x);
    double operator()(double x);
    std::shared_ptr<AbstractFunction> Copy();
  protected:
    double param;
};

class Polynomial: public AbstractFunction {
  public:
    Polynomial();
    explicit Polynomial(double param);
    explicit Polynomial(std::vector<double> param);
    std::string ToString() const;
    double GetDeriative(double x);
    double operator()(double x);
    std::shared_ptr<AbstractFunction> Copy();
  protected:
    std::map<unsigned int, double> ParamsDict;
};

template <typename TFunction>
FunctionComposition operator+(AbstractFunction &lfunc, TFunction &rfunc) {
    if constexpr (std::is_base_of_v<AbstractFunction, TFunction>) {
        return FunctionComposition(lfunc, rfunc, "+");
    } else {
        throw std::logic_error("type mismatch");
    }
}

template <typename TFunction>
FunctionComposition operator-(AbstractFunction &lfunc, TFunction &rfunc) {
    if constexpr (std::is_base_of_v<AbstractFunction, TFunction>) {
        return FunctionComposition(lfunc, rfunc, "-");
    } else {
        throw std::logic_error("type mismatch");
    }
}

template <typename TFunction>
FunctionComposition operator*(AbstractFunction &lfunc, TFunction &rfunc) {
    if constexpr (std::is_base_of_v<AbstractFunction, TFunction>) {
        return FunctionComposition(lfunc, rfunc, "*");
    } else {
        throw std::logic_error("type mismatch");
    }
}

template <typename TFunction>
FunctionComposition operator/(AbstractFunction &lfunc, TFunction &rfunc) {
    if constexpr (std::is_base_of_v<AbstractFunction, TFunction>) {
        return FunctionComposition(lfunc, rfunc, "/");
    } else {
        throw std::logic_error("type mismatch");
    }
}

template <typename TFunction>
double FindRoot(TFunction &f, double x, int it, double lambda) {
    for (; it > 0; --it) {
        x = x - lambda * f(x) * (f).GetDeriative(x);
    }
    return x;
}
#endif 