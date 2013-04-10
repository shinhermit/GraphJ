#include "Violation.hpp"

using namespace GraphTypes;
using namespace FlowTypes;

Violation::Violation():
  _violationType(UNDEFINED)
{}

Violation::Violation(const Violation::E_Violation & violationType):
  _violationType(violationType)
{}

Violation::Violation(const Violation & source)
  _violationType(source._violationType)
{}

Violation & Violation::operator=(const Violation & source)
{
  _violationType = source._violationType;
}

Violation & Violation::operator=(const Violation::E_Violation & violationType)
{
  _violationType = violationType;
}

bool Violation::Violation::operator==(const Violation & ref)const
{
  return _violationType == ref._violationType;
}

bool Violation::operator==(const Violation::E_Violation & violationType)const
{
  return _violationType == violationType;
}

bool Violation::operator!=(const Violation & ref)const
{
  return !operator==(ref);
}

bool Violation::operator!=(const Violation::E_Violation & violationType)const
{
  return !operator==(violationType);
}

bool operator==(const Violation::E_Violation & violationType, const Violation & violation)
{
  return violation.operator==(violationType);
}

bool operator!=(const Violation::E_Violation & violationType, const Violation & violation)
{
  return violation.operator!=(violationType);
}

std::string Violation::toString()const
{
  std::string conv;

  switch(_violation)
    {
    case UNDEFINED:
      conv = "Unset violation";
      break;

    case NOVIOLATION:
      conv = "no violation";
      break;

    case CONSERVATION_VIOLATION:
      conv = "consertaion violation";
      break;

    case INTERNAL_NEUTRALITY_VIOLATION:
      conv = "internal neutrality violation";
      break;

    case FLOW_LIMITS_VIOLATION:
      conv = "flow limits violation";
      break;

    default:
      conv = "unknow violation code";
    }

  return conv;
}

const Violation::E_Violation & Violation::violationType()const
{
  return _violationType;
}
