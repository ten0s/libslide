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

#include "slide.hpp"
#include "slide_endian.hpp"
#include "slide_writer.hpp"
#include "slide_header_writer.hpp"
//#include "slide_records_writer.hpp"

namespace libslide {

std::ostream&
write_slide(std::ostream& os, const Slide& slide)
{
    const auto& header = slide.header();
    //const auto& records = slide->records();
    Endian endian = header.endian();

    write_slide_header(os, header, endian);

    return os;
}

} // namespace libslide
