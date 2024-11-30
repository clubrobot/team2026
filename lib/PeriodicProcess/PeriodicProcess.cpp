#include "PeriodicProcess.h"


bool PeriodicProcess::update()
{

	float a = m_clock.getElapsedTime();
	if (m_enabled &&  a > m_timestep)
	{
		float timestep = m_clock.restart();
		process(timestep);
		return true;
	}
	return false;
}

void PeriodicProcess::enable()
{
	if (!m_enabled)
	{
		m_enabled = true;
		m_clock.restart();
		onProcessEnabling();
	}
}

void PeriodicProcess::disable()
{
	if (m_enabled)
	{
		m_enabled = false;
		onProcessDisabling();
	}
}
