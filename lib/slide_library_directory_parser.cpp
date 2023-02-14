#include <cstddef> // offsetof
#include <cstring> // strncpy
#include "slide_library_directory.hpp"
#include "slide_library_directory_parser.hpp"
#include "slide_parser_util.hpp"

namespace {

struct Directory {
    // Slide name (NUL terminated) (32 bytes)
    uint8_t name[32];
    // Address of slide within library file (4 bytes)
    uint32_t addr;
};

} // namespace


namespace libslide {

std::tuple<SlideLibraryDirectory*, size_t>
parse_slide_library_directory(const uint8_t* buf, size_t /*size*/)
{
    SlideLibraryDirectory* dir = nullptr;
    size_t offset = sizeof(Directory);

    constexpr size_t len = offsetof(Directory, addr);
    char name[len];
    strncpy(name, (char*)buf, len);

    // If name is null, then return dir = null, increased
    //  offset should point to the first Slide.
    if (strlen(name) > 0) {
        // The slide address is always written with the low-order byte first.
        uint32_t addr = read<uint32_t>(buf+offsetof(Directory, addr), Endian::LE);
        dir = new SlideLibraryDirectory{
            std::string{name},
            addr
        };
    }

    return {dir, offset};
}

} // namespace libslide