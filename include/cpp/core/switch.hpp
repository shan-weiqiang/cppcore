///
// SwitchType - switch any type than can be compared with ==
// Written in 2023 by Shan Weiqiang(schmessi@163.com)
//
//
// To the extent possible under law, the author(s) have dedicated all
// copyright and related and neighboring rights to this software to the
// public domain worldwide. This software is distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication
// along with this software. If not, see
// <http://creativecommons.org/publicdomain/zero/1.0/>.
///

#ifndef CPP_CORE_SWITCHT_HPP
#define CPP_CORE_SWITCHT_HPP

#include <functional>
#include <optional>
#include <type_traits>

namespace cpp
{
namespace core
{

template <typename Fn, typename Out>
concept FnReturnConvertibleToOut = requires(Fn&& func) {
	{
		std::forward<Fn>(func)()
	} -> std::convertible_to<Out>;
};

template <typename Given, typename Out>
concept GivenTypeConvertibleToOut = requires(Given&& given) {
	{
		std::forward<Given>(given)
	} -> std::convertible_to<Out>;
};

template <typename T>
concept NotRef = !std::is_reference_v<T>;
;

template <NotRef In, typename Out>
class SwitchType
{
	using ConstIn = std::add_const_t<In>;

public:
	SwitchType(ConstIn& in)
		: out_{}
		, in_{in}
	{ }
	template <typename Fn>
		requires FnReturnConvertibleToOut<Fn, Out>
	auto Case(ConstIn& in, Fn&& func) && -> SwitchType&&
	{
		if(in == in_.get() && !out_)
		{
			out_.emplace(std::forward<Fn>(func)());
		}
		return std::move(*this);
	}

	template <typename Given>
		requires GivenTypeConvertibleToOut<Given, Out>
	auto Case(ConstIn& in, Given&& given) && -> SwitchType&&
	{
		if(in == in_.get() && !out_)
		{
			out_.emplace(std::forward<Given>(given));
		}
		return std::move(*this);
	}

	template <typename Fn>
		requires FnReturnConvertibleToOut<Fn, Out>
	auto Default(Fn&& func) && -> Out
	{
		return out_ ? std::move(*this->out_) : std::forward<Fn>(func)();
	}

	template <typename Given>
		requires GivenTypeConvertibleToOut<Given, Out>
	auto Default(Given&& given) && -> Out
	{
		return out_ ? std::move(*this->out_) : std::forward<Given>(given);
	}

	auto get() && -> std::optional<Out>
	{
		return out_;
	}

private:
	std::reference_wrapper<ConstIn> in_;
	std::optional<Out> out_;
};

template <typename In>
class SwitchType<In, void>
{
	using ConstIn = std::add_const_t<In>;

public:
	SwitchType(ConstIn& in)
		: in_{in}
	{ }

	template <typename Callable>
		requires FnReturnConvertibleToOut<Callable, void>
	auto Case(ConstIn& in, Callable&& func) && -> SwitchType&&
	{
		if(!matched_ && in == in_.get())
		{
			std::forward<Callable>(func)();
			matched_ = true;
		}
		return std::move(*this);
	}

	template <typename Callable>
		requires FnReturnConvertibleToOut<Callable, void>
	auto Default(Callable&& func) && -> void
	{
		if(!matched_)
		{
			std::forward<Callable>(func)();
			matched_ = true;
		}
	}

private:
	std::reference_wrapper<ConstIn> in_;
	bool matched_{false};
};
template <typename In, typename Out = void>
auto Switch(const In& in) -> SwitchType<In, Out>
{
	return SwitchType<In, Out>{in};
} // namespace core
} // namespace core

} // namespace cpp

#endif
