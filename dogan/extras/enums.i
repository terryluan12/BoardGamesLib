%module dogan_enums
%{
#include "enums.h"
using namespace Dogan;
using StructureType = DoganStructureType::Type;
%}

%include "enums.h"

%apply unsigned int { ResourceType, DevelopmentType, StructureType };

%pythoncode %{
import dogan_enums
for name in dir(dogan_enums):
    prefixes = ["Resource_", "Development_", "DoganStructureType_"]
    for prefix in prefixes:
        if name.find(prefix) == 0:
            setattr(dogan_enums, name[len(prefix):], getattr(dogan_enums, name))
            delattr(dogan_enums, name) # optional
del name
%}