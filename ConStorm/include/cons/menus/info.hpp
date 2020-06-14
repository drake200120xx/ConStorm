/*
 Code by Drake Johnson

 Contains the InfoMenu class
*/
#ifndef CONS_INFO_MENU_HEADER__
#define CONS_INFO_MENU_HEADER__
#include "interface.hpp"
#include "../output/header.hpp"

namespace cons
{
	/**
	 A type of menu to present information to the user without any interaction

	 @param m_title           The title to display at the top of the menu
	 @param m_desc            A description of the menu that shows under title_
	 @param m_section_headers A container of subheadings. Size must equal m_section_text
	 @param m_section_text    Descriptions that show under the corresponding subheading
	 @param m_pause_msg       The message that prompts the user to press a key to continue
	 @param m_goto_next       A MenuInterface* to the menu to go return from run()
	*/
	class InfoMenu final : public MenuInterface
	{
	private:
		struct SectionPair;
		struct SectionPairRef;

	public:
		using section_container = std::vector<Header>;
		using text_container = std::vector<WordWrap>;

		InfoMenu(Header title = Header(), MenuInterface* goto_next = nullptr);
		InfoMenu(const InfoMenu& other);
		InfoMenu(InfoMenu&& other) noexcept;
		~InfoMenu() = default;

		InfoMenu& operator=(const InfoMenu& other);
		InfoMenu& operator=(InfoMenu&& other) noexcept;

		[[nodiscard]] const MenuInterface* run() const override;

		void set_title(Header title);
		void set_description(WordWrap desc);
		void set_description(std::string text);
		void set_section_headers(section_container headers);
		void set_section_texts(text_container texts);
		void append_section(const Header& header, const WordWrap& text);
		void append_section(const Header& header, const std::string& text);
		void set_pause_msg(std::string msg);
		void set_goto_next(MenuInterface* goto_next);

		[[nodiscard]] Header get_title() const { return m_title; }
		[[nodiscard]] WordWrap get_description() const { return m_desc; }
		[[nodiscard]] section_container	get_section_headers() const;
		[[nodiscard]] text_container get_section_texts() const;
		[[nodiscard]] std::string get_pause_msg() const { return m_pause_msg; }
		[[nodiscard]] MenuInterface* get_goto_next() const { return m_goto_next; }

		/**
		 @returns A reference to the Header object and text at 'index'
		*/
		SectionPairRef operator[](size_t index);

		/**
		 @returns the value of the Header object and text at 'index'
		*/
		SectionPair operator[](size_t index) const;

	private:
		Header m_title;
		WordWrap m_desc;
		section_container m_section_headers;
		text_container m_section_texts;
		std::string m_pause_msg;
		MenuInterface* m_goto_next;

		void display() const override;

		SectionPairRef get_section_ref(size_t index);
		SectionPair get_section(size_t index) const;

		static void copy(InfoMenu& dest, const InfoMenu& src);
		static void move(InfoMenu& dest, InfoMenu&& src) noexcept;
	};
} // namespace cons
#endif // !CONS_INFO_MENU_HEADER__
