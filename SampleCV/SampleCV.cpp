﻿// SampleCV.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <opencv2/opencv.hpp>
#include <SkCanvas.h>
#include <boost/filesystem.hpp>
#include<boost/asio.hpp>
#include<thread>
#include"mnist.h"
#include"common.h"
using namespace std;
using namespace cv;
using namespace seraphim;
int main()
{
	auto mnist = Mnist::createFormFile("D:/dataset/mnist/mnist");
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
	auto sample = mnist->getTrainSample(0);
	Mat mat(28, 28, CV_8UC1, std::get<1>(sample));
	auto s =  mat.data;
	cv::imshow("0", mat);
	cv::waitKey();



	return 0;
}