/* ======================================================================
   Useful macros

   Modification History
   Date      Author  Comment
   ----------------------------------------------------------------------
   12-20-92  LLW     Created and Writen
   02-18-02  LLW     Added more general macros and #defines
   
   ====================================================================== */

#ifndef JASON_MACRO_INCLUDE
#define JASON_MACRO_INCLUDE

// 19 Feb 2002 LLW Moved from jasontalk.h
#define TRUE    1
#define FALSE   0

#define fsign(x)  ((x)>0.0 ? 1.0 : ( (x)<0 ? -1.0 : 0.0 ) )
#define fssqrt(x) (fsign((x)) * sqrt(fabs(x)))


#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#define inrange(val,min,max) ( ((val) >= (min)) && ((val) <= (max)))
#define fsat(x,max) ((x)>fabs(max))? fabs(max) : (((x)<(-fabs(max)))? (-fabs(max)): x)

#define state_pos_assign( target, source, dof ) { target->pos[dof] = source->pos[dof];  target->pos_source[dof] = source->pos_source[dof]; target->pos_time[dof] = source->pos_time[dof]; }

#define state_vel_assign( target, source, dof ) { target->vel[dof] = source->vel[dof];  target->vel_source[dof] = source->vel_source[dof]; target->vel_time[dof] = source->vel_time[dof]; }

#define state_acc_assign( target, source, dof ) { target->acc[dof] = source->acc[dof];  target->acc_source[dof] = source->acc_source[dof]; target->acc_time[dof] = source->acc_time[dof]; }

#endif
