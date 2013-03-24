#ifndef _MpmTask
#define _MpmTask

#include <string>
#include "GraphTypes.hpp"

class MpmTask
{
private:
  std::string _label;

  GraphTypes::Planning::Duration _duration;
  GraphTypes::Planning::Duration _early_start;
  GraphTypes::Planning::Duration _late_start;

  GraphTypes::Planning::Duration _total_slack;
  GraphTypes::Planning::Duration _free_slack;
  GraphTypes::Planning::Duration _sure_slack;

public:
  MpmTask();

  MpmTask(const std::string  & label);

  MpmTask(const GraphTypes::Planning::Duration  & duration);

  MpmTask(const std::string  & label,
	  const GraphTypes::Planning::Duration  & duration);

  MpmTask(const MpmTask  & source);

  MpmTask & operator=(const MpmTask & source);

  const std::string & label()const;

  const GraphTypes::Planning::Duration & duration()const;
  const GraphTypes::Planning::Duration & earlyStart()const;
  const GraphTypes::Planning::Duration & lateStart()const;

  const GraphTypes::Planning::Duration & totalSlack()const;
  const GraphTypes::Planning::Duration & freeSlack()const;
  const GraphTypes::Planning::Duration & sureSlack()const;

  void setLabel(const std::string & label);

  void setDuration(const GraphTypes::Planning::Duration & duration);
  void setEarlyStart(const GraphTypes::Planning::Duration & early_start);
  void setLateStart(const GraphTypes::Planning::Duration & late_start);

  void setTotalSlack(const GraphTypes::Planning::Duration & duration);
  void setFreeSlack(const GraphTypes::Planning::Duration & early_start);
  void setSureSlack(const GraphTypes::Planning::Duration & late_start);
};

#endif
