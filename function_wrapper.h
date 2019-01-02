#ifndef FUNCTION_DECORATOR_H_
#define FUNCTION_DECORATOR_H_

#include <stdarg.h>
#include <chrono>
//参数个数
//返回值类型
template<class FuntionType>
struct ArgcAt;

template<class ResultType, class... ArgsType>
struct ArgcAt<ResultType(ArgsType...)>
{
    using type = ResultType;
    static const uint32_t argc = sizeof...(ArgsType);
};

//获取各个参数的类型
template<int index, class FuntionType>
struct ArgsTypeAt;

template<class ResultType, class FirstArgType, class... ArgsType>
struct ArgsTypeAt<1, ResultType(FirstArgType, ArgsType...)>
{
    using type = FirstArgType;
};

template<int index, class ResultType, class FirstArgType, class... ArgsType>
struct ArgsTypeAt<index, ResultType(FirstArgType, ArgsType...)>
{
    using type = typename ArgsTypeAt<index - 1, ResultType(ArgsType...)>::type;
};

//通用的函数包装器
template<class Function, class... Args>
inline auto FuncWrapper(Function && func, Args && ... args) -> decltype(func(std::forward<Args>(args)...))
{
    //typedef decltype(f(std::forward<Args>(args)...)) ReturnType;
    return func(std::forward<Args>(args)...);
    //your code; you can use the above typedef.
}

#endif // FUNCTION_DECORATOR_H_