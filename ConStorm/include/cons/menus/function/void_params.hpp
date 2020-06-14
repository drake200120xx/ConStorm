/*
 Code by Drake Johnson

 Contains cons::FuncMenu_base specialization for void return
 with parameters
*/
#ifndef CONS_MENUS_FUNCTION_VOID_PARAMS_HEADER__
#define CONS_MENUS_FUNCTION_VOID_PARAMS_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif // _MSC_VER
#include "default.hpp"
namespace cons
{
	template<class... ParamTys>
	/**
	 Specialization of FuncMenu_base for 'void' return type
	*/
	class FuncMenu_base<void, true, ParamTys...> 
		: public MenuInterface
	{
	public:
		explicit FuncMenu_base(ParamTys... args)
			: func_set_(false)
			, m_args(std::make_tuple(std::forward<ParamTys>(args)...))
			, m_goto_next(nullptr)
		{}


		FuncMenu_base(const FuncMenu_base& other)
			: func_set_(other.func_set_)
			, m_function(other.m_function)
			, m_args(other.m_args)
			, m_goto_next(other.m_goto_next)
		{}

		[[nodiscard]] FuncMenu_base& operator=(const FuncMenu_base& other)
		{
			if (this == &other)
				return *this;
			func_set_ = other.func_set_;
			m_function = other.m_function;
			m_args = other.m_args;
			m_goto_next = other.m_goto_next;
			return *this;
		}

		FuncMenu_base(FuncMenu_base&& other) noexcept
			: func_set_(other.func_set_)
			, m_function(std::move(other.m_function))
			, m_args(std::move(other.m_args))
			, m_goto_next(other.m_goto_next)
		{}

		[[nodiscard]] FuncMenu_base& operator=(FuncMenu_base&& other) noexcept
		{
			if (this == &other)
				return *this;
			func_set_ = other.func_set_;
			m_function = std::move(other.m_function);
			m_args = std::move(other.m_args);
			m_goto_next = other.m_goto_next;
			return *this;
		}

		~FuncMenu_base() = default;

		/**
		 set_function() must be called before this method
		*/
		[[nodiscard]] const MenuInterface* run() const override
		{
			if (!func_set_)
				return nullptr;

			std::apply(m_function, m_args);
			return m_goto_next;
		}

		void set_function(std::function<void(ParamTys...)> function)
		{
			m_function = std::move(function);
			func_set_ = true;
		}

		void set_goto_next(const MenuInterface* const goto_next)
		{
			m_goto_next = goto_next;
		}

	private:
		bool func_set_;
		std::function<void(ParamTys...)> m_function;
		std::tuple<ParamTys...> m_args;
		const MenuInterface* m_goto_next;

		void display() const override {}
	};
} // namespace cons
#endif // !CONS_MENUS_FUNCTION_VOID_PARAMS_HEADER__