/*
 Code by Drake Johnson
*/

#include "files/load.hpp"
namespace fs = std::filesystem;

static std::mutex s_files_mutex;
static void load_file(
	cons::FilesLoad::file_vec* output_vec, 
	const fs::path path, 
	const cons::File::openmode om)
{
	std::lock_guard<std::mutex> lock(s_files_mutex);
	output_vec->emplace_back(path, om);
}

namespace cons
{
	FilesLoad::FilesLoad(
		const std::vector<fs::path>& file_paths, 
		File::openmode open_mode)
	{
		m_files.reserve(file_paths.size());
		m_futures.reserve(file_paths.size());

		for (const auto& file : file_paths)
			m_futures.push_back(
				std::async(
					std::launch::async,
					load_file, &m_files, file, open_mode)
			);
	}

	FilesLoad::FilesLoad(
		const std::vector<std::string>& file_paths, 
		File::openmode open_mode)
	{
		m_files.reserve(file_paths.size());
		m_futures.reserve(file_paths.size());
		
		for (const auto& file_str : file_paths)
			m_futures.push_back(
				std::async(
					std::launch::async,
					load_file, &m_files, file_str, open_mode)
			);
	}
} // namespace cons
