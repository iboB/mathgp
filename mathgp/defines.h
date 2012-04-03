//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this 
//  distribution for details about the copyright
#pragma once

#define MATHGP_FOR_VALUES(counter) for(size_type counter=0; counter<value_count; ++counter)

#define MATHGP_EACH_VAL for(size_type i=0; i<value_count; ++i) at(i)

#define MATHGP_EACH_OF(x) for(size_type i=0; i<value_count; ++i) x.at(i)
