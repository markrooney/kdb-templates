#pragma once

#ifndef _MARKROONEY_DETAIL_EXCEPTIONS_H
#define _MARKROONEY_DETAIL_EXCEPTIONS_H

#include <exception>
#include <stdexcept>
#include <string>

namespace kdb::exception {

    class invalid_conversion : public std::runtime_error {
    public:
        explicit invalid_conversion(const std::string& msg) : std::runtime_error(msg) { }
    };
}

#endif