////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoSplash library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoSplash/Duration.hpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoSplash_Duration_HPP_INCLUDED__
#define __TotoSplash_Duration_HPP_INCLUDED__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore/SmingCore.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoSplash
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Time ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Duration
{

	public:

								Duration 									( ) ;

								Duration 									( 	const 	Time&						anEarlierTime,
																				const 	Time&						aLaterTime							) ;

		bool					operator ==									(	const 	Duration&					aDuration 							) const ;
		bool					operator !=									(	const 	Duration&					aDuration 							) const ;
		bool					operator <=									(	const 	Duration&					aDuration 							) const ;
		bool					operator <									(	const 	Duration&					aDuration 							) const ;
		bool					operator >=									(	const 	Duration&					aDuration 							) const ;
		bool					operator >									(	const 	Duration&					aDuration 							) const ;

		bool					isDefined									( ) const ;

		int						getSeconds									( ) const ;
		String					getString									( ) const ;

		static Duration 		Undefined									( ) ;

		static Duration 		Zero										( ) ;

		static Duration 		Seconds										( 	const 	int&						aCount								) ;
		static Duration 		Minutes										( 	const 	int&						aCount								) ;
		static Duration 		Hours										( 	const 	int&						aCount								) ;
		static Duration 		Days										( 	const 	int&						aCount								) ;
		static Duration 		Weeks										( 	const 	int&						aCount								) ;

		static Duration			Parse										(	const	String&						aString								) ;

	private:

		bool					defined_ ;
		int						duration_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////