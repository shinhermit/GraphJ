#include "MpmTask.hpp"

MpmTask::MpmTask():
  _label(""),

  _duration(0),
  _early_start(0),
  _late_start(0),

  _total_slack(0),
  _free_slack(0),
  _sure_slack(0)
{}

MpmTask::MpmTask(const std::string  & label):
  _label(label),

  _duration(0),
  _early_start(0),
  _late_start(0),

  _total_slack(0),
  _free_slack(0),
  _sure_slack(0)
{}

MpmTask::MpmTask(const GraphTypes::Planning::Duration  & duration):
  _label(""),

  _duration(duration),
  _early_start(0),
  _late_start(0),

  _total_slack(0),
  _free_slack(0),
  _sure_slack(0)
{}

MpmTask::MpmTask(const std::string  & label,
		 const GraphTypes::Planning::Duration  & duration):
  _label(label),

  _duration(duration),
  _early_start(0),
  _late_start(0),

  _total_slack(0),
  _free_slack(0),
  _sure_slack(0)
{}

MpmTask::MpmTask(const MpmTask  & source):
  _label(source._label),

  _duration(source._duration),
  _early_start(source._early_start),
  _late_start(source._late_start),

  _total_slack(source._total_slack),
  _free_slack(source._free_slack),
  _sure_slack(source._sure_slack)
{}

MpmTask & MpmTask::operator=(const MpmTask & source)
{
  _duration = source._duration;

  _early_start = source._early_start;
  _late_start = source._late_start;
  _label = source._label;

  _total_slack = source._total_slack;
  _free_slack = source._free_slack;
  _sure_slack = source._sure_slack;

  return *this;
}

const std::string & MpmTask::label()const
{
  return _label;
}

const GraphTypes::Planning::Duration & MpmTask::duration()const
{
  return _duration;
}

const GraphTypes::Planning::Duration & MpmTask::earlyStart()const
{
  return _early_start;
}

const GraphTypes::Planning::Duration & MpmTask::lateStart()const
{
  return _late_start;
}

const GraphTypes::Planning::Duration & MpmTask::totalSlack()const
{
  return _total_slack;
}

const GraphTypes::Planning::Duration & MpmTask::freeSlack()const
{
  return _free_slack;
}

const GraphTypes::Planning::Duration & MpmTask::sureSlack()const
{
  return _sure_slack;
}

void MpmTask::setLabel(const std::string & label)
{
  _label = label;
}

void MpmTask::setDuration(const GraphTypes::Planning::Duration & duration)
{
  _duration = duration;
}

void MpmTask::setEarlyStart(const GraphTypes::Planning::Duration & early_start)
{
  _early_start = early_start;
}

void MpmTask::setLateStart(const GraphTypes::Planning::Duration & late_start)
{
  _late_start = late_start;
}

void MpmTask::setTotalSlack(const GraphTypes::Planning::Duration & total_slack)
{
  _total_slack = total_slack;
}

void MpmTask::setFreeSlack(const GraphTypes::Planning::Duration & free_slack)
{
  _free_slack = free_slack;
}

void MpmTask::setSureSlack(const GraphTypes::Planning::Duration & sure_slack)
{
  _sure_slack = sure_slack;
}

