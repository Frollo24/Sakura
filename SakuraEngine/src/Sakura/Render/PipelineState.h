#pragma once

#include "Sakura/Core/Base.h"

namespace Sakura
{
#pragma region PipelineDepthState
	enum class DepthComparison : uint8_t
	{
		None,
		Less,
		Equal,
		LessOrEqual,
		Greater,
		NotEqual,
		GreaterOrEqual,
		Always
	};

	struct DepthBoundaries
	{
		float MinDepth = 0.0f;
		float MaxDepth = 1.0f;
	};

	struct PipelineDepthState
	{
		DepthBoundaries DepthRange{};
		DepthComparison DepthFunc = DepthComparison::Less;
		bool DepthTest = true;
		bool DepthWrite = true;
	};
#pragma endregion

#pragma region PipelineBlendState
	enum class ColorWriteMask
	{
		ColorWriteMaskR = SKR_BIT(0), // 1 (0x0001)
		ColorWriteMaskG = SKR_BIT(1), // 2 (0x0010)
		ColorWriteMaskB = SKR_BIT(2), // 4 (0x0100)
		ColorWriteMaskA = SKR_BIT(3), // 8 (0x1000)
		ColorWriteMaskAll = ColorWriteMaskR | ColorWriteMaskG | ColorWriteMaskB | ColorWriteMaskA, // 15 (0x1111)
	};

	enum class BlendFactor
	{
		Zero, One,
		SrcColor, OneMinusSrcColor, DstColor, OneMinusDstColor,
		SrcAlpha, OneMinusSrcAlpha, DstAlpha, OneMinusDstAlpha,
		ConstantColor, OneMinusConstantColor,
		ConstantAlpha, OneMinusConstantAlpha,
	};

	enum class BlendOperation
	{
		Add, Subtract, ReverseSubtract, Minimum, Maximum,
		SrcMinusDst = Subtract,
		DstMinusSrc = ReverseSubtract,
	};

	struct BlendingEquation
	{
		BlendFactor SrcFactor = BlendFactor::One;
		BlendFactor DstFactor = BlendFactor::Zero;
		BlendOperation Operation = BlendOperation::Add;
	};

	struct BlendConstants
	{
		float R = 0.0f;
		float G = 0.0f;
		float B = 0.0f;
		float A = 0.0f;
	};

	struct PipelineBlendState
	{
		ColorWriteMask ColorWriteMask = ColorWriteMask::ColorWriteMaskAll;
		BlendingEquation ColorEquation{};
		BlendingEquation AlphaEquation{};
		BlendConstants ConstantColor{};
		bool BlendEnable = false;
	};

	SKR_DEFINE_ENUM_FLAG_OPERATORS(ColorWriteMask);
#pragma endregion

#pragma region PipelinePolygonState
	enum class PolygonRasterMode
	{
		Fill,
		Line,
		Point
	};

	enum class CullingMode
	{
		None,
		Front,
		Back,
		FrontAndBack
	};

	enum class FrontFaceMode
	{
		CounterClockwise,
		Clockwise
	};

	struct PipelinePolygonState
	{
		PolygonRasterMode PolygonMode = PolygonRasterMode::Fill;
		CullingMode CullMode = CullingMode::Back;
		FrontFaceMode FrontFace = FrontFaceMode::CounterClockwise;
	};
#pragma endregion
}