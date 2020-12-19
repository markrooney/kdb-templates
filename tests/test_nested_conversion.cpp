#define KXVER 3
#include "k.h"
#include <markrooney/kdb.hpp>

using namespace kdb;

#include <unordered_map>
#include "doctest/doctest.h"

using L2OrderBook = std::unordered_map<std::string,std::vector<float>>;
using L2OrderBookList = std::unordered_map<std::string, L2OrderBook>;

struct InstrumentInfo {
    type::atom_symbol longSymbol;
    type::atom_long lastUpdated{};
    L2OrderBookList orderBookList;
    type::list_float values;
    type::atom_long timestamp{};
    type::atom_any other;
};
KDB_REGISTER(InstrumentInfo,longSymbol,lastUpdated,orderBookList,values,timestamp,other)

TEST_CASE("roundtrip conversion with complex nested objects should result in equivalent objects") {
    khp((S) "", -1);

    SUBCASE("lists can be nested infinitely") {
        typedef type::list<type::list<type::list_int>> nestedints;

        nestedints value = {{{1, 2, 3, 4, 5},{6,7,8,9,10}},{{11, 12, 13, 14, 15},{16,17,18,19,20}}};
        nestedints result;
        CHECK_NOTHROW(kdb::convert::to_native(kdb::convert::from_native(value), result));

        CHECK_EQ(value.size(), result.size());
        CHECK_EQ(value, result);
    }

    SUBCASE("list of integer atoms are converted between types correctly") {
        L2OrderBook orderBook = {{"BidPrices",{1.7, 2.3, 5.6}},{"AskPrices",{2.3, 1.2, 6.4}},{"BidQty",{1000.0, 500.0, 64.0}}};
        L2OrderBookList list = {{"IBM",orderBook},{"MSFT",orderBook},{"GOOG",orderBook}};
        InstrumentInfo priceObj = { .longSymbol = "Technology", .lastUpdated = 202004110031, .orderBookList = list, .values = { 1, 2, 3, 4, 5}, .timestamp = 20000101, .other = 25 };

        InstrumentInfo result;
        CHECK_NOTHROW(kdb::convert::to_native(kdb::convert::from_native(priceObj), result));

        CHECK_EQ(priceObj.longSymbol,  result.longSymbol);
        CHECK_EQ(priceObj.lastUpdated, result.lastUpdated);
        CHECK_EQ(priceObj.values,  result.values);
        CHECK_EQ(priceObj.timestamp, result.timestamp);
        CHECK_EQ(priceObj.other, result.other);

        CHECK_EQ(priceObj.orderBookList["IBM"]["BidPrices"], result.orderBookList["IBM"]["BidPrices"]);
        CHECK_EQ(priceObj.orderBookList["IBM"]["AskPrices"], result.orderBookList["IBM"]["AskPrices"]);
        CHECK_EQ(priceObj.orderBookList["IBM"]["BidQty"], result.orderBookList["IBM"]["BidQty"]);

        CHECK_EQ(priceObj.orderBookList["MSFT"]["BidPrices"], result.orderBookList["MSFT"]["BidPrices"]);
        CHECK_EQ(priceObj.orderBookList["MSFT"]["AskPrices"], result.orderBookList["MSFT"]["AskPrices"]);
        CHECK_EQ(priceObj.orderBookList["MSFT"]["BidQty"], result.orderBookList["MSFT"]["BidQty"]);

        CHECK_EQ(priceObj.orderBookList["GOOG"]["BidPrices"], result.orderBookList["GOOG"]["BidPrices"]);
        CHECK_EQ(priceObj.orderBookList["GOOG"]["AskPrices"], result.orderBookList["GOOG"]["AskPrices"]);
        CHECK_EQ(priceObj.orderBookList["GOOG"]["BidQty"], result.orderBookList["GOOG"]["BidQty"]);
    }
}