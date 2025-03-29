%module dogan

%{
#include "Coordinate.h"
#include "DoganResponse.h"
#include "DoganConfigBuilder.h"
#include "DoganGame.h"
using namespace Dogan;
%}

%insert(cgo_comment) %{
#cgo CPPFLAGS: -I${SRCDIR}/../../../include -I${SRCDIR}/../../../dogan/include -I${SRCDIR}/../../../dogan/libs -I${SRCDIR}/../../../dogan/libs/Configuration -I${SRCDIR}/../../../dogan/libs/Structures
#cgo LDFLAGS: -L${SRCDIR}/../../src/HexGame -L${SRCDIR}/../../dogan -L${SRCDIR}/../../dogan/libs -L${SRCDIR}/../../dogan/libs/Configuration -L${SRCDIR}/../../dogan/libs/Structures
#cgo LDFLAGS: -lGame -lBoard -lCell -lBank -lStructure -lBuilding -lConfig -lConfigBuilder -lElement -lVertex -lEdge -lAxialDirection -lPlayer -lenums
%}

%include <std_array.i>
%include <std_vector.i>
%include "exception.i"
%include "std_string.i"

%template(IntArray5) std::array<int, 5>;
%template(IntArray2) std::array<int, 2>;

%include "Coordinate.h"
%template(Coordinate2D) Coordinate<2>;

%include "AxialDirection.h"
%include "enums.h"
%exception {
    try {
        $function;
    } catch (const std::invalid_argument& e) {
        SWIG_exception(SWIG_AttributeError, e.what());
    }
}

%include "DoganResponse.h"
%include "DoganConfigBuilder.h"
%include "DoganGame.h"