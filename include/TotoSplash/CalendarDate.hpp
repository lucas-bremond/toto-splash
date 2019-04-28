////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoSplash library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file						TotoSplash/CalendarDate.hpp
///	@author						Lucas Bremond <lucas@axelspace.com>
///	@date						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoSplash_CalendarDate_HPP_INCLUDED__
#define __TotoSplash_CalendarDate_HPP_INCLUDED__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore/SmingCore.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoSplash
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Time ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CalendarDate
{

	public:

		enum class Format
		{

			Undefined,
			DateTime,
			Date,
			Time

		} ;

								CalendarDate								( ) ;

								CalendarDate								(	const	int16_t&					aYear,
																				const	int8_t&						aMonth,
																				const	int8_t&						aDay,
																				const	int8_t&						anHourCount,
																				const	int8_t&						aMinuteCount,
																				const	int8_t&						aSecondCount						) ;

		bool					operator ==									(	const	CalendarDate&				aCalendarDate						) const ;
		bool					operator !=									(	const	CalendarDate&				aCalendarDate						) const ;

		bool					isDefined									( ) const ;

		int16_t					getYear										( ) const ;
		int8_t					getMonth									( ) const ;
		int8_t					getDay										( ) const ;
		int8_t					getHours									( ) const ;
		int8_t					getMinutes									( ) const ;
		int8_t					getSeconds									( ) const ;

		String					getString									(	const	CalendarDate::Format&		aFormat								=		CalendarDate::Format::DateTime ) const ;

		void					setYear										(	const	int16_t&					aYearCount							) ;
		void					setMonth									(	const	int8_t&						aMonthCount							) ;
		void					setDay										(	const	int8_t&						aDayCount							) ;
		void					setHours									(	const	int8_t&						aHourCount							) ;
		void					setMinutes									(	const	int8_t&						aMinuteCount						) ;
		void					setSeconds									(	const	int8_t&						aSecondCount						) ;

		static CalendarDate		Undefined									( ) ;

		static CalendarDate		Time										(	const	TotoSplash::Time&			aTime								) ;

		static CalendarDate		Parse										(	const	String&						aString								) ;

	private:

		int16_t					year_ ;
		int8_t					month_ ;
		int8_t					day_ ;
		int8_t					hours_ ;
		int8_t					minutes_ ;
		int8_t					seconds_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////