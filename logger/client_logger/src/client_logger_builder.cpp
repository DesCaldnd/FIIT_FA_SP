#include "../include/client_logger_builder.h"

#include <not_implemented.h>

#include <filesystem>
#include <utility>

using namespace nlohmann;

logger_builder& client_logger_builder::add_file_stream(std::string const& stream_file_path, logger::severity severity) & {
	auto opened_stream = _output_streams.find(severity);
	if (opened_stream == _output_streams.end()) {
		auto inserted = _output_streams.emplace(severity, std::make_pair(std::forward_list<client_logger::refcounted_stream>(), false));
		opened_stream = inserted.first;
	}
	opened_stream->second.first.emplace_front(std::filesystem::weakly_canonical(stream_file_path).string());
	return *this;
}

logger_builder& client_logger_builder::add_console_stream(logger::severity severity) & {
	auto opened_stream = _output_streams.find(severity);
	if (opened_stream == _output_streams.end()) {
		auto inserted = _output_streams.emplace(severity, std::make_pair(std::forward_list<client_logger::refcounted_stream>(), true));
		opened_stream = inserted.first;
	}
	opened_stream->second.second = true;
	return *this;
}

logger_builder& client_logger_builder::transform_with_configuration(std::string const& configuration_file_path, std::string const& configuration_path) & {
	std::ifstream file(configuration_file_path);
	if (!file.is_open()) throw std::ios_base::failure("Can't open file " + configuration_file_path);

	json data = json::parse(file);
	file.close();

	auto opened_stream = data.find(configuration_path);
	if (opened_stream == data.end() || !opened_stream->is_object()) return *this;

	parse_severity(logger::severity::information, (*opened_stream)["information"]);
	parse_severity(logger::severity::critical, (*opened_stream)["critical"]);
	parse_severity(logger::severity::warning, (*opened_stream)["warning"]);
	parse_severity(logger::severity::trace, (*opened_stream)["trace"]);
	parse_severity(logger::severity::debug, (*opened_stream)["debug"]);
	parse_severity(logger::severity::error, (*opened_stream)["error"]);

	auto format = opened_stream->find("format");
	if (format != opened_stream->end() && format->is_string()) {
		_format = format.value();
	}
	return *this;
}

logger_builder& client_logger_builder::clear() & {
	_output_streams.clear();
	_format = "%m";
	return *this;
}

logger* client_logger_builder::build() const {
	return new client_logger(_output_streams, _format);
}

logger_builder& client_logger_builder::set_format(const std::string& format) & {
	_format = format;
	return *this;
}

void client_logger_builder::parse_severity(logger::severity sev, nlohmann::json& j) {
	if (j.empty() || !j.is_object()) return;

	auto opened_stream = _output_streams.find(sev);

	auto data_paths = j.find("paths");
	if (data_paths != j.end() && data_paths->is_array()) {
		json data = *data_paths;
		for (const json& js: data) {
			if (js.empty() || !js.is_string()) continue;

			const std::string& path = js;
			if (opened_stream == _output_streams.end()) {
				opened_stream = _output_streams.emplace(sev,std::make_pair(std::forward_list<client_logger::refcounted_stream>(),false)).first;
			}
			opened_stream->second.first.emplace_front(std::filesystem::weakly_canonical(path).string());
		}
	}

	auto console = j.find("console");
	if (console != j.end() && console->is_boolean()) {
		if (opened_stream == _output_streams.end()) {
			opened_stream = _output_streams.emplace(sev, std::make_pair(std::forward_list<client_logger::refcounted_stream>(), false)).first;
		}
		opened_stream->second.second = console->get<bool>();
	}
}

logger_builder& client_logger_builder::set_destination(const std::string& format) & {
	return *this;
}
