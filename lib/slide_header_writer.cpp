/**
 *   AutoCAD slide library
 *
 *   Copyright (C) 2023 Dmitry Klionsky aka ten0s <dm.klionsky@gmail.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* SPDX-License-Identifier: GPL-3.0-or-later */

#include "slide_header.hpp"
#include "slide_header_writer.hpp"
#include "slide_parser_util.hpp"

namespace libslide {

std::ostream&
write_slide_header(std::ostream& os, const SlideHeader& header, Endian endian)
{
    // Generic Part
    os << "AutoCAD Slide" << '\x0d' << '\x0a' << '\x1a' << '\x00';
    os << header.type_indicator();
    os << header.level_indicator();

    uint8_t buf2[2];
    write(buf2, header.high_x_dot(), endian);
    os.write((char*)buf2, sizeof(buf2));

    write(buf2, header.high_y_dot(), endian);
    os.write((char*)buf2, sizeof(buf2));

    if (header.level_indicator() == 1) {

        // V1 Specific
        uint8_t buf8[8];
        write(buf8, header.aspect_ratio(), endian);
        os.write((char*)buf8, sizeof(buf8));

        write(buf2, header.hardware_fill(), endian);
        os.write((char*)buf2, sizeof(buf2));

        os << '\x00'; // Filler byte

    } else if (header.level_indicator() == 2) {

        // V2 Specific
        uint8_t buf4[4];

        write(buf4, static_cast<uint32_t>(header.aspect_ratio() * 10'000'000), Endian::LE);
        os.write((char*)buf4, sizeof(buf4));

        write(buf2, header.hardware_fill(), endian);
        os.write((char*)buf2, sizeof(buf2));

        write(buf2, 0x1234, endian);
        os.write((char*)buf2, sizeof(buf2));

    } else {
        throw std::runtime_error{"Unknown slide version"};
    }
    return os;
}

} // namespace libslide