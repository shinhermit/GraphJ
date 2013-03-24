#ifndef _PlanningActivity
#define _PlanningActivity

#include <set>
#include <string>
#include "GraphTypes.hpp"

class PlanningActivity
{
public:
  typedef std::set<GraphTypes::Planning::Activity_id>::const_iterator PreceedingsIterator;

private:
  std::string _label;
  std::string _description;
  GraphTypes::Planning::Duration _duration;

public:
  PlanningActivity();

  PlanningActivity(const std::string & label,
		   const GraphTypes::Planning::Duration & duration);

  PlanningActivity(const std::string & label,
		   const std::string & description,
		   const GraphTypes::Planning::Duration & duration);

  PlanningActivity(const PlanningActivity & source);

  PlanningActivity & operator=(const PlanningActivity & source);

  const std::string & label()const;

  const std::string & description()const;

  const GraphTypes::Planning::Duration & duration()const;

  void setLabel(const std::string & label);

  void setDescription(const std::string & label);

  void setDuration(const GraphTypes::Planning::Duration & duration);
};

#endif
