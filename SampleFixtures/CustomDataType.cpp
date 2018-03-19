// Originally written by David Venditti.

#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <iostream>

#include <boost/algorithm/string.hpp>

#include "fitnesse/cppslim/DecisionFixture.h"
#include "fitnesse/cppslim/Registry.h"

struct Vector {
    Vector( int X = 0, int Y = 0, int Z = 0 )
            : x{ X }, y{ Y }, z{ Z } {
        //std::cerr << __FUNCTION__ << std::endl;
    };
    Vector& operator+( Vector const& other ) {
        //std::cerr << __FUNCTION__ << std::endl;
        x += other.x;
        y += other.y;
        z += other.z;
        return (*this);
    }
    int x; int y; int z;
};

namespace slim {
    inline void slim2type( Context& ctx, const List& list, Vector& result ) {
        std::cerr << __FUNCTION__ << std::endl;
        std::vector< std::string > Ss;
        if (list.isList) { throw Exception("list of list not supported"); }
        boost::split( Ss, list.string, boost::is_any_of( "," ) );
        if (Ss.size() != 3) { throw Exception("invalid argument count"); }
        std::vector< int > Is;
        std::transform(Ss.cbegin(), Ss.cend(), std::back_inserter( Is ),
                       [](std::string const& S) { return std::stoi(S); });
        if (Is.size() != 3) { throw Exception("invalid argument count"); }
        result.x = Is[0];
        result.y = Is[1];
        result.z = Is[2];
    }
    inline List type2slim( Context& ctx, const Vector& input ) {
        std::cerr << __FUNCTION__ << std::endl;
        std::stringstream SS;
        SS << input. x << ","
           << input.y << ","
           << input.z;
        return List( SS.str() );
    }
}

SLIM_DEFINE_FIXTURE(CustomDataType) {
        public:
        using MapStrStr = std::map< std::string, std::string >;
        static void RegisterMethods() {
            //std::cerr << __FUNCTION__ << std::endl;
            RegisterCtor0();
            RegisterMember( "V1", &CustomDataType::V1 );
            RegisterMember( "V2", &CustomDataType::V2 );
            RegisterMethod( "sum", &CustomDataType::sum );
        }
        private:
        Vector V1;
        Vector V2;
        Vector const& sum() {
            //std::cerr << __FUNCTION__ << std::endl;
            return V1 + V2;
        }
};
