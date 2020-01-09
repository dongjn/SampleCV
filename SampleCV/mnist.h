#pragma once
#include"common.h"
using std::shared_ptr;

namespace seraphim {
	class Mnist : public std::enable_shared_from_this<Mnist> {
	private:
		static shared_ptr<Mnist> self_;
		static constexpr int  image_heat_size_{ 16 };
	    static constexpr int label_heat_size_{ 8 };
		static constexpr uint32_t   width_{ 28 };
		static constexpr uint32_t   height_{ 28 };
		static constexpr uint32_t image_bytes_ = width_ * height_;
		uint32_t count_train_{ 0 };
		uint32_t count_test_{ 0 };
		size_t train_images_bytes_{ 0 };
		size_t train_labels_bytes_{ 0 };
		size_t test_iamges_bytes_{ 0 };
		size_t test_labels_bytes_{ 0 };
	protected:
	private:
		uint8_t* image_train{ nullptr };
		uint8_t*    label_train{ nullptr };
		uint8_t* image_test{ nullptr };
		uint8_t* label_test{ nullptr };
	public:
		Mnist() {
		};
		~Mnist() {
			delete[] image_train;
			delete[] label_train;
			delete[] image_test;
			delete[] label_test;
		}
		friend shared_ptr<Mnist> ReadDisk(const string& p);
		
		static shared_ptr<Mnist>  createFormFile(const string& path);
	public:
		std::pair<char, uint8_t*> getTrainSample(uint32_t index) {
			uint8_t* sample = image_train + image_bytes_ * index;
			char digital= label_train[index];
			return std::make_pair(digital, sample);
		}
	};


}
