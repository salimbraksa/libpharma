//
//  sb_date.h
//  PharmApp
//
//  Created by Salim Braksa on 1/2/16.
//  Copyright © 2016 Braksa Salim. All rights reserved.
//

#ifndef sb_date_h
#define sb_date_h

#include <stdio.h>

typedef enum {
    Day = 1 << 0,
    Month = 1 << 1,
    Year = 1 << 2,
    None = 1 << 3
} DateComponents ;

#endif /* sb_date_h */
