/*
 Code by Drake Johnson

 Defines the 'File' class
*/
#ifndef CONS_FILE_FILE_HEADER__
#define CONS_FILE_FILE_HEADER__
#ifdef _MSC_VER
#   pragma once
#endif // _MSC_VER
#include "../output/print.hpp"
#include <filesystem>
#include <fstream>

namespace cons
{
	/**
	 Wraps std::ifstream and std::ofstream into a single object, which allows
	 for greater flexibility with file IO. This class has operator overloads
	 for '<<' and '>>' operators; these overloads act as wrappers and simply
	 call the overloaded methods from the <fstream> header.
	*/
	class File
	{
	public:
		enum class openmode
		{
			input,  // std::ifstream defaults
			output_destroy,  // std::ofstream defaults
			output_keep,  // std::ofstream, but does not truncate
			input_and_output  // input and output; does not truncate
		};

		File(
			std::filesystem::path file_path, 
			openmode open_mode = openmode::input_and_output
		);


		File(const File& other);
		File& operator=(const File& other);

		File(File&& other) noexcept;
		File& operator=(File&& other) noexcept;

		~File() noexcept { close_streams_(); }

		/**
		 Closes current IO streams, then opens a new file

		 @param new_path Path to new file to open
		 @param open_mode Method of opening file (defaults to the current value of m_openmode)
		*/
		void open_file(
			std::filesystem::path new_path, 
			openmode open_mode = static_cast<openmode>(-1)
		);

		/**
		 Changes the position to start reading the file from
		*/
		void read_from(std::streampos pos);
		void read_from(std::streamoff offset, std::fstream::seekdir rel_pos);

		/**
		 Changes the position to start writing the file to
		*/
		void write_to(std::streampos pos);
		void write_to(std::streamoff offset, std::fstream::seekdir rel_pos);

		/**
		 Deletes this file and closes the streams
		*/
		void delete_file();

		[[nodiscard]] std::filesystem::path get_path() const { return m_path; }
		[[nodiscard]] openmode get_openmode() const { return m_openmode; }
		[[nodiscard]] std::ifstream& get_ifstream() { return m_input_stream; }
		[[nodiscard]] std::ofstream& get_ofstream() { return m_output_stream; }
		[[nodiscard]] std::streampos get_file_length() const;

		std::istream& operator>>(bool& val)               { return common_extract(val); }
		std::istream& operator>>(short& val)              { return common_extract(val); }
		std::istream& operator>>(unsigned short& val)     { return common_extract(val); }
		std::istream& operator>>(int& val)                { return common_extract(val); }
		std::istream& operator>>(unsigned& val)           { return common_extract(val); }
		std::istream& operator>>(long& val)               { return common_extract(val); }
		std::istream& operator>>(unsigned long& val)      { return common_extract(val); }
		std::istream& operator>>(long long& val)          { return common_extract(val); }
		std::istream& operator>>(unsigned long long& val) { return common_extract(val); }
		std::istream& operator>>(float& val)              { return common_extract(val); }
		std::istream& operator>>(double& val)             { return common_extract(val); }
		std::istream& operator>>(long double& val)        { return common_extract(val); }
		std::istream& operator>>(void*& val)              { return common_extract(val); }
		std::istream& operator>>(std::string& val)        { return common_extract(val); }
		std::istream& operator>>(std::streambuf* val)     { return common_extract(val); }
		std::istream& operator>>(std::istream& (*pf)(std::istream&));
		std::istream& operator>>(std::ios& (*pf)(std::ios&));
		std::istream& operator>>(std::ios_base& (*pf)(std::ios_base&));

		std::ostream& operator<<(bool& val)               { return common_insert(val); }
		std::ostream& operator<<(short& val)              { return common_insert(val); }
		std::ostream& operator<<(unsigned short& val)     { return common_insert(val); }
		std::ostream& operator<<(int& val)                { return common_insert(val); }
		std::ostream& operator<<(unsigned& val)           { return common_insert(val); }
		std::ostream& operator<<(long& val)               { return common_insert(val); }
		std::ostream& operator<<(unsigned long& val)      { return common_insert(val); }
		std::ostream& operator<<(long long& val)          { return common_insert(val); }
		std::ostream& operator<<(unsigned long long& val) { return common_insert(val); }
		std::ostream& operator<<(float& val)              { return common_insert(val); }
		std::ostream& operator<<(double& val)             { return common_insert(val); }
		std::ostream& operator<<(long double& val)        { return common_insert(val); }
		std::ostream& operator<<(void*& val)              { return common_insert(val); }
		std::ostream& operator<<(const char* val)         { return common_insert(val); }
		std::ostream& operator<<(std::string& val)        { return common_insert(val); }
		std::ostream& operator<<(std::streambuf* val)     { return common_insert(val); }
		std::ostream& operator<<(std::ostream& (*pf)(std::ostream&));
		std::ostream& operator<<(std::ios& (*pf)(std::ios&));
		std::ostream& operator<<(std::ios_base& (*pf)(std::ios_base&));

	private:
		std::filesystem::path m_path;
		openmode m_openmode;
		std::ifstream m_input_stream;
		std::ofstream m_output_stream;

		void open_streams_();
		void close_streams_();

		template<class ExtTy>
		std::istream& common_extract(ExtTy& ext_obj)
		{
			if (m_input_stream.is_open())
				m_input_stream >> ext_obj;
			return m_input_stream;
		}

		template<class InsTy>
		std::ostream& common_insert(InsTy& ins_obj)
		{
			if (m_output_stream.is_open())
				m_output_stream << ins_obj;
			return m_output_stream;
		}

	public:
		/**
		 Deletes a file after checking if the file exists. Will NOT delete 
		 directories.

		 @param path The path of file to delete
		 @returns 'true' for success; 'false' otherwise
		*/
		static bool delete_file(const std::filesystem::path& path);
		/**
		 Deletes a file by calling the above overload

		 @param file The file to delete
		 @returns 'true' for success; 'false' otherwise
		*/
		static bool delete_file(const File& file);
	};

	using fopenmode = File::openmode;
} // namespace cons
#endif // !CONS_FILE_FILE_HEADER__
