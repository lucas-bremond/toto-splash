////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoSplash library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoSplash/Time.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoSplash/CalendarDate.hpp>

#include <TotoSplash/Time.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoSplash
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								Time::Time 									( )
								:	timestamp_(0)
{

}

bool							Time::operator ==							(	const 	Time&						aTime 								) const
{
	return (timestamp_ == aTime.timestamp_) ;
}

bool							Time::operator !=							(	const 	Time&						aTime 								) const
{
	return (timestamp_ != aTime.timestamp_) ;
}

bool							Time::operator <=							(	const 	Time&						aTime 								) const
{
	return (timestamp_ <= aTime.timestamp_) ;
}

bool							Time::operator <							(	const 	Time&						aTime 								) const
{
	return (timestamp_ < aTime.timestamp_) ;
}

bool							Time::operator >=							(	const 	Time&						aTime 								) const
{
	return (timestamp_ >= aTime.timestamp_) ;
}

bool							Time::operator >							(	const 	Time&						aTime 								) const
{
	return (timestamp_ > aTime.timestamp_) ;
}

Time 							Time::operator +							(	const 	Duration&					aDuration							) const
{

	if (this->isDefined())
	{

		Time 					time(*this) ;

		time.timestamp_														   +=		aDuration.getSeconds() ;

		return time ;

	}

	return Time::Undefined() ;

}

bool							Time::isDefined								( ) const
{
	return (timestamp_ > 0) ;
}

time_t 							Time::getUnixTime							( ) const
{
	return timestamp_ ;
}

String							Time::getString								( ) const
{
	return CalendarDate::Time(*this).getString() ;
}

Time 							Time::Undefined								( )
{
	
	Time 						time ;

	time.timestamp_																=		0 ;

	return time ;

}

Time 							Time::Now									( )
{

	// time_t						systemTime										=		RTC.getRtcSeconds() ;
	// time_t 						UTCTime											=		systemTime - (timezoneDiff * SECS_PER_HOUR) ;

	// return Time(UTCTime) ;

	// TBM => probably wrong

	// return Time::Unix(SystemClock.now(TimeZone::eTZ_UTC).toUnixTime()) ;

	return Time::Undefined() ; // [TBR]

}

Time 							Time::Unix									( 	const 	time_t&						aTimestamp							)
{

	Time 						time ;

	time.timestamp_																=		aTimestamp ;

	return time ;

}

Time 							Time::CalendarDate							( 	const 	TotoSplash::CalendarDate&		aCalendarDate						)
{
	// return Time::Unix(DateTime::convertToUnixTime(aCalendarDate.getSeconds(), aCalendarDate.getMinutes(), aCalendarDate.getHours(), aCalendarDate.getDay(), aCalendarDate.getMonth() - 1, aCalendarDate.getYear())) ;
	return Time::Undefined() ; // [TBR]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////