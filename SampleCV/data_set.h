#ifndef DATA_SET_H
#define DATA_SET_H
#include"common.h"
#include<vector>
#include<utility>
#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>
namespace seraphim {

	namespace bfs = boost::filesystem;
	template<class X,class Y>
	class DatasetBacked {
	public:
		virtual  size_t count() = 0;
		virtual  std::pair<X, Y> train() = 0 ;
		virtual  size_t train(size_t first, size_t count,std::vector<std::pair<X,Y>>& buf) = 0;
		virtual  size_t train(size_t count ,std::vector<X>&  xbuf, std::vector<Y>& ybuf) = 0;
		virtual  void shuffle() = 0;
	};
	
	template<typename X,typename Y,size_t XS,size_t YS=sizeof(Y),size_t Xoffset=0,size_t Yoffset=0>
	class FilesDataset : public DatasetBacked<X, Y> , public std::enable_shared_from_this<FilesDataset<X,Y,XS,YS,Xoffset,Yoffset>> {
	private:

	public:
		FileDataset() {

		}
	public:
		virtual  size_t count() override {
			return 0;
		};
		virtual std::pair<X, Y> train() override {
			return std::make_pair(X(0), Y(0));
		}
		virtual  size_t train(size_t first, size_t count, std::vector& < std::pair<X, Y>> buf) {
			return 0;
		};
		virtual  size_t train(std::vector<X>&  xbuf, std::vector<Y>& ybuf) override {
			return 0;
		};
		virtual  void shuffle() override {
		};
	};

};


#endif