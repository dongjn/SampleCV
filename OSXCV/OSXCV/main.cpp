////
////  main.cpp
////  OSXCV
////
////  Created by seraph on 14/1/2020.
////  Copyright © 2020 tqhl. All rights reserved.
////
//
//#include <iostream>
//#include<opencv2/opencv.hpp>
//#include<SkCanvas.h>
//#include<SkPaint.h>
//#include<GLFW/glfw3.h>
//#include"../../SampleCV/vulkan_context.h"
//#include"../../SampleCV/skia_backed_vk.h"
//using namespace seraphim;
//using namespace cv;
////int main(int argc, const char * argv[]) {
////    GLFWwindow* win;
////    if(!glfwInit()){
////        return -1;
////    }
////    win = glfwCreateWindow(640, 480, "OpenGL Base Project", NULL, NULL);
////    if(!win)
////    {
////        glfwTerminate();
////        return -1;
////    }
////    glfwMakeContextCurrent(win);
////    while(!glfwWindowShouldClose(win)){
////
////        glfwSwapBuffers(win);
////        glfwPollEvents();
////    }
////    glfwTerminate();
////    return 0;
////}
//int main(int argc, const char * argv[]) {
//
//
//    //
////    auto mnist = Mnist::createFormFile("D:/dataset/mnist/mnist");
//    //auto canvas = SkiaBackedVK::makeBacked(0, 1000, 1000);
//    auto vk = VulkanContext::make(NULL, nullptr, 1000, 1000);
//    auto backed = SkiaBackedVK::make(vk);
//    auto canvas = backed->makeBacked(0, 1000, 1000);
//    SkPaint paint;
//    paint.setARGB(128, 64, 89, 200);
//    canvas->drawRect({ 100,100,400,400 }, paint);
//    paint.setARGB(255, 0, 0, 255);
//    canvas->drawLine({ 0,0 }, { 400,400 }, paint);
//    uint8_t *buf = new uint8_t[1000 * 1000 * 3];
//    backed->readPixel(0, buf, 1000 * 1000 * 3);
//    Mat mat(1000,1000,CV_8UC3,buf);
//    cv::imshow("seraphim", mat);
//    cv::waitKey(0);
//    return 0;
//}



#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include<MoltenVK/vk_mvk_moltenvk.h>
#include <iostream>

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
    
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported" << std::endl;

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;
    
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    
    return 0;
}
