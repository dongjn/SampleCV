#ifndef MONGO_BACKEND_H
#define MONGO_BACKEND_H
#include"common.h"
#include"sample_base.h"

#include<vector>
#include<string>
#include<iostream>
#include<memory>
#include <algorithm> // std::move_backward
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
#include<mongocxx/client.hpp>
#include<mongocxx/instance.hpp>
#include<mongocxx/database.hpp>
#include<mongocxx/collection.hpp>
#include<bsoncxx/builder/basic/document.hpp>
#include<bsoncxx/builder/basic/kvp.hpp>
#include<bsoncxx/json.hpp>


 
using std::string;
using std::vector;
using bsoncxx::builder::basic::kvp;
//using bsoncxx::builder::stream::close_array;
//using bsoncxx::builder::stream::close_document;
//using bsoncxx::builder::stream::document;
//using bsoncxx::builder::stream::finalize;
//using bsoncxx::builder::stream::open_array;
//using bsoncxx::builder::stream::open_document;
namespace seraphim {

extern shared_ptr<mongocxx::instance> gMongoInstance;



template<typename S>
class MongoBacked{
    public:
    using SampleType = S;
    using SampleBitch = vector<SampleType>;
private:
    static constexpr size_t cacheMax_ = 1024 * 64;
    size_t cacheMin_ = 1024;
    size_t bitchSize_ = 256;
    size_t totalTrain_ = 0;
    size_t totalTest_ = 0;
    size_t already_ = 0;
    vector<uint32_t> train_i_{0};
    vector<SampleType> samples_;
private:
    bsoncxx::builder::basic::document empty_doc_{};
    bsoncxx::builder::basic::document proj_doc_{};
    mongocxx::database db_;
    mongocxx::collection train_co_;
    mongocxx::collection test_co_;
    mongocxx::options::find find_ops_{};
    
    SampleBitch train_;
    SampleBitch test_;
    void fetch_(){
        auto cursor = train_co_.find(empty_doc_.view(),find_ops_);
        for(auto c : cursor){
            auto itr = c.begin();
            SampleType s(itr);
            samples_.push_back(std::move(s));
        }
        std::cout<<samples_.size()<<std::endl;
    }

    
public:
    MongoBacked(const string& uri,const string& dbName,vector<string>& fieldNames ){
        if(!gMongoInstance){
            gMongoInstance.reset(new mongocxx::instance());
        }
        auto conn = mongocxx::client(mongocxx::uri(uri));
        db_ = conn[dbName];
        train_co_ = db_["train"];
        test_co_ = db_["test"];
        for(auto s : fieldNames){
            proj_doc_.append(bsoncxx::builder::basic::kvp(s,"1"));
        }
        proj_doc_.append(bsoncxx::v_noabi::builder::basic::kvp("_id", 0));
        totalTrain_ = train_co_.count(empty_doc_.view());
        totalTest_ =  test_co_.count(empty_doc_.view());
        find_ops_.projection(proj_doc_.view());
        fetch_();
        
    }
    MongoBacked(){
        
    }
    
    size_t getBitch(SampleBitch& dst){
        return 0;
    }
    void shuffle(){
        unsigned seed = std::chrono::system_clock::now ().time_since_epoch ().count ();
        std::shuffle (samples_.begin (), samples_.end (), std::default_random_engine (seed));
    }
    void setBitchSize(size_t b){
        bitchSize_ = b;
    }
    
};
}

#endif
