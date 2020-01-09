#ifndef DATA_SET_H
#define DATA_SET_H
#include"common.h"
#include<vector>
#include<utility>
#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>
#include
namespace seraphim {

	namespace bfs = boost::filesystem;
	using std::vector;

	template<class X,class Y>
	class DatasetBacked {
	public:
		virtual  size_t count() = 0;
		virtual  std::pair<X, Y> train() = 0 ;
		virtual  size_t train(size_t count ,std::vector<X>&  xbuf, std::vector<Y>& ybuf) = 0;
		virtual  void shuffle() = 0;
	};
	
	template<typename X,typename Y,size_t XS,size_t YS=sizeof(Y),size_t Xoffset=0,size_t Yoffset=0>
	class FilesDataset : public DatasetBacked<X, Y> , public std::enable_shared_from_this<FilesDataset<X,Y,XS,YS,Xoffset,Yoffset>> {
	private:
		X* x_train_{nullptr};
		Y* y_train{ nullptr };
		X* x_test_{ nullptr };
		Y* y_test_{ nullptr };
	public:
		FilesDataset(const string& strPath,const vector<string> files) {


			bfs::path p(strPath);
			if (!bfs::is_directory(p)) throw std::logic_error(strPath + string(" not is directory"));
			if (files.size() > 4) throw std::logic_error("too more files , at more 4,1 {train_x train_y,test_x,test_y(options)");
			for (size_t i = 0; i < files.size(); i++) {
				auto file = p / bfs::path(files[i]);
				size_t s = bfs::file_size(file);
				
			}

		}
		~FilesDataset() {
			delete[] x_train_;
			delete[] y_test_;
			delete[] x_test_;
			delete[] y_test_;
		}
	public:
		virtual  size_t count() override {
			return 0;
		};
		virtual std::pair<X, Y> train() override {
			return std::make_pair(X(0), Y(0));
		}
		virtual  size_t train(size_t count,std::vector<X>&  xbuf, std::vector<Y>& ybuf) override {
			return 0;
		};
		virtual  void shuffle() override {
		};
	};

};


#endif