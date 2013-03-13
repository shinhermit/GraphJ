#include "PlanningActivity.hpp"

PlanningActivity::PlanningActivity():_label(""), _description(""), _duration(0){}

PlanningActivity::PlanningActivity(const std::string & label,
				   const GraphTypes::Planning::Duration & duration)
  :_label(label),
   _description(""),
   _duration(duration)
{}

PlanningActivity::PlanningActivity(const std::string & label,
				   const std::string & description,
				   const GraphTypes::Planning::Duration & duration)
  :_label(label),
   _description(description),
   _duration(duration)
{}

PlanningActivity::PlanningActivity(const PlanningActivity & source)
 :_label(source._label),
  _description(source._description),
  _duration(source._duration)
{}

PlanningActivity & PlanningActivity::operator=(const PlanningActivity & source)
{
  _label = source._label;
  _description = source._description;
  _duration = source._duration;

  return *this;
}

const std::string & PlanningActivity::label()const
{
  return _label;
}

const std::string & PlanningActivity::description()const
{
  return _description;
}

const GraphTypes::Planning::Duration & PlanningActivity::duration()const
{
  return _duration;
}

void PlanningActivity::setLabel(const std::string & label)
{
  _label = label;
}

void PlanningActivity::setDescription(const std::string & description)
{
  _description = description;
}

void PlanningActivity::setDuration(const GraphTypes::Planning::Duration & duration)
{
  _duration = duration;
}
