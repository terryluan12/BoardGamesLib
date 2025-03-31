%module dogan

%{
#include "Coordinate.h"
#include "DoganResponse.h"
#include "DoganConfigBuilder.h"
#include "DoganGame.h"
#include <vector>
using namespace Dogan;
%}

%insert(cgo_comment) %{
#cgo CPPFLAGS: -I${SRCDIR}/../../../include -I${SRCDIR}/../../../dogan/include -I${SRCDIR}/../../../dogan/libs -I${SRCDIR}/../../../dogan/libs/Configuration -I${SRCDIR}/../../../dogan/libs/Structures
#cgo LDFLAGS: -L${SRCDIR}/../../src/HexGame -L${SRCDIR}/../../dogan -L${SRCDIR}/../../dogan/libs -L${SRCDIR}/../../dogan/libs/Configuration -L${SRCDIR}/../../dogan/libs/Structures
#cgo LDFLAGS: -lGame -lBoard -lCell -lBank -lStructure -lBuilding -lConfig -lConfigBuilder -lElement -lVertex -lEdge -lAxialDirection -lPlayer -lenums
%}

%include "std_array.i"
%include "std_vector.i"
%include "std_pair.i"
%include "std_string.i"
%include "Coordinate.h"
%include "AxialDirection.h"
%include "enums.h"


%template(IntArray2) std::array<int, 2>;
%template(IntArray3) std::array<int, 3>;
%template(IntArray5) std::array<int, 5>;
%template(IntVector) std::vector<int>;
%template(CoordinateVector) std::vector<std::array<int, 2>>;
%template(Point) std::pair<std::array<int, 2>, int>;
%template(DockVector) std::vector<std::pair<std::array<int, 2>, int>>;
%template(PortVector) std::vector<std::vector<std::pair<std::array<int, 2>, int>>>;

%include "DoganResponse.h"
%include "DoganConfigBuilder.h"
%include "DoganGame.h"