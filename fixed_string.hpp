#ifndef __FIXED_STRING_HPP__
#define __FIXED_STRING_HPP__

#include <cctype>

namespace fstr
{
template<typename CharT, std::size_t N>
struct fixed_string
{
    using value_type = CharT;

    template<std::size_t N2>
    constexpr fixed_string(const CharT (&str)[N2])
    {
        static_assert(N + 1 == N2);
        for (std::size_t i = 0; i < N; ++i)
        {
            data_[i] = str[i];
        }
    }

    template<std::size_t N2>
    constexpr auto operator+(const CharT (&rhs)[N2])
    {
        fixed_string<CharT, N + N2 - 1> result;

        for (std::size_t i = 0; i < N; ++i)
        {
            result.data_[i] = data_[i];
        }
        for (std::size_t i = 0; i < N2 - 1; ++i)
        {
            result.data_[i + N] = rhs[i];
        }

        return result;
    }

    template<std::size_t N2>
    constexpr auto operator+(const fixed_string<CharT, N2> &rhs)
    {
        fixed_string<CharT, N + N2> result;

        for (std::size_t i = 0; i < N; ++i)
        {
            result.data_[i] = data_[i];
        }
        for (std::size_t i = 0; i < N2; ++i)
        {
            result.data_[i + N] = rhs[i];
        }

        return result;
    }

    constexpr CharT &operator[](std::size_t i)
    {
        return data_[i];
    }

    constexpr CharT operator[](std::size_t i) const
    {
        return data_[i];
    }

    constexpr std::size_t size() const
    {
        return N;
    }

    constexpr const CharT *data() const
    {
        return data_;
    }

    constexpr const CharT *c_str() const
    {
        return data_;
    }

  // make it
  public:
    CharT data_[N + 1] {};
};

template<typename CharT, std::size_t N1, std::size_t N2>
constexpr auto operator+(const CharT (&lhs)[N1], const fixed_string<CharT, N2> &rhs)
{
    fixed_string<CharT, N1 + N2 - 1> result;

    for (std::size_t i = 0; i < N1 - 1; ++i)
    {
        result.data_[i] = data_[i];
    }
    for (std::size_t i = 0; i < N2; ++i)
    {
        result.data_[i + N1 - 1] = rhs[i];
    }

    return result;
}

template<typename CharT, std::size_t N>
fixed_string(const CharT (&str)[N]) -> fixed_string<CharT, N - 1>;
}; // namespace fstr

#endif
