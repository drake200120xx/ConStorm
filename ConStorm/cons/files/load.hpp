/*
 Code by Drake Johnson

 Defines the 'FilesLoad' class, which is a wrapper for multi-threaded
 file loading.
*/
#ifndef CONS_FILE_LOAD_HEADER__
#define CONS_FILE_LOAD_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif // _MSC_VER
#include "file.hpp"
#include <future>

namespace cons
{
	/**
	 Loads a vector of files async. File objects are stored in a vector of
	 shared pointers and can be retrieved using 'get_files()'.
	*/
	class FilesLoad
	{
	public:
		using file_vec = std::vector<File>;

		explicit FilesLoad(
			const std::vector<std::filesystem::path>& file_paths,
			File::openmode open_mode = File::openmode::input_and_output);

		explicit FilesLoad(
			const std::vector<std::string>& file_paths,
			File::openmode open_mode = File::openmode::input_and_output);

		~FilesLoad() = default;

		[[nodiscard]] file_vec get_files() const { return m_files; }

	private:
		file_vec m_files;
		std::vector<std::future<void>> m_futures;
	};
} // namespace cons
#endif // !CONS_FILE_LOAD_HEADER__

