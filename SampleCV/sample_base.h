#ifndef SAMPLE_BASE_H
#define SAMPLE_BASE_H
namespace seraphim {
	template< typename F, typename... T> struct Sample {
		using Type = F;
		using NextType = Sample<T...>;
		Type data;
		NextType next;
		Sample(NextType n, Type d) :next(n), data(d) {

		}
        Sample(Type d,T... args):data(d),next(args...){
            
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

	template<typename S,typename D, typename... Args>
	S make_sample(D d, Args... args) {
		typename S::NextType next = make_sample<S::NextType>(args...);
		return S( next,d);
	}

	template<typename S,typename D>
	S make_sample(D d) {
		return S(d);
	}
};
#endif
