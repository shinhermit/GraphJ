#include "MpmTask.hpp"

MpmTask::MpmTask():
  _duration(0),
  _earliest_beginning(0),
  _latest_beginning(0),
  _label("")
{}

MpmTask::MpmTask(const std::string  & label):
  _duration(0),
  _earliest_beginning(0),
  _latest_beginning(0),
  _label(label)
{}

MpmTask::MpmTask(const GraphTypes::Planning::Duration  & duration):
  _duration(duration),
  _earliest_beginning(0),
  _latest_beginning(0),
  _label("")
{}

MpmTask::MpmTask(const std::string  & label,
		 const GraphTypes::Planning::Duration  & duration):
  _duration(duration),
  _earliest_beginning(0),
  _latest_beginning(0),
  _label(label)
{}

MpmTask::MpmTask(const std::string  & label,
	const GraphTypes::Planning::Duration & duration,
	const GraphTypes::Planning::Duration & early_beginning,
	const GraphTypes::Planning::Duration & late_beginning):
  _duration(duration),
  _earliest_beginning(early_beginning),
  _latest_beginning(late_beginning),
  _label(label)
{}

MpmTask::MpmTask(const MpmTask  & source):
  _duration(source._duration),
  _earliest_beginning(source._earliest_beginning),
  _latest_beginning(source._latest_beginning),
  _label(source._label)
{}

MpmTask & MpmTask::operator=(const MpmTask & source)
{
  _duration = source._duration;
  _earliest_beginning = source._earliest_beginning;
  _latest_beginning = source._latest_beginning;
  _label = source._label;

  return *this;
}

const GraphTypes::Planning::Duration & MpmTask::duration()const
{
  return _duration;
}

const GraphTypes::Planning::Duration & MpmTask::earlyBegin()const
{
  return _earliest_beginning;
}

const GraphTypes::Planning::Duration & MpmTask::latelyBegin()const
{
  return _latest_beginning;
}

const std::string & MpmTask::label()const
{
  return _label;
}

void MpmTask::setDuration(const GraphTypes::Planning::Duration & duration)
{
  _duration = duration;
}

void MpmTask::setEarlyBegin(const GraphTypes::Planning::Duration & early_beginning)
{
  _earliest_beginning = early_beginning;
}

void MpmTask::setLatelyBegin(const GraphTypes::Planning::Duration & late_beginning)
{
  _latest_beginning = late_beginning;
}

void MpmTask::setLabel(const std::string & label)
{
  _label = label;
}
