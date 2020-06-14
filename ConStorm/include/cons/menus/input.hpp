/*
 Code by Drake Johnson

 Contains the InputMenu class
*/
#ifndef CONS_MENU_INPUT_HEADER__
#define CONS_MENU_INPUT_HEADER__
#include "interface.hpp"
#include "../output.hpp"
#include "../input.hpp"

namespace cons
{
	template<class Ty>
	struct enable_if_copy_constructible
	{
		using type = std::enable_if_t<std::is_constructible_v<Ty>>;
	};
	template<class Ty>
	using enable_if_cc_t = typename enable_if_copy_constructible<Ty>::type;

	template<class, class = void>
	class InputMenu;

	template<class ReturnTy>
	/**
	 Displays a title, description, and prompt. Collects stores input into a 
	 variable of type 'ReturnTy' that can be retrieved through 'get_value()'

	 @param title_      The title of the menu; displayed at the top of the menu
	 @param desc_       A section of text right under title_
	 @param prompt_msg_ The message to prompt the user for input
	 @param validation_ The validation function to validate user input. Must take
					    in one parameter of type 'ReturnTy' and return a bool if
						the input is valid or not
	 @param value_      Validated user input from the most recent invocation of
						'run()'
	*/
	class InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>> 
		: public MenuInterface
	{
	public:
		using value_type = ReturnTy;

		InputMenu(Header title = Header(""));
		InputMenu(std::function<bool(value_type)> validation_function);
		InputMenu(Header title, 
			std::function<bool(value_type)> validation_function);
		InputMenu(const InputMenu& other);
		InputMenu(InputMenu&& other) noexcept;
		virtual ~InputMenu() = default;

		InputMenu& operator=(const InputMenu& other);
		InputMenu& operator=(InputMenu&& other) noexcept;


		[[nodiscard]] const MenuInterface* run() const override;

		void set_title(Header title);
		void set_description(WordWrap desc);
		void set_description(std::string text);
		void set_description(std::string text, unsigned char_count, 
			unsigned space_for_tab = 4U);
		void set_prompt_msg(std::string prompt_msg);
		void set_validation(std::function<bool(value_type)> validation_function);
		void set_goto_next(MenuInterface* menu_interface);

		[[nodiscard]] Header get_title() const;
		[[nodiscard]] WordWrap get_desc() const;
		[[nodiscard]] std::string get_prompt_msg() const;
		[[nodiscard]] std::function<bool(value_type)> get_validation() const;
		[[nodiscard]] value_type get_value() const;
		[[nodiscard]] MenuInterface* get_goto_next() const;

	protected:
		Header title_;
		WordWrap desc_;
		std::string prompt_msg_;
		std::function<bool(value_type)> validation_;
		mutable value_type value_;
		MenuInterface* goto_next_;

		void display() const override;

	private:
		static void copy(InputMenu& dest, const InputMenu& src);
		static void move(InputMenu& dest, InputMenu&& src) noexcept;
	};

	template <class ReturnTy>
	InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::InputMenu(Header title)
		: title_(std::move(title))
		, desc_("", 80U, 4U)
		, validation_([](value_type dummy) -> bool { return true; })
		, goto_next_(nullptr)
	{}

	template <class ReturnTy>
	InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::InputMenu(
		std::function<bool(value_type)> validation_function)
		: desc_("", 80U, 4U)
		, validation_(std::move(validation_function))
		, goto_next_(nullptr)
	{}

	template <class ReturnTy>
	InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::InputMenu(Header title,
		std::function<bool(value_type)> validation_function)
		: title_(std::move(title))
		, desc_("", 80U, 4U)
		, validation_(std::move(validation_function))
		, value_()
		, goto_next_(nullptr)
	{}

	template <class ReturnTy>
	InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::InputMenu(
		const InputMenu& other)
		: desc_("", 4U, 80U)
	{
		copy(*this, other);
	}

	template <class ReturnTy>
	InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::InputMenu(
		InputMenu&& other) noexcept
		: desc_("", 4U, 80U)
	{
		move(*this, std::move(other));
	}

