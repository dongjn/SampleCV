#ifndef SAMPLE_BASE_H
#define SAMPLE_BASE_H
#include<bsoncxx/builder/basic/document.hpp>
//#include<string.h>
namespace seraphim {
using b_view = bsoncxx::document::view;
using v_iterator = bsoncxx::document::view::iterator;


struct Bytes{
    Bytes(const uint8_t* buf,uint32_t len){
        buf_ = new uint8_t[len];
        memcpy(buf_,buf,len);
    }
    
    Bytes(Bytes&& o){
        buf_ = o.buf_;
        o.buf_ = nullptr;
    }
    
    Bytes(){
        
    }
    uint8_t* buf_{nullptr};
    ~Bytes(){
        delete[] buf_;
    }
};

template<typename T>
inline T element_to_data(v_iterator i){

}
template<>
inline uint32_t element_to_data<uint32_t>(v_iterator i){
    return i->get_int32();
}

template<>
inline uint16_t element_to_data<uint16_t>(v_iterator i){
    return (uint16_t)i->get_int64();
}
template<>
inline Bytes element_to_data<Bytes>(v_iterator i){
    auto binary = i->get_binary();
    const uint8_t* buf = binary.bytes;
    uint32_t len = binary.size;
    return Bytes(buf,len);
}


template< typename F, typename... T> struct Sample {
    using Type = F;
    using NextType = Sample<T...>;
    Type data;
    NextType next;
    Sample(NextType n, Type d) :next(n), data(d) {
        
    }
    Sample(Type d,T... args):data(d),next(args...){
        
    }
    Sample(v_iterator& itr):data(element_to_data<F>(itr)),next(++itr){

    }
    Sample(){
        
    }
};

template<typename F> struct Sample<F> {
    using Type = F;
    using NextType = void;
    Type  data;
    Sample(Type d) :data(d) {
        
    }
    Sample(){
        
    }
    Sample(v_iterator& itr):data(element_to_data<F>(itr)){
        
    }
};
template<int I,typename R,typename S>
R get_field(S sample) {
    if constexpr (I == 0) {
        return sample.data;
    }
    else {
        return (get_field<I - 1,R>(sample.next));
    }
}

};
#endif
