/*
 Code by Drake Johnson
*/

#include "menus/info.hpp"
#include "output.hpp"
#include "input.hpp"

namespace cons
{
	InfoMenu::InfoMenu()
		: InfoMenu("")
	{}

	InfoMenu::InfoMenu(Header title, MenuInterface* goto_next)
		: m_title(std::move(title))
		, m_desc("", 80, 4)
		, m_section_headers({})
		, m_section_texts({})
		, m_pause_msg("Press any key to continue...")
		, m_goto_next(goto_next)
	{}

	InfoMenu::InfoMenu(const InfoMenu& other)
		: m_title(other.m_title)
		, m_desc(other.m_desc)
		, m_section_headers(other.m_section_headers)
		, m_section_texts(other.m_section_texts)
		, m_pause_msg(other.m_pause_msg)
		, m_goto_next(other.m_goto_next)
	{}

	InfoMenu& InfoMenu::operator=(const InfoMenu& other)
	{
		if (this != &other)
		{
			m_title = other.m_title;
			m_desc = other.m_desc;
			m_section_headers = other.m_section_headers;
			m_section_texts = other.m_section_texts;
			m_pause_msg = other.m_pause_msg;
			m_goto_next = other.m_goto_next;
		}

		return *this;
	}

	InfoMenu::InfoMenu(InfoMenu&& other) noexcept
		: m_title(std::move(other.m_title))
		, m_desc(std::move(m_desc))
		, m_section_headers(std::move(m_section_headers))
		, m_section_texts(std::move(other.m_section_texts))
		, m_pause_msg(std::move(other.m_pause_msg))
		, m_goto_next(other.m_goto_next)
	{}

	InfoMenu& InfoMenu::operator=(InfoMenu&& other) noexcept
	{
		if (this != &other)
		{
			m_title = std::move(other.m_title);
			m_desc = std::move(other.m_desc);
			m_section_headers = std::move(other.m_section_headers);
			m_section_texts = std::move(other.m_section_texts);
			m_pause_msg = std::move(other.m_pause_msg);
			m_goto_next = other.m_goto_next;
		}

		return *this;
	}

	const MenuInterface* InfoMenu::run() const
	{
		display();

		if (m_pause_msg.empty())
			pause();
		else
			pause(m_pause_msg);

		return m_goto_next;
	}

	void InfoMenu::set_description(const std::string& text)
	{
		m_desc = WordWrap(text, m_desc.getCharCount(), m_desc.getTabSpaces());
	}

	void InfoMenu::set_description(
		const std::string& text, 
		const unsigned char_count, 
		const unsigned spaces_for_tab)
	{
		m_desc = WordWrap(text, char_count, spaces_for_tab);
	}

	void InfoMenu::set_section_headers(section_container headers)
	{
		m_section_headers = std::move(headers);
	}


	void InfoMenu::set_section_texts(text_container texts)
	{
		m_section_texts = std::move(texts);
	}

	void InfoMenu::append_section(const Header& header, const WordWrap& text)
	{
		m_section_headers.push_back(header);
		m_section_texts.push_back(text);
	}

	void InfoMenu::append_section(
		const Header& header, 
		const std::string& text, 
		unsigned char_count, 
		unsigned spaces_for_tab)
	{
		m_section_headers.push_back(header);
		m_section_texts.emplace_back(text, char_count, spaces_for_tab);
	}

	void InfoMenu::append_section(const Header& header, const std::string& text)
	{
		append_section(
			header, text,
			m_desc.getCharCount(),
			m_desc.getTabSpaces()
		);
	}

	InfoMenu::section_container InfoMenu::get_section_headers() const
	{
		return m_section_headers;
	}

	InfoMenu::text_container InfoMenu::get_section_texts() const
	{
		return m_section_texts;
	}

	void InfoMenu::display() const
	{
		cls();
		print(
			m_title,
			m_desc,
			"", ""
		);
		for (size_t i = 0; i < m_section_texts.size(); ++i)
			print(
				m_section_headers.at(i),
				m_section_texts.at(i),
				""
			);
		print("");
	}

	InfoMenu::SectionPairRef InfoMenu::get_section_ref(const size_t index)
	{
		return {
			m_section_headers.at(index),
			m_section_texts.at(index)
		};
	}

	InfoMenu::SectionPair InfoMenu::get_section(const size_t index) const
	{
		return {
			m_section_headers.at(index),
			m_section_texts.at(index)
		};
	}
} // namespace cons
