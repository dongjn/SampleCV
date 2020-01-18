#ifndef MONGO_BACKEND_H
#define MONGO_BACKEND_H
#include"common.h"
#include"sample_base.h"

#include<vector>
#include<string>

#include<mongocxx/client.hpp>
#include<mongocxx/instance.hpp>
#include<mongocxx/database.hpp>
#include<mongocxx/collection.hpp>
#include<bsoncxx/builder/stream/document.hpp>
#include<bsoncxx/json.hpp>
#include<bsoncxx/types.hpp>

using std::string;
using std::vector;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
namespace seraphim {

extern shared_ptr<mongocxx::instance> gMongoInstance;

extern void test_mongo();
template<typename S>


class MongoBacked{
private:
    static constexpr size_t cacheMax_ = 1024 * 64;
    size_t cacheMin_ = 1024;
    size_t bitchSize_ = 256;
    size_t totalTrain_ = 0;
    size_t totalTest_ = 0;
    size_t already_ = 0;
    vector<uint32_t> train_i_{0};
private:
    mongocxx::database db_;
    mongocxx::collection train_co_;
    mongocxx::collection test_co_;
    void fetch(){
        
    }
public:
    using SampleType = S;
    using SampleBitch = vector<SampleType>;
public:
    MongoBacked(const string& uri,const string& dbName,vector<string>& fieldNames ){
        if(!gMongoInstance){
            gMongoInstance.reset(new mongocxx::instance());
        }
        auto conn = mongocxx::client(mongocxx::uri(uri));
        db_ = conn[dbName];
        train_co_ = db_["train"];
        test_co_ = db_["test"];
        auto eDocument = document{} << bsoncxx::v_noabi::builder::stream::finalize;
        totalTrain_ = train_co_.count(eDocument.view());
        totalTest_ =  test_co_.count(eDocument.view());
    }
    MongoBacked(){
        
    }
    
    size_t getBitch(SampleBitch& dst){
        return 0;
    }
    void shuffle();
    void setBitchSize(size_t b){
        bitchSize_ = b;
    }
    
};
}

#endif
