class A
{
    static auto const class_static_member_variable_auto_const = 0;

    void f()
    {
        auto class_method_local_variable_auto = 1;
    }
};

void f()
{
    auto free_function_local_variable_auto = 2;
}

namespace ns
{
    auto namespace_variable_auto = 4;
    auto &namespace_variable_auto_ref = namespace_variable_auto;
}

namespace
{
    auto anonymous_namespace_variable_auto = 5;
    auto &anonymous_namespace_variable_auto_ref = anonymous_namespace_variable_auto;
}

auto global_variable_auto = 6;
auto const global_variable_auto_const = 7;
auto &global_variable_auto_ref = global_variable_auto;
auto const &global_variable_auto_const_ref = global_variable_auto;
auto &&global_variable_auto_ref_ref = global_variable_auto;
auto const &&global_variable_auto_const_ref_ref = 8;
