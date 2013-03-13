#ifndef _MpmTask
#define _MpmTask

#include <string>
#include "GraphTypes.hpp"

class MpmTask
{
private:
  GraphTypes::Planning::Duration _duration;
  GraphTypes::Planning::Duration _earliest_beginning;
  GraphTypes::Planning::Duration _latest_beginning;
  std::string _label;

public:
  MpmTask();

  MpmTask(const std::string  & label);

  MpmTask(const GraphTypes::Planning::Duration  & duration);

  MpmTask(const std::string  & label,
	  const GraphTypes::Planning::Duration  & duration);

  MpmTask(const std::string  & label,
	  const GraphTypes::Planning::Duration & duration,
	  const GraphTypes::Planning::Duration & early_beginning,
	  const GraphTypes::Planning::Duration & late_beginning);

  MpmTask(const MpmTask  & source);

  MpmTask & operator=(const MpmTask & source);

  const GraphTypes::Planning::Duration & duration()const;
  const GraphTypes::Planning::Duration & earlyBegin()const;
  const GraphTypes::Planning::Duration & latelyBegin()const;
  const std::string & label()const;

  void setDuration(const GraphTypes::Planning::Duration & duration);
  void setEarlyBegin(const GraphTypes::Planning::Duration & early_beginning);
  void setLatelyBegin(const GraphTypes::Planning::Duration & late_beginning);
  void setLabel(const std::string & label);
};

#endif
