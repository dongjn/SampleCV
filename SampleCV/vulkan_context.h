#ifndef VULKAN_ANDROID_CONTEXT_H
#define VULKAN_ANDROID_CONTEXT_H
#ifdef _WIN32
#include<Windows.h>
#endif
#define NOMINMAX
#undef max
#undef min

#include<vulkan/vulkan.h>
#include<memory>
#include<vector>
#include <SkCanvas.h>
#include<SkSurface.h>
#include<SkRefCnt.h>
#include<vector>

#ifdef _WIN32
typedef HWND T_WINDOW;
typedef HINSTANCE T_MODULE;
typedef  uint8_t byte;
#elif ANDROID
typedef
#else

typedef void* T_WINDOW;
typedef void* T_MODULE;
#endif


class SkCanvas;
class SkSurface;

using  std::shared_ptr;
using std::unique_ptr;
namespace seraphim {
class SkiaBackedVK;


	class VulkanContext {
	public:
		friend class SkianBancked;
	public:
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		struct InstanceHandle {
			std::vector<const char*> vkInstanceExtensionsName;
			std::vector<const char*> vkLayerExtensionName;
			T_MODULE hInstance{ nullptr };
			VkInstance vkInstance{ VK_NULL_HANDLE };
			VkDebugReportCallbackEXT debugReportCallbackExt;
		};
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		struct DeviceHandle {
			std::vector<const char*> vkDeviceExtensionName;
			VkPhysicalDeviceMemoryProperties memoryProperties;
			VkPhysicalDevice vkPhysicalDevice{ VK_NULL_HANDLE };
			VkDevice  vkDevice{ VK_NULL_HANDLE };
			VkFence submitFence{ VK_NULL_HANDLE };
			VkQueue  graphicQueue{ VK_NULL_HANDLE };
			VkQueue  transferQueue{ VK_NULL_HANDLE };
			VkQueue  calculateQueue{ VK_NULL_HANDLE };
			VkCommandPool graphicPool{VK_NULL_HANDLE};
			VkCommandPool transferPool{ VK_NULL_HANDLE};
			VkCommandPool calculatePool{VK_NULL_HANDLE};
			VkPhysicalDeviceFeatures features;
			uint32_t graphicFamily{ (std::numeric_limits<uint32_t>::max)() };
			uint32_t calculateFamily{ (std::numeric_limits<uint32_t >::max)() };
			uint32_t transferFamily{ (std::numeric_limits<uint32_t>::max)() };

		};
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		struct PresentHandle {
			VkSwapchainKHR swapchain;
			VkSurfaceKHR  surface;
			VkFormat   format;
			VkColorSpaceKHR  colorSpace;
			VkFence acquireFence{VK_NULL_HANDLE};
			VkSemaphore acquireSemaphore{ VK_NULL_HANDLE };
			VkSemaphore commandFinishSemaphore{ VK_NULL_HANDLE };
			std::vector<VkImage> images{0};
			std::vector<VkCommandBuffer> imageCmdBuffer{0};
			uint32_t currentImageIndex;

		};
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
	public:
		friend class SkiaBackedVK;
		static std::shared_ptr<VulkanContext> make(T_WINDOW window, T_MODULE hInstance, uint32_t width, uint32_t height) {
			if (gpVKContext.get() != nullptr)
				return gpVKContext;
			VulkanContext* c = new VulkanContext(window, hInstance, width, height);
			gpVKContext.reset(c);
			gpVKContext->initVulkan();
			gpVKContext->initGrContext();
			return gpVKContext;
		};

		static std::shared_ptr<VulkanContext> get() {
			//assert(gpVKContext);
			return gpVKContext;
		}
		static void release() {
			gpVKContext = nullptr;
		}
	private:

		//global
		uint32_t vulkan_api{ 0 };
		static std::shared_ptr<VulkanContext> gpVKContext;
		T_WINDOW window{ nullptr };
		T_MODULE module{ nullptr };
		uint32_t wWidth;
		uint32_t wHeight;
		InstanceHandle ih;
		DeviceHandle   dh;
		PresentHandle  ph{0};
		bool hashSurface{ false };
	private://toolkit
		uint32_t queryMemoryTypeIndex(uint32_t type,uint32_t require_properites);
	public:

		VulkanContext(T_WINDOW window, T_MODULE hInstance, uint32_t width, uint32_t height);

		void commit();

		//SkCanvas* getCanvas() {
		//	if (backend.get()) {
		//		return backend->surface->getCanvas();
		//	}
		//	return nullptr;
		//}
		void testRead();

		void resize(uint32_t width, uint32_t height);
		void cleanBank(uint32_t image_index);
		void clean();
		void present();
		void draw(uint8_t* data, size_t cbData);
		void copyToSkia();
		void copyToVulakn();
		~VulkanContext();
	private:
		void initVulkan();
		void initInstance();
		void initDevice();
		void initPresent();
		void initGrContext();

	};
};

#endif
