/*
 Code by Drake Johnson
*/
#include "output/word_wrap.hpp"

namespace cons
{
	WordWrap::WordWrap(std::string orig_str, unsigned char_count, unsigned tab_spaces)
		: m_orig_str(std::move(orig_str)), m_char_count(char_count)
		, m_tab_spaces(tab_spaces)
	{
		Wrap();
	}

	WordWrap::WordWrap(const char* orig_str, unsigned char_count, unsigned tab_spaces)
		: WordWrap(std::string(orig_str), char_count, tab_spaces)
	{}

	WordWrap& WordWrap::operator=(const WordWrap& other)
	{
		if (this != &other)
		{
			m_orig_str = other.m_orig_str;
			m_char_count = other.m_char_count;
			m_tab_spaces = other.m_tab_spaces;
			m_processed_str = other.m_processed_str;
		}
		return *this;
	}

	WordWrap& WordWrap::operator=(const std::string& other)
	{
		m_orig_str = other;
		Wrap();
		return *this;
	}

	WordWrap::WordWrap(WordWrap&& other) noexcept
		: m_orig_str(std::move(other.m_orig_str))
		, m_char_count(other.m_char_count)
		, m_tab_spaces(other.m_tab_spaces)
		, m_processed_str(std::move(other.m_processed_str))
	{}

	WordWrap& WordWrap::operator=(WordWrap&& other) noexcept
	{
		if (this != &other)
		{
			m_orig_str = std::move(other.m_orig_str);
			m_char_count = other.m_char_count;
			m_tab_spaces = other.m_tab_spaces;
			m_processed_str = std::move(other.m_processed_str);
		}
		return *this;
	}

	WordWrap& WordWrap::operator=(std::string&& other) noexcept
	{
		m_orig_str = std::move(other);
		try
		{
			Wrap();
		}
		catch (const std::exception & ex)
		{
			std::cerr << "ERROR! " << ex.what() << std::endl;
		}
		return *this;
	}

	std::string WordWrap::getStr() const
	{
		std::string final_str;
		for (const auto& str : m_processed_str)
			final_str += str + '\n';

		return final_str + '\n';
	}

	void WordWrap::Wrap()
	{
		if (m_orig_str.size() <= m_char_count)
		{
			m_processed_str.push_back(m_orig_str);
			return;
		}

		std::vector<std::string> all_tokens;
		const std::unordered_set<char> delims{ ' ', '\n', '\t' };
		const std::unordered_set<char> punct{
			'.', ',', '?', '!', ':', ';', '-', '\'', '\"', '/', '\\'
		};
		std::string cur_token;  // String-building var
		for (const char& ch : m_orig_str)
		{
			if (delims.find(ch) != delims.end())
			{ // ch is a delim, so flush to all_tokens and reset cur_token
				if (ch == '\n')
				{ // ch is newline char and gets its own element
					all_tokens.push_back(cur_token);
					all_tokens.emplace_back("\n");
					cur_token.clear();
				}
				else if (ch == '\t')
				{ // ch is tab, so convert to spaces and add to next element
					all_tokens.push_back(cur_token);
					cur_token.clear();

					std::string tab;
					for (unsigned i = 0; i < m_tab_spaces; i++)
					{ // Convert '\t' to spaces
						tab += ' ';
					}
					cur_token += tab;
				}
				else
				{ // ch is regular delim and gets no special treatment
					all_tokens.push_back(cur_token);
					cur_token.clear();
				}
			}
			else
			{ // Char is not delim, so add it to cur_token
				cur_token += ch;
			}
		}
		// Flush last token to all_tokens
		all_tokens.push_back(cur_token);

		// Delete all empty elements (if any)
		auto token_itr = all_tokens.begin();
		unsigned short tmp_token_pos = 0;
		while (token_itr != all_tokens.end())
		{
			if (token_itr->empty())
			{ // Null strings throw std::out_of_range
				all_tokens.erase(token_itr);

				// Erase causes mem realloc, so reassign token
				token_itr = (all_tokens.begin() + tmp_token_pos);
			}
			else
				++token_itr, ++tmp_token_pos;
		}

		// Assemble tokens into lines
		std::string cur_line;
		for (auto token : all_tokens)
		{
			if (token == "\t")
			{ // Convert to spaces
				cur_line += std::string(m_tab_spaces - 1, ' ');
			}

			if (token == "\n")
			{ // Manual line break; Flush to all_lines and reset cur_line
				m_processed_str.push_back(cur_line);
				cur_line.clear();
			}
			else if (token.size() + 1 > m_char_count)
			{ // Token size (plus a space) larger than char_count; Flush to all_lines with hyphen
				if (!cur_line.empty())
					m_processed_str.push_back(cur_line);
				std::string tmp_token;
				unsigned pos = 0;

				// Insert '-' upon reaching char_count - 2
				while (pos < token.size())
				{
					for (unsigned i = 0; pos < token.size() && i < m_char_count - 2; i++, pos++)
						tmp_token += token.at(pos);

					if (pos < token.size())
					{ // Not last char in token, so add hyphen
						tmp_token += '-';
					}
					m_processed_str.push_back(tmp_token);
					tmp_token.clear();
				}

				cur_line.clear();
			}
			else if (cur_line.size() + (token.size() + 1) > m_char_count)
			{ // Token (plus a space) too large for current line; Flush to all_lines and reset cur_line
				m_processed_str.push_back(cur_line);
				cur_line.clear();

				// Add token to cur_line
				cur_line += token + ' ';
			}
			else
			{ // Token not too large for current line; add it
				cur_line += token + ' ';
			}
		}

		if (!cur_line.empty())
		{ // Flush last line to all_lines
			m_processed_str.push_back(cur_line);
		}
	}

	println<WordWrap, void>::println(const WordWrap& lines)
	{
		auto vec_strs = lines.getVec();
		println<decltype(vec_strs)> p(vec_strs);
	}


} // namespace cons
