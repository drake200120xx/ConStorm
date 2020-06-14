/*
 Code by Drake Johnson
*/

#include "../../include/cons/menus/info.hpp"
#include "../../include/cons/output.hpp"
#include "../../include/cons/input.hpp"

namespace cons
{
	struct InfoMenu::SectionPair
	{
		Header& header;
		WordWrap& text;
	};

	struct InfoMenu::SectionPairRef
	{
		Header header;
		WordWrap text;
	};

	InfoMenu::InfoMenu(Header title, MenuInterface* goto_next)
		: m_title(std::move(title))
		, m_desc("", 80, 4)
		, m_section_headers({})
		, m_section_texts({})
		, m_pause_msg("Press any key to continue...")
		, m_goto_next(goto_next)
	{}

	InfoMenu::InfoMenu(const InfoMenu& other)
		: m_desc("", 80, 4)
		, m_goto_next(nullptr)
	{
		copy(*this, other);
	}

	InfoMenu::InfoMenu(InfoMenu&& other) noexcept
		: m_desc("", 80, 4)
		, m_goto_next(nullptr)
	{
		move(*this, std::move(other));
	}

	InfoMenu& InfoMenu::operator=(const InfoMenu& other)
	{
		if (this != &other)
			copy(*this, other);
		return *this;
	}

	InfoMenu& InfoMenu::operator=(InfoMenu&& other) noexcept
	{
		if (this != &other)
			move(*this, std::move(other));
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

	void InfoMenu::set_title(Header title)
	{
		m_title = std::move(title);
	}

	void InfoMenu::set_description(WordWrap desc)
	{
		m_desc = std::move(desc);
	}

	void InfoMenu::set_description(std::string text)
	{
		set_description(WordWrap(
			std::move(text), m_desc.get_char_count(), m_desc.get_tab_spaces()
		));
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

	void InfoMenu::append_section(const Header& header, const std::string& text)
	{
		append_section(
			header, WordWrap(
				text, m_desc.get_char_count(), m_desc.get_tab_spaces()
			)
		);
	}

	void InfoMenu::set_pause_msg(std::string msg)
	{
		m_pause_msg = std::move(msg);
	}

	void InfoMenu::set_goto_next(MenuInterface* const goto_next)
	{
		m_goto_next = goto_next;
	}

	InfoMenu::section_container InfoMenu::get_section_headers() const
	{
		return m_section_headers;
	}

	InfoMenu::text_container InfoMenu::get_section_texts() const
	{
		return m_section_texts;
	}

	InfoMenu::SectionPairRef InfoMenu::operator[](const size_t index)
	{
		return get_section_ref(index);
	}

	InfoMenu::SectionPair InfoMenu::operator[](const size_t index) const
	{
		return get_section(index);
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
		auto sect_heads = m_section_headers.at(index);
		auto sect_texts = m_section_texts.at(index);
		return SectionPair{ sect_heads, sect_texts };
	}

	void InfoMenu::copy(InfoMenu& dest, const InfoMenu& src)
	{
		dest.m_title = src.m_title;
		dest.m_desc = src.m_desc;
		dest.m_section_headers = src.m_section_headers;
		dest.m_section_texts = src.m_section_texts;
		dest.m_pause_msg = src.m_pause_msg;
		dest.m_goto_next = src.m_goto_next;
	}

	void InfoMenu::move(InfoMenu& dest, InfoMenu&& src) noexcept
	{
		dest.m_title = std::move(src.m_title);
		dest.m_desc = std::move(src.m_desc);
		dest.m_section_headers = std::move(src.m_section_headers);
		dest.m_section_texts = std::move(src.m_section_texts);
		dest.m_pause_msg = std::move(src.m_pause_msg);
		dest.m_goto_next = src.m_goto_next;
	}
} // namespace cons
