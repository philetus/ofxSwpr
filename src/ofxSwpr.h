#pragma once

// #define BOOST_POLYGON_NO_DEPS
// #define BOOST_NO_USER_CONFIG
// #define BOOST_NO_COMPILER_CONFIG
// #define BOOST_NO_STDLIB_CONFIG
// #define BOOST_NO_PLATFORM_CONFIG
// #define BOOST_HAS_STDINT_H

// #define __GLIBC__ 0

#include "boost/polygon/voronoi.hpp"
#include "ofMain.h"
//#include "VoronoiDiagram.h"

namespace ofxSwpr {
    // define point concept for boost lib :P
    struct Point {
        int X;
        int Y;
        Point(int x = 0, int y = 0) : X(x), Y(y) {}
    };
}

namespace boost {
    namespace polygon {
        template <>
        struct geometry_concept<ofxSwpr::Point> { typedef point_concept type; };

        template <>
        struct point_traits<ofxSwpr::Point> {
            typedef int coordinate_type;

            static inline coordinate_type get(const ofxSwpr::Point& point, orientation_2d orient) {
                return (orient == HORIZONTAL) ? point.X : point.Y;
            }
        };
    }
}

using namespace boost::polygon;

namespace ofxSwpr {

    class Cll {
    public:

        Cll(long long dx = -1) : srcdx(dx), clrd(false), opn(false) {}
        ~Cll() {}

        void mesh(ofVboMesh &msh, std::vector<glm::vec3>srcs, std::vector<glm::vec3> gens);
        void setColor(ofColor c);
        void clearColor();

        long long srcdx;
        std::vector<std::size_t> nbrdxs;
        std::vector<long long> gendxs;
        ofColor clr;
        bool clrd;
        bool opn; // flag to set if perimeter not closed
    };

    class Swpr {

    public:

        Swpr();
        ~Swpr();

        void addSource(double x, double y);
        void addSource(glm::vec3 src) {
            addSource(src.x, src.y);
        }
        void diagram();
        void mesh();
        void clear();

        std::vector<glm::vec3> srcs, gens; // source points to generate 
        std::vector<Cll> clls;
        ofVboMesh vrn;

    private:

        voronoi_diagram<double> bvd;
    };

}