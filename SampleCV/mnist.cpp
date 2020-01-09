#include "mnist.h"
#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>
#include<iostream>
namespace seraphim {
	shared_ptr<Mnist> Mnist::self_{ nullptr };

	shared_ptr<Mnist> ReadDisk(const string& p) {
		shared_ptr<Mnist> mnist = std::make_shared<Mnist>();
		namespace bfs = boost::filesystem ;
		boost::filesystem::path mPath(p);
		auto itr = boost::filesystem::directory_iterator(boost::filesystem::path(p));
		for (auto& f : itr) {
			auto name = bfs::basename(f);
			auto size = bfs::file_size(f);
			bfs::basic_ifstream<uint8_t> fs(f);
			if (name.compare("t10k-images") == 0) {
				fs.seekg(Mnist::image_heat_size_);
				mnist->count_train_ = (size - Mnist::image_heat_size_) / Mnist::image_bytes_;
				mnist->train_images_bytes_ = mnist->count_train_ * Mnist::image_bytes_;
				mnist->image_train = new uint8_t[mnist->train_images_bytes_];
				fs.read(mnist->image_train, mnist->train_images_bytes_);

				
			}
			else if (name.compare("t10k-labels") == 0) {
				assert(mnist->count_train_ == (size - Mnist::label_heat_size_));
				fs.seekg(Mnist::label_heat_size_);
				mnist->train_labels_bytes_ = mnist->count_train_;
				mnist->label_train = new uint8_t[mnist->count_train_];
				fs.read(mnist->label_train, mnist->count_train_);
			}
			else if (name.compare("train-images") == 0) {
				fs.seekg(Mnist::image_heat_size_);
				mnist->count_test_ = (size - Mnist::image_heat_size_) / Mnist::image_bytes_;
				mnist->test_iamges_bytes_ = mnist->count_test_ * Mnist::image_bytes_;
				mnist->image_test = new uint8_t[mnist->test_iamges_bytes_];
				//fs >> mnist->image_test;
			}
			else if (name.compare("train-labels") == 0) {
				assert(mnist->count_test_ == (size - Mnist::label_heat_size_));
				fs.seekg(Mnist::label_heat_size_);
				mnist->label_test = new uint8_t[mnist->count_test_];
				//fs >> mnist->label_test;
			}
			else {
				throw std::logic_error("error");
			}
			fs.close();
		}
		return mnist;
	}


	shared_ptr<Mnist> Mnist::createFormFile(const string& path)
	{
		if (self_ == nullptr) {
			self_ = ReadDisk(path);
		}
		return self_;
	}
};
