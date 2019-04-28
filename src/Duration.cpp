////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoSplash library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoSplash/Duration.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoSplash/Time.hpp>
#include <TotoSplash/Duration.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoSplash
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								Duration::Duration 							( )
								:	defined_(false),
									duration_(0)
{

}

								Duration::Duration 							( 	const 	Time&						anEarlierTime,
																				const 	Time&						aLaterTime							)
								:	defined_(true),
									duration_(aLaterTime.getUnixTime() - anEarlierTime.getUnixTime())
{

}

bool							Duration::operator ==						(	const 	Duration&					aDuration 							) const
{
	return (duration_ == aDuration.duration_) ;
}

bool							Duration::operator !=						(	const 	Duration&					aDuration 							) const
{
	return (duration_ != aDuration.duration_) ;
}

bool							Duration::operator <=						(	const 	Duration&					aDuration 							) const
{
	return (duration_ <= aDuration.duration_) ;
}

bool							Duration::operator <						(	const 	Duration&					aDuration 							) const
{
	return (duration_ < aDuration.duration_) ;
}

bool							Duration::operator >=						(	const 	Duration&					aDuration 							) const
{
	return (duration_ >= aDuration.duration_) ;
}

bool							Duration::operator >						(	const 	Duration&					aDuration 							) const
{
	return (duration_ > aDuration.duration_) ;
}

bool							Duration::isDefined							( ) const
{
	return defined_ ;
}

int								Duration::getSeconds						( ) const
{
	return duration_ ;
}

String							Duration::getString							( ) const
{

	char buffer[64] ;
	
	sprintf(buffer, "%d [sec]", duration_) ;	

	return String(buffer) ;

}

Duration 						Duration::Undefined							( )
{
	
	Duration 					duration ;

	duration.defined_															=		false ;
	duration.duration_															=		0 ;

	return duration ;

}

Duration 						Duration::Zero								( )
{
	
	Duration 					duration ;

	duration.defined_															=		true ;
	duration.duration_															=		0 ;

	return duration ;

}

Duration 						Duration::Seconds							( 	const 	int&						aCount								)
{

	Duration 					duration ;

	duration.defined_															=		true ;
	duration.duration_															=		aCount ;

	return duration ;

}

Duration 						Duration::Minutes							( 	const 	int&						aCount								)
{

	Duration 					duration ;

	duration.defined_															=		true ;
	duration.duration_															=		aCount * 60 ;

	return duration ;

}

Duration 						Duration::Hours								(	const 	int&						aCount								)
{

	Duration 					duration ;

	duration.defined_															=		true ;
	duration.duration_															=		aCount * 60 * 60 ;

	return duration ;

}

Duration 						Duration::Days								(	const 	int&						aCount								)
{

	Duration 					duration ;

	duration.defined_															=		true ;
	duration.duration_															=		aCount * 60 * 60 * 24 ;

	return duration ;

}

Duration 						Duration::Weeks								(	const 	int&						aCount								)
{

	Duration 					duration ;

	duration.defined_															=		true ;
	duration.duration_															=		aCount * 60 * 60 * 24 * 7 ;

	return duration ;

}

Duration						Duration::Parse								(	const 	String&						aString								)
{

	Serial.println("Duration::Parse") ;

	int16_t 					seconds											=		aString.toInt() ;

	return Duration::Seconds(seconds) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////