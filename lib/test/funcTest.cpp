#include <gtest/gtest.h>

#include <iostream>

#include "../FuncFactory.hpp"

class Function_test : public testing::Test {};

TEST(Function_test, Creation) {
    FunctionFactory F;

    auto A1 = F.Create("ident", {});
    Identical A2;
    ASSERT_EQ(typeid(*A1), typeid(A2));

    auto B1 = F.Create("power", {1, 2, 3});
    Power B2(5);
    ASSERT_EQ(typeid(*B1), typeid(B2));

    auto C1 = F.Create("exp");
    Exponential C2(10);
    ASSERT_EQ(typeid(*C1), typeid(C2));

    auto D1 = F.Create("const", {1});
    Constant D2;
    ASSERT_EQ(typeid(*D1), typeid(D2));

    auto E1 = F.Create("polynomial");
    Polynomial E2({1, 2, 3});
    ASSERT_EQ(typeid(*E1), typeid(E2));
}

TEST(Function_test, ToString) {
    FunctionFactory F;

    auto A1 = F.Create("ident");
    ASSERT_EQ((*A1).ToString(), "0");
    auto A2 = F.Create("ident", 1);
    ASSERT_EQ((*A2).ToString(), "x");
    auto A3 = F.Create("ident", {1, 2, 3, 4, 5});
    ASSERT_EQ((*A3).ToString(), "x");

    auto B1 = F.Create("const");
    ASSERT_EQ((*B1).ToString(), "(0.000000)");
    auto B2 = F.Create("const", 1);
    ASSERT_EQ((*B2).ToString(), "(1.000000)");
    auto B3 = F.Create("const", {1, 2, 3, 4, 5});
    ASSERT_EQ((*B3).ToString(), "(1.000000)");

    auto C1 = F.Create("power");
    ASSERT_EQ((*C1).ToString(), "1");
    auto C2 = F.Create("power", 1);
    ASSERT_EQ((*C2).ToString(), "x^(1.000000)");
    auto C3 = F.Create("power", {1, 2, 3, 4, 5});
    ASSERT_EQ((*C3).ToString(), "x^(1.000000)");

    auto D1 = F.Create("exp");
    ASSERT_EQ((*D1).ToString(), "1");
    auto D2 = F.Create("exp", 1);
    ASSERT_EQ((*D2).ToString(), "exp(1.000000*x)");
    auto D3 = F.Create("exp", {1, 2, 3, 4, 5});
    ASSERT_EQ((*D3).ToString(), "exp(1.000000*x)");

    auto E1 = F.Create("polynomial");
    ASSERT_EQ((*E1).ToString(), "0");
    auto E2 = F.Create("polynomial", 1);
    ASSERT_EQ((*E2).ToString(), "1.000000");
    auto E3 = F.Create("polynomial", {1, 2, 3, 4, 5});
    ASSERT_EQ((*E3).ToString(), "1.000000 + (2.000000)*x^(1) + (3.000000)*x^(2) + (4.000000)*x^(3) + (5.000000)*x^(4)");
}

TEST(Function_test, Operations) {
    FunctionFactory F;

    auto A1 = F.Create("polynomial", {0, 2, 1});
    auto A2 = F.Create("polynomial", {0, 1, 2});
    auto A3 = *A1 + *A2;
    ASSERT_EQ(A3(1), 6);
    ASSERT_EQ(A3(2), 18);
    ASSERT_EQ((*A1 - *A2)(1), 0);
    ASSERT_EQ((*A1 - *A2)(2), -2);
    ASSERT_EQ((*A1 * *A2)(1), 9);
    ASSERT_EQ((*A1 * *A2)(2), 80);

    auto A4 = F.Create("exp", 0);
    ASSERT_EQ((A3 / *A4)(1), 6);
    ASSERT_EQ((A3 / *A4)(2), 18);

    auto A5 = A3 / *A4;
    auto A6 = F.Create("const", 18);
    ASSERT_EQ((A5 / *A6)(2), 1);
}

TEST(Function_test, Deriations) {
    FunctionFactory F;

    auto f = F.Create("power", 2);
    auto g = F.Create("polynomial", {7, 0, 3, 15});
    auto p = *f + *g;
    ASSERT_EQ(p.GetDeriative(1), 53);
    ASSERT_THROW(*f + "abc", std::logic_error);
    ASSERT_EQ(f->GetDeriative(3), 6);

    auto k = F.Create("exp", 2);
    ASSERT_EQ((*k).GetDeriative(2), ((*k) + (*k))(2));
    ASSERT_EQ((*k).GetDeriative(20), ((*k) + (*k))(20));
}

TEST(Function_test, LogicError) {
    FunctionFactory F;

    auto A1 = F.Create("polynomial", {0, 2});
    ASSERT_THROW(*A1 + "abc", std::logic_error);
    ASSERT_THROW(*A1 + A1, std::logic_error);

    auto A2 = F.Create("ident", 2);
    auto A3 = *A1 + *A2;
    ASSERT_THROW(A3 + "abc", std::logic_error);
    ASSERT_THROW(A3 + A1, std::logic_error);
}