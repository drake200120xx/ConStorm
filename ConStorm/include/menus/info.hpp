/*
 Code by Drake Johnson

 Contains the InfoMenu class
*/
#ifndef CONS_INFO_MENU_HEADER__
#define CONS_INFO_MENU_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif // _MSC_VER
#include "interface.hpp"
#include "output/header.hpp"

namespace cons
{
	/**
	 A type of menu to present information to the user without any interaction

	 @param m_title           The title to display at the top of the menu
	 @param m_desc            A description of the menu that shows under m_title
	 @param m_section_headers A container of subheadings. Size must equal m_section_text
	 @param m_section_text    Descriptions that show under the corresponding subheading
	 @param m_pause_msg       The message that prompts the user to press a key to continue
	 @param m_goto_next       A MenuInterface* to the menu to go return from run()
	*/
	class InfoMenu final : public MenuInterface
	{
	public:
		using section_container = std::vector<Header>;
		using text_container = std::vector<WordWrap>;

		InfoMenu();

		explicit InfoMenu(Header title, MenuInterface* goto_next = nullptr);

		InfoMenu(const InfoMenu& other);
		InfoMenu& operator=(const InfoMenu& other);

		InfoMenu(InfoMenu&& other) noexcept;
		InfoMenu& operator=(InfoMenu&& other) noexcept;

		~InfoMenu() = default;

		[[nodiscard]] const MenuInterface* run() const override;

		void set_title(const Header& title) { m_title = title; }
		void set_description(const WordWrap& desc) { m_desc = desc; }
		void set_description(const std::string& text);
		void set_description(
			const std::string& text,
			unsigned char_count,
			unsigned spaces_for_tab = 4U);
		void set_section_headers(section_container headers);
		void set_section_texts(text_container texts);
		void append_section(const Header& header, const WordWrap& text);
		void append_section(
			const Header& header,
			const std::string& text,
			unsigned char_count,
			unsigned spaces_for_tab = 4U);
		void append_section(
			const Header& header,
			const std::string& text);
		void set_pause_msg(const std::string& msg) { m_pause_msg = msg; }
		void set_goto_next(MenuInterface* const goto_next) 
		{ 
			m_goto_next = goto_next; 
		}

		/**
		 @returns A reference to the Header object and text at 'index'
		*/
		auto operator[](const size_t index)
		{
			return get_section_ref(index);
		}

		/**
		 @returns the value of the Header object and text at 'index'
		*/
		auto operator[](const size_t index) const
		{
			return get_section(index);
		}

		[[nodiscard]] Header get_title() const { return m_title; }
		[[nodiscard]] WordWrap get_description() const { return m_desc; }
		[[nodiscard]] section_container	get_section_headers() const;
		[[nodiscard]] text_container get_section_texts() const;
		[[nodiscard]] std::string get_pause_msg() const { return m_pause_msg; }
		[[nodiscard]] MenuInterface* get_goto_next() const { return m_goto_next; }

	private:
		Header m_title;
		WordWrap m_desc;
		section_container m_section_headers;
		text_container m_section_texts;
		std::string m_pause_msg;
		MenuInterface* m_goto_next;

		void display() const override;

		struct SectionPairRef
		{
			Header& header;
			WordWrap& text;
		};

		struct SectionPair
		{
			Header header;
			WordWrap text;
		};

		SectionPairRef get_section_ref(size_t index);
		SectionPair get_section(size_t index) const;
	};
} // namespace cons
#endif // !CONS_INFO_MENU_HEADER__
