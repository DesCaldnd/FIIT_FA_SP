#include "../include/server_logger_builder.h"

#include <not_implemented.h>

#include <filesystem>
#include <utility>

logger_builder& server_logger_builder::add_file_stream(std::string const& stream_file_path, logger::severity severity) & {
	auto opened_stream = _output_streams.find(severity);
	if (opened_stream == _output_streams.end()) {
		opened_stream = _output_streams.emplace(severity, std::make_pair(std::string(), false)).first;
	}

	opened_stream->second.first = stream_file_path;
	return *this;
}

logger_builder& server_logger_builder::add_console_stream(logger::severity severity) & {
	auto opened_stream = _output_streams.find(severity);
	if (opened_stream == _output_streams.end()) {
		opened_stream = _output_streams.emplace(severity, std::make_pair(std::string(), false)).first;
	}

	opened_stream->second.second = true;
	return *this;
}

logger_builder& server_logger_builder::transform_with_configuration(std::string const& configuration_file_path, std::string const& configuration_path) & {
	std::ifstream file(configuration_file_path);
	if (!file.is_open()) throw std::ios_base::failure("Can't open file" + configuration_file_path);

	nlohmann::json data = nlohmann::json::parse(file);
	file.close();

	auto opened_stream = data.find(configuration_path);
	if (opened_stream == data.end() || !opened_stream->is_object()) return *this;

	parse_severity(logger::severity::trace, (*opened_stream)["trace"]);
	parse_severity(logger::severity::debug, (*opened_stream)["debug"]);
	parse_severity(logger::severity::information, (*opened_stream)["information"]);
	parse_severity(logger::severity::warning, (*opened_stream)["warning"]);
	parse_severity(logger::severity::error, (*opened_stream)["error"]);
	parse_severity(logger::severity::critical, (*opened_stream)["critical"]);

	return *this;
}

logger_builder& server_logger_builder::clear() & {
	_output_streams.clear();
	_destination = "http://127.0.0.1:9200";
	return *this;
}

logger* server_logger_builder::build() const {
	return new server_logger(_destination, _output_streams);
}

logger_builder& server_logger_builder::set_destination(const std::string& dest) & {
	_destination = dest;
	return *this;
}

logger_builder& server_logger_builder::set_format(const std::string& format) & {
	return *this;
}

void server_logger_builder::parse_severity(logger::severity sev, nlohmann::json& j) {
	if (j.empty() || !j.is_object()) return;

	auto opened_stream = _output_streams.find(sev);
	auto data_it = j.find("path");
	if (data_it != j.end() && data_it->is_string()) {
		std::string data = *data_it;
		auto console_it = j.find("console");
		bool console = false;
		if (console_it != j.end() && console_it->is_boolean()) {
			console = *console_it;
		}

		if (opened_stream == _output_streams.end()) {
			opened_stream = _output_streams.emplace(sev, std::make_pair(data, console)).first;
		}
	}
}