	template <class ReturnTy>
	InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>& InputMenu<ReturnTy, 
		enable_if_cc_t<ReturnTy>>::operator=(const InputMenu& other)
	{
		if (this != &other)
			copy(*this, other);

		return *this;
	}

	template <class ReturnTy>
	InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>& InputMenu<ReturnTy, 
		enable_if_cc_t<ReturnTy>>::operator=(InputMenu&& other) noexcept
	{
		if (this != &other)
			move(*this, std::move(other));

		return *this;
	}

	template <class ReturnTy>
	const MenuInterface* InputMenu<ReturnTy, enable_if_cc_t<
		ReturnTy>>::run() const
	{
		display();

		value_ = input<value_type>(validation_);
		return goto_next_;
	}

	template <class ReturnTy>
	void InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::set_title(
		Header title)
	{
		title_ = std::move(title);
	}

	template <class ReturnTy>
	void InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::set_description(
		WordWrap desc)
	{
		desc_ = std::move(desc);
	}

	template <class ReturnTy>
	void InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::set_description(
		std::string text)
	{
		set_description(std::move(text), desc_.get_char_count(), 
			desc_.get_tab_spaces());
	}

	template <class ReturnTy>
	void InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::set_description(
		std::string text, const unsigned char_count, 
		const unsigned space_for_tab)
	{
		desc_ = WordWrap(std::move(text), char_count, space_for_tab);
	}

	template <class ReturnTy>
	void InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::set_prompt_msg(
		std::string prompt_msg)
	{
		prompt_msg_ = std::move(prompt_msg);
	}

	template <class ReturnTy>
	void InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::set_validation(
		std::function<bool(value_type)> validation_function)
	{
		validation_ = std::move(validation_function);
	}

	template <class ReturnTy>
	void InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::set_goto_next(
		MenuInterface* const menu_interface)
	{
		goto_next_ = menu_interface;
	}

	template <class ReturnTy>
	Header InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::get_title() const
	{
		return title_;
	}

	template <class ReturnTy>
	WordWrap InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::get_desc() const
	{
		return desc_;
	}

	template <class ReturnTy>
	std::string InputMenu<ReturnTy, enable_if_cc_t<
		ReturnTy>>::get_prompt_msg() const
	{
		return prompt_msg_;
	}

	template <class ReturnTy>
	std::function<bool(ReturnTy)> 
		InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::get_validation() const
	{
		return validation_;
	}

	template <class ReturnTy>
	ReturnTy InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::get_value() const
	{
		return value_;
	}

	template <class ReturnTy>
	MenuInterface* InputMenu<ReturnTy, enable_if_cc_t<
		ReturnTy>>::get_goto_next() const
	{
		return goto_next_;
	}

	template <class ReturnTy>
	void InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::display() const
	{
		cls();
		print(
			title_,
			desc_,
			""
		);
		if (prompt_msg_.empty())
			prompt();
		else
			prompt(prompt_msg_);
	}

	template <class ReturnTy>
	void InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::copy(InputMenu& dest,
		const InputMenu& src)
	{
		dest.title_ = src.title_;
		dest.desc_ = src.desc_;
		dest.prompt_msg_ = src.prompt_msg_;
		dest.validation_ = src.validation_;
		dest.value_ = src.value_;
		dest.goto_next_ = src.goto_next_;
	}

	template <class ReturnTy>
	void InputMenu<ReturnTy, enable_if_cc_t<ReturnTy>>::move(InputMenu& dest,
		InputMenu&& src) noexcept
	{
		dest.title_ = std::move(src.title_);
		dest.desc_ = std::move(src.desc_);
		dest.prompt_msg_ = std::move(src.prompt_msg_);
		dest.validation_ = std::move(src.validation_);
		dest.value_ = src.value_;
		dest.goto_next_ = src.goto_next_;
	}
} // namespace cons
#endif // !CONS_MENU_INPUT_HEADER__
