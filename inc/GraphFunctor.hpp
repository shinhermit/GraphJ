#ifndef _GraphFunctor
#define _GraphFunctor

#include "MapValueComparator.hpp"
#include "WeightedEdgeComparator.hpp"
#include "GreaterDegreeComparator.hpp"

#include "EdgeWeighter.hpp" //abstract
#include "DefaultEdgeWeighter.hpp"
#include "MpmEdgeWeighter.hpp"

#include "Visitor.hpp" //abstract
#include "ColorizingVisitor.hpp"
#include "DefaultVisitor.hpp"
#include "MathVisitor.hpp"
#include "GraphvizVisitor.hpp"
#include "TricolorBuilderVisitor.hpp"

#include "PathFindingValidator.hpp"
#include "StringConverter.hpp"

#endif
