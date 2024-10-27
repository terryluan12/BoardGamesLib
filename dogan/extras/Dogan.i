%module dogan
%{
#include "DoganConfigBuilder.h"
#include "DoganExceptions.h"
#include "CDoganGame.h"
#include "AxialHexDirection.h"
#include "Coordinate.h"
#include "enums.h"
using namespace Dogan;
%}


%include <std_array.i>
%template(IntArray5) std::array<int, 5>;
%template(IntArray2) std::array<int, 2>;

%include "Config.h"
%include "Coordinate.h"
%include "DoganConfigBuilder.h"
%include "CDoganGame.h"
%include "AxialHexDirection.h"
%include "DoganExceptions.h"
%include "enums.h"

%template(Coordinate2D) Coordinate<2>;