#pragma once

#include "clargs.h"
#include <iostream>

namespace clargs {
    bool Arguments::is_set(std::string_view flag_name) const {
        auto temp = key_values.find(flag_name.data());

        if (temp == key_values.end()) {
            return false;
        }

        return temp->second == "true";
    }

    const std::vector<std::string>& Arguments::get_stray_values() {
        return stray_values;
    }

    void Arguments::clear() {
        stray_values.clear();
        key_values.clear();
    }

    void Arguments::parse(
        std::size_t number_of_arguments, 
        char* const arguments[]
    ) {
        clear();
        std::size_t source_position = 0;

        auto read_name = [&](auto& iter, const auto& end) {
            std::string name;
            if ((iter != end) && std::isalpha(*iter)) {
                do {
                    name += *iter++;
                } while (
                    (iter != end) && (std::isalnum(*iter) || *iter == '_')
                );
            }
            return name;
        };

        while (source_position < number_of_arguments) {
            std::string item = arguments[source_position];
            auto item_iter = std::begin(item);

            if (*item_iter++ != '-') {
                stray_values.push_back(std::move(item));
                source_position++;
                continue;
            }

            if (item_iter == std::end(item)) {
                report_error(source_position, "expected '-' or alphabet");
            }

            std::string name;
            std::string value;

            const auto there_is_a_name = [&] {
                return name.size() > 0;
            };

            const auto report_error_if_there_is_no_name = [&](auto... args) {
                if (!there_is_a_name()) {
                    report_error(std::forward<decltype(args)>(args)...);
                }
            };

            auto read_required_name = [&](auto...args) {
                name = read_name(item_iter, std::end(item));
                report_error_if_there_is_no_name(
                    std::forward<decltype(args)>(args)...
                );
            };

            auto read_key_value_pair = [&] {
                item_iter++;

                read_required_name(
                    source_position, 
                    "expected a name after '--'"
                );

                value = "true";
                source_position++;
            };

            auto read_flag = [&] {
                read_required_name(
                    source_position, 
                    "expected a name after '-'"
                );

                if ((source_position + 1) >= number_of_arguments) {
                    report_error(
                        source_position, 
                        "expected a value after -",
                        name
                    );
                }

                value = std::string(arguments[++source_position]);
                source_position++;
            };

            if (*item_iter == '-') {
                read_key_value_pair();
            }
            else {
                read_flag();
            }

            key_values[std::move(name)] = std::move(value);
        }
    }

    std::optional<std::string_view> Arguments::get_value_of(
        const std::string& name
    ) {
        if (auto temp = key_values.find(name); 
            temp != key_values.end()
        ) {
            return temp->second;
        }
        return std::nullopt;
    }

    template <typename ...Args>
    void Arguments::report_error(std::size_t position, Args&&... args) {
        std::cout << "error: in argument " << (position + 1) << ": ";
        (std::cout << ... << args);
        std::cout << "\n";
        exit(position + 1);
    }
}
