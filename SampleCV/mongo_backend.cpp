#include "mongo_backend.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include<bsoncxx/types.hpp>
#include <mongocxx/instance.hpp>
#include<mongocxx/client.hpp>
#include<mongocxx/database.hpp>
#include<mongocxx/collection.hpp>
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

namespace seraphim {
void test_mongo() {
	mongocxx::instance instance{};
	mongocxx::client conn(mongocxx::uri("mongodb://192.168.1.106:27017/seraph?readPreference=primary&appname=MongoDB%20Compass&ssl=false"));
	mongocxx::database mnist = conn["mnist"];
	mongocxx::collection train = mnist["test_2_2"];
	auto builder = bsoncxx::builder::stream::document{};
	uint8_t* data = new uint8_t[256];
	memset(data, 0x55, 256);
	bsoncxx::types::b_binary img{ bsoncxx::binary_sub_type::k_binary,256,data };
	bsoncxx::document::value doc_value = builder
		<< "info" << bsoncxx::builder::stream::open_document
		<< "label" << 7<<"label2"<<8<<"data"<<img
		<< bsoncxx::builder::stream::close_document
		<< bsoncxx::builder::stream::finalize;
	auto name = train.name();
	auto doc = doc_value.view();
	bsoncxx::stdx::optional<mongocxx::result::insert_one> result = train.insert_one(doc);
	auto cur = train.find(doc);
	
	printf("seraphim");
}
}


