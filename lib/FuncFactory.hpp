#ifndef FUNCTION_FACTORY_H
#define FUNCTION_FACTORY_H

#include <map>

#include "Func.hpp"
#include "Func.cpp"

class FunctionFactory {
  public:
    FunctionFactory() {
        RegisterAll();
    };

    class ICreator {
      public:
        virtual ~ICreator() {};
        virtual std::shared_ptr<AbstractFunction> Create() const = 0;
        virtual std::shared_ptr<AbstractFunction> Create(double param) const = 0;
        virtual std::shared_ptr<AbstractFunction> Create(std::vector<double> params) const = 0;
    };

    template <class TFunction>
    class FunctionCreator: public ICreator {
      public:
        std::shared_ptr<AbstractFunction> Create() const override {
            return std::make_shared<TFunction>(TFunction());
        }

        std::shared_ptr<AbstractFunction> Create(double param) const override {
            return std::make_shared<TFunction>(TFunction(param));
        }

        std::shared_ptr<AbstractFunction> Create(std::vector<double> params) const override {
            return std::make_shared<TFunction>(TFunction(params));
        }
    };

    std::vector<std::string> GetAvailableObjects() const {
        std::vector<std::string> res;
        for (auto & [key, val]: RegisteredCreators) {
            res.push_back(key);
        }
        return res;
    }

    std::shared_ptr<AbstractFunction> Create(const std::string& type) {
        return RegisteredCreators[type] -> Create();
    }

    std::shared_ptr<AbstractFunction> Create(const std::string& type, double param) {
        return RegisteredCreators[type] -> Create(param);
    }
       
    std::shared_ptr<AbstractFunction> Create(const std::string& type, std::vector<double> params) {
        return RegisteredCreators[type] -> Create(params);
    }
  private:
    using TCreatorPtr = std::shared_ptr<ICreator>;
    using TRegisteredCreators = std::map<std::string, TCreatorPtr>;
    TRegisteredCreators RegisteredCreators;

    void RegisterAll() {
        RegisteredCreators["ident"] = std::make_shared<FunctionCreator<Identical>>();
        RegisteredCreators["const"] = std::make_shared<FunctionCreator<Constant>>();
        RegisteredCreators["power"] = std::make_shared<FunctionCreator<Power>>();
        RegisteredCreators["exp"] = std::make_shared<FunctionCreator<Exponential>>();
        RegisteredCreators["polynomial"] = std::make_shared<FunctionCreator<Polynomial>>();
    }
};

#endif 