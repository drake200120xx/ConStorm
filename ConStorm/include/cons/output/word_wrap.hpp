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
#include "println/deque.hpp"
#include <string>
#include <unordered_set>

namespace cons
{
	/**
	 Wraps a string into lines, each with a maximum length of `line_limit_`.
	 The lines are stored in the deque `wrapped_` with 1 line / element.

	 @param orig_str_      Original string to be wrapped
	 @param char_count_    Max number of chars per line
	 @param tab_spaces_    Number of spaces '\t' will be converted to
	 @param processed_str_ A deque containing the wrapped version of `orig_str_`
	*/
	class WordWrap
	{

	public:
		WordWrap(std::string orig_str, unsigned char_count, unsigned tab_spaces = 4);
		WordWrap(const char* orig_str, unsigned char_count, unsigned tab_spaces = 4);
		WordWrap(const WordWrap& other) = default;
		WordWrap(WordWrap&& other) noexcept;
		~WordWrap() = default;

		WordWrap& operator=(const WordWrap& other);
		WordWrap& operator=(const std::string& other);

		WordWrap& operator=(WordWrap&& other) noexcept;
		WordWrap& operator=(std::string&& other) noexcept;

		[[nodiscard]] std::deque<std::string> get_deque() const;
		[[nodiscard]] std::string get_str() const;
		[[nodiscard]] unsigned get_char_count() const { return line_limit_; }
		[[nodiscard]] unsigned get_tab_spaces() const { return tab_spaces_; }
		
	private:
		std::string orig_str_;
		unsigned line_limit_, tab_spaces_;
		std::deque<std::string> wrapped_;

		void wrap();
	};

	template<>
	/**
	 Template specialization for the cons::println class. This allows for printing a
	 cons::WordWrap object via the cons::print() or cons::prompt() functions.

	 This functor simply calls the std::deque specialization for the cons::println
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
