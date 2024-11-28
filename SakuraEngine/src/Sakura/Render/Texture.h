#pragma once

#include "Sakura/Core/Base.h"

namespace Sakura
{
	enum class ImageType
	{
		Image1D,
		Image2D,
		Image3D,
		Cubemap
	};

	struct ImageExtent
	{
		uint32_t width;
		uint32_t height;
		uint32_t depth;
	};

	enum class ImageFormat
	{
		None = 0,
		RGB8,
		RGBA8,
		D32
	};

	enum class TextureFilterMode
	{
		Nearest,
		Linear
	};

	enum class TextureMipmapFilterMode
	{
		None,
		NearestMipmap,
		LinearMipmap
	};

	enum class TextureWrapMode
	{
		Repeat = 0,
		Mirror,
		ClampEdge,
		ClampBorder
	};

	struct TextureDescription
	{
		ImageExtent ImageExtent{1, 1, 1};
		ImageType ImageType = ImageType::Image2D;
		ImageFormat ImageFormat = ImageFormat::RGBA8;
		TextureFilterMode FilterMode = TextureFilterMode::Linear;
		TextureMipmapFilterMode MipmapFilterMode = TextureMipmapFilterMode::None;
		TextureWrapMode WrapMode = TextureWrapMode::Repeat;
		bool GenerateMipmaps = true;
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		inline const TextureDescription& GetDescription() const { return m_TextureDesc; }

		virtual void SetData(const void* data) = 0;

		static Ref<Texture> Create(const TextureDescription& desc);

	protected:
		Texture(const TextureDescription& desc) : m_TextureDesc(desc) {}
		TextureDescription m_TextureDesc;
	};
}

