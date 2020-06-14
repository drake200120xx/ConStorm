/*
 Code by Drake Johnson

 Contains the FuncMenu_base class
*/
#ifndef CONS_MENUS_FUNCTION_DEFAULT_HEADER__
#define CONS_MENUS_FUNCTION_DEFAULT_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif // _MSC_VER
#include "../interface.hpp"
#include <functional>  // function
#include <tuple>       // tuple
#include <utility>     // move, forward
namespace cons
{
	template<class RetTy, bool /* RetTy void? */, class... ParamTys>

	class FuncMenu_base : public MenuInterface
	{
	public:
		FuncMenu_base(
			RetTy default_value,
			ParamTys... args)
			: func_set_(false)
			, m_args(std::make_tuple(std::forward<ParamTys>(args)...))
			, m_value(default_value)
			, m_goto_next(nullptr)
		{}


		FuncMenu_base(const FuncMenu_base& other)
			: func_set_(other.func_set_)
			, m_function(other.m_function)
			, m_args(other.m_args)
			, m_value(other.m_value)
			, m_goto_next(other.m_goto_next)
		{}

		FuncMenu_base& operator=(const FuncMenu_base& other)
		{
			if (this == &other)
				return *this;
			func_set_ = other.func_set_;
			m_function = other.m_function;
			m_args = other.m_args;
			m_value = other.m_value;
			m_goto_next = other.m_goto_next;
			return *this;
		}

		FuncMenu_base(FuncMenu_base&& other) noexcept
			: func_set_(other.func_set_)
			, m_function(std::move(other.m_function))
			, m_args(std::move(other.m_args))
			, m_value(other.m_value)
			, m_goto_next(other.m_goto_next)
		{}

		[[nodiscard]] FuncMenu_base& operator=(FuncMenu_base&& other) noexcept
		{
			if (this == &other)
				return *this;
			func_set_ = other.func_set_;
			m_function = std::move(other.m_function);
			m_args = std::move(other.m_args);
			m_value = other.m_value;
			m_goto_next = other.m_goto_next;
			return *this;
		}

		~FuncMenu_base() = default;

		/**
		 set_function() must be called before calling this method
		*/
		[[nodiscard]] const MenuInterface* run() const override
		{
			if (!func_set_)
				return nullptr;

			m_value = std::apply(m_function, m_args);
			return m_goto_next;
		}

		void set_function(std::function<RetTy(ParamTys...)> function)
		{
			m_function = std::move(function);
			func_set_ = true;
		}

		void set_goto_next(const MenuInterface* const goto_next)
		{
			m_goto_next = goto_next;
		}

		[[nodiscard]] RetTy get_value() const { return m_value; }

	private:
		bool func_set_;
		std::function<RetTy(ParamTys...)> m_function;
		std::tuple<ParamTys...> m_args;
		RetTy m_value;
		const MenuInterface* m_goto_next;

		void display() const override {}
	};
} // namespace cons
#endif // CONS_MENU_FUNCTION_DEFAULT_HEADER__
