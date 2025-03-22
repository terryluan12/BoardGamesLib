%module dogan

%{
#include "Coordinate.h"
#include "DoganConfigBuilder.h"
#include "DoganGame.h"


#include "DoganExceptions.h"
#include "AxialHexDirection.h"
#include "enums.h"
using namespace Dogan;
using StructureType = DoganStructureType::Type;
%}

%include <std_array.i>
%include <std_vector.i>

%template(IntArray2) std::array<int, 2>;
%template(IntArray5) std::array<int, 5>;

%include "Coordinate.h"
%template(Coordinate2D) Coordinate<2>;

%include "AxialHexDirection.h"
%include "enums.h"

%include "DoganConfigBuilder.h"
%include "DoganGame.h"
