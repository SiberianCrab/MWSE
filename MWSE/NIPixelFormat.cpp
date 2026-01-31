#include "NIPixelFormat.h"

namespace NI {
	const auto NI_PixelFormat_ctor = reinterpret_cast<PixelFormat*(__thiscall*)(PixelFormat*, unsigned int, unsigned int, unsigned int, unsigned int, int)>(0x6ED7C0);
	PixelFormat::PixelFormat(unsigned int maskR, unsigned int maskG, unsigned int maskB, unsigned int maskA, int bitsPerPixel) {
		NI_PixelFormat_ctor(this, maskR, maskG, maskB, maskA, bitsPerPixel);
	}

	PixelFormat::PixelFormat(D3DFORMAT d3dFormat) {
		switch (d3dFormat) {
		case D3DFMT_R8G8B8:
		case D3DFMT_X8R8G8B8:
			NI_PixelFormat_ctor(this, 0xFF0000u, 0xFF00u, 0xFFu, 0, 32);
			break;
		case D3DFMT_R5G6B5:
			NI_PixelFormat_ctor(this, 0xF800u, 0x7E0u, 0x1Fu, 0, 16);
			break;
		case D3DFMT_X1R5G5B5:
			NI_PixelFormat_ctor(this, 0x7C00u, 0x3E0u, 0x1Fu, 0, 16);
			break;
		case D3DFMT_A1R5G5B5:
			NI_PixelFormat_ctor(this, 0x7C00u, 0x3E0u, 0x1Fu, 0x8000u, 16);
			break;
		case D3DFMT_A4R4G4B4:
			NI_PixelFormat_ctor(this, 0xF00u, 0xF0u, 0xFu, 0xF000u, 16);
			break;
		}
	}
}
