#ifndef CMAKE_BASE_PROJECT_GENERIC_MATH_FUNCTION_H
#define CMAKE_BASE_PROJECT_GENERIC_MATH_FUNCTION_H

template<typename TNumeric>
class Math
{
public:
    TNumeric add(TNumeric a, TNumeric b);
};

template<typename TNumeric>
TNumeric Math<TNumeric>::add(TNumeric a, TNumeric b)
{
    return a + b;
}

#endif  // CMAKE_BASE_PROJECT_GENERIC_MATH_FUNCTION_H
