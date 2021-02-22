#pragma once

#include <cstdint>
#include <string_view>
#include <map>
#include <vector>
#include <string>
#include <optional>

namespace clargs {
    class Arguments {
    public:
        Arguments() = default;

        bool is_set(std::string_view) const;
        const std::vector<std::string>& get_stray_values();

        void clear();
        void parse(std::size_t, char* const[]);

        std::optional<std::string_view> get_value_of(const std::string&);

    private:
        template <typename ...Args>
        void report_error(std::size_t, Args&&...);

        std::map<std::string, std::string> key_values;
        std::vector<std::string> stray_values;
    };

    Arguments get_arguments(std::size_t, char* const[]);
}
