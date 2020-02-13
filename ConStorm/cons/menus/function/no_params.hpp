/*
 Code by Drake Johnson

 Contains the specialization for FuncMenu_base with no
 parameters
*/
#ifndef	CONS_MENUS_FUNCTION_NO_PARAMS_HEADER__
#define	CONS_MENUS_FUNCTION_NO_PARAMS_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif // _MSC_VER
#include "default.hpp"

namespace cons
{
	template<class RetTy>
	/**
	 Specialization of FuncMenu_base for no parameters
	*/
	class FuncMenu_base<RetTy, false> : public MenuInterface
	{
	public:
		explicit FuncMenu_base(RetTy default_value)
			: func_set_(false)
			, m_value(default_value)
			, m_goto_next(nullptr)
		{}

		FuncMenu_base(const FuncMenu_base& other)
			: func_set_(other.func_set_)
			, m_function(other.m_function)
			, m_value(other.m_value)
			, m_goto_next(other.m_goto_next)
		{}

		[[nodiscard]] FuncMenu_base& operator=(const FuncMenu_base& other)
		{
			if (this == &other)
				return *this;
			func_set_ = other.func_set_;
			m_function = other.m_function;
			m_value = other.m_value;
			m_goto_next = other.m_goto_next;
			return *this;
		}

		FuncMenu_base(FuncMenu_base&& other) noexcept
			: func_set_(other.func_set_)
			, m_function(std::move(other.m_function))
			, m_value(other.m_value)
			, m_goto_next(other.m_goto_next)
		{}

		[[nodiscard]] FuncMenu_base& operator=(FuncMenu_base&& other) noexcept
		{
			if (this == &other)
				return *this;
			func_set_ = other.func_set_;
			m_function = std::move(other.m_function);
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

			m_value = m_function();
			return m_goto_next;
		}

		void set_function(std::function<RetTy()> function)
		{
			m_function = std::move(function);
			func_set_ = true;
		}

		[[nodiscard]] RetTy get_value() const { return m_value; }
		[[nodiscard]] MenuInterface* get_goto_next() const { return m_goto_next; }

	private:
		bool func_set_;
		std::function<RetTy()> m_function;
		RetTy m_value;
		MenuInterface* m_goto_next;

		void display() const override {}
	};
} // namespace cons
#endif // !CONS_MENUS_FUNCTION_NO_PARAMS_HEADER__