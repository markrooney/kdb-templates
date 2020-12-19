#define KXVER 3
#include <kx/k.h>
#include <markrooney/kdb.hpp>

using namespace kdb;

#include <unordered_map>
#include "doctest/doctest.h"

struct ConfigurationAny {
    type::atom_any timeout;
    type::atom_symbol callback;
};

KDB_REGISTER_TYPE(ConfigurationAny,
    &ConfigurationAny::timeout,
    &ConfigurationAny::callback)

struct Configuration {
    type::atom_int timeout;
    type::atom_symbol callback;
};

KDB_REGISTER_TYPE(Configuration,
    &Configuration::timeout,
    &Configuration::callback)

TEST_CASE("K objects can be decoded into custom objects if the structure matches") {
    khp((S) "", -1);

    SUBCASE("reading in configuration with correct types works") {
        K obj = ktn(0, 2);
        kK(obj)[0] = ki(2000);
        kK(obj)[1] = ks((S) "upd");

        Configuration config;
        CHECK_NOTHROW(convert::to_native(obj, config));

        CHECK_EQ(config.timeout, 2000);
        CHECK_EQ(config.callback, "upd");

        r0(obj);
    }

    SUBCASE("reading in configuration with any types works for numerical values") {
        K obj = ktn(0, 2);
        kK(obj)[0] = kf(2000);
        kK(obj)[1] = ks((S) "upd");

        ConfigurationAny config;
        CHECK_NOTHROW(convert::to_native(obj, config));

        if (type::is_floating(config.timeout)) {
            CHECK_EQ(type::as_float(config.timeout), 2000.0);
        } else {
            FAIL("deserialization failed: type::atom_any is holding the wrong datatype");
        }

        CHECK_EQ(config.callback, "upd");

        r0(obj);
    }
}