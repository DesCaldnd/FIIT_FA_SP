#include "../include/server_logger_builder.h"

#include <not_implemented.h>

#include <filesystem>
#include <fstream>
#include <utility>

using namespace nlohmann;

logger_builder& server_logger_builder::add_file_stream(std::string const& stream_file_path, logger::severity severity) & {
	auto opened_stream = _output_streams.find(severity);
	if (opened_stream == _output_streams.end()){
		opened_stream = _output_streams.emplace(severity, std::make_pair(std::string(), false)).first;
	}

	opened_stream->second.first = stream_file_path;
	return *this;
}

logger_builder& server_logger_builder::add_console_stream(logger::severity severity) & {
	auto opened_stream = _output_streams.find(severity);
	if (opened_stream == _output_streams.end()){
		opened_stream = _output_streams.emplace(severity, std::make_pair(std::string(), false)).first;
	}

	opened_stream->second.second = true;
	return *this;
}

logger_builder& server_logger_builder::transform_with_configuration(std::string const& configuration_file_path, std::string const& configuration_path) & {
	json js;
	std::ifstream stream(configuration_file_path);
	if (stream.is_open()) {
		json::parser_callback_t callback = [&configuration_path](int depth, json::parse_event_t event, json& parsed) {
			if (event == json::parse_event_t::key && depth == 1 && parsed != json(configuration_path)) return false;
			return true;
		};

		js = json::parse(stream, callback);
		stream.close();
		if (!js.contains(configuration_path)) return *this;

		js = js[configuration_path];

		if (js.contains("format")) {
			set_format(js["format"]);
		}

		if (js.contains("streams")) {
			for (auto& stream_item : js["streams"]) {
				std::string type = stream_item["type"];
				if (type == "file" && stream_item.contains("path") && stream_item.contains("severities")) {
					std::string path = stream_item["path"];
					for (auto& sev : stream_item["severities"]) {
						add_file_stream(path, string_to_severity(sev.get<std::string>()));
					}
				} else if (type == "console" && stream_item.contains("severities")) {
					for (auto& sev : stream_item["severities"]) {
						add_console_stream(string_to_severity(sev.get<std::string>()));
					}
				}
			}
		}
	}

	return *this;
}

logger_builder& server_logger_builder::clear() & {
	_output_streams.clear();
	_destination = "http://127.0.0.1:9200";
	return *this;
}

logger* server_logger_builder::build() const {
	return new server_logger(_destination, _output_streams, _format);
}

logger_builder& server_logger_builder::set_destination(const std::string& dest) & {
	_destination = dest;
	return *this;
}

logger_builder& server_logger_builder::set_format(const std::string& format) & {
	return *this;
}
