// SampleCV.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <opencv2/opencv.hpp>
#include <SkCanvas.h>
#include <boost/filesystem.hpp>
#include<boost/asio.hpp>
#include<thread>
#include"mnist.h"
#include"common.h"
#include"bith_iterator.h"
#include"data_set.h"
#include"skia_backed_vk.h"
#include"mongo_backend.h"
#include"sample_base.h"
using namespace std;
using namespace cv;
using namespace seraphim;
	//boost::asio::io_service service;
	//std::thread t([&service] {
	//	for (;;) {
	//		int code = 0;
	//		service.run_one();
	//		std::cout << "seraphim" << std::endl;
	//		std::cin >> code;// << std::endl;
	//		if (code == 0)break;
	//	};
	//	std::cout << std::this_thread::get_id() << std::endl;
	//	});
	//service.post([] {
	//	std::cout << "work thread::" << std::this_thread::get_id() << std::endl;
	//	});
	//std::cout << "main thread::" << std::this_thread::get_id() << std::endl;
	//t.join();
	//std::wcout << "exit" << std::endl;
	//auto a = squrt<int, 10000>();
	//auto b = squrt<int, 1000>();
	//std::cout << "a=" << a << "|b=" << b << std::endl;

	//Sample<uint32_t, uint32_t, 1024, 1024> e;
	//auto sample = mnist->getTrainSample(0);
	//Mat mat(28, 28, CV_8UC1, std::get<1>(sample));
	//auto s =  mat.data;
	//cv::imshow("0", mat);
	//cv::waitKey();
//template<typename T,typename... Args>
//void test(T t,Args... args) {
//	printf("seraphim%d   t = %d\n ",t, sizeof...(args));
//	test(args...);
//}
//template<typename D>
//void test(D d) {
//	printf("seraphim call D\n");
//}
int main()
{
	
	test_mongo();
	//auto mnist = Mnist::createFormFile("D:/dataset/mnist/mnist");
	////auto canvas = SkiaBackedVK::makeBacked(0, 1000, 1000);
	//auto vk = VulkanContext::make(NULL, ::GetModuleHandle(nullptr), 1000, 1000);
	//auto backed = SkiaBackedVK::make(vk);
	//auto canvas = backed->makeBacked(0, 1000, 1000);
	//SkPaint paint;
	//paint.setARGB(128, 64, 89, 200);
	//canvas->drawRect({ 100,100,400,400 }, paint);
	//paint.setARGB(255, 0, 0, 255);
	//canvas->drawLine({ 0,0 }, { 400,400 }, paint);
	//uint8_t *buf = new uint8_t[1000 * 1000 * 4];
	//backed->readPixel(0, buf, 1000 * 1000 * 4);
	//Mat mat(1000,1000,CV_8UC4,buf);
	//cv::imshow("seraphim", mat);
	//cv::waitKey(0);
	uint32_t width = 1000;
	uint32_t height = 1000;
	char label = '7';
	uint8_t* buf = nullptr;
    vector<string> fields{"image","index_"};
	using ImageSample = Sample<uint32_t, uint32_t, char, uint8_t*>;
    MongoBacked<ImageSample> backed("mongodb://127.0.0.1:27017/seraph?readPreference=primary&appname=MongoDB%20Compass&ssl=false","mnist",fields);
    MongoBacked<ImageSample>::SampleBitch  bitch(1024);
    backed.getBitch(bitch);
    return 0;
}
