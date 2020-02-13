/*
 Code by Drake Johnson

 This header contains a word wrap class which can wrap a string
 by splitting it into lines contained in a vector (1 line / element)
 and can return the vector. This header also contains a cons::println
 template specialization for printing a WordWrap object to the console
 via the cons::print() or cons::prompt() functions.

 Header includes:
   - <string>        : string
   - <unordered_set> : unordered_set
*/
#ifndef CONS_WORD_WRAP__
#define CONS_WORD_WRAP__
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#include "println/vector.hpp"
#include <string>
#include <unordered_set>

namespace cons
{
	/**
	 Wraps a string into lines, each with a maximum length of `m_char_count`.
	 The lines are stored in the vector `m_processed_str` with 1 line / element.

	 @param m_orig_str      Original string to be wrapped
	 @param m_char_count    Max number of chars per line
	 @param m_tab_spaces    Number of spaces '\t' will be converted to
	 @param m_processed_str A vector containing the wrapped version of `m_orig_str`
	*/
	class WordWrap
	{

	public:
		WordWrap(std::string orig_str, unsigned char_count, unsigned tab_spaces = 4);
		WordWrap(const char* orig_str, unsigned char_count, unsigned tab_spaces = 4);
		WordWrap(const WordWrap& other) = default;

		WordWrap& operator=(const WordWrap& other);
		WordWrap& operator=(const std::string& other);

		WordWrap(WordWrap&& other) noexcept;

		WordWrap& operator=(WordWrap&& other) noexcept;
		WordWrap& operator=(std::string&& other) noexcept;

		[[nodiscard]] std::vector<std::string> getVec() const
		{
			return m_processed_str;
		}

		[[nodiscard]] std::string getStr() const;

		[[nodiscard]] unsigned getCharCount() const { return m_char_count; }
		[[nodiscard]] unsigned getTabSpaces() const { return m_tab_spaces; }
		
	private:
		std::string m_orig_str;
		unsigned m_char_count, m_tab_spaces;
		std::vector<std::string> m_processed_str;

		void Wrap();
	};

	template<>
	/**
	 Template specialization for the cons::println class. This allows for printing a
	 cons::WordWrap object via the cons::print() or cons::prompt() functions.

	 This functor simply calls the std::vector specialization for the cons::println
	 class

	 @param lines The WordWrap object to print to the console
	*/
	class println<WordWrap>
	{
	public:
		println(const WordWrap& lines);
	};
} // namespace cons
#endif // CONS_WORD_WRAP__
