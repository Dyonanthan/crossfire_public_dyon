// https://github.com/biesigrr/phoenix-cf

#include "log.h"

Log::Log(char* filename, bool enabled)
{
	// might disable this in releases, they don't have to know everything
	this->logging_enabled_ = enabled;
	this->out_file_stream_.open(filename, std::fstream::out);
}

Log::~Log()
{
	this->Close();
}

void Log::Close()
{
	this->out_file_stream_.close();
}

void Log::Write(const char* message, LogLevel level)
{
	if (!this->logging_enabled_)
		return;

	char buffer[200];
	Log::NowTimeString(buffer);
	this->out_file_stream_ << "- " << buffer;
	this->out_file_stream_ << " " << Log::ToString(level) << ":\t";
	this->out_file_stream_ << message << std::endl;
	this->out_file_stream_.flush();
}

void Log::Writef(const char* format, uint32_t value)
{
	if (!this->logging_enabled_)
		return;

	char buffer[1024];

	sprintf_s(buffer, format, value);

	this->Write(buffer, kInfo);
}

char* Log::ToString(LogLevel level)
{
	static char* const buffer[] = { "ERROR", "WARNING", "INFO", "DEBUG" };
	return buffer[level];
}

LogLevel Log::FromString(const std::string& level)
{
	if (level == "DEBUG")
		return kDebug;
	if (level == "INFO")
		return kInfo;
	if (level == "WARNING")
		return kWarning;
	if (level == "ERROR")
		return kError;
	
	// use info if something unknown was specified
	return kInfo;
}

void Log::NowTimeString(char* out)
{
	char buffer[200];
	if (!GetTimeFormatA(LOCALE_INVARIANT, 0, 0, "HH':'mm':'ss", buffer, 200))
		return;

	static DWORD first = GetTickCount();
	sprintf_s(out, 100, "%s.%03ld", buffer, (int32_t)(GetTickCount() - first) % 1000);
}