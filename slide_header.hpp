#ifndef __SLIDE_HEADER_HPP__
#define __SLIDE_HEADER_HPP__

#include <string>
#include "slide_endian.hpp"

class SlideHeader {
public:
    explicit SlideHeader(const std::string& id_string,
                         char type_indicator,
                         char level_indicator,
                         short high_x_dot,
                         short high_y_dot,
                         double aspect_ration,
                         short hardware_fill,
                         Endian endian)
        : _id_string{id_string},
          _type_indicator{type_indicator},
          _level_indicator{level_indicator},
          _high_x_dot{high_x_dot},
          _high_y_dot{high_y_dot},
          _aspect_ratio{aspect_ration},
          _hardware_fill{hardware_fill},
          _endian{endian}
        {}

    std::string id_string() const { return _id_string; }
    int type_indicator() const { return _type_indicator; }
    int level_indicator() const { return _level_indicator; }
    short high_x_dot() const { return _high_x_dot; }
    short high_y_dot() const { return _high_y_dot; }
    double aspect_ratio() const { return _aspect_ratio; }
    short hardware_fill() const { return _hardware_fill; }
    Endian endian() const { return _endian; }

private:
    std::string _id_string;
    char _type_indicator;
    char _level_indicator;
    short _high_x_dot;
    short _high_y_dot;
    double _aspect_ratio;
    short _hardware_fill;
    Endian _endian;
};

std::ostream& operator<<(std::ostream& os, const SlideHeader& header);

#endif // __SLIDE_HEADER_HPP__