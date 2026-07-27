#pragma once
#include <fstream>
#include <string>
#include <cstdint>

namespace bin {
	inline void writeHeader(std::ostream& os) {
		const char h[4] = { 'P', 'H', 'B', 0x01 };
		os.write(h, 4);
	}
	inline bool readHeader(std::istream& is) {
		char h[4] = { 0, 0, 0, 0 };
		is.read(h, 4);
		return (bool)is && h[0] == 'P' && h[1] == 'H' && h[2] == 'B' && h[3] == 0x01;
	}
	inline void writeInt(std::ostream& os, int v) {
		int32_t x = (int32_t)v;
		os.write(reinterpret_cast<const char*>(&x), 4);
	}
	inline int readInt(std::istream& is) {
		int32_t x = 0;
		is.read(reinterpret_cast<char*>(&x), 4);
		return (int)x;
	}
	inline void writeStr(std::ostream& os, const std::string& s) {
		writeInt(os, (int)s.size());
		os.write(s.data(), s.size());
	}
	inline std::string readStr(std::istream& is) {
		int n = readInt(is);
		if (n < 0 || n > 4096) return std::string(); // guarda contra lixo
		std::string s(n, '\0');
		if (n > 0) is.read(&s[0], n);
		return s;
	}
}
