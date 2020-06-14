/*
 Code by Drake Johnson
*/
#include "../../include/cons/output/word_wrap.hpp"

namespace cons
{
	WordWrap::WordWrap(std::string orig_str, const unsigned char_count, 
		const unsigned tab_spaces)
		: orig_str_(std::move(orig_str)), line_limit_(char_count)
		, tab_spaces_(tab_spaces)
	{
		wrap();
	}

	WordWrap::WordWrap(const char* orig_str, const unsigned char_count, 
		const unsigned tab_spaces)
		: WordWrap(std::string(orig_str), char_count, tab_spaces)
	{}

	WordWrap& WordWrap::operator=(const WordWrap& other)
	{
		if (this != &other)
		{
			orig_str_ = other.orig_str_;
			line_limit_ = other.line_limit_;
			tab_spaces_ = other.tab_spaces_;
			wrapped_ = other.wrapped_;
		}
		return *this;
	}

	WordWrap& WordWrap::operator=(const std::string& other)
	{
		orig_str_ = other;
		wrap();
		return *this;
	}

	WordWrap::WordWrap(WordWrap&& other) noexcept
		: orig_str_(std::move(other.orig_str_))
		, line_limit_(other.line_limit_)
		, tab_spaces_(other.tab_spaces_)
		, wrapped_(std::move(other.wrapped_))
	{}

	WordWrap& WordWrap::operator=(WordWrap&& other) noexcept
	{
		if (this != &other)
		{
			orig_str_ = std::move(other.orig_str_);
			line_limit_ = other.line_limit_;
			tab_spaces_ = other.tab_spaces_;
			wrapped_ = std::move(other.wrapped_);
		}
		return *this;
	}

	WordWrap& WordWrap::operator=(std::string&& other) noexcept
	{
		orig_str_ = std::move(other);
		try
		{
			wrap();
		}
		catch (const std::exception & ex)
		{
			std::cerr << "ERROR! " << ex.what() << std::endl;
		}
		return *this;
	}

	std::deque<std::string> WordWrap::get_deque() const 
	{
		return wrapped_;
	}

	std::string WordWrap::get_str() const
	{
		std::string final_str;
		for (const auto& str : wrapped_)
			final_str += str + '\n';

		return final_str + '\n';
	}

	void WordWrap::wrap()
	{
		if (orig_str_.size() <= line_limit_)
		{
			wrapped_.push_back(orig_str_);
			return;
		}

		static const std::unordered_set<char> delims{ ' ', '\n', '\t' };
		//static const std::unordered_set<char> punct{
		//	'.', ',', '?', '!', ':', ';', '-', '\'', '\"', '/', '\\'
		//};

		std::string cur_token;
		std::string cur_line;
		wrapped_.clear();

		// Build a token, then try to add it to the current line. If the current
		// line can't fit the token, flush the current line to all_lines, reset
		// the current line, and then add the current token
		for (const auto& ch : orig_str_)
		{
			if (delims.find(ch) != std::end(delims))
			{ // Character is a delim
				// If the character is a space, see if the weak token can fit
				// on the current line (including the space). If not, move to
				// a new line
				if (ch == ' ')
				{
					if ((cur_line + cur_token + ' ').size() <= line_limit_)
					{ // Size with new token is fine, add to current line
						cur_line += cur_token + ' ';
					}
					else
					{ // Size with new token is too big, flush current line
						wrapped_.push_back(cur_line);
						cur_line.clear();
						cur_line += cur_token + ' ';
					}
				}
				else if (ch == '\n')
				{
					cur_line += cur_token;
					wrapped_.push_back(cur_line);
					cur_line.clear();
				}
				else if (ch == '\t')
				{
					std::string tab(tab_spaces_, ' ');
					if ((cur_line + cur_token + tab).size() <= line_limit_)
					{ // Size with new token is fine, add to current line
						cur_line += cur_token + tab;
					}
					else if ((cur_line + cur_token).size() <= line_limit_)
					{ // Size with new token plus tab is too large, move tab to new line
						cur_line += cur_token;
						wrapped_.push_back(cur_line);
						cur_line.clear();
						cur_line += tab;
					}
					else
					{ // The current token without the tab is too large
						wrapped_.push_back(cur_line);
						cur_line.clear();
						cur_line += cur_token + tab;
					}
				}

				// Always clear current token when delim reached
				cur_token.clear();
			}
			else
			{ // Normal character, so try to add it
				// If the current token (plus a hyphen) here is bigger than the
				// line allowance, that means the current token itself is 
				// bigger than the line allowance and must be broken up and 
				// hyphenated
				if ((cur_token + ch).size() + 1 > line_limit_)
				{ // Flush and reset the current token
					wrapped_.push_back(cur_token + ch + '-');
					cur_token.clear();
				}
				else
					cur_token += ch;
			}
		}

		// Flush final token
		if ((cur_line + cur_token).size() <= line_limit_)
			wrapped_.push_back(cur_line + cur_token);
		else
		{
			wrapped_.push_back(cur_line);
			wrapped_.push_back(cur_token);
		}
	}

	println<WordWrap, void>::println(const WordWrap& lines)
	{
		auto deque = lines.get_deque();
		println<decltype(deque)> p(deque);
	}
} // namespace cons
