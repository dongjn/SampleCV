#ifndef SKIA_BACKED_CONTEXT
#define SKIA_BACKED_CONTEXT
#include <SkCanvas.h>
#include<SkSurface.h>
#include"vulkan_context.h"
#include<gpu/GrContext.h>
#include<gpu/vk/GrVkExtensions.h>
//#include<gpu/vk/GrVkMemoryAllocator.h>
#include<gpu/vk/GrVkBackendContext.h>
#include<gpu/vk/GrVkVulkan.h>
#include<memory>
#include<string>
#include<unordered_map>
class GrVkExtensions;

using std::shared_ptr;
using std::unique_ptr;
using std::string;
namespace seraphim {
	class SkiaBackedVK {
	private:
		struct BackendHandle{
			string tag;
			VkImage  image{VK_NULL_HANDLE};
			VkDeviceMemory skiaImageMemory{VK_NULL_HANDLE};
			VkDeviceMemory transferMemory{VK_NULL_HANDLE};
			VkBuffer       transferBuffer{ VK_NULL_HANDLE };
			uint32_t width{(std::numeric_limits<uint32_t>::max)()};
			uint32_t height{(std::numeric_limits<uint32_t>::max)()};
			VkFormat format;
			VkColorSpaceKHR colorSpace;
			sk_sp<SkSurface> surface;
			BackendHandle() {};
			BackendHandle(const BackendHandle&& o) 
				:tag(o.tag),
				image(o.image),
				skiaImageMemory(o.skiaImageMemory), 
				transferMemory(o.transferMemory),
				transferBuffer(o.transferBuffer),
				width(o.width),
				height(o.height)
			{

			}
		};
	public:
		static shared_ptr<SkiaBackedVK> get();
		static shared_ptr<SkiaBackedVK> make(shared_ptr<VulkanContext> vkContext);
		static void release();
	private:
		
		VkCommandPool  commandPool;
		VkQueue tranQueue;
		VkCommandBuffer commandBuffer;
		VkFence  submintFence;
		shared_ptr<VulkanContext> vkContext;
		unique_ptr<GrVkExtensions> grVkExtensions;
		sk_sp<GrContext> grContext;
		static shared_ptr<SkiaBackedVK> self;
		std::unordered_map<int, std::shared_ptr<BackendHandle>> mapBackend;
		SkiaBackedVK(shared_ptr<VulkanContext> context) :vkContext(context) {

		}
		bool init();
	public:// Toolkit

	public:
		unique_ptr<SkCanvas> makeBacked(int tag, uint32_t w, uint32_t h, VkFormat ft = VK_FORMAT_B8G8R8_UINT, VkColorSpaceKHR  cs = VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT);
		unique_ptr<SkCanvas> resizeBacked(int tag, uint32_t width, uint32_t height);
		std::unordered_map<int,std::shared_ptr<BackendHandle>>::iterator releaseBacked(int tag);
		size_t readPixel(int tag, uint8_t* buf, size_t data);
		size_t readPixel_0(int tag, uint8_t* buf, size_t data);
		~SkiaBackedVK();
		
		
	};

}


#endif
