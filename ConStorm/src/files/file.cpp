/*
 Code by Drake Johnson
*/

#include "files/file.hpp"

namespace cons
{
	namespace fs = std::filesystem;

	File::File(fs::path file_path, const openmode open_mode)
		: m_path(std::move(file_path))
		, m_openmode(open_mode)
	{
		open_streams_();
	}

	File::File(const File& other)
		: File(other.m_path, other.m_openmode)
	{}

	File& File::operator=(const File& other)
	{
		if (this != &other)
		{
			m_path = other.m_path;
			m_openmode = other.m_openmode;
			open_streams_();
		}
		return *this;
	}

	File::File(File&& other) noexcept
		: m_path(std::move(other.m_path))
		, m_openmode(other.m_openmode)
		, m_input_stream(std::move(other.m_input_stream))
		, m_output_stream(std::move(other.m_output_stream))
	{}

	File& File::operator=(File&& other) noexcept
	{
		if (this != &other)
		{
			m_path = std::move(other.m_path);
			m_openmode = other.m_openmode;
			m_input_stream = std::move(other.m_input_stream);
			m_output_stream = std::move(other.m_output_stream);
		}
		return *this;
	}

	void File::open_file(fs::path new_path, const openmode open_mode)
	{
		if (open_mode != static_cast<openmode>(-1))
			m_openmode = open_mode;

		close_streams_();

		m_path = std::move(new_path);
		open_streams_();
	}

	void File::read_from(const std::streampos pos)
	{
		if (!m_input_stream.is_open())
			return;
		if (pos > get_file_length())
			return;

		m_input_stream.seekg(pos);
	}

	void File::read_from(const std::streamoff offset, const std::fstream::seekdir rel_pos)
	{
		if (!m_input_stream.is_open())
			return;

		m_input_stream.seekg(offset, rel_pos);
	}

	void File::write_to(const std::streampos pos)
	{
		if (!m_output_stream.is_open())
			return;

		m_output_stream.seekp(pos);
	}

	void File::write_to(const std::streamoff offset, const std::fstream::seekdir rel_pos)
	{
		if (!m_output_stream.is_open())
			return;

		m_output_stream.seekp(offset, rel_pos);
	}

	std::streampos File::get_file_length() const
	{
		#pragma warning(disable:26812)
		auto& in_stream = *const_cast<std::ifstream*>(&m_input_stream);
		const auto cur_pos = std::ifstream::cur;
		in_stream.seekg(0, std::ifstream::end);
		const auto len = in_stream.tellg();
		in_stream.seekg(0, cur_pos);
		return len;
		#pragma warning(default:26812)
	}

	std::istream& File::operator>>(std::istream&(* pf)(std::istream&))
	{
		pf(m_input_stream);
		return m_input_stream;
	}

	std::istream& File::operator>>(std::ios&(* pf)(std::ios&))
	{
		pf(m_input_stream);
		return m_input_stream;
	}

	std::istream& File::operator>>(std::ios_base&(* pf)(std::ios_base&))
	{
		pf(m_input_stream);
		return m_input_stream;
	}

	std::ostream& File::operator<<(std::ostream&(* pf)(std::ostream&))
	{
		pf(m_output_stream);
		return m_output_stream;
	}

	std::ostream& File::operator<<(std::ios&(* pf)(std::ios&))
	{
		pf(m_output_stream);
		return m_output_stream;
	}

	std::ostream& File::operator<<(std::ios_base&(* pf)(std::ios_base&))
	{
		pf(m_output_stream);
		return m_output_stream;
	}

	void File::open_streams_()
	{
		switch (m_openmode)
		{
		case openmode::input:
			m_input_stream.open(m_path);
			break;

		case openmode::output_destroy:
			m_output_stream.open(m_path);
			break;

		case openmode::output_keep:
			m_output_stream.open(m_path, std::fstream::out | std::fstream::app);
			break;

		case openmode::input_and_output:
			m_input_stream.open(m_path);
			m_output_stream.open(m_path, std::fstream::out | std::fstream::app);
			break;
		}
	}

	void File::close_streams_()
	{
		try
		{
			if (m_input_stream.is_open())
				m_input_stream.close();
			if (m_output_stream.is_open())
				m_output_stream.close();
		}
		catch (const std::exception& err)
		{
			print(std::string("STREAM ERROR: ") + err.what());
		}
		catch (...)
		{
			print("STREAM ERROR: Unknown");
		}
	}
} // namespace cons
