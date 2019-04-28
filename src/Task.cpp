////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoSplash library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoSplash/Task.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoSplash/Configuration.hpp>
#include <TotoSplash/StepperMotorController.hpp>

#include <TotoSplash/Task.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoSplash
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								Task::Task 									( )
								:	id_(0),
									status_(Task::Status::Undefined),
									executionTime_(Time::Undefined()),
									duration_(Duration::Zero()),
									ruleId_(0)
{

}

								Task::Task 									( 	const 	uint&						anId,
																				const 	Time&						anExecutionTime,
																				const 	Duration&					aDuration,
																				const 	uint&						aRuleId								)
								:	id_(anId),
									status_(Task::Status::Pending),
									executionTime_(anExecutionTime),
									duration_(aDuration),
									ruleId_(aRuleId)
{

}

bool							Task::isDefined								( ) const
{
	return status_ != Task::Status::Undefined ;
}

bool							Task::isRuleDefined							( ) const
{
	return ruleId_ > 0 ;
}

uint							Task::getId									( ) const
{
	return id_ ;
}

Task::Status 					Task::getStatus								( ) const
{
	return status_ ;
}

Time 							Task::getExecutionTime						( ) const
{
	return executionTime_ ;
}

Duration						Task::getDuration							( ) const
{
	return duration_ ;
}

uint							Task::getRuleId								( ) const
{
	return ruleId_ ;
}

void							Task::setStatus								(	const 	Task::Status&				aStatus								)
{
	status_																		=		aStatus ;
}

void							Task::start									( )
{

	Serial.println("Starting task...") ;

	if (Duration(executionTime_, Time::Now()) <= Duration::Minutes(1))
	{

		// Executing task...

		// Serial.println("Executing task...") ;

		status_																	=		Task::Status::Executing ;

		pinMode(D1, OUTPUT) ;

		digitalWrite(D1, true) ;

	}
	else
	{
		status_ 																=		Task::Status::Failed ;
	}

	Serial.println("Starting task [OK]") ;

}

void							Task::stop									( )
{

	Serial.println("Stopping task...") ;

	if (status_ == Task::Status::Executing)
	{
		
		digitalWrite(D1, false) ;

		status_ 																=		Task::Status::Completed ;

	}

	Serial.println("Stopping task [OK]") ;

}

Task 							Task::Undefined								( )
{
	return Task() ;
}

String							Task::getStringOfStatus						(	const 	Task::Status&				aStatus								)
{

	switch (aStatus)
	{

		case Task::Status::Undefined:
			return "Undefined" ;

		case Task::Status::Pending:
			return "Pending" ;

		case Task::Status::Executing:
			return "Executing" ;

		case Task::Status::Completed:
			return "Completed" ;

		case Task::Status::Failed:
			return "Failed" ;

	}

	return "Error" ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////