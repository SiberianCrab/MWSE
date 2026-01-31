#include "NIPixelFormat.h"

namespace NI {
	const auto NI_PixelFormat_ctor = reinterpret_cast<PixelFormat*(__thiscall*)(PixelFormat*, unsigned int, unsigned int, unsigned int, unsigned int, int)>(0x6ED7C0);
	PixelFormat::PixelFormat(unsigned int maskR, unsigned int maskG, unsigned int maskB, unsigned int maskA, int bitsPerPixel) {
		NI_PixelFormat_ctor(this, maskR, maskG, maskB, maskA, bitsPerPixel);
	}
}
