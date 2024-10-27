#include "skrpch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

namespace Sakura
{
	static GLenum GetOpenGLTarget(const TextureDescription& desc)
	{
		switch (desc.ImageType)
		{
			using enum Sakura::ImageType;
			case Image1D: return GL_TEXTURE_1D;
			case Image2D: return GL_TEXTURE_2D;
			case Image3D: return GL_TEXTURE_3D;
			case Cubemap: return GL_TEXTURE_CUBE_MAP;
			default:
				return GL_NONE;
		}
	}

	static GLenum ImageFormatToOpenGLInternalFormat(ImageFormat format)
	{
		switch (format)
		{
			using enum Sakura::ImageFormat;
			case None:    return GL_NONE;
			case RGB8:    return GL_RGB8;
			case RGBA8:   return GL_RGBA8;
			case D32:     return GL_DEPTH_COMPONENT32F;
			default:
				return GL_NONE;
		}
	}

	static GLenum ImageFormatToOpenGLFormat(ImageFormat format)
	{
		switch (format)
		{
			using enum Sakura::ImageFormat;
			case None:    return GL_NONE;
			case RGB8:    return GL_RGB;
			case RGBA8:   return GL_RGBA;
			case D32:     return GL_DEPTH_COMPONENT;
			default:
				return GL_NONE;
		}
	}

	static GLenum ImageFormatToOpenGLType(ImageFormat format)
	{
		switch (format)
		{
			using enum Sakura::ImageFormat;
			case None:    return GL_NONE;
			case RGB8:    return GL_UNSIGNED_BYTE;
			case RGBA8:   return GL_UNSIGNED_BYTE;
			case D32:     return GL_FLOAT;
			default:
				return GL_NONE;
		}
	}

	static GLenum TextureFilterModeToOpenGLFilterMode(TextureFilterMode filterMode, TextureMipmapFilterMode mipmapMode)
	{
		switch (mipmapMode)
		{
			using enum Sakura::TextureMipmapFilterMode;
			case None:
				return filterMode == TextureFilterMode::Linear ? GL_LINEAR : GL_NEAREST;
			case NearestMipmap:
				return filterMode == TextureFilterMode::Linear ? GL_LINEAR_MIPMAP_NEAREST : GL_NEAREST_MIPMAP_NEAREST;
			case LinearMipmap:
				return filterMode == TextureFilterMode::Linear ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR;
			default:
				return GL_NONE;
		}
	}

	static GLenum TextureWrapModeToOpenGLWrapMode(TextureWrapMode wrapMode)
	{
		switch (wrapMode)
		{
			using enum Sakura::TextureWrapMode;
			case Repeat:      return GL_REPEAT;
			case ClampEdge:   return GL_CLAMP_TO_EDGE;
			case ClampBorder: return GL_CLAMP_TO_BORDER;
			case Mirror:      return GL_MIRRORED_REPEAT;
			default:
				return GL_NONE;
		}
	}

	static GLsizei CalculateMipmapLevels(const ImageExtent& extent)
	{
		double maxElement = std::max(std::max(extent.width, extent.height), extent.depth);
		GLsizei mipLevels = static_cast<GLsizei>(std::floor(std::log2(maxElement))) + 1;
		return mipLevels;
	}

	OpenGLTexture::OpenGLTexture(const TextureDescription& desc)
		: Texture(desc)
	{
		GLenum target = GetOpenGLTarget(desc);
		glCreateTextures(target, 1, &m_RendererID);

		GLenum filterMode = TextureFilterModeToOpenGLFilterMode(desc.FilterMode, desc.MipmapFilterMode);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, filterMode);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, filterMode == GL_NEAREST ? filterMode : GL_LINEAR);

		GLenum wrapMode = TextureWrapModeToOpenGLWrapMode(desc.WrapMode);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, wrapMode);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, wrapMode);

		GLsizei mipLevels = 1;
		if (desc.GenerateMipmaps)
			mipLevels = CalculateMipmapLevels(desc.ImageExtent);

		GLenum internalFormat = ImageFormatToOpenGLInternalFormat(desc.ImageFormat);
		const ImageExtent& extent = desc.ImageExtent;

		switch (desc.ImageType)
		{
			using enum Sakura::ImageType;
			case Image1D:
				glTextureStorage1D(m_RendererID, mipLevels, internalFormat, extent.width);
				break;
			case Image2D:
			case Cubemap:
				glTextureStorage2D(m_RendererID, mipLevels, internalFormat, extent.width, extent.height);
				break;
			case Image3D:
				glTextureStorage3D(m_RendererID, mipLevels, internalFormat, extent.width, extent.height, extent.depth);
				break;
			default:
				break;
		}
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture::SetData(const void* data)
	{
		GLenum format = ImageFormatToOpenGLFormat(m_TextureDesc.ImageFormat);
		GLenum type = ImageFormatToOpenGLType(m_TextureDesc.ImageFormat);

		switch (m_TextureDesc.ImageType)
		{
			using enum Sakura::ImageType;
			case Image1D:
				glTextureSubImage1D(m_RendererID, 0, 0, m_TextureDesc.ImageExtent.width, format, type, data);
				break;
			case Image2D:
				glTextureSubImage2D(m_RendererID, 0, 0, 0, m_TextureDesc.ImageExtent.width, m_TextureDesc.ImageExtent.height, format, type, data);
				break;
			case Image3D:
				glTextureSubImage3D(m_RendererID, 0, 0, 0, 0, m_TextureDesc.ImageExtent.width, m_TextureDesc.ImageExtent.height, m_TextureDesc.ImageExtent.depth,
					format, type, data);
				break;
			case Cubemap:
				for (int face = 0; face < 6; face++)
				{
					// Cubemap data is distributed in 6 different pointers, where each pointer corresponds to a different face
					const void* faceData = ((size_t**)(data))[face];
					glTextureSubImage3D(m_RendererID, 0, 0, 0, face, m_TextureDesc.ImageExtent.width, m_TextureDesc.ImageExtent.height, 1, format, type, faceData);
				}
				break;
			default:
				break;
		}

		if (m_TextureDesc.GenerateMipmaps)
			glGenerateTextureMipmap(m_RendererID);
	}
